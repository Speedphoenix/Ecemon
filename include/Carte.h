#ifndef CARTE_H
#define CARTE_H

#include "defines.h"
#include "ModeleCarte.h"

class Player;


class Carte
{
    private:

    protected:

    public:
        Carte();
        virtual ~Carte();

        /** renvoie le type de carte (creature, energie, special) */
        virtual CardType GetCardType() = 0;

        /** renvoie la face de la carte*/
        virtual BITMAP *GetCardFront() = 0;

        /** montre les détails de la carte. contient une boucle evennementielle */
        virtual void Detail(BITMAP *fond, PlayerInput& p_input, const Sprites& sprites);


        virtual ModeleCarte& GetModele() = 0;

        //virtual void Write_file(const std::ostream& fichier) = 0;

        /** remet à zero à la fin/début d'une partie */
        virtual void Reset() = 0;
};

#endif // CARTE_H

