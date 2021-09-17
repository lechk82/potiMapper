# potiMapper
A callback-based C++ Library to read potentiometer values through ADCs, map and forward them e.g as volume control.

Example:
```
// ADC properties
#define ADC_MIN 43
#define ADC_MAX 1023
#define ADC_THRESHOLD 4

// Mapping properties
#define GAIN_MIN 0.0f
#define GAIN_MAX 1.0f
#define OFFSET 0.0f

potiMapper* poti = new potiMapper();

// setup your callbacks

void read_poti(int *val){
  // read poti value
  *val = analogRead(A1);
  // Serial.println(*val); // uncomment for ADC_MIN, ADC_MAX determination (calibration)
}
void write_poti(float *val){
  // write mapped poti value, print for test
  Serial.println(*val);
}

void setup(){
  // init poti
  poti->init(   ADC_MIN,
                ADC_MAX,
                GAIN_MIN,
                GAIN_MAX,
                ADC_THRESHOLD,
                OFFSET,
                &read_poti,
                &write_poti);
}

void loop(){
  poti->update();
}
```
