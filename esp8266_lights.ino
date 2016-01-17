#include <ESP8266WiFi.h>
#include "Constants.h"
#include "Led.h"


#define LEDoff digitalWrite(LEDPIN,HIGH)
#define LEDon digitalWrite(LEDPIN,LOW)

#define LED2off digitalWrite(LED2PIN,HIGH)
#define LED2on digitalWrite(LED2PIN,LOW)

Led red(redPIN);
Led green(greenPIN);
Led blue(bluePIN);
Led white(w1PIN);
Led white2(w2PIN);

const char *ssid =  "strong";
const char *pass =  "almond33";

// Start WiFi Server
WiFiServer server(80);

void setup()
{
  red.setup();
  green.setup();
  blue.setup();
  white.setup();
  white2.setup();

  pinMode(LEDPIN, OUTPUT);
  pinMode(LED2PIN, OUTPUT);

  // Setup console
  Serial1.begin(115200);
  delay(10);
  Serial1.println();
  Serial1.println();

  WiFi.begin(ssid, pass);

  LEDon;

  while (WiFi.status() != WL_CONNECTED) {

    LED2off;
    delay(500);
    Serial1.print(".");
    LED2on;
  }

  Serial1.println("");

  Serial1.println("WiFi connected");
  Serial1.println("IP address: ");
  Serial1.println(WiFi.localIP());

  Serial1.println("");

  server.begin();
  Serial1.println("Webserver started");

}

void loop()
{
  // Check if a client has connected
  WiFiClient client = server.available();
  if (client) {

      LED2off;

      // Read the first line of the request
      String req = client.readStringUntil('\r');
      Serial1.println(req);
      client.flush();

      // Prepare the response. Start with the common header:
      String s = "HTTP/1.1 200 OK\r\n";
      s += "Content-Type: text/html\r\n\r\n";
      s += "<!DOCTYPE HTML>\r\n<html>\r\n";

      if((req.indexOf("/rgb/") != -1)) { // rgb changed

        // get RGB value
        int pos = req.length();
        int ind1 = req.indexOf('/rgb/') + 5;
        String teststring = req.substring(ind1, pos);
        int ind2 = teststring.indexOf('/');
        String hexRGB = req.substring(ind1, ind2+ind1);

        // convert HEX to RGB
        hexRGB.toUpperCase();
        char c[10];
        hexRGB.toCharArray(c,7);

        red.set(convertToInt(c[0], c[1]));
        green.set(convertToInt(c[2], c[3]));
        blue.set(convertToInt(c[4], c[5]));
        // confirm to client
        s += "RGB value changed to ";
        s += hexRGB;

      }

      if((req.indexOf("/ww/") != -1)) { // white changed

        // get ww values
        int pos = req.length();
        int ind1 = req.indexOf('/ww/') + 4;
        String teststring = req.substring(ind1, pos);
        int ind2 = teststring.indexOf('/');
        String hex = req.substring(ind1, ind2+ind1);

        // convert HEX to int
        hex.toUpperCase();
        char c[6];
        hex.toCharArray(c,5);

        white.set(convertToInt(c[0], c[1]));
        white2.set(convertToInt(c[2], c[3]));

        // confirm to client
        s += "WW value changed to ";
        s += hex;

      }

      s += "<br>";
      s += "Request OK!";

      s += "</html>\n";

      client.flush();

      // Send the response to the client
      client.print(s);
      //delay(1);
      Serial1.println("Client disonnected");

      // The client will actually be disconnected
      // when the function returns and 'client' object is detroyed

      LED2on;
  }

  red.update();
  green.update();
  blue.update();
  white.update();
  white2.update();
}

int convertToInt(char upper,char lower)
{
  int uVal = (int)upper;
  int lVal = (int)lower;
  uVal = uVal >64 ? uVal - 55 : uVal - 48;
  uVal = uVal << 4;
  lVal = lVal >64 ? lVal - 55 : lVal - 48;
  return uVal + lVal;
}
