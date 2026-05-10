#include <stdio.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <limits> 
#include <string>
#include <vector>

using namespace std;

void czekajNaEnter() {
    cin.clear(); 
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    cout << "Naciśnij ENTER, aby zakończyć..." << endl;
    cin.get(); 
}

int main()
{
    int k,l,nrzad;
    int dlugosc, pozycja, liczbl;
    string wpis; 
    string nrlinii, wynik_str, maska_plik;
    vector<string> wynik_pola; 
    vector<string> maska_pola;  

    cout << "Gra w wisielca!" << endl;
    cout << "   ____" << endl;
    cout << "  |    |" << endl;
    cout << "  |    @" << endl;
    cout << "__|__" << endl << endl;
    cout << "Krótka instrukcja:" << endl;
    cout << "Dopasuj litery do kształtu wyświetlonej poniżej maski." << endl;
    cout << "Zadania w pliku wisielec-dane-pl.txt na pendriv-ie." << endl;
    cout << "Gramy do 6 nietrafionych liter :)" << endl;
    cout << endl;
    
    fstream plik;
    plik.open("/media/krzychas/DANE/wisielec-dane-pl.txt", ios::in);

    cout << "Sprawdzam, czy istnieje plik z zadaniami?..." << endl;

    if(plik.good() == false) {
        cout << "BŁĄD: Włóż pendrive z plikiem wisielec-dane-pl.txt a następnie uruchom program ponownie!" << endl;
        czekajNaEnter();
        exit(0);
    }
    cout << "OK" << endl;

    cout << "Podaj nr zadania: ";
    while (!(cin >> nrzad)) {
        cout << "BŁĄD: Podaj poprawną liczbę całkowitą!" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Podaj nr zadania: ";
    }

    while (plik >> nrlinii >> wynik_str >> maska_plik) {
        l = stoi(nrlinii);
        if (l==nrzad)
        {
            cout << "Mam takie zadanie..." << endl;
            break;
        }
    }

    if (l<nrzad)
    {
        cout << "Mam tylko " << nrlinii << " zadań." << endl;
        cout << "Podaj nr zadania: ";
        while (!(cin >> nrzad)) {
            cout << "BŁĄD: Podaj poprawną liczbę całkowitą!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Podaj nr zadania: ";
        }
    }

    plik.clear();
    plik.seekg(0, ios::beg);

    while (plik >> nrlinii >> wynik_str >> maska_plik) {
        l = stoi(nrlinii);
        if (l==nrzad)
        {
            cout << "Przedstawiam zadanie: " << nrlinii << endl;
            break;
        }
    }

    if (l<nrzad)
    {
        cout << "Człowieku, nie mam tylu zadań!" << endl;
        czekajNaEnter();
        exit(0);
    }
    plik.close();

    for (int b = 0; b < (int)wynik_str.length(); b++) {
        string litera = "";
        litera += wynik_str[b];
        if ((wynik_str[b] & 0xc0) == 0xc0) { 
            litera += wynik_str[++b];
        }
        wynik_pola.push_back(litera);
    }

    for (int m = 0; m < (int)maska_plik.length(); m++) {
        string m_znak = "";
        m_znak += maska_plik[m];
        maska_pola.push_back(m_znak);
    }
    
    while(maska_pola.size() < wynik_pola.size()) maska_pola.push_back("_");
    dlugosc = wynik_pola.size();
    
    for (int m = 0; m < dlugosc; m++) cout << maska_pola[m];
    cout << endl;
    
    liczbl=0;

    while (liczbl < 6) {
        bool wygrana = true;
        for(int m=0; m<dlugosc; m++) if(maska_pola[m] != wynik_pola[m]) wygrana = false;
        if (wygrana) break;

        cout << "Podaj literę: ";
        cin >> wpis; 
        
        cout << "na pozycji: ";
        while (!(cin >> pozycja)) {
            cout << "BŁĄD: Pozycja musi być liczbą! Podaj ponownie: ";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
        
        int p = pozycja - 1;

        if (p >= 0 && p < dlugosc && wynik_pola[p] == wpis) {
            maska_pola[p] = wpis;
            cout << endl << "Zadanie " << nrlinii << " cd.: ";
            for (k=0; k<dlugosc; k++) cout << maska_pola[k];
            cout << endl;
        } else {
            liczbl++;
            cout << "to jest " << liczbl <<" nietrafiona :)" << endl << endl;

            if (liczbl == 1) 
            {
                cout << "__ __" << endl;
            }
            if (liczbl == 2) 
            {
                cout << "__|__" << endl;
            }
            if (liczbl == 3)
            {
                cout << "  |" << endl;
                cout << "__|__" << endl;
            }
            if (liczbl == 4)
            {
                cout << "  |" << endl;
                cout << "  |" << endl;
                cout << "__|__" << endl;
            }
            if (liczbl == 5)
            {
                cout << "   ____" << endl;
                cout << "  |" << endl;
                cout << "  |" << endl;
                cout << "__|__" << endl;
            }
            if (liczbl == 6)
            {
                cout << "   ____" << endl;
                cout << "  |    |" << endl;
                cout << "  |    @" << endl;
                cout << "__|__" << endl;
                break;
            }
            
            cout << endl << "Zadanie " << nrlinii << " cd.: ";
            for (k=0; k<dlugosc; k++) cout << maska_pola[k];
            cout << endl;
        }
    }

    bool wygrana_koniec = true;
    for(int m=0; m<dlugosc; m++) if(maska_pola[m] != wynik_pola[m]) wygrana_koniec = false;

    if (wygrana_koniec) cout << "Gratuluję sukcesu!" << endl;
    else cout << "PRZEGRANA. Hasło to: " << wynik_str << "." << endl;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    czekajNaEnter();
    return 0;
}
