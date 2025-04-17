#include "tree-utils.hpp"

namespace aleksandrov
{
  tree_t* getTree(std::pair< int, int >* pairs, size_t quantity)
  {
    if (!quantity)
    {
      return nullptr;
    }
    tree_t* pairsTree = new tree_t{pairs[0]};
    try
    {
      for (size_t i = 1; i < quantity; ++i)
      {
        pushPair(pairsTree, pairs[i]);
      }
    }
    catch (const std::bad_alloc&)
    {
      clearTree(pairsTree);
      return nullptr;
    }
    return pairsTree;
  }

  void pushPair(tree_t* tree, const std::pair< int, int >& pair)
  {
    if (pair.second < tree->data.first)
    {
      if (!tree->left)
      {
        tree->left = new tree_t{pair, nullptr, nullptr, nullptr, tree};
      }
      else
      {
        pushPair(tree->left, pair);
      }
    }
    else if (pair.first < tree->data.first && tree->data.second < pair.second)
    {
      if (!tree->middle)
      {
        tree->middle = new tree_t{pair, nullptr, nullptr, nullptr, tree};
      }
      else
      {
        pushPair(tree->middle, pair);
      }
    }
    else if (tree->data.second < pair.first)
    {
      if (!tree->right)
      {
        tree->right = new tree_t{pair, nullptr, nullptr, nullptr, tree};
      }
      else
      {
        pushPair(tree->right, pair);
      }
    }
  }

  void clearTree(tree_t* tree)
  {
    if (!tree)
    {
      return;
    }
    clearTree(tree->left);
    clearTree(tree->middle);
    clearTree(tree->right);
    delete tree;
  }
}
