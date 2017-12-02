#ifndef POW_H
#define POW_H

#include <ModeleSpecial.h>


class Pow : public ModeleSpecial
{
    public:
        Pow();
        Pow(int cardNum, std::istream& fichier);
        virtual ~Pow();

        void StartAction(Player& ally, Player& enemy);
        void EndAction(Player& ally, Player& enemy);
};

#endif // POW_H

