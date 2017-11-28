#ifndef COLLECTION_H
#define COLLECTION_H

#include "defines.h"
#include "Creature.h"
#include "Energie.h"
#include "Special.h"

class Collection
{
    private:
        std::vector<Carte *> m_Cartes;

    protected:

    public:
        Collection();
        virtual ~Collection();

        //void Fill(std::map<ModeleCarte *> cardList); //pour remplir depuis l'utilisateur
        //void CreateDeck(std::queue<Carte *>& deck); //pour créer un deck depuis la collection
        //void AddCard(Carte *ajout);
        //Carte *PopCard(int num); //enlevè la numième carte et la renvoie. pour l'enjeu
        //
};

#endif // COLLECTION_H
