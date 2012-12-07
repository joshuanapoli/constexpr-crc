#pragma once

// Thanks to Xeo. http://stackoverflow.com/a/13073076/766900
namespace crc
{
  /* seq is an argument pack container for a list of indices, 0 to
  sizeof...(Index). */
  template<std::size_t... Index> struct seq {};

  /* Given seq types s1 and s2, concat<s1,s2>::type is a seq type whose
  argument pack concatenates the argument packs of s1 and s2. */
  template<class S1, class S2> struct concat;
  template<std::size_t... I1, std::size_t... I2>
  struct concat<seq<I1...>, seq<I2...>> : seq<I1..., (sizeof...(I1)+I2)...>
  {
    using type = seq<I1..., (sizeof...(I1)+I2)...>;
  };

  /* gen_seq<N>::type gives a seq type whose argument pack contains the
  sequence 0...N. Template instantiation depth is log2(N). */
  template<unsigned N> struct gen_seq : concat<typename gen_seq<N/2>::type, typename gen_seq<N-N/2>::type> { };
  template<> struct gen_seq<0> { using type = seq<>; };
  template<> struct gen_seq<1> { using type = seq<0>; };
}
