#include <boost/algorithm/string/case_conv.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <stunService.h>

using boost::asio::io_service;
using boost::asio::ip::udp;
using boost::system::error_code;

class UdpServer {
public:
  UdpServer(io_service &io_service, short port)
      : socket_(io_service, udp::endpoint(udp::v4(), port)) {
    // Start receiving messages from clients
    start_receive();
  }

private:
  void start_receive() {
    // Set up the buffer to store incoming data
    socket_.async_receive_from(
        boost::asio::buffer(recv_buffer_), remote_endpoint_,
        [this](const error_code &ec, std::size_t bytes_received) {
          handle_receive(ec, bytes_received);
        });
  }

  void handle_receive(const error_code &error, std::size_t bytes_received) {
    if (!error) {
      // Process the received message (just print it)
      std::cout << "Received message: "
                << std::string(recv_buffer_.data(), bytes_received)
                << std::endl;

      handle_stun_request(
          std::vector<uint8_t>(recv_buffer_.begin(),
                               recv_buffer_.begin() + bytes_received),
          socket_, remote_endpoint_);

      // Continue to receive more messages
      start_receive();
    } else {
      std::cerr << "Error receiving data: " << error.message() << std::endl;
    }
  }

  udp::socket socket_;
  udp::endpoint remote_endpoint_;
  std::array<char, 1024> recv_buffer_; // Buffer to store incoming data
};
