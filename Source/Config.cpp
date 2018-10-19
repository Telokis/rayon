#include "Config.hh"

#include <boost/filesystem.hpp>
#include <iostream>

#include "Version.hh"

namespace po = boost::program_options;
namespace fs = boost::filesystem;

namespace Rayon
{
  Config::Config() : _description("Rayon options")
  {
  }

  void Config::init(int ac, char** av)
  {
    _description.add_options()("help", "Produce help message")("version,v",
                                                               "Prints version information")(
      "width,w", po::value<uint32>(&_width)->default_value(512), "Width of the output image")(
      "height,h", po::value<uint32>(&_height)->default_value(512), "Height of the output image")(
      "output,o", po::value<std::string>(&_outputPath), "Path to the image output")(
      "thread-count,j",
      po::value<uint32>(&_threadsCount)->default_value(4),
      "Number of threads to use to render");

    po::options_description hidden;
    hidden.add_options()("input", po::value<std::string>(&_inputPath), "Input scene file");
    hidden.add(_description);

    po::positional_options_description positional;
    positional.add("input", 1);

    po::store(po::command_line_parser(ac, av).options(hidden).positional(positional).run(),
              _variables);
    po::notify(_variables);

    fs::path input = _inputPath;
    if (!_inputPath.empty() && _outputPath.empty() && input.has_filename())
      _outputPath = (input.parent_path() / input.stem()).string() + ".png";
    else if (_inputPath.empty() && _outputPath.empty())
    {
      std::size_t i = 0;
      _outputPath   = "out.png";
      while (fs::exists(_outputPath))
        _outputPath = "out (" + std::to_string(++i) + ").png";
    }

    if (_threadsCount < 1)
      _threadsCount = 1;
  }

  bool Config::handleStoppingArgs() const
  {
    if (_variables.count("help"))
    {
      std::cout << _description << '\n';
      return true;
    }

    if (_variables.count("version"))
    {
      std::cout << "Rayon v." << version() << '\n';
      return true;
    }

    if (config().getInputPath().empty())
    {
      std::cout << "No input file specified." << '\n';
      return true;
    }

    return false;
  }

  RAYON_GENERATE_PROPERTY_DEFINITION(Config, std::string, _outputPath, OutputPath)
  RAYON_GENERATE_PROPERTY_DEFINITION(Config, std::string, _inputPath, InputPath)
  RAYON_GENERATE_PROPERTY_DEFINITION(Config, uint32, _width, Width)
  RAYON_GENERATE_PROPERTY_DEFINITION(Config, uint32, _height, Height)
  RAYON_GENERATE_PROPERTY_DEFINITION(Config, uint32, _threadsCount, ThreadCount)
}  // namespace Rayon
