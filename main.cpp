#include <iostream>
#include <windows.h>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

struct Uzytkownik
{
    int id;
    string nazwa, haslo;
};

struct Adresat
{
    int id;
    string imie, nazwisko, nrTel, email, adres;
};

int wczytajDaneZPlikuTekstowegoUzytkownicy(vector <Uzytkownik> & uzytkownicy, int liczbaAdresatow);
int rejestracja( vector <Uzytkownik> & uzytkownicy, int liczbaUzytkownikow);
int logowanie(vector <Uzytkownik> & uzytkownicy, int liczbaUzytkownikow);
void zmianaHasla(vector <Uzytkownik> & uzytkownicy, int liczbaUzytkownikow, int idZalogowanegoUzytkownika);
void menuPrzedZalogowaniem(vector <Uzytkownik> & uzytkownicy);
int wczytajDaneZPlikuTekstowegoAdresaci(vector <Adresat> & adresaci, int liczbaAdresatow, int idZalogowanegoUzytkownika);
int dodajAdresata(vector <Adresat> & adresaci, int liczbaAdresatow, int idZalogowanegoUzytkownika);
void szukajAdresataPoImieniu(vector <Adresat> & adresaci, int liczbaAdresatow);
void szukajAdresataPoNazwisku(vector <Adresat> & adresaci, int liczbaAdresatow);
void wyswietlWszystkichAdresatow(vector <Adresat> & adresaci, int liczbaAdresatow);
void edytujAdresata(vector <Adresat> & adresaci, int liczbaAdresatow, int idZalogowanegoUzytkownika);
int usunAdresata(vector <Adresat> & adresaci, int liczbaAdresatow);
void wyjscieDoMenuGlownego();

int main()
{
    vector <Uzytkownik> uzytkownicy;
    vector <Adresat> adresaci;
    int idZalogowanegoUzytkownika = 0;
    int liczbaUzytkownikow = 0;

    char wybor;
    char wprowadzonyZnakZKlawiatury;

    liczbaUzytkownikow = wczytajDaneZPlikuTekstowegoUzytkownicy(uzytkownicy, liczbaUzytkownikow);

    while(1)
    {
        int liczbaAdresatow = 0;

        if(idZalogowanegoUzytkownika == 0)
        {
            system("cls");
            cout << "----------------" << endl;
            cout << "Ksiazka adresowa" << endl;
            cout << "----------------" << endl;

            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "9. Zakoncz program" << endl;

            cin >> wybor;

            if(wybor == '1')
            {
                liczbaUzytkownikow = rejestracja(uzytkownicy, liczbaUzytkownikow);
            }
            else if(wybor == '2')
            {
                idZalogowanegoUzytkownika = logowanie(uzytkownicy, liczbaUzytkownikow);
            }
            else if(wybor == '9')
            {
                exit(0);
            }
        }
        else
        {
            adresaci.clear();
            liczbaAdresatow = wczytajDaneZPlikuTekstowegoAdresaci(adresaci, liczbaAdresatow, idZalogowanegoUzytkownika);

            system("cls");
            cout << "------------------------------" << endl;
            cout << "Ksiazka adresowa - menu glowne" << endl;
            cout << "------------------------------" << endl;
            cout << "Zalogowano jako uzytkownik z id: " << idZalogowanegoUzytkownika << endl << endl;

            cout << "1. Dodaj adresata" << endl;
            cout << "2. Wyszukaj po imieniu" << endl;
            cout << "3. Wyszukaj po nazwisku" << endl;
            cout << "4. Wyswietl wszystkich adresatow" << endl;
            cout << "5. Usun adresata" << endl;
            cout << "6. Edytuj adresata" << endl;
            cout << "7. Zmien haslo" << endl;
            cout << "9. Wyloguj sie" << endl;

            cin >> wprowadzonyZnakZKlawiatury;

            if (wprowadzonyZnakZKlawiatury == '1')
            {
                liczbaAdresatow = dodajAdresata(adresaci, liczbaAdresatow, idZalogowanegoUzytkownika);
            }
            else if (wprowadzonyZnakZKlawiatury == '2')
            {
                szukajAdresataPoImieniu(adresaci, liczbaAdresatow);
            }
            else if (wprowadzonyZnakZKlawiatury == '3')
            {
                szukajAdresataPoNazwisku(adresaci, liczbaAdresatow);
            }
            else if (wprowadzonyZnakZKlawiatury == '4')
            {
                wyswietlWszystkichAdresatow(adresaci, liczbaAdresatow);
            }
            else if (wprowadzonyZnakZKlawiatury == '5')
            {
                liczbaAdresatow = usunAdresata(adresaci, liczbaAdresatow);
            }
            else if (wprowadzonyZnakZKlawiatury == '6')
            {
                edytujAdresata(adresaci, liczbaAdresatow, idZalogowanegoUzytkownika);
            }
            else if (wprowadzonyZnakZKlawiatury == '7')
            {
                zmianaHasla(uzytkownicy, liczbaUzytkownikow, idZalogowanegoUzytkownika);
            }
            else if (wprowadzonyZnakZKlawiatury == '9')
            {
                idZalogowanegoUzytkownika = 0;
            }
        }
    }

    return 0;
}

