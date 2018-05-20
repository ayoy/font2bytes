#include <iostream>
#include <getopt.h>
#include "png_read.h"
#include "inputpngimage.h"
#include <f2b.h>

int main(int argc, char *argv[]) {
  if(argc != 2) abort();

  png_data *imageData = png_data_create(argv[1]);

  InputPNGImage inputImage(imageData);
  SourceCodeOptions options(SourceCodeOptions::LSB, false);
  CCodeGenerator generator(options);

  FixedConverter converter(8, 8, FixedConverter::TopToBottom);

  ConverterError error = converter.convert(inputImage, &generator);

  if (error != ConverterError::NoError) {
      std::cout << "Error while converting image: " <<
                   error.summary << " (" << error.description << ")" <<
                   std::endl;
      return 1;
  }

  std::cout << generator.sourceCode();

  return 0;
}
