from time import sleep
import serial
from thingspeaker import dataUpdater

serialOutputString = ""
Glucose = 0

nanoSerial = serial.Serial("/dev/ttyUSB0",9600)
myupdater = dataUpdater

# nanoSerial.baudrate = 9600;
# nanoSerial.port = "/dev/ttyUSB0"

# nanoSerial.open()

def sendtoDatabase (bloodGlucose):
    # placeholder
    pass

def sendToThingspeak(bloodGlucose):
    # make sure you have a pair of data greater than 0
    if (bloodGlucose == 0):
        print ("no data.")
    else:
        myupdater.sendData(bloodGlucose)
    
    sleep(5)

while (1):
    serialOutput = nanoSerial.readline()
    
    try:
        serialOutputString = serialOutput.decode()
    except UnicodeDecodeError as e:
        print("Unicode Decode Error:\n " + str(e))
    
    # print  (serialOutputString)

    if (serialOutputString.__contains__("Glucose")):
        inputVal = serialOutputString.split("-->")
        Glucose = inputVal[len(inputVal)-1]
        Glucose = Glucose.strip()
        Glucose = Glucose.strip('\r')
        Glucose = Glucose.strip('\r')
        Glucose = Glucose.strip('\n')
        print("Glucose = " + Glucose)
        sendToThingspeak(Glucose)


    # let's breathe, although we'll need to breathe after every 2 lines:
    # time.sleep(5)
    

nanoSerial.close()