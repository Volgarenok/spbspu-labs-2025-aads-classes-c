#include <iostream>
#include <utility>
#include <exception>
#include <cstddef>
#include "tritree.hpp"
#include "iterators.hpp"

int main()
{
  size_t cnt;
  std::cin >> cnt;
  if (std::cin.fail())
  {
    std::cerr << "<INVALID INPUT>\n";
    return 1;
  }
  std::pair< int, int >* pairs = new std::pair< int, int >[cnt];
  for (size_t i = 0; i < cnt; i++)
  {
    std::cin >> pairs[i].first >> pairs[i].second;
    if (std::cin.fail())
    {
      delete[] pairs;
      std::cerr << "<INVALID INPUT>\n";
      return 1;
    }
    if (pairs[i].first > pairs[i].second)
    {
      std::swap(pairs[i].first, pairs[i].second);
    }
  }
  TriTree< int, std::less< int > >* root = convert< int, std::less< int > >(pairs, cnt);

  auto it = begin(root);
  for (; it.hasNext(); it = it.next())
  {
    std::cout << it.data().first << " " << it.data().second << '\n';
  }
  std::cout << it.data().first << " " << it.data().second << '\n';
}
