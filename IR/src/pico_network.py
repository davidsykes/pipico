import time
import network
import urequests as requests

class PicoNetwork:
    def initialise(self):
        ssid = 'ssid'
        password = 'password'

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
            print ("About to get", url)
            response = requests.get(url)
            print('got response')
            print('get response', response.json())
            #response.close()

            return response.json()
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



    def initialise_original(self):
        ssid = 'ssid'
        password = 'password'

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