#ifndef STAR_H
#define STAR_H

#include <ModeleSpecial.h>


class Star : public ModeleSpecial
{
    public:
        Star();
        Star(int cardNum, std::istream& fichier);
        virtual ~Star();

        void StartAction(Player& ally, Player& enemy);
        void EndAction(Player& ally, Player& enemy);
};

#endif // STAR_H
