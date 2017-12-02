#ifndef POW_H
#define POW_H

#include <ModeleSpecial.h>


class Pow : public ModeleSpecial
{
    public:
        Pow();
        Pow(int cardNum, std::istream& fichier);
        virtual ~Pow();

        void StartAction(KeepSpecial& keep, Player& ally, Player& enemy);
        void EndAction(KeepSpecial& keep, Player& ally, Player& enemy);
};

#endif // POW_H

