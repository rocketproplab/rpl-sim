#include "./src/virtual_GPS.hpp"

/**
 * rocketPosition: posiiton provided by PhoenixPositionProvider
 */
Vector3 virtual_GPS::process(Vector3 rocketPosition, double deltaTime){
    time_counter += deltaTime;

    if (time_counter >= refresh_time) {
        time_counter -= refresh_time;

        //update the GPS position
        last_GPS_pos.x = rocketPosition.x + rand()%error_amount;
        last_GPS_pos.x = rocketPosition.y + rand()%error_amount;
        last_GPS_pos.x = rocketPosition.z + rand()%error_amount;
    }
    return last_GPS_pos;
}
