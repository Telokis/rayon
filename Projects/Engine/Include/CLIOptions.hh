#pragma once

#ifndef RAYON_CLIOPTIONS_HH_
#define RAYON_CLIOPTIONS_HH_

#include <boost/program_options.hpp>

#include "Config.hh"

namespace Rayon
{
  namespace CLI
  {
    class CLIOptions
    {
    public:
      CLIOptions();
      void fillConfig(int ac, char** av, Config& config);
      bool handleStoppingArgs(const Config& config) const;

    private:
      boost::program_options::options_description _description;
      boost::program_options::variables_map       _variables;
    };
  }  // namespace CLI
}  // namespace Rayon

#endif  // RAYON_CLIOPTIONS_HH_