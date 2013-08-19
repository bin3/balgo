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

#ifndef BALGO_AC_AHO_CORASICK_H_
#define BALGO_AC_AHO_CORASICK_H_

#include <queue>

#include "ac_da_trie.h"
#include "multi_pattern_matcher.h"

namespace balgo {

/**
 * @brief Aho–Corasick automata
 */
template<typename Char, typename Value, typename Trie = AcDaTrie<Char, Value> >
class AhoCorasick : public MultiPatternMatcher<Char, Value> {
 public:
  typedef typename Trie::NodePtrType NodePtr;

  AhoCorasick()
      : not_built_(true) {
  }
  virtual ~AhoCorasick() {
  }

  std::size_t NodeSize() const {
    return trie_.NodeSize();
  }

  std::size_t NumNodes() const {
    return trie_.NumNodes();
  }

  std::string Name() const {
    return "AhoCorasick";
  }

  std::string ToString() const {
    return trie_.ToString();
  }

  std::string StatsString() const {
    std::stringstream ss;
    ss << "nodes=" << NumNodes() << ", node_size=" << NodeSize() << ", size="
       << static_cast<float>(NodeSize()) * NumNodes() / (1 << 20) << "M";
    return ss.str();
  }

 protected:
  typedef MultiPatternMatcher<Char, Value> Base;
  typedef typename Base::MatchFunc MatchFunc;

  virtual void DoInsert(const Char* begin, const Char* end, const Value &value) {
    trie_.Insert(begin, end, value);
  }

  virtual void DoBuild(bool sort = true) {
    trie_.Build();
    Compile();
  }

  virtual std::size_t DoMatch(const Char* begin, const Char* end, MatchFunc& func) const {
    NodePtr root = trie_.Root();
    NodePtr cur = trie_.Root();
    NodePtr nxt = trie_.Null();
    std::size_t cnt = 0;
    for (const Char* it = begin; it != end; ++it) {
      while ((nxt = trie_.Child(cur, *it)) == trie_.Null()) {
        if (cur == root) {
          break;
        }
        cur = trie_.Fail(cur);
      }
      if (nxt != trie_.Null()) {
        cur = nxt;
        std::size_t pos = std::distance(begin, it);
        NodePtr report = cur;
        do {
          const Value* value = trie_.GetValue(report);
          if (value) {
            func(*(trie_.GetValue(report)), pos);
            ++cnt;
          }
          report = trie_.Report(report);
        } while (report != trie_.Null());
      }
    }
    return cnt;
  }

  void DoClear() {
    trie_.Clear();
  }

 private:
  virtual NodePtr Root() const {
    return trie_.Root();
  }
  virtual NodePtr Child(NodePtr parent, Char label) const {
    return trie_.Child(parent, label);
  }
  virtual bool IsFinal(NodePtr p) const {
    return trie_.IsFinal(p);
  }
  virtual const Value* GetValue(NodePtr p) const {
    return trie_.GetValue(p);
  }

  void Compile() {
    trie_.SetFail(trie_.Root(), trie_.Root());
    std::queue<NodePtr> q;
    q.push(trie_.Root());
    while (!q.empty()) {
      NodePtr parent = q.front();
      q.pop();
      for (NodePtr child = trie_.FirstChild(parent); child; child = trie_.Sibling(child)) {
        NodePtr fail = FindFail(parent, trie_.Label(child));
        trie_.SetFail(child, fail);
        q.push(child);
      }
      NodePtr report = FindReport(parent);
      trie_.SetReport(parent, report);
    }
  }

  NodePtr FindFail(NodePtr parent, Char label) const {
    NodePtr root = trie_.Root();
    NodePtr fail = trie_.Null();
    while (parent != root && trie_.Null() == (fail = trie_.Child(trie_.Fail(parent), label))) {
      parent = trie_.Fail(parent);
    }
    if (fail == trie_.Null()) {
      fail = root;
    }
    return fail;
  }

  NodePtr FindReport(NodePtr p) const {
    NodePtr fail = trie_.Fail(p);
    if (trie_.Final(fail)) {
      return fail;
    } else {
      return trie_.Report(fail);
    }
  }

  bool not_built_;
  Trie trie_;
};

}  // namespace balgo
#endif  // BALGO_AC_AHO_CORASICK_H_
