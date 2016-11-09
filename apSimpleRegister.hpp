#ifndef APSIMPLEREGISTER_H
#define APSIMPLEREGISTER_H

#include <SimpleITK.h>
#include <boost/shared_ptr.hpp>
#include <iostream>
#include <stdlib.h>

using namespace std;
using boost::shared_ptr;
namespace sitk = itk::simple;

namespace ap {

    class SimpleRegister
    {
    public:
      SimpleRegister(string project_path);
      void GetImages(string fixed, string moving);
      void SetRegisteredImage(string registered_image);
      void SetParameterMapFromFile(string parameter_map_file);
      void ExecuteRegister();
      ~SimpleRegister();
	
    private:
      shared_ptr<sitk::SimpleElastix> elastix;
      shared_ptr<sitk::ImageFileReader> fixedReader, movingReader;
      shared_ptr<sitk::ImageFileWriter> registeredImageWriter;
      string pathToImages;
      
    public:
      static const int OK=0000;
      static const int FAILED=0001;
      
    public:
      sitk::Image GetFixedImage() const { return fixedReader->Execute(); }
      sitk::Image GetMovingImage() const { return movingReader->Execute(); }
    };
}

#endif // APSIMPLEREGISTER_H
