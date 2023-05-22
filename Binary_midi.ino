bool myByte[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int step = 0;

#define debug 0
#define zeropin 2
#define onepin 3
#define LED 5

unsigned long lastdb0 = 0;
unsigned long lastdb1 = 0;
int dbdelay = 150;
int midicommand = 0;
int midinote = 0;
int midivelocity = 0;

void setup() {

if(debug == 0)
{Serial.begin(31250);}
else
{Serial.begin(9600);}
  
pinMode(zeropin, INPUT_PULLUP);
pinMode(onepin, INPUT_PULLUP);
pinMode(LED, OUTPUT);

analogWrite(LED, 255);

attachInterrupt(digitalPinToInterrupt(zeropin), PRESSZERO, FALLING);
attachInterrupt(digitalPinToInterrupt(onepin), PRESSONE, FALLING);

}

void PRESSZERO()
{if((millis() - lastdb0) > dbdelay)
{
myByte[step]=0;
lastdb0 = millis();
press();
}}

void PRESSONE()
{if((millis() - lastdb0) > dbdelay)
{
myByte[step]=1;
lastdb0 = millis();
press();
}}

void press()
{
analogWrite(LED, 0);
step = step+1;
if(step == 8)
{analogWrite(LED, 20);
midicommand = myByte[7] + 2*myByte[6] + 4*myByte[5] + 8*myByte[4] 
+ 16*myByte[3] + 32*myByte[2] + 64*myByte[1] + 128*myByte[0];}
if(step == 16)
{analogWrite(LED, 20);
midinote = myByte[15] + 2*myByte[14] + 4*myByte[13] + 8*myByte[12] 
+ 16*myByte[11] + 32*myByte[10] + 64*myByte[9] + 128*myByte[8];}
if(step == 24)
{midivelocity = myByte[23] + 2*myByte[22] + 4*myByte[21] + 8*myByte[20] 
+ 16*myByte[19] + 32*myByte[18] + 64*myByte[17] + 128*myByte[16];
noteOn(midicommand, midinote, midivelocity);
step = 0;
}  
}

void loop() {


}

void noteOn(int cmd, int pitch, int velocity) {
 if(debug == 0) 
 {

  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);}
else
 {Serial.println(cmd);
  Serial.println(pitch);
  Serial.println(velocity);
  Serial.println();
 }
  analogWrite(LED, 255);

}