#include <ELECHOUSE_CC1101_SRC_DRV.h>
#define GDO0_PIN 2//pin to use it to capture the raw singal
#define BATCH_SIZE 120// Captures 30 Highs and 30 Lows

unsigned long batch[BATCH_SIZE];
int count = 0;
 
void setup() {
  Serial.begin(115200);
  //SPI pins setup
  ELECHOUSE_cc1101.setSpiPin(12, 13, 11, 10); //My ESP-32-S3 
//ELECHOUSE_cc1101.setSpiPin(18, 19, 23, 5);
  ELECHOUSE_cc1101.Init();
  ELECHOUSE_cc1101.setMHZ(433.92);
  ELECHOUSE_cc1101.setModulation(2);/// set modulation mode. 0 = 2-FSK, 1 = GFSK, 2 = ASK/OOK, 3 = 4-FSK, 4 = MSK.
  ELECHOUSE_cc1101.SetRx();
  pinMode(GDO0_PIN, INPUT);
  Serial.println("--- Batch High/Low Logger Ready ---");
}

void loop() {
  // 1. Capture a HIGH pulse
  unsigned long highDur = pulseIn(GDO0_PIN, HIGH, 1000000);
  
  if (highDur > 50) { //if Valid pulse detected
    // 2. Immediately capture the following LOW gap
    unsigned long lowDur = pulseIn(GDO0_PIN, LOW, 1000000);
    
    // Store them in the buffer
    batch[count] = highDur;
    batch[count + 1] = lowDur;
    count += 2;
  }

  // 3. Once the batch is full, print everything
  if (count >= BATCH_SIZE) {
    Serial.println("\n--- Captured Signal Snapshot ---");
    for (int i = 0; i < BATCH_SIZE; i += 2) {
      Serial.print("Step "); Serial.print(i/2);
      Serial.print(" -> HIGH: "); Serial.print(batch[i]);
      Serial.print(" | LOW: "); Serial.println(batch[i+1]);
      // This is to detect sync gap it's important to find this gap to analyze the signal.
      if (batch[i+1] > 5000) { 
        Serial.print(" <--- [SYNC GAP DETECTED]"); 
      }
      Serial.println();
    }



    Serial.println("---------------------------------");

    
    // 4. THE IMPORTANT DELAY: Gives you time to read
    Serial.println("Waiting 3 seconds before next capture...");
    delay(3000); 
    
    count = 0; // Reset for next capture
    Serial.println("Listening again...");
  }
}