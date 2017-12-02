#ifndef STAR_H
#define STAR_H

#include <ModeleSpecial.h>


class Star : public ModeleSpecial
{
    public:
        Star();
        Star(int cardNum, std::istream& fichier);
        virtual ~Star();

        void StartAction(KeepSpecial& keep, Player& ally, Player& enemy);
        void EndAction(KeepSpecial& keep, Player& ally, Player& enemy);
};

#endif // STAR_H
