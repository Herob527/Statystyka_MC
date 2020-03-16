#pragma once
#ifndef funkcje
#define funkcje

using namespace std;

class narzedzie {
private:
    int stopien_unbreaking;
    string nazwa;
    int zuzycie;
    int maksymalna;
public:
    narzedzie(string nazwa, int maksymalna, int zuzycie = 0);
    void setStopien(int stopien);
    int getZuzycie();
    void setZuzycie();
    int getStopien();
    string getNazwa();
    int zuzyj();
    void odnowa();
};
#endif // !funkcje

