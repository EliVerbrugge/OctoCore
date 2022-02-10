import socket
import struct
import time

UDP_IP = "127.0.0.1"
UDP_PORT = 12000
MESSAGE = "Hello, World!"

print("UDP target IP: %s" % UDP_IP)
print("UDP target port: %s" % UDP_PORT)
print("message: %s" % MESSAGE)

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # Internet  # UDP
while True:
    msg = bytes("Hello/this/topic\\", "utf-8")
    sock.sendto(struct.pack("<" + "i" + f"{len(msg)}s" + "i", 1, msg, 4), (UDP_IP, UDP_PORT))
    time.sleep(0.5)
