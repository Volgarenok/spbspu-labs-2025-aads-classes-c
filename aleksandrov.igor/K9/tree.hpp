#ifndef TREE_HPP
#define TREE_HPP

#include <utility>
#include <cassert>

namespace aleksandrov
{  
  template< class T, class Cmp >
  struct TriTree
  {
    std::pair< T, T > data;
    TriTree< T, Cmp >* left;
    TriTree< T, Cmp >* middle;
    TriTree< T, Cmp >* right;
    TriTree< T, Cmp >* parent;
  };

  template< class T, class Cmp >
  struct TriTreeIterator
  {
    using this_t = TriTreeIterator< T, Cmp >;

    bool hasNext() const;
    bool hasPrev() const;

    this_t prev() const;
    this_t next() const;

    this_t fallLeft() const;
    this_t fallRight() const;
    
    std::pair< T, T >& data();

    bool operator==(const this_t&) const;
    bool operator!=(const this_t&) const;

    TriTree< T, Cmp >* node;
  };

  template< class T, class Cmp >
  bool TriTreeIterator< T, Cmp >::hasNext() const
  {
    return next().node != nullptr;
  }

  template< class T, class Cmp >
  bool TriTreeIterator< T, Cmp >::hasPrev() const
  {
    return prev().node != nullptr;
  }

  template< class T, class Cmp >
  TriTreeIterator< T, Cmp > TriTreeIterator< T, Cmp >::prev() const
  {
    if (!node)
    {
      return this_t{nullptr};
    }
    if (node->left)
    {
      return this_t{node->left}.fallLeft();
    }
    else if (node->middle)
    {
      return this_t{node->middle}.fallLeft();
    }
    auto temp = node;
    while (temp->parent && (temp->parent->left == temp || temp->parent->middle == temp))
    {
      temp = temp->parent;
    }
    return this_t{temp->parent};
  }

  template< class T, class Cmp >
  TriTreeIterator< T, Cmp > TriTreeIterator< T, Cmp >::next() const
  {
    if (!node)
    {
      return this_t{nullptr};
    }
    if (node->right)
    {
      return this_t{node->right}.fallLeft();
    }
    else if (node->middle)
    {
      return this_t{node->middle}.fallLeft();
    }
    auto temp = node;
    while (temp->parent && (temp->parent->right == temp || temp->parent->middle == temp))
    {
      temp = temp->parent;
    }
    return this_t{temp->parent};
  }

  template< class T, class Cmp >
  TriTreeIterator< T, Cmp > TriTreeIterator< T, Cmp >::fallLeft() const
  {
    if (!node)
    {
      return this_t{nullptr};
    }
    return node->left ? this_t{node->left}.fallLeft() : (node->middle ? this_t{node->middle}.fallLeft() : this_t{node});
  }

  template< class T, class Cmp >
  TriTreeIterator< T, Cmp > TriTreeIterator< T, Cmp >::fallRight() const
  {
    if (!node)
    {
      return this_t{nullptr};
    }
    return node->right ? this_t{node->right}.fallRight() : (node->middle ? this_t{node->middle}.fallRight() : this_t{node});
  }

  template< class T, class Cmp >
  std::pair< T, T >& TriTreeIterator< T, Cmp >::data()
  {
    return node->data;
  }

  template< class T, class Cmp >
  bool TriTreeIterator< T, Cmp >::operator==(const TriTreeIterator< T, Cmp >& rhs) const
  {
    return node == rhs.node;
  }

  template< class T, class Cmp >
  bool TriTreeIterator< T, Cmp >::operator!=(const TriTreeIterator< T, Cmp >& rhs) const
  {
    return !(*this == rhs);
  }
}

#endif

