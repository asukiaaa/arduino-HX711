#ifndef _HX711_ASUKIAAA_H_
#define _HX711_ASUKIAAA_H_

#include <Arduino.h>

namespace HX711_asukiaaa {
  enum Error {
    timeout = 1,
  };

  class Parser {
  public:
    Parser(float ratedVoltage, float ratedGram, float r1, float r2);
    float parseToGram(int32_t raw);
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
    Reader(int* pinsDout, int doutLen, int pinSlk);
    ~Reader();
    void begin();
    void reset();
    int read(int sumNumber = 10);

    int32_t* values;
    const int doutLen;
  private:
    const int* pinsDout;
    const int pinSlk;

    int readRawOnce(int32_t* readValues, unsigned long timeout = 50UL);
    bool pinsAreReady();
  };
}

#endif
