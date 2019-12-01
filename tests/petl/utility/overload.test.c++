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

#include "petl/test.h++"

#include <petl/utility/overload.h++>

#include <utility>

namespace
{
  [[maybe_unused]] void f();
  [[maybe_unused]] void f(int);
  [[maybe_unused]] void f(short);
  [[maybe_unused]] void f(int, short);

  [[maybe_unused]] void g(int, short = 1);

  struct A
  {
    virtual ~A () = default;

    [[maybe_unused]] void f();
    [[maybe_unused]] void f(int);
    [[maybe_unused]] void f(short);
    [[maybe_unused]] void f(int, short);

    [[maybe_unused]] void f() const;
    [[maybe_unused]] void f(int) const;
    [[maybe_unused]] void f(short) const;
    [[maybe_unused]] void f(int, short) const;

    [[maybe_unused]] void f() volatile;
    [[maybe_unused]] void f(int) volatile;
    [[maybe_unused]] void f(short) volatile;
    [[maybe_unused]] void f(int, short) volatile;

    [[maybe_unused]] void f() const volatile;
    [[maybe_unused]] void f(int) const volatile;
    [[maybe_unused]] void f(short) const volatile;
    [[maybe_unused]] void f(int, short) const volatile;

    [[maybe_unused]] int g(int, short = 1);
    [[maybe_unused]] int g(int, short = 1) const;
    [[maybe_unused]] int g(int, short = 1) volatile;
    [[maybe_unused]] int g(int, short = 1) const volatile;

    virtual void v();
    virtual void v(int);
    virtual void v(short);
    virtual void v(int, short);

    virtual void pv() = 0;
    virtual void pv(int) = 0;
    virtual void pv(short) = 0;
    virtual void pv(int, short) = 0;

    virtual void v() const;
    virtual void v(int) const;
    virtual void v(short) const;
    virtual void v(int, short) const;

    virtual void pv() const = 0;
    virtual void pv(int) const = 0;
    virtual void pv(short) const = 0;
    virtual void pv(int, short) const = 0;

    virtual void v() volatile;
    virtual void v(int) volatile;
    virtual void v(short) volatile;
    virtual void v(int, short) volatile;

    virtual void pv() volatile = 0;
    virtual void pv(int) volatile = 0;
    virtual void pv(short) volatile = 0;
    virtual void pv(int, short) volatile = 0;

    virtual void v() const volatile;
    virtual void v(int) const volatile;
    virtual void v(short) const volatile;
    virtual void v(int, short) const volatile;

    virtual void pv() const volatile = 0;
    virtual void pv(int) const volatile = 0;
    virtual void pv(short) const volatile = 0;
    virtual void pv(int, short) const volatile = 0;
  };

  struct B : A
  {
    ~B() override = default;

    void pv() override;
    void pv(int) override;
    void pv(short) override;
    void pv(int, short) override;

    void pv() const override;
    void pv(int) const override;
    void pv(short) const override;
    void pv(int, short) const override;

    void pv() volatile override;
    void pv(int) volatile override;
    void pv(short) volatile override;
    void pv(int, short) volatile override;

    void pv() const volatile override;
    void pv(int) const volatile override;
    void pv(short) const volatile override;
    void pv(int, short) const volatile override;
  };
}

using petl::utility::overload;
using petl::utility::non_const_overload;
using petl::utility::const_overload;
using petl::utility::volatile_overload;
using petl::utility::const_volatile_overload;

static_assert(std::is_same_v<decltype(overload<>(&f)), void(*)()>);
static_assert(std::is_same_v<decltype(overload<int>(&f)), void(*)(int)>);
static_assert(std::is_same_v<decltype(overload<short>(&f)), void(*)(short)>);
static_assert(std::is_same_v<decltype(overload<int, short>(&f)), void(*)(int, short)>);

static_assert(std::is_same_v<decltype(overload<>(&f)), void(*)()>);
static_assert(std::is_same_v<decltype(overload<int>(&f)), void(*)(int)>);
static_assert(std::is_same_v<decltype(overload<short>(&f)), void(*)(short)>);
static_assert(std::is_same_v<decltype(overload<int, short>(&f)), void(*)(int, short)>);

static_assert(std::is_same_v<decltype(non_const_overload<>(&A::f)), void(A::*)()>);
static_assert(std::is_same_v<decltype(non_const_overload<int>(&A::f)), void(A::*)(int)>);
static_assert(std::is_same_v<decltype(non_const_overload<short>(&A::f)), void(A::*)(short)>);
static_assert(std::is_same_v<decltype(non_const_overload<int, short>(&A::f)), void(A::*)(int, short)>);

