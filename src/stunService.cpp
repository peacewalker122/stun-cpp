#include <boost/asio.hpp>
#include <cstdint>
#include <iostream>

using boost::asio::ip::udp;

void send_binding_response(uint64_t transaction_id,
                           udp::endpoint &remote_endpoint,
                           udp::socket &socket) {
  std::vector<uint8_t> response(
      20); // Minimum response size (Message Type, Length, Transaction ID)

  // Set Message Type (Binding Response)
  response[0] = 0x01;
  response[1] = 0x01;

  // Set Transaction ID
  for (size_t i = 0; i < 12; ++i) {
    response[2 + i] = (transaction_id >> (8 * (11 - i))) & 0xFF;
  }

  // Add the public IP address and port (use the server's IP and port for now)
  uint32_t ip =
      boost::asio::ip::address_v4::from_string("127.0.0.1").to_ulong();
  uint16_t port = 3478; // Local port used by the STUN server

  response.push_back(0x00); // Padding
  response.push_back(0x01); // Mapped Address (IPv4)
  response.push_back(0x00); // Reserved
  response.push_back(0x01); // Address Family (IPv4)
  response.push_back((ip >> 24) & 0xFF);
  response.push_back((ip >> 16) & 0xFF);
  response.push_back((ip >> 8) & 0xFF);
  response.push_back(ip & 0xFF);
  response.push_back((port >> 8) & 0xFF);
  response.push_back(port & 0xFF);

  // Send the response back to the client
  socket.async_send_to(boost::asio::buffer(response), remote_endpoint,
                       [](const std::error_code &ec, std::size_t bytes_sent) {
                         if (ec) {
                           std::cerr
                               << "Error sending response: " << ec.message()
                               << std::endl;
                         }
                       });
}

void handle_stun_request(const std::vector<uint8_t> &buffer,
                         udp::socket &socket, udp::endpoint &remote_endpoint) {
  uint16_t message_type = (buffer[0] << 8) | buffer[1];

  if (message_type == 0x0001) {
    std::cout << "Received STUN Binding Request" << std::endl;

    uint64_t transaction_id = 0;

    for (int i = 0; i < 12; i++) {
      transaction_id = (transaction_id << 8) | buffer[2 + i];
    }

    send_binding_response(transaction_id, remote_endpoint, socket);
  }
}