int wczytajDaneZPlikuTekstowegoUzytkownicy(vector <Uzytkownik> & uzytkownicy, int liczbaAdresatow)
{
    int dlugoscLinii;
    int pozycjaSeparatora[3];

    uzytkownicy.push_back(Uzytkownik());

    string id, nazwa, haslo;
    string linia;
    fstream plikTekstowy;

    plikTekstowy.open("Uzytkownicy.txt", ios::in);

    if (plikTekstowy.good() == true)
    {
        while (getline(plikTekstowy, linia))
        {
            dlugoscLinii = linia.length();
            int n = 0;
            for (int i = 0; i < dlugoscLinii; i++)
            {
                if (linia[i] == '|')
                {
                    pozycjaSeparatora[n] = i;
                    n++;
                }
            }

            id = "";

            for (int i = 0; i < pozycjaSeparatora[0]; i++)
            {
                id.push_back(linia[i]);
            }

            uzytkownicy.push_back(Uzytkownik());
            uzytkownicy[liczbaAdresatow].id = atoi(id.c_str());

            for (int i = pozycjaSeparatora[0] + 1; i < pozycjaSeparatora[1]; i++)
            {
                uzytkownicy[liczbaAdresatow].nazwa.push_back(linia[i]);
                uzytkownicy.push_back(Uzytkownik());
            }

            for (int i = pozycjaSeparatora[1] + 1; i < pozycjaSeparatora[2]; i++)
            {
                uzytkownicy[liczbaAdresatow].haslo.push_back(linia[i]);
                uzytkownicy.push_back(Uzytkownik());
            }

            liczbaAdresatow++;
        }

        plikTekstowy.close();
    }
    else
    {
        liczbaAdresatow = 0;
    }

    return liczbaAdresatow;
}

int rejestracja(vector <Uzytkownik> & uzytkownicy, int liczbaUzytkownikow)
{
    fstream plikTekstowy;
    string nazwa, haslo;

    system("cls");
    cout << "------------------------------" << endl;
    cout << "Ksiazka adresowa - rejestracja" << endl;
    cout << "------------------------------" << endl;

    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwa;

    int i = 0;

    while(i < liczbaUzytkownikow)
    {
        if(uzytkownicy[i].nazwa == nazwa)
        {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> nazwa;
            i = 0;
        }
        else
        {
            i++;
        }
    }

    cout << "Podaj haslo: ";
    cin >> haslo;

    uzytkownicy.push_back(Uzytkownik());
    uzytkownicy[liczbaUzytkownikow].nazwa = nazwa;
    uzytkownicy.push_back(Uzytkownik());
    uzytkownicy[liczbaUzytkownikow].haslo = haslo;
    uzytkownicy.push_back(Uzytkownik());

    if (liczbaUzytkownikow == 0)
    {
        uzytkownicy[liczbaUzytkownikow].id =  1;
        uzytkownicy.push_back(Uzytkownik());
    }
    else
    {
        uzytkownicy[liczbaUzytkownikow].id = uzytkownicy[liczbaUzytkownikow - 1].id + 1;
    }

    plikTekstowy.open("Uzytkownicy.txt", ios::out | ios::app);

    if (plikTekstowy.good() == true)
    {
        plikTekstowy << uzytkownicy[liczbaUzytkownikow].id << "|";
        plikTekstowy << uzytkownicy[liczbaUzytkownikow].nazwa << "|";
        plikTekstowy << uzytkownicy[liczbaUzytkownikow].haslo << "|" << endl;
    }

    plikTekstowy.close();

    cout << "Konto zalozone" << endl;
    Sleep(1000);

    return liczbaUzytkownikow + 1;
}

