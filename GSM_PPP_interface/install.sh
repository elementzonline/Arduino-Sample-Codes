#!/bin/sh

echo "====Installing required packages======="
echo ""
echo ""
sudo apt-get update
sudo apt-get install -y  ppp



echo "=====copying configuration script to /etc/ppp/peers/======="
echo "Make sure that the serial port and baudrate are correct"
echo ""
sudo cp -f rnet /etc/ppp/peers/


echo "========================================= "
echo " If SIM pin is set edit the following file using the command "
echo "nano /etc/chatscripts/gprs"
echo " ========================================= "
echo ""
echo ""

echo "=======Finally activating the new interface========"
echo ""
echo ""
sudo pon rnet

echo "=======You can turn off the interface using the following comamnd ========"
echo "sudo poff rnet"