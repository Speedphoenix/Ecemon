#ifndef MODELECREATURE_H
#define MODELECREATURE_H

#include "defines.h"
#include "ModeleCarte.h"

///ATTENTION L'implementation de ModeleCreature et Move ne sont pas dans les mêmes fichiers

class Player;

/* la classe de l'action d'une créature (généralement une attaque) */
class Move
{
    private:

    protected:
        int m_Damage;

    public:
        Move();
        Move(int _Damage);
        virtual ~Move();

        /* who = -1 to attack the enemy player himself
        pas nécéssaire de passer l'allié en paramètre mais si jamais on décide de faire une classe fille vampirique...*/
        virtual void Attack(Player& ally, Player& enemy, int who);

        //accesseur
        int GetDamage() { return m_Damage; }
};

class ModeleCreature : public ModeleCarte
{
    private:

    protected:
        int m_HP;
        Move m_Moves[MAXMOVES];

    public:
        ModeleCreature();       ///LES CONSTRUCTEURS DE TOUTES LES CARTES RESTENT À FAIRE
        ModeleCreature(int a);  //pour instacier une carte.
        virtual ~ModeleCreature();

        //accesseurs
        int GetHP() { return m_HP; }
        void SetHP(int val) { m_HP = val; }
        BITMAP *GetCardFront() { return m_CardFront; }
        const Move& GetMove(int num) { return m_Moves[num]; }

};

#endif // MODELECREATURE_H

