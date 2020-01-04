#include <iostream>

#include "CLIOptions.hh"
#include "Ray.hh"
#include "Rayon.hh"

int main(int ac, char** av)
{
  try
  {
    Rayon::CLI::CLIOptions cliOptions;
    Rayon::Config          config;

    cliOptions.fillConfig(ac, av, config);

    if (cliOptions.handleStoppingArgs(config))
      return 0;

    Rayon::Rayon engine(config);

    engine.registerDefaults();

    if (!config.getInputPath().empty())
      engine.loadSceneFromFile(config.getInputPath());

    return engine.run();
  }
  catch (std::exception& except)
  {
    std::cerr << "*****************************************************\n";
    std::cerr << "ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR\n";
    std::cerr << "_____________________________________________________\n";
    std::cerr << except.what() << "\n";
    std::cerr << "_____________________________________________________\n";
    std::cerr << "ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR\n";
    std::cerr << "*****************************************************\n";
    std::cin.get();
    return 1;
  }
}
