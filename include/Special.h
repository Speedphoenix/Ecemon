#ifndef SPECIAL_H
#define SPECIAL_H

#include "defines.h"
#include "Carte.h"

#include "Coin.h"
#include "Flower.h"
#include "GreenShroom.h"
#include "Pow.h"
#include "RedShroom.h"
#include "Star.h"

class Special : public Carte
{
    private:

    protected:
        /* le modele de carte */
        ModeleSpecial& m_Modele;

        /* nombre de tours pendant lequel la carte est encore active */
        int m_ActiveLeft;

    public:
        Special(ModeleSpecial& _Modele);
        virtual ~Special();

        /* Fait toutes les actions à faire avant que le joueur ait joué (par exemple décrémenter activeLeft, annuler ce qui etait mis par endturn) */
        void StartTurn(Player& ally, Player& enemy);

        /* Fait toutes les actions à faire après que le joueur ait joué */
        void EndTurn(Player& ally, Player& enemy);

        //renvoie le type de carte
        virtual CardType GetCardType() { return SPECIAL; }
        //renvoie la face de la carte
        virtual BITMAP *GetCardFront();

        ModeleCarte& GetModele() { return m_Modele; }

        virtual void Reset();
        int GetActiveLeft() { return m_ActiveLeft; }

};

#endif // SPECIAL_H
