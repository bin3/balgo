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

#ifndef BRUTE_FORCE_H_
#define BRUTE_FORCE_H_

#include <cstddef>
#include <cstring>

namespace balgo {
namespace string {

template<typename T>
const T* BruteForceSearch(const T* pattern, std::size_t plen,
    const T* text, std::size_t tlen) {
  std::size_t pi = 0;
  for (std::size_t ti = 0; ti + plen <= tlen; ++ti) {
    for (pi = 0; pi < plen && pattern[pi] == text[ti + pi]; ++pi) {}
    if (pi == plen)
      return text + ti;
  }
  return NULL;
}

template<typename T>
const T* BruteForceSearch(const T* pattern, const T* text) {
  return BruteForceSearch(pattern, std::strlen(pattern), text,
      std::strlen(text));
}

template<typename T>
const T* BruteForceSearchFromRightToLeft(const T* pattern, std::size_t plen,
    const T* text, std::size_t tlen) {
  int pi = 0;
  for (std::size_t ti = 0; ti + plen <= tlen; ++ti) {
    for (pi = plen - 1; pi >= 0 && pattern[pi] == text[ti + pi]; --pi) {}
    if (pi < 0)
      return text + ti;
  }
  return NULL;
}

template<typename T>
const T* BruteForceSearchFromRightToLeft(const T* pattern, const T* text) {
  return BruteForceSearch(pattern, std::strlen(pattern), text,
      std::strlen(text));
}


} /* namespace string */
} /* namespace balgo */
#endif /* BRUTE_FORCE_H_ */
