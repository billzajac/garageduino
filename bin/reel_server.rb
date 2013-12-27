#!/usr/bin/env ruby

require 'reel'
require 'serialport'

arduino_port = "/dev/ttyACM0" # garage windows 7 - ubuntu
baud_rate = 9600
data_bits = 8
stop_bits = 1
parity = SerialPort::NONE
server_ip = "0.0.0.0"
server_port = 8080


now = Time.now.strftime("%Y%m%d_%H%M%S")
puts "#{now} Correcting permissions on #{arduino_port}"
system("sudo chmod 777 #{arduino_port}")
puts "#{now} Starting server on: #{server_ip}:#{server_port}"

Reel::Server.supervise(server_ip, server_port) do |connection|
  while request = connection.request
    puts "#{now} Client requested: #{request.method} #{request.url}"
    now = Time.now.strftime("%Y%m%d_%H%M%S")

    if request.url == "/button"
      request.respond :ok, "Button Pressed"
      puts "#{now} Pressing the button"
      sp = SerialPort.new(arduino_port, baud_rate, data_bits, stop_bits, parity)
      sleep 0.5
      sp.read_timeout=200
      puts sp.readlines.join()
      sp.write("\n")
      sleep 1.5
      puts sp.readlines.join()
      sp.close
    else
      puts "#{now} 404 Not Found: #{request.path}"
      connection.respond :not_found, "Not found"
    end
  end
end

sleep
