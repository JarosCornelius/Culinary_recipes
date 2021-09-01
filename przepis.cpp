#include "przepis.h"

void Lista_Przepisow::Wczytaj_Baze_Danych()
{
    fstream plik;
    plik.open( type directory to BAZA_DANYCH, ios::in);

        // sprawdza, czy plik został poprawnie otwarty
    if(plik.good())
    {
            // wczytuje wszystkie linie z pliku
        while(plik.eof() == false)
        {
            string obiekt; // wczytanie [P: ,S: ,W: ,O:]
            plik >> obiekt;

            switch(obiekt[0])
            {
                case 'S': // dodawanie Skladnika
                {
                    int id;
                    string nazwa;

                    plik >> id >> nazwa;
                    Dodaj_Skladnik(id, nazwa);

                    break;
                }

                case 'P': // dodawanie Przepisu
                {
                    int id, czas;
                    string nazwa, opis;

                    plik >> id >> nazwa >> czas;
                    getline(plik, opis); // pobieranie linii - opis
                    getline(plik, opis);
                    Dodaj_Przepis(id, nazwa, czas, opis);

                    break;
                }

                case 'W': // dodawanie Wymagane składniki
                {
                    int id_skladnika, id_przepisu;
                    plik >> id_skladnika >> id_przepisu;
                    Dodaj_Wymagane(id_skladnika, id_przepisu);

                    break;
                }

                case 'O': // dodawanie Opcjonalne składniki
                {
                    int id_skladnika, id_przepisu;
                    plik >> id_skladnika >> id_przepisu;
                    Dodaj_Opcjonalne(id_skladnika, id_przepisu);

                    break;
                }
            }
        }

        plik.close();
    }
    else cout << "Error: Wczytywanie bazy danych nie powiodlo sie.";
}

string Lista_Przepisow::Generuj_Komorke(string zawartosc)
{
        // wypełnienie
    int szerokosc_komorki = 15;
    int liczba_spacji = szerokosc_komorki - zawartosc.length();
    for (int k = 0; k < liczba_spacji; ++k)
        zawartosc += ' ';

    return "  " + zawartosc; // kilka spacji z przodu
}

void Lista_Przepisow::Wyswietl_Przepisy()
{
        // pierwszy wiersz (opisowy)
    Wyswietl_Naglowek();
    cout << endl << endl;

        // wypisywanie w każdym wierszu jednego przepisa
    for (Przepis przepis: przepisy)
    {
        Wyswietl_Rekord(przepis);
        cout << endl;
    }

    cout << endl;
}

void Lista_Przepisow::Wyswietl_Przepisy(vector<Przepis> lista)
{
        // pierwszy wiersz (opisowy)
    Wyswietl_Naglowek();
    cout << endl << endl;

        // wypisywanie w każdym wierszu jednego przepisa
    for (Przepis przepis: lista)
    {
        Wyswietl_Rekord(przepis);
        cout << endl;
    }

    cout << endl;
}

void Lista_Przepisow::Wyswietl_Naglowek()
{
    cout << endl;
    cout << Generuj_Komorke("ID");
    cout << Generuj_Komorke("NAZWA");
    cout << Generuj_Komorke("CZAS (MIN)");
}

void Lista_Przepisow::Wyswietl_Rekord(Przepis przepis)
{
    cout << Generuj_Komorke(to_string(przepis.id));
    cout << Generuj_Komorke(przepis.nazwa);
    cout << Generuj_Komorke(to_string(przepis.czas));
}

void Lista_Przepisow::Wyswietl_Jeden_Przepis(int id)
{
        // pobiera przepis
    Przepis przepis = Pobierz_Przepis(id);

        // dane szczegółowe przepisu
    cout << "OPIS PRZEPISU:" << endl << endl;
    cout << Generuj_Komorke("   NAZWA: ") << przepis.nazwa << endl;
    cout << Generuj_Komorke("   CZAS: ") << przepis.czas << " MIN" << endl;

        // dane szczegółowe przepisu - składniki wymagane
    cout << Generuj_Komorke("   WYMAGANE: ");
    for (Wymagane wymagany : wymagane)
    {
        if (wymagany.przepis == id)
        {
            Skladnik skladnik = Pobierz_Skladnik(wymagany.skladnik);
            cout << skladnik.nazwa << ", ";
        }
    }

        // dane szczegółowe przepisu - składniki opcjonalne
    cout << endl << Generuj_Komorke("   OPCJONALNE: ");
    for (Opcjonalne opcjonalny : opcjonalne)
    {
        if (opcjonalny.przepis == id)
        {
            Skladnik skladnik = Pobierz_Skladnik(opcjonalny.skladnik);
            cout << skladnik.nazwa << ", ";
        }
    }

    cout << endl;
    cout << Generuj_Komorke("   OPIS: ") << przepis.opis << endl << endl;
}

Przepis Lista_Przepisow::Pobierz_Przepis(int id)
{
    for (Przepis przepis: przepisy)
    {
        if (przepis.id == id)
            return przepis;
    }

    return Przepis(); // gdy nie znajdzie
}

Skladnik Lista_Przepisow::Pobierz_Skladnik(int id)
{
    for (Skladnik skladnik: skladniki)
    {
        if (skladnik.id == id)
            return skladnik;
    }

    return Skladnik(); // gdy nie znajdzie
}

Skladnik Lista_Przepisow::Pobierz_Skladnik(string nazwa)
{
    for (Skladnik skladnik: skladniki)
    {
        if (skladnik.nazwa == nazwa)
            return skladnik;
    }

    return Skladnik(); // gdy nie znajdzie
}

void Lista_Przepisow::Dodaj_Przepis(int id, string nazwa, int czas, string opis)
{
        // tworzy nowy element listy
    Przepis nowy;

        // wypełnia naszymi danymi
    nowy.id = id;
    nowy.nazwa = nazwa;
    nowy.czas = czas;
    nowy.opis = opis;

        // wrzuca na listę przepisów
    przepisy.push_back(nowy);
}

void Lista_Przepisow::Dodaj_Skladnik(int id, string nazwa)
{
        // tworzy nowy element listy
    Skladnik nowy;

        // wypełnia naszymi danymi
    nowy.id = id;
    nowy.nazwa = nazwa;

        // wrzuca na listę przepisów
    skladniki.push_back(nowy);
}

void Lista_Przepisow::Dodaj_Wymagane(int id_skladnika, int id_przepisu)
{
        // tworzy nowy element listy
    Wymagane nowy;

        // wypełnia naszymi danymi
    nowy.skladnik = id_skladnika;
    nowy.przepis = id_przepisu;

        // wrzuca na listę przepisów
    wymagane.push_back(nowy);
}

void Lista_Przepisow::Dodaj_Opcjonalne(int id_skladnika, int id_przepisu)
{
        // tworzy nowy element listy
    Opcjonalne nowy;

        // wypełnia naszymi danymi
    nowy.skladnik = id_skladnika;
    nowy.przepis = id_przepisu;

        // wrzuca na listę przepisów
    opcjonalne.push_back(nowy);
}

bool Lista_Przepisow::Przepis_Zawiera_Skladnik(Przepis przepis, Skladnik skladnik)
{
        // jeżeli to jest wymagany składnik przepisu
    for (Wymagane wymagany : wymagane)
    {
        if (wymagany.przepis == przepis.id)
            if (wymagany.skladnik == skladnik.id)
                return true;
    }

        // jeżeli to jest opcjonalny składnik przepisu
    for (Opcjonalne opcjonalny : opcjonalne)
    {
        if (opcjonalny.przepis == przepis.id)
            if (opcjonalny.skladnik == skladnik.id)
                return true;
    }

    return false;
}

bool Lista_Przepisow::Przepis_Istnieje_W_Liscie(Przepis przepis, vector<Przepis> lista)
{
        // sprawdza, czy w lista znajduje się podany przepis
    for (Przepis temp : lista)
    {
        if (przepis.id == temp.id)
            return true;
    }

    return false;
}

vector<Przepis> Lista_Przepisow::Filtruj(vector<string> nazwy_skladnikow)
{
    vector<Przepis> przefiltrowane;
    vector<Skladnik> lista_skladnikow;

        // konwertowanie nazw składników do listy składników
    for (string nazwa_skladnika : nazwy_skladnikow)
        lista_skladnikow.push_back(Pobierz_Skladnik(nazwa_skladnika));

        // tworzy listę przefiltrowanych przepisów
    for (Skladnik skladnik : lista_skladnikow)
    {
        for (Przepis przepis : przepisy)
        {
            if(Przepis_Zawiera_Skladnik(przepis, skladnik)) // ten przepis zawiera taki składnik
                if(Przepis_Istnieje_W_Liscie(przepis, przefiltrowane) == false) // w przefiltrowane nie ma jeszcze takiego przepisu
                    przefiltrowane.push_back(przepis); // dodaję przepis do listy przefiltrowanych
        }
    }

        // wynik
    return przefiltrowane;
}

