#include "apSimpleRegister.hpp"
#include "utils/itkCommandLineArgumentParser.h"

using namespace ap;


int main ( int argc, char* argv[] ) {

  if ( argc < 4 ) {
    std::cerr << "Usage: " << argv[0] << " <path_to_images> <fixed_name> <moving_name> <parameterFile> <output_image>\n";
    return SimpleRegister::OK;
  }
  
  // TODO: Complete command line argument parser function
  itk::CommandLineArgumentParser::Pointer parser = itk::CommandLineArgumentParser::New();
  parser->SetCommandLineArguments( argc, argv );

  shared_ptr<SimpleRegister> imgregister(new SimpleRegister(string(argv[1])));
  imgregister->GetImages(string(argv[2]),string(argv[3]));
  imgregister->SetParameterMapFromFile(string(argv[4])); 
  imgregister->ExecuteRegister();  
  imgregister->SetRegisteredImage(string(argv[5]));

  return SimpleRegister::OK;
}

