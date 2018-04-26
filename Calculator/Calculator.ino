int num1;
String op;
int num2;
int result;

void setup() 
{
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(Serial.available())
  {
    int num1 = Serial.parseInt();
    Serial.println(num1);
    
    while(!Serial.available())
    {
      delay(1000);
    }
    
    op = Serial.readString();
    Serial.println(op);
    
    while(!Serial.available())
    {
      delay(1000);
    }
    
    int num2 = Serial.parseInt();
    Serial.println(num2);

    if(op.equalsIgnoreCase("+"))
    {
      result = num1 + num2;
      Serial.println(result);
    }
    else if(op.equalsIgnoreCase("-"))
    {
      result = num1 - num2;
      Serial.println(result);
    }
    else if(op.equalsIgnoreCase("*"))
    {
      result = num1 * num2;
      Serial.println(result);
    }
    else if(op.equalsIgnoreCase("/"))
    {
      result = num1 / num2;
      Serial.println(result);
    }
    else
    {
      Serial.println("Unknown command!");
    }
  }
}
