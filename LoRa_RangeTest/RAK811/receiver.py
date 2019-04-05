import serial
import time
import sys
import datetime
import paho.mqtt.client as mqtt

PORT = '/dev/ttyUSB0'
baud = 115200

mqttc = mqtt.Client()
mqttc.connect("iot.eclipse.org", 1883)
mqttc.loop_start()

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


def parseResponse(timeout_in_seconds=10):
    lora_serial.flushInput()
    lora_serial.flushOutput()
    seconds_elapsed = 0
    while seconds_elapsed < timeout_in_seconds:
        response = lora_serial.readline().rstrip()  # comment this line if echo off
        if (len(response)) > 0:
            # print(time.time(),"recv:",response)
            data = response.split(",")
            if len(data)  == 6:
                data = "{} Port: {}, RSSI: {}, SNR: {}, LEN: {}, DATA: {}".format(datetime.datetime.now(), data[1],data[2],data[3],data[4],data[5].decode("hex")) 
                print(data)

                file = open("datalog.txt", "a")
                file.write(data+'\n')
                file.close()

                mqttc.publish("Elementz/rangetest/RAK811", data)
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

status = False
while not status:
    status = False
    sendCommand("at+rx_stop")
    status = getResponse("OK",2)

status = False
while not status:
    status = False
    sendCommand("at+mode=1")
    status = getResponse("OK",2)

status = False
while not status:
    status = False
    sendCommand("at+rf_config=865700000,12,0,4,8,20")
    status = getResponse("OK",2)

status = False
while not status:
    status = False
    sendCommand("at+rxc=1")
    status = getResponse("OK",2)


status = False
while not status:
    status = parseResponse(120)
