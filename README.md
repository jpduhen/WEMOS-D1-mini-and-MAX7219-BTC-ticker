# WEMOS-D1-mini-and-MAX7219-BTC-ticker
## A low cost BTC ticker based on a WEMOS D1 mini and a MAX7219 display

![IMG_3493](https://user-images.githubusercontent.com/45515609/119229483-964a6800-bb18-11eb-8cde-a79fbf68d500.jpg)
![IMG_3500](https://user-images.githubusercontent.com/45515609/119230500-c431ab80-bb1c-11eb-88c9-e0e230abaa82.jpg)

## CONNECTIONS
```
**DISPLAY -> WEMOS**
CLK -> D2
CS  -> D3
DIN -> D4
VCC -> 3.3v
GND -> GND
```
## SET UP
Using Arduino IDE, make sure the MAX7219-jpd.ccp an MAX7219-jpd.h are in the same directory as the 20210522_v0.99.ino file

1. Read through te comments in the 20210522_v0.99.ino file and make your changes to fit your wishes (see below)
2. Enter the BTC and purchesed value(s) for up to 3 wallets you want displayed
3. Flash the WEMOS with the 20210522_v0.99.ino file
4. The display shows the version "2021.0522" number
![IMG_3494](https://user-images.githubusercontent.com/45515609/119230363-2211c380-bb1c-11eb-8baf-810155fdf3d6.jpg)

5. the WEMOS wants to connect to the internet and needs your local WIFI credentials
6. You can set the local WIFI credentials via AccesPoint "btc8x7AP" no password needed
![IMG_3495](https://user-images.githubusercontent.com/45515609/119230388-4077bf00-bb1c-11eb-9033-71d6c4198103.jpg)

7. You should get redirected to page http://192.168.4.1 or go there manually
![IMG_3496](https://user-images.githubusercontent.com/45515609/119230400-4bcaea80-bb1c-11eb-8196-9b09440aa567.jpg)

8. Select your local WIFI SSID and enter the correct password
![IMG_3498](https://user-images.githubusercontent.com/45515609/119230406-538a8f00-bb1c-11eb-8fe5-61b19d7094e2.jpg)

9. The WEMOS saves these in memory and tries to connect to the internet via your Local WIFI network
![IMG_3499](https://user-images.githubusercontent.com/45515609/119230414-5a190680-bb1c-11eb-859a-7fff8c039ce5.jpg)

10. If the network is found the display shows "Get btc"
![IMG_3501](https://user-images.githubusercontent.com/45515609/119230605-4c17b580-bb1d-11eb-9cbb-fdf6beb309a7.jpg)

12. After a few seconds the current BTC value's are shown in the display 

## Make changes to fit your wishes in the 20210522_v0.99.ino file

### Set the currency in line 29, you can choose usd, gbp of eur
```
char* currency = "eur";            // currency type choose [usd/gbp/eur]
```

### Set the amount of BTC in wallets 1-3 and the cost of puchase in your currency in lines 8-13

In this example:
- wallet 1 has 2.18066526 BTC bought at 17456.01, 
- wallet 2 has 1.00867729 BTC bought at 8069.55 and 
- wallet 3 has 0.09683423 BTC bought at 1657.50
```
float B_1 = 2.18066526; // Fill in your own total BTC in 1st wallet
float D_1 = 17456.01;   // Fill in your puchasing cost of those BTC in Dollars
float B_2 = 1.00867729;
float D_2 = 8069.55;
float B_3 = 0.09683423;
float D_3 = 1657.50;
```
