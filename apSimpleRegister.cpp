#include "apSimpleRegister.hpp"

using namespace ap;

SimpleRegister::SimpleRegister(string project_path)
  :elastix(shared_ptr<sitk::SimpleElastix> (new sitk::SimpleElastix()))
  ,fixedReader(shared_ptr<sitk::ImageFileReader> (new sitk::ImageFileReader()))
  ,movingReader(shared_ptr<sitk::ImageFileReader> (new sitk::ImageFileReader()))
  ,registeredImageWriter(shared_ptr<sitk::ImageFileWriter> (new sitk::ImageFileWriter()))
  ,pathToImages(project_path)
{

}

void SimpleRegister::GetImages(string fixed, string moving)
{
  fixedReader->SetFileName(pathToImages+"/"+fixed);
  movingReader->SetFileName(pathToImages+"/"+moving);  
  elastix->SetMovingImage( movingReader->Execute() );
  elastix->SetFixedImage( fixedReader->Execute() );  
}

void SimpleRegister::SetParameterMapFromFile(string parameter_map_file)
{
  elastix->SetParameterMap(sitk::ReadParameterFile( string( parameter_map_file)));
}

void SimpleRegister::ExecuteRegister()
{
  elastix->Execute();
}

void SimpleRegister::SetRegisteredImage(string registered_image)
{
  registeredImageWriter->SetFileName( pathToImages+"/"+registered_image );
  registeredImageWriter->Execute(elastix->GetResultImage());
  
}
SimpleRegister::~SimpleRegister()
{

}

