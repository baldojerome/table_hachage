#ifndef Couple_H
#define Couple_H

#include <iostream>
using namespace std;

class Couple
{
public:
	Couple(int cle, int valeur) {this->cle = cle; this->valeur = valeur;}
	int getCle() {return cle;}
	int getValeur() {return valeur;}

	bool operator<(const Couple& couple) {return cle < couple.cle;} const
	bool operator==(const Couple& couple) {return cle == couple.cle;} const
	bool operator>(const Couple& couple) {return cle > couple.cle;} const
	bool operator!=(const Couple& couple) {return cle != couple.cle;} const
	friend ostream &operator<< (ostream& out, const Couple& couple) {out << "(" << couple.cle << ", \t" << couple.valeur << ")"; return out;}
	Couple& operator=(const Couple& couple)
	{
		if( this == &couple) return *this;
		valeur = couple.valeur;
		cle = couple.cle;
	}

private:
	int cle;
	int valeur;
};

#endif