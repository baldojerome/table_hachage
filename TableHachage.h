#ifndef TABLEHACHAGE_H
#define TABLEHACHAGE_H

#include <list>
#include "Couple.h"
using namespace std;

class TableHachage
{
public:
	TableHachage(int m);
	~TableHachage();
	void ajouter(int cle, int valeur);
	bool supprimer(int cle);
	int rechercher(int cle);
	friend ostream &operator<< (ostream& out, const TableHachage& tableHachage);

private:
	int m;
	list<Couple>* T;
	int hachage(int cle);
};

#endif