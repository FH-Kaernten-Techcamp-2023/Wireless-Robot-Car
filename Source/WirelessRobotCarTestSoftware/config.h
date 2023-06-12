//const char* ssid = "FH_Techcamp_WRC_"; //Enter SSID
const char* password = "FH-Techcamp"; //Enter Password

 // PWM channel  parameter
const int freq = 5000; // 5000 Hz
const int ledChannel = 0;
const int resolution = 8; // 8-bit resolution

#define AIN1 2
#define AIN2 13
#define BIN1 12
#define BIN2 4
//#define PWMA 26
//#define PWMB 27
//#define STBY 17

#define LineFolL 34
#define LineFolM 35
#define LineFolR 32

#define WheelEncL 18
#define WheelEncR 19

#define LEDFL 25
#define LEDFR 33
#define LEDBL 22
#define LEDBR 23

// these constants are used to allow you to make your motor configuration
// line up with function names like forward.  Value can be 1 or -1
const int offsetA = 1;
const int offsetB = 1;

//Motor motor2 = Motor(AIN1, AIN2, PWMA, offsetA, STBY,5000 ,8,1 );
//Motor motor1 = Motor(BIN1, BIN2, PWMB, offsetB, STBY,5000 ,8,2 );
 
using namespace websockets;
WebsocketsServer server;
AsyncWebServer webserver(80);

int LValue, RValue, commaIndex;
