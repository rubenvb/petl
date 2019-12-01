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

/*
 * utility/overload
 * Explicitly resolves multiple overloads of a function pointer.
 * The result matches the given arguments.
 */

#ifndef PETL_UTILITY_OVERLOAD_H
#define PETL_UTILITY_OVERLOAD_H

namespace petl::utility
{
  namespace detail
  {
    template<typename... ArgTypes>
    struct non_const_overload
    {
      template<typename ReturnType, typename ClassType>
      constexpr auto operator()(ReturnType(ClassType::* member_function_pointer)(ArgTypes...)) const
      {
        return member_function_pointer;
      }
    };

    template<typename... ArgTypes>
    struct const_overload
    {
      template<typename ReturnType, typename ClassType>
      constexpr auto operator()(ReturnType(ClassType::* const_member_function_pointer)(ArgTypes...) const) const
      {
        return const_member_function_pointer;
      }
    };

    template<typename... ArgTypes>
    struct volatile_overload
    {
      template<typename ReturnType, typename ClassType>
      constexpr auto operator()(ReturnType(ClassType::* volatile_member_function_pointer)(ArgTypes...) volatile) const
      {
        return volatile_member_function_pointer;
      }
    };

    template<typename... ArgTypes>
    struct const_volatile_overload
    {
      template<typename ReturnType, typename ClassType>
      constexpr auto operator()(ReturnType(ClassType::* const_volatile_member_function_pointer)(ArgTypes...) const volatile) const
      {
        return const_volatile_member_function_pointer;
      }
    };

    template<typename... ArgTypes>
    struct overload : non_const_overload<ArgTypes...>
                    , const_overload<ArgTypes...>
                    , volatile_overload<ArgTypes...>
                    , const_volatile_overload<ArgTypes...>
    {
      using non_const_overload<ArgTypes...>::operator();
      using const_overload<ArgTypes...>::operator();
      using volatile_overload<ArgTypes...>::operator();
      using const_volatile_overload<ArgTypes...>::operator();

      template<typename ReturnType>
      constexpr auto operator()(ReturnType(*function_pointer)(ArgTypes...)) const
      {
        return function_pointer;
      }
    };
  }
  template<typename... ArgTypes>
  constexpr detail::overload<ArgTypes...> overload{};

  template<typename... ArgTypes>
  constexpr detail::non_const_overload<ArgTypes...> non_const_overload{};
  template<typename... ArgTypes>
  constexpr detail::const_overload<ArgTypes...> const_overload{};

  template<typename... ArgTypes>
  constexpr detail::volatile_overload<ArgTypes...> volatile_overload{};

  template<typename... ArgTypes>
  constexpr detail::const_volatile_overload<ArgTypes...> const_volatile_overload{};
}

#endif
