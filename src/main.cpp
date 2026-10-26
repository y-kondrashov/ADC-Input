#include <Arduino.h>
#include <iostream>

#define LED 17
#define LDR 2
#define N 4

const u16_t LDR_THRESHOLD = 2000;
u32_t adc_period = 10;
u32_t lastTimeChange = 0;
u16_t readings[N];
u16_t idx = 0;
u32_t sum = 0;

u16_t movingAvg(u16_t rawData)
{
  sum -= readings[idx];
  sum += rawData;
  readings[idx] = rawData;
  ++idx;

  if (idx >= N)
  {
    idx = 0;
  }

  return sum / N;
}

void filterInit(u16_t initData)
{
  for (u8_t i = 0; i < N; ++i)
  {
    readings[i] = initData;
    sum += initData;
  }
}

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(LDR, INPUT);
  Serial.begin(115200);
  Serial.println("setuped\n");
  filterInit(analogRead(LDR));
}

void loop()
{
  if (millis() - lastTimeChange > adc_period)
  {
    lastTimeChange = millis();
    u16_t adc_value = analogRead(LDR);
    u16_t filtered_adc_value = movingAvg(adc_value);
    std::cout << "adc raw value: " << adc_value << " | adc filtered: " << filtered_adc_value << std::endl;

    digitalWrite(LED, filtered_adc_value < LDR_THRESHOLD ? HIGH : LOW);

    // if(adc_value < LDR_THRESHOLD) {
    //  digitalWrite(LED, HIGH);
    // } else {
    //  digitalWrite(LED, LOW);
    // }
  }
}