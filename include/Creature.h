#ifndef CREATURE_H
#define CREATURE_H

#include "defines.h"
#include "Carte.h"
#include "ModeleCreature.h"

class Creature : public Carte
{
    private:

    protected:
        /** le modele de carte */
        ModeleCreature& m_Modele;
        /** une copie de l'hp, est variable dans une partie */
        int m_HP;

        /** l'arsenal d'attaques de la carte */
        Move m_Moves[MAXMOVES];

        /** si cette carte devra attaquer au prochain tour */
        bool m_Attack;
        /** le numéro de la carte ennemie à attaquer. -1 si c'est directement le joueur */
        int m_Cible;
        /** quelle attaque utiliser */
        int m_AttackMove;

        /** si la carte est stun, le nombre de tours restants (0 si pas stun) */
        int m_Frozen;

    public:
        Creature(ModeleCreature& _Modele);
        virtual ~Creature();

        //renvoie le type de carte
        virtual CardType GetCardType() { return CREATURE; }
        //renvoie la face de la carte
        virtual BITMAP *GetCardFront();

        ModeleCarte& GetModele() { return m_Modele; }
        Move& GetMove(int num) { return m_Moves[num]; }

        /** fait attaquer à la fin du tour */
        virtual void SetAttack(int who, int _move);
        virtual int TakeDamage(int quant);
        virtual void EndTurn(Player& ally, Player& enemy);

        //accesseurs
        virtual void Reset();
        int GetHP() { return m_HP; }
        int GetAD(int num) { return m_Moves[num].GetDamage(); }
        bool IsFrozen() { return (bool) m_Frozen; }
        void AddFrozen(int quant);
};

#endif // CREATURE_H

