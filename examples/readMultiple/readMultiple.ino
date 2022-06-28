#include <HX711_asukiaaa.h>

int pinsDout[] = {5, 6, 7, 8};
const int numPins = sizeof(pinsDout) / sizeof(pinsDout[0]);
int pinSlk = 4;
HX711_asukiaaa::Reader reader(pinsDout, numPins, pinSlk);

//---------------------------------------------------//
// Load cell SC301A 100kg
// https://akizukidenshi.com/catalog/g/gP-12036/
//---------------------------------------------------//
// #define LOAD_CELL_RATED_VOLT 0.002f
// #define LOAD_CELL_RATED_GRAM 100000.0f

//---------------------------------------------------//
// Load cell SC601 120kg
// https://akizukidenshi.com/catalog/g/gP-12035/
//---------------------------------------------------//
#define LOAD_CELL_RATED_VOLT 0.002f
#define LOAD_CELL_RATED_GRAM 120000.0f

//---------------------------------------------------//
// Load cell SC133 20kg
// https://akizukidenshi.com/catalog/g/gP-12034/
//---------------------------------------------------//
// #define LOAD_CELL_RATED_VOLT 0.002f
// #define LOAD_CELL_RATED_GRAM 20000.0f

//---------------------------------------------------//
// Load cell SC133 2kg
// https://akizukidenshi.com/catalog/g/gP-13041/
//---------------------------------------------------//
// #define LOAD_CELL_RATED_VOLT 0.001f
// #define LOAD_CELL_RATED_GRAM 2000.0f

//---------------------------------------------------//
// Load cell SC616C 500g
// https://akizukidenshi.com/catalog/g/gP-12532/
//---------------------------------------------------//
// #define LOAD_CELL_RATED_VOLT 0.0008f
// #define LOAD_CELL_RATED_GRAM 500.0f

//---------------------------------------------------//
// Resistors for HX711 module AE-HX711-SIP
// https://akizukidenshi.com/catalog/g/gK-12370/
//---------------------------------------------------//
#define HX711_R1 20000.0
#define HX711_R2 8200.0

HX711_asukiaaa::Parser parser(LOAD_CELL_RATED_VOLT, LOAD_CELL_RATED_GRAM,
                              HX711_R1, HX711_R2);
float offsetGrams[numPins];

void setup() {
  Serial.begin(115200);
  Serial.println("start");
  reader.begin();
  for (int i = 0; i < reader.doutLen; ++i) {
    offsetGrams[i] = parser.parseToGram(reader.values[i]);
  }
}

void loop() {
  auto readState = reader.read();
  Serial.println("ReadState: " + HX711_asukiaaa::getStrOfReadState(readState));
  if (readState == HX711_asukiaaa::ReadState::Success) {
    for (int i = 0; i < reader.doutLen; ++i) {
      float gram = parser.parseToGram(reader.values[i]) - offsetGrams[i];
      Serial.print("sensor" + String(i) + ": " + String(gram / 1000) + " kg ");
      Serial.print("offset: " + String(offsetGrams[i]) + " g ");
      Serial.print("voltage: " +
                   String(parser.parseToMicroVolt(reader.values[i])) + " uV ");
      Serial.print(String(parser.parseToMicroVolt(reader.values[i]) / 1000) +
                   " mV ");
      Serial.println("");
    }
    Serial.println("at " + String(millis()));
    Serial.println("");
  }
  delay(1000);
}
