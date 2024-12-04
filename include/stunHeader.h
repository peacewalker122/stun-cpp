// StunHeader.h
#ifndef STUN_HEADER_H
#define STUN_HEADER_H

#include <array>
#include <cstdint>
#include <vector>

namespace stun {

struct StunHeader {
  uint16_t messageType;
  uint16_t messageLength;
  uint32_t magicCookie;
  std::array<uint8_t, 12> transactionID;

  std::vector<uint8_t> Serialize();
  static StunHeader Deserialize(const std::vector<uint8_t> &buffer);
};

} // namespace stun

#endif // STUN_HEADER_H
