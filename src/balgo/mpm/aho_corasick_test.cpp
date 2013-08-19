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
 * @date		2013-8-18
 */

#include <vector>
#include <gtest/gtest.h>

#include "aho_corasick.h"
#include "mpm_test_common.h"

namespace balgo {

TEST(AhoCorasick, Match) {
  AhoCorasick<char, size_t> mpm;
  TestMatch(mpm);

  std::vector<size_t> expected;
  expected.push_back(0);
  expected.push_back(0);
  expected.push_back(2);
  expected.push_back(1);
  expected.push_back(4);
  expected.push_back(3);
  std::vector<size_t> values;
  EXPECT_EQ(6U, mpm.Match("ababcdef", &values));
  EXPECT_EQ(expected, values) << "mpm.ToString: \n" << mpm.ToString();
}

TEST(AhoCorasick, Match2) {
  AhoCorasick<char, size_t> ac;
  ac.Build();
  EXPECT_EQ(0U, ac.Match("abc"));

  const char * kPatterns[] = { "a", "bc", "abc", "abcde", "cd" };
  size_t n = sizeof(kPatterns) / sizeof(kPatterns[0]);

  ac.Clear();
  for (size_t i = 0; i < n; ++i) {
    ac.Insert(kPatterns[i], i);
  }
  ac.Build();

  EXPECT_EQ(1U, ac.Match("a"));
  EXPECT_EQ(3U, ac.Match("abc"));

  std::vector<size_t> expected;
  expected.push_back(0);
  expected.push_back(0);
  expected.push_back(2);
  expected.push_back(1);
  expected.push_back(4);
  expected.push_back(3);
  std::vector<size_t> values;
  EXPECT_EQ(6U, ac.Match("ababcdef", &values));
  EXPECT_EQ(expected, values) << "ac.ToString: \n" << ac.ToString();
}

}  // namespace balgo
