#include <ESP8266WiFi.h>
#include <HCSR04.h>
#include <ESP8266WebServer.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

const char index_html[] PROGMEM={"<!DOCTYPE html>\n"
"<html>\n"
"<head>\n"
"<title>My first chart using FusionCharts Suite XT</title>\n"
"<script type=\"text/javascript\" src=\"http://static.fusioncharts.com/code/latest/fusioncharts.js\"></script>\n"
"<script type=\"text/javascript\" src=\"http://static.fusioncharts.com/code/latest/themes/fusioncharts.theme.fint.js?cacheBust=56\"></script>\n"
"<script src=\"https://cdnjs.cloudflare.com/ajax/libs/zepto/1.2.0/zepto.min.js\"></script>\n"
"<script src=\"https://simeydotme.github.io/jQuery-ui-Slider-Pips/dist/js/jquery-plus-ui.min.js\"></script>\n"
"<script src=\"https://simeydotme.github.io/jQuery-ui-Slider-Pips/dist/js/jquery-ui-slider-pips.js\"></script>\n"
"<link rel=\"stylesheet\" href=\"https://simeydotme.github.io/jQuery-ui-Slider-Pips/dist/css/jqueryui.min.css\">\n"
"<link rel=\"stylesheet\" href=\"https://simeydotme.github.io/jQuery-ui-Slider-Pips/dist/css/jquery-ui-slider-pips.min.css\">\n"
"<link rel=\"stylesheet\" href=\"https://simeydotme.github.io/jQuery-ui-Slider-Pips/dist/css/app.min.css\">\n"
"<style>\n"
".raphael-group-7-background rect {\n"
"fill: rgb(218, 218, 218) !important;\n"
"}\n"
"[id*=flat-slider].ui-slider.ui-slider-vertical {\n"
"\theight: 220px;\n"
"\tmargin-top: 90px;\n"
"    margin-right: 15%;\n"
"    margin-bottom: 90px;\n"
"    margin-left: 15%;\n"
"}\n"
"$bg: #434d5a;\n"
"[id*=flat-slider].ui-slider,\n"
"[id*=flat-slider].ui-slider .ui-slider-pip .ui-slider-line {\n"
"    background: lighten($bg, 15%);\n"
"}\n"
"[id*=flat-slider].ui-slider .ui-slider-handle .ui-slider-tip:after {\n"
"    border-left-color: #434d5a;\n"
"}\n"
"[id*=flat-slider].ui-slider .ui-slider-handle.ui-state-hover, \n"
"[id*=flat-slider].ui-slider .ui-slider-handle.ui-state-focus, \n"
"[id*=flat-slider].ui-slider .ui-slider-handle.ui-state-active {\n"
"      border-color: white; }\n"
"body {\n"
"background-image: url(\"https://drive.google.com/uc?id=1JC1A8qTXnHrcvFH1-un6D3rTjfEAggVn\");\n"
"   \n"
"    font-family: \"Roboto\";\n"
"}\n"
".stuff {    \n"
"    padding: 10px 5px 5px;\n"
"    max-width: 150px;    \n"
"\tmax-height: 550px;    \n"
"}\n"
"div.inline { float:left; }\n"
".clearBoth { clear:both; }\n"
"\n"
"</style>\n"
"<script>\n"
"$(document).ready(function() {\n"
"            setInterval(\"get_motor_status()\", 2000);\n"
"        });\n"
"\t\t\t\t\n"
"        function get_motor_status() {\n"
"            var someUrl = \"/motor_status\";\n"
"            $.ajax({url: someUrl,dataType: \"text\",success: function(response) {\n"
"                    if (response == \"on\")\n"
"                        $(\"#status\").html(\"Motor ON\")\n"
"                    else\n"
"                        $(\"#status\").html(\"Motor OFF\")\n"
"                   }})}\t\t\n"
"\t\t\t\t\n"
"    </script>\n"
"\t\n"
"<script type=\"text/javascript\">\n"
"    FusionCharts.ready(function(){\n"
"    var fusioncharts = new FusionCharts({\n"
"    \"type\": \"cylinder\",\n"
"    \"dataFormat\": \"json\",\n"
"    \"id\": \"fuelMeter\",\n"
"    \"renderAt\": \"chart-container\",\n"
"    \"width\": \"200\",\n"
"    \"height\": \"350\",\n"
"    \"dataSource\": {\n"
"        \"chart\": {\n"
"            \"theme\": \"fint\",\n"
"            \"caption\": \"Water Level in Bucket\",\n"
"            \"subcaption\": \"at my Home\",\n"
"            \"lowerLimit\": \"0\",\n"
"            \"upperLimit\": \"15\",\n"
"            \"lowerLimitDisplay\": \"Empty\",\n"
"            \"upperLimitDisplay\": \"Full\",\n"
"            \"numberSuffix\": \" ltrs\",\n"
"            \"showValue\": \"1\",\n"
"            \"chartBottomMargin\": \"25\"\n"
"        },\n"
"        \"value\": \"10\"\n"
"    },\n"
"    \"events\": {\n"
"    \"rendered\": function(evtObj, argObj) {\n"
"\tsetInterval(function() {\n"
"\tvar someUrl = \"/level\";\n"
"\t\t\t\t\t$.ajax({\n"
"\t\t\t\t\t\turl: someUrl,\n"
"\t\t\t\t\t\tdataType: \"text\",\n"
"\t\t\t\t\t\tsuccess: function(response) {\n"
"\t\t\t\t\t\t\t evtObj.sender.feedData(\"&value=\" + response);\n"
"\t\t\t\t\t\t},\n"
"\t\t\t\t\t\ttimeout: 2000\n"
"\t\t\t\t\t})\t\n"
"\t\t\n"
"        }, 1000); \n"
"   }\n"
"}\n"
"});\n"
"    fusioncharts.render();\n"
"    });\n"
"</script>\n"
"</head>\n"
"<body>\n"
"<div style=\"width:600px;margin:auto;\">\n"
"\n"
"<div class=\"stuff\">\n"
" \n"
"    <main>        \n"
"        <div class=\"inline\" id=\"flat-slider-vertical-1\"></div>        \n"
"    </main>\n"
"    \n"
"</div>\n"
"    <div style=\"margin-left: 10px;\" class=\"inline\" id=\"chart-container\">FusionCharts XT will load here!</div>\n"
"\t<div class=\"inline\" id=\"status\" style=\"background-color: lightgrey;\n"
"    width: 100px;\n"
"    border: 10px solid;\n"
"\tborder-color: coral;\n"
"    padding: 2px;\n"
"    margin: 1px;\">Motor OFF</div>\n"
" </div>\n"
"\n"
"<script>\n"
"$.extend( $.ui.slider.prototype.options, { \n"
"    animate: 300\n"
"});\n"
"\n"
"\n"
"$(\"#flat-slider-vertical-1\")\n"
"    .slider({\n"
"        max: 16,\n"
"        min: 0,\n"
"        range: true,\n"
"         values: [3, 12],\n"
"        orientation: \"vertical\",\n"
"\t\t\n"
"\t\tslide: function( event, ui ) {\n"
"\t\tconsole.log(ui.values);\n"
"\t\tvar someUrl = \"/configRange?lower=\" + ui.values[0]+\"&upper=\"+ui.values[1];\n"
"            $.ajax(\n"
"\t\t\t{\n"
"\t\t\t\turl: someUrl,dataType: \"text\",success: function(response) {}\n"
"\t\t\t})               \n"
"        }\n"
"    })\n"
"    .slider(\"pips\", {\n"
"        first: \"pip\",\n"
"        last: \"pip\"\n"
"    })\n"
"    .slider(\"float\");\n"
"</script>\n"
"\n"
"\t</body>\n"
"</html>"
  };
