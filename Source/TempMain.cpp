/*
 *  This file is temporary and can be removed
 *  in any version. It is only meant to be
 *  used to ease the development.
 */

#include "Tools/Helpers.hh"
#include <iostream>
#include <iomanip>
#include "Tools/Vector3.hh"

template<int n>
struct constN
{
  constN()
  {
    std::cout << n << '\n';
  }
};

int  main()
{
  constN<RayOn::Tools::Helpers::Pow3(2)> N;
  std::cin.get();
  return 0;
}