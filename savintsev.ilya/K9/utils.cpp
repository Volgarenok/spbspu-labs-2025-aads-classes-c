#include "utils.h"

tree_t * savintsev::convert_ints_to_tree(std::pair< int, int > * vals, size_t n)
{
  tree_t * root = new tree_t{vals[0]};
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
        }
      }
      temp = root;
    }
  }
  catch (const std::bad_alloc & e)
  {
    clear(root, n);
    return nullptr;
  }
  return root;
}
