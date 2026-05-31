
  // 
#include <Wire.h>
#include <PCF85263.h>

#define PIN_SDA 0
#define PIN_SCL 1
#define PIN_RTC_INT 6
#define PIN_SERVO 10
#define PIN_MANUAL_BTN 13

//feeding times
const uint8_t FEED1_HOUR = 8;
const uint8_t FEED1_MINUTE = 0;
const uint8_t FEED2_HOUR = 18;
const uint8_t FEED2_MINUTE = 0;

#define DISPENSE_MS 1500

PCF85263 rtc;

volatile bool rtcAlarm = false;
volatile bool manualFeedReq = false;

//for pcf85263
#define REG_ALARM1_SEC    0x08
#define REG_ALARM1_MIN    0x09
#define REG_ALARM1_HR     0x0A
#define REG_ALARM_ENABLES 0x10   // INTA_EN register
#define REG_FLAGS         0x44  //flag alarm

//for servo control
#define LEDC_CHANNEL 0
#define LEDC_FREQ 50 //Hz
#define LEDC_RES 16 

//degrees to LEDC duty 
uint32_t degreesToDuty(int deg){
  //500us = 0 degrees, 2500us = 180 degree
  uint32_t pulseUs = map(deg, 0, 180, 500, 2500);
  return (uint32_t)(pulseUs * 65535UL / 20000UL);
}

void servoWrite(int deg){
  ledcWrite(LEDC_CHANNEL, degreesToDuty(deg));
}

void servoAttach() {
  ledcAttach(PIN_SERVO, LEDC_FREQ, LEDC_RES);
}

void servoDetach(){
  ledcWrite(LEDC_CHANNEL, 0);
  ledcDetach(PIN_SERVO);
}

void IRAM_ATTR onManualFeed() { manualFeedReq = true; }

void IRAM_ATTR onRtcAlarm() { rtcAlarm = true; }

uint8_t  toBCD(uint8_t val) { return ((val / 10) <<4) | (val % 10); }

void clearAlarmFlag() {
  int flags = rtc.readRegister(REG_FLAGS);
  rtc.writeRegister(REG_FLAGS, flags & ~0x04);
}

void setAlarmRegisters(uint8_t hour, uint8_t minute){
  rtc.writeRegister(REG_ALARM1_SEC, 0X00);
  rtc.writeRegister(REG_ALARM1_MIN, toBCD(minute));
  rtc.writeRegister(REG_ALARM1_HR, toBCD(hour));

  int flags = rtc.readRegister(REG_FLAGS);
  rtc.writeRegister(REG_ALARM1_SEC, ~0X04);

  int ctrl = rtc.readRegister(REG_ALARM_ENABLES);
  rtc.writeRegister(REG_ALARM_ENABLES, ctrl | 0x04 );
}

void dispenseFood(){
  Serial.println("Feeder dispensing food...");
  servoAttach();
  servoWrite(90); //to open
  delay(DISPENSE_MS);
  servoWrite(0); //to close
  delay(500);
  servoDetach();
  Serial.print("Feeder Done.");
}

void setNextAlarm() {
  rtc.readDateTime();
  uint16_t nowTotal = rtc.hours() * 60 + rtc.minutes();
  uint16_t feed1Total = FEED1_HOUR * 60 + FEED1_MINUTE;
  uint16_t feed2Total = FEED2_HOUR * 60 + FEED2_MINUTE;

  uint8_t nextH, nextM;
  if (nowTotal < feed1Total) {nextH = FEED1_HOUR; nextM = FEED1_MINUTE;}
  else if (nowTotal < feed2Total) {nextH = FEED2_HOUR; nextM= FEED2_MINUTE;}
  else {nextH = FEED1_HOUR; nextM = FEED1_MINUTE;}

  Serial.printf("[RTC] Next alarm: %02d:%02d\n", nextH, nextM);

  setAlarmRegisters(nextH, nextM);
 
}

void setup(){
  Serial.begin(115200);
  Wire.begin(PIN_SDA, PIN_SCL);

  if (!rtc.begin()){
    Serial.println("[Error] RTC not found!");
    while (true) delay (1000);
  }
  //rtc.settime

  pinMode(PIN_MANUAL_BTN, INPUT);
  attachInterrupt(digitalPinToInterrupt(PIN_MANUAL_BTN), onManualFeed, RISING);

  pinMode(PIN_RTC_INT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_RTC_INT), onRtcAlarm, FALLING);

  setNextAlarm();
}
void loop() {
  //for rtc alarm
  if (rtcAlarm) {
    rtcAlarm= false;
    clearAlarmFlag();
    Serial.println("[Alarm] Feed time");
    dispenseFood();
    setNextAlarm();

  }

  if(manualFeedReq)
  {
    manualFeedReq = false;
    delay(50);
    Serial.println("[Manual] Dispensing now");
    dispenseFood();
  }

  delay(100);
}
