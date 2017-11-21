#ifndef ENERGIE_H
#define ENERGIE_H


#include "defines.h"
#include "Carte.h"
#include "ModeleEnergie.h"


class Energie : public Carte
{
    private:
        ModeleEnergie& m_Modele;

    protected:

    public:
        Energie(ModeleEnergie& _Modele);
        virtual ~Energie();

        CardType GetCardType();

        void Use(Domaines& where);
};

#endif // ENERGIE_H
