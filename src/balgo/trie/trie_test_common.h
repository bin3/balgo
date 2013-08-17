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

#ifndef BALGO_TRIE_TRIE_TEST_COMMON_H_
#define BALGO_TRIE_TRIE_TEST_COMMON_H_

#include <vector>
#include <gtest/gtest.h>
#include <boost/range.hpp>

#include "trie.h"

#define ARRAY_SIZE(arr) sizeof(arr) / sizeof(arr[0])

namespace balgo {

void TestMatch(Trie<char, size_t>& trie) {
  trie.Clear();
  trie.Build();
  EXPECT_FALSE(trie.Match("abc"));

  const char * kPatterns[] = { "a", "bc", "abc", "abcde" };
  const char * kNonPatterns[] = { "", "ab", "bcd", "de", "abcdefabc" };

  trie.Clear();
  for (size_t i = 0; i < ARRAY_SIZE(kPatterns); ++i) {
    trie.Insert(kPatterns[i], i);
  }
  trie.Build();

  for (size_t i = 0; i < ARRAY_SIZE(kPatterns); ++i) {
    size_t value = 9999;
    EXPECT_TRUE(trie.Match(kPatterns[i], &value));
    EXPECT_EQ(i, value);
  }
  for (size_t i = 0; i < ARRAY_SIZE(kNonPatterns); ++i) {
    EXPECT_FALSE(trie.Match(kNonPatterns[i]));
  }
}

void TestMatchPrefix(Trie<char, size_t>& trie) {
  const char * kPatterns[] = { "a", "bca", "abc", "abcde" };
  const char * kNonPrefix[] = { "", "bc", "bbcd", "dabcde", "babcdefabc" };

  trie.Clear();
  for (size_t i = 0; i < ARRAY_SIZE(kPatterns); ++i) {
    trie.Insert(kPatterns[i], i);
  }
  trie.Build();

  std::vector<size_t> values;
  for (size_t i = 0; i < ARRAY_SIZE(kPatterns); ++i) {
    EXPECT_GE(trie.MatchPrefix(kPatterns[i], &values), 1) << " pattern: "
        << kPatterns[i];
  }
  for (size_t i = 0; i < ARRAY_SIZE(kNonPrefix); ++i) {
    EXPECT_EQ(trie.MatchPrefix(kNonPrefix[i]), 0) << " non-prefix: "
        << kNonPrefix[i];
  }

  EXPECT_EQ(0U, trie.MatchPrefix(""));
  EXPECT_EQ(0U, trie.MatchPrefix("babcdefg"));
  EXPECT_EQ(1U, trie.MatchPrefix("ab"));
  EXPECT_EQ(2U, trie.MatchPrefix("abc"));
  EXPECT_EQ(2U, trie.MatchPrefix("abcd"));
  EXPECT_EQ(3U, trie.MatchPrefix("abcde"));

  std::vector<size_t> expected;
  expected.push_back(0);
  expected.push_back(2);
  expected.push_back(3);
  ASSERT_EQ(3U, trie.MatchPrefix("abcdefgh", &values));
  EXPECT_EQ(expected, values);
}

}  // namespace balgo
#endif  // BALGO_TRIE_TRIE_TEST_COMMON_H_
