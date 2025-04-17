#ifndef TREE_UTILS
#define TREE_UTILS

#include "tree.hpp"
#include <cstddef>
#include <string>

namespace aleksandrov
{
  using tree_t = TriTree< int, std::less< int > >;

  template< class T, class Cmp >
  TriTreeIterator< T, Cmp > begin(TriTree< T, Cmp >* root)
  {
    assert(root != nullptr);
    return TriTreeIterator< T, Cmp >{root}.fallLeft();
  }

  template< class T, class Cmp >
  TriTreeIterator< T, Cmp > rbegin(TriTree< T, Cmp >* root)
  {
    assert(root != nullptr);
    return TriTreeIterator< T, Cmp >{root}.fallRight();
  }

  tree_t* getTree(std::pair< int, int >*, size_t);
  void pushPair(tree_t*, const std::pair< int, int >&);
  void clearTree(tree_t*);

  void processCommand(tree_t* tree, const std::string&, int, int);
  size_t intersects(tree_t*, int, int);
  size_t covers(tree_t*, int, int);
  size_t avoids(tree_t*, int, int);
}

#endif

