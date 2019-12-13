/**
 * The MIT License (MIT)
 *
 * Copyright © 2019 Ruben Van Boxem
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 **/

#include "petl/traits/pointee_type.h++"

#include <type_traits>

namespace
{
  struct A
  {
    virtual ~A() = default;

    int i;
    [[maybe_unused]] void f();
    [[maybe_unused]] virtual void g();
  };

  struct B : A
  {
    ~B() override = default;

    int ii;
    [[maybe_unused]] void ff();
    [[maybe_unused]] void g() override;
  };
}

using petl::traits::pointee_type_t;

static_assert(std::is_same_v<pointee_type_t<decltype(&A::i)>, int>);
static_assert(std::is_same_v<pointee_type_t<decltype(&A::f)>, void()>);
static_assert(std::is_same_v<pointee_type_t<decltype(&A::g)>, void()>);

static_assert(std::is_same_v<pointee_type_t<decltype(&B::i)>, int>);
static_assert(std::is_same_v<pointee_type_t<decltype(&B::f)>, void()>);
static_assert(std::is_same_v<pointee_type_t<decltype(&B::g)>, void()>);

static_assert(std::is_same_v<pointee_type_t<decltype(&B::ii)>, int>);
static_assert(std::is_same_v<pointee_type_t<decltype(&B::ff)>, void()>);
