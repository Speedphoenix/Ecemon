#ifndef MODELESPECIAL_H
#define MODELESPECIAL_H

#include "defines.h"
#include "ModeleCarte.h"

class Player;

class ModeleSpecial : public ModeleCarte
{
    private:

    protected:
        /* le nombre de tours pendant lequel la carte doit être active */
        int m_ActiveLeft;

    public:
        ModeleSpecial();
        ModeleSpecial(int cardNum, std::istream& fichier);
        virtual ~ModeleSpecial();

        virtual void StartAction(Player& ally, Player& enemy);

        virtual void EndAction(Player& ally, Player& enemy);

        /* écrit la carte dans un fichier. Ne servira à priori jamais */
        virtual void Write_file(std::ostream& fichier);

        /* lit la carte dans un fichier
        ON ASSUME QUE LE NUMÉRO DE LA CARTE A DÉJÀ ÉTÉ LU!!!*/
        virtual void Read_file(std::istream& fichier);

        //renvoie le type de carte
        virtual CardType GetCardType() { return SPECIAL; }

        int GetActiveLeft() { return m_ActiveLeft; }
        BITMAP *GetCardFront() { return m_CardFront; }
};

#endif // MODELESPECIAL_H

