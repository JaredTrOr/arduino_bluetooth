#include <SoftwareSerial.h>	// libreria que permite establecer pines digitales
				// para comunicacion serie

//MODULO BLUETOOTH
const int rxPin = 10;
const int txPin = 11;

//RGB PIN
const int redPin = 2;
const int greenPin = 3;
const int bluePin = 4;

SoftwareSerial miBT(rxPin, txPin); 	// pin 10 como RX, pin 11 como TX

void setup(){

  //Configuracion de modulo bluetooth
  Serial.begin(9600);		// comunicacion de monitor serial a 9600 bps
  miBT.begin(9600);
  
  Serial.println("Listo para conectar");		// comunicacion serie entre Arduino y el modulo a 38400 bps

  //Configuracion de led RGB
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  apagarLed();
}

void encenderLed() {
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
}

void cambiarColorLed(int value1, int value2, int value3) {
  analogWrite(redPin, value1);
  analogWrite(greenPin, value2);
  analogWrite(bluePin, value3);
}

void apagarLed() {
  analogWrite(redPin, 255);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 255);
}

void loop(){
  if (miBT.available()) {
    
    String data = miBT.readString();

    if (data == "1") {
      encenderLed();
    }
    else if (data == "0") {
      apagarLed();
    }

    else {
      int firstCommaIndex = data.indexOf(',');
      int secondCommaIndex = data.indexOf(',', firstCommaIndex + 1);
      
      // Extract the substrings and convert them to integers
      int value1 = data.substring(0, firstCommaIndex).toInt();
      int value2 = data.substring(firstCommaIndex + 1, secondCommaIndex).toInt();
      int value3 = data.substring(secondCommaIndex + 1).toInt();

      //int intensity = constrain(intensity,0 ,255);

      value1 = map(value1, 0, 255, 255, 0);
      value2 = map(value2, 0, 255, 255, 0);
      value3 = map(value3, 0, 255, 255, 0);
      
      // Print the values to the serial monitor for verification
      Serial.print("Value 1: ");
      Serial.println(value1);
      Serial.print("Value 2: ");
      Serial.println(value2);
      Serial.print("Value 3: ");
      Serial.println(value3);


      cambiarColorLed(value1, value2, value3);
    }
    
  }
    
  if (Serial.available()) { // si hay informacion disponible desde el monitor serial
      Serial.write("seriallll");
      miBT.write(Serial.read()); 	// lee monitor serial y envia a Bluetooth
  }   	
    

}
