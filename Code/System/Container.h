#pragma once

#include "HardbopAllocator.h"

#include <algorithm>
#include <array>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace HardBop
{
   template <typename T>
   using LinkedList = std::list<T, HardbopAllocator<T>>;

   template <class Key,
      class Value,
      class Predict = std::less<Key>,
      class Alloc = HardbopAllocator<pair<const Key, Value>>
   using Map = std::map<Key, Value, Predict, Alloc>;

   template<class Key,
      class Value,
      class Hasher = std::hash<Key>,
      class KeyEq = std::equal_to<Key>,
      class Alloc = HardbopAllocator<pair<const Key, Value>>>
     using HashMap = std::unordered_map<Key, Value, Hasher, KeyEq, Alloc>;

   template <class Value, class Alloc = HardbopAllocator<Value>>
   using Vector = std::vector<Value, Alloc>;
} // HardBop

