#include <stdio.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <limits> // Potrzebne do wyczyszczenia bufora wejściowego

using namespace std;

// Funkcja pomocnicza, która czyści bufor i czeka na ENTER
void czekajNaEnter() {
    cin.clear(); // Resetuje ewentualne błędy strumienia
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Usuwa zalegające znaki (np. po cin >>)
    cout << "Naciśnij ENTER, aby kontynuować..." << endl;
    cin.get(); // Czeka na faktyczne naciśnięcie ENTER
}

// Funkcja główna programu wisielec
int main()
{
    int i,j,k,l,nrzad;
    int dlugosc, pozycja, liczbl;
    char znak;
    string nrlinii, wynik, maska;

    cout << "Gra w wisielca!" << endl;
    cout << "   ____" << endl;
    cout << "  |    |" << endl;
    cout << "  |    @" << endl;
    cout << "__|__" << endl;
    cout << endl;
    cout << "Krótka instrukcja:" << endl;
    cout << "Dopasuj litery do kształtu wyświetlonej poniżej maski." << endl;
    cout << "Zadania w pliku wisielec-dane.txt na pendriv-ie." << endl;
    cout << "Gramy do 6 nietrafionych liter :)" << endl;
    cout << endl;

    fstream plik;
    plik.open("/media/krzychas/DANE/wisielec-dane.txt", ios::in);

    cout << "Sprawdzam, czy istnieje plik z zadaniami?..." << endl;

    if(plik.good() == false)
    {
        cout << "BŁĄD: Włóż pendrive z plikiem wisielec-dane.txt a następnie uruchom program ponownie!" << endl;
        czekajNaEnter();
        exit(0);
    }

    cout << "OK" << endl;
    cout << "Podaj nr zadania: ";
    cin >> nrzad;

    // Pierwsza pętla - szukanie zadania
    while (!plik.eof())
    {
        plik >> nrlinii;
        l = atoi(nrlinii.c_str());
        plik >> wynik;
        plik >> maska;
        dlugosc = maska.length();

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
        cin >> nrzad;
    }
    
    plik.clear();
    plik.seekg(0, ios::beg);
    
    // Druga pętla - wczytywanie zadania
    while (!plik.eof())
    {
        plik >> nrlinii;
        l = atoi(nrlinii.c_str());
        plik >> wynik;
        plik >> maska;
        dlugosc = maska.length();

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

    for (i=0; i<dlugosc; i++)
    {
        cout << maska[i];
    }
    cout << endl;
    liczbl=0;

    // Główna pętla gry
    for (j=1; j<=dlugosc+liczbl; j++)
    {
        cout << "Podaj literę: ";
        cin >> znak;
        cout << "na pozycji: ";

        while (!(cin >> pozycja)) {
            cout << "BŁĄD: Pozycja musi być liczbą!" << endl << endl;
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Podaj ponownie pozycję: ";
            }
        pozycja--;

        if (wynik[pozycja]==znak)
        {
            maska[pozycja]=znak;
            cout << endl << "Zadanie " << nrlinii << " cd.: ";
            for (k=0; k<dlugosc; k++) cout << maska[k];
            cout << endl;
        }
        else
        {
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
            for (k=0; k<dlugosc; k++) cout << maska[k];
            cout << endl;
        }
    }

    if (liczbl!=6) cout << "Gratuluję sukcesu!" << endl;
    else cout << "PRZEGRANA. Hasło to: " << wynik << "." << endl;
    cout << "KONIEC" << endl;
    
    // Ostateczne czekanie na zamknięcie
    czekajNaEnter();

    return 0;
}
