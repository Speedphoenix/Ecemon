#ifndef FLOWER_H
#define FLOWER_H

#include <ModeleSpecial.h>


class Flower : public ModeleSpecial
{
    public:
        Flower();
        Flower(int cardNum, std::istream& fichier);
        virtual ~Flower();


        void StartAction(KeepSpecial& keep, Player& ally, Player& enemy);
        void EndAction(KeepSpecial& keep, Player& ally, Player& enemy);
};

#endif // FLOWER_H
