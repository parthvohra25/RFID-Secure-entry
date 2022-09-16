
/* Arduino Simple RFID Access Control
  Using EM-18 RFID Reader Module
  Prefatory Code For Novices
  An inspired design. Thanks to Internet!
  T.K.Hareendran
  Project designed & tested at TechNode on 17.02.2014
  https://www.electroschematics.com */

#define RELAYPIN 13
#define WARNLEDPIN 12

char tag[] = "51005F46642C"; // Replace with your own Tag ID
char input[12]; // A variable to store the Tag ID being presented
int count = 6; // A counter variable to navigate through the input[] character
boolean flag = 0;// A variable to store the Tag match status
void setup()
{
  Serial.begin(9600);           // Initialise Serial Communication with the Serial Monitor
  pinMode(RELAYPIN, OUTPUT);    // RELAY OUTPUT
  pinMode(WARNLEDPIN, OUTPUT); //WRONG TAG INDICATOR
}

void loop()
{
  if (Serial.available()) // Check if there is incoming data in the RFID Reader Serial Buffer.
  {
    count = 0; // Reset the counter to zero
    /* Keep reading Byte by Byte from the Buffer till the RFID Reader Buffer is
      or till 12 Bytes (the ID size of our Tag) is read */
    while (Serial.available() && count < 12)
    {
      input[count] = Serial.read(); // Read 1 Byte of data and store it in the input!
      count++; // increment counter
      delay(5);
    }
    if (count == 12) //
    {
      count = 0; // reset counter varibale to 0
      flag = 1;
      /* Iterate through each value and compare till either the 12 values are
        all matching or till the first mistmatch occurs */

      while (count < 12 && flag != 0)
      {
        if (input[count] == tag[count])
          flag = 1;
        else
          flag = 0;
        /*if the ID values don't match, set flag variable to 0
          and stop comparing by exiting the while loop */
        count++; // increment i
      }
    }

    if (flag == 1) // If flag variable is 1, then it means the tags match
    {
      Serial.println("Access Allowed!");
      digitalWrite(RELAYPIN, HIGH);
      delay(5000);
      digitalWrite (RELAYPIN, LOW);
    }
    else
    {
      Serial.println("Access Denied"); // Incorrect Tag Message
      digitalWrite(WARNLEDPIN, HIGH);
      delay(5800);
      digitalWrite(WARNLEDPIN, HIGH);
    }

    /* Fill the input variable array with a fixed value 'F' to overwrite all values getting it empty for the next read cycle */
    for (count = 0; count < 12; count++)
    {
      for (count = 0; count < 12; count++)
      {
        input[count] = 'F';
      }
      count = 0; //Reset Counter Variable
    }
  }
}
