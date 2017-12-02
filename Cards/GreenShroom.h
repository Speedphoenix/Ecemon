#ifndef GREENSHROOM_H
#define GREENSHROOM_H

#include <ModeleSpecial.h>


class GreenShroom : public ModeleSpecial
{
    public:
        GreenShroom();
        GreenShroom(int cardNum, std::istream& fichier);
        virtual ~GreenShroom();

        void StartAction(KeepSpecial& keep, Player& ally, Player& enemy);
        void EndAction(KeepSpecial& keep, Player& ally, Player& enemy);
};

#endif // GREENSHROOM_H
