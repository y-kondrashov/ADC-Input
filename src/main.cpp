#include <Arduino.h>
#include <iostream>
#include <iomanip>

#define LED 17
#define LDR 2

const u16_t LDR_THRESHOLD = 2500;
u32_t adc_period = 100;
u32_t adc_max = 4095;

u32_t lastTimeChange = 0;

float u_ref_v = 3.1; // 3100 мВ

float calcU(u16_t rawData)
{
  return ((float)rawData / adc_max) * u_ref_v;
}

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(LDR, INPUT);
  Serial.begin(115200);
  Serial.println("setuped\n");
}

void loop()
{
  if (millis() - lastTimeChange > adc_period)
  {
    lastTimeChange = millis();
    u16_t adc_value = analogRead(LDR);
    uint32_t u_measured_mv = analogReadMilliVolts(LDR);
    float u_calc = calcU(adc_value);
    std::cout << "ADC raw value: " << adc_value << " | U calculated: " << std::fixed << std::setprecision(2) << u_calc << "V | Read millivolts: " << u_measured_mv << std::endl;

    digitalWrite(LED, adc_value < LDR_THRESHOLD ? HIGH : LOW);
  }
}