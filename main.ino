#include <FS.h>
#ifdef ESP32
#include <SPIFFS.h>
#endif
//#include <WiFi.h>
#include <WiFiManager.h>
#include <WiFiClientSecure.h>
#include <WebServer.h>
#include <Wire.h>
#include <time.h>
#include <DNSServer.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include <lvgl.h>
#include <Ticker.h>
#include <PubSubClient.h>
#include <ModbusMaster.h>
#include <TridentTD_LineNotify.h>
#include "Adafruit_MCP23X17.h"
#include "RTClib.h"
#include <HTTPUpdate.h>
#include <ESP32Ping.h>
#include <esp_now.h>


typedef struct struct_message {
  char message[200];
  int b;
  char ssid[50];
  bool status;
} struct_message;

struct_message myData;

#define MQTT_MAX_PACKET_SIZE 2048
#define SDA_PIN 4
#define SCL_PIN 15

TFT_eSPI tft = TFT_eSPI(); /* TFT instance */
Adafruit_MCP23X17 mcp;
Ticker tick; /* timer for interrupt handler */
RTC_DS3231 RTC;
WiFiManager wifiManager;
ModbusMaster node;
WiFiClient espClient;
PubSubClient client(espClient);

/* PIN OUT */
static uint8_t p0 = 0;
static uint8_t p1 = 1;
static uint8_t p2 = 2;
static uint8_t p3 = 3;
static uint8_t p4 = 4;
static uint8_t p5 = 5;
static uint8_t p6 = 6;
static uint8_t p7 = 7;
static uint8_t p8 = 8;
static uint8_t p9 = 9;
static uint8_t p10 = 10;
static uint8_t p11 = 11;
static uint8_t p12 = 12;
static uint8_t p13 = 13;
static uint8_t p14 = 14;
static uint8_t p15 = 15;
int pin[] = {0, 1, 2, 3};
char pinName[4][12] = {"R1", "R2", "R3", "ALERT"};
int state[4];
bool phState[4];
bool ecState[4];
bool timerState[4];
bool sclState[4];
bool bclState[4];
int phCounter = 0;
int ecCounter = 0;
bool ecInputState = false;
bool phInputState = false;
bool waterInputState = false;
bool tempHumInputState = false;
float maxEc[] = {0, 0, 0, 0};
float minEc[] = {0, 0, 0, 0};
float maxPh[] = {0, 0, 0, 0};
float minPh[] = {0, 0, 0, 0};
String tStart[4][8];
String tStop[4][8];
String tDays[4][8][8];
/* END PINOUT */

bool restart = false;
bool startUp = false;

String ver = "2.1.1";

/* END DEVICE */

boolean phSend = true;
boolean ecSend = true;
boolean waterSend = true;
bool pingTest = false;

#define INTERVAL_TH_READ 5000
unsigned long time_th_read = 0;

#define INTERVAL_PHSEND 3600000 //1H
#define INTERVAL_ECSEND 3600000 //1H
#define INTERVAL_WATERSEND 3600000 //1H
unsigned long time_updatephsend = 0;
unsigned long time_updateecsend = 0;
unsigned long time_updatewatersend = 0;

int phCount = 0;
int ecCount = 0;
int thCount = 0;
int pinCheckCount = 5;
int inputCheckCount = 4;
int stuCount = 0;
bool Auto;
bool fan = false;
bool data_save = false;
int mqtt_con = 0 ;

/* SAVE READ STATE */
bool shouldSaveConfig = false;
bool shouldReadGpioApi = false;
bool shouldReadGpioDataApi = false;
bool shouldReadDeviceApi = false;
bool shouldReadGpioTimerApi = false;
bool shouldReadSensorStateApi = false;
bool shouldReadFanApi = false;
/* END SAVE READ STATE */
char ssid[20] = "";
char pass[20] = "";

int timezone = 7 * 3600;
int dst = 0;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

/* state check */
bool state_check_online = false;
bool input_check_online = false;
bool auto_check_online = false;
/* end check */


/* BROKKER */
const char* MQTT_BROKER = "45.136.253.202";
const char* MQTT_BROKER_USER = "matchmqtt";
const char* MQTT_BROKER_PASS = "@matchmqtt";
const String SERVER_OTA_IP = "http://45.136.253.202:4007/v1";
/* END BROKER */

/* DEVICE */
char device_id[30] = "";
char device_name[30] = "MATCH_IOT";
char LINE_TOKEN[50] = "";

/////////////////////////// INTERVAL RECON /////////////
#define INTERVAL_RECON_WIFI 10000 // 15MIN SAVE DATA
unsigned long time_recon_wifi = 0;
int time_recon_count = 0;
int recon_wifi_conut = 0;
/////////////////////////////////////////////////////

/* -- TOPIC -- */

/* IN TOPIC */
String gpioInTopic;
String gpioDataInTopic ;
String deviceInTopic ;
String gpioTimerInTopic ;
String deviceSensorInTopic ;
String fanInTopic ;
/* END IN TOPIC */

/* CHECK IN TOPIC */
String checkinTopic ;
String gpioOutCheckinTopic ;
String sensorOutCheckinTopic ;

/* END CHECKIN TOPIC */

/* OUT TOPIC */
String outTopic ;
String gpioOutTopic;
String autoOutTopic ;
String sensorOutTopic;
String sensorStatusOutTopic;
String fanOutTopic ;
/* END OUT TOPIC */

/* WILL TOPIC */
String willTopic ;
/* END WILL TOPIC */

/* -- END TOPIC -- */

int time_count = 0;
int read_serial_count = 0;

/* SENSOR */
float PostPH = 0;
float PostPHTEMP = 0;
float PostEC = 0;
float PostECTEMP = 0;
float PostWaterFlow = 0;
float PostWaterTotal = 0;
float PostBOARDTEMP = 0;
float PostBOARDHUM = 0;
int SCL_TANK = 0;
int BCL_TANK = 0;
int ultrasonic_count = 0;
bool ultraSonicInputState = false;
/* END SENSOR */

uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};//ส่งไปหาทุกตัว

esp_now_peer_info_t peerInfo;

void loop() {
  lv_task_handler();
  delay(10);
}
