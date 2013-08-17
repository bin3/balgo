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

#include <gtest/gtest.h>

#include "trie_traits.h"

namespace balgo {

TEST(UIntTraits, Traits) {
  EXPECT_EQ(1, sizeof(UIntTraits<1>::UInt));
  EXPECT_EQ(2, sizeof(UIntTraits<2>::UInt));
  EXPECT_EQ(4, sizeof(UIntTraits<4>::UInt));
  EXPECT_EQ(8, sizeof(UIntTraits<8>::UInt));
  EXPECT_EQ(4, sizeof(UIntTraits<0>::UInt));
  EXPECT_EQ(4, sizeof(UIntTraits<3>::UInt));
}

TEST(TrieTraits, Traits) {
  EXPECT_EQ(typeid(uint8_t), typeid(TrieTraits<char>::UChar));
  EXPECT_EQ(typeid(uint16_t), typeid(TrieTraits<int16_t>::UChar));
  EXPECT_EQ(typeid(uint32_t), typeid(TrieTraits<int32_t>::UChar));
  EXPECT_EQ(typeid(uint64_t), typeid(TrieTraits<int64_t>::UChar));
}

}  // namespace balgo
