#ifndef TREE_UTILS_HPP
#define TREE_UTILS_HPP
#include <exception>
#include <iostream>

template< class T >
struct BiTree {
  T data;
  BiTree< T >* left;
  BiTree< T >* right;
  BiTree< T >* parent;
};

template< class T, class Comparator >
BiTree< T >* create(std::istream& in, size_t cnt, Comparator comp);

template< class T >
BiTree< T >* rotate_right(BiTree< T >* root);

template< class T >
BiTree< T >* rotate_left(BiTree< T >* root);

template< class T, class Comparator >
BiTree< T >* find(BiTree< T >* root, const T & value, Comparator comp);

template< class T >
void clear(BiTree< T >* root);

template< class T, class Comparator >
BiTree< T >* create(std::istream& in, size_t cnt, Comparator comp)
{
  BiTree< T >* root = new BiTree< T >{0, nullptr, nullptr, nullptr};
  in >> root->data;
  for (size_t i = 1; i < cnt && in; i++)
  {
    BiTree< T >* node;
    try
    {
      node = new BiTree< T >{0, nullptr, nullptr, nullptr};
    }
    catch (const std::bad_alloc& e)
    {
      clear(root);
      throw;
    }
    in >> node->data;
    BiTree< T >* tmp = root;
    while (tmp->left && tmp->right)
    {
      if (comp(node->data, tmp->data))
      {
        tmp = tmp->left;
      }
      else
      {
        tmp = tmp->right;
      }
    }
    if (comp(node->data, tmp->data))
    {
      tmp->left = node;
    }
    else
    {
      tmp->right = node;
    }
    node->parent = tmp;
  }
  if (!in)
  {
    clear(root);
    throw std::invalid_argument("<INVALID INPUT>");
  }
  return root;
}

template< class T >
BiTree< T >* rotate_right(BiTree< T >* root)
{
  if (!root)
  {
    throw std::invalid_argument("<INVALID ROTATE>");
  }
  if (!root->left)
  {
    throw std::invalid_argument("<INVALID ROTATE>");
  }
  BiTree< T >* new_root = root->left;
  new_root->parent = root->parent;
  root->parent = new_root;
  root->left = new_root->right;
  new_root->right = root;
  return new_root;
}

template< class T >
BiTree< T >* rotate_left(BiTree< T >* root)
{
  if (!root)
  {
    throw std::invalid_argument("<INVALID ROTATE>");
  }
  if (!root->right)
  {
    throw std::invalid_argument("<INVALID ROTATE>");
  }
  BiTree< T >* new_root = root->right;
  new_root->parent = root->parent;
  root->parent = new_root;
  root->right = new_root->left;
  new_root->left = root;
  return new_root;
}

template< class T, class Comparator >
BiTree< T >* find(BiTree< T >* root, const T& value, Comparator comp)
{
  if (!root)
  {
    return nullptr;
  }
  while (value != root->data)
  {
    if (comp(value, root->data))
    {
      if (!root->left)
      {
        return nullptr;
      }
      root = root->left;
    }
    else
    {
      if (!root->right)
      {
        return nullptr;
      }
      root = root->right;
    }
  }
  return root;
}

template< class T >
void clear(BiTree< T >* root)
{
  if (root)
  {
    clear(root->left);
    clear(root->right);
    delete root;
  }
}

#endif
