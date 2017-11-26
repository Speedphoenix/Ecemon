#ifndef CREATURE_H
#define CREATURE_H

#include "defines.h"
#include "Carte.h"
#include "ModeleCreature.h"

class Creature : public Carte
{
    private:

    protected:
        ModeleCreature& m_Modele;
        int m_HP;
        int m_AD;

        bool m_Attack;
        int m_Cible; //le numéro de la carte ennemie à attaquer. -1 si c'est directement le joueur

        BITMAP *m_Front;

    public:
        Creature(ModeleCreature& _Modele);
        virtual ~Creature();

        virtual CardType GetCardType();
        virtual BITMAP *GetCardFront();

        void SetAttack(int who);
        virtual int TakeDamage(int quant);
        virtual void EndTurn(Player& ally, Player& enemy);

        int GetHP() { return m_HP; }
        int GetAD() { return m_AD; }
};

#endif // CREATURE_H

