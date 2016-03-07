/*
 *  This file is temporary and can be removed
 *  in any version. It is only meant to be
 *  used to ease the development.
 */

#include "Tools/Helpers.hh"
#include <iostream>
#include <iomanip>
#include "Tools/Vector3.hh"
#include "Tools/Helpers/Any.hh"
#include <string>

int  main()
{
  RayOn::Tools::Helpers::Any  test = 18;
  test = 3.5;
  std::cout << RayOn::Tools::Helpers::AnyCast<double>(test) << "\n";
  test = std::string("toto");
  std::cout << RayOn::Tools::Helpers::AnyCast<std::string>(test) << "\n";
  std::cin.get();
  return 0;
}