#include "pid.h"

float PID::calculatePID(float current_angle, float desired_angle) {

    timePrev = time;  // the previous time is stored before the actual time read
    time = millis();  // actual time read
    elapsedTime = (time - timePrev) / 1000; 

    error = current_angle - desired_angle;
    
    pid_p = kp*error;

    if(-3 <error <3)
    {
        pid_i = pid_i+(ki*error);  
    }

    pid_d = kd*((error - previous_error)/elapsedTime);

    PID = pid_p + pid_i + pid_d;

    if(PID < -1000)
    {
        PID=-1000;
    }
    if(PID > 1000)
    {
        PID=1000;
    }
    
    previous_error = error; //Remember to store the previous error.

    return (PID);
}