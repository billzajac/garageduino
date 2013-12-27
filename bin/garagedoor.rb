#!/usr/bin/env ruby
require "serialport"

# params for serial port
#port_str = "/dev/ttyUSB0"  #may be different for you
#port_str = "/dev/tty.usbmodemfd121"  #may be different for you
#port_str = "/dev/ttyS9" # garage windows 7
#------------------------------------------------------------
# Install arduino software and drivers on Windows 7
# Install an ubuntu virtualbox
# In the virtualbox settings: USB -> USB device filters -> Add filter from device-> Arduino
# The following will allow you to start virtualbox as a service
#   http://sourceforge.net/projects/vboxvmservice/files/
# C:\vms\VBoxVMmService.ini
#   [Settings]
#   ServiceName=VBoxVmService
#   VBOX_USER_HOME=C:\Users\billz\.VirtualBox
#   PauseShutdown=5000
#
#   [Vm0]
#   VmName=vpn.phelpsmanagement.com
#   WorkingDir=C:\vms
#   ShutdownMethod=savestate
#   AutoStart=yes
#
#   [Vm1]
#   VmName=sandbox01.consultla.com
#   WorkingDir=C:\vms
#   ShutdownMethod=savestate
#   AutoStart=yes
#
#   [Vm2]
#   VmName=ubuntu01
#   WorkingDir=C:\vms
#   ShutdownMethod=savestate
#   AutoStart=yes
#
# How to prep the VM
#   sudo apt-get update && apt-get -y upgrade
#   sudo apt-get install ruby1.9.1 ruby1.9.1-dev build-essential
#   sudo gem install serialport
# Add public key to ~/.ssh/authorized_keys
#   chmod 700 ~/.ssh
#
# Find the arduino device file descriptor path
#   ls -ltr /dev
#   sudo chmod o+rw /dev/ttyACM0
#
# Also, can interact with screen:
#   screen /dev/ttyACM0 9600
#------------------------------------------------------------
port_str = "/dev/ttyACM0" # garage windows 7 - ubuntu
system("sudo chmod 777 #{port_str}")
baud_rate = 9600
data_bits = 8
stop_bits = 1
parity = SerialPort::NONE

sp = SerialPort.new(port_str, baud_rate, data_bits, stop_bits, parity)
sleep 1
sp.read_timeout=10
puts sp.readlines.join()
sp.write("\n")
sleep 1.5
puts sp.readlines.join()
sp.close

#
##sp.gets
##sp.read
#sp.write("1\r\n")
#sp.gets
#sp.gets
#sp.close
