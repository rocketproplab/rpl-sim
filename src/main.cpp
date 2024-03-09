#include "PhoenixPositionProvider.h"

int main(){
    PhoenixPositionProvider ppp;
    ppp.process(0, 10.0);
    ppp.ignite();
    ppp.process(10.0, 16.4792 + 10);
    ppp.drogue();
    ppp.process(26.4792, 30);
}