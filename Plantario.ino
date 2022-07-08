///////////////////////////////////////////////////////////
//                                                       // 
// Autor: Diego Paiani Cardoso    Data: 19/12/2020       //
// Projeto Plantario                                     // 
//                                                       // 
///////////////////////////////////////////////////////////

  #include "dht.h"                              // INCLUI A BIBLIOTECA PARA O SENSOR
  const int pinoDHT11 = 2;                      // PINO D2 QUE CONECTA O SENSOR DE TEMPERATURA
  dht DHT;                                      // ESTANCIAMENTO DA VARIAVEL DO DTH11
  
  unsigned long tempo = 0;                      // VARIAVEL DO RELOGIO
  int temporizador = 0;                         // TEMPORIZADOR DOS CICLOS


void setup() {
  
  pinMode(3, OUTPUT);                           // DEFINE D3 COMO SAIDA DIGITAL DA LAMPADA
  pinMode(4, OUTPUT);                           // DEFINE D4 COMO SAIDA DIGITAL DA LAMPADA

  pinMode(5, OUTPUT);                           // DEFINE D5 COMO SAIDA DIGITAL PARA BOMBA DAGUA
  pinMode(6, OUTPUT);                           // DEFINE D6 COMO SAIDA DIGITAL PARA VENTILACAO

  Serial.begin(9600);                           // INICIA O MONITOR SERIAL COM BAUT RATE DE 9600         
  delay(100);                                  // INTERVALO DE 2 SEGUNDOS

}

void loop() {
////////////////////////////////////////////////////////////////////////////////////////////////
//        CICLO DE DESENVOLVIMENTO DAS PLANTAS - 12 HORAS DE LUZ                              //
//         LUZ LIGADAS, MONITORAMENTO DE VENTILACAO E UMIDADE AR E DO SOLO                    //
////////////////////////////////////////////////////////////////////////////////////////////////

  tempo = millis();                                  // PEGA O VALOR DO RELOGIO
  while(millis() - tempo <= 43200000)                // 16 HORAS DE FLUXO DE LUZ
  {                                                  // CICLO CONSTANTE
    digitalWrite(3, LOW);                            // LUZ LIGADA                   
    digitalWrite(4, LOW);                            // LUZ LIGADA

///////////////////////////////////////////////////////////////////////////////////////////////
//  CONTROLE DA TEMPERATURA E UMIDADE INTERNA - MONITORACAO PELA PORTA SERIAL                //
//  SENSOR DTH 11 PINO 1 = SINAL - D2(ARDUINO)     VENTILADOR - MODULO RELE                  //
//                PINO 2 = VCC                                - PINO D6(ARDUINO)             //
//                PINO 3 = GND                     TEMPERATURA MAXIMA - 30C                  //
///////////////////////////////////////////////////////////////////////////////////////////////    
    
    DHT.read11(pinoDHT11);                            //LE AS INFORMACOES DO SENSOR
    Serial.print("Umidade do ar: ");                  //IMPRIME O TEXTO NA SERIAL
    Serial.print(DHT.humidity);                       //IMPRIME NA SERIAL O VALOR DE UMIDADE MEDIDO
    Serial.print("%");                                //ESCREVE O TEXTO EM SEGUIDA
    Serial.print(" / Temperatura: ");                 //IMPRIME O TEXTO NA SERIAL
    Serial.print(DHT.temperature, 0);                 //IMPRIME NA SERIAL O VALOR DE UMIDADE MEDIDO E REMOVE A PARTE DECIMAL
    Serial.print("*C ");                              //IMPRIME O TEXTO NA SERIAL
    delay(2000);                                      //INTERVALO DE 2 SEGUNDOS * NAO DIMINUIR ESSE VALOR

    if(DHT.temperature > 28 && DHT.temperature <= 10){// SE A TEMPERATURA FOR SUPERIOR DE 30
      digitalWrite(6, LOW);                           // LIGA A VENTILACAO
    }
    else{                                             // CASO CONTRARIO
      digitalWrite(6, HIGH);                          // DESLIGA VENTILACAO
    }
    if(DHT.humidity > 50 && DHT.humidity < 90){       // SE A UMIDADE RELATIVA DO AR MUDAR DEMAIS
      digitalWrite(6, LOW);                           // LIGA VENTILACAO
    }
    else{                                             // CASO CONTRARIO
      digitalWrite(6, HIGH);                          // DESLIGA VENTILACAO
    }

////////////////////////////////////////////////////////////////////////////////////////////////
//    CONTROLE E MONITORACAO DA UMIDADE DO SOLO - MONITORACAO PELA PORTA SERIAL               //
//    SENSOR DE UMIDADE DO SOLO   PINO 1 - VCC          ARDUINO PORTA A0                      //    
//                                PINO 2 - GND                                                //  
//                                PINO 3 - SINAL(A0)                                          //
////////////////////////////////////////////////////////////////////////////////////////////////
     
     int sensorValue = analogRead(A0);                  // DEFINE O PINO A0 PARA LEITURA ANALOGICA
                                                        // SENSOR DE UMIDADE DO SOLO
     if (sensorValue > 600){                            // SE O VALOR FOR MAIOR QUE 600
            Serial.print(" / umidade do solo: ");       // MOSTRA NO MONITOR SERIAL
            Serial.print(sensorValue);                  // MOSTRA OS VALORES DO SENSOR
            digitalWrite(5, LOW);                       // LIGA A BOMBA DAGUA
            delay(100);
     }
     if (sensorValue < 600){                             // SE O VALOR FOR MENOR QUE 600
            Serial.print(" / umidade do solo: ");        // MOSTRA NA TELA 
            Serial.println(sensorValue);                 // MOSTRA O VALOR DOS SENSORES
            digitalWrite(5, HIGH);                       // LIGA A BOMBA DAGUA
            delay(100);                                  // AGUARDA PRA PROXIMA LEITURA
     }
  }
////////////////////////////////////////////////////////////////////////////////////////////////
//       CICLO DE DESCANSO DAS PLANTAS - 12 HORAS DE LUZ                                      //
//       LUZ DESLIGADAS, MONITORAMENTO DE VENTILACAO E UMIDADE DO AR E UMIDADE DO SOLO        //
////////////////////////////////////////////////////////////////////////////////////////////////
}
  
