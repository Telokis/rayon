#include <iostream>

#include "CLIOptions.hh"
#include "ImageFileHandlers/ImageFileHandler.hh"
#include "Rayon.hh"
#include "Batch/LocalBatchGenerator.hh"
#include "Registry.hh"

int main(int ac, char** av)
{
  try
  {
    Rayon::CLI::CLIOptions cliOptions;
    Rayon::Config          config;
    Rayon::RawImage        img;

    cliOptions.fillConfig(ac, av, config);

    if (cliOptions.handleStoppingArgs())
      return 0;

    Rayon::LocalBatchGenerator batchGenerator{
      &img, cliOptions.getRpp(), cliOptions.getRpp(), config.getThreadCount()};
    Rayon::Rayon engine(config);

    Rayon::registry().registerDefaults();

    if (!cliOptions.getInputPath().empty())
    {
      engine.loadSceneFromFile(cliOptions.getInputPath());
    }

    auto result = engine.run(img, &batchGenerator);

    if (result == 0)
    {
      Rayon::ImageFileHandler::writeToFileBasedOnExtension(cliOptions.getOutputPath(), img);
    }

    return result;
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
