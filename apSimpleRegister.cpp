#include "apSimpleRegister.hpp"

using namespace ap;

SimpleRegister::SimpleRegister(string project_path)
  :elastix(shared_ptr<sitk::SimpleElastix> (new sitk::SimpleElastix()))
  ,fixedReader(shared_ptr<sitk::ImageFileReader> (new sitk::ImageFileReader()))
  ,movingReader(shared_ptr<sitk::ImageFileReader> (new sitk::ImageFileReader()))
  ,registeredImageWriter(shared_ptr<sitk::ImageFileWriter> (new sitk::ImageFileWriter()))
  ,pathToImages(project_path)
  ,log(false)
{

}

SimpleRegister::parameter_map_code SimpleRegister::GetParameterMapTemplateStringValues(string const& in_string)
{
    if (in_string == "translation") return translation;
    if (in_string == "rigid") return rigid;
    if (in_string == "affine") return affine;
    if (in_string == "bspline") return bspline;        
    else return no_value;
}

void SimpleRegister::GetImages(string fixed, string moving)
{
  fixedReader->SetFileName(pathToImages+"/"+fixed);
  movingReader->SetFileName(pathToImages+"/"+moving);  
  elastix->SetMovingImage( movingReader->Execute() );
  elastix->SetFixedImage( fixedReader->Execute() );  
}

void SimpleRegister::SetImageSize( sitk::Image * image)
{ 
  //TODO: Complete this method
}

vector<unsigned int> SimpleRegister::GetImageSize( sitk::Image image)
{
  return image.GetSize();
}

void SimpleRegister::SetParameterMapFromFile(string parameter_map_file)
{
  elastix->SetParameterMap(sitk::ReadParameterFile( string( parameter_map_file)));
}

void SimpleRegister::SetParameterMapFromTemplate(string parameter_map_template)
{
    string map_template;
    
    switch(GetParameterMapTemplateStringValues(parameter_map_template)){
	case translation:
            map_template="translation";
            break;
        case rigid:
            map_template="rigid";
            break;        
	case affine:
            map_template="affine";
            break;
	case bspline:
            map_template="bspline";
	    break;
        default:
	    std::cerr<<"Template not recognized"<<endl;
            break;
    }    
 
    elastix->SetParameterMap(sitk::GetDefaultParameterMap(map_template));
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

void SimpleRegister::ShowImage()
{
  //TODO: Complete this method
}

void SimpleRegister::GetTransformationMatrix()
{
  //TODO: Complete this method
}

void SimpleRegister::SetFilenameLog(string filename)
{   
   elastix->SetLogFileName(filename);
   elastix->SetLogToFile(true);
   log=true;
}

void SimpleRegister::LogToFile(bool on)
{
  if(log)
  { if(on)
      elastix->LogToFileOn();
    else
      elastix->LogToFileOff();
  }
  else
    cerr<<"Please set the filename log first"<<endl;
}

void SimpleRegister::LogToConsole(bool on)
{
  if(on)
    elastix->LogToConsoleOn();
  else
    elastix->LogToConsoleOff();
}


SimpleRegister::~SimpleRegister()
{

}