//create new adafruit IO feed and name it as 'waterLevel'
//uncomment these two lines and write your wifi ssid/password
/*const char* ssid = "ssid";
const char* password = "password";*/
//also uncomment and write here your own adafruit IO username and key.
//#define AIO_USERNAME    "programmer5"//replace it with your username
//#define AIO_KEY         "6e5fd35c936743808ceae4e101f6cbd5"//replace it with your key
//uncomment these lines as well, write radius of tank and total height in units of inches,
//#define RADIUS 5.5
//#define MAX_HEIGHT 10
//modify this line if you have to connect relay to some pin other than D4
#define MOTOR_CONTROL_PIN D4 
//Connect trig of ultrasonic sensor at D1 and echo at D2, modify this line otherwise
UltraSonicDistanceSensor distanceSensor(D1,D2);  //D1 trig, D2=echo
//these are default water level limits, these values will be applied until on reset until user sends new limits from webpage. 
int waterLevelLowerThreshold=3;
int waterLevelUpperThreshold=12;


#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
float volume;
float liters;
// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish waterLevel = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/waterLevel");

/*************************** Sketch Code ************************************/

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();


String inputString = "";         // a string to hold incoming data
String dataToSend="";
int waterLevelDownCount=0,waterLevelUpCount=0;

ESP8266WebServer server(80);
void handleRoot() {
  server.send_P(200, "text/html;charset=UTF-8", index_html);
}

