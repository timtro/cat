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

#include <unordered_map>
#include <cat/functor/functor.hpp>

namespace cat
{
    // unordered_map is a functor:
    //

    template <> struct is_functor<std::unordered_map> : std::true_type { };

    // unordered_map instance:
    //

    template <typename Fun, typename K, typename A, typename Hash, typename Comp, typename Alloc>
    struct FunctorInstance<std::unordered_map, Fun, K, A, Hash, Comp, Alloc> : Functor<std::unordered_map>::Class1<Fun, K, A, Hash, Comp, Alloc>
    {
        using B = decltype(std::declval<Fun>()(std::declval<A>()));

        std::unordered_map<K, B, Hash, Comp, rebind_t<Alloc, std::pair<const K, B>>>
        fmap(Fun f, std::unordered_map<K, A, Hash, Comp, Alloc> const &xs) final
        {
            std::unordered_map<K, B, Hash, Comp, rebind_t<Alloc, std::pair<const K, B>> > out;

            for(auto & x : xs)
                out.insert(std::make_pair(x.first, f(x.second)));

            return out;
        }
    };

    // unordered_multimap is a functor:
    //

    template <> struct is_functor<std::unordered_multimap> : std::true_type { };

    // unordered_multimap instance:
    //

    template <typename Fun, typename K, typename A, typename Hash, typename Comp, typename Alloc>
    struct FunctorInstance<std::unordered_multimap, Fun, K, A, Hash, Comp, Alloc> : Functor<std::unordered_multimap>::Class1<Fun, K, A, Hash, Comp, Alloc>
    {
        using B = decltype(std::declval<Fun>()(std::declval<A>()));

        std::unordered_multimap<K, B, Hash, Comp, rebind_t<Alloc, std::pair<const K, B>>>
        fmap(Fun f, std::unordered_multimap<K, A, Hash, Comp, Alloc> const &xs) final
        {
            std::unordered_multimap<K, B, Hash, Comp, rebind_t<Alloc, std::pair<const K, B>> > out;

            for(auto & x : xs)
                out.insert(std::make_pair(x.first, f(x.second)));

            return out;
        }
    };
} // namespace cat