static_assert(std::is_same_v<decltype(const_overload<>(&A::f)), void(A::*)() const>);
static_assert(std::is_same_v<decltype(const_overload<int>(&A::f)), void(A::*)(int) const>);
static_assert(std::is_same_v<decltype(const_overload<short>(&A::f)), void(A::*)(short) const>);
static_assert(std::is_same_v<decltype(const_overload<int, short>(&A::f)), void(A::*)(int, short) const>);

static_assert(std::is_same_v<decltype(volatile_overload<>(&A::f)), void(A::*)() volatile>);
static_assert(std::is_same_v<decltype(volatile_overload<int>(&A::f)), void(A::*)(int) volatile>);
static_assert(std::is_same_v<decltype(volatile_overload<short>(&A::f)), void(A::*)(short) volatile>);
static_assert(std::is_same_v<decltype(volatile_overload<int, short>(&A::f)), void(A::*)(int, short) volatile>);

static_assert(std::is_same_v<decltype(const_volatile_overload<>(&A::f)), void(A::*)() const volatile>);
static_assert(std::is_same_v<decltype(const_volatile_overload<int>(&A::f)), void(A::*)(int) const volatile>);
static_assert(std::is_same_v<decltype(const_volatile_overload<short>(&A::f)), void(A::*)(short) const volatile>);
static_assert(std::is_same_v<decltype(const_volatile_overload<int, short>(&A::f)), void(A::*)(int, short) const volatile>);

static_assert(std::is_same_v<decltype(non_const_overload<int, short>(&A::g)), int(A::*)(int, short)>);
static_assert(std::is_same_v<decltype(const_overload<int, short>(&A::g)), int(A::*)(int, short) const>);
static_assert(std::is_same_v<decltype(volatile_overload<int, short>(&A::g)), int(A::*)(int, short) volatile>);
static_assert(std::is_same_v<decltype(const_volatile_overload<int, short>(&A::g)), int(A::*)(int, short) const volatile>);

static_assert(std::is_same_v<decltype(non_const_overload<>(&A::v)), void(A::*)()>);
static_assert(std::is_same_v<decltype(non_const_overload<int>(&A::v)), void(A::*)(int)>);
static_assert(std::is_same_v<decltype(non_const_overload<short>(&A::v)), void(A::*)(short)>);
static_assert(std::is_same_v<decltype(non_const_overload<int, short>(&A::v)), void(A::*)(int, short)>);

static_assert(std::is_same_v<decltype(const_overload<>(&A::v)), void(A::*)() const>);
static_assert(std::is_same_v<decltype(const_overload<int>(&A::v)), void(A::*)(int) const>);
static_assert(std::is_same_v<decltype(const_overload<short>(&A::v)), void(A::*)(short) const>);
static_assert(std::is_same_v<decltype(const_overload<int, short>(&A::v)), void(A::*)(int, short) const>);

static_assert(std::is_same_v<decltype(volatile_overload<>(&A::v)), void(A::*)() volatile>);
static_assert(std::is_same_v<decltype(volatile_overload<int>(&A::v)), void(A::*)(int) volatile>);
static_assert(std::is_same_v<decltype(volatile_overload<short>(&A::v)), void(A::*)(short) volatile>);
static_assert(std::is_same_v<decltype(volatile_overload<int, short>(&A::v)), void(A::*)(int, short) volatile>);

static_assert(std::is_same_v<decltype(const_volatile_overload<>(&A::v)), void(A::*)() const volatile>);
static_assert(std::is_same_v<decltype(const_volatile_overload<int>(&A::v)), void(A::*)(int) const volatile>);
static_assert(std::is_same_v<decltype(const_volatile_overload<short>(&A::v)), void(A::*)(short) const volatile>);
static_assert(std::is_same_v<decltype(const_volatile_overload<int, short>(&A::v)), void(A::*)(int, short) const volatile>);

static_assert(std::is_same_v<decltype(non_const_overload<>(&B::v)), void(A::*)()>);
static_assert(std::is_same_v<decltype(non_const_overload<int>(&B::v)), void(A::*)(int)>);
static_assert(std::is_same_v<decltype(non_const_overload<short>(&B::v)), void(A::*)(short)>);
static_assert(std::is_same_v<decltype(non_const_overload<int, short>(&B::v)), void(A::*)(int, short)>);

static_assert(std::is_same_v<decltype(const_overload<>(&B::v)), void(A::*)() const>);
static_assert(std::is_same_v<decltype(const_overload<int>(&B::v)), void(A::*)(int) const>);
static_assert(std::is_same_v<decltype(const_overload<short>(&B::v)), void(A::*)(short) const>);
static_assert(std::is_same_v<decltype(const_overload<int, short>(&B::v)), void(A::*)(int, short) const>);

