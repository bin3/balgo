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

#ifndef BALGO_TRIE_TERNARY_TRIE_H_
#define BALGO_TRIE_TERNARY_TRIE_H_

#include <stdint.h>
#include <algorithm>
#include <deque>
#include <functional>
#include <sstream>
#include <string>
#include <vector>

#include "trie_traits.h"
#include "trie.h"

namespace balgo {

/**
 * @brief Ternary Trie
 */
template<typename Char = char, typename Value = uint32_t, typename NodePtr = uint32_t,
    typename Compare = std::less<Char> >
class TernaryTrie : public Trie<Char, Value, NodePtr> {
 public:
  typedef typename TrieTraits<Char>::UChar UChar;

  struct Node;
  struct AuxUnit;
  struct Key;
  typedef std::vector<Node> NodeContainer;
  typedef std::vector<AuxUnit> AuxContainer;
  typedef std::vector<Key> KeyContainer;
  typedef std::vector<NodePtr> KidContainer;
  typedef std::vector<Value> ValueContainer;

  struct Node {
    NodePtr child;
    Char label;
    UChar nchild;
    bool final;
    bool sibling;
    Node()
        : child(Null()),
          label(NullChar()),
          nchild(0),
          final(false),
          sibling(false) {
    }
    NodePtr GetValueIndex() const {
      return child;
    }
    void SetValueIndex(NodePtr idx) {
      child = idx;
    }
    std::string ToString() const {
      std::stringstream ss;
      ss << this << "(child=" << child <<  ", label=";
      ss << HexString(static_cast<UChar>(label)) << ", nchild="
          << static_cast<uint32_t>(nchild) << ", sibling=" << sibling << ", final=" << final
          << ")";
      return ss.str();
    }
  };

  struct Key {
    const Char* ptr;
    std::size_t length;
    Key(const Char* p, std::size_t l)
        : ptr(p),
          length(l) {
    }
    bool operator<(const Key& rhs) const {
      static Compare s_cmp;
      const Char* lp = ptr;
      const Char* rp = rhs.ptr;
      std::size_t minlen = std::min(length, rhs.length);
      for (std::size_t i = 0; i < minlen; ++i) {
        if (s_cmp(lp[i], rp[i])) {
          return true;
        } else if (s_cmp(rp[i], lp[i])) {
          return false;
        }
      }
      return length < rhs.length;
    }
    bool operator==(const Key& rhs) const {
      if (length != rhs.length) {
        return false;
      }
      for (std::size_t i = 0; i < length; ++i) {
        if (ptr[i] != rhs.ptr[i]) {
          return false;
        }
      }
      return true;
    }
    std::string ToString() const {
      std::stringstream ss;
      for (std::size_t i = 0; i < length; ++i) {
        ss << HexString(static_cast<UChar>(ptr[i])) << " ";
      }
      return ss.str();
    }
  };
  class KeyIdLess {
   public:
    explicit KeyIdLess(KeyContainer& p)
        : keys_(p) {
    }
    bool operator()(const NodePtr lhs, const NodePtr rhs) const {
      return keys_[lhs] < keys_[rhs];
    }
   private:
    KeyContainer& keys_;
  };
  class KeyIdEqual {
   public:
    explicit KeyIdEqual(KeyContainer& keys)
        : keys_(keys) {
    }
    bool operator()(const NodePtr lhs, const NodePtr rhs) const {
      return keys_[lhs] == keys_[rhs];
    }
   private:
    KeyContainer& keys_;
  };

  virtual ~TernaryTrie() { }

  virtual std::size_t NodeSize() const {
    return sizeof(Node);
  }

  virtual std::size_t NumNodes() const {
    return units_.size();
  }

  virtual std::string Name() const {
    return "TernaryTrie";
  }

  virtual std::string ToString() const {
    std::stringstream ss;
    for (std::size_t i = Root(); i < units_.size(); ++i) {
      ss << "[" << i << "] " << units_[i].ToString() << "\n";
    }
    return ss.str();
  }

 protected:
  virtual NodePtr Root() const {
    return 1;
  }

