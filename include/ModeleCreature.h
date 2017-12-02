#ifndef MODELECREATURE_H
#define MODELECREATURE_H

#include "defines.h"
#include "ModeleCarte.h"

///ATTENTION L'implementation de ModeleCreature et Move ne sont pas dans les mêmes fichiers

class Player;

/** la classe de l'action d'une créature (généralement une attaque) */
class Move
{
    private:

    protected:
        int m_Damage;
        Domaines m_Consomation;

    public:
        Move();
        Move(std::istream& fichier);
        Move(int _Damage, Domaines& consomation);
        Move(const Move& other);
        virtual ~Move();
        Move& operator=(const Move& other);


        /** who = -1 to attack the enemy player himself
        pas nécéssaire de passer l'allié en paramètre mais si jamais on décide de faire une classe fille vampirique..., pour la consomation d'energie aussi */
        virtual void Attack(Player& ally, Player& enemy, int who);

        /** écrit la carte dans un fichier. Ne servira à priori jamais */
        virtual void Write_file(std::ostream& fichier);

        /** lit la carte dans un fichier */
        virtual void Read_file(std::istream& fichier);

        //accesseur
        int GetDamage() const { return m_Damage; }
        void SetDamage(int dmg) { m_Damage = dmg; }
        Domaines GetConsomation() const { return m_Consomation; }
        void SetConsomation(Domaines conso);
};

class ModeleCreature : public ModeleCarte
{
    private:

    protected:
        int m_HP;
        Move m_Moves[MAXMOVES]; //c'est le seul endroit qui utilisera ces moves (à priori) il n'y a donc pas besoin de pointeur

    public:
        ModeleCreature();       ///LES CONSTRUCTEURS DE TOUTES LES CARTES RESTENT À FAIRE
        ModeleCreature(int cardNum, std::istream& fichier);
        virtual ~ModeleCreature();

        /** écrit la carte dans un fichier. Ne servira à priori jamais */
        virtual void Write_file(std::ostream& fichier);

        /** lit la carte dans un fichier
        ON ASSUME QUE LE NUMÉRO DE LA CARTE A DÉJÀ ÉTÉ LU!!!*/
        virtual void Read_file(std::istream& fichier);

        //renvoie le type de carte
        virtual CardType GetCardType() { return CREATURE; }

        //accesseurs
        int GetHP() { return m_HP; }
        void SetHP(int val) { m_HP = val; }
        BITMAP *GetCardFront() { return m_CardFront; }
        const Move& GetMove(int num) { return m_Moves[num]; }

};

#endif // MODELECREATURE_H

