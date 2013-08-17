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
 * @date		2013-8-17
 */

#include <iostream>
#include <vector>

#include "da_trie.h"
#include "ternary_trie.h"

void Demo(balgo::Trie<char, size_t>& trie) {
  const char * kPatterns[] = { "a", "abc", "abcde", "bc", "bcd" };
  size_t n = sizeof(kPatterns) / sizeof(kPatterns[0]);

  trie.Clear();
  for (size_t i = 0; i < n; ++i) {
    trie.Insert(kPatterns[i], i);
  }
  trie.Build();

  std::cout << "Using " << trie.Name() << std::endl;
  std::cout << "StatsString: " << trie.StatsString() << std::endl;

  for (size_t i = 0; i < n; ++i) {
    size_t value;
    if (trie.Match(kPatterns[i], &value)) {
      std::cout << "[Match] pattern=" << kPatterns[i] << ", value=" << value << std::endl;
    }
  }

  for (size_t i = 0; i < n; ++i) {
    std::vector<size_t> values;
    if (trie.MatchPrefix(kPatterns[i], &values) > 0) {
      std::cout << "[MatchPrefix] pattern=" << kPatterns[i] << ", values=[";
      for (size_t j = 0; j < values.size(); ++j) {
        if (j) std::cout << ", ";
        std::cout << values[j];
      }
      std::cout << "]" << std::endl;
    }
  }
}

int main(int argc, char **argv) {
	std::cout << "------" << argv[0] << "------" << std::endl;

  balgo::DaTrie<char, size_t> datrie;
  balgo::TernaryTrie<char, size_t> tetrie;
  Demo(datrie);
  Demo(tetrie);

  return 0;
}
