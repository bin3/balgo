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
 * @date		2013-1-27
 */

#include "min_queue.h"
#include <gtest/gtest.h>

namespace toystl {

TEST(MinQueue, Method) {
  MinQueue<int> q;
  EXPECT_TRUE(q.Empty());
  q.Push(5);
  EXPECT_EQ(5, q.Min());
  q.Push(2);
  EXPECT_EQ(2, q.Min());
  q.Push(3);
  EXPECT_EQ(2, q.Min());
  EXPECT_EQ(3U, q.Size());
  q.Pop();
  EXPECT_EQ(2, q.Min());
  q.Pop();
  EXPECT_EQ(3, q.Min());
  q.Pop();
  EXPECT_TRUE(q.Empty());
  EXPECT_EQ(0U, q.Size());
}

} /* namespace toystl */
