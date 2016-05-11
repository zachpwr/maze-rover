// Zachary Maniatis & Zachary Power
#define LEFT_ENCODER_MASK  0b00110000
#define RIGHT_ENCODER_MASK 0b00000011
#define LEFT_MOTOR_MASK    0b11000000
#define RIGHT_MOTOR_MASK   0b00001100

void drift(int direction);
void turn(int direction);
void driveForward();
int stop();
int setLeftMotor(int direction);
int setRightMotor(int direction);
