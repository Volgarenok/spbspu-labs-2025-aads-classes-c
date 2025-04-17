#include <iostream>
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
      return 1;
    }
    pairs[i] = std::make_pair(std::min(a, b), std::max(a, b));
  }
  
  tree_t* pairsTree = getTree(pairs, quantity);
  if (!pairsTree)
  {
    return 0;
  }
  for (auto it = begin(pairsTree);; it = it.next())
  {
    std::cout << it.data().first << ' ' << it.data().second << '\n';
    if (!it.hasNext())
    {
      break;
    }
  }
  for (auto it = rbegin(pairsTree);; it = it.prev())
  {
    std::cout << it.data().first << ' ' << it.data().second << '\n';
    if (!it.hasPrev())
    {
      break;
    }
  }
}

