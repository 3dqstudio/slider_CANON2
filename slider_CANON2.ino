int  ledon = 3; //LED de encendido en pin 3
int ledoff = 5; //LED de apagado en pin 5
int   strt = 4; //BOTON de arranque en pin 4
int    stp = 0; //INTERRUPCION de paro en pin 2
int  motor = 6; //Motor en pin 6
int     go = 0; //variable avance
int      i = 0; //variable i para 'for'
int shutter= 8; //Activa shutter
int  focus = 7; //Activa el auto focus

//---------------------TIEMPO A MODIFICAR-------------------------//
float    segundos =  3; //SEGUNDOS que quieres que espere entre fotos + tiempo para focus
float     t_motor =  0.1; //SEGUNDOS que quieres para avance
  int     t_focus =   5; //SEGUNDOS que quieres para focus
  int focus_state =    1; //1 para focus ON, 0 para focus OFF
float     tiempos =    1; //SEGUNDOS de espera despues de shutter
//----------------------------------------------------------------//
unsigned long       TimerA;                   //Timer de arranque
unsigned long elapsed_time;                   //Tiempo transcurrido
unsigned long   focus_time =  t_focus*1000UL; //Convierte a ms el tiempo de focus
unsigned long desired_time = segundos*1000UL; //Convierte a ms el tiempo de espera
        float      motor_t =    t_motor*1000; //Convierte a ms el tiempo de avance
        float     tiempo_s =    tiempos*1000; //Convierte a ms el tiempo de espera despues de shutter

//-------------------------CONFIGURACION----------------------------//
void setup()
{
  //CONFIG de I/O's
  pinMode (  ledon, OUTPUT);
  pinMode ( ledoff, OUTPUT);
  pinMode (  motor, OUTPUT);
  pinMode (   strt,  INPUT);
  pinMode (shutter, OUTPUT);
  pinMode (  focus, OUTPUT);
 
  digitalWrite( ledoff, HIGH); //Activa LED STANDBY
  digitalWrite(  focus,  LOW); //Desactiva focus
  digitalWrite(shutter,  LOW); //Desactiva shutter
  digitalWrite(  motor,  LOW); //Desactiva motor
  
  attachInterrupt(stp,STOP,RISING); //Genera INTERRUPCION para detener todo proceso
  
  millis(); //Inicia timer para tiempo transcurrido
}

//---------------------------PROGRAMA------------------------------//

void loop()
{
  strt = digitalRead(4);
  
  if(strt==HIGH)
  {
    go=1;                       //Bandera GO de activacion
    i=0;                        //variable de inicializacion
    digitalWrite(ledon, HIGH);  //Activa led ON
    digitalWrite(ledoff, LOW);  //Desactiva led STANDBY
    delay(1000);                //Espera de 1 segundo para evitar movimientos indeseados de fotografia
    TimerA = millis();          //Se guarda el tiempo transcurrido en TimerA
  }
  
  /*------------------------PROCESO-------------------------------*/
  //Si bandera GO se activa
  while(go==1)
  {
    
    //Primer paso con i=0
    if(i==0)
    {
      //Si FOCUS esta envendido, activa señal de enfoque
      if(focus_state==1)
        digitalWrite(focus,HIGH);
      
      //Se guarda el tiempo transcurrido menos el tiempo transcurrido cuando se presiono el boton
      elapsed_time = millis()-TimerA;
      
      //Se compara el tiempo transcurrido contra el tiempo de enfoque predefinido o verifica que focus este desactivado
      if ((elapsed_time >= focus_time)||focus_state==0)
      {
        digitalWrite(focus,LOW);    //Desactiva el focus
        digitalWrite(shutter,HIGH); //Activa el shutter
        delay(200);                 //Espera 100ms con shutter activo
        digitalWrite(shutter,LOW);  //Desactiva shutter
        i=1;          //i = 1 para pasar a siguiente paso
        delay(tiempo_s); //Pausa despues de shutter para evitar movimiento en fotografia
        TimerA = millis();          //Se guarda tiempo transcurrido en TimerA
      }
        
    }
    
    //Siguiente paso con i=1  
    if(i==1)
    {
      digitalWrite(motor,HIGH); //Activa motor
      delay(motor_t);           //Espera predefinida por usuario
      digitalWrite(motor,LOW);  //Desactiva motor
      i=2;                      //i = 2 para impedir que reinicie el proceso
      delay(100);               //Espera de 100ms para evitar movimientos indeseados
      TimerA=millis();          //Se guarda tiempo transcurrido en TimerA
    }
    
    //Se guarda el tiempo transcurrido menos el tiempo transcurrido cuando se presiono el boton
    if(i==2)
    {
      elapsed_time = millis()-TimerA;
    
    //Se compara el tiempo transcurrido contra el tiempo de espera predefinido
      if (elapsed_time >= desired_time)
      {  
        i=0; //i = 0 para reiniciar el proceso
        TimerA=millis();          //Se guarda tiempo transcurrido en TimerA
      }
    }
  }
  
  /*------------------------DESACTIVACION---------------------------*/
  //Si la bandera GO se desactiva
  if(go==0)
  {
    digitalWrite(motor,LOW);   //Desactiva motor
    digitalWrite(focus,LOW);   //Desactiva focus
    digitalWrite(shutter,LOW); //Desactiva shutter
  }
}

//-----------------------INTERRUPCION-----------------------------//  
//Si en cualquier momento el boton STOP es activado  
void STOP()
{ 
    go=0;                      //Bandera GO se desactiva
    digitalWrite(ledon,  LOW); //Desactiva LED ON
    digitalWrite(ledoff,HIGH); //Activa LED STANDBY
    digitalWrite(focus,  LOW); //Desactiva focus
    digitalWrite(shutter,LOW); //Desactiva shutter
    i=2;                       //i = 2 para impedir entrada a proceso
}

