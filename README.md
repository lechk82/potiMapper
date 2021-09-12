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
#define OFFSET1 0.0f

potiMapper* poti0 = new potiMapper();

// setup your callbacks

void read_poti0(int *val){
  // read poti value
  *val = analogRead(A1);
}
void write_poti0(float *val){
  // write poti value, print for test
  Serial.println(*val);
}

void setup(){

  //init poti
  poti0->init(  ADC_MIN,
                ADC_MAX,
                GAIN_MIN,
                GAIN_MAX,
                ADC_TH,
                OFFSET1,
                &read_poti0,
                &write_poti0);

}

void loop(){
  poti0->update();
}
```
