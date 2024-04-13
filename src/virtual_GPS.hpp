#ifndef PHOENIX_VIRTUAL_GPS
#define PHOENIX_VIRTUAL_GPS
#include "./src/Vector3.hpp"
#include <stdio.h>
#include <stdlib.h>

class virtual_GPS {
    private:
    Vector3 last_GPS_pos;
    double refresh_time;
    int error_amount;
    int error_seed;
    double time_counter;

    public:
        /**
         * Constructor:
         * ini_latitude, ini_longitude, ini_elevation: launch site coordinates
         * refresh_rate: refresh rate of GPS sensor in Hz
         * error_amount: range for the noise in GPS [0, error_amount] in meters
         * error_seed: seed used to generate error in c++ rand() function
         */
        virtual_GPS(float ini_latitude, float ini_longitude, float ini_elevation,
        int refresh_rate, int error_amount, int error_seed):
         error_amount(error_amount), error_seed(error_seed), time_counter(0) {
            last_GPS_pos.x = ini_latitude;
            last_GPS_pos.y = ini_latitude;
            last_GPS_pos.z = ini_elevation;
            refresh_time = 1/refresh_rate;
            srand(error_seed);
        }

        Vector3 process(Vector3 rocketPosition, double deltaTime);
};
#endif