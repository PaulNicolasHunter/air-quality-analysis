 /* *-*- some definations *-* */
#define CALIBRATION_SAMPLES 100
#define CALIBRATION_INTERVAL 50
#define LOAD_RESISTANCE_VAL 5.0
#define GAS_RES_SAMPLE_VAL 50.0
#define GAS_RES_DELAY_VAL 5
#define CLEAN_AIR_FACTOR 9.83
#define TOTAL_GASES_IDENTIFY 3

// dust sensor contituents
int dust_in = A0;
int fan_out = A3;
int dust_led = 7;
float dust_read, dust_samp, dust_;
unsigned int delt_time = 40;

// gas sensor contituents
//int gas_sens = A6;
//float r0, ratio;
unsigned int sampling_time = 280;
unsigned int sleep_time = 9680;
int i;
void setup() {

  Serial.begin(9600);
  pinMode(dust_led, OUTPUT);
}

void loop() {

  dust_samp = read_dust();

  if (dust_samp >= 0.20) {
    analogWrite(fan_out, 255);
  }
  else {  
    analogWrite(fan_out, 0);

  }
    Serial.println(dust_samp);
  
//  delay(5000);  
  

}

/* Dust sensor reading */
float read_dust() {

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
