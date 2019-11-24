#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstring>
#include "png_read.h"
#include "inputpngimage.h"
#include <f2b.h>
#include <functional>
#include <map>

typedef std::function<std::unique_ptr<SourceCodeGeneratorInterface>(SourceCodeOptions)> GeneratorLambda;


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

static void printUsage(char *programName)
{
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

static void parseOpts(int argc, char *argv[], Config &config)
{
    int opt;
    while ((opt = getopt(argc, argv, "w:h:f:ilmo:")) != -1) {
        switch (opt) {
        case 'w':
            config.fontWidthProvided = true;
            config.fontWidth = static_cast<uint8_t>(strtol(optarg, nullptr, 10));
            break;
        case 'h':
            config.fontHeightProvided = true;
            config.fontHeight = static_cast<uint8_t>(strtol(optarg, nullptr, 10));
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

static void parseCommandLineArguments(int argc, char *argv[], Config &config)
{
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

template <typename T>
static auto make_generator_pair()
{
    return std::make_pair(
            T::identifier,
            [](SourceCodeOptions options) {
                return std::make_unique<SourceCodeGenerator<T>>(std::move(options));
            }
    );
}

static std::unique_ptr<SourceCodeGeneratorInterface> makeGenerator(const Config &config)
{
    std::map<const std::string, GeneratorLambda> generators;

    generators.emplace(make_generator_pair<CCodeGenerator>());
    generators.emplace(make_generator_pair<ArduinoCodeGenerator>());
    generators.emplace(make_generator_pair<PythonListCodeGenerator>());
    generators.emplace(make_generator_pair<PythonBytesCodeGenerator>());

    auto it = generators.find(config.generatorIdentifier);
    if (it != generators.end()) {
        return std::get<1>(*it)(config.options);
    }
    return std::make_unique<SourceCodeGenerator<CCodeGenerator>>(config.options);
}

int main(int argc, char *argv[]) {
    Config config;
    parseCommandLineArguments(argc, argv, config);

    auto inputImage = InputPNGImage::construct(std::string(config.inputFilePath));
    if (!inputImage.has_value()) {
        std::cerr << "Error while converting image: " 
	    << std::strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }

    auto generator = makeGenerator(config);

    FixedWidthFontConverter converter(config.fontWidth,
            config.fontHeight,
            FixedWidthFontConverter::TopToBottom,
            std::move(generator));

    ConverterError error;
    auto sourceCode = converter.convert(*inputImage, &error);

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
            file << sourceCode;
            file.close();
            std::cout << "Successfully wrote source code to " << config.outputFilePath << std::endl;
        }
    } else {
        std::cout << sourceCode;
    }

    return EXIT_SUCCESS;
}
