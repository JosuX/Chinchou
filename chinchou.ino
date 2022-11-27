#include <OneWire.h>
#include <DallasTemperature.h>

#define WaterSensor0  A0
#define WaterSensor1  A1

#define Temp0         13
#define Temp1         12

#define HotIndicator   4
#define ColdIndicator  7

#define HotPump        3
#define ColdPump       2

OneWire cWater(Temp0);
OneWire hWater(Temp1);

DallasTemperature coldWater(&cWater);
DallasTemperature hotWater(&hWater);

float coldCelcius=0;
float hotCelcius=0;


void setup() {
  Serial.begin(9600);
  coldWater.begin();
  hotWater.begin();
  pinMode(HotPump, OUTPUT);
  digitalWrite(HotPump, LOW);
  pinMode(ColdPump, OUTPUT);
  digitalWrite(ColdPump, LOW);

}

void loop() {
  coldWater.requestTemperatures();
  hotWater.requestTemperatures();
  coldCelcius = coldWater.getTempCByIndex(0);
  hotCelcius = hotWater.getTempCByIndex(0);
  bool water0 = detectWater0();
  bool water1 = detectWater1();

  //Logging
  Serial.println("||Cold Gallon||");
  Serial.print("Water detected: ");
  Serial.println(water0);
  Serial.print("Temp: ");
  Serial.println(coldCelcius);
  Serial.println();
  Serial.println("||Hot Gallon||");
  Serial.print("Water detected: ");
  Serial.println(water1);
  Serial.print("Temp: ");
  Serial.println(hotCelcius);
  

  delay(500);
}

bool detectWater0() {
  val = analogRead(WaterSensor0)
  if(val >= 100){
    return true;
  }
  else{
    return false;
  }
}

bool detectWater1() {
  val = analogRead(WaterSensor1)
  if(val >= 100){
    return true;
  }
  else{
    return false;
  }
}
