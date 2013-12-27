#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(10,10,0,111);

// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(80);

//const int triggerLEDPin = 5;
const int triggerLEDPin = 13;
const int triggerRelayPin1 = 6;
//const int triggerRelayPin2 = 7;

String HTTP_req;          // stores the HTTP request

void setup() {
  //Serial.begin(9600); // DEBUG
   // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  //Serial.print("server is at "); // DEBUG
  //Serial.println(Ethernet.localIP()); // DEBUG
  
  pinMode(triggerLEDPin, OUTPUT);
  pinMode(triggerRelayPin1, OUTPUT);
  //pinMode(triggerRelayPin2, OUTPUT);

  //digitalWrite(triggerLEDPin, LOW);
  digitalWrite(triggerRelayPin1, HIGH);
  //digitalWrite(triggerRelayPin2, HIGH);

  //Serial.println("Ready."); // DEBUG
}

void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
    if (client) {  // got client?
      boolean currentLineIsBlank = true;
      while (client.connected()) {
        if (client.available()) { // client data available to read
          char c = client.read(); // read 1 byte (character) from client
          // Don't let HTTP_req get too big and use up all RAM
          if (HTTP_req.length() < 22) { // GET /button HTTP/1.1\r\n
              HTTP_req += c;  // save the HTTP request 1 char at a time
          }
          // last line of client request is blank and ends with \n
          // respond to client only after last line received
        
          if (c == '\n' && currentLineIsBlank) {
            // send a standard http response header
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");  // the connection will be closed after completion of the response
            client.println();
            
            if (HTTP_req.indexOf("/button") > -1) {  // see if /button was sent
              client.println("Button Pressed");     
              //Serial.print("Button Pressed... ");  // DEBUG
              digitalWrite(triggerLEDPin, HIGH);
              digitalWrite(triggerRelayPin1, LOW);
              //digitalWrite(triggerRelayPin2, LOW);
              delay(100);
              digitalWrite(triggerLEDPin, LOW);
              digitalWrite(triggerRelayPin1, HIGH);
              //digitalWrite(triggerRelayPin2, HIGH);  
              //Serial.println("Complete"); // DEBUG
            }
          
            //Serial.print(HTTP_req); // DEBUG
            HTTP_req = "";    // finished with request, empty string
            break;
          }
          if (c == '\n') {
            // you're starting a new line
            currentLineIsBlank = true;
          } 
          else if (c != '\r') {
            // you've gotten a character on the current line
            currentLineIsBlank = false;
          }
        }
      }
      
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    //Serial.println("Client disonnected"); // DEBUG
  }
}
