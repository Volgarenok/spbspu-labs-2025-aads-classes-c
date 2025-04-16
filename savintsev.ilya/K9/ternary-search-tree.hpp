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
    using this_t = TriTreeItretor< T, Cmp >;

    TriTree< T, Cmp > * node;

    bool hasNext() const;
    bool hasPrev() const;

    this_t prev() const;
    this_t next() const
    {
      auto current = node;
      if (current->middle)
      {
        current = current->middle;
        while (current->left)
        {
          current = current->left;
        }
        return current;
      }
      else if (current->right)
      {
        current = current->right;
        while (current->left)
        {
          current = current->left;
        }
        return current;
      }
      if (current->parent->left == current)
      {
        return current->parent;
      }
      else if (current->parent->middle == current)
      {
        current = current->parent->right;
        while (current->left)
        {
          current = current->left;
        }
        return current;
      }
      else if (current->parent->right == current)
      {
        auto prev = current;
        while (current->right)
        {
          
        }
      }
      return current->parent;
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
    return temp;
  }

  template< class T, class Cmp >
  TriTreeIterator< T, Cmp > rbegin(TriTree< T, Cmp > * root);
}

#endif
