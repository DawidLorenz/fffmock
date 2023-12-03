/*
MIT License

Copyright (c) 2023 Dawid Lorenz

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <stdint.h>
#include <functional>
#include "fff/fff.h"

namespace fffmock {

template <typename FFFFunctionFake>
class MockFFF {
 public:
  using ReturnType = decltype(FFFFunctionFake()->return_val);

  MockFFF &Times(const uint64_t &times) {
    mCallCount = times;
    return *this;
  }

  MockFFF &ResetHistory() {
    mResetFake();
    return *this;
  }

  MockFFF &WillOnce(const ReturnType &once) { return *this; }
  MockFFF &WillRepeatedly(const ReturnType &repeat) { return *this; }

 public:
  MockFFF(FFFFunctionFake functionFake, int line, const char *functionName,
          std::function<void()> resetFake)
      : mFFFFake(functionFake),
        mLine(line),
        mFunctionName(functionName),
        mResetFake(resetFake){};
  ~MockFFF() { OnDestroy(); };
  MockFFF(const MockFFF &other) = delete;
  MockFFF &operator=(const MockFFF &other) = delete;
  MockFFF(MockFFF &&other) = delete;
  MockFFF &operator=(MockFFF &&other) = delete;

 private:
  void OnDestroy() {
    // Check Times function if needed
    if (mCallCount != MinValue<decltype(mCallCount)>()) {
      ExpectTrue(mFFFFake->call_count == mCallCount);
    }

    // Reset history at the end
    ResetHistory();
  }

 private:  // helper functions
  template <typename T>
  constexpr T MinValue() {
    return std::numeric_limits<T>::min();
  }
  void ExpectTrue(bool checkCase) {
    if (checkCase != true) {
    }
  }

 private:
  std::function<void()> mResetFake;

 private:
  uint64_t mCallCount;
  int mLine;
  const char *mFunctionName;

 private:
  FFFFunctionFake mFFFFake;
};

}  // namespace fffmock

/**
 * @brief Define which creates the MockFFF object and allows calling the
 * function
 *
 * @param object object name.
 * @param fff_function Fake function from FFF.
 */
#define MOCK_FFF_EXPECT_CALL(object, fff_function)         \
  fffmock::MockFFF<decltype(&fff_function##_fake)> object( \
      &fff_function##_fake, __LINE__, __FILE__,            \
      []() { RESET_FAKE(fff_function) });                  \
  object
