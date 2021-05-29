#include <Arduino.h>

class PID
{
	public:
        float calculatePID(float current_angle, float desired_angle);
        
	private:
        float PID, pwmLeft, pwmRight, error, previous_error;
        float pid_p=0;
        float pid_i=0;
        float pid_d=0;
        /////////////////PID CONSTANTS/////////////////
        double kp=3.55;//3.55
        double ki=0.005;//0.003
        double kd=2.05;//2.05
        ///////////////////////////////////////////////
        float elapsedTime, time, timePrev;
};