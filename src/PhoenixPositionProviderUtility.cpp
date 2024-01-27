# include "PhoenixPositionProviderUtility.h"

//the first row of atmosisa csv file is T, second is a, third is P, fourth is rho


vector<vector<float>> parseFile(const string& filename){
    vector<vector<float>> result; // Vector to store the final result

    ifstream atmos_file(filename);
    if (!atmos_file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return result; // Return an empty vector if the file cannot be opened
    }

    string line;
    while (getline(atmos_file, line)) {
        vector<float> row; // Vector to store the values of a single row

        istringstream iss(line);
        string value;
        while (getline(iss, value, ',')) {
            float floatValue = stof(value);
            row.push_back(floatValue);
        }

        result.push_back(row); // Add the row to the final result
    }

    atmos_file.close();

    return result;
}

vector<vector<float>> atmos_data = parseFile("src/atmosisa.csv");
vector<float> temperature = atmos_data[0];
vector<float> speed_of_sound = atmos_data[1];
vector<float> pressure = atmos_data[2];
vector<float> rho = atmos_data[3];

float linearInterp(float x, vector<float> all_x, vector<float> all_y) {
    if (all_x[0] == x) {
        return all_y[0];
    }
    int pos = 0;
    while (all_x[pos] < x) {
        pos++;
    }
    float x1 = all_x[pos - 1];
    float x2 = all_x[pos];
    float y1 = all_y[pos - 1];
    float y2 = all_y[pos];
    float slope = (y2 - y1) / (x2 - x1);
    return y1 + (x - x1) * slope;
}

//put airDensityFromAltitude function here
vector<float> getAltitudes(){
    vector<float> toReturn;
    for(int i = 0; i < 10001; i++){
        toReturn.push_back(float(i)); 
    }
    return toReturn;
}

vector<float> altitudes = getAltitudes();

float AirDensityFromAltitude(float x){ // looks correct
    return linearInterp(x, altitudes, rho);
}


// put mach and drag stuff here

vector<float> convert_to_ms(vector<float> mach_data){
    vector<float> toReturn;
    for(float num: mach_data){
        num = num*343;
        toReturn.push_back(num);
    }
    // cout << toReturn[0] << endl;
    // cout << toReturn[99] << endl;
    return toReturn;
}

vector<vector<float>> mach_drag_data = parseFile("src/mach_vs_cd.csv");
vector<float> mach_num = convert_to_ms(mach_drag_data[0]);
vector<float> drag_coef = mach_drag_data[1];

vector<vector<float>> thrust_curve = parseFile("src/thrust_curve.csv");
vector<float> height = thrust_curve[0];
vector<float> thrust = thrust_curve[1];


float mass(float t) {
    return DryMass + FuelMass - m_dot * t;
}
// calculate the mass of rocket at time t

float TempWindLoad(float y) {
    int WindOffset = (rand() % 7) - 3; // force range to [-3, 3]
    return 0.5 * AirDensityFromAltitude(y) * pow((AvgWindSpeed + WindOffset), 2) * Rocket_WindloadArea;
}

vector<float> GenerateWindLoadData() {
    vector<float> windloads;
    for (int alt = 0; alt < 10001; alt++) {
        float offset = -1 + 2 * (rand() / static_cast<double>(RAND_MAX));
        // cout << TempWindLoad(alt) << endl;
        windloads.push_back(offset * TempWindLoad(alt));
    }
    return windloads;
}

vector<float> windloads = GenerateWindLoadData();

float WindLoad(float y) {
    return linearInterp(y, altitudes, windloads);
}

float Thrust(float y) { // looks correct
    return linearInterp(y, height, thrust);
}

float RocketCd(float vy) { // looks good
    return linearInterp(vy, mach_num, drag_coef);
}


float RocketDrag(float y, float vy) { // looks good
    return 0.5 * AirDensityFromAltitude(y) * pow(vy, 2) * RocketCd(vy) * Rocket_Cross_Section_Area;
}

float DrogueDrag(float y, float vy) {
    return 0.5 * AirDensityFromAltitude(y) * pow(vy, 2) * DrogueCd * Drogue_Area; 
}

float MainDrag(float y, float vy) {
    return 0.5 * AirDensityFromAltitude(y) * pow(vy, 2) * MainCd * Main_Area; 
}

// DE1 works!
void createDE1(const stateType& q, stateType& dqdt, const double t) {
    // cout << "Stage 1: Lift off, Engine in operation..." << endl;
    dqdt[0] = q[1];
    dqdt[1] = 1.0 / mass(t) * WindLoad(q[2]);
    dqdt[2] = q[3];
    dqdt[3] = 1.0 / mass(t) * (Thrust(q[2]) - mass(t) * g - RocketDrag(q[2], q[3]));
}

//
void createDE2(const stateType& q, stateType& dqdt, const double t) {
    //cout << "Stage 2: Engine turns off, continuing upward..." << endl;
    dqdt[0] = q[1];
    dqdt[1] = 1.0 / DryMass * WindLoad(q[2]);
    dqdt[2] = q[3];
    dqdt[3] = 1.0 / DryMass * (-DryMass * g - RocketDrag(q[2], q[3]));
}

void createDE3(const stateType& q, stateType& dqdt, const double t) {
    //cout << "Stage 3: Drogue parachute deploys at Apogee..." << endl;
    dqdt[0] = q[1];
    dqdt[1] = 1.0 / DryMass * WindLoad(q[2]);
    dqdt[2] = q[3];
    dqdt[3] = 1.0 / DryMass * (RocketDrag(q[2], q[3]) + DrogueDrag(q[2], q[3]) - DryMass*g);
}

void createDE4(const stateType& q, stateType& dqdt, const double t) {
    //cout << "Stage 4: Main parachute deploys..." <<endl;
    dqdt[0] = q[1];
    dqdt[1] = 1.0 / DryMass * WindLoad(q[2]);
    dqdt[2] = q[3];
    dqdt[3] = 1.0 / DryMass * (RocketDrag(q[2], q[3]) + MainDrag(q[2], q[3]) - DryMass*g);
}