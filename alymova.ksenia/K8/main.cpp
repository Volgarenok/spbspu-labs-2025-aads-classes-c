#include <iostream>
#include <exception>
#include "tree-utils.hpp"

int main()
{
  size_t cnt;
  std::cin >> cnt;
  if (std::cin.fail())
  {
    std::cerr << "<INVALID INPUT>\n";
    return 1;
  }
  BiTree< int, std::less< int > >* root = nullptr;
  try
  {
    if (cnt > 0)
    {
      root = create< int, std::less< int > >(std::cin, cnt, std::less< int >());
    }
    int num;
    while (std::cin >> num)
    {
      BiTree< int, std::less< int > >* result = nullptr;
      root = extract< int, std::less< int > >(root, num, &result);
      if (result == nullptr)
      {
        std::cout << "<INVALID NODE>\n";
        continue;
      }
      delete result;
    }
    if (!std::cin.eof())
    {
      print< int, std::less< int > >(std::cout, root);
      std::cout << '\n';
      throw std::out_of_range("<INVALID COMMAND>");
    }
    print< int, std::less< int > >(std::cout, root);
    std::cout << '\n';
    clear(root);
  }
  catch (const std::invalid_argument& e)
  {
    clear(root);
    std::cout << e.what() << '\n';
    return 0;
  }
  catch (const std::exception& e)
  {
    clear(root);
    std::cerr << e.what() << '\n';
    return 1;
  }
}
