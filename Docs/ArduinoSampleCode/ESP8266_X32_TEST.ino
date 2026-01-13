/*
  File Name: ESP8266_X32_TEST.ino
  Function: All relays turn on in sequence and then turn off in sequence
  Development Environment: VS Code with PlatformIO
  Note: Clone the entire project to your local machine. If you don't have the required environment set up,
        you can use this sample code in Docs/ArduinoSampleCode.
*/
#define    HC595_SI_PIN     14
#define    HC595_SCK_PIN    13
#define    HC595_RCK_PIN    12
#define    HC595_G_PIN    5


void HC595Init(void)
{
 pinMode(HC595_SI_PIN,  OUTPUT);      // Output Mode  
 pinMode(HC595_SCK_PIN, OUTPUT);      // Output Mode
 pinMode(HC595_RCK_PIN, OUTPUT);      // Output Mode
 pinMode(HC595_G_PIN,   OUTPUT);      // Output Mode
 digitalWrite(HC595_G_PIN, HIGH);
 digitalWrite(HC595_SI_PIN, LOW);
 digitalWrite(HC595_SCK_PIN,LOW);
 digitalWrite(HC595_RCK_PIN,LOW);
}

void HC595SendData(unsigned long OutData)
{
    unsigned char i; // Temporary variable for data sending loop
    for (i = 0; i < 32; i++) // Send 32-bit data bit by bit
    {
        digitalWrite(HC595_SCK_PIN,LOW);  // Clock line low
    if ((OutData & 0x80000000) == 0x80000000) // Check data high/low bit
    {
        digitalWrite(HC595_SI_PIN,HIGH); // Send high bit data
    }
    else
    {
        digitalWrite(HC595_SI_PIN,LOW); // Send low bit data
    }
    OutData = OutData << 1; // Shift data left by 1 bit
    digitalWrite(HC595_SCK_PIN,HIGH);  // Clock line high
    }
    // Output data on rising edge
    digitalWrite(HC595_RCK_PIN,LOW);
    digitalWrite(HC595_RCK_PIN,HIGH);
    digitalWrite(HC595_G_PIN,LOW);
}

unsigned long relay_data = 0x00000000;  // Define a variable for relay current status
void RelayON(unsigned int number)
{
  switch(number)
  {
    case 1  : relay_data = relay_data | 0x00000001; break;
    case 2  : relay_data = relay_data | 0x00000002; break;
    case 3  : relay_data = relay_data | 0x00000004; break;
    case 4  : relay_data = relay_data | 0x00000008; break;
    case 5  : relay_data = relay_data | 0x00000010; break;
    case 6  : relay_data = relay_data | 0x00000020; break;
    case 7  : relay_data = relay_data | 0x00000040; break;
    case 8  : relay_data = relay_data | 0x00000080; break;
    case 9  : relay_data = relay_data | 0x00000100; break;
    case 10 : relay_data = relay_data | 0x00000200; break;
    case 11 : relay_data = relay_data | 0x00000400; break;
    case 12 : relay_data = relay_data | 0x00000800; break;
    case 13 : relay_data = relay_data | 0x00001000; break;
    case 14 : relay_data = relay_data | 0x00002000; break;
    case 15 : relay_data = relay_data | 0x00004000; break;
    case 16 : relay_data = relay_data | 0x00008000; break;
    case 17 : relay_data = relay_data | 0x00010000; break;
    case 18 : relay_data = relay_data | 0x00020000; break;
    case 19 : relay_data = relay_data | 0x00040000; break;
    case 20 : relay_data = relay_data | 0x00080000; break;
    case 21 : relay_data = relay_data | 0x00100000; break;
    case 22 : relay_data = relay_data | 0x00200000; break;
    case 23 : relay_data = relay_data | 0x00400000; break;
    case 24 : relay_data = relay_data | 0x00800000; break;
    case 25 : relay_data = relay_data | 0x01000000; break;
    case 26 : relay_data = relay_data | 0x02000000; break;
    case 27 : relay_data = relay_data | 0x04000000; break;
    case 28 : relay_data = relay_data | 0x08000000; break;
    case 29 : relay_data = relay_data | 0x10000000; break;
    case 30 : relay_data = relay_data | 0x20000000; break;
    case 31 : relay_data = relay_data | 0x40000000; break;
    case 32 : relay_data = relay_data | 0x80000000; break;
    default : break;
  }
  HC595SendData(relay_data);
}
void RelayOFF(unsigned int number)
{
  switch(number)
  {
    case 1  : relay_data = relay_data & 0xFFFFFFFE; break;
    case 2  : relay_data = relay_data & 0xFFFFFFFD; break;
    case 3  : relay_data = relay_data & 0xFFFFFFFB; break;
    case 4  : relay_data = relay_data & 0xFFFFFFF7; break;
    case 5  : relay_data = relay_data & 0xFFFFFFEF; break;
    case 6  : relay_data = relay_data & 0xFFFFFFDF; break;
    case 7  : relay_data = relay_data & 0xFFFFFFBF; break;
    case 8  : relay_data = relay_data & 0xFFFFFF7F; break;
    case 9  : relay_data = relay_data & 0xFFFFFEFF; break;
    case 10 : relay_data = relay_data & 0xFFFFFDFF; break;
    case 11 : relay_data = relay_data & 0xFFFFFBFF; break;
    case 12 : relay_data = relay_data & 0xFFFFF7FF; break;
    case 13 : relay_data = relay_data & 0xFFFFEFFF; break;
    case 14 : relay_data = relay_data & 0xFFFFDFFF; break;
    case 15 : relay_data = relay_data & 0xFFFFBFFF; break;
    case 16 : relay_data = relay_data & 0xFFFF7FFF; break;
    case 17 : relay_data = relay_data & 0xFFFEFFFF; break;
    case 18 : relay_data = relay_data & 0xFFFDFFFF; break;
    case 19 : relay_data = relay_data & 0xFFFBFFFF; break;
    case 20 : relay_data = relay_data & 0xFFF7FFFF; break;
    case 21 : relay_data = relay_data & 0xFFEFFFFF; break;
    case 22 : relay_data = relay_data & 0xFFDFFFFF; break;
    case 23 : relay_data = relay_data & 0xFFBFFFFF; break;
    case 24 : relay_data = relay_data & 0xFF7FFFFF; break;
    case 25 : relay_data = relay_data & 0xFEFFFFFF; break;
    case 26 : relay_data = relay_data & 0xFDFFFFFF; break;
    case 27 : relay_data = relay_data & 0xFBFFFFFF; break;
    case 28 : relay_data = relay_data & 0xF7FFFFFF; break;
    case 29 : relay_data = relay_data & 0xEFFFFFFF; break;
    case 30 : relay_data = relay_data & 0xDFFFFFFF; break;
    case 31 : relay_data = relay_data & 0xBFFFFFFF; break;
    case 32 : relay_data = relay_data & 0x7FFFFFFF; break;
    default : break;
  }
  HC595SendData(relay_data);
}

void setup() 
{
  HC595Init();
//  HC595SendData(0x0000);  // Turn off all relays on power up
}

void loop() 
{
  RelayON(1); delay(100);

  RelayON(2); delay(100);

  RelayON(3); delay(100);
  
  RelayON(4); delay(100);
  
  RelayON(5); delay(100);
  
  RelayON(6); delay(100);
  
  RelayON(7); delay(100);
  
  RelayON(8); delay(100);
  
  RelayON(9); delay(100);
  
  RelayON(10); delay(100);
  
  RelayON(11); delay(100);
  
  RelayON(12); delay(100);
  
  RelayON(13); delay(100);
  
  RelayON(14); delay(100);
  
  RelayON(15); delay(100);
  
  RelayON(16); delay(100);

  RelayON(17); delay(100);

  RelayON(18); delay(100);

  RelayON(19); delay(100);

  RelayON(20); delay(100);

  RelayON(21); delay(100);

  RelayON(22); delay(100);

  RelayON(23); delay(100);

  RelayON(24); delay(100);

  RelayON(25); delay(100);

  RelayON(26); delay(100);

  RelayON(27); delay(100);

  RelayON(28); delay(100);

  RelayON(29); delay(100);

  RelayON(30); delay(100);

  RelayON(31); delay(100);

  RelayON(32); delay(100);

  
  RelayOFF(1); delay(100);

  RelayOFF(2); delay(100);

  RelayOFF(3); delay(100);
  
  RelayOFF(4); delay(100);
  
  RelayOFF(5); delay(100);
  
  RelayOFF(6); delay(100);
  
  RelayOFF(7); delay(100);
  
  RelayOFF(8); delay(100);
  
  RelayOFF(9); delay(100);
  
  RelayOFF(10); delay(100);
  
  RelayOFF(11); delay(100);
  
  RelayOFF(12); delay(100);
  
  RelayOFF(13); delay(100);
  
  RelayOFF(14); delay(100);
  
  RelayOFF(15); delay(100);
  
  RelayOFF(16); delay(100);

  RelayOFF(17); delay(100);
  
  RelayOFF(18); delay(100);
  
  RelayOFF(19); delay(100);
  
  RelayOFF(20); delay(100);
  
  RelayOFF(21); delay(100);
  
  RelayOFF(22); delay(100);
  
  RelayOFF(23); delay(100);
  
  RelayOFF(24); delay(100);

  RelayOFF(25); delay(100);
  
  RelayOFF(26); delay(100);
  
  RelayOFF(27); delay(100);
  
  RelayOFF(28); delay(100);
  
  RelayOFF(29); delay(100);
  
  RelayOFF(30); delay(100);
  
  RelayOFF(31); delay(100);
  
  RelayOFF(32); delay(100);
}
