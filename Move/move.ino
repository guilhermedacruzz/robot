#include <AccelStepper.h>
#include <IRremote.h>

#define X_VELOCIDADE   400
#define X_ACELERACAO   800
#define X_ENABLE_PIN   38
#define X_STEP_PIN     54
#define X_DIR_PIN      55

#define Y_VELOCIDADE   400
#define Y_ACELERACAO   800
#define Y_ENABLE_PIN   56
#define Y_STEP_PIN     60
#define Y_DIR_PIN      61

#define E_VELOCIDADE   400
#define E_ACELERACAO   800
#define E_ENABLE_PIN   24
#define E_STEP_PIN     26
#define E_DIR_PIN      28

#define Q_VELOCIDADE   400
#define Q_ACELERACAO   800
#define Q_ENABLE_PIN   30
#define Q_STEP_PIN     36
#define Q_DIR_PIN      34

#define INFRAVERMELHO_PIN      16
#define COOLER_PIN             9

IRrecv irRecv(INFRAVERMELHO_PIN);

decode_results irResults;

bool isRunning; 

AccelStepper motorX (1, X_STEP_PIN, X_DIR_PIN);
int directionX = 1;

AccelStepper motorY (1, Y_STEP_PIN, Y_DIR_PIN);
int directionY = 1;

AccelStepper motorE (1, E_STEP_PIN, E_DIR_PIN);
int directionE = -1;

AccelStepper motorQ (1, Q_STEP_PIN, Q_DIR_PIN);
int directionQ = -1;


void setup() {

    // LIGAR A SERIAL
    Serial.begin(9600);
    
    // MOTOR
    pinMode(X_ENABLE_PIN, OUTPUT);
    pinMode(Y_ENABLE_PIN, OUTPUT);
    pinMode(E_ENABLE_PIN, OUTPUT);
    pinMode(Q_ENABLE_PIN, OUTPUT);

    motorX.setMaxSpeed(X_VELOCIDADE);
    motorX.setSpeed(X_VELOCIDADE);
    motorX.setAcceleration(X_ACELERACAO);

    motorY.setMaxSpeed(X_VELOCIDADE);
    motorY.setSpeed(X_VELOCIDADE);
    motorY.setAcceleration(X_ACELERACAO);

    motorE.setMaxSpeed(X_VELOCIDADE);
    motorE.setSpeed(X_VELOCIDADE);
    motorE.setAcceleration(X_ACELERACAO);

    motorQ.setMaxSpeed(X_VELOCIDADE);
    motorQ.setSpeed(X_VELOCIDADE);
    motorQ.setAcceleration(X_ACELERACAO);

    //COOLER 
    pinMode(COOLER_PIN, OUTPUT);
    digitalWrite(COOLER_PIN, HIGH);

    // INFRAVERMELHO
    irRecv.enableIRIn();

    // ESTADO INICIAL
    isRunning = false;
}

void loop() {

    if(irRecv.decode(&irResults)) {
        Serial.println(irResults.value, HEX);
        if(irResults.value == 0xFF629D) {
          
            directionX = +1;
            directionY = +1;
            directionE = -1;
            directionQ = -1;
        
            isRunning = true;
            
            digitalWrite(X_ENABLE_PIN, LOW);
            digitalWrite(Y_ENABLE_PIN, LOW);
            digitalWrite(E_ENABLE_PIN, LOW);
            digitalWrite(Q_ENABLE_PIN, LOW);
        }
        else if(irResults.value == 0xFFA857) {

            directionX = -1;
            directionY = -1;
            directionE = +1;
            directionQ = +1;
            
            isRunning = true;
            digitalWrite(X_ENABLE_PIN, LOW);
            digitalWrite(Y_ENABLE_PIN, LOW);
            digitalWrite(E_ENABLE_PIN, LOW);
            digitalWrite(Q_ENABLE_PIN, LOW);
        }
        else if(irResults.value == 0xFFC23D) {

            directionX = +1;
            directionY = +1;
            directionE = +1;
            directionQ = +1;
            
            isRunning = true;
            digitalWrite(X_ENABLE_PIN, LOW);
            digitalWrite(Y_ENABLE_PIN, LOW);
            digitalWrite(E_ENABLE_PIN, LOW);
            digitalWrite(Q_ENABLE_PIN, LOW);
        }
        else if(irResults.value == 0xFF22DD) {

            directionX = -1;
            directionY = -1;
            directionE = -1;
            directionQ = -1;
            
            isRunning = true;
            digitalWrite(X_ENABLE_PIN, LOW);
            digitalWrite(Y_ENABLE_PIN, LOW);
            digitalWrite(E_ENABLE_PIN, LOW);
            digitalWrite(Q_ENABLE_PIN, LOW);
        }
        else if(irResults.value == 0xFF30CF) {

            directionX = +1;
            directionY = -1;
            directionE = +1;
            directionQ = -1;
            
            isRunning = true;
            digitalWrite(X_ENABLE_PIN, LOW);
            digitalWrite(Y_ENABLE_PIN, LOW);
            digitalWrite(E_ENABLE_PIN, LOW);
            digitalWrite(Q_ENABLE_PIN, LOW);
        }
        else if(irResults.value == 0xFF7A85) {

            directionX = -1;
            directionY = +1;
            directionE = -1;
            directionQ = +1;
            
            isRunning = true;
            digitalWrite(X_ENABLE_PIN, LOW);
            digitalWrite(Y_ENABLE_PIN, LOW);
            digitalWrite(E_ENABLE_PIN, LOW);
            digitalWrite(Q_ENABLE_PIN, LOW);
        } 
        else if(irResults.value == 0xFF02FD) {
            motorX.moveTo(0);
            motorY.moveTo(0);
            motorE.moveTo(0);
            motorQ.moveTo(0);
            digitalWrite(X_ENABLE_PIN, HIGH);
            digitalWrite(Y_ENABLE_PIN, HIGH);
            digitalWrite(E_ENABLE_PIN, HIGH);
            digitalWrite(Q_ENABLE_PIN, HIGH);
            isRunning = false;
        }
        else if(irResults.value == 0xFF4AB5) {
        }

        irRecv.resume();
    }

    if(isRunning) {
        motorX.moveTo(10000 * directionX);

        motorY.moveTo(10000 * directionY);
    
        motorE.moveTo(10000 * directionE);
    
        motorQ.moveTo(10000 * directionQ);
    }
    
    motorX.run();
    motorY.run();
    motorE.run();
    motorQ.run();
}
