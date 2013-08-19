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

#ifndef BALGO_MPM_TRIE_MPM_H_
#define BALGO_MPM_TRIE_MPM_H_

#include "balgo/trie/da_trie.h"
#include "multi_pattern_matcher.h"

namespace balgo {

/**
 * @brief Trie based multi-pattern matcher
 */
template<typename Char, typename Value, typename Trie = DaTrie<Char, Value> >
class TrieMpm : public MultiPatternMatcher<Char, Value> {
 public:
  virtual ~TrieMpm() { }

  virtual std::size_t NodeSize() const {
    return trie_.NodeSize();
  }

  virtual std::size_t NumNodes() const {
    return trie_.NumNodes();
  }

  virtual std::string Name() const {
    return "TrieMpm";
  }

  virtual std::string ToString() const {
    return trie_.ToString();
  }

 protected:
  typedef MultiPatternMatcher<Char, Value> Base;
  typedef typename Base::MatchFunc MatchFunc;

  struct TrieMatchFunc : public Trie::MatchFunc {
    TrieMatchFunc(MatchFunc& func, std::size_t base) : func_(func), base_(base) { }
    virtual void operator()(const Value& value, std::size_t offset) {
      func_(value, base_ + offset);
    }
   private:
    MatchFunc& func_;
    std::size_t base_;
  };

  virtual void DoInsert(const Char* begin, const Char* end, const Value &value) {
   trie_.Insert(begin, end, value);
 }

  virtual void DoBuild(bool sort = true) {
    trie_.Build();
  }

  virtual std::size_t DoMatch(const Char* begin, const Char* end, MatchFunc& func) const {
    std::size_t cnt = 0;
    for (std::size_t base = 0; begin != end; ++begin, ++base) {
      TrieMatchFunc tfunc(func, base);
      cnt += trie_.MatchPrefix(begin, end, tfunc);
    }
    return cnt;
  }

  virtual void DoClear() {
    trie_.Clear();
  }

 private:
  Trie trie_;
};

}  // namespace balgo
#endif  // BALGO_MPM_TRIE_MPM_H_
