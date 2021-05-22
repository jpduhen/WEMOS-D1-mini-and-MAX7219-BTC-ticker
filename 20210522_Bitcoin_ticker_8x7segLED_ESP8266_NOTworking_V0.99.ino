//Version
char Version[] = "2021.0522";

//working BTC ticker with WEMOS D1 mini and 8 x 7seg display MAX7219


//3 different wallet totals in BTC (B_1/2/3) and their puchacing price in dollars (D_1/2/3)
float B_1 = 2.18066526; // Fill in your own total BTC in 1st wallet
float D_1 = 17456.01;   // Fill in your puchasing cost of those BTC in Dollars
float B_2 = 1.00867729;
float D_2 = 8069.55;
float B_3 = 0.09683423;
float D_3 = 1657.50;


// Libraries
#include <ESP8266WiFi.h>
//#include <ArduinoJson.h>

#include <WiFiManager.h>     // https://github.com/tzapu/WiFiManager
#include "max7219-jpd.h"     // https://github.com/JemRF/max7219

//Edit the pins config in max7219.h => WEMOS D1 mini (MAX_DIN 13, MAX_CS 12, MAX_CLK 14);
MAX7219 ld;                  //define display

// API server
const int httpPort = 80;                 // http port API BTC
const char* host = "api.coindesk.com";   // api server-url
char* currency = "eur";            // currency type choose [usd/gbp/eur]
float old = 0;
float old_1 = 0;
float old_2 = 0;
float old_3 = 0;
float delta = 0;
float delta_1 = 0;
float delta_2 = 0;
float delta_3 = 0;
float price = 0;


int readTime = 1000;
unsigned long nu = 0;

unsigned long previousMillis = 0;
const long interval = 60000;           // interval at which to update BTC (1 min = 60.000 ms)

void setup() {

    Serial.begin(115200);

  //display setup
    ld.Begin();
    ld.Clear();
    /* Set the brightness min:0, max:15 */
    ld.MAX7219_SetBrightness(0);
    ld.DisplayText(Version,0);   

  //WiFi-setup
    WiFi.mode(WIFI_STA); // it is a good practice to make sure your code sets wifi mode how you want it.

    //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wm;

    //reset settings - wipe credentials for testing
    //wm.resetSettings();

    // Automatically connect using saved credentials,
    // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
    // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
    // then goes into a blocking loop awaiting configuration and will return success result

    bool res;
    // res = wm.autoConnect(); // auto generated AP name from chipid
    res = wm.autoConnect("btc8x7AP"); // anonymous ap
    // res = wm.autoConnect("AutoConnectAP","password"); // password protected ap

    if(!res) {
        Serial.println("Failed to connect");
        ld.Clear();
        ld.DisplayText("btcledAP",0);
        // ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("connected...yeey :)");
        Serial.println(WiFi.localIP());
        ld.Clear();
        ld.DisplayText("Connect",0);           
    }

    ld.Clear();
    ld.DisplayText("get  btc",0);           
    
    getBTC();

    old_1 = (price * B_1) - D_1;
    old = price;
}


void loop() {

  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    // save the last time you updated the BTC
    previousMillis = currentMillis;

    getBTC();
    if ( price == 0 ) {
    getBTC();
    }
  }



  // Display on 8 x 7 segment LED
    String temp;
    char btc[9]; // 9 not 8 because 8 digits and 1 decimal point


    ld.Clear();
    ld.DisplayText(currency,0);
    delay(1000);
        
    ld.Clear();
    temp = String(price);
    temp.toCharArray(btc, temp.length()+1);  
    ld.DisplayText(btc, 1); // left aligned (left=0, right=1)
    delay(5000);

   
    ld.Clear();
    ld.DisplayText("btcdelta",1);
    delay(1000);
    
    ld.Clear();
    delta = price - old;
    temp = String(delta);
    temp.toCharArray(btc, temp.length()+1);
    ld.DisplayText(btc, 1); // right alligned (left=0, right=1)
    delay(5000);

/* 1st BTC part */

    ld.Clear();
    ld.DisplayText("1  total",0);
    delay(1000);

    ld.Clear();
    temp = String(price * B_1); // current BTC value  
    temp.toCharArray(btc, temp.length()+1);   
    ld.DisplayText(btc, 1); // left alligned (left=0, right=1)
    delay(5000);

    
    ld.Clear();
    ld.DisplayText("1 profit",0);
    delay(1000);

    ld.Clear();
    temp = String((price * B_1) - D_1);  // net result of current price against paid price
    temp.toCharArray(btc, temp.length()+1);   
    ld.DisplayText(btc, 1); // left alligned (left=0, right=1)
    delay(5000);


    ld.Clear();
    ld.DisplayText("1  delta",0);
     delay(1000);
    
    ld.Clear();
    delta_1 = ((price * B_1) - D_1) - old_1;  // difference between current price and last enquiery
    temp = String(delta_1);
    temp.toCharArray(btc, temp.length()+1);   
    ld.DisplayText(btc, 1); // left alligned (left=0, right=1)
    delay(5000);

