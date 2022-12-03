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

#define Peltier0       5
#define Peltier1       6

//Water Level Sensor threshold = 275
//Water Temp Sensor threshold  = 20C

OneWire cWater(Temp0);
OneWire hWater(Temp1);

DallasTemperature coldWater(&cWater);
DallasTemperature hotWater(&hWater);

double coldCelcius=0;
double hotCelcius=0;


void setup() {
  Serial.begin(9600);
  coldWater.begin();
  hotWater.begin();
  pinMode(Peltier0,   OUTPUT);
  pinMode(Peltier1,   OUTPUT);
  pinMode(ColdPump,   OUTPUT);
  digitalWrite(HotPump,  LOW);
  digitalWrite(ColdPump, LOW);
  digitalWrite(Peltier0, LOW);
  digitalWrite(Peltier1, LOW);
}

void loop() {
  coldWater.requestTemperatures();
  hotWater.requestTemperatures();
  coldCelcius = coldWater.getTempCByIndex(0);
  hotCelcius = hotWater.getTempCByIndex(0);
  bool water0 = detectWater0();
  bool water1 = detectWater1();
  
  if(coldCelcius <= 20.0){
    digitalWrite(Peltier0, HIGH);
  }
  else{
    digitalWrite(Peltier0, LOW);
  }
  
  if(hotCelcius >= 85.0){
    digitalWrite(Peltier1, HIGH);
  }
  else{
    digitalWrite(Peltier1, LOW);
  }

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
  double val = analogRead(WaterSensor0);
  Serial.println(val);
  if(val >= 275){
    return true;
  }
  else{
    return false;
  }
}

bool detectWater1() {
  double val = analogRead(WaterSensor1);
  Serial.println(val);
  if(val >= 275){
    return true;
  }
  else{
    return false;
  }
}
