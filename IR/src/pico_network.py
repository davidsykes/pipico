import time
import network
import urequests as requests
from secretsausage import SecretSausage
import json

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
            raise RuntimeError('network connection failed')
        else:
            print('The internet is connected')
            status = wlan.ifconfig()
            print( 'ip = ' + status[0] )

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
        response = requests.put(url, data=jsonObj, headers=headers)
        print('put response', response.status_code)
        return response.status_code

    def initialise_original(self):
        ssid = SecretSausage.SSID
        pwd = SecretSausage.Password

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
            raise RuntimeError('network connection failed')
        else:
            print('The internet is connected')
            status = wlan.ifconfig()
            print( 'ip = ' + status[0] )


        try:
            url = "http://192.168.1.125:5004/weatherforecast"
            print ("About to get", url)
            response = requests.get(url)
            print('got response')
            print('get response', response.json())
            response.close()



            #headers = 'headers'
            #payload = 'payload'
            #print("sending...")
            #response = requests.post("A REMOTE END POINT", headers=headers, data=payload)
            #print("sent (" + str(response.status_code) + "), status = " + str(wlan.status()) )
            #response.close()
        except:
            print("could not connect (status =" + str(wlan.status()) + ")")
            if wlan.status() < 0 or wlan.status() >= 3:
                print("trying to reconnect...")
                wlan.disconnect()
                wlan.connect(ssid, password)
            if wlan.status() == 3:
                print('connected')
            else:
                print('failed')