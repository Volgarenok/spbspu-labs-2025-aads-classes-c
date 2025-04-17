#include <iostream>
#include <limits>
#include "tree-utils.hpp"

int main()
{
  using namespace aleksandrov;

  size_t quantity = 0;
  std::cin >> quantity;
  if (!std::cin)
  {
    std::cerr << "ERROR: Incorrect input!\n";
    return 1;
  }

  std::pair< int, int >* pairs = new std::pair< int, int >[quantity];
  int a = 0;
  int b = 0;
  for (size_t i = 0; i < quantity; ++i)
  {
    std::cin >> a >> b;
    if (!std::cin)
    {
      std::cerr << "ERROR: Incorrect input!\n";
      delete[] pairs;
      return 1;
    }
    pairs[i] = std::make_pair(std::min(a, b), std::max(a, b));
  }

  tree_t* pairsTree = nullptr;
  try
  {
    pairsTree = getTree(pairs, quantity);
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "ERROR: Out of memory!\n";
    delete[] pairs;
    return 1;
  }
  delete[] pairs;
  if (!pairsTree)
  {
    return 0;
  }

  do
  {
    std::string command;
    std::cin >> command;
    if (std::cin.eof())
    {
      clearTree(pairsTree);
      return 0;
    }
    if (!std::cin)
    {
      std::cerr << "ERROR: Incorrect input!\n";
      clearTree(pairsTree);
      return 1;
    }
    int param1 = 0;
    int param2 = 0;
    if (!(std::cin >> param1 >> param2))
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      continue;
    }
    try
    {
      processCommand(pairsTree, command, param1, param2);
    }
    catch (const std::logic_error& e)
    {
      std::cerr << "ERROR: " << e.what() << '\n';
      clearTree(pairsTree);
      return 1;
    }
  }
  while (!std::cin.eof());
  clearTree(pairsTree);
}

