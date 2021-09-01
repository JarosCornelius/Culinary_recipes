#include "interfejs.h"

void Interfejs::Start()
{
        // wpisywanie przykładowych danych
    lista_przepisow.Wczytaj_Baze_Danych();

        // pętla nieskończona programu
    while (true)
    {
            // wyświetlanie tabeli przepisow
        lista_przepisow.Wyswietl_Przepisy();

            // wczytywanie komendy podanej przez użytkownika
        char komenda;
        cout << "Podaj komende:    (jezeli nie znasz komend, wybierz '?')   ";
        cin >> komenda;

            // sprawdzanie co wybrał użytkownik
        switch (komenda)
        {
            case '?': // wyświetla menu
                Wyswietl_Menu();
                system("pause");
                break;

            case 'D': // szczegóły przepisu
                Szczegoly_Przepisu();
                system("pause");
                break;

            case 'W': // wyszukaj przepis
                Wyszukaj_Przepis();
                system("pause");
                break;

            case 'A': // dodaj przepis
                Dodaj_Przepis();
                system("pause");
                break;

            case 'Q': // koniec programu
                cout << "Koncze program." << endl;
                return; // wychodzi z funkcji - przerywa pętle
                break;

            default: // coś innego
                cout << "Taka komenda nieistnieje." << endl;
                system("pause");
                break;
        }

            // czyszczenie okna konsoli
        system("cls");
    }
}

void Interfejs::Wyswietl_Menu()
{
    cout << "? - wyswietlanie menu" << endl;
    cout << "Q - zakoncz program" << endl;
    cout << "W - wyszukiwanie przepisu" << endl;
    cout << "D - szczegoly przepisu" << endl;
    cout << "A - dodaj przepis" << endl;
}

void Interfejs::Szczegoly_Przepisu()
{
    int id_przepisu;

    cout << "Podaj ID przepisu: ";
    cin >> id_przepisu;

        // czyszczenie okna konsoli
    system("cls");

    lista_przepisow.Wyswietl_Jeden_Przepis(id_przepisu);
}

void Interfejs::Wyszukaj_Przepis()
{
    vector<string> lista_skladnikow;
    int liczba_skladnikow;
    string skladnik;

        // wczytuje liczbę składników
    cout << "Podaj liczbe skladnikow: ";
    cin >> liczba_skladnikow;

        // wczytuje składniki do wyszukania
    cout << "Podaj skladniki: ";
    for (int k = 0; k < liczba_skladnikow; ++k)
    {
        cin >> skladnik;
        lista_skladnikow.push_back(skladnik);
    }

        // filtrowanie
    vector<Przepis> przefiltrowane =
            lista_przepisow.Filtruj(lista_skladnikow);

        // wyświetlanie wyniku
    lista_przepisow.Wyswietl_Przepisy(przefiltrowane);
}

void Interfejs::Dodaj_Przepis()
{
    string nazwa, opis;
    int id, czas;

        // pobieranie informacji o przepis
    id = lista_przepisow.przepisy.size() + 1;
    cout << "Podaj nazwe: ";
    cin >> nazwa;

    cout << "Podaj czas (min): ";
    cin >> czas;

    cout << "Podaj opis: ";
    cin.ignore();
    getline(cin, opis);

        // zapisywanie nowego produktu
    lista_przepisow.Dodaj_Przepis(id, nazwa, czas, opis);

        // tworzenie powiązań z produktami
    int liczba_skladnikow;

        // wymagane składniki
    cout << "Podaj liczbe skladnikow wymaganych: ";
    cin >> liczba_skladnikow;

        // wczytuje składniki do wyszukania
    if (liczba_skladnikow != 0) cout << "Podaj skladniki: ";
    for (int k = 0; k < liczba_skladnikow; ++k)
    {
        cin >> nazwa;
        Skladnik skladnik = lista_przepisow.Pobierz_Skladnik(nazwa);
        lista_przepisow.Dodaj_Wymagane(skladnik.id, id);
    }

        // wymagane składniki
    cout << "Podaj liczbe skladnikow opcjonalnych: ";
    cin >> liczba_skladnikow;

        // wczytuje składniki do wyszukania
    if (liczba_skladnikow != 0) cout << "Podaj skladniki: ";
    for (int k = 0; k < liczba_skladnikow; ++k)
    {
        cin >> nazwa;
        Skladnik skladnik = lista_przepisow.Pobierz_Skladnik(nazwa);
        lista_przepisow.Dodaj_Opcjonalne(skladnik.id, id);
    }
}