int logowanie(vector <Uzytkownik> & uzytkownicy, int liczbaUzytkownikow)
{
    string nazwa, haslo;

    system("cls");
    cout << "----------------------------" << endl;
    cout << "Ksiazka adresowa - logowanie" << endl;
    cout << "----------------------------" << endl;

    cout << "Podaj login: ";
    cin >> nazwa;

    int i = 0;

    while(i < liczbaUzytkownikow)
    {
        if(uzytkownicy[i].nazwa == nazwa)
        {
            for(int proby = 0; proby < 3; proby++)
            {
                cout << "Podaj haslo. Pozostalo prob " << 3 - proby << ": ";
                cin >> haslo;

                if(uzytkownicy[i].haslo == haslo)
                {
                    cout << "Zalogowales sie." << endl;
                    Sleep(1000);
                    return uzytkownicy[i].id;
                }
            }
            cout << "Podales 3 razy bledne haslo. Poczekaj 3 sek przed kolejna proba." << endl;
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout << "Nie ma uzytkownika z takim loginem." << endl;
    Sleep(1500);

    return 0;
}

void zmianaHasla(vector <Uzytkownik> & uzytkownicy, int liczbaUzytkownikow, int idZalogowanegoUzytkownika)
{
    fstream plikTekstowy;
    string haslo;

    system("cls");
    cout << "-------------------------------" << endl;
    cout << "Ksiazka adresowa - zmiana hasla" << endl;
    cout << "-------------------------------" << endl;

    cout << "Podaj nowe haslo: ";
    cin >> haslo;

    for(int i = 0; i < liczbaUzytkownikow; i++)
    {
        if(uzytkownicy[i].id == idZalogowanegoUzytkownika)
        {
            uzytkownicy.push_back(Uzytkownik());
            uzytkownicy[i].haslo = haslo;
            uzytkownicy.push_back(Uzytkownik());

            cout << "Haslo zostalo zmienione.";
            Sleep(1500);
        }
    }

    plikTekstowy.open("Uzytkownicy.txt", ios::out | ios::trunc);
    plikTekstowy.close();
    plikTekstowy.open("Uzytkownicy.txt", ios::out | ios::app);

    if (plikTekstowy.good() == true)
    {
        for (int i = 0; i < liczbaUzytkownikow; i++)
        {
            plikTekstowy << uzytkownicy[i].id << "|";
            plikTekstowy << uzytkownicy[i].nazwa << "|";
            plikTekstowy << uzytkownicy[i].haslo << "|" << endl;
        }
    }

    plikTekstowy.close();
}

int dodajAdresata(vector <Adresat> & adresaci, int liczbaAdresatow, int idZalogowanegoUzytkownika)
{
    string idAdresataStr, linia;
    int idAdresata;
    int dlugoscLinii;
    int pozycjaSeparatora[7];
    bool czySaAdresaci = false;

    system("cls");
    cout << "----------------------------------" << endl;
    cout << "Ksiazka adresowa - dodawanie osoby" << endl;
    cout << "----------------------------------" << endl;

    string imie, nazwisko, nrTel, email, adres;
    fstream plikTekstowy;

    cout << "Podaj imie: ";
    cin >> imie;
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;
    cout << "Podaj nr. tel.: ";
    cin >> nrTel;
    cout << "Podaj adres email: ";
    cin >> email;

    cin.sync();

    cout << "Podaj adres [ulica, numer domu/numer mieszkania, kod pocztowy, miasto]: ";
    getline(cin, adres);

    adresaci.push_back(Adresat());
    adresaci[liczbaAdresatow].imie = imie;
    adresaci.push_back(Adresat());
    adresaci[liczbaAdresatow].nazwisko = nazwisko;
    adresaci.push_back(Adresat());
    adresaci[liczbaAdresatow].nrTel = nrTel;
    adresaci.push_back(Adresat());
    adresaci[liczbaAdresatow].email = email;
    adresaci.push_back(Adresat());
    adresaci[liczbaAdresatow].adres = adres;
    adresaci.push_back(Adresat());

    plikTekstowy.open("Adresaci.txt", ios::in);

    if (plikTekstowy.good() == true)
    {
        while (getline(plikTekstowy, linia))
        {
            czySaAdresaci = true;

            dlugoscLinii = linia.length();
            int n = 0;
            for (int i = 0; i < dlugoscLinii; i++)
            {
                if (linia[i] == '|')
                {
                    pozycjaSeparatora[n] = i;
                    n++;
                }
            }

            idAdresataStr = "";

            for (int i = 0; i < pozycjaSeparatora[0]; i++)
            {
                idAdresataStr.push_back(linia[i]);
            }

            idAdresata = atoi(idAdresataStr.c_str());
        }
    }

    plikTekstowy.close();

    if(czySaAdresaci)
    {
        adresaci[liczbaAdresatow].id = idAdresata + 1;
    }
    else
    {
        adresaci[liczbaAdresatow].id = 1;
    }

    plikTekstowy.open("Adresaci.txt", ios::out | ios::app);

    if (plikTekstowy.good() == true)
    {
        plikTekstowy << adresaci[liczbaAdresatow].id << "|";
        plikTekstowy << idZalogowanegoUzytkownika << "|";
        plikTekstowy << adresaci[liczbaAdresatow].imie << "|";
        plikTekstowy << adresaci[liczbaAdresatow].nazwisko << "|";
        plikTekstowy << adresaci[liczbaAdresatow].nrTel << "|";
        plikTekstowy << adresaci[liczbaAdresatow].email << "|";
        plikTekstowy << adresaci[liczbaAdresatow].adres << "|" << endl;
    }

    plikTekstowy.close();

    cout << endl;
    cout << "Dodano osobe do ksiazki adresowej" << endl << endl;
    cout << "Indeks dodanej osoby to: " << adresaci[liczbaAdresatow].id << endl << endl;

    wyjscieDoMenuGlownego();

    return liczbaAdresatow + 1;
}

void szukajAdresataPoImieniu(vector <Adresat> & adresaci, int liczbaAdresatow)
{
    system("cls");
    cout << "------------------------------------------" << endl;
    cout << "Ksiazka adresowa - wyszukiwanie po imieniu" << endl;
    cout << "------------------------------------------" << endl;

    string imie;
    int i = 0, j = 0;

    if (liczbaAdresatow == 0)
    {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }
    else
    {
        cout << "Podaj imie do wyszukania: ";
        cin >> imie;
        cout << endl;

        while (i < liczbaAdresatow)
        {
            if (adresaci[i].imie == imie)
            {
                cout << "Id: " << adresaci[i].id << endl;
                cout << "Imie: " << adresaci[i].imie << endl;
                cout << "Nazwisko: " << adresaci[i].nazwisko << endl;
                cout << "Numer tel: " << adresaci[i].nrTel << endl;
                cout << "Email: " << adresaci[i].email << endl;
                cout << "Adres: " << adresaci[i].adres << endl;

                cout << endl;

                j++;
            }
            i++;
        }

        if (j == 0)
        {
            cout << "Brak osob w ksiazce adresowej o takim imieniu" <<  endl << endl;
        }
    }

    wyjscieDoMenuGlownego();
}

void szukajAdresataPoNazwisku(vector <Adresat> & adresaci, int liczbaAdresatow)
{
    system("cls");
    cout << "-------------------------------------------" << endl;
    cout << "Ksiazka adresowa - wyszukiwanie po nazwisku" << endl;
    cout << "-------------------------------------------" << endl;

    string nazwisko;
    int i = 0, j = 0;

    if (liczbaAdresatow == 0)
    {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }
    else
    {
        cout << "Podaj nazwisko do wyszukania: ";
        cin >> nazwisko;
        cout << endl;

        while (i < liczbaAdresatow)
        {
            if (adresaci[i].nazwisko == nazwisko)
            {
                cout << "Id: " << adresaci[i].id << endl;
                cout << "Imie: " << adresaci[i].imie << endl;
                cout << "Nazwisko: " << adresaci[i].nazwisko << endl;
                cout << "Numer tel: " << adresaci[i].nrTel << endl;
                cout << "Email: " << adresaci[i].email << endl;
                cout << "Adres: " << adresaci[i].adres << endl;

                cout << endl;

                j++;
            }
            i++;
        }

        if (j == 0)
        {
            cout << "Brak osob w ksiazce adresowej o takim nazwisku" <<  endl << endl;
        }
    }

    wyjscieDoMenuGlownego();
}

void wyswietlWszystkichAdresatow(vector <Adresat> & adresaci, int liczbaAdresatow)
{
    system("cls");
    cout << "-----------------------------------------------" << endl;
    cout << "Ksiazka adresowa - wyswietlanie wszystkich osob" << endl;
    cout << "-----------------------------------------------" << endl;

    if (liczbaAdresatow == 0)
    {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }
    else
    {
        for (int i = 0; i < liczbaAdresatow; i++)
        {
            cout << "Id: " << adresaci[i].id << endl;
            cout << "Imie: " << adresaci[i].imie << endl;
            cout << "Nazwisko: " << adresaci[i].nazwisko << endl;
            cout << "Numer tel: " << adresaci[i].nrTel << endl;
            cout << "Email: " << adresaci[i].email << endl;
            cout << "Adres: " << adresaci[i].adres << endl;
            cout << endl;
        }
    }

    wyjscieDoMenuGlownego();
}

int wczytajDaneZPlikuTekstowegoAdresaci(vector <Adresat> & adresaci, int liczbaAdresatow, int idZalogowanegoUzytkownika)
{
    int dlugoscLinii;
    int pozycjaSeparatora[7];

    adresaci.push_back(Adresat());

    string id, imie, nazwisko, nrTel, email, adres;
    string linia, idUzytkownika;
    fstream plikTekstowy;

    plikTekstowy.open("Adresaci.txt", ios::in);

    if (plikTekstowy.good() == true)
    {
        while (getline(plikTekstowy, linia))
        {
            dlugoscLinii = linia.length();
            int n = 0;
            for (int i = 0; i < dlugoscLinii; i++)
            {
                if (linia[i] == '|')
                {
                    pozycjaSeparatora[n] = i;
                    n++;
                }
            }

            idUzytkownika = "";
            id = "";

            for (int i = pozycjaSeparatora[0] + 1; i < pozycjaSeparatora[1]; i++)
            {
                idUzytkownika.push_back(linia[i]);
            }

            if(atoi(idUzytkownika.c_str()) != idZalogowanegoUzytkownika)
            {
                continue;
            }
            else
            {
                for (int i = 0; i < pozycjaSeparatora[0]; i++)
                {
                    id.push_back(linia[i]);
                }

                adresaci.push_back(Adresat());
                adresaci[liczbaAdresatow].id = atoi(id.c_str());

                for (int i = pozycjaSeparatora[1] + 1; i < pozycjaSeparatora[2]; i++)
                {
                    adresaci[liczbaAdresatow].imie.push_back(linia[i]);
                    adresaci.push_back(Adresat());
                }

                for (int i = pozycjaSeparatora[2] + 1; i < pozycjaSeparatora[3]; i++)
                {
                    adresaci[liczbaAdresatow].nazwisko.push_back(linia[i]);
                    adresaci.push_back(Adresat());
                }

                for (int i = pozycjaSeparatora[3] + 1; i < pozycjaSeparatora[4]; i++)
                {
                    adresaci[liczbaAdresatow].nrTel.push_back(linia[i]);
                    adresaci.push_back(Adresat());
                }

                for (int i = pozycjaSeparatora[4] + 1; i < pozycjaSeparatora[5]; i++)
                {
                    adresaci[liczbaAdresatow].email.push_back(linia[i]);
                    adresaci.push_back(Adresat());
                }

                for (int i = pozycjaSeparatora[5] + 1; i < pozycjaSeparatora[6]; i++)
                {
                    adresaci[liczbaAdresatow].adres.push_back(linia[i]);
                    adresaci.push_back(Adresat());
                }

                liczbaAdresatow++;
            }
        }

        plikTekstowy.close();
    }
    else
    {
        liczbaAdresatow = 0;
    }

    return liczbaAdresatow;
}

int usunAdresata(vector <Adresat> & adresaci, int liczbaAdresatow)
{
    system("cls");
    cout << "------------------------------------" << endl;
    cout << "Ksiazka adresowa - usuwanie adresata" << endl;
    cout << "------------------------------------" << endl;

    char wprowadzonyZnakZKlawiatury;
    int nrIndeksuDoUsuniecia, doUsuniecia;
    int liczbaPominiec = 0;

    int dlugoscLinii;
    int pozycjaSeparatora[7];

    string linia, id;
    fstream plikTekstowy;
    fstream plikTekstowyTymczasowy;

    cout << "Podaj numer indeksu adresata do usuniecia: ";
    cin >> nrIndeksuDoUsuniecia;

    for (int i = 0; i < liczbaAdresatow; i++)
    {
        if (adresaci[i].id == nrIndeksuDoUsuniecia)
        {
            doUsuniecia = i;
        }
        else
        {
            liczbaPominiec++;
        }
    }

    if (liczbaPominiec == liczbaAdresatow)
    {
        cout << endl << "Brak adresata o takim indeksie" << endl;
        Sleep(1500);
    }
    else
    {
        do
        {
            cout << endl << "Czy na pewno chcesz usunac wybranego adresata? [t/n] ";
            cin >> wprowadzonyZnakZKlawiatury;

            if (wprowadzonyZnakZKlawiatury == 't')
            {
                adresaci.erase(adresaci.begin() + doUsuniecia);
                liczbaAdresatow--;

                plikTekstowy.open("Adresaci.txt", ios::in);

                plikTekstowyTymczasowy.open("Adresaci_tymczasowy.txt",ios::out);

                if (plikTekstowy.good() == true)
                {
                    while (getline(plikTekstowy, linia))
                    {
                        dlugoscLinii = linia.length();
                        int n = 0;
                        for (int i = 0; i < dlugoscLinii; i++)
                        {
                            if (linia[i] == '|')
                            {
                                pozycjaSeparatora[n] = i;
                                n++;
                            }
                        }

                        id = "";

                        for (int i = 0; i < pozycjaSeparatora[0]; i++)
                        {
                            id.push_back(linia[i]);
                        }

                        if(atoi(id.c_str()) != nrIndeksuDoUsuniecia)
                        {
                            plikTekstowyTymczasowy << linia << endl;
                        }
                    }
                }

                plikTekstowy.close();
                plikTekstowyTymczasowy.close();

                remove("Adresaci.txt");
                rename("Adresaci_tymczasowy.txt", "Adresaci.txt");

                cout << endl << "Adresat zostal usuniety" << endl;
                Sleep(1500);

                break;
            }

            if (wprowadzonyZnakZKlawiatury == 'n')
            {
                break;
            }
        }
        while (wprowadzonyZnakZKlawiatury != 't' || wprowadzonyZnakZKlawiatury != 'n');
    }

    return liczbaAdresatow;
}

void edytujAdresata(vector <Adresat> & adresaci, int liczbaAdresatow, int idZalogowanegoUzytkownika)
{
    system("cls");
    cout << "----------------------------------" << endl;
    cout << "Ksiazka adresowa - edycja adresata" << endl;
    cout << "----------------------------------" << endl;

    char wprowadzonyZnakZKlawiatury;
    int nrIndeksuDoEdycji, doEdycji;
    int liczbaPominiec = 0;

    int dlugoscLinii;
    int pozycjaSeparatora[7];

    string edytowanaWartosc;
    string linia, id;
    fstream plikTekstowy;
    fstream plikTekstowyTymczasowy;

    cout << "Podaj numer indeksu adresata do edycji: ";
    cin >> nrIndeksuDoEdycji;

    for (int i = 0; i < liczbaAdresatow; i++)
    {
        if (adresaci[i].id == nrIndeksuDoEdycji)
        {
            doEdycji = i;
        }
        else
        {
            liczbaPominiec++;
        }
    }

    if (liczbaPominiec == liczbaAdresatow)
    {
        cout << endl << "Brak adresata o takim indeksie" << endl;
        Sleep(1500);
    }
    else
    {
        cout << endl;
        cout << "1. Edytuj imie" << endl;
        cout << "2. Edytuj nazwisko" << endl;
        cout << "3. Edytuj numer telefonu" << endl;
        cout << "4. Edytuj email" << endl;
        cout << "5. Edytuj adres" << endl;
        cout << "6. Wyjdz" << endl;

        cin >> wprowadzonyZnakZKlawiatury;

        if (wprowadzonyZnakZKlawiatury == '1')
        {
            cout << "Podaj nowe imie: ";
            cin >> edytowanaWartosc;
            adresaci[doEdycji].imie = edytowanaWartosc;
        }
        else if (wprowadzonyZnakZKlawiatury == '2')
        {
            cout << "Podaj nowe nazwisko: ";
            cin >> edytowanaWartosc;
            adresaci[doEdycji].nazwisko = edytowanaWartosc;
        }
        else if (wprowadzonyZnakZKlawiatury == '3')
        {
            cout << "Podaj nowy numer telefonu: ";
            cin >> edytowanaWartosc;
            adresaci[doEdycji].nrTel = edytowanaWartosc;
        }
        else if (wprowadzonyZnakZKlawiatury == '4')
        {
            cout << "Podaj nowy adres email: ";
            cin >> edytowanaWartosc;
            adresaci[doEdycji].email = edytowanaWartosc;
        }
        else if (wprowadzonyZnakZKlawiatury == '5')
        {
            cout << "Podaj nowy adres: ";
            cin.sync();
            getline(cin, edytowanaWartosc);
            adresaci[doEdycji].adres = edytowanaWartosc;
        }
        else if (wprowadzonyZnakZKlawiatury == '6')
        {
            return;
        }

        plikTekstowy.open("Adresaci.txt", ios::in);

        plikTekstowyTymczasowy.open("Adresaci_tymczasowy.txt",ios::out);

        if (plikTekstowy.good() == true)
        {
            while (getline(plikTekstowy, linia))
            {
                dlugoscLinii = linia.length();
                int n = 0;
                for (int i = 0; i < dlugoscLinii; i++)
                {
                    if (linia[i] == '|')
                    {
                        pozycjaSeparatora[n] = i;
                        n++;
                    }
                }

                id = "";

                for (int i = 0; i < pozycjaSeparatora[0]; i++)
                {
                    id.push_back(linia[i]);
                }

                if(atoi(id.c_str()) != nrIndeksuDoEdycji)
                {
                    plikTekstowyTymczasowy << linia << endl;
                }
                else
                {
                    plikTekstowyTymczasowy << adresaci[doEdycji].id << "|";
                    plikTekstowyTymczasowy << idZalogowanegoUzytkownika << "|";
                    plikTekstowyTymczasowy << adresaci[doEdycji].imie << "|";
                    plikTekstowyTymczasowy << adresaci[doEdycji].nazwisko << "|";
                    plikTekstowyTymczasowy << adresaci[doEdycji].nrTel << "|";
                    plikTekstowyTymczasowy << adresaci[doEdycji].email << "|";
                    plikTekstowyTymczasowy << adresaci[doEdycji].adres << "|" << endl;
                }
            }
        }

        plikTekstowy.close();
        plikTekstowyTymczasowy.close();

        remove("Adresaci.txt");
        rename("Adresaci_tymczasowy.txt", "Adresaci.txt");

        cout << endl << "Wprowadzono zmiany" << endl;
        Sleep(1500);
    }
}

void wyjscieDoMenuGlownego()
{
    char wprowadzonyZnakZKlawiatury;

    while (wprowadzonyZnakZKlawiatury != '1')
    {
        cout << "1. Wyjdz" << endl;
        cin >> wprowadzonyZnakZKlawiatury;
    }
}
