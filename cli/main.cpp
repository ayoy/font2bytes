#include <iostream>
#include <fstream>
#include <unistd.h>
#include "png_read.h"
#include "inputpngimage.h"
#include <f2b.h>
#include <functional>
#include <map>

typedef std::function<std::unique_ptr<SourceCodeGenerator>(SourceCodeOptions)> GeneratorLambda;

struct SourceCodeGeneratorItem {
    SourceCodeGeneratorItem(std::string identifier,
                            GeneratorLambda createGenerator) :
        identifier(std::move(identifier)),
        createGenerator(createGenerator)
    {}

    std::string identifier;
    GeneratorLambda createGenerator;
};

struct Config {
    bool fontWidthProvided { false };
    bool fontHeightProvided { false };
    uint8_t fontHeight { 0 };
    uint8_t fontWidth { 0 };
    SourceCodeOptions options;
    std::string generatorIdentifier  { CCodeGenerator::identifier };
    char *outputFilePath { nullptr };
    char *inputFilePath { nullptr };
};

void printUsage(char *programName) {
    std::cerr << "Usage: " << programName << " -h font_height -w font_width [-i] [-l|-m] "
              << "[-f output_format] path_to_image [-o path_to_output_file]" << std::endl
              << std::endl
              << "Required arguments:" << std::endl
              << "  -h\tfont height in pixels" << std::endl
              << "  -w\tfont width in pixels" << std::endl
              << std::endl
              << "Optional arguments:" << std::endl
              << "  -f\toutput source code format (defaults to C/C++ array)" << std::endl
              << "  -i\tinvert bits in output" << std::endl
              << "  -l\tstore bytes in LSB mode (default)" << std::endl
              << "  -m\tstore bytes in MSB mode" << std::endl
              << "  -o\tpath to output file (if not provided, code outputs to stdout)" << std::endl
              << std::endl
              << "Available output formats:" << std::endl
              << "  " << CCodeGenerator::identifier << "\t\t- " << CCodeGenerator::description << std::endl
              << "  " << ArduinoCodeGenerator::identifier << "\t\t- " << ArduinoCodeGenerator::description << std::endl
              << "  " << PythonListCodeGenerator::identifier << "\t\t- " << PythonListCodeGenerator::description << std::endl
              << "  " << PythonBytesCodeGenerator::identifier << "\t\t- " << PythonBytesCodeGenerator::description << std::endl;
}

void parseOpts(int argc, char *argv[], Config &config) {
    int opt;
    while ((opt = getopt(argc, argv, "w:h:f:ilmo:")) != -1) {
        switch (opt) {
        case 'w':
            config.fontWidthProvided = true;
            config.fontWidth = atoi(optarg);
            break;
        case 'h':
            config.fontHeightProvided = true;
            config.fontHeight = atoi(optarg);
            break;
        case 'i':
            config.options.shouldInvertBits = true;
            break;
        case 'l':
            config.options.bitNumbering = SourceCodeOptions::LSB;
            break;
        case 'm':
            config.options.bitNumbering = SourceCodeOptions::MSB;
            break;
        case 'f':
            config.generatorIdentifier = std::string(optarg);
            break;
        case 'o':
            config.outputFilePath = optarg;
            break;
        default: /* '?' */
            printUsage(argv[0]);
            exit(EXIT_FAILURE);
        }
    }
}

void parseCommandLineArguments(int argc, char *argv[], Config &config) {
    parseOpts(argc, argv, config);
    if (optind < argc) {
        config.inputFilePath = argv[optind];
        optind += 1;
    }
    parseOpts(argc, argv, config);


    if (!config.fontHeightProvided || config.fontHeight == 0) {
        std::cerr << std::endl
                  << "Font height not provided or invalid" << std::endl
                  << std::endl;
        printUsage(argv[0]);
        exit(EXIT_FAILURE);
    }

    if (!config.fontWidthProvided || config.fontWidth == 0) {
        std::cerr << std::endl
                  << "Font width not provided or invalid" << std::endl
                  << std::endl;
        printUsage(argv[0]);
        exit(EXIT_FAILURE);
    }
}



int main(int argc, char *argv[]) {
    Config config;

    std::map<std::string, GeneratorLambda> generators;

    generators.emplace(
                std::make_pair(
                    CCodeGenerator::identifier,
                    [](SourceCodeOptions options) { return std::make_unique<CCodeGenerator>(std::move(options)); }
                )
            );
    generators.emplace(
                std::make_pair(
                    ArduinoCodeGenerator::identifier,
                    [](SourceCodeOptions options) { return std::make_unique<ArduinoCodeGenerator>(std::move(options)); }
                )
            );
    generators.emplace(
                std::make_pair(
                    PythonListCodeGenerator::identifier,
                    [](SourceCodeOptions options) { return std::make_unique<PythonListCodeGenerator>(std::move(options)); }
                )
            );
    generators.emplace(
                std::make_pair(
                    PythonBytesCodeGenerator::identifier,
                    [](SourceCodeOptions options) { return std::make_unique<PythonBytesCodeGenerator>(std::move(options)); }
                )
            );

    parseCommandLineArguments(argc, argv, config);

    auto generator = [generators, config]() -> std::unique_ptr<SourceCodeGenerator> {
        auto it = generators.find(config.generatorIdentifier);
        if (it != generators.end()) {
            return std::get<GeneratorLambda>(*it)(config.options);
        }
        return std::make_unique<CCodeGenerator>(config.options);
    }();

    std::unique_ptr<png_data> imageData { png_data_create(config.inputFilePath) };
    InputPNGImage inputImage(std::move(imageData));

    FixedConverter converter(config.fontWidth, config.fontHeight, FixedConverter::TopToBottom);
    auto error = converter.convert(inputImage, *(generator.get()));

    if (error != ConverterError::NoError) {
        std::cerr << "Error while converting image: "
                  << error.summary << " (" << error.description << ")"
                  << std::endl;
        exit(EXIT_FAILURE);
    }

    if (config.outputFilePath) {
        std::fstream file;
        file.open(config.outputFilePath, std::fstream::out);
        if (file.rdstate() == std::fstream::failbit) {
            std::cerr << "Failed to write to file at " << config.outputFilePath << std::endl;
            exit(EXIT_FAILURE);
        } else {
            file << generator->sourceCode();
            file.close();
            std::cout << "Successfully wrote source code to " << config.outputFilePath << std::endl;
        }
    } else {
        std::cout << generator->sourceCode();
    }

    return EXIT_SUCCESS;
}
