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
    private:
      enum parameter_map_code {translation, rigid, affine, bspline, no_value};

    public:
      SimpleRegister(string project_path);
      void GetImages(string fixed, string moving);
      void SetRegisteredImage(string registered_image);
      void SetParameterMapFromFile(string parameter_map_file);
      void SetParameterMapFromTemplate(string parameter_map_template);
      void GetTransformationMatrix();
      void ShowImage();
      void SetFilenameLog(string filename);
      void LogToFile(bool on);
      void LogToConsole(bool on);
      void ExecuteRegister();
      ~SimpleRegister();

    private:
      parameter_map_code GetParameterMapTemplateStringValues(string const& in_string);
      void SetImageSize( sitk::Image * image);
      vector<unsigned int> GetImageSize( sitk::Image image);
      bool log;      
      
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
      sitk::Image GetRegisteredImage() const { return elastix->GetResultImage(); }
    };
}

#endif // APSIMPLEREGISTER_H
