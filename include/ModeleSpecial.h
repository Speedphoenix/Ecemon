#ifndef MODELESPECIAL_H
#define MODELESPECIAL_H

#include "defines.h"
#include "ModeleCarte.h"

class Player;
class Creature;

/** La structure qui garde les données de l'action d'une carte entre la fin et le début du tour */
struct KeepSpecial{
    int aimType;
    int aimNum;
    int aimSide;
    bool couldAct;
    Creature *theOne;
};

class ModeleSpecial : public ModeleCarte
{
    private:

    protected:
        /** le nombre de tours pendant lequel la carte doit être active */
        int m_ActiveLeft;

    public:
        ModeleSpecial();
        ModeleSpecial(int cardNum, std::istream& fichier);
        virtual ~ModeleSpecial();

        /** si c'est une carte nécéssitant une cible par le joueur lock sur cette cible */
        virtual void SetAction(KeepSpecial& keep, Player& ally, Player& opponent, PlayerInput& p_input) { }

        /** Mettre l'action. generalement à la fin du tour */
        virtual void StartAction(KeepSpecial& keep, Player& ally, Player& enemy);

        /** Enlever les effets de l'action. Generalement au début du tour */
        virtual void EndAction(KeepSpecial& keep, Player& ally, Player& enemy);

        /** écrit la carte dans un fichier. Ne servira à priori jamais */
        virtual void Write_file(std::ostream& fichier);

        /** lit la carte dans un fichier
        ON ASSUME QUE LE NUMÉRO DE LA CARTE A DÉJÀ ÉTÉ LU!!!*/
        virtual void Read_file(std::istream& fichier);

        //renvoie le type de carte
        virtual CardType GetCardType() { return SPECIAL; }

        int GetActiveLeft() { return m_ActiveLeft; }
        BITMAP *GetCardFront() { return m_CardFront; }
};

#endif // MODELESPECIAL_H

