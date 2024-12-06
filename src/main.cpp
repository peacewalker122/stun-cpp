#include <boost/asio.hpp>
#include <iostream>
#include <stunHeader.h>
#include <udpServer.h>

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
