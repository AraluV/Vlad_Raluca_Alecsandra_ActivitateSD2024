#include<stdio.h>
#include<string.h>
#include<malloc.h>

//ARBORI

//un arbore este un graf, conex si aciclic
//descendentul din dreapta trebuie sa aiba nr mai mare din radacina
//descententul din stanga mai mic
//contine adresa din stanga si adresa dijn dreapta
//daca nodul nu are descendent se numeste nod frunza

typedef struct Cinema Cinema;
typedef struct Nod Nod;

struct Cinema {
	int id;
	char* nume;
	int nrFilme;
	char** listaFilme;
	
};

struct Nod {
	Cinema info;
	Nod* st;
	Nod* dr;
};

void inserareInArbore(Nod** radacina,Cinema c) { //inserare in arbore, radacina pointeaza catre NULL
	//verificam daca avem radacina(de facut mereu)
	if (*radacina) {
		if ((*radacina)->info.id > c.id) {//comparam info radacina cu info pe care tre sa adaugam
			inserareInArbore(&((*radacina)->st) , c);
		}
		else {
			inserareInArbore(&((*radacina)->dr), c);
		}
	}
	else {
		Nod* nod = malloc(sizeof(Nod));
		nod->dr = NULL; //inserarea se face intr-un nod frunza
		nod->st = NULL;
		nod->info = c;
		*radacina = nod; //
	}
}

Cinema citireCinema(FILE* f) {
	Cinema c;
	fscanf(f, "%d", &c.id);
	fscanf(f, "%d", &c.nrFilme);
	if (c.nrFilme != 0) {
		c.listaFilme =(char**)malloc(sizeof(char*)*c.nrFilme);
		for (int i = 0; i < c.nrFilme; i++) {//alocare spatiu pentru liste de filme
			char buffer[100];
			fscanf(f,"%s", buffer);
			c.listaFilme[i] = malloc(sizeof(char) * strlen(buffer)+1);
			strcpy(c.listaFilme[i], buffer);
		}
	}else{
		c.listaFilme = NULL;
	}
	return c;
}

Nod* citireFisier(const char* fisier) {
	Nod* radacina = NULL;
	if (fisier != NULL && strlen(fisier) != 0) {
		FILE* f = fopen(fisier, "r");
		if (f != NULL) {
			int dim = 0;
			fscanf(f, "%d",&dim);
			for (int i = 0; i < dim; i++) {
				Cinema cinema;
				cinema = citireCinema(f);
				inserareInArbore(&radacina, cinema);
			}
		}
	}
	return radacina;
}

void afisareCinema(Cinema c) {
	printf("Cinematograful cu id-ul &d are in derulare %d filme:", c.id, c.nrFilme);
	for (int i = 0; i < c.nrFilme; i++) {
		printf("%s", c.listaFilme[i]);
	}
	printf("\n");
}

void afisareArborePreordine(Nod* rad) {
	if (rad) {
		afisareCinema(rad->info);
		afisareArborePreordine(rad->st);
		afisareArborePreordine(rad->dr);
	}
}

void afisareArboreInOrdine(Nod* rad) {
	if (rad) {
		afisareArboreInOrdine(rad->st);
		afisareCinema(rad->info);
		afisareArboreInOrdine(rad->dr);

	}
}

int calculnrFilmeRedate(Nod* rad) {
	if (rad) {
		int suma = rad->info.nrFilme;
		suma += calculnrFilmeRedate(rad->st);
		suma += calculnrFilmeRedate(rad->dr);
		return suma;
	}
	else {
		return 0;
	}
}

void main() {
	Nod* arbore = NULL;   //adresa primului nod
	arbore = citireFisier("cinema.txt");
	afisareArboreInOrdine(arbore);
	printf("\n\nNumar filme: %d", calculnrFilmeRedate(arbore));

}