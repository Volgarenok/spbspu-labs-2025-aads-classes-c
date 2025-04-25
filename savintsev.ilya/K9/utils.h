#ifndef UTILS_H
#define UTILS_H
#include <functional>
#include "ternary-search-tree.hpp"

using tree_t = savintsev::TriTree< int, std::less< int > >;

namespace savintsev
{
  tree_t * convert_ints_to_tree(std::pair< int, int > * vals, size_t n);
  void clear(tree_t * root);

  size_t intersect(tree_t * root, int v1, int v2);
  size_t covers(tree_t * root, int v1, int v2);
  size_t avoids(tree_t * root, int v1, int v2);
}

#endif
