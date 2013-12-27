const int triggerLEDPin = 9;
const int triggerRelayPin1 = 10;
//const int triggerRelayPin2 = 11;

int incomingByte = 0;   // for incoming serial data

void setup() {
  Serial.begin(9600);
  pinMode(triggerLEDPin, OUTPUT);
  pinMode(triggerRelayPin1, OUTPUT);
  //pinMode(triggerRelayPin2, OUTPUT);

  digitalWrite(triggerLEDPin, LOW);
  digitalWrite(triggerRelayPin1, HIGH);
  //digitalWrite(triggerRelayPin2, HIGH);

  Serial.println("Ready.");
}

void loop() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    Serial.print("Received byte: ");
    Serial.print(incomingByte, DEC);
    Serial.println(" -- Opening door.");
    digitalWrite(triggerLEDPin, HIGH);
    digitalWrite(triggerRelayPin1, LOW);
    //digitalWrite(triggerRelayPin2, LOW);

    delay(300);
    digitalWrite(triggerLEDPin, LOW);
    digitalWrite(triggerRelayPin1, HIGH);
    //digitalWrite(triggerRelayPin2, HIGH);

    Serial.println("Complete.");
  }
}

/* Ruby code for client:
require "serialport"

port_str = "/dev/tty.usbmodemfd121"  # may be different
baud_rate = 9600
data_bits = 8
stop_bits = 1
parity = SerialPort::NONE

sp = SerialPort.new(port_str, baud_rate, data_bits, stop_bits, parity)
sp.read_timeout=10
puts sp.readlines.join()
sp.write("\n")
puts sp.readlines.join()
sp.close
*/


