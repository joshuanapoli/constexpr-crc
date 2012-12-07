#define BOOST_TEST_ALTERNATIVE_INIT_API
#include <array>
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test.hpp>
#include <crc/initialized_array.hpp>

bool init_unit_test()
{
  return true;
}

struct times_two
{
  constexpr std::size_t operator()( std::size_t x ) { return x*2; }
};

BOOST_AUTO_TEST_CASE( initialized_array_test )
{
  constexpr crc::initialized_array<std::size_t, 5> actual_array{ times_two() };

  std::array<std::size_t,5> expected_array{{0,2,4,6,8}};

  BOOST_CHECK_EQUAL_COLLECTIONS
    ( actual_array.begin(), actual_array.end()
    , expected_array.begin(), expected_array.end()
    );
}
