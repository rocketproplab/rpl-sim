/*
process(long simTime, long deltaTime): This function is 
called once per simulation step.Use this function to update
 the internal position/rotation state.
*/

#include "boost_1_82_0/boost/numeric/odeint.hpp"
#include <vector>
#include <time.h> // for seeind rand
#include <stdlib.h> // for rand
#include <math.h> // for pow

using namespace std;
using namespace boost::numeric::odeint;

struct DE_1 {
    // gravity
    const int g = 9.81; // m/s

    // rocket body parameters
    const float DryMass = 54.4218; //kg  (126 lbs)
    const float FuelMass = 20.72917; //kg  (45.7 lbs)
    const float Rocket_Diameter = 0.206756; //m  (8.14 in)
    const float Rocket_Height = 4.64; //m (165 in)
    const float Rocket_WindloadArea = Rocket_Diameter * Rocket_Height;

    // rocket fuel parameters
    const float m_dot = 1.5434; // kg/s, mass flow rate of fuel
    const float BurnTime = FuelMass / m_dot; // 13.4308 seconds

    // wind parameters
    const float AvgWindSpeed = 10; // m/s, average speed of wind of FAR site

    const float rho = 0.7637; // using air density as a constant for now

    // calculate the mass of rocket at time t
    float mass(float t) {
        return DryMass + FuelMass - m_dot * t;
    }

    float WindLoad(float y) {
        int WindOffset = (rand() % 7) - 3; // force range to [-3, 3]
        return 1 / 2 * rho * pow(AvgWindSpeed + WindOffset, 2) * Rocket_WindloadArea;
    }

    float Thrust(float y) {
        return 1;
    }

    float RocketDrag(float y, float vy) {
        return 1;
    }

    void operator()(const vector<double>& q, vector<double>& dqdt, const double t) {
        dqdt[0] = q[1];
        dqdt[1] = 1.0 / mass(t) * WindLoad(q[2]);
        dqdt[2] = q[3];
        dqdt[3] = 1.0 / mass(t) * (Thrust(q[2]) - mass(t) * g - RocketDrag(q[2], q[3]));
    }
};


class PhoenixPositionProvider{
    public:
        int currCoords[3] = {0, 0, 0};
        int previousRotState;
        int updatedRotState;
        int igniteCounter;
        int destroyed;

        DE_1 DiffEq1;

        PhoenixPositionProvider() : DiffEq1() {
            srand(time(NULL)); // seed random generator


        };

        

        // Define your initial conditions

         // if it is 0, then rocket isn't ignited. If 1, then it is
        // a boolean to check if the chute has to be deployed?
        
        /*
        WHAT WE CURRENTLY UNDERSTAND:
            - There is an update loop being called in another file
            - The process function in our file will be called at each step in the loop
            - 
        */
        // Define your differential equations

        /* TO DO
        - make air density a function of altitude (using interpolation or something)
        */



        

        void process(long simTime, long deltaTime){
            return;
        }
       
        int* getPosition(){
            return currCoords;
       }

        void do_stuff() {
            // Define the time span
            double t_start = 0.0;
            double t_end = BurnTime;

            vector<double> initial_conditions = {0.0, 0.0, 0.0, 0.0};


            // Integrate the differential equations using ODEint
            integrate(DE_1(), initial_conditions, t_start, t_end, 0.1, [](const auto& q, const auto t) {
                // Print the results or store them as needed
                cout << t << "\t" << q[0] << "\t" << q[1] << "\t" << q[2] << "\t" << q[3] << endl;
            });

        }
};


int main() {
    PhoenixPositionProvider ppp = PhoenixPositionProvider();
}