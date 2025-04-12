#ifndef TREE_UTILS_HPP
#define TREE_UTILS_HPP
#include <exception>
#include <iostream>

template< class T, class Comparator >
struct BiTree
{
  T data;
  Comparator cmp;
  BiTree< T, Comparator >* left;
  BiTree< T, Comparator >* right;
  BiTree< T, Comparator >* parent;
};

template< class T, class Comparator >
BiTree< T, Comparator >* create(std::istream& in, size_t cnt, Comparator cmp);

template< class T, class Comparator >
BiTree< T, Comparator >* rotate_right(BiTree< T, Comparator >* root);

template< class T, class Comparator >
BiTree< T, Comparator >* rotate_right(BiTree< T, Comparator >* root);

template< class T, class Comparator >
BiTree< T, Comparator >* find(BiTree< T, Comparator >* root, const T& value, Comparator cmp);

template< class T, class Comparator >
BiTree< T, Comparator >* extract(BiTree< T, Comparator >* root, const T& value, BiTree< T, Comparator >** result);

template< class T, class Comparator >
void print(std::ostream& out, BiTree< T, Comparator >* root);

template< class T, class Comparator >
void clear(BiTree< T, Comparator >* root);

template< class T, class Comparator >
BiTree< T, Comparator >* create(std::istream& in, size_t cnt, Comparator cmp)
{
  BiTree< T, Comparator >* root = new BiTree< T, Comparator >{0, cmp, nullptr, nullptr, nullptr};
  in >> root->data;
  for (size_t i = 1; i < cnt && in; i++)
  {
    BiTree< T, Comparator >* node;
    try
    {
      node = new BiTree< T, Comparator >{0, cmp, nullptr, nullptr, nullptr};
    }
    catch (const std::bad_alloc& e)
    {
      clear(root);
      throw;
    }
    in >> node->data;
    BiTree< T, Comparator >* tmp = root;
    while (tmp->left || tmp->right)
    {
      if (cmp(node->data, tmp->data))
      {
        if (!tmp->left)
        {
          break;
        }
        tmp = tmp->left;
      }
      else
      {
        if (!tmp->right)
        {
          break;
        }
        tmp = tmp->right;
      }
    }
    if (cmp(node->data, tmp->data))
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
    throw std::out_of_range("<INVALID INPUT>");
  }
  return root;
}

template< class T, class Comparator >
BiTree< T, Comparator >* rotate_right(BiTree< T, Comparator >* root)
{
  if (!root)
  {
    throw std::invalid_argument("<INVALID ROTATE>");
  }
  if (!root->left)
  {
    throw std::invalid_argument("<INVALID ROTATE>");
  }
  std::cout << root->data << root->left->data;
  BiTree< T, Comparator >* new_root = root->left;
  new_root->parent = root->parent;
  if (root->parent)
  {
    if (root->parent->left == root)
    {
      root->parent->left = new_root;
    }
    else
    {
      root->parent->right = new_root;
    }
  }
  root->parent = new_root;
  root->left = new_root->right;
  new_root->right = root;
  return new_root;
}

template< class T, class Comparator >
BiTree< T, Comparator >* rotate_left(BiTree< T, Comparator >* root)
{
  if (!root)
  {
    throw std::invalid_argument("<INVALID ROTATE>");
  }
  if (!root->right)
  {
    throw std::invalid_argument("<INVALID ROTATE>");
  }
  BiTree< T, Comparator >* new_root = root->right;
  new_root->parent = root->parent;
  if (root->parent)
  {
    if (root->parent->left == root)
    {
      root->parent->left = new_root;
    }
    else
    {
      root->parent->right = new_root;
    }
  }
  root->parent = new_root;
  root->right = new_root->left;
  new_root->left = root;
  return new_root;
}

template< class T, class Comparator >
BiTree< T, Comparator >* extract(BiTree< T, Comparator >* root, const T& value, BiTree< T, Comparator >** result)
{
  BiTree< T, Comparator >* node = find(root, value, root->cmp);
  if (!node)
  {
    *result = nullptr;
    return root;
  }
  BiTree< T, Comparator >* tmp = nullptr;
  while (node->left)
  {
    tmp = rotate_right(node);
    if (node == root)
    {
      root = tmp;
    }
  }
  while (node->right)
  {
    tmp = rotate_left(node);
    if (node == root)
    {
      root = tmp;
    }
  }
  if (node->parent->left == node)
  {
    node->parent->left = nullptr;
  }
  else if (node->parent->right == node)
  {
    node->parent->right = nullptr;
  }
  *result = node;
  return root;
}

template< class T, class Comparator >
BiTree< T, Comparator >* find(BiTree< T, Comparator >* root, const T& value, Comparator cmp)
{
  if (!root)
  {
    return nullptr;
  }
  while (value != root->data)
  {
    if (cmp(value, root->data))
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

template< class T, class Comparator >
void print(std::ostream& out, BiTree< T, Comparator >* root)
{
  static size_t cnt = 0;
  if (root)
  {
    print(out, root->left);
    print(out, root->right);
    if (cnt != 0)
    {
      out << " ";
    }
    out << root->data;
    cnt += 1;
  }
}

template< class T, class Comparator >
void clear(BiTree< T, Comparator >* root)
{
  if (root)
  {
    clear(root->left);
    clear(root->right);
    delete root;
  }
}

#endif
