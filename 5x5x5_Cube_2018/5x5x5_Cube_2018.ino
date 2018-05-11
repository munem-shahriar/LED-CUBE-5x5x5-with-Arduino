/*
 * 5x5x5 LED Cube (mono-color)
 * Made by Sarowar & Munem Shahriar
 * Department of CSE, University of Rajshahi
 * 12 October, 2016
 * cube made of 125 LEDs
 * we used only 30 input lines to control each of 125 leds
 * Arduino mega was used for the project, and 5 transistors (2N-2222)
 */

//column=piller=col and layer=row

int col[]={22,24,26,28,30, 
           32,34,36,38,40,
           42,44,46,48,50,
           23,25,27,29,31,
           33,35,37,39,41};
//column pins supply power to leds
//see those pin numbers in Arduino mega to understand           
          
int row[] = {2,3,4,5,6};
//row pins activate the transistors to let the GND pass

int i,j;  
int k;
//i increments row, j increments column





//now initializing all pins as output
void setup()   
{
  for(i=0;i<5;i++)
  {
    pinMode(row[i], OUTPUT); 
    //set layers or rows as output
  }

  for(j=0;j<25;j++)
  {
      pinMode(col[j], OUTPUT); 
      //set pillers or columns as output
  }
}





void loop()
{
// things in this loop runs forever
  

//Animation 1a

k=0;
while(k<5)
{
  lightAll();
  delay(200);
  offAll();
  delay(200);
  k = k+1;
}

k=0;
while(k<20)
{
  lightAll();
  delay(15);
  offAll();
  delay(15);
  k = k+1;
}

  delay(200);
  
//Animation 2
k=0;
while(k<5)
{
  lightAll();
  delay(200);
  
  off1Layer(1);
  delay(100);
  
  off1Layer(2);
  delay(100);
  
  off1Layer(3);
  delay(100);

  off1Layer(4);
  delay(100);
  off1Layer(5);
  delay(1000);

//now reverse
 lightAll();
 delay(500);
  
  off1Layer(5);
  delay(100);
  
  off1Layer(4);
  delay(100);
  
  off1Layer(3);
  delay(100);

  off1Layer(2);
  delay(100);
  off1Layer(1);
  delay(100);
  k = k + 1;
}


//Animation 3
for(k=0;k<5; k++)
{
  //light1by1(10);
  offAll();
  delay(100);
  //light1by1(20);
  delay(100);
  light1byAll(5);
  off1byAll(150);
}

//Animation 4

  for(j=1;j<25;j+3)
  {
    light1Column(j);
    delay(10);
    off1Column(j);
  }


  for(j=2;j<25;j+3)
  {
    light1Column(j);
    delay(10);
    off1Column(j);
  }

  for(j=3;j<25;j+3)
  {
    light1Column(j);
    delay(10);
    off1Column(j);
  }

/*
// Animation 5

  for(j=0;j<=16;j++)
  {
    light1Column(j+1);
    //j+1, because we have written col[column_number-1]
    //in the defination of function light1Column()
    //and to keep proper array index
  }
  delay(50);
  offAll();


  for(j=17;j<=24;j++)
  {
    light1Column(j+1);
  }
  delay(50);
  offAll();

  
  light1Column(25);
  delay(50);
  offAll();

 light1Column(25);



// Animation 6




*/

}



/***********************************************
 definations of custom made functions below:

*       *
* *   * *
*   *   *
*       *
*       *
 
 ***********************************************/



//turn on LED based on row number and column number
void ledOn(int row_number, int col_number)
{
  digitalWrite(row_number, HIGH); //turn on row
  digitalWrite(col_number, HIGH); //turn on col
  
}

//overload funtion -used to turn LED on with certain intensity
void ledOn(int row_number, int col_number, int value)
{
  digitalWrite(row_number, HIGH); //turn on row
  analogWrite(col_number, value); //turn on col
}


//turn off LED based on row number and column number
void ledOff(int row_number, int col_number){
  digitalWrite(row_number, LOW); //turn off row
  digitalWrite(col_number, LOW); //turn off col
}



// this will light leds 1 by 1, 
//i.e. one on one off,again another on,previous one off
void light1by1(int delay_time)
{ 
    for(i=0;i<25;i++)
    { 
        for(j=0;j<25;j++)
        {
           ledOn(row[i], col[i]);
           // calling a func with parameters
           delay( delay_time );
           ledOff(row[i], col[i]);
        }                            
    }
}



//this is same as light1bt1()
//but this time no turn Off
void light1byAll(int delay_time)
{ 
    for(i=0;i<25;i++)
    { 
        for(j=0;j<25;j++)
        {
           ledOn(row[i], col[i]);
           // calling a func with parameters
           delay( delay_time );
        }                            
  }
}



//this is same as light1byAll()
//but this will turn them off serially
void off1byAll(int delay_time)
{  
  for(j=0;j<25;j++)
  {
      digitalWrite(col[j], LOW);
      delay(delay_time);
  }

  for(i=0;i<5;i++)
  {
    digitalWrite(row[i], LOW);
  }
}



//this turns ON all at once
void lightAll()
{ 
    for(i=0;i<25;i++)
    { 
        for(j=0;j<25;j++)
        {
           ledOn(row[i], col[i]);
        }                            
  }
}



//this turns OFF all at once
void offAll()
{ 
    for(i=0;i<5;i++)
    { 
        for(j=0;j<25;j++)
        {
           ledOff(row[i], col[i]);
        }                            
  }
}


//this turns a whole layer ON
void light1Layer(int layer_number)
{    
        digitalWrite(row[layer_number-1], HIGH);
 
        for(j=0;j<25;j++)
        {
           digitalWrite(col[j], HIGH);
        }                            
}



//this turns a whole layer OFF
void off1Layer(int layer_number)
{    
        digitalWrite(row[layer_number-1], LOW);
// -1 used, because array index starts from row[0]
//but in the cube row[0]= layer number 1                        
}



//this turns a whole column or piller ON
void light1Column(int column_number)
{    
        digitalWrite(col[column_number-1], HIGH);
// -1 used, because array index starts from col[0]
//but in the cube col[0]= column or piller number 1
        for(i=0;i<5;i++)
        {
           digitalWrite(row[i], HIGH);
        }                            
}



//this turns a whole column or piller OFF
void off1Column(int column_number)
{    
        digitalWrite(col[column_number-1], LOW);
// to turn a colum of, you need not turn the rows off
// compare light1Column() vs off1Column() 
}




