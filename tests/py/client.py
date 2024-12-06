from scapy.all import *
from scapy.layers.inet import UDP, IP

# Define STUN message types
BINDING_REQUEST = 0x0001
MAGIC_COOKIE = 0x2112A442


class STUNMessage(Packet):
    name = "STUNMessage"
    fields_desc = [
        XShortField("msg_type", BINDING_REQUEST),
        XShortField("msg_length", 0),  # Will be updated later
        IntField("magic_cookie", MAGIC_COOKIE),
        # Transaction ID is 96 bits (12 bytes)
        StrFixedLenField("transaction_id", bytes(ord("b") * 12), length=12),
    ]

    def post_build(self, p, pay):
        msg_length = len(pay)
        p = p[:2] + struct.pack("!H", msg_length) + p[4:]
        return p + pay


# Example Usage
def send_stun_binding_request(stun_server, stun_port=3478):
    # Create a STUN binding request
    stun = STUNMessage()

    # Build the packet
    packet = IP(dst=stun_server) / UDP(sport=RandShort(), dport=stun_port) / stun

    # Send the packet and wait for a response
    response = sr1(packet, timeout=5)

    if response:
        response.show()
    else:
        print("No response received.")


if __name__ == "__main__":
    import sys

    if len(sys.argv) < 2:
        print("Usage: python3 stun_test.py <STUN_SERVER> [PORT]")
        sys.exit(1)
    stun_server = sys.argv[1]
    stun_port = int(sys.argv[2]) if len(sys.argv) > 2 else 3478
    send_stun_binding_request(stun_server, stun_port)
