#include "TableHachage.h"

//BALDO JEROME - BALJ17058609


TableHachage::TableHachage(int m)
{
	this->m = m;					// La taille du tableau
	T = new list<Couple>[m];		// Le tableau de Couple (taille m)
}

TableHachage::~TableHachage()
{
	delete[] T;						// On efface le tableau lors de la destruction de la table de hachage 
									// pour éviter une fuite de mémoire  
									// (Rappel : Si on utilise un pointeur  (new) alors il faut un delete)
}

// Ajout trié dans la liste
//methode pour ajouter une paire clé/valeur dans la table de hache 
//en entree : clé + valeur 

void TableHachage::ajouter(int cle, int valeur)
{
	int x = 0;
	while (x < this->m)
	{
		// Trouver la bonne position (ou alvéole) dans le tableau  *** Par hachage évidemment ***
		int numHach = this->hachage(cle);
		if (numHach == x)
		{
			Couple couple(cle, valeur);
			list<Couple>::iterator itCouple;
			for (itCouple = this->T[x].begin(); itCouple != this->T[x].end(); itCouple++)
			{
				// Rechercher dans la liste chainée si CLE existe
				if (itCouple->getCle() == cle)
				{
					//   Si la CLE verifiée est == CLE
					//     Ne rien faire  (return); 
					return;
				}
				else if (itCouple->getCle() > cle)
				{
					//   Si la CLÉ vérifiée est > CLE
					//     Insérer un nouveau Couple à la position courante (celle de l'itérateur)
					//	   Return;
					this->T[x].insert(itCouple, couple);
					return;
				}
				else
				{
					;
				}

			}
			if (itCouple == this->T[x].end()) // Insérer le nouveau couple à la fin de la liste (push_back)  -->  la valeur est la plus grande de cette liste!
			{
				this->T[x].push_back(couple);
			}
		}
		x++;
	}		
}

//methode permettant de supprimer la paire clé/valeur 
//en entrée : la clé à localiser 
//en sortie un booléen : si trouvé alors suppression + return true si pas trouvé alors return false
bool TableHachage::supprimer(int cle)
{
	// Trouver la bonne position (ou alvéole) dans le tableau
	// Rechercher dans la liste chainée si CLE existe
	//   Si c'est le cas
	//     Supprimer la CLE
	//     Retourner TRUE
	// Retourner FALSE   (La CLE n'est pas dans la liste chainée)
	bool verif = false;
	int numHach = hachage(cle); //hachage de la clé pour localiser l'alvéole de la table 
	if (numHach < 0 || numHach > 9) //verification sur alvéole existe (pas forcement important)
	{
		return verif; //return false 
	}
	else
	{
		list<Couple>::iterator itCouple;
		for (itCouple = this->T[numHach].begin(); itCouple != this->T[numHach].end(); itCouple++)// iteration sur la list comprise dans l'alvéole 
		{
			if (cle == itCouple->getCle()) //si clé d'une paire  == clé à supprimer alors suppression + return true
			{
				this->T[numHach].erase(itCouple);
				verif = true;
				return verif;
			}
		}
	}

	return verif;// clé pas trouvé dans la liste alors return false
}

//methode pour rechercher une clé dans les alvéoles de la table de hache 
//en entrée : la clé à rechercher 
//en sortie : si trouvé return valeur lié à la clé si pas trouvé return -1
int TableHachage::rechercher(int cle)
{
	// Trouver la bonne position (ou alvéole) dans le tableau
	// Rechercher dans la liste chainée si CLE existe
	//   Si c'est le cas
	//     Retourner la valeur
	// RETOURNER -1  (PAS TROUVÉ)

	int numHach = hachage(cle);//hachage grâce à la methode hachage pour localiser l'avéole 
	if (numHach < 0 || numHach > 9)//verification si l'alvéole existe (j'ai jugé u'il fallait le mettre mais je ne pense qu'il soit important)
	{
		return -1; //echec de localisation alors -1
	}
	else //localisation de l'alvéole par numHach
	{
		list<Couple>::iterator itCouple;
		for (itCouple = this->T[numHach].begin(); itCouple != this->T[numHach].end(); itCouple++) //parcours de la list comprise dans l'alvéole 
		{
			if (cle == itCouple->getCle()) // si trouve dans une paire dans list alors return la valeur
			{
				
				return itCouple->getValeur();
			}
		}
	}

	return -1; // si la clé n'a pas été trouvé dans la liste de paires 
}

//methode prenant en entre la clé à hacher et en sortie retourne le numéro de l'alvéole de la table de hache
//utilisation du modulo avec la constante M pour hacher la clé 
int TableHachage::hachage(int cle)
{
	// La fonction de hachage est la suivante --> CLE MOD M
	int hacha = cle % this->m;
	return hacha;
}

//methode pour  l'affichage 
//methode non retouché car répond aux pré-requis
ostream &operator<< (ostream& out, const TableHachage& tableHachage)
{
	list<Couple>::iterator itCouple;

	out << "----------------------" << endl;
	out << "T[], \t(CLE, \tVALEUR)" << endl;
	for (int x = 0; x < tableHachage.m; x++)
		for (itCouple=tableHachage.T[x].begin(); itCouple != tableHachage.T[x].end(); itCouple++)
		{
			out << x << "\t" << (*itCouple);
			out << endl;
		}
	out << "----------------------" << endl;

	return out;
}