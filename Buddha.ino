const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
int lastVolt;
int state = 0;
int lastState = 0;
int onoff = 0;
int piezoPin = 12;


void setup() 
{
   Serial.begin(115200);

}
 
 
void loop() 
{

  unsigned long startMillis= millis();  // Start of sample window
  unsigned int peakToPeak = 0;   // peak-to-peak level
 
  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;
 
   // collect data for 50 mS
  while (millis() - startMillis < sampleWindow)
  {
      sample = analogRead(0);
      if (sample < 1024)  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
      }
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
   double volts = (peakToPeak * 5.0) / 1024;  // convert to volts

//0 off, 1 on
   
   if (volts != lastVolt){
    lastVolt = volts;
    if (volts > 10){
      volts = 0;
    }
    if (volts >= 4.5 && volts <= 5){
      state = state + 1;
    }


      
//    if (state = 1 && volts >= 3 && volts <= 5){
//      state = 0;
//      Serial.print("off");  
//    }
//    Serial.println(counter);
   }
   if (state != lastState){
      lastState = state;
      Serial.print("ON/OFF? ");      
      Serial.println(onoff);
      if ( (state % 2) == 0) { 
        onoff = 0;  
        tone(piezoPin, 800, 600);
        delay(100);
        tone(piezoPin, 900, 800);
        delay(4000);


        } 
      else { 
        onoff = 1;
        tone(piezoPin, 500, 400);
        delay(200);
        tone(piezoPin, 300, 400);
        delay(200);
        tone(piezoPin, 200, 500);
        delay(200);
        tone(piezoPin, 100, 700);
        delay(4000);
      }
   }
}

