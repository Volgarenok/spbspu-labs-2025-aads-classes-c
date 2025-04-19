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
  TriTree< T, Cmp >* nextForLeaf(TriTree< T, Cmp >* leaf) const;
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
    return nextForLeaf(tmp) != nullptr;
  }
  return true;
}

template< class T, class Cmp >
TriTree< T, Cmp >* TriTreeIterator< T, Cmp >::nextForLeaf(TriTree< T, Cmp >* leaf) const
{
  if (leaf->parent->left == leaf)
  {
    return {leaf->parent};
  }
  if (leaf->parent->middle == leaf)
  {
    return {nextForMiddleParent(leaf->parent)};
  }
  return {nextForRightParent(leaf->parent)};
}

template< class T, class Cmp >
TriTree< T, Cmp >* TriTreeIterator< T, Cmp >::nextForMiddleParent(TriTree< T, Cmp >* node_parent) const
{
  TriTree< T, Cmp >* next_parent = nullptr;
  TriTree< T, Cmp >* next_right = nullptr;
  TriTree< T, Cmp >* tmp = node_parent;
  if (tmp->parent)
  {
    next_parent = nextForLeaf(tmp);
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
    return nextForLeaf(node_parent);
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
  return {nextForLeaf(tmp)};
}
#endif
