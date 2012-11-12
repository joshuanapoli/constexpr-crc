#pragma once

constexpr int crc_table_item(uint8_t n)
{
  ulong cm_tab (p_cm,index)
  p_cm_t p_cm;
  int    index;
  {
   int   i;
   ulong r;
   ulong topbit = BITMASK(p_cm->cm_width-1);
   ulong inbyte = (ulong) index;

   if (p_cm->cm_refin) inbyte = reflect(inbyte,8);
   r = inbyte << (p_cm->cm_width-8);
   for (i=0; i<8; i++)
      if (r & topbit)
         r = (r << 1) ^ p_cm->cm_poly;
      else
         r<<=1;
   if (p_cm->cm_refin) r = reflect(r,p_cm->cm_width);
   return r & widmask(p_cm);
  }
  return n;
}

template<unsigned int N, int ...Vals>
constexpr typename std::enable_if< N==sizeof...(Vals), std::array<int,N> >::type
generate_crc_table()
{
  return std::array<int,N>{{Vals...}};
}

template<int N, int ...Vals>
constexpr typename std::enable_if<N!=sizeof...(Vals), std::array<int,N>>::type 
generate_crc_table()
{
  return generate_crc_table<N, Vals..., f(sizeof...(Vals))>();  
}

template<uint32_t Polynomial, uint8_t N>
struct crc_table_item
{
};
