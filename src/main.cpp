#include "PhoenixPositionProvider.h"

int main(){
    PhoenixPositionProvider ppp;
    for (int i = 0; i < 10; i++) {
        cout << -1 + 2 * (rand() / static_cast<double>(RAND_MAX)) << endl;
    }
}

