#include <boost/asio.hpp>
#include <cstdint>
#include <vector>

using boost::asio::ip::udp;

// void send_binding_response(uint64_t transaction_id,
//                            udp::endpoint &remote_endpoint, udp::socket
//                            &socket);

void handle_stun_request(const std::vector<uint8_t> &buffer,
                         udp::socket &socket, udp::endpoint &remote_endpoint);
