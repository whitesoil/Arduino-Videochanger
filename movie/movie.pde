import processing.video.*;
import processing.serial.*;
Serial myPort;  // Create object from Serial class
int flag;      //for synchronization
int serial; // Data received from the serial port
Movie first,menu,material1,material2,last;

/*
* Before start, you should close serial monitor in arduino.
*/

void setup()
{
    serial = 0;
    flag = 0;
    
    fullScreen();
    first = new Movie(this, "./first.mp4");
    menu = new Movie(this, "./menu.mov");
    material1 = new Movie(this, "./material1.mov");
    material2 = new Movie(this, "./material2.mov");
    last = new Movie(this, "./last.mp4");
    first.loop();
    menu.loop();
    material1.loop();
    material2.loop();
    last.loop();
    
    imageMode(CENTER);
    image(first,displayWidth/2,displayHeight/2,900,900);
    first.play();
    /*
    * You should change Serial port of Serial.list()[NUMBER] by check print(Serial.list());
    *  Which is what you use in arduino.
    *  println(Serial.list());
    */
    String portName = Serial.list()[11];
    println(portName);
    myPort = new Serial(this, portName, 115200);
}
void movieEvent(Movie m)
{
  m.read();
}

void draw()
{
   imageMode(CENTER);
   background(0);

   if (flag == 0) {
    image(first,displayWidth/2,displayHeight/2,900,900);
  } else if(flag == 1){
    image(menu,displayWidth/2,displayHeight/2,900,900);
  }else if(flag == 2){
    image(material1,displayWidth/2,displayHeight/2,900,900);
  }else if(flag ==3){
    image(material2,displayWidth/2,displayHeight/2,900,900);
  }else if(flag == 4){
    image(last,displayWidth/2,displayHeight/2,900,900);
  }
  
  if ( myPort.available() > 0) {  // If data is available,
    serial = myPort.read();         // read it and store it in val
    //println(serial);
  }
  if (serial == 101 && flag == 0) {
    card_interrupt();
    
  }else if(serial == 121 && flag == 1){
    card_interrupt();
    
  }else if(serial == 151 && flag == 2){
    card_interrupt();
    
  }else if(serial == 251 && flag == 3){
    card_interrupt();
    
  }else if(serial == 241 && flag == 4){
    card_interrupt();
  }
}

void card_interrupt(){
   if (flag == 0) {
    menu.stop();
    menu.play();
    flag = 1;
  } else if(flag == 1){
    material1.stop();
    material1.play();
    flag = 2;
  }else if(flag == 2){
    material2.stop();
    material2.play();
    flag = 3;
  }else if(flag == 3){
    last.stop();
    last.play();
    flag = 4;
  }else if(flag == 4){
    first.stop();
    first.play();
    flag = 0;
  }
}