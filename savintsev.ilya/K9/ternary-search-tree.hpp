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
        return this_t{current};
      }
      else if (current->right)
      {
        current = current->right;
        while (current->left)
        {
          current = current->left;
        }
        return this_t{current};
      }
      if (current->parent->left == current)
      {
        return this_t{current->parent};
      }
      else if (current->parent->middle == current)
      {
        current = current->parent->right;
        while (current->left)
        {
          current = current->left;
        }
        return this_t{current};
      }
      else if (current->parent->right == current)
      {
        auto prev = current;
        while (current->right == prev)
        {
          prev = current;
          current = current->parent;
        }
        if (current->middle == prev)
        {
          current = current->right;
        }
        return this_t{current};
      }
      return this_t{current->parent};
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
  TriTreeIterator< T, Cmp > rbegin(TriTree< T, Cmp > * root);

  template< class T, class Cmp >
  bool TriTreeIterator< T, Cmp >::hasNext() const
  {
    if (node->middle || node->right)
    {
      return true;
    }
    else if (node->parent)
    {
      if (node->parent->left == node)
      {
        return true;
      }
      else if (node->parent->middle == node && node->parent->right)
      {
        return true;
      }
      else
      {
        auto current = node;
        auto prev = current;
        while (current->right == prev)
        {
          prev = current;
          if (!current->parent)
          {
            return false;
          }
          current = current->parent;
        }
        return current->right != nullptr;
      }
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
