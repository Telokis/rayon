#include "Config.hh"
#include <iostream>

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
      ("help,h", "Produce help message")
      ("version,v", "Prints version information")
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
      std::cout << "RayOn v." << "toto" << '\n';
      return true;
    }
    return false;
  }
} // namespace RayOn
