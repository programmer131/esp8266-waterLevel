# esp8266-waterLevel
water level control system using ESP8266 and HC-SR04
complete demonstration and setup details in this YouTube video: watch->like->subscribe-> https://youtu.be/KK4ebz8kvqs 

Instructions:

Step 1: 

you need a cylindrical tank and measure its capacity in liters, may use this tool for that
http://aqua.ucdavis.edu/Calculations/Volume_of_a_Cylindrical_Tank.htm
if don't have cylidrical tank, then need to modify code accordingly.

relay connected to water pump, nodemcu pin D4

hc sr04 TRIG connected to D1 and Echo connected to D2 through a voltage divider, (1k,2k)

Step 2:

modify these two lines as per capacity in FusionCharts.ready() function
"lowerLimit": "0",
"upperLimit": "15",

modify  slider paramters as per capacity and default settings
max: 16,
min: 0,
range: true,
values: [3, 12],

you can locate these settings inside $("#flat-slider-vertical-1").slider(

html file is already included in Arduino sketch, you can modify these paramters inside arduino sketch.

Step3:

create new adafruit IO feed and name it as 'waterLevel'

uncomment these two lines in sketch and write your wifi ssid/password

/*const char* ssid = "ssid";

const char* password = "password";*/

also uncomment and write here your own adafruit IO username and key.

//#define AIO_USERNAME    "programmer5"//replace it with your username

//#define AIO_KEY         "6e5fd35c936743808ceae4e101f6cbd1"//replace it with your key

uncomment these lines as well, write radius of tank and total height in units of inches,

//#define RADIUS 5.5

//#define MAX_HEIGHT 10

modify this line if you have to connect relay to some pin other than D4

#define MOTOR_CONTROL_PIN D4 

Connect trig of ultrasonic sensor at D1 and echo at D2, modify this line otherwise

UltraSonicDistanceSensor distanceSensor(D1,D2);  //D1 trig, D2=echo

these are default water level limits, these values will be applied on reset until user sends new limits from webpage. 

int waterLevelLowerThreshold=3;

int waterLevelUpperThreshold=12;

Need to install this HCSR04 library: https://github.com/Martinsos/arduino-lib-hc-sr04
