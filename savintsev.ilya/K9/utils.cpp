#include "utils.h"
#include <iostream>

tree_t * savintsev::convert_ints_to_tree(std::pair< int, int > * vals, size_t n)
{
  tree_t * root = new tree_t{vals[0]};
  std::cout << root->data.first << ' ' << root->data.second << ' ';
  tree_t * temp = root;
  try
  {
    for (size_t i = 1; i < n; ++i)
    {
      if (vals[i].second < temp->data.first)
      {
        if (temp->left)
        {
          temp = temp->left;
        }
        else
        {
          temp->left = new tree_t{vals[i]};
          temp->left->parent = temp;
          temp = temp->left;
          std::cout << temp->data.first << ' ' << temp->data.second << ' ';
          temp = root;
        }
      }
      else if (vals[i].first > temp->data.first && vals[i].second < temp->data.second)
      {
        if (temp->middle)
        {
          temp = temp->middle;
        }
        else
        {
          temp->middle = new tree_t{vals[i]};
          temp->middle->parent = temp;
          temp = temp->middle;
          std::cout << temp->data.first << ' ' << temp->data.second << ' ';
          temp = root;
        }
      }
      else if (vals[i].first > temp->data.second)
      {
        if (temp->right)
        {
          temp = temp->right;
        }
        else
        {
          temp->right = new tree_t{vals[i]};
          temp->right->parent = temp;
          temp = temp->right;
          std::cout << temp->data.first << ' ' << temp->data.second << ' ';
          temp = root;
        }
      }
    }
  }
  catch (const std::bad_alloc & e)
  {
    //clear(root, n);
    return nullptr;
  }
  return root;
}

//void savintsev::clear(tree_t * root, size_t created)
//{
  //cheto
//}
