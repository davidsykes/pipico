import time
import network
import urequests as requests
from secretsausage import SecretSausage
import json
import socket

class PicoNetwork:
    def initialise(self):
        ssid = SecretSausage.SSID
        password = SecretSausage.Password

        wlan = network.WLAN(network.STA_IF)
        wlan.active(True)
        wlan.connect(ssid, password)

        # Wait for connect or fail
        max_wait = 10
        while max_wait > 0:
            if wlan.status() < 0 or wlan.status() >= 3:
                break
            max_wait -= 1
            print('waiting for connection...')
            time.sleep(1)

        # Handle connection error
        if wlan.status() != 3:
            print('network connection failed')
            return False
        else:
            print('The internet is connected')
            status = wlan.ifconfig()
            print( 'ip = ' + status[0] )
            return True

    def get(self, url):
        try:
            response = requests.get(url)
            #print(response.status_code)
            return response.text
        except:
            print('Get url failed:', url)
            #print("could not connect (status =" + str(wlan.status()) + ")")
            #if wlan.status() < 0 or wlan.status() >= 3:
            #    print("trying to reconnect...")
            #    wlan.disconnect()
            #    wlan.connect(ssid, password)
            #if wlan.status() == 3:
            #    print('connected')
            #else:
            #    print('failed')

    def put(self, url, headers, data):
        jsonObj = json.dumps(data)
        try:
            response = requests.put(url, data=jsonObj, headers=headers)
        except:
            response = requests.put(url, data=jsonObj, headers=headers)
        status_code = response.status_code
        response.close()
        print('put response', status_code)
        return status_code

    def listen(self):
        html = """<!DOCTYPE html>
            <html>
                <head> <title>Hello Oliver</title> </head>
                <body> <h1>Hello Oliver</h1>
                    <p>Hello from Pico!</p>
                </body>
            </html>
        """
        # Open socket
        addr = socket.getaddrinfo('0.0.0.0', 80)[0][-1]
        s = socket.socket()
        s.bind(addr)
        s.listen(1)
        
        print('listening on', addr)
        
        # Listen for connections
        while True:
            try:
                cl, addr = s.accept()
                print('client connected from', addr)

                request = cl.recv(1024)
                print(request)
                print()
                print(''.join([chr(int(x,2)) for x in request]))
                print()

                request = str(request)
                response = html
                
                cl.send('HTTP/1.0 200 OK\r\nContent-type: text/html\r\n\r\n')
                cl.send(response)
                cl.close()
        
            except OSError as e:
                cl.close()
                print('connection closed')