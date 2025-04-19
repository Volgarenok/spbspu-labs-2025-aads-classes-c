#ifndef TRITREE_HPP
#define TRITREE_HPP
#include <utility>

template< class T, class Cmp >
struct TriTree {
  std::pair< T, T > data;
  TriTree< T, Cmp > * left, * middle, * right, * parent;
};

template< class T, class Cmp >
void clear(TriTree< T, Cmp >* root);

template< class T, class Cmp >
TriTree< T, Cmp >* convert(std::pair< T, T >* pairs, size_t cnt);

template< class T, class Cmp >
void clear(TriTree< T, Cmp >* root)
{
  if (root)
  {
    clear(root->left);
    clear(root->right);
    delete root;
  }
}

template< class T, class Cmp >
TriTree< T, Cmp >* convert(std::pair< T, T >* pairs, size_t cnt)
{
  if (cnt == 0 || !pairs)
  {
    return nullptr;
  }
  TriTree< T, Cmp >* root = new TriTree< T, Cmp >{pairs[0], nullptr, nullptr, nullptr, nullptr};
  for (size_t i = 1; i < cnt; i++)
  {
    TriTree< T, Cmp >* tmp = root;
    TriTree< T, Cmp >* node;
    try
    {
      node = new TriTree< T, Cmp >{pairs[i], nullptr, nullptr, nullptr, nullptr};
    }
    catch(const std::exception& e)
    {
      clear(root);
      throw;
    }
    while (tmp)
    {
      if (tmp->data.first > pairs[i].second)
      {
        if (tmp->left)
        {
          tmp = tmp->left;
          continue;
        }
        else
        {
          tmp->left = node;
          node->parent = tmp;
          break;
        }
      }
      else if (tmp->data.first < pairs[i].first && tmp->data.second > pairs[i].second)
      {
        if (tmp->middle)
        {
          tmp = tmp->middle;
          continue;
        }
        else
        {
          tmp->middle = node;
          node->parent = tmp;
          break;
        }
      }
      else if (tmp->data.second < pairs[i].first)
      {
        if (tmp->right)
        {
          tmp = tmp->right;
          continue;
        }
        else
        {
          tmp->right = node;
          node->parent = tmp;
          break;
        }
      }
      else
      {
        delete node;
        break;
      }
    }
  }
  return root;
}
#endif
