#include <iostream>

#include "Config.hh"
#include "Version.hh"

namespace po = boost::program_options;

namespace RayOn
{

  Config::Config()
    : _description("RayOn options")
  {
  }

  void  Config::init(int ac, char** av)
  {
    _description.add_options()
      ("help", "Produce help message")
      ("version,v", "Prints version information")
      ("width,w", po::value<uint32>(&_width)->default_value(512), "Width of the output image")
      ("height,h", po::value<uint32>(&_height)->default_value(512), "Height of the output image")
      ("output,o", po::value<std::string>(&_outputPath)->default_value("out.bmp"), "Path to the image output")
      ;

    po::store(po::parse_command_line(ac, av, _description), _variables);
    po::notify(_variables);
  }

  bool  Config::handleStoppingArgs() const
  {
    if (_variables.count("help"))
    {
      std::cout << _description << '\n';
      return true;
    }
    if (_variables.count("version"))
    {
      std::cout << "RayOn v." << version() << '\n';
      return true;
    }
    return false;
  }

  RAYON_GENERATE_PROPERTY_DEFINITION(Config, std::string, _outputPath, OutputPath)
  RAYON_GENERATE_PROPERTY_DEFINITION(Config, uint32, _width, Width)
  RAYON_GENERATE_PROPERTY_DEFINITION(Config, uint32, _height, Height)
} // namespace RayOn
