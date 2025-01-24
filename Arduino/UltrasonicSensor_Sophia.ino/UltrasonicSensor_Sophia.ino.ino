#include <NewPing.h>
#define trigPin 12 // define TrigPin
#define echoPin 11 // define EchoPin.
#define MAX_DISTANCE 200 // Maximum sensor distance is rated at 400-500cm.
NewPing sonar(trigPin, echoPin, MAX_DISTANCE); // NewPing setup of pins and maximumdistance.
void setup() {
Serial.begin(9600); // Open serial monitor at 9600 bauds to see ping results.
}
void loop() {
delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortestdelay between pings.
Serial.print("Ping: ");
Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 =outside set distance range)
Serial.println("cm");

if(sonar.ping_cm() < 20){
  Serial.println("Too close!");
  delay(1000);
}
}