import sys
from time import sleep
from urllib.request import urlopen

API_KEY = 'MY_API_KEY'

class dataUpdater():
    #temperature = 0
    #PID = 0

    def setData(glucose,flow):
        bloodGlucose = glucose
    
    def sendData(glucose):
        baseURL = 'https://api.thingspeak.com/update?api_key={}}&field1={}'
        
        newRequest = baseURL.format(API_KEY,glucose)
        print (newRequest)

        f = urlopen(newRequest)
        f.read()
        f.close()
        # sleep(5)
        print ("Data Sent Successfully")
