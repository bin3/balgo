/*
 * Copyright (c) 2013 Binson Zhang.
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @author	Binson Zhang <bin183cs@gmail.com>
 * @date		2013-8-16
 */

#ifndef BALGO_TRIE_TRIE_TRAITS_H_
#define BALGO_TRIE_TRIE_TRAITS_H_

#include <stdint.h>

namespace balgo {

template<int size>
struct UIntTraits {
  typedef uint32_t UInt;
};

template<>
struct UIntTraits<1> {
  typedef uint8_t UInt;
};

template<>
struct UIntTraits<2> {
  typedef uint16_t UInt;
};

template<>
struct UIntTraits<4> {
  typedef uint32_t UInt;
};

template<>
struct UIntTraits<8> {
  typedef uint64_t UInt;
};

/**
 * @brief Trie traits to help determine unsigned Char type
 */
template<typename Char>
struct TrieTraits {
  typedef typename UIntTraits<sizeof(Char)>::UInt UChar;
};

}  // namespace balgo
#endif  // BALGO_TRIE_TRIE_TRAITS_H_
