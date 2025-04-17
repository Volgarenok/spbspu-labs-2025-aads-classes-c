#include "tree-utils.hpp"
#include <iostream>

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

  void processCommand(tree_t* tree, const std::string& command, int param1, int param2)
  {
    if (command == "intersects")
    {
      std::cout << intersects(tree, param1, param2) << '\n';
    }
    else if (command == "covers")
    {
      std::cout << covers(tree, param1, param2) << '\n';
    }
    else if (command == "avoids")
    {
      std::cout << avoids(tree, param1, param2) << '\n';
    }
    else
    {
      throw std::logic_error("Unknown command!");
    }
  }

  size_t intersects(tree_t* tree, int a, int b)
  {
    size_t count = 0;
    for (auto it = begin(tree);; it = it.next())
    {
      if ((it.data().first <= b && a <= it.data().second) ||
        (it.data().second >= a && it.data().first >= b))
      {
        ++count;
      }
      if (!it.hasNext())
      {
        break;
      }
    }
    return count;
  }

  size_t covers(tree_t* tree, int a, int b)
  {
    size_t count = 0;
    for (auto it = begin(tree);; it = it.next())
    {
      if (a <= it.data().first && it.data().second <= b)
      {
        ++count;
      }
      if (!it.hasNext())
      {
        break;
      }
    }
    return count;
  }

  size_t avoids(tree_t* tree, int a, int b)
  {
    size_t count = 0;
    for (auto it = begin(tree);; it = it.next())
    {
      if (!(it.data().first <= b && a <= it.data().second) &&
          !(it.data().second >= a && it.data().first >= b))
      {
        ++count;
      }
      if (!it.hasNext())
      {
        break;
      }
    }
    return count;
  }
}

