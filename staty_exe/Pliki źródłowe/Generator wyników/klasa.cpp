#include <string>
#include "klasa.h"


narzedzie::narzedzie(std::string nazwa, int maksymalna, int zuzycie) {
    this->nazwa = nazwa;
    this->maksymalna = maksymalna;
    this->zuzycie = zuzycie;
    if (zuzycie == 0) {
        this->zuzycie = maksymalna;
    }
}
void narzedzie::setStopien(int stopien) {
    stopien_unbreaking = stopien;
}
int narzedzie::getStopien() {
    return this->stopien_unbreaking;
}
int narzedzie::getZuzycie() {
    return this->zuzycie;
}
void narzedzie::setZuzycie() {
    this->zuzycie -= 1;
}
void narzedzie::odnowa() {
    this->zuzycie = this->maksymalna;
}
string narzedzie::getNazwa() {
    return this->nazwa;
}
int narzedzie::zuzyj() {
    {
        int stopien1 = this->getStopien();
        double stopien = stopien1;
        if (!stopien) {
            this->setZuzycie();
            return 1;
        }
        double szansa = ((stopien + 1)) * 10;
        if (szansa >= 100) {
            return 2;
        }
        double los = rand() % 100;
        if (los >= szansa) {
            this->setZuzycie();
            return 1;
        }
        else {
            return 0;
        }
    }
}