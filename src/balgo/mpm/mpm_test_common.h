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

#include "multi_pattern_matcher.h"

namespace balgo {

static void TestMatch(MultiPatternMatcher<char, size_t>& mpm) {
  mpm.Build();
  EXPECT_EQ(0U, mpm.Match("abc"));

  const char * kPatterns[] = { "a", "bc", "abc", "abcde", "cd" };
  size_t n = sizeof(kPatterns) / sizeof(kPatterns[0]);

  mpm.Clear();
  for (size_t i = 0; i < n; ++i) {
    mpm.Insert(kPatterns[i], i);
  }
  mpm.Build();

  EXPECT_EQ(1U, mpm.Match("a"));
  EXPECT_EQ(3U, mpm.Match("abc"));
  EXPECT_EQ(6U, mpm.Match("ababcdef"));
}

}  // namespace balgo
