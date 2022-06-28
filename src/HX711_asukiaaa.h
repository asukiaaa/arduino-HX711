#ifndef _HX711_ASUKIAAA_H_
#define _HX711_ASUKIAAA_H_

#include <Arduino.h>

namespace HX711_asukiaaa {
enum ReadState {
  Success = 0,
  Timeout = 1,
};

String getStrOfReadState(int state);
String getStrOfReadState(ReadState state);

class Parser {
 public:
  Parser(float ratedVoltage, float ratedGram, float r1, float r2);
  float parseToGram(int32_t raw);
  float parseToMicroVolt(int32_t raw);
  // float offsetGram;
 private:
  // const float ratedVoltage;
  // const float ratedGram;
  // const float r1;
  // const float r2;
  const float avdd;
  const float adc1bit;
  const float scale;
};

class Reader {
 public:
  Reader(const int* pinsDout, int doutLen, int pinSlk);
  ~Reader();
  void begin();
  void beginWighoutInitialRead();
  void reset();
  ReadState read(int sumNumber = 10);

  int32_t* values;
  const int doutLen;

 private:
  const int* pinsDout;
  const int pinSlk;

  ReadState readRawOnce(int32_t* readValues, unsigned long timeout = 100UL);
  bool pinsAreReady();
};

}  // namespace HX711_asukiaaa

#endif
