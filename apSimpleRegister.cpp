#include "apSimpleRegister.hpp"

using namespace ap;

SimpleRegister::SimpleRegister()
  :elastix(shared_ptr<sitk::SimpleElastix> (new sitk::SimpleElastix()))
  ,fixed_reader(shared_ptr<sitk::ImageFileReader> (new sitk::ImageFileReader()))
  ,moving_reader(shared_ptr<sitk::ImageFileReader> (new sitk::ImageFileReader()))	       
{

}

void SimpleRegister::GetImages(string path, string fixed, string moving)
{
  fixed_reader->SetFileName(path+"/"+fixed);
  moving_reader->SetFileName(path+"/"+moving);  
  elastix->SetMovingImage( moving_reader->Execute() );
  elastix->SetFixedImage( fixed_reader->Execute() );  
}

void SimpleRegister::SetRegisteredImage(string registered_image)
{
  
}
SimpleRegister::~SimpleRegister()
{

}

