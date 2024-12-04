#include <boost/asio.hpp>
#include <iostream>
#include <random>
#include <stunHeader.h>
#include <udpServer.h>

stun::StunHeader createBindingRequest() {
  stun::StunHeader msg;
  msg.messageType = 0x0001;     // Binding Request
  msg.messageLength = 0;        // For now, no attributes
  msg.magicCookie = 0x2112A442; // STUN Magic Cookie
  // Generate a random transaction ID (96 bits)
  std::random_device rd;
  std::uniform_int_distribution<uint8_t> dist(0, 255);
  for (int i = 0; i < 12; i++) {
    msg.transactionID[i] = dist(rd);
  }
  return msg;
}

int connect() {
  boost::asio::io_service io_service;
  boost::asio::ip::udp::socket socket(io_service);
  socket.open(boost::asio::ip::udp::v4());

  try {
    boost::asio::ip::udp::endpoint endpoint(
        boost::asio::ip::address::from_string("74.125.250.129"),
        3478); // Public STUN server

    std::vector<uint8_t> buffer = createBindingRequest().Serialize();

    socket.send_to(boost::asio::buffer(buffer, buffer.size()), endpoint);
  } catch (const boost::system::system_error &e) {
    std::cerr << "Error sending message: " << e.what() << std::endl;
    return -1;
  }

  return 1;
}

int main(int argc, char *argv[]) {
  try {
    io_service io_service;

    UdpServer server(io_service, 3478);

    io_service.run();
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  return 0;
}
