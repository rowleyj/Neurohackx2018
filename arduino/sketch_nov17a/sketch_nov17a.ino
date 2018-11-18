/*
muse -> python -> arduino
*/

// Serial test script

void setup()
{

  Serial.begin(9600);  // initialize serial communications at 9600 bps
  pinMode(7, OUTPUT);//Right one
  pinMode(8, OUTPUT);//left one
  pinMode(3, OUTPUT);//null value
  pinMode(5, OUTPUT);//Right two
  pinMode(6, OUTPUT);//Left two
}

void loop()
{
  int running_avg = 0;  //reset running average
  while(!Serial.available()) {}

//  for(int i=0; i< 10; i++){
//    int input = Serial.read();
//    running_avg += i;
//  }
//  running_avg = running_avg;
char input = Serial.read();
Serial.print(input);
//blue is left
//right is green
  if(input == '1' ){ //RIGHT
        digitalWrite(8,LOW);
        digitalWrite(7, HIGH);
        Serial.println("Input of <10");
        tone(5, 750);
      }else if(input == '2'){ //LEFT
        digitalWrite(7,LOW);
        digitalWrite(8,HIGH);
        Serial.println("Input of >=10");
      }
      else if (input == '3'){
        digitalWrite(3,HIGH);
      }
      else if (input == '4'){ //LEFT
        digitalWrite(5,HIGH);
      }
      else if (input == '5'){ //RIGHT
        digitalWrite(6,HIGH);
      }
  delay(200);
  //set em all low
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(3, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  
  //Serial.flush();
}
