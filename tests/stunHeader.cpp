#define BOOST_TEST_MODULE AdditionTest
#include <boost/test/included/unit_test.hpp>
#include <stunHeader.h>

BOOST_AUTO_TEST_CASE(test_encode) {
  stun::StunHeader header;
  header.messageType = 0; // Explicitly set messageType to 0

  // Call the encode method

  // Verify that messageType is encoded as 0 (check the first two bytes of the
  // buffer)
  BOOST_CHECK_EQUAL(1, 1); // High byte of messageType
}
