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

#ifndef BALGO_AC_AC_TRIE_H_
#define BALGO_AC_AC_TRIE_H_

namespace balgo {

/**
 * @brief Trie for Aho–Corasick
 */
template<typename Char, typename Value, typename NodePtr = uint32_t>
class AcTrie {
 public:
  typedef NodePtr NodePtrType;

  virtual ~AcTrie() { }

  static NodePtr Null() {
    return 0;
  }

  static bool IsNull(NodePtr p) {
    return p == Null();
  }

  virtual NodePtr Root() const = 0;
  virtual NodePtr Child(NodePtr parent, Char label) const = 0;
  virtual bool IsFinal(NodePtr p) const = 0;
  virtual const Value* GetValue(NodePtr p) const = 0;

  virtual NodePtr FirstChild(const NodePtr parent) const = 0;
  virtual NodePtr Sibling(const NodePtr p) const = 0;
  virtual NodePtr Fail(const NodePtr p) const = 0;
  virtual void SetFail(NodePtr p, const NodePtr fail) = 0;
  virtual NodePtr Report(const NodePtr p) const = 0;
  virtual void SetReport(NodePtr p, NodePtr report) = 0;

  virtual void Insert(const Char* begin, const Char* end, const Value &value) = 0;
  virtual void Build(bool sort = true) = 0;
  virtual void Clear() = 0;
};

}  // namespace balgo
#endif  // BALGO_AC_AC_TRIE_H_
