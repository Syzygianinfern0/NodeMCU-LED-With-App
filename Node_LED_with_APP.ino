#include <ESP8266WiFi.h>

String  i;
WiFiServer server(80);

void setup()
{
  i = "";

Serial.begin(9600);
pinMode(14, OUTPUT);
//  WiFi.disconnect();
//  delay(3000);
   WiFi.begin("PremaBai","pass@4321");
  Serial.println("Connecting to Wi-Fi");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print(".");

  }
  Serial.println("WiFi now connected");
  Serial.println((WiFi.localIP().toString()));
  server.begin();

}


void loop()
{

    WiFiClient client = server.available();
    if (!client) { return; }
    Serial.println("Some ones here");
    while(!client.available()){  delay(1); }
    i = (client.readStringUntil('\r'));
    i.remove(0, 5);
    i.remove(i.length()-9,9);
    Serial.println(i);
    if (i == "ON") {
      digitalWrite(14,HIGH);
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("LED is ON");
      client.println("</html>");
      client.stop();
      delay(1);

    }
    if (i == "OFF") {
      digitalWrite(14,LOW);
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("LED is OFF");
      client.println("</html>");
      client.stop();
      delay(1);

    }

}
