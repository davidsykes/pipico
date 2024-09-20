try:
 import usocket as socket        #importing socket
except:
 import socket
import network            #importing network
import gc
gc.collect()
ssid = 'RPI_PICO_AP'                  #Set access point name 
password = '12345678'      #Set your access point password


ap = network.WLAN(network.AP_IF)
ap.config(essid=ssid, password=password)
ap.active(True)            #activating

while ap.active() == False:
  pass
print('Connection is successful')
print(ap.ifconfig())
def web_page():
#  html = """<html><head><meta name="viewport" content="width=device-width, initial-scale=1"></head>
#  <body><h1>Welcome to microcontrollerslab!</h1></body></html>"""
  html = 'HTTP/1.0 200 OK\r\nContent-type: text/html\r\n\r\n'
  html = html + '<h1>Push My Button</h1><p><a href="/sequence/Sequence%202">Sequence 2</a></p><p><a href="/sequence/Sequence%201">Sequence 1</a></p>'
  return html
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)   #creating socket object
s.bind(('', 80))
s.listen(5)
while True:
  conn, addr = s.accept()
  print('Got a connection from %s' % str(addr))
  request = conn.recv(1024)
  print('Content = %s' % str(request))
  response = web_page()
  print('response=', response)
  conn.send(response)
  conn.close()