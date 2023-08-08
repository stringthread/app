#include "wavelet_tree.h"
#include <iostream>

using namespace wavelet_tree;

int main(int argc, char const *argv[])
{
  std::cout << "Put string:" << std::endl;
  std::string str;
  std::cin >> str;
  auto wt = WaveletTree(str);
  std::string op;
  std::string arg0;
  std::string arg1;
  while (1)
  {
    std::cout << "Operation:" << std::endl;
    std::cin >> op;
    if (op == "access")
    {
      std::cin >> arg0;
      std::cout << wt.access(std::stoi(arg0)) << std::endl;
    }
    else if (op == "rank")
    {
      std::cin >> arg0 >> arg1;
      std::cout << wt.rank(arg0[0], std::stoi(arg1)) << std::endl;
    }
    else if (op == "select")
    {
      std::cin >> arg0 >> arg1;
      std::cout << wt.select(arg0[0], std::stoi(arg1)) << std::endl;
    }
    else
    {
      std::cout << "exit" << std::endl;
      break;
    }
  }

  return 0;
}
