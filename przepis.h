#ifndef PRZEPIS_H


#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

struct Skladnik
{
    int id;
    string nazwa;
};

struct Przepis
{
    int id;
    string nazwa;
    int czas; // w minutach
    string opis;
};

struct Wymagane
{
    int skladnik;
    int przepis;
};

struct Opcjonalne
{
    int skladnik;
    int przepis;
};



struct Lista_Przepisow
{
    vector<Przepis> przepisy;
    vector<Skladnik> skladniki;
    vector<Wymagane> wymagane;
    vector<Opcjonalne> opcjonalne;

    void Wczytaj_Baze_Danych();
    string Generuj_Komorke(string zawartosc);

        // funkcje dla przepisów
    void Wyswietl_Przepisy();
    void Wyswietl_Przepisy(vector<Przepis> lista);
    void Wyswietl_Naglowek();
    void Wyswietl_Rekord(Przepis przepis);
    void Wyswietl_Jeden_Przepis(int id);

    Przepis Pobierz_Przepis(int id);
    Skladnik Pobierz_Skladnik(int id);
    Skladnik Pobierz_Skladnik(string nazwa);

    void Dodaj_Przepis(int id, string nazwa, int czas, string opis);
    void Dodaj_Skladnik(int id, string nazwa);
    void Dodaj_Wymagane(int id_skladnika, int id_przepisu);
    void Dodaj_Opcjonalne(int id_skladnika, int id_przepisu);

    bool Przepis_Zawiera_Skladnik(Przepis przepis, Skladnik skladnik);
    bool Przepis_Istnieje_W_Liscie(Przepis przepis, vector<Przepis> lista);
    vector<Przepis> Filtruj(vector<string> skladniki);
};

#endif