/* 2nd BTC part */

    ld.Clear();
    ld.DisplayText("2  total",0);
    delay(1000);

    ld.Clear();
    temp = String(price * B_2); 
    temp.toCharArray(btc, temp.length()+1);   
    ld.DisplayText(btc, 1); // left alligned (left=0, right=1)
    delay(5000);

    
    ld.Clear();
    ld.DisplayText("2 profit",0);
    delay(1000);

    ld.Clear();
    temp = String((price * B_2) - D_2);  
    temp.toCharArray(btc, temp.length()+1);   
    ld.DisplayText(btc, 1); // left alligned (left=0, right=1)
    delay(5000);


    ld.Clear();
    ld.DisplayText("2  delta",0);
     delay(1000);
    
    ld.Clear();
    delta_2 = ((price * B_2) - D_2) - old_2;
    temp = String(delta_2);
    temp.toCharArray(btc, temp.length()+1);   
    ld.DisplayText(btc, 1); // left alligned (left=0, right=1)
    delay(5000);

/* 3rd BTC part */

    ld.Clear();
    ld.DisplayText("3 total",0);
    delay(1000);

    ld.Clear();
    temp = String(price * B_3); 
    temp.toCharArray(btc, temp.length()+1);   
    ld.DisplayText(btc, 1); // left alligned (left=0, right=1)
    delay(5000);

    
    ld.Clear();
    ld.DisplayText("3 profit",0);
    delay(1000);

    ld.Clear();
    temp = String((price * B_3) - D_3);  
    temp.toCharArray(btc, temp.length()+1);   
    ld.DisplayText(btc, 1); // left alligned (left=0, right=1)
    delay(5000);


    ld.Clear();
    ld.DisplayText("3 delta",0);
     delay(1000);
    
    ld.Clear();
    delta_3 = ((price * B_3) - D_3) - old_3;  // euro verschil tussen de huidige waarde en de laatste waarde alle BTC_JPM
    temp = String(delta_3);
    temp.toCharArray(btc, temp.length()+1);   
    ld.DisplayText(btc, 1); // left alligned (left=0, right=1)
    delay(5000);



}


void getBTC() {

    old_1 = (price * B_1) - D_1;
    old_2 = (price * B_2) - D_2;
    old_3 = (price * B_3) - D_3;
    
    old = price;
    
    // Connect to API
    Serial.print("connecting to ");
    Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
    WiFiClient client;
    if (!client.connect(host, httpPort)) {
      Serial.println("connection failed");
      return;
    }
  
  // We now create a URL for the request
    String url = "/v1/bpi/currentprice.json";   
    Serial.print("Requesting URL: ");
    Serial.println(url);
    
  // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" + 
                 "Connection: close\r\n\r\n");
    delay(100);
  
  // Read all the lines of the reply from server and print them to Serial
    String answer;
    while(client.available()){
      String line = client.readStringUntil('\r');
      answer += line;
    }

    client.stop();
    Serial.println();
    Serial.println("closing connection");

  // Process answer
    Serial.println();
    Serial.println("Answer: ");
    Serial.println(answer);

  // Convert to JSON
    String jsonAnswer;
    int jsonIndex;
  
    for (int i = 0; i < answer.length(); i++) {
      if (answer[i] == '{') {
        jsonIndex = i;
        break;
      }
    }

  // Get JSON data
    jsonAnswer = answer.substring(jsonIndex);
    Serial.println();
    Serial.println("JSON answer: ");
    Serial.println(jsonAnswer);
    jsonAnswer.trim();

  // Get rate as float
  // Uncomment (remove //) @ JUST one of the next three options [USD/GBP/EUR]

  // Option 1 USD
  //  int rateIndex = jsonAnswer.indexOf("\"United States Dollar\",\"rate_float\"");
  //  String priceString = jsonAnswer.substring(rateIndex + 36, rateIndex + 46); 

  // Option 2: GBP 
  //  int rateIndex = jsonAnswer.indexOf("\"British Pound Sterling\",\"rate_float\"");
  //  String priceString = jsonAnswer.substring(rateIndex + 38, rateIndex + 48); 

  // Option 3: EUR
    int rateIndex = jsonAnswer.indexOf("\"Euro\",\"rate_float\"");
    String priceString = jsonAnswer.substring(rateIndex + 20, rateIndex + 30); 
   
    Serial.println(priceString);
    priceString.trim();
    price = priceString.toFloat();

  // Print price
    Serial.println();
    Serial.println("Bitcoin price: ");
    Serial.println(price);

}
