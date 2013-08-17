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

#ifndef BALGO_TRIE_TRIE_H_
#define BALGO_TRIE_TRIE_H_

#include <stdint.h>
#include <cstddef>
#include <sstream>
#include <string>
#include <vector>

namespace balgo {

/**
 * @brief Interface for Trie
 *
 * @note Usage:
 * 1) Insert
 * 2) Build
 * 3) Match or MatchPrefix
 */
template<typename Char, typename Value, typename NodePtr = uint32_t>
class Trie {
 public:
  Trie() : not_built_(true) { }
  virtual ~Trie() { }

  bool Insert(const Char* begin, const Char* end, const Value &value) {
    if (not_built_) DoInsert(begin, end, value);
    return not_built_;
  }

  bool Insert(const Char* begin, std::size_t length, const Value &value) {
    if (not_built_) DoInsert(begin, begin + length, value);
    return not_built_;
  }

  bool Insert(const Char* begin, const Value &value) {
    if (not_built_) {
      std::size_t length = std::char_traits<Char>::length(begin);
      DoInsert(begin, begin + length, value);
    }
    return not_built_;
  }

  bool Build() {
    if (not_built_) {
      not_built_ = false;
      DoBuild();
      return true;
    }
    return false;
  }

  bool Match(const Char* begin, const Char* end, Value* value = NULL) const {
    NodePtr p = Root();
    for ( ; begin != end; ++begin) {
      NodePtr child = Child(p, *begin);
      if (IsNull(child)) return false;
      p = child;
    }
    if (!IsFinal(p)) {
      return false;
    }
    if (value) {
      *value = *GetValue(p);
    }
    return true;
  }

  bool Match(const Char* begin, std::size_t length, Value* value = NULL) const {
    return Match(begin, begin + length, value);
  }

  bool Match(const Char* begin, Value* value = NULL) const {
    std::size_t length = std::char_traits<Char>::length(begin);
    return Match(begin, begin + length, value);
  }


  template<typename Values>
  std::size_t MatchPrefix(const Char* begin, const Char* end, Values* values, bool clear = true) const {
    if (values && clear) values->clear();
    std::size_t cnt = 0;
    NodePtr p = Root();
    for ( ; begin != end; ++begin) {
      NodePtr child = Child(p, *begin);
      if (IsNull(child)) break;
      p = child;
      if (IsFinal(p)) {
        ++cnt;
        if (values) values->push_back(*GetValue(p));
      }
    }
    return cnt;
  }

  template<typename Values>
  std::size_t MatchPrefix(const Char* begin, std::size_t length, Values* values, bool clear = true) const {
    return MatchPrefix(begin, begin + length, values, clear);
  }

  template<typename Values>
  std::size_t MatchPrefix(const Char* begin, Values* values, bool clear = true) const {
    std::size_t length = std::char_traits<Char>::length(begin);
    return MatchPrefix(begin, begin + length, values, clear);
  }

  std::size_t MatchPrefix(const Char* begin, const Char* end) const {
    return MatchPrefix<DefaultValues>(begin, end, NULL, false);
  }

  std::size_t MatchPrefix(const Char* begin, std::size_t length) const {
    return MatchPrefix<DefaultValues>(begin, begin + length, NULL, false);
  }

  std::size_t MatchPrefix(const Char* begin) const {
    std::size_t length = std::char_traits<Char>::length(begin);
    return MatchPrefix<DefaultValues>(begin, begin + length, NULL, false);
  }

  void Clear() {
    not_built_ = true;
    DoClear();
  }

  virtual std::size_t NodeSize() const = 0;
  virtual std::size_t NumNodes() const = 0;
  virtual std::string Name() const = 0;
  virtual std::string ToString() const {
    return Name();
  }
  virtual std::string StatsString() const {
    std::stringstream ss;
    ss << "nodes=" << NumNodes() << ", node_size=" << NodeSize() << ", size="
        << static_cast<float>(NodeSize()) * NumNodes() / (1 << 20) << "M";
    return ss.str();
  }

 protected:
  typedef std::vector<Value> DefaultValues;

  virtual NodePtr Root() const = 0;
  virtual NodePtr Child(NodePtr parent, Char label) const = 0;
  virtual bool IsNull(NodePtr p) const = 0;
  virtual bool IsFinal(NodePtr p) const = 0;
  virtual const Value* GetValue(NodePtr p) const = 0;

  virtual void DoBuild(bool sort = true) = 0;
  virtual void DoInsert(const Char* begin, const Char* end, const Value &value) = 0;
  virtual void DoClear() = 0;

 private:
  bool not_built_;  ///< This Trie has not been built yet
};

}  // namespace balgo
#endif  // BALGO_TRIE_TRIE_H_
