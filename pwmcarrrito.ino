String strGeral, dispositivo, valorRecebido;
int estado = 0;
int control = 0;


int pwm_del = 2;
int pwm_tra = 3;
int atras = 4;
int adelante = 5;
int izquierda =6;
int derecha = 7;
#define PIN_TRIG 8
#define PIN_ECO  9
#define PIN_TRIG1 52
#define PIN_ECO1 53


int dimmer;

void setup () {
    Serial.begin(9600);
    pinMode(pwm_del,OUTPUT);
    pinMode(pwm_tra,OUTPUT); 
    pinMode(atras,OUTPUT);
    pinMode(adelante,OUTPUT);
    pinMode(izquierda,OUTPUT);
    pinMode(derecha,OUTPUT); 
    pinMode(PIN_TRIG,OUTPUT);
    pinMode(PIN_ECO,INPUT);
    pinMode(PIN_TRIG1,OUTPUT);
    pinMode(PIN_ECO1,INPUT);
    pinMode(11,INPUT);
    pinMode(12,OUTPUT);
}


void divideDados() {
    if (strGeral.indexOf(" ") >=0){
        dispositivo = strGeral.substring(0,(strGeral.indexOf(" ")));   
        valorRecebido = strGeral.substring(strGeral.indexOf(" ")+1);  
  }
}

void loop ()
{
    estado = digitalRead(11);   
  
  
   long duracion,distancia;
   long duracion1,distancia1;
   digitalWrite(PIN_TRIG,LOW); 
   delayMicroseconds(2);
   digitalWrite(PIN_TRIG,HIGH); 
   delayMicroseconds(10);
   digitalWrite(PIN_TRIG,LOW);
 
   duracion = pulseIn(PIN_ECO,HIGH);
   distancia = (duracion/2)/29; // es el sensor delantero del carrito
   delay(500);
   digitalWrite(PIN_TRIG1,LOW); 
   delayMicroseconds(2);
   digitalWrite(PIN_TRIG1,HIGH); 
   delayMicroseconds(10);
   digitalWrite(PIN_TRIG1,LOW);
 
   duracion1 = pulseIn(PIN_ECO1,HIGH);
   distancia1 = (duracion1/2)/29;//es el sensor derecho del carrito
   delay(500);
   Serial.print("Sensor Delantero: ");
   Serial.println(distancia);
   Serial.print("Sensor Derecho: ");
   Serial.println(distancia1);
   
   
   
  switch(estado)
  {
      case HIGH:
        digitalWrite(12,HIGH);
        if (distancia >=10){
            digitalWrite(atras,LOW);
            digitalWrite(adelante,HIGH);
        
    }
            else 
                if(distancia <10){
                     digitalWrite(atras,HIGH);
                     digitalWrite(adelante,LOW);
                   
    }
      break;
    
      case LOW: 
        digitalWrite(12,LOW);
        if (Serial.available())
   {
            Serial.println(strGeral);
            while (Serial.available()) {
                strGeral = strGeral + char(Serial.read());
                delay(1);
    }  
            divideDados();
            dimmer = valorRecebido.toInt();
            Serial.println("\nString Geral: " + strGeral);
            Serial.println("Dispositivo: " + dispositivo);
            Serial.println("Valor recebido: " + valorRecebido);  
            Serial.println(dimmer);
        
            if (strGeral == "1"){
               delay(50); 
               digitalWrite(adelante,HIGH);
               digitalWrite(atras,LOW);
               strGeral = "";
    }
            if (strGeral == "2"){
                delay(50);
                digitalWrite(atras,HIGH);
                digitalWrite(adelante,LOW);
                strGeral = "";
    }
            if (strGeral == "3"){
               delay(50);
               digitalWrite(derecha,HIGH);
               digitalWrite(izquierda,LOW);
               strGeral = "";
    }
            if (strGeral == "4"){
               delay(50);
               digitalWrite(izquierda,HIGH);
               digitalWrite(derecha,LOW); 
               strGeral = "";
    }
    
            if(strGeral == "5"){
               digitalWrite(atras,LOW);
               digitalWrite(adelante,LOW);
               digitalWrite(izquierda,LOW);
               digitalWrite(derecha,LOW);
               strGeral = "";
    }
    
            if (dispositivo == "Dimmer2"){
               analogWrite(pwm_tra, dimmer);
               strGeral ="";
     }
      break;
   }  
  }
}
