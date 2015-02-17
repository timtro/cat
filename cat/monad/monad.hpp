/******************************************************************************
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2014-15 Nicola Bonelli <nicola@pfq.io>
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
 *
 ******************************************************************************/

#pragma once

#include <utility>
#include <cat/type_traits.hpp>

namespace cat
{
    template <template <typename ...> class M>
    struct MonadNull
    {
        template <typename T>
        M<T> operator()(T const &) const
        {
            return M<T>{};
        }
    };

    //
    // class Monad
    //

    template <template <typename ...> class M>
    struct Monad
    {
        template <typename Fun, typename A>
        struct Class
        {
            virtual auto mbind(M<A> const & ma, Fun f)
                -> M< inner_type_t<decltype(f(std::declval<A>()))> > = 0;

            virtual M<A> mreturn(A const &) = 0;
        };
    };

    template <template <typename ...> class M, typename ...> struct MonadInstance;

    template <template <typename ...> class M, typename Fun, typename A>
    auto mbind(M<A> const &ma, Fun f)
    {
        return MonadInstance<M, A, Fun>{}.mbind(ma, std::move(f));
    }

    template <template <typename ...> class M, typename Fun, typename A>
    auto operator>>=(M<A> const &ma, Fun f)
    {
        return mbind(ma, std::move(f));
    }

    template <template <typename ...> class M, typename A>
    auto mreturn(A const &a)
    {
        return MonadInstance<M, A, MonadNull<M>>{}.mreturn(a);
    }

    template <template <typename...> class F>
    struct is_monad : std::false_type
    { };


} // namespace cat

