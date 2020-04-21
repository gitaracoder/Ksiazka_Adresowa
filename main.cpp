#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Adresat
{
    int id;
    string imie, nazwisko, nrTel, email, adres;
};

int wczytajDaneZPlikuTekstowego(vector <Adresat> & adresaci, int liczbaOsob);
int dodajOsobe(vector <Adresat> & adresaci, int liczbaOsob);
void szukajOsobePoImieniu(vector <Adresat> & adresaci, int liczbaOsob);
void szukajOsobePoNazwisku(vector <Adresat> & adresaci, int liczbaOsob);
void wyswietlWszystkieOsoby(vector <Adresat> & adresaci, int liczbaOsob);
void edytujAdresata(vector <Adresat> & adresaci, int liczbaOsob);
int usunAdresata(vector <Adresat> & adresaci, int liczbaOsob);
void wyjscieDoMenuGlownego();

int main()
{
    vector <Adresat> adresaci;
    int liczbaOsob = 0;

    liczbaOsob = wczytajDaneZPlikuTekstowego(adresaci, liczbaOsob);

    while(1)
    {
        system("cls");
        cout << "------------------------------" << endl;
        cout << "Ksiazka adresowa - menu glowne" << endl;
        cout << "------------------------------" << endl;

        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zamknij program" << endl;

        char wprowadzonyZnakZKlawiatury;
        cin >> wprowadzonyZnakZKlawiatury;

        if (wprowadzonyZnakZKlawiatury == '1')
        {
            liczbaOsob = dodajOsobe(adresaci, liczbaOsob);
        }
        else if (wprowadzonyZnakZKlawiatury == '2')
        {
            szukajOsobePoImieniu(adresaci, liczbaOsob);
        }
        else if (wprowadzonyZnakZKlawiatury == '3')
        {
            szukajOsobePoNazwisku(adresaci, liczbaOsob);
        }
        else if (wprowadzonyZnakZKlawiatury == '4')
        {
            wyswietlWszystkieOsoby(adresaci, liczbaOsob);
        }
        else if (wprowadzonyZnakZKlawiatury == '5')
        {
            liczbaOsob = usunAdresata(adresaci, liczbaOsob);
        }
        else if (wprowadzonyZnakZKlawiatury == '6')
        {
            edytujAdresata(adresaci, liczbaOsob);
        }
        else if (wprowadzonyZnakZKlawiatury == '9')
        {
            exit(0);
        }
    }

    return 0;
}

int dodajOsobe(vector <Adresat> & adresaci, int liczbaOsob)
{
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
    adresaci[liczbaOsob].imie = imie;
    adresaci.push_back(Adresat());
    adresaci[liczbaOsob].nazwisko = nazwisko;
    adresaci.push_back(Adresat());
    adresaci[liczbaOsob].nrTel = nrTel;
    adresaci.push_back(Adresat());
    adresaci[liczbaOsob].email = email;
    adresaci.push_back(Adresat());
    adresaci[liczbaOsob].adres = adres;
    adresaci.push_back(Adresat());

    if (liczbaOsob == 0)
    {
        adresaci[liczbaOsob].id =  1;
    }
    else
    {
        adresaci[liczbaOsob].id = adresaci[liczbaOsob - 1].id + 1;
    }

    plikTekstowy.open("indeksy.txt", ios::out | ios::app);

    if (plikTekstowy.good() == true)
    {
        plikTekstowy << adresaci[liczbaOsob].id << "|";
        plikTekstowy << adresaci[liczbaOsob].imie << "|";
        plikTekstowy << adresaci[liczbaOsob].nazwisko << "|";
        plikTekstowy << adresaci[liczbaOsob].nrTel << "|";
        plikTekstowy << adresaci[liczbaOsob].email << "|";
        plikTekstowy << adresaci[liczbaOsob].adres << "|" << endl;
    }

    plikTekstowy.close();

    cout << endl;
    cout << "Dodano osobe do ksiazki adresowej" << endl << endl;
    cout << "Indeks dodanej osoby to: " << adresaci[liczbaOsob].id << endl << endl;

    wyjscieDoMenuGlownego();

    return liczbaOsob + 1;
}

void szukajOsobePoImieniu(vector <Adresat> & adresaci, int liczbaOsob)
{
    system("cls");
    cout << "------------------------------------------" << endl;
    cout << "Ksiazka adresowa - wyszukiwanie po imieniu" << endl;
    cout << "------------------------------------------" << endl;

    string imie;
    int i = 0, j = 0;

    if (liczbaOsob == 0)
    {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }
    else
    {
        cout << "Podaj imie do wyszukania: ";
        cin >> imie;
        cout << endl;

        while (i < liczbaOsob)
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

void szukajOsobePoNazwisku(vector <Adresat> & adresaci, int liczbaOsob)
{
    system("cls");
    cout << "-------------------------------------------" << endl;
    cout << "Ksiazka adresowa - wyszukiwanie po nazwisku" << endl;
    cout << "-------------------------------------------" << endl;

    string nazwisko;
    int i = 0, j = 0;

    if (liczbaOsob == 0)
    {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }
    else
    {
        cout << "Podaj nazwisko do wyszukania: ";
        cin >> nazwisko;
        cout << endl;

        while (i < liczbaOsob)
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

void wyswietlWszystkieOsoby(vector <Adresat> & adresaci, int liczbaOsob)
{
    system("cls");
    cout << "-----------------------------------------------" << endl;
    cout << "Ksiazka adresowa - wyswietlanie wszystkich osob" << endl;
    cout << "-----------------------------------------------" << endl;

    if (liczbaOsob == 0)
    {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }
    else
    {
        for (int i = 0; i < liczbaOsob; i++)
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

int wczytajDaneZPlikuTekstowego(vector <Adresat> & adresaci, int liczbaOsob)
{

    int dlugoscLinii;
    int pozycjaSeparatora[6];

    adresaci.push_back(Adresat());

    string id, imie, nazwisko, nrTel, email, adres;
    string linia;
    fstream plikTekstowy;

    plikTekstowy.open("indeksy.txt", ios::in);

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

            adresaci.push_back(Adresat());
            adresaci[liczbaOsob].id = atoi(id.c_str());

            for (int i = pozycjaSeparatora[0] + 1; i < pozycjaSeparatora[1]; i++)
            {
                adresaci[liczbaOsob].imie.push_back(linia[i]);
                adresaci.push_back(Adresat());
            }

            for (int i = pozycjaSeparatora[1] + 1; i < pozycjaSeparatora[2]; i++)
            {
                adresaci[liczbaOsob].nazwisko.push_back(linia[i]);
                adresaci.push_back(Adresat());
            }

            for (int i = pozycjaSeparatora[2] + 1; i < pozycjaSeparatora[3]; i++)
            {
                adresaci[liczbaOsob].nrTel.push_back(linia[i]);
                adresaci.push_back(Adresat());
            }

            for (int i = pozycjaSeparatora[3] + 1; i < pozycjaSeparatora[4]; i++)
            {
                adresaci[liczbaOsob].email.push_back(linia[i]);
                adresaci.push_back(Adresat());
            }

            for (int i = pozycjaSeparatora[4] + 1; i < pozycjaSeparatora[5]; i++)
            {
                adresaci[liczbaOsob].adres.push_back(linia[i]);
                adresaci.push_back(Adresat());
            }

            liczbaOsob++;
        }

        plikTekstowy.close();

    }
    else
    {
        liczbaOsob = 0;
    }

    return liczbaOsob;
}

int usunAdresata(vector <Adresat> & adresaci, int liczbaOsob)
{
    system("cls");
    cout << "------------------------------------" << endl;
    cout << "Ksiazka adresowa - usuwanie adresata" << endl;
    cout << "------------------------------------" << endl;

    char wprowadzonyZnakZKlawiatury;
    int nrIndeksuDoUsuniecia, doUsuniecia;
    int liczbaPominiec = 0;

    string linia;
    fstream plikTekstowy;

    cout << "Podaj numer indeksu adresata do usuniecia: ";
    cin >> nrIndeksuDoUsuniecia;

    for (int i = 0; i < liczbaOsob; i++)
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

    if (liczbaPominiec == liczbaOsob)
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
                liczbaOsob--;
                plikTekstowy.open("indeksy.txt", ios::out | ios::trunc);
                plikTekstowy.close();
                plikTekstowy.open("indeksy.txt", ios::out | ios::app);

                if (plikTekstowy.good() == true)
                {
                    for (int i = 0; i < liczbaOsob; i++)
                    {
                        plikTekstowy << adresaci[i].id << "|";
                        plikTekstowy << adresaci[i].imie << "|";
                        plikTekstowy << adresaci[i].nazwisko << "|";
                        plikTekstowy << adresaci[i].nrTel << "|";
                        plikTekstowy << adresaci[i].email << "|";
                        plikTekstowy << adresaci[i].adres << "|" << endl;
                    }
                }

                plikTekstowy.close();

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

    return liczbaOsob;
}

void edytujAdresata(vector <Adresat> & adresaci, int liczbaOsob)
{
    system("cls");
    cout << "----------------------------------" << endl;
    cout << "Ksiazka adresowa - edycja adresata" << endl;
    cout << "----------------------------------" << endl;

    char wprowadzonyZnakZKlawiatury;
    int nrIndeksuDoEdycji, doEdycji;
    int liczbaPominiec = 0;

    string edytowanaWartosc;
    string linia;
    fstream plikTekstowy;

    cout << "Podaj numer indeksu adresata do edycji: ";
    cin >> nrIndeksuDoEdycji;

    for (int i = 0; i < liczbaOsob; i++)
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

    if (liczbaPominiec == liczbaOsob)
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

        plikTekstowy.open("indeksy.txt", ios::out | ios::trunc);
        plikTekstowy.close();
        plikTekstowy.open("indeksy.txt", ios::out | ios::app);

        if (plikTekstowy.good() == true)
        {
            for (int i = 0; i < liczbaOsob; i++)
            {
                plikTekstowy << adresaci[i].id << "|";
                plikTekstowy << adresaci[i].imie << "|";
                plikTekstowy << adresaci[i].nazwisko << "|";
                plikTekstowy << adresaci[i].nrTel << "|";
                plikTekstowy << adresaci[i].email << "|";
                plikTekstowy << adresaci[i].adres << "|" << endl;
            }
        }

        plikTekstowy.close();

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


