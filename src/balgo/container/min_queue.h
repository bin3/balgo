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

#ifndef MIN_QUEUE_H_
#define MIN_QUEUE_H_

#include <deque>

namespace toystl {

/**
 * @brief Queue with minimum operator
 */
template<typename T>
class MinQueue {
public:
  void Push(const T& x) {
    q_.push_back(x);
    while (!sq_.empty() && sq_.back() > x) {
      sq_.pop_back();
    }
    sq_.push_back(x);
  }
  void Pop() {
    if (!q_.empty()) {
      if (q_.front() == sq_.front()) sq_.pop_front();
      q_.pop_front();
    }
  }
  T Front() const {
    if (!q_.empty()) return q_.front();
    return T();
  }
  std::size_t Size() const {
    return q_.size();
  }
  bool Empty() const {
    return q_.empty();
  }
  T Min() const {
    if (!sq_.empty()) return sq_.front();
    return T();
  }
private:
  std::deque<T> q_;
  std::deque<T> sq_;
};

} /* namespace toystl */
#endif /* MIN_QUEUE_H_ */
