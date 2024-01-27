#include "PhoenixPositionProvider.h"

int main(){
    PhoenixPositionProvider ppp;
    // for (int i = 0; i < 10; i++) {
    //     cout << -1 + 2 * (rand() / static_cast<double>(RAND_MAX)) << endl;
    // }

    vector<float> abc = GenerateWindLoadData();
    cout << abc[1] << endl;
    cout << abc[2] << endl;
    // for (int i = 10; i < 21; i++) {
    //     cout << WindLoad(float(i/10)) << endl;
    // }
    cout << WindLoad(1.0) << endl;
}

