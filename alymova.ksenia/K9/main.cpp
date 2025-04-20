#include <iostream>
#include <utility>
#include <exception>
#include <cstddef>
#include "tritree.hpp"
#include "iterators.hpp"
#include "utils.hpp"

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
  TriTree< int, std::less< int > >* root = nullptr;
  if (cnt > 0)
  {
    try
    {
      root = convert< int, std::less< int > >(pairs, cnt);
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << '\n';
      return 1;
    }
  }
  
  std::string command;
  while (std::cin >> command)
  {
    std::pair< int, int > nums;
    std::cin >> nums.first >> nums.second;
    if (std::cin.fail() || nums.first > nums.second)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
    if (command == "intersects")
    {
      std::cout << intersects(root, nums) << '\n';
    }
    else if (command == "covers")
    {
      std::cout << covers(root, nums) << '\n';
    }
    else if (command == "avoids")
    {
      std::cout << avoids(root, nums) << '\n';
    }
    else
    {
      clear< int, std::less< int > >(root);
      std::cerr << "<UNKNOWN COMMAND>\n";
      return 1;
    }
  }
  clear< int, std::less< int > >(root);
}
