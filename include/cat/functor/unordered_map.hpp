#pragma once

#include <unordered_map>

#include <cat/functor/functor.hpp>

namespace cat
{
    // unordered_map instance:

    template <typename Fun, typename K, typename A, typename Hash, typename Comp, typename Alloc>
    struct FunctorInstance<std::unordered_map, Fun, K, A, Hash, Comp, Alloc> : Functor<std::unordered_map>::Class1<Fun, K, A, Hash, Comp, Alloc>
    {
        using B = decltype(std::declval<Fun>()(std::declval<A>()));

        auto fmap(Fun f, std::unordered_map<K, A, Hash, Comp, Alloc> const &xs) -> std::unordered_map<K, B, Hash, Comp, rebind_t<Alloc, std::pair<const K, B>> > final
        {
            std::unordered_map<K, B, Hash, Comp, rebind_t<Alloc, std::pair<const K, B>> > out;

            for(auto & x : xs)
                out.insert(std::make_pair(x.first, f(x.second)));

            return out;
        }
    };



} // namespace cat
