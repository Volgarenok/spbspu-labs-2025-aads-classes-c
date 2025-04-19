#ifndef ITERATORS_HPP
#define ITERATORS_HPP
#include <cassert>
#include <iostream>
#include "tritree.hpp"

template< class T, class Cmp >
struct TriTreeIterator {
  using this_t = TriTreeIterator< T, Cmp >;

  TriTree< T, Cmp >* node;

  bool hasNext() const;
  bool hasPrev() const;
  this_t prev() const;
  this_t next() const;
  std::pair< T, T >& data();
private:
  TriTree< T, Cmp >* nextForMiddleParent(TriTree< T, Cmp >* node) const;
  TriTree< T, Cmp >* nextForRightParent(TriTree< T, Cmp >* node) const;
};

template< class T, class Cmp >
TriTreeIterator< T, Cmp > begin(TriTree< T, Cmp >* root);

template< class T, class Cmp >
TriTreeIterator< T, Cmp > rbegin(TriTree< T, Cmp >* root);

template< class T, class Cmp >
std::pair< T, T >& TriTreeIterator< T, Cmp >::data()
{
  return node->data;
}

template< class T, class Cmp >
TriTreeIterator< T, Cmp > begin(TriTree< T, Cmp >* root)
{
  assert(root != nullptr && "Invalid root");
  while (root->parent)
  {
    root = root->parent;
  }
  while (root->left)
  {
    root = root->left;
  }
  return {root};
}

template< class T, class Cmp >
TriTreeIterator< T, Cmp > rbegin(TriTree< T, Cmp >* root)
{
  assert(root != nullptr && "Invalid root");
  while (root->parent)
  {
    root = root->parent;
  }
  while (root->right)
  {
    root = root->right;
  }
  return {root};
}

template< class T, class Cmp >
bool TriTreeIterator< T, Cmp >::hasNext() const
{
  TriTree< T, Cmp >* tmp = node;
  if (!tmp->middle && !tmp->right)
  {
    if (!tmp->parent)
    {
      return false;
    }
    if (tmp->parent->left == tmp)
    {
      return true;
    }
    if (tmp->parent->middle == tmp)
    {
      return nextForMiddleParent(tmp->parent) != nullptr;
    }
    if (tmp->parent->right == tmp)
    {
      return nextForRightParent(tmp->parent) != nullptr;
    }
  }
  return true;
}

template< class T, class Cmp >
TriTree< T, Cmp >* TriTreeIterator< T, Cmp >::nextForMiddleParent(TriTree< T, Cmp >* node_parent) const
{
  TriTree< T, Cmp >* next_parent = nullptr;
  TriTree< T, Cmp >* next_right = nullptr;
  TriTree< T, Cmp >* tmp = node_parent;
  if (tmp->parent)
  {
    while (tmp->parent->left != tmp)
    {
      tmp = tmp->parent;
      if (!tmp->parent)
      {
        break;
      }
    }
    if (!next_parent)
    {
      next_parent = tmp->parent;
    }
  }
  tmp = node_parent;
  if (tmp->right)
  {
    tmp = tmp->right;
    while (tmp->left)
    {
      tmp = tmp->left;
    }
    next_right = tmp;
  }
  if (!next_parent)
  {
    return next_right;
  }
  if (!next_right)
  {
    return next_parent;
  }
  if (next_parent->data < next_right->data)
  {
    return next_parent;
  }
  return next_right;
}

template< class T, class Cmp >
TriTree< T, Cmp >* TriTreeIterator< T, Cmp >::nextForRightParent(TriTree< T, Cmp >* node_parent) const
{
  TriTree< T, Cmp >* next_parent = nullptr;
  if (node_parent->parent)
  {
    while (node_parent->parent->left != node_parent)
    {
      node_parent = node_parent->parent;
      if (!node_parent->parent)
      {
        return nullptr;
      }
    }
    return node_parent->parent;
  }
  return nullptr;
}

template< class T, class Cmp >
TriTreeIterator< T, Cmp > TriTreeIterator< T, Cmp >::next() const
{
  TriTree< T, Cmp >* tmp = node;
  if (tmp->middle)
  {
    tmp = tmp->middle;
    while (tmp->left)
    {
      tmp = tmp->left;
    }
    return {tmp};
  }
  if (tmp->right)
  {
    tmp = tmp->right;
    while (tmp->left)
    {
      tmp = tmp->left;
    }
    return {tmp};
  }
  if (!tmp->parent)
  {
    return {nullptr};
  }
  if (tmp->parent->left == tmp)
  {
    return {tmp->parent};
  }
  if (tmp->parent->middle == tmp)
  {
    return {nextForMiddleParent(tmp->parent)};
  }
  return {nextForRightParent(tmp->parent)};
}
#endif
