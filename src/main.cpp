/**
   esp32 firmware OTA 
   
   Purpose: Perform an OTA update from a bin located   on a webserver (HTTP Only)

   Setup: 
   Step 1 : Set your WiFi (ssid & password)
   Step 2 : set esp32fota()
   
   Upload:
   Step 1 : Menu > Sketch > Export Compiled Library. The bin file will be saved in the sketch folder (Menu > Sketch > Show Sketch folder)
   Step 2 : Upload it to your webserver
   Step 3 : Update your firmware JSON file ( see firwmareupdate )

*/

#include <esp32fota.h>
#include <WiFi.h>

// Change to your WiFi credentials
const char *ssid = "bitotron2";
const char *password = "b1t0tr0nw1f1";

// esp32fota esp32fota("<Type of Firme for this device>", <this version>, <validate signature>);

// azonosítani a progit, a verziószámmal együtt. Ezek az adatok kerülnek a JSON fájlba  ** !!!!! 

esp32FOTA esp32FOTA("otateszt", "1.4", false);     

// **** !!!!!!!!!!  ***************   az első paraméter egy tetszőleges TIPUSJELZÉS, de az ÖSSZES további verziónál maradjon változatlan !

void setup_wifi()
{
  delay(10);
 
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println(WiFi.localIP());
}

void setup()
{
  esp32FOTA.checkURL =  "http://192.168.57.203:8000/fota/firmware.json";   //  a JSON fájl pontos helye, ha ezt nem találja nincs frissítés
  Serial.begin(115200);
  setup_wifi();
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  Serial.print("check: ");
  bool updatedNeeded = esp32FOTA.execHTTPcheck();
  if (updatedNeeded)
  { 
    Serial.print("frissítés indul...");
    esp32FOTA.execOTA();
    Serial.print(" ..és vége !");
  } else Serial.println(" nincs frissítés **** ");
   digitalWrite(2, !digitalRead(2));                  // "ledes" változat
  delay(10000);
}
