#pragma once
#include <array>

namespace crc
{
  template<typename T, std::size_t N, template<std::size_t> class F, typename... Values>
  struct initialized_array : initialized_array<T, N-1, F, F<N-1>, Values...>
  {
  };

  template<typename T, template<std::size_t> class F, typename... Values>
  struct initialized_array<T, 0, F, Values...> : std::array<T, sizeof...(Values)>
  {
  public:
    constexpr initialized_array() : std::array<T, sizeof...(Values)>{{Values()...}} {}
  };
}
