import socket

HOST = 'localhost'    # The remote host
PORT = 5051              # The same port as used by the server

data = b"GET /codes HTTP/1.1\r\nHost: bla.com\r\nAccept: */*\r\n\r\n"

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as cs:
    cs.connect((HOST, PORT))
    cs.sendall(data)
    print('data sent')
    data = cs.recv(1024)
    print('data', data)
