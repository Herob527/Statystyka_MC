#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include "klasa.h"

using namespace std;

fstream plik;

int main()
{
    srand(time(NULL));
    system("chcp 1250");
    system("cls");
    int ktory;
    int it;
    int i1;
    int ii1;
    string folder;
    string kilofy[][5] = { {"Drewniany", "60"}, {"Kamienny", "132"}, {"Zloty" , "33"}, {"Zelazny", "251"}, {"Diamentowy", "1562"} };
    for (int stopien = 1; stopien <= 8; stopien++) {
        ktory = 0;
        for (auto x : kilofy) {
            narzedzie* kilof = new narzedzie(kilofy[ktory][0] + "kilof", stoi(kilofy[ktory][1]));
            kilof->setStopien(stopien);
            folder = "statystyka/stopnieUb/" + to_string(kilof->getStopien()) + "/" + kilof->getNazwa() + ".txt";
            plik.open(folder, ios::out);
            if (plik.fail()) {
                cout << "błąd w otwarciu pliku: ";
                cout << folder << "\n";
                cin.ignore();
            }
            for (ii1 = 0; ii1 < 200; ii1++) {
                for (it = 0; kilof->getZuzycie() != 0; it++) {
                    i1 = kilof->zuzyj();
                    if (i1 == 2) {
                        break;
                    }
                };
                plik << it << "\n";
                kilof->odnowa();
            }
            ktory++;
            folder = "";
            delete kilof;
            plik.close();
        }
    }
    cout << "Utworzono statystyki. Kliknij Enter, by zakończyć.";
    cin.ignore();
    return 0;
}

