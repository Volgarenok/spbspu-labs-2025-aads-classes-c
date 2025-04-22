#ifndef UTILS_HPP
#define UTILS_HPP
#include "tritree.hpp"
#include "iterators.hpp"

template< class T, class Cmp >
size_t intersects(TriTree< T, Cmp >* root, const std::pair< T, T >& nums);

template< class T, class Cmp >
size_t covers(TriTree< T, Cmp >* root, const std::pair< T, T >& nums);

template< class T, class Cmp >
size_t avoids(TriTree< T, Cmp >* root, const std::pair< T, T >& nums);

template< class T, class Cmp >
size_t intersects(TriTree< T, Cmp >* root, const std::pair< T, T >& nums)
{
  if (!root)
  {
    return 0;
  }
  size_t cnt = 0;
  auto it = begin(root);
  for (; it.hasNext(); it = it.next())
  {
    if (!std::less< T >{}(nums.second, it.data().first) && !std::less< T >{}(it.data().second, nums.first))
    {
      cnt++;
    }
  }
  if (!std::less< T >{}(nums.second, it.data().first) && !std::less< T >{}(it.data().second, nums.first))
  {
    cnt++;
  }
  return cnt;
}

template< class T, class Cmp >
size_t covers(TriTree< T, Cmp >* root, const std::pair< T, T >& nums)
{
  if (!root)
  {
    return 0;
  }
  size_t cnt = 0;
  auto it = begin(root);
  for (; it.hasNext(); it = it.next())
  {
    if (!std::less< T >{}(it.data().first, nums.first) && !std::greater< T >{}(it.data().second, nums.second))
    {
      cnt++;
    }
  }
  if (!std::less< T >{}(it.data().first, nums.first) && !std::greater< T >{}(it.data().second, nums.second))
  {
    cnt++;
  }
  return cnt;
}

template< class T, class Cmp >
size_t avoids(TriTree< T, Cmp >* root, const std::pair< T, T >& nums)
{
  if (!root)
  {
    return 0;
  }
  size_t cnt = 0;
  auto it = begin(root);
  for (; it.hasNext(); it = it.next())
  {
    if (std::less< T >{}(it.data().second, nums.first) && std::greater< T >{}(it.data().first, nums.second))
    {
      cnt++;
    }
  }
  if (std::less< T >{}(it.data().second, nums.first) && std::greater< T >{}(it.data().first, nums.second))
  {
    cnt++;
  }
  return cnt;
}
#endif
