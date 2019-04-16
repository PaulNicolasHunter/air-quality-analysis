/* *-*- some definations *-* */
#define CALIBRATION_SAMPLES 100
#define CALIBRATION_INTERVAL 50
#define LOAD_RESISTANCE_VAL 5.0
#define GAS_RES_SAMPLE_VAL 50.0
#define GAS_RES_DELAY_VAL 5
#define CLEAN_AIR_FACTOR 9.83
#define TOTAL_GASES_IDENTIFY 3
``

// dust sensor contituents
int dust_in = A0;
int fan_out = A5;
int dust_led = 7;
float dust_read, dust_samp, dust_;
unsigned int delt_time = 40;

// gas sensor contituents
int gas_sens = A2;
float r0, ratio;
unsigned int sampling_time = 280;
unsigned int sleep_time = 9680;
char *gases[TOTAL_GASES_IDENTIFY] = {"LPG", "CO", "Smoke"};
float gas_curve_data[TOTAL_GASES_IDENTIFY][3] = {{2.3, 0.21, -0.47}, {2.3, 0.72, -0.34}, {2.3, 0.53, -0.44}}; // points are taken from the curve.

// code serving constituents
int i;
float cali_point_val = 0.0;
char *data;
struct gas_reads {

  char *gas[TOTAL_GASES_IDENTIFY];
  float reading[TOTAL_GASES_IDENTIFY];

} air_;

void setup() {

  Serial.begin(9600);
  Serial.write("Calibrating...");
  pure_air_read_calibration();
  pinMode(dust_led, OUTPUT);
}

void loop() {

  dust_samp = read_dust();
  ratio = gaseous_air_res_samples();
  gas_digest(ratio);
  
  Serial.println(dust_samp);
  
  if (dust_samp >= 0.10) {
    analogWrite(fan_out, 255);
  } else {
    analogWrite(fan_out, 0);
  }

  /*
    gpio logic goes here
  */

    Serial.println("{\"dust\":" + String(dust_samp) + ",\"0\":{\"gas\":" + String(air_.gas[0]) + ",\"reading\":" + String(air_.reading[0]) + "},\"1\":{\"gas\":" + String(air_.gas[1]) + ",\"reading\":" + String(air_.reading[1]) + "},\"2\":{\"gas\":" + String(air_.gas[2]) + ",\"reading\":" + String(air_.reading[2]) + "}}");
}

/* Dust sensor reading */
float read_dust() {
  /* *-*
    The LED control pin (pin 3 on the SHARP dust sensor module) is active low.
    This means that a LOW ( 0V ) value will turn the LED on and a HIGH ( VCC ) value will turn the LED off.
    -** */

  digitalWrite(dust_led, LOW); // turning the led to ACTIVE HIGH
  delayMicroseconds(sampling_time); // delay for pulse mapping [1]

  dust_read = analogRead(dust_in); // read the dust measurement

  delayMicroseconds(delt_time); //[1]
  digitalWrite(dust_led, HIGH); // turning the sensing IR led to LOW
  delayMicroseconds(sleep_time); // [1]
  dust_read = dust_read * (5.0 / 1024.0); // mapped 5 voltage values to 1023 integer value
  dust_read = (dust_read * 0.17) - 0.1;

  delay(500);
  return dust_read;
}

/* gas sensor reading and identification */
float pure_air_read_calibration() {
  for (i = 0; i < CALIBRATION_SAMPLES; i++ ) {

    cali_point_val += calibrate_current_reading(analogRead(gas_sens));
    delay(CALIBRATION_INTERVAL);
  }

  r0 = cali_point_val / CALIBRATION_SAMPLES;
  r0 = r0 / CLEAN_AIR_FACTOR;
}

float calibrate_current_reading(float raw_read) {

  raw_read = raw_read * (LOAD_RESISTANCE_VAL / 1024.0);

  return ((float)LOAD_RESISTANCE_VAL - raw_read) / raw_read;
}

float gaseous_air_res_samples() {

  for (i = 0; i < GAS_RES_SAMPLE_VAL; i++) {
    cali_point_val += calibrate_current_reading(analogRead(gas_sens));
    delay(GAS_RES_DELAY_VAL);
  }
  return (cali_point_val / GAS_RES_SAMPLE_VAL) / r0;
}

float gas_digest(float ratios) {
  for (i = 0; i < TOTAL_GASES_IDENTIFY; i++) {
    air_.gas[i] = gases[i];
    air_.reading[i] = gas_percent(ratios, gas_curve_data[i]);
  }
}

float gas_percent(float ratios, float *line_curve) {
  return pow(10, ( ((log(ratios) - line_curve[1]) / line_curve[2]) + line_curve[0]));
}
