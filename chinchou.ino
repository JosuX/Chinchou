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
  pinMode(Peltier0,        OUTPUT);
  pinMode(Peltier1,        OUTPUT);
  pinMode(ColdPump,        OUTPUT);
  pinMode(HotPump,         OUTPUT);
  pinMode(ColdIndicator,   OUTPUT);
  pinMode(HotIndicator,    OUTPUT);
  digitalWrite(HotPump,  LOW);
  digitalWrite(ColdPump, LOW);
  digitalWrite(Peltier0, LOW);
  digitalWrite(Peltier1, LOW);
  digitalWrite(ColdIndicator, LOW);
  digitalWrite(HotIndicator, LOW);
}

void loop() {
  coldWater.requestTemperatures();
  hotWater.requestTemperatures();
  coldCelcius = coldWater.getTempCByIndex(0);
  hotCelcius = hotWater.getTempCByIndex(0);
  bool water0 = detectWater0();
  bool water1 = detectWater1();

  if(water0 = false){
    while(water0 = false){
      digitalWrite(ColdPump, HIGH);
    }
  }
  else{
    digitalWrite(HotPump, LOW);
  }

    if(water1 = false){
    while(water1 = false){
      digitalWrite(HotPump, HIGH);
    }
  }
  else{
    digitalWrite(HotPump, LOW);
  }

  
  // Peltier
  if(coldCelcius <= 20.0 || hotCelcius >= 83.0){
    digitalWrite(Peltier0, LOW);
    digitalWrite(Peltier1, LOW);

  }

  else{
    digitalWrite(Peltier0, HIGH);
    digitalWrite(Peltier1, HIGH);
  }

  if(coldCelcius <= 20.0){
    digitalWrite(ColdIndicator, HIGH);
  } else {
    digitalWrite(ColdIndicator, LOW);
  }

  if(coldCelcius >= 83.0){
    digitalWrite(HotIndicator, HIGH);
  } else {
    digitalWrite(HotIndicator, LOW);
  }

  // Logging
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
  if(val >= 275){
    return true;
  }
  else{
    return false;
  }
}

bool detectWater1() {
  double val = analogRead(WaterSensor1);
  if(val >= 275){
    return true;
  }
  else{
    return false;
  }
}