  virtual NodePtr Child(const NodePtr parent, Char label) const {
    if (!HasRealChild(parent)) {
      return Null();
    }
    const Node& unit = units_[parent];
    NodePtr lo = unit.child + unit.final;
    NodePtr hi = unit.child + unit.nchild;
    while (lo < hi) {
      NodePtr mid = lo + (hi - lo) / 2;
      if (units_[mid].label == label) {
        return mid;
      }
      if (cmp_(units_[mid].label, label)) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }
    return Null();
  }

  virtual bool IsNull(NodePtr p) const {
    return p == Null();
  }

  virtual bool IsFinal(const NodePtr node) const {
    return units_[node].final;
  }

  virtual const Value* GetValue(NodePtr node) const {
    if (units_[node].final) {
      NodePtr idx = units_[units_[node].child].GetValueIndex();
      return &(values_[idx]);
    }
    return NULL;
  }

  virtual void DoInsert(const Char* begin, const Char* end, const Value &value) {
    if (begin != end) {
      std::size_t length = end - begin;
      keys_.push_back(Key(begin, length));
      values_.push_back(value);
    }
  }

  virtual void DoBuild(bool sort = true) {
    kids_.clear();
    for (std::size_t i = 0; i < keys_.size(); ++i) {
      kids_.push_back(i);
    }
    if (sort) {
      std::sort(kids_.begin(), kids_.end(), KeyIdLess(keys_));
      typename KidContainer::iterator new_end = std::unique(kids_.begin(), kids_.end(),
                                                                   KeyIdEqual(keys_));
      kids_.resize(new_end - kids_.begin());
    }

    // init m_root
    units_.clear();
    while (units_.size() <= Root()) {
      units_.push_back(Node());
    }

    BuildNode(0, Root(), 0, kids_.size());

    // release keys_
    KeyContainer().swap(keys_);
  }

  virtual void DoClear() {
    units_.clear();
    values_.clear();
    kids_.clear();
    keys_.clear();
  }

 private:
  static Char NullChar() {
    return 0;
  }

  static NodePtr Null() {
    return 0;
  }

  // debug
  template<typename T>
  static std::string HexString(T x) {
    std::stringstream ss;
    ss << std::hex << static_cast<uint64_t>(x);
    return ss.str();
  }

  static std::string HexString(Char x) {
    return HexString(static_cast<UChar>(x));
  }

  bool HasRealChild(const NodePtr parent) const {
    return (units_[parent].nchild > 1)
        || (units_[parent].nchild == 1 && !units_[parent].final);
  }

  void BuildNode(std::size_t depth, NodePtr parent, NodePtr begin, NodePtr end) {
    if (begin >= end)
      return;

    units_[parent].child = units_.size();

    std::vector<NodePtr> guards;
    NodePtr prev_node = Null();
    Char prev_label = NullChar();
    for (NodePtr i = begin; i < end; ++i) {
      const Key& key = keys_[kids_[i]];
      Char label = (depth < key.length) ? key.ptr[depth] : NullChar();
      if (i == begin || label != prev_label) {
        prev_label = label;
        guards.push_back(i);
        if (!IsNull(prev_node)) {
          units_[prev_node].sibling = true;
        }
        prev_node = units_.size();
        units_.push_back(Node());
        units_.back().label = label;
        units_[parent].nchild++;
      }
    }
    guards.push_back(end);

    if (keys_[kids_[begin]].length == depth) {
      units_[parent].final = true;
      units_[units_[parent].child].SetValueIndex(kids_[begin]);
      prev_node = units_[parent].child;
    }

    for (NodePtr i = units_[parent].final; i < units_[parent].nchild; ++i) {
      NodePtr child = units_[parent].child + i;
      BuildNode(depth + 1, child, guards[i], guards[i + 1]);
    }
  }

  Char Label(const NodePtr node) const {
    return units_[node].label;
  }

  Compare cmp_;
  NodeContainer units_;
  ValueContainer values_;
  KidContainer kids_;
  KeyContainer keys_;    // Released at the end of Build
};

}  // namespace balgo
#endif  // BALGO_TRIE_TERNARY_TRIE_H_
