import socket
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind(("0.0.0.0", 3333))
for _ in range(20):  # receive 20 packets then stop
    data, addr = s.recvfrom(1024)
    print(f"From {addr}: {data.decode()}")