#define BOOST_TEST_MODULE table_test
#include <array>
#include <boost/test/unit_test.hpp>
#include <crc.hpp>
#include <boost/crc.hpp>

bool init_unit_test()
{
  return true;
}

BOOST_AUTO_TEST_CASE( constexpr_32_bit_crc_has_same_result_as_boost_crc )
{
  char message[] = "hello world";

  boost::crc_optimal<32, koopman32()> boost_crc;
  boost_crc.process_bytes( message, sizeof( message ) );

  crc<32,koopman32()> constexpr_crc;

  BOOST_CHECK_EQUAL
    ( constexpr_crc.process_cstring( message )
    , boost_crc.checksum()
    );
}

BOOST_AUTO_TEST_CASE( constexpr_32_bit_crc_has_same_result_as_boost_crc_with_initial_remainder )
{
  char message[] = u8"unicode stuff \u00FFaäáéöő";

  boost::crc_optimal<32, koopman32(), 0xffffffff> boost_crc;
  boost_crc.process_bytes( message, sizeof( message ) );

  crc<32,koopman32(), 0xffffffff> constexpr_crc;

  BOOST_CHECK_EQUAL
    ( constexpr_crc.process_cstring( message )
    , boost_crc.checksum()
    );
}

BOOST_AUTO_TEST_CASE( constexpr_8_bit_crc_has_same_result_as_boost_crc )
{
  char message[] = "hello world";

  boost::crc_optimal<8,koopman8()> boost_crc;
  boost_crc.process_bytes( message, sizeof( message ) );

  crc<8,koopman8()> constexpr_crc;

  BOOST_CHECK_EQUAL
    ( constexpr_crc.process_cstring( message )
    , boost_crc.checksum()
    );
}
