import socket

SERVER_HOST = ''                 # Symbolic name meaning all available interfaces
SERVER_PORT = 5052              # Arbitrary non-privileged port
CLIENT_HOST = 'localhost'    # The remote host
CLIENT_PORT = 5051              # The same port as used by the server

while True:
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as ss:
        ss.bind((SERVER_HOST, SERVER_PORT))
        ss.listen(1)
        conn, addr = ss.accept()
        with conn:
            print('Connected by', addr)
            data = conn.recv(100024)
            print('data', data)
            #if not data: break
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as cs:
                cs.connect((CLIENT_HOST, CLIENT_PORT))
                cs.sendall(data)
                print('data sent')
                data = cs.recv(100024000)
                #print('data', data)
                conn.sendall(data)
                print('data sent back')