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

#ifndef BALGO_MPM_MULTI_PATTERN_MATCHER_H_
#define BALGO_MPM_MULTI_PATTERN_MATCHER_H_

#include <stdint.h>
#include <sstream>
#include <string>

namespace balgo {

/**
 * @brief Interface for multi-pattern matcher
 */
template<typename Char, typename Value>
class MultiPatternMatcher {
 public:
  struct MatchFunc {
    virtual void operator()(const Value& value, std::size_t offset) {
    }
  };

  template<typename Values>
  struct ValueMatchFunc : public MatchFunc {
   public:
    ValueMatchFunc(Values* values)
        : values_(values) {
    }
    virtual void operator()(const Value& value, std::size_t offset) {
      values_->push_back(value);
    }
   private:
    Values* values_;
  };

  MultiPatternMatcher() : not_built_(true) { }
  virtual ~MultiPatternMatcher() { }

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

  bool Build(bool sort = true) {
    if (not_built_) {
      not_built_ = false;
      DoBuild(sort);
      return true;
    }
    return false;
  }

  virtual std::size_t Match(const Char* begin, const Char* end, MatchFunc& func) const {
    return DoMatch(begin, end, func);
  }

  template<typename Values>
  std::size_t Match(const Char* begin, const Char* end, Values* values, bool clear = true) const {
    if (values && clear) values->clear();
    if (values) {
      ValueMatchFunc<Values> func(values);
      return DoMatch(begin, end, func);
    } else {
      static MatchFunc s_func;
      return DoMatch(begin, end, s_func);
    }
  }

  template<typename Values>
  std::size_t Match(const Char* begin, std::size_t length, Values* values, bool clear = true) const {
    return Match(begin, begin + length, values, clear);
  }

  template<typename Values>
  std::size_t Match(const Char* begin, Values* values, bool clear = true) const {
    std::size_t length = std::char_traits<Char>::length(begin);
    return Match(begin, begin + length, values, clear);
  }

  std::size_t Match(const Char* begin, const Char* end) const {
    static MatchFunc s_func;
    return Match(begin, end);
  }

  std::size_t Match(const Char* begin, std::size_t length) const {
    return Match(begin, begin + length, MatchFunc());
  }

  std::size_t Match(const Char* begin) const {
    std::size_t length = std::char_traits<Char>::length(begin);
    return Match(begin, begin + length);
  }

  void Clear() {
    not_built_ = true;
    DoClear();
  }

  virtual std::size_t NodeSize() const = 0;
  virtual std::size_t NumNodes() const = 0;

  virtual std::string Name() const {
    return "MultiPatternMatcher";
  }

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
  virtual void DoInsert(const Char* begin, const Char* end, const Value &value) = 0;
  virtual void DoBuild(bool sort = true) = 0;
  virtual std::size_t DoMatch(const Char* begin, const Char* end, MatchFunc& func) const = 0;
  virtual void DoClear() = 0;

 private:
  bool not_built_;  ///< It has not been built yet
};

}  // namespace balgo
#endif  // BALGO_MPM_MULTI_PATTERN_MATCHER_H_
