## Install the required application using the following commands

`sudo apt-get update`

`sudo apt-get install ppp`

## Now we want to configure the ppp interface to communicate with our GSM modem. This can be done using the following instructions

`cd /etc/ppp/peers/ `

`sudo nano rnet`

Then include the following contents to the rnet file

```
###  File Begin  ###
#imis/internet is the apn for idea connection
connect "/usr/sbin/chat -v -f /etc/chatscripts/gprs -T imis/internet"

# For Raspberry Pi3 use /dev/ttyS0 as the communication port:
/dev/ttyUSB0

# Baudrate
115200

# Assumes that your IP address is allocated dynamically by the ISP.
noipdefault

# Try to get the name server addresses from the ISP.
usepeerdns

# Use this connection as the default route to the internet.
defaultroute

# Makes PPPD "dial again" when the connection is lost.
persist

# Do not ask the remote to authenticate.
noauth

# No hardware flow control on the serial link with GSM Modem
nocrtscts

# No modem control lines with GSM Modem
local
###  File End  ###
```

> Special note: Here we assume that the modem can be communicated using ttyUSB0 interface and baudrate 115200. Please ensure this beforehand and then try the instructions in the blog post. 

Edit the following file if the SIM is protected by a PIN

`nano /etc/chatscripts/gprs`

Finally type the following command to activate the new interface

`sudo pon rnet` 

> At this point you will be noticing a fast blink rate of network led in our GSM module which represents the GPRS activity.

We can also deactivate the PPP interface if required using the following command

`sudo poff rnet`

 