#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <iomanip>
#include "staty.h"

using namespace std;

fstream plik;
vector<double> dane;
struct wyniki {
    string 
        moda = "",
        nazwa = "";
    double 
        sredniaAryt = 0,
        mediana = 0,
        wariancja = 0,
        odchylenie = 0;
    int
        max = 0,
        min = 0,
        stopien = 0;
};
double sredniaAryt() {
    int dlugosc = dane.size();
    double suma = 0;
    for (double x : dane) {
        suma += x;
    }
    return suma / dlugosc;
}
double mediana() {
    int dlugosc = dane.size();
    double zwrot = 0;
    if (dlugosc < 2) {
        return NULL;
    }
    if (dlugosc % 2 == 1) {
        zwrot = dane[(dlugosc) / 2];
    }
    else if (dlugosc % 2 == 0) {
        zwrot = dane[(dlugosc - 1) / 2] + dane[(dlugosc) / 2];
        zwrot /= 2;
    }
    return zwrot;
}
string moda() {
    int max = 0;
    string zwrot = "";
    map<int, int> m_liczby; // <liczba, ilosc>
    for (int x : dane) {
        auto b1 = m_liczby.try_emplace(x, 1);
            if (!b1.second) {
                m_liczby[x]++;
            }
            if (m_liczby[x] > max) {
                max = m_liczby[x];
            }
    }
    zwrot = "[";
    int wielkosc = m_liczby.size();
    int licznik = 0;
    for (pair <int, int> y : m_liczby) {
        if (y.second == max) {
            zwrot += to_string(y.first) + " ," ;
        }
        licznik++;
    }
    zwrot += "]";
    return zwrot;
}
int max() {
    int max = 0;
    for (int x : dane) {
        if (x > max) {
            max = x;
        }
    }
    return max;
}
int min() {
    int min = max();
    for (int x : dane) {
        if (x < min) {
            min = x;
        }
    }
    return min;
}
double wariancja() {
    double zwrot = 0;
    int dlugosc = dane.size();
    double srednia = sredniaAryt();
    for (double x : dane) {
        zwrot += pow((x - srednia),2);
    }
    zwrot /= 2;
    return zwrot;
}

int main()
{
    system("@echo off");
    system("chcp 1250");
    system("cls");
    string kilofy[5] = { "Diamentowy", "Drewniany", "Kamienny", "Zelazny", "Zloty" };
    string sciezkaDoPliku;
    string linia;
    vector<wyniki> wynik;
    wyniki wyn;
    for (int stopien = 1; stopien <= 8; stopien++) {
        for (string x : kilofy) {
            sciezkaDoPliku = "statystyka/stopnieUb/" + to_string(stopien) + "/" + x + "kilof.txt";
            plik.open(sciezkaDoPliku, ios::in);
            if (plik.fail()) {
                cout << "Nie istnieje scieżka do" << sciezkaDoPliku;
                cout << "\nlub brak uprawnień";
            }
            while (getline(plik, linia)) {
                dane.push_back(stod(linia));
            }
            wyn.nazwa = x;
            wyn.stopien = stopien;
            wyn.max = max();
            wyn.min = min();
            wyn.mediana = mediana();
            wyn.moda = moda();
            wyn.sredniaAryt = sredniaAryt();
            wyn.wariancja = wariancja();
            wyn.odchylenie = sqrt(wariancja());
            wyn.moda.erase(wyn.moda.end() - 3, wyn.moda.end() - 1);
            wynik.push_back(wyn);
            dane.clear();
            plik.close();
        }
    }
    plik.open("wyniki.json", ios::out);
    if (plik.fail()) {
        cout << "Błąd w otwarciu pliku wyniki.json \n";
        cout << "Sprawdź ścieżkę lub uprawnienia do zapisu" << "\n";
        cin.ignore();
        return 1;
    }
    plik << "{\n";
    int it = 0;
    for (auto x : wynik) {
        plik << setprecision(3) << fixed;
        plik << "\t \"" << x.nazwa << " kilof | Unbreaking " << x.stopien << "\": {\n";
        plik << "\t\t \"Maksimum\": " << x.max << ",\n" ;
        plik << "\t\t \"Minimum\": " << x.min << ",\n";
        plik << "\t\t \"Moda\": " << x.moda << ",\n";
        plik << "\t\t \"Mediana\": " << x.mediana << ",\n";
        plik << "\t\t \"Srednia arytmetyczna\": " << x.sredniaAryt << ",\n";
        plik << "\t\t \"Wariancja\": " << x.wariancja << ",\n";
        plik << "\t\t \"Odchylenie standardowe\": " << x.odchylenie << "\n";
        if (it == wynik.size() - 1) {
            plik << "\t}\n";
        }
        else {
            plik << "\t},\n";
        }
        it++;
    }
    plik << "}\n";
    plik.close();
    cout << "Utworzono plik wyniki.json. Kliknij Enter, aby zakończyć";
    cin.ignore();
    return 0;
}