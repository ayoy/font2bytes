#include <iostream>
#include <unistd.h>
#include "png_read.h"
#include "inputpngimage.h"
#include <f2b.h>
#include <functional>
#include <map>

typedef std::function<SourceCodeGenerator * (const SourceCodeOptions &)> GeneratorLambda;

struct SourceCodeGeneratorItem {
    SourceCodeGeneratorItem(std::string identifier,
                            GeneratorLambda createGenerator) :
        identifier(identifier),
        createGenerator(createGenerator)
    {}

    std::string identifier;
    GeneratorLambda createGenerator;
};


void printUsage(char *programName) {
    std::cerr << "Usage: " << programName << " -h font_height -w font_width [-i] [-L|-M] "
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
              << "  " << CCodeGenerator::identifier << "\t- " << CCodeGenerator::description << std::endl
              << "  " << ArduinoCodeGenerator::identifier << "\t- " << ArduinoCodeGenerator::description << std::endl
              << "  " << PythonListCodeGenerator::identifier << "\t- " << PythonListCodeGenerator::description << std::endl
              << "  " << PythonBytesCodeGenerator::identifier << "\t- " << PythonBytesCodeGenerator::description << std::endl;
}


int main(int argc, char *argv[]) {
    int opt;
    bool fontWidthProvided = false, fontHeightProvided = false;
    uint8_t fontHeight = 0, fontWidth = 0;

    SourceCodeOptions options;
    std::string generatorIdentifier = CCodeGenerator::identifier;
    std::map<std::string, GeneratorLambda> generators;

    generators.insert(
                std::pair<std::string, GeneratorLambda>(
                    CCodeGenerator::identifier,
                    [](const SourceCodeOptions &options) { return new CCodeGenerator(options); })
            );
    generators.insert(
                std::pair<std::string, GeneratorLambda>(
                    ArduinoCodeGenerator::identifier,
                    [](const SourceCodeOptions &options) { return new ArduinoCodeGenerator(options); })
            );
    generators.insert(
                std::pair<std::string, GeneratorLambda>(
                    PythonListCodeGenerator::identifier,
                    [](const SourceCodeOptions &options) { return new PythonListCodeGenerator(options); })
            );
    generators.insert(
                std::pair<std::string, GeneratorLambda>(
                    PythonBytesCodeGenerator::identifier,
                    [](const SourceCodeOptions &options) { return new PythonBytesCodeGenerator(options); })
            );

    while ((opt = getopt(argc, argv, "w:h:f:ilm")) != -1) {
        switch (opt) {
        case 'w':
            fontWidthProvided = true;
            fontWidth = atoi(optarg);
            break;
        case 'h':
            fontHeightProvided = true;
            fontHeight = atoi(optarg);
            break;
        case 'i':
            options.shouldInvertBits = true;
            break;
        case 'l':
            options.bitNumbering = SourceCodeOptions::LSB;
            break;
        case 'm':
            options.bitNumbering = SourceCodeOptions::MSB;
            break;
        case 'f':
            generatorIdentifier = std::string(optarg);
            break;
        default: /* '?' */
            printUsage(argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    if (!fontHeightProvided || fontHeight == 0) {
        std::cerr << std::endl
                  << "Font height not provided or invalid" << std::endl
                  << std::endl;
        printUsage(argv[0]);
        exit(EXIT_FAILURE);
    }

    if (!fontWidthProvided || fontWidth == 0) {
        std::cerr << std::endl
                  << "Font width not provided or invalid" << std::endl
                  << std::endl;
        printUsage(argv[0]);
        exit(EXIT_FAILURE);
    }

    SourceCodeGenerator *generator = nullptr;

    auto it = generators.find(generatorIdentifier);
    if (it != generators.end()) {
        generator = (*it).second(options);
    } else {
        generator = new CCodeGenerator(options);
    }

//    if (optind < argc) {
//        std::cout << "path: " << argv[optind] << std::endl;
//    }

    png_data *imageData = png_data_create(argv[optind]);
    InputPNGImage inputImage(imageData);

    FixedConverter converter(fontWidth, fontHeight, FixedConverter::TopToBottom);
    ConverterError error = converter.convert(inputImage, generator);

    if (error != ConverterError::NoError) {
        std::cout << "Error while converting image: "
                  << error.summary << " (" << error.description << ")"
                  << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << generator->sourceCode();

    delete generator;

    return EXIT_SUCCESS;
}
