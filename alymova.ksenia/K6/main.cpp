#include <iostream>
#include <exception>
#include "tree-utils.hpp"

int main()
{
  size_t cnt;
  std::cin >> cnt;
  if (std::cin.fail())
  {
    std::cerr << "<INVAID INPUT>\n";
    return 1;
  }
  BiTree< int >* root = nullptr;
  try
  {
    if (cnt > 0)
    {
      root = create< int, std::less< int > >(std::cin, cnt, std::less< int >());
    }
    std::string command;
    int num;
    while (std::cin >> command >> num)
    {
      BiTree< int >* new_root = find(root, num, std::less< int >());
      if (command == "right")
      {
        new_root = rotate_right(new_root);
      }
      else if (command == "left")
      {
        new_root = rotate_left(new_root);
      }
      if (root == find(root, num, std::less< int >()))
      {
        root = new_root;
      }
      std::cout << new_root->data << '\n';
    }
    if (!std::cin.eof())
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }
  catch(const std::exception& e)
  {
    clear(root);
    std::cerr << e.what() << '\n';
    return 1;
  }
  clear(root);
}
