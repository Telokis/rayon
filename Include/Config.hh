#pragma once

#ifndef RAYON_CONFIG_HH_
#define RAYON_CONFIG_HH_

#include <boost/program_options.hpp>

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
  };
} // namespace RayOn

#endif // RAYON_CONFIG_HH_