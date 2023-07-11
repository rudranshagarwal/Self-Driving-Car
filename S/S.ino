//#include <NewPing.h>
#include <Servo.h> 
#include <MotorDriver.h>
//#include <WiFiNINA.h>
//#include <SPI.h>
//#include <AESLib.h>
//#include <ArduinoHttpClient.h>

MotorDriver m;
bool on = false;
#define triggerpin A4 
#define echopin A5 
#define MAX_DISTANCE 200 
#define MAX_SPEED 400 // sets speed of DC  ms
#define MAX_SPEED_OFFSET 20
#define ROUNDTRIP_CM 57      // Microseconds (uS) it takes sound to travel round-trip 1cm (2cm total), uses integer to save compiled code space.

//NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

Servo myservo;   

boolean goesForward=false;
int distance = 100;
int speedSet = 0;
float angle = 0;
float x = 0;
float y = 0;
float pi = 3.14;

//char ssid[] = "";             //  your network SSID (name) between the " "
//char pass[] = "";      // your network password between the " "
//int keyIndex = 0;                 // your network key Index number (needed only for WEP)
//int status = WL_IDLE_STATUS;      //connection status
//WiFiServer server(80);            //server socket
////IPAddress cse_ip(192,168,43,75);
//char cse_ip[] = "192.168.43.75";
//int cse_port = 8080;
//WiFiClient wifi;
//String cse_server = "http://"+String(cse_ip)+":"+String(cse_port)+"/~/in-cse/in-name/";
//HttpClient Hclient = HttpClient(wifi, cse_ip, cse_port);
//WiFiClient client = server.available();

//int ledPin = 2;

static const int servoPin = 2;

void setup() {
  Serial.begin(9600);
//  pinMode(ledPin, OUTPUT);
//  while (!Serial);
//  
//  enable_WiFi();
//  connect_WiFi();

//  server.begin();
//  printWifiStatus();
  
  myservo.attach(2);  
  myservo.write(130); 
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() {
// client = server.available();
// if (client) {
//  // if you get a client,
//  on = !on;
//    Serial.println("new client");           // print a message out the serial port
//    String currentLine = "";                // make a String to hold incoming data from the client
//    while (client.connected()) {            // loop while the client's connected
//      if (client.available()) {             // if there's bytes to read from the client,
//        char c = client.read();             // read a byte, then
//        Serial.write(c);                    // print it out the serial monitor
//        if (c == '\n') {                    // if the byte is a newline character
//
//          // if the current line is blank, you got two newline characters in a row.
//          // that's the end of the client HTTP request, so send a response:
//          if (currentLine.length() == 0) {
//
//            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
//            // and a content-type so the client knows what's coming, then a blank line:
//            client.println("HTTP/1.1 200 OK");
//            client.println("Content-type:text/html");
//            client.println();
//           
//            //create the buttons
//            client.print("Click <a href=\"/H\">here</a> turn the LED on<br>");
//            client.print("Click <a href=\"/L\">here</a> turn the LED off<br><br>");
//            
//            int randomReading = analogRead(A1);
//            client.print("Random reading from analog pin: ");
//            client.print(randomReading);
//
//            // The HTTP response ends with another blank line:
//            client.println();
//            // break out of the while loop:
//            break;
//          }
//          else {      // if you got a newline, then clear currentLine:
//            currentLine = "";
//          }
//        }
//        else if (c != '\r') {    // if you got anything else but a carriage return character,
//          currentLine += c;      // add it to the end of the currentLine
//        }
//      }
//      }
//
//      client.stop();
// }
//
on = true;
  if(on == true){
 int distanceR = 0;
 int distanceL =  0;
 delay(40);
 
 if(distance<=25 )
 {
  moveStop();
  delay(100);
  moveBackward();
  delay(300);
  moveStop();
  delay(200);
//  unsigned long t = millis();
//  String val = String(x) + " " + String(y) + " " + String(t); 
//  createCI(val);
  distanceR = lookRight();
  delay(200);
  distanceL = lookLeft();
  delay(200);

  if(distanceR>=distanceL)
  {
    turnRight();
    moveStop();
  }else
  {
    turnLeft();
    moveStop();
  }
 }else
 {
  moveForward();
 }
 distance = readPing();
}
}

int lookRight()
{
    myservo.write(80); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(130); 
    return distance;
}

int lookLeft()
{
    myservo.write(180); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(130); 
    return distance;
    delay(100);
}

int readPing() { 
digitalWrite(triggerpin, LOW);
delayMicroseconds(2);
digitalWrite(triggerpin, HIGH);
delayMicroseconds(15);
digitalWrite(triggerpin, LOW);
int distance;
int duration;
duration = pulseIn(echopin, HIGH);
distance= duration*0.034/2;
Serial.print("Distance: ");
Serial.println(distance);
return distance;
}

void moveStop() {
  m.motor(1, FORWARD,0);    
  m.motor(2, FORWARD,0);
  m.motor(3, FORWARD,0); 
  m.motor(4, FORWARD,0); 
  } 
  
void moveForward() {

 if(!goesForward)
  {
    goesForward=true;
    m.motor(1, FORWARD,speedSet);    
    m.motor(2, FORWARD,speedSet);
    m.motor(3, FORWARD,speedSet); 
    m.motor(4, FORWARD,speedSet);   
    x = x + speedSet*cos(angle*pi/180);
    y = y + speedSet*sin(angle*pi/180);
    
   for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
   {
    m.motor(1, FORWARD,speedSet);    
    m.motor(2, FORWARD,speedSet);
    m.motor(3, FORWARD,speedSet); 
    m.motor(4, FORWARD,speedSet); 
    x = x + speedSet*cos(angle*pi/180);
    y = y + speedSet*sin(angle*pi/180);
    delay(5);
   }
   
  }
}

void moveBackward() {
    goesForward=false;
    m.motor(1, BACKWARD,speedSet);    
    m.motor(2, BACKWARD,speedSet);
    m.motor(3, BACKWARD,speedSet); 
    m.motor(4, BACKWARD,speedSet);
    x = x - speedSet*cos(angle*pi/180);
    y = y - speedSet*sin(angle*pi/180);
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    m.motor(1, BACKWARD,speedSet);    
    m.motor(2, BACKWARD,speedSet);
    m.motor(3, BACKWARD,speedSet); 
    m.motor(4, BACKWARD,speedSet);
    x = x - speedSet*cos(angle*pi/180);
    y = y - speedSet*sin(angle*pi/180);
    delay(5);
  }
}  

void turnRight() {
  m.motor(1,FORWARD, speedSet);    
  m.motor(2,FORWARD, speedSet);
  m.motor(3,BACKWARD, speedSet); 
  m.motor(4,BACKWARD, speedSet);
  angle -= 15;
  delay(500);
  m.motor(1,FORWARD, speedSet);    
  m.motor(2,FORWARD, speedSet);
  m.motor(3,FORWARD, speedSet); 
  m.motor(4,FORWARD, speedSet);
  x = x + speedSet*cos(angle*pi/180);
  y = y + speedSet*sin(angle*pi/180);     
} 
 
void turnLeft() {
  m.motor(1, BACKWARD, speedSet);    
  m.motor(2, BACKWARD, speedSet);
  m.motor(3, FORWARD,speedSet); 
  m.motor(4, FORWARD, speedSet);
  angle += 15;
  delay(500);
  m.motor(1, FORWARD,speedSet);    
  m.motor(2, FORWARD,speedSet);
  m.motor(3, FORWARD,speedSet); 
  m.motor(4, FORWARD,speedSet); 
  x = x + speedSet*cos(angle*pi/180);
  y = y + speedSet*sin(angle*pi/180);
}

//void createCI(String val){
//  uint8_t key[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};
//  int i;
//  char data[] = "0123456789012345";
//  for(i=0;i<val.length();i++){
//    data[i]=val[i];
//  }
//  while(i<16){
//    data[i]="A";
//    i++;
//  }
//  aes256_enc_single(key, data);
//  String body = "{\"m2m:cin\": {\"lbl\": [ \"Team-13\" ],\"con\": \"" + String(val)+ "\"}}";
//  Hclient.beginRequest();
//  Hclient.post("/~/in-cse/in-name/Team-13/Node-1/Data/");
//  Hclient.sendHeader("Content-Length", body.length());
//  Hclient.sendHeader("X-M2M-Origin", "admin:admin");
//  Hclient.sendHeader("Content-Type", "application/json;ty=4");
//  Hclient.sendHeader("Connection", "keep-alive");
//  Hclient.beginBody();
////  String body = "m2m:cin: {lbl: [ \"Team-13\" ],con: \"" + String(val)+ "\"}";
//  Serial.println(body);
//  Hclient.print(body);
//  Hclient.endRequest();
//  int status = Hclient.responseStatusCode();
//  String responseBody = Hclient.responseBody();
//  Serial.println(status);
//  Serial.println(responseBody);
//  delay(1000); 
//}
//
//void printWifiStatus() {
//  // print the SSID of the network you're attached to:
//  Serial.print("SSID: ");
//  Serial.println(WiFi.SSID());
//
//  // print your board's IP address:
//  IPAddress ip = WiFi.localIP();
//  Serial.print("IP Address: ");
//  Serial.println(ip);
//
//  // print the received signal strength:
//  long rssi = WiFi.RSSI();
//  Serial.print("signal strength (RSSI):");
//  Serial.print(rssi);
//  Serial.println(" dBm");
//
//  Serial.print("To see this page in action, open a browser to http://");
//  Serial.println(ip);
//}
//
//void enable_WiFi() {
//  // check for the WiFi module:
//  if (WiFi.status() == WL_NO_MODULE) {
//    Serial.println("Communication with WiFi module failed!");
//    // don't continue
//    while (true);
//  }
//
//  String fv = WiFi.firmwareVersion();
//  if (fv < "1.0.0") {
//    Serial.println("Please upgrade the firmware");
//  }
//}
//
//void connect_WiFi() {
//  // attempt to connect to Wifi network:
//  while (status != WL_CONNECTED) {
//    Serial.print("Attempting to connect to SSID: ");
//    Serial.println(ssid);
//    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
//    status = WiFi.begin(ssid, pass);
//
//    // wait 10 seconds for connection:
//    delay(10000);
//  }
//}
//
//void printWEB() {
//
//  if (client) {                             // if you get a client,
//    Serial.println("new client");           // print a message out the serial port
//    String currentLine = "";                // make a String to hold incoming data from the client
//    while (client.connected()) {            // loop while the client's connected
//      if (client.available()) {             // if there's bytes to read from the client,
//        char c = client.read();             // read a byte, then
//        Serial.write(c);                    // print it out the serial monitor
//        if (c == '\n') {                    // if the byte is a newline character
//
//          // if the current line is blank, you got two newline characters in a row.
//          // that's the end of the client HTTP request, so send a response:
//          if (currentLine.length() == 0) {
//
//            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
//            // and a content-type so the client knows what's coming, then a blank line:
//            client.println("HTTP/1.1 200 OK");
//            client.println("Content-type:text/html");
//            client.println();
//           
//            //create the buttons
//            client.print("Click <a href=\"/H\">here</a> turn the LED on<br>");
//            client.print("Click <a href=\"/L\">here</a> turn the LED off<br><br>");
//            
//            int randomReading = analogRead(A1);
//            client.print("Random reading from analog pin: ");
//            client.print(randomReading);
//            
//
//            // The HTTP response ends with another blank line:
//            client.println();
//            // break out of the while loop:
//            break;
//          }
//          else {      // if you got a newline, then clear currentLine:
//            currentLine = "";
//          }
//        }
//        else if (c != '\r') {    // if you got anything else but a carriage return character,
//          currentLine += c;      // add it to the end of the currentLine
//        }
//
//        if (currentLine.endsWith("GET /H")) {
//        digitalWrite(ledPin, HIGH);        
//        }
//        if (currentLine.endsWith("GET /L")) {
//        digitalWrite(ledPin, LOW);       
//        }
//
//      }
//    }
//    // close the connection:
//    client.stop();
//    Serial.println("client disconnected");
//  }
//}