void handleLevelRequest(){
  server.send(200,"text",String(liters));
}

void handleNotFound(){
  String message = "File Not Found\n\n";
  server.send(404, "text/plain", message);
}
void handleStatus()
{
  if(digitalRead(MOTOR_CONTROL_PIN)==0)//MOTOR ON
 server.send(200, "text/plain","on"); 
 else server.send(200, "text/plain","off");
}
void handleRangeSetting(){
   waterLevelLowerThreshold=(server.arg(0)).toInt();  
   waterLevelUpperThreshold=(server.arg(1)).toInt(); 
   Serial.print(waterLevelLowerThreshold);
   Serial.print(":");   
   Serial.println(waterLevelUpperThreshold);
     
   server.send(200, "text/plain", "");
}

void measure_Volume()
{
    float heightInch=0.393701*distanceSensor.measureDistanceCm();    
    Serial.println(heightInch); 
    if(heightInch>MAX_HEIGHT)
      heightInch=MAX_HEIGHT;
    if(heightInch<0)
      heightInch=0;      
    volume=3.14*RADIUS*RADIUS*(MAX_HEIGHT-heightInch);//MAX_HEIGHT-distance will give actual height,
    liters=volume*0.0164  ;
    Serial.println(liters); 

    if(liters<=waterLevelLowerThreshold)
        waterLevelDownCount++;
      else waterLevelDownCount=0;

      if(liters>=waterLevelUpperThreshold)
        waterLevelUpCount++;
      else waterLevelUpCount=0;

      waterLevel.publish(liters);      
      

      if(waterLevelDownCount==3)
      {//TURN ON RELAY
        Serial.println("motor turned on");   
        digitalWrite(MOTOR_CONTROL_PIN,LOW);//Relay is active LOW
      }
      if(waterLevelUpCount==3)
      {//TURN OFF RELAY
        Serial.println("motor turned off");   
        digitalWrite(MOTOR_CONTROL_PIN,HIGH);//Relay is active LOW
      }      
}
void runPeriodicFunc()
{
    static const unsigned long REFRESH_INTERVAL1 = 2100; // 2.1sec
    static unsigned long lastRefreshTime1 = 0;
    
    if(millis() - lastRefreshTime1 >= REFRESH_INTERVAL1)
    {   
      measure_Volume();
      lastRefreshTime1 = millis();
   }
}

void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

    while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       }
  Serial.println("MQTT Connected!");
}


void setup(void){
  Serial.begin(115200);
  delay(100);
  pinMode(MOTOR_CONTROL_PIN, OUTPUT);
  WiFi.begin(ssid, password);
  Serial.println("");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("IP address:");  
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);  
  server.on("/level",handleLevelRequest);
  server.on("/configRange",handleRangeSetting);
  server.on("/motor_status",handleStatus);
    
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  runPeriodicFunc();
  
  MQTT_connect();
  server.handleClient();
}
