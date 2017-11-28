#ifndef MODELESPECIAL_H
#define MODELESPECIAL_H

#include "defines.h"
#include "ModeleCarte.h"

class ModeleSpecial : public ModeleCarte
{
    private:

    protected:
        /* le nombre de tours pendant lequel la carte doit être active */
        int m_ActiveLeft;

    public:
        ModeleSpecial();
        virtual ~ModeleSpecial();

        /* à changer, mettre des start-turn? */
        void Action();

        int GetActiveLeft() { return m_ActiveLeft; }
        BITMAP *GetCardFront() { return m_CardFront; }
};

#endif // MODELESPECIAL_H

