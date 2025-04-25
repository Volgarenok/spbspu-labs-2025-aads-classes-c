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

size_t savintsev::intersect(tree_t * root, int v1, int v2)
{
  size_t count = 0;
  auto it = begin(root);
  for (; it.hasNext(); it = it.next())
  {
    if (((it.data().first - v2) * (v1 - it.data().second)) > 0)
    {
      count++;
    }
  }
  if (((it.data().first - v2) * (v1 - it.data().second)) > 0)
  {
    count++;
  }
  return count;
}

size_t savintsev::avoids(tree_t * root, int v1, int v2)
{
  size_t count = 0;
  auto it = begin(root);
  for (; it.hasNext(); it = it.next())
  {
    if (((it.data().first - v2) * (v1 - it.data().second)) <= 0)
    {
      count++;
    }
  }
  if (((it.data().first - v2) * (v1 - it.data().second)) <= 0)
  {
    count++;
  }
  return count;
}

size_t savintsev::covers(tree_t * root, int v1, int v2)
{
  size_t count = 0;
  auto it = begin(root);
  for (; it.hasNext(); it = it.next())
  {
    if (it.data().first <= v1 && it.data().second >= v2)
    {
      count++;
    }
  }
  if (it.data().first <= v1 && it.data().second >= v2)
  {
    count++;
  }
  return count;
}
