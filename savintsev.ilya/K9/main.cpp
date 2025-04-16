#include <iostream>
#include "ternary-search-tree.hpp"
#include "utils.h"

int main()
{
  size_t n = 0;
  int input1 = 0, input2 = 0;
  std::cin >> n;
  std::pair< int, int > * data = new std::pair< int, int >[n];

  if (n == 0)
  {
    return 0;
  }
  for (size_t i = 0; i < n; ++i)
  {
    std::cin >> input1 >> input2;

    if (!std::cin)
    {
      std::cerr << "ERROR: invalid input\n";
      return 1;
    }
    if (input1 < input2)
    {
      data[i] = {input1, input2};
    }
    else
    {
      data[i] = {input2, input1};
    }
  }

  tree_t * root = savintsev::convert_ints_to_tree(data, n);
  if (!root)
  {
    std::cerr << "ERROR: memory overflow\n";
  }

  
}
