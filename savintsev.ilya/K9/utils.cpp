#include "utils.h"
#include <iostream>

tree_t * savintsev::convert_ints_to_tree(std::pair< int, int > * vals, size_t n)
{
  tree_t * root = new tree_t{vals[0]};
  tree_t * temp = root;
  try
  {
    for (size_t i = 1; i < n;)
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
          temp = root;
          ++i;
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
          temp = root;
          ++i;
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
          temp = root;
          ++i;
        }
      }
      else
      {
        ++i;
      }
    }
  }
  catch (const std::bad_alloc & e)
  {
    clear(root);
    return nullptr;
  }
  return root;
}

void savintsev::clear(tree_t * root)
{
  if (!root)
  {
    return;
  }
  clear(root->left);
  clear(root->right);
  clear(root->middle);
  delete root;
}

namespace savintsev
{
  template< typename P >
  size_t count_if(tree_t *root, P predicate, int v1, int v2)
  {
    size_t count = 0;
    auto it = begin(root);
    for (; it.hasNext(); it = it.next())
    {
      if (predicate(it.data(), v1, v2))
      {
        count++;
      }
    }
    if (predicate(it.data(), v1, v2))
    {
      count++;
    }
    return count;
  }

  struct IntersectsPredicate
  {
    bool operator()(const std::pair< int, int > & p, int v1, int v2) const
    {
      return ((p.first - v2) * (v1 - p.second)) >= 0;
    }
  };

  struct AvoidsPredicate
  {
    bool operator()(const std::pair< int, int > & p, int v1, int v2) const
    {
      return ((p.first - v2) * (v1 - p.second)) < 0;
    }
  };

  struct CoversPredicate
  {
    bool operator()(const std::pair< int, int > & p, int v1, int v2) const
    {
      return p.first >= v1 && p.second <= v2;
    }
  };

  size_t intersects(tree_t * root, int v1, int v2)
  {
    return count_if(root, IntersectsPredicate{}, v1, v2);
  }

  size_t avoids(tree_t * root, int v1, int v2)
  {
    return count_if(root, AvoidsPredicate{}, v1, v2);
  }

  size_t covers(tree_t * root, int v1, int v2)
  {
    return count_if(root, CoversPredicate{}, v1, v2);
  }
}
