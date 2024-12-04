#include "stunHeader.h"
#include <cstdint>
#include <cstring>
#include <iostream>
#include <ostream>

namespace stun {

StunHeader StunHeader::Deserialize(const std::vector<uint8_t> &buffer) {
  if (buffer.size() != 96) {
    throw std::runtime_error("Invalid STUN header size");
  }

  StunHeader header;
  header.messageType = (buffer[0] << 8) | buffer[1];
  header.messageLength = (buffer[2] << 8) | buffer[3];
  header.magicCookie =
      (buffer[4] << 24) | (buffer[5] << 16) | (buffer[6] << 8) | buffer[7];
  for (size_t i = 0; i < 12; ++i) {
    header.transactionID[i] = buffer[8 + i];
  }
  return header;
}

std::vector<uint8_t> StunHeader::Serialize() {
  std::vector<uint8_t> buffer(96);

  buffer[0] = messageType >> 8;   // High byte of messageType
  buffer[1] = messageType & 0xFF; // Low byte of messageType

  std::cout << "Message type: " << messageType << std::endl;

  buffer[2] = messageLength >> 8;
  buffer[3] = messageLength & 0xFF;

  buffer[4] = magicCookie >> 24;
  buffer[5] = magicCookie >> 16;
  buffer[6] = magicCookie >> 8;
  buffer[7] = magicCookie & 0xFF;

  for (size_t i = 0; i < 12; ++i) {
    buffer[8 + i] = transactionID[i];
  }

  return buffer;
}

// void StunHeader::encode(uint8_t *buffer) const {
//   buffer[0] = messageType >> 8;   // High byte of messageType
//   buffer[1] = messageType & 0xFF; // Low byte of messageType

//   buffer[2] = messageLength >> 8;
//   buffer[3] = messageLength & 0xFF;

//   buffer[4] = magicCookie >> 24;
//   buffer[5] = magicCookie >> 16;
//   buffer[6] = magicCookie >> 8;
//   buffer[7] = magicCookie & 0xFF;

//   for (size_t i = 0; i < 12; ++i) {
//     buffer[8 + i] = transactionID[i];
//   }
// }

// StunHeader StunHeader::decode(const uint8_t *buffer) {
//   StunHeader header;

//   header.messageType = (buffer[0] << 8) | buffer[1];
//   header.messageLength = (buffer[2] << 8) | buffer[3];
//   header.magicCookie =
//       (buffer[4] << 24) | (buffer[5] << 16) | (buffer[6] << 8) | buffer[7];

//   for (size_t i = 0; i < 12; ++i) {
//     header.transactionID[i] = buffer[8 + i];
//   }

//   return header;
// }

} // namespace stun
