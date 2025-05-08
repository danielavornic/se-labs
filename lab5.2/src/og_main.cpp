
// #define MOTOR_ENABLE_PIN 3
// #define MOTOR_IN1_PIN 5
// #define MOTOR_IN2_PIN 4

// #define ENCODER_A 2
// #define POT_IN A0
// #define ENCODER_CALIBRATION 19.1
// #define UPDATE_INTERVAL 100
// #define SERIAL_BAUD_RATE 9600

// #define MAX_SAFE_SPEED 600
// #define MAX_INTEGRAL_CONTRIBUTION 50

// static FILE serialOutput = { 0 };

// struct PIDConfig {
//     float kp;
//     float ki;
//     float kd;
//     int minOutput;
//     int maxOutput;
// };

// struct SystemState {
//     int speed;
//     int setpoint;
//     int output;
//     int lastError;
//     long integralError;
// };

// PIDConfig pidConfig = {
//     .kp = 0.06f,
//     .ki = 0.00008f,
//     .kd = 0.0059f,
//     .minOutput = 5,
//     .maxOutput = 255
// };

// SystemState state = {
//     .speed = 0,
//     .setpoint = 0,
//     .output = 10,
//     .lastError = 0,
//     .integralError = 0
// };

// static unsigned long lastUpdateTimeMs = 0;
// static bool protectionHasOverriddenOutput = false;

// static int serialWriteByte(char c, FILE* stream)
// {
//     if (c == '\n') {
//         Serial.println();
//     } else {
//         Serial.write(c);
//     }
//     return 0;
// }

// void initSerial()
// {
//     Serial.begin(SERIAL_BAUD_RATE);
//     while (!Serial) {
//         ;
//     }
//     fdev_setup_stream(&serialOutput, serialWriteByte, NULL, _FDEV_SETUP_WRITE);
//     stdout = &serialOutput;
// }

// void initEncoder()
// {
//     pinMode(ENCODER_A, INPUT);
// }

// int measureSpeed()
// {
//     unsigned long pulseDuration = pulseIn(ENCODER_A, HIGH);
//     if (pulseDuration == 0) {
//         printf("Warning: pulseIn timeout or no pulse detected.\n");
//         return 0;
//     }
//     return ENCODER_CALIBRATION * ((60 * 1000 * 10) / pulseDuration);
// }

// void initMotor()
// {
//     pinMode(MOTOR_ENABLE_PIN, OUTPUT);
//     pinMode(MOTOR_IN1_PIN, OUTPUT);
//     pinMode(MOTOR_IN2_PIN, OUTPUT);

//     digitalWrite(MOTOR_IN1_PIN, HIGH);
//     digitalWrite(MOTOR_IN2_PIN, LOW);

//     analogWrite(MOTOR_ENABLE_PIN, state.output);
// }

// void applyMotorOutput()
// {
//     analogWrite(MOTOR_ENABLE_PIN, state.output);
// }

// void updatePIDController()
// {
//     int error = state.setpoint - state.speed;

//     state.integralError += error;

//     if (pidConfig.ki != 0) {
//         long integralSumLimit = (long)(MAX_INTEGRAL_CONTRIBUTION / pidConfig.ki);
//         state.integralError = constrain(state.integralError, -integralSumLimit, integralSumLimit);
//     }

//     int derivativeError = error - state.lastError;

//     float pidContribution = (pidConfig.kp * error) + (pidConfig.ki * state.integralError) + (pidConfig.kd * derivativeError);

//     state.output += (int)pidContribution;

//     state.output = constrain(state.output,
//         pidConfig.minOutput,
//         pidConfig.maxOutput);

//     state.lastError = error;
// }

// void initPotentiometer()
// {
//     pinMode(POT_IN, INPUT);
// }

// int readSetpointFromPot()
// {
//     return map(analogRead(POT_IN), 0, 1023, 0, 600);
// }

// void initTiming()
// {
//     lastUpdateTimeMs = millis();
// }

// bool isUpdateDue()
// {
//     return (millis() - lastUpdateTimeMs >= UPDATE_INTERVAL);
// }

// void markUpdateTime()
// {
//     lastUpdateTimeMs = millis();
// }

// void checkAndApplyProtections()
// {
//     protectionHasOverriddenOutput = false;

//     if (state.speed > MAX_SAFE_SPEED) {
//         printf("PROTECTION: Over-speed! Speed=%d > MAX=%d. Forcing output to min.\n", state.speed, MAX_SAFE_SPEED);
//         state.output = pidConfig.minOutput; // Or 0 for a harder stop if minOutput still runs motor
//         state.integralError = 0;
//         protectionHasOverriddenOutput = true;
//     }
// }

// void setup()
// {
//     initSerial();
//     initEncoder();
//     initPotentiometer();
//     initMotor();
//     initTiming();
// }

// void loop()
// {
//     if (isUpdateDue()) {
//         state.setpoint = readSetpointFromPot();
//         state.speed = measureSpeed();

//         updatePIDController();
//         checkAndApplyProtections();
//         applyMotorOutput();

//         printf("SP=%d, Value=%d, Output=%d", state.setpoint, state.speed, state.output);
//         if (protectionHasOverriddenOutput) {
//             printf(" (PROTECTION OVERRIDE)");
//         }
//         printf("\n");

//         markUpdateTime();
//     }
// }
