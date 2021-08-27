#include "CLIOptions.hh"

#include <boost/filesystem.hpp>
#include <iostream>

#include "Tools/Types.hh"
#include "Version.hh"

namespace po = boost::program_options;
namespace fs = boost::filesystem;

namespace Rayon::CLI
{
  CLIOptions::CLIOptions() : _description("Rayon options")
  {
  }

  void CLIOptions::fillConfig(int ac, char** av, Config& config)
  {
    auto&& opts = _description.add_options();
    opts("help", "Produce help message");
    opts("version,v", "Prints version information");
    opts("silent",
         po::value<bool>(&config.silent)->implicit_value(true)->default_value(false),
         "Don't print stats");
    opts(
      "width,w", po::value<uint32>(&config.width)->default_value(512), "Width of the output image");
    opts("height,h",
         po::value<uint32>(&config.height)->default_value(512),
         "Height of the output image");
    opts("output,o", po::value<std::string>(&_outputPath), "Path to the image output");
    opts("rpp",
         po::value<int>(&_rpp)->default_value(1),
         "Rays per pixels. Negative value will pack pixels together.");
    opts("thread-count,j",
         po::value<uint32>(&config.threadsCount)->default_value(4),
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
    {
      _outputPath = (input.parent_path() / input.stem()).string() + ".png";
    }
    else if (_inputPath.empty() && _outputPath.empty())
    {
      std::size_t i = 0;
      _outputPath   = "out.png";

      while (fs::exists(_outputPath))
        _outputPath = "out (" + std::to_string(++i) + ").png";
    }

    if (config.threadsCount < 1)
      config.threadsCount = 1;
  }

  bool CLIOptions::handleStoppingArgs() const
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

    if (_inputPath.empty())
    {
      std::cout << "No input file specified." << '\n';
      return true;
    }

    return false;
  }

  RAYON_GENERATE_PROPERTY_DEFINITION(CLIOptions, std::string, _outputPath, OutputPath);
  RAYON_GENERATE_PROPERTY_DEFINITION(CLIOptions, std::string, _inputPath, InputPath);
  RAYON_GENERATE_PROPERTY_DEFINITION(CLIOptions, int, _rpp, Rpp);
}  // namespace Rayon::CLI