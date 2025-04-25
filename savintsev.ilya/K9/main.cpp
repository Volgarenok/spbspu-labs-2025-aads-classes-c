#include <iostream>
#include <string>
#include <limits>
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
    return 1;
  }

  std::string command;
  int v1 = 0, v2 = 0;

  while (std::cin >> command)
  {
    std::cin >> v1 >> v2;
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      std::cout << "<INVALID COMMAND>\n";
      continue;
    }
    if (v1 >= v2)
    {
      std::cout << "<INVALID COMMAND>\n";
      continue;
    }
    if (command == "intersects")
    {
      std::cout << savintsev::intersects(root, v1, v2) << '\n';
    }
    else if (command == "covers")
    {
      std::cout << savintsev::covers(root, v1, v2) << '\n';
    }
    else if (command == "avoids")
    {
      std::cout << savintsev::avoids(root, v1, v2) << '\n';
    }
    else
    {
      std::cout << "ERROR: INVALID COMMAND\n";
      return 1;
    }
  }
}
