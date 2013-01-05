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
 * @date		2013-1-5
 */

#include "brute_force_search.h"
#include <gtest/gtest.h>

namespace balgo {
namespace string {

TEST(BruteForce, BruteForceSearch) {
  const char* p = BruteForceSearch("abc", "abbbbc");
  EXPECT_EQ(NULL, p);

  p = BruteForceSearch("abc", "iamnotanabcohyeah");
  EXPECT_STREQ("abcohyeah", p);
}

TEST(BruteForce, BruteForceSearchFromRightToLeft) {
  const char* p = BruteForceSearchFromRightToLeft("abc", "abbbbc");
  EXPECT_EQ(NULL, p);

  p = BruteForceSearchFromRightToLeft("abc", "iamnotanabcohyeah");
  EXPECT_STREQ("abcohyeah", p);
}

} /* namespace string */
} /* namespace balgo */
