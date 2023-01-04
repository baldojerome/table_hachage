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
									// pour �viter une fuite de m�moire  
									// (Rappel : Si on utilise un pointeur  (new) alors il faut un delete)
}

// Ajout tri� dans la liste
//methode pour ajouter une paire cl�/valeur dans la table de hache 
//en entree : cl� + valeur 

void TableHachage::ajouter(int cle, int valeur)
{
	int x = 0;
	while (x < this->m)
	{
		// Trouver la bonne position (ou alv�ole) dans le tableau  *** Par hachage �videmment ***
		int numHach = this->hachage(cle);
		if (numHach == x)
		{
			Couple couple(cle, valeur);
			list<Couple>::iterator itCouple;
			for (itCouple = this->T[x].begin(); itCouple != this->T[x].end(); itCouple++)
			{
				// Rechercher dans la liste chain�e si CLE existe
				if (itCouple->getCle() == cle)
				{
					//   Si la CLE verifi�e est == CLE
					//     Ne rien faire  (return); 
					return;
				}
				else if (itCouple->getCle() > cle)
				{
					//   Si la CL� v�rifi�e est > CLE
					//     Ins�rer un nouveau Couple � la position courante (celle de l'it�rateur)
					//	   Return;
					this->T[x].insert(itCouple, couple);
					return;
				}
				else
				{
					;
				}

			}
			if (itCouple == this->T[x].end()) // Ins�rer le nouveau couple � la fin de la liste (push_back)  -->  la valeur est la plus grande de cette liste!
			{
				this->T[x].push_back(couple);
			}
		}
		x++;
	}		
}

//methode permettant de supprimer la paire cl�/valeur 
//en entr�e : la cl� � localiser 
//en sortie un bool�en : si trouv� alors suppression + return true si pas trouv� alors return false
bool TableHachage::supprimer(int cle)
{
	// Trouver la bonne position (ou alv�ole) dans le tableau
	// Rechercher dans la liste chain�e si CLE existe
	//   Si c'est le cas
	//     Supprimer la CLE
	//     Retourner TRUE
	// Retourner FALSE   (La CLE n'est pas dans la liste chain�e)
	bool verif = false;
	int numHach = hachage(cle); //hachage de la cl� pour localiser l'alv�ole de la table 
	if (numHach < 0 || numHach > 9) //verification sur alv�ole existe (pas forcement important)
	{
		return verif; //return false 
	}
	else
	{
		list<Couple>::iterator itCouple;
		for (itCouple = this->T[numHach].begin(); itCouple != this->T[numHach].end(); itCouple++)// iteration sur la list comprise dans l'alv�ole 
		{
			if (cle == itCouple->getCle()) //si cl� d'une paire  == cl� � supprimer alors suppression + return true
			{
				this->T[numHach].erase(itCouple);
				verif = true;
				return verif;
			}
		}
	}

	return verif;// cl� pas trouv� dans la liste alors return false
}

//methode pour rechercher une cl� dans les alv�oles de la table de hache 
//en entr�e : la cl� � rechercher 
//en sortie : si trouv� return valeur li� � la cl� si pas trouv� return -1
int TableHachage::rechercher(int cle)
{
	// Trouver la bonne position (ou alv�ole) dans le tableau
	// Rechercher dans la liste chain�e si CLE existe
	//   Si c'est le cas
	//     Retourner la valeur
	// RETOURNER -1  (PAS TROUV�)

	int numHach = hachage(cle);//hachage gr�ce � la methode hachage pour localiser l'av�ole 
	if (numHach < 0 || numHach > 9)//verification si l'alv�ole existe (j'ai jug� u'il fallait le mettre mais je ne pense qu'il soit important)
	{
		return -1; //echec de localisation alors -1
	}
	else //localisation de l'alv�ole par numHach
	{
		list<Couple>::iterator itCouple;
		for (itCouple = this->T[numHach].begin(); itCouple != this->T[numHach].end(); itCouple++) //parcours de la list comprise dans l'alv�ole 
		{
			if (cle == itCouple->getCle()) // si trouve dans une paire dans list alors return la valeur
			{
				
				return itCouple->getValeur();
			}
		}
	}

	return -1; // si la cl� n'a pas �t� trouv� dans la liste de paires 
}

//methode prenant en entre la cl� � hacher et en sortie retourne le num�ro de l'alv�ole de la table de hache
//utilisation du modulo avec la constante M pour hacher la cl� 
int TableHachage::hachage(int cle)
{
	// La fonction de hachage est la suivante --> CLE MOD M
	int hacha = cle % this->m;
	return hacha;
}

//methode pour  l'affichage 
//methode non retouch� car r�pond aux pr�-requis
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