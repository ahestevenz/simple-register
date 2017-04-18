#include "../inc/apSimpleRegister.hpp"
#include <QCommandLineParser>

using namespace ap;


int main ( int argc, char* argv[] ) {

    QCoreApplication arg(argc, argv);
    QCoreApplication::setApplicationName(argv[0]);
    QCoreApplication::setApplicationVersion("0.1");
    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption cfg(QStringList()<<"i"<<"images","Path to moving and fixed images.","/directory_1/images/");
    QCommandLineOption par(QStringList()<<"p"<<"parameters","Path to the parameter file configuration.","/directory_1/parameter_1.txt");
    QCommandLineOption fix(QStringList()<<"f"<<"fixed","Fixed image name.","ct.dmg");
    QCommandLineOption mov(QStringList()<<"m"<<"moving","Moving image name.","pet.dmg");
    QCommandLineOption reg(QStringList()<<"r"<<"registered","Registered image name.","pet_reg.dcm");
    QCommandLineOption shw(QStringList()<<"s"<<"show","Show information on the console.","OK");

    parser.addOption(cfg);
    parser.addOption(par);
    parser.addOption(fix);
    parser.addOption(mov);
    parser.addOption(reg);
    parser.addOption(shw);
    parser.process(arg);

    string pathToImages;
    string pathToParameterFile;
    string FixedImageName;
    string MovingImageName;
    string RegisteredImageName;    
    string showCheck;
    
    if(arg.arguments().length()<10)
    {
        parser.showHelp(SimpleRegister::OK);
    }

    if(parser.isSet("images"))
    {
        pathToImages=parser.value("images").toStdString();
    }

    if(parser.isSet("parameters"))
    {
        pathToParameterFile=parser.value("parameters").toStdString();
    }

    if(parser.isSet("fixed"))
    {
        FixedImageName=parser.value("fixed").toStdString();
    }

    if(parser.isSet("moving"))
    {
        MovingImageName=parser.value("moving").toStdString();
    }
    
    if(parser.isSet("registered"))
    {
        RegisteredImageName=parser.value("registered").toStdString();
    }

    if(parser.isSet("show"))
    {
        showCheck=parser.value("show").toStdString();
    }
    
    bool verbose=false;
    if(strcmp(showCheck.c_str(),"OK")==0) verbose=true;
    
  shared_ptr<SimpleRegister> imgregister(new SimpleRegister(pathToImages));
    
  imgregister->GetImages(FixedImageName,MovingImageName);
  imgregister->SetParameterMapFromFile(pathToParameterFile); 
  if (verbose) imgregister->LogToConsole();
  imgregister->ExecuteRegister();  
  imgregister->SetRegisteredImage(RegisteredImageName);
  
  imgregister->ShowFixedImage();
  imgregister->ShowMovingImage();
  imgregister->ShowRegisteredImage();  
  
  return SimpleRegister::OK;
}

