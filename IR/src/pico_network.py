import network
import urequests as requests
import json
import socket
import time
from localsettings import LocalSettings
from ir_exception import IrException

class PicoNetwork:
    def __init__(self):
        self.connected = None
        self.ip_address = 'not connected'
        ssid = LocalSettings.SSID
        password = LocalSettings.Password

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
            self.connected = False
        else:
            status = wlan.ifconfig()
            print('The internet is connected. ip = ' + status[0] )
            self.connected = True
            self.ip_address = status[0]

    def get(self, url):
        response = requests.get(url)
        status_code = response.status_code
        text = response.text
        response.close()
        if status_code == 200:
            return text
        raise IrException(''.join(['Error ', str(status_code), ' accessing url ', url]))

    def put(self, url, headers, data):
        jsonObj = json.dumps(data)
        try:
            response = requests.put(url, data=jsonObj, headers=headers)
        except:
            response = requests.put(url, data=jsonObj, headers=headers)
        status_code = response.status_code
        response.close()
        if (status_code != 200):
            print('put response', status_code)
        return status_code

    def open_socket(self):
        addr = socket.getaddrinfo('0.0.0.0', 80)[0][-1]
        s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        s.bind(addr)
        s.listen(1)
        return s

    def accept(self, s):
        return s.accept()

    def recv(self, cl):
        request = cl.recv(1024)
        request_string = ''.join([chr(int(x)) for x in request])
        return request_string
