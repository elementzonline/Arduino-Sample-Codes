import serial
import time
import sys

PORT = '/dev/ttyUSB2'
baud = 9600

def sendCommand(at_com):
    print(time.time(),"send:",at_com)
    lora_serial.flushInput()
    lora_serial.flushOutput()
    lora_serial.write(at_com + '\r\n')

 
def getResponse(required_response="",timeout_in_seconds=10):
    lora_serial.flushInput()
    lora_serial.flushOutput()
    seconds_elapsed = 0
    while seconds_elapsed < timeout_in_seconds:
        response = lora_serial.readline().rstrip()  # comment this line if echo off
        if (len(response)) > 0:
            print(time.time(),"recv:",response)
            if response == required_response:
                return True
        seconds_elapsed = seconds_elapsed+1
    return False



print("Trying with baudrate {}".format(baud))

lora_serial = serial.Serial()
lora_serial.port = PORT
lora_serial.baudrate = baud
lora_serial.timeout = 1
lora_serial.xonxoff = False
lora_serial.rtscts = False
lora_serial.bytesize = serial.EIGHTBITS
lora_serial.parity = serial.PARITY_NONE
lora_serial.stopbits = serial.STOPBITS_ONE

try:
    lora_serial.open()
    lora_serial.flushInput()
    lora_serial.flushOutput()
except:
    print ('Cannot open serial port')
    sys.exit()

# sendCommand("at+uart=9600,8,0,1,0")
# status = getResponse("OK",2)


# try:
#     lora_serial.close()
# except:
#     print ('Cannot close serial port')
#     sys.exit()

# baud = 9600
# lora_serial = serial.Serial()
# lora_serial.port = PORT
# lora_serial.baudrate = baud
# lora_serial.timeout = 1
# lora_serial.xonxoff = False
# lora_serial.rtscts = False
# lora_serial.bytesize = serial.EIGHTBITS
# lora_serial.parity = serial.PARITY_NONE
# lora_serial.stopbits = serial.STOPBITS_ONE

# try:
#     lora_serial.open()
#     lora_serial.flushInput()
#     lora_serial.flushOutput()
# except:
#     print ('Cannot open serial port')
#     sys.exit()

status = False
while not status:
    status = False
    sendCommand("at+tx_stop")
    status = getResponse("OK",2)

status = False
while not status:
    status = False
    sendCommand("at+mode=1")
    status = getResponse("OK",2)

status = False
while not status:
    status = False
    sendCommand("at+rf_config=865700000,12,0,1,8,20")
    status = getResponse("OK",2)

# status = False
# while not status:
#     status = False
#     sendCommand("at+txc=5,1000,800100000600010002da9557e142d9")
#     status = getResponse("OK",2)

payload = 1
pktCounter = 0
while pktCounter < 100:
    payload_data = "%02X" % payload
    sendCommand("at+txc=1,1000,{}".format(str(payload).encode("hex")))
    status = getResponse("at+recv=9,0,0",5)
    payload = payload + 1

status = False
while not status:
    status = False
    sendCommand("at+tx_stop")
    status = getResponse("OK",2)
