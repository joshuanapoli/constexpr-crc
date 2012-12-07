#pragma once
#include <array>
#include <crc/seq.hpp>

namespace crc
{
  namespace detail
  {
    template<typename T, typename Sequence>
    struct initialized_array_impl;
  
    template<typename T, std::size_t... Index>
    struct initialized_array_impl<T, seq<Index...>> : std::array<T, sizeof...(Index)>
    {
    public:
      template<typename F>
      constexpr initialized_array_impl( F f )
        : std::array<T, sizeof...(Index)>{{f(Index)...}}
      {}
    };
  }

  template<typename T, std::size_t N>
  struct initialized_array : detail::initialized_array_impl<T, typename gen_seq<N>::type>
  {
    template<typename F>
    constexpr initialized_array( F f )
      : detail::initialized_array_impl<T, typename gen_seq<N>::type>( f )
    {}
  };
}