static_assert(std::is_same_v<decltype(volatile_overload<>(&B::v)), void(A::*)() volatile>);
static_assert(std::is_same_v<decltype(volatile_overload<int>(&B::v)), void(A::*)(int) volatile>);
static_assert(std::is_same_v<decltype(volatile_overload<short>(&B::v)), void(A::*)(short) volatile>);
static_assert(std::is_same_v<decltype(volatile_overload<int, short>(&B::v)), void(A::*)(int, short) volatile>);

static_assert(std::is_same_v<decltype(const_volatile_overload<>(&B::v)), void(A::*)() const volatile>);
static_assert(std::is_same_v<decltype(const_volatile_overload<int>(&B::v)), void(A::*)(int) const volatile>);
static_assert(std::is_same_v<decltype(const_volatile_overload<short>(&B::v)), void(A::*)(short) const volatile>);
static_assert(std::is_same_v<decltype(const_volatile_overload<int, short>(&B::v)), void(A::*)(int, short) const volatile>);

static_assert(std::is_same_v<decltype(non_const_overload<>(&A::pv)), void(A::*)()>);
static_assert(std::is_same_v<decltype(non_const_overload<int>(&A::pv)), void(A::*)(int)>);
static_assert(std::is_same_v<decltype(non_const_overload<short>(&A::pv)), void(A::*)(short)>);
static_assert(std::is_same_v<decltype(non_const_overload<int, short>(&A::pv)), void(A::*)(int, short)>);

static_assert(std::is_same_v<decltype(const_overload<>(&A::pv)), void(A::*)() const>);
static_assert(std::is_same_v<decltype(const_overload<int>(&A::pv)), void(A::*)(int) const>);
static_assert(std::is_same_v<decltype(const_overload<short>(&A::pv)), void(A::*)(short) const>);
static_assert(std::is_same_v<decltype(const_overload<int, short>(&A::pv)), void(A::*)(int, short) const>);

static_assert(std::is_same_v<decltype(volatile_overload<>(&A::pv)), void(A::*)() volatile>);
static_assert(std::is_same_v<decltype(volatile_overload<int>(&A::pv)), void(A::*)(int) volatile>);
static_assert(std::is_same_v<decltype(volatile_overload<short>(&A::pv)), void(A::*)(short) volatile>);
static_assert(std::is_same_v<decltype(volatile_overload<int, short>(&A::pv)), void(A::*)(int, short) volatile>);

static_assert(std::is_same_v<decltype(const_volatile_overload<>(&A::pv)), void(A::*)() const volatile>);
static_assert(std::is_same_v<decltype(const_volatile_overload<int>(&A::pv)), void(A::*)(int) const volatile>);
static_assert(std::is_same_v<decltype(const_volatile_overload<short>(&A::pv)), void(A::*)(short) const volatile>);
static_assert(std::is_same_v<decltype(const_volatile_overload<int, short>(&A::pv)), void(A::*)(int, short) const volatile>);

static_assert(std::is_same_v<decltype(non_const_overload<>(&B::pv)), void(B::*)()>);
static_assert(std::is_same_v<decltype(non_const_overload<int>(&B::pv)), void(B::*)(int)>);
static_assert(std::is_same_v<decltype(non_const_overload<short>(&B::pv)), void(B::*)(short)>);
static_assert(std::is_same_v<decltype(non_const_overload<int, short>(&B::pv)), void(B::*)(int, short)>);

static_assert(std::is_same_v<decltype(const_overload<>(&B::pv)), void(B::*)() const>);
static_assert(std::is_same_v<decltype(const_overload<int>(&B::pv)), void(B::*)(int) const>);
static_assert(std::is_same_v<decltype(const_overload<short>(&B::pv)), void(B::*)(short) const>);
static_assert(std::is_same_v<decltype(const_overload<int, short>(&B::pv)), void(B::*)(int, short) const>);

static_assert(std::is_same_v<decltype(volatile_overload<>(&B::pv)), void(B::*)() volatile>);
static_assert(std::is_same_v<decltype(volatile_overload<int>(&B::pv)), void(B::*)(int) volatile>);
static_assert(std::is_same_v<decltype(volatile_overload<short>(&B::pv)), void(B::*)(short) volatile>);
static_assert(std::is_same_v<decltype(volatile_overload<int, short>(&B::pv)), void(B::*)(int, short) volatile>);

static_assert(std::is_same_v<decltype(const_volatile_overload<>(&B::pv)), void(B::*)() const volatile>);
static_assert(std::is_same_v<decltype(const_volatile_overload<int>(&B::pv)), void(B::*)(int) const volatile>);
static_assert(std::is_same_v<decltype(const_volatile_overload<short>(&B::pv)), void(B::*)(short) const volatile>);
static_assert(std::is_same_v<decltype(const_volatile_overload<int, short>(&B::pv)), void(B::*)(int, short) const volatile>);
