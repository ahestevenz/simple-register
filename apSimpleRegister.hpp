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
      SimpleRegister();
      void GetImages(string path, string fixed, string moving);
      void SetRegisteredImage(string registered_image);
      ~SimpleRegister();
	
    private:
      shared_ptr<sitk::SimpleElastix> elastix;
      shared_ptr<sitk::ImageFileReader> fixed_reader, moving_reader;
      
    public:
      static const int OK=0000;
      static const int FAILED=0001;
      
    public:
      sitk::Image GetFixedImage() const { return fixed_reader->Execute(); }
      sitk::Image GetMovingImage() const { return moving_reader->Execute(); }
    };
}

#endif // APSIMPLEREGISTER_H
