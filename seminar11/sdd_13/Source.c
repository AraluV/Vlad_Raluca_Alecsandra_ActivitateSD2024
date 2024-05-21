#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Metrou Metrou;
typedef struct NodPrincipal NodPrincipal;
typedef struct NodSecundar NodSecundar;

struct Metrou {
	int serie;
	int nrStatie;
	char* magistrale;
};

struct NodPrincipal {
	Metrou info;
	NodSecundar* vecini;
	NodPrincipal* next;
};

struct NodSecundar {
	NodPrincipal* nod;
	NodSecundar* next;
};

//functie initializare Metrou
Metrou initializareMetrou(int serie, int nrStatie, char* magistrale) {
	Metrou m;
	m.serie = serie;
	m.nrStatie = nrStatie;
	m.magistrale = (char*)malloc((strlen(magistrale) + 1) * sizeof(char));
	strcpy_s(m.magistrale, strlen(magistrale)+1,magistrale);
	return m;
}

//inserare la inceput la lista principala
void inserarePrincipala(NodPrincipal** cap, Metrou m) {
	NodPrincipal* nou = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nou->info = m;
	nou->next = *cap;
	nou->vecini = NULL;
	*cap = nou;
}

//cautare nod dupa serie
NodPrincipal* cautareNod(NodPrincipal* graf, int serie) {
	while (graf && graf->info.serie != serie) {
		graf = graf->next;
	}
	return graf;
}

//inserare la final in lista secundara
NodSecundar*  inserareSecundar(NodSecundar* cap, NodPrincipal* info) {
	NodSecundar* nou = (NodSecundar*)malloc(sizeof(NodSecundar));
	nou->nod = info;
	nou->next = NULL;
	if (cap) {
		NodSecundar* aux = cap;
		while (aux->next) {
			aux = aux->next;
		}
		aux = nou;
	}
	else {
		return nou;
	}
}

//inserare muchie
void adaugareMuchie(NodPrincipal* graf, int serieStart, int serieStop) {
	NodPrincipal* nodStart = cautareNod(&graf, serieStart);
	NodPrincipal* nodStop = cautareNod(&graf, serieStop);

	if (nodStart && nodStop) {
		nodStart->vecini = inserareSecundar(nodStart->vecini, nodStop);
		nodStop->vecini = inserareSecundar(nodStop->vecini, nodStart);
	}
}

//functia de dezalocare


void main() {
	NodPrincipal* graf = NULL;

	inserarePrincipala(&graf, initializareMetrou(0, 1, "Rosie"));
	inserarePrincipala(&graf, initializareMetrou(1, 2, "Albastra"));
	inserarePrincipala(&graf, initializareMetrou(2, 3, "Galbena"));

	adaugareMuchie(graf, 0, 1);
	adaugareMuchie(graf, 0, 2);
	adaugareMuchie(graf, 1, 2);

}