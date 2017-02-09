#pragma once

#ifndef RAYON_CONFIG_HH_
#define RAYON_CONFIG_HH_

#include <boost/program_options.hpp>
#include "Tools/Helpers.hh"

namespace RayOn
{
  class Config
  {
  public:
    Config();
    void  init(int ac, char** av);
    bool  handleStoppingArgs() const;

  private:
    boost::program_options::options_description _description;
    boost::program_options::variables_map       _variables;

  private:
    RAYON_GENERATE_PROPERTY_DECLARATION(Config, std::string, _outputPath, OutputPath)
    RAYON_GENERATE_PROPERTY_DECLARATION(Config, uint32, _width, Width)
    RAYON_GENERATE_PROPERTY_DECLARATION(Config, uint32, _height, Height)
  };
} // namespace RayOn

#endif // RAYON_CONFIG_HH_