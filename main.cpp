#include <iostream>
#include "Couple.h"
#include "TableHachage.h"
using namespace std;

int main()
{
	// Section #1
	int cle[]    = {2, 5, 8, 34, 22, 55, 9, 56, 11,  3, 5};
	int valeur[] = {1, 2, 3,  4,  5,  6, 7,  8,  9, 10, 200};
	const int M = 10;

	// Section #2
	TableHachage th(M);

	// Section #3
	for (int x = 0; x < 10; x++)
		th.ajouter(cle[x], valeur[x]);

	// Section #4
	cout << th << endl;

	// Section #5
	th.supprimer(5);
	th.ajouter(cle[10], valeur[10]);
	th.ajouter(cle[1], valeur[1]);

	// Section #6
	cout << th << endl;

	// Section #7
	cout << "Recherche #1 (cle : 22)  : " << th.rechercher(22) << endl;
	cout << "Recherche #2 (cle : 122) : " << th.rechercher(122) << endl;

	return 0;
}