#ifndef TERNARY_SEARCH_TREE_HPP
#define TERNARY_SEARCH_TREE_HPP
#include <cstddef>
#include <utility>

namespace savintsev
{
  template< class T, class Cmp >
  struct TriTree
  {
    std::pair< T, T > data;
    TriTree< T, Cmp > * left, * middle, * right, * parent;
  };

  template< class T, class Cmp >
  struct TriTreeIterator
  {
    using this_t = TriTreeIterator< T, Cmp >;

    TriTree< T, Cmp > * node;

    bool hasNext() const;
    bool hasPrev() const
    {
      if (!node)
      {
        return false;
      }
      if (node->left)
      {
        return true;
      }
      TriTree< T, Cmp > * current = node;
      while (current->parent)
      {
        if (current->parent->right == current || current->parent->middle == current)
        {
          return true;
        }
        current = current->parent;
      }
      return false;
    }
    this_t prev() const
    {
      this_t result(*this);
      if (result.node->left)
      {
        result.node = result.node->left;
        while (result.node->right)
        {
          result.node = result.node->right;
        }
      }
      else
      {
        while (result.node->parent)
        {
          TriTree< T, Cmp > * prev = result.node;
          result.node = result.node->parent;
          if (result.node->right == prev)
          {
            return result;
          }
          if (result.node->middle == prev)
          {
            if (result.node->left)
            {
              result.node = result.node->left;
              while (result.node->right)
              {
                result.node = result.node->right;
              }
            }
            return result;
          }
        }
        result.node = nullptr;
      }
      return result;
    }
    this_t next() const
    {
      this_t result(*this);
      if (result.node->middle)
      {
        result.node = result.node->middle;
        while (result.node->left)
        {
          result.node = result.node->left;
        }
      }
      else if (result.node->right)
      {
        result.node = result.node->right;
        while (result.node->left)
        {
          result.node = result.node->left;
        }
      }
      else
      {
        while (result.node->parent)
        {
          TriTree< T, Cmp > * prev = result.node;
          result.node = result.node->parent;
          if (result.node->left == prev)
          {
            return result;
          }
          if (result.node->middle == prev && result.node->right)
          {
            result.node = result.node->right;
            while (result.node->left)
            {
              result.node = result.node->left;
            }
            return result;
          }
        }
        result.node = nullptr;
      }
      return result;
    }

    std::pair< T, T > & data();
  };

  template< class T, class Cmp >
  TriTreeIterator< T, Cmp > begin(TriTree< T, Cmp > * root)
  {
    auto temp = root;
    while (temp->left)
    {
      temp = temp->left;
    }
    return TriTreeIterator< T, Cmp >{temp};
  }

  template< class T, class Cmp >
  TriTreeIterator< T, Cmp > rbegin(TriTree< T, Cmp > * root)
  {
    auto temp = root;
    while (temp->right)
    {
      temp = temp->right;
    }
    return TriTreeIterator< T, Cmp >{temp};
  }

  template< class T, class Cmp >
  bool TriTreeIterator< T, Cmp >::hasNext() const
  {
    if (!node)
    {
      return false;
    }
    if (node->middle || node->right)
    {
      return true;
    }
    TriTree< T, Cmp > * current = node;
    while (current->parent)
    {
      if (current->parent->left == current || current->parent->middle == current)
      {
        return true;
      }
      current = current->parent;
    }
    return false;
  }

  template< class T, class Cmp >
  std::pair< T, T > & TriTreeIterator< T, Cmp >::data()
  {
    return node->data;
  }
}

#endif