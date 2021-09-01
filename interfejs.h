#ifndef INTERFEJS_H
#define INTERFEJS_H

#include "przepis.h"

struct Interfejs
{
    Lista_Przepisow lista_przepisow;

    void Start();
    void Wyswietl_Menu();
    void Szczegoly_Przepisu();
    void Wyszukaj_Przepis();
    void Dodaj_Przepis();
};

#endif
