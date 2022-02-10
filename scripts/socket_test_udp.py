import random
from socket import *
import struct
import select
import time

# Create a UDP socket
# Notice the use of SOCK_DGRAM for UDP packets
serverSocket = socket(AF_INET, SOCK_DGRAM)

# Assign IP address and port number to socket
serverSocket.bind(("", 12007))

while True:
    try:
        # Receive the client packet along with the address it is coming from
        available_sockets = select.select([serverSocket], [], [], 0)[0]
        if len(available_sockets) > 0:
            message, address = serverSocket.recvfrom(1024)

            if len(message) > 0:
                print(message)
                message = struct.unpack("<" + "i" * 6, message)
                print(message)
        serverSocket.sendto(struct.pack("<" + "i", 12), ("127.0.0.1", 5150))
        time.sleep(0.1)

    except KeyboardInterrupt:
        break
