#include <Arduino.h>
#include <Wire.h>

class IMU
{
	public:
        void setup(void);
        float getAngle(char axis);

	private:
        int16_t Acc_rawX, Acc_rawY, Acc_rawZ,Gyr_rawX, Gyr_rawY, Gyr_rawZ;

        float Acceleration_angle[2];
        float Gyro_angle[2];
        float Total_angle[2];

        float elapsedTime, time, timePrev;
        float rad_to_deg = 180/3.141592654;
};