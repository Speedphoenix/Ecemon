#ifndef REDSHROOM_H
#define REDSHROOM_H

#include <ModeleSpecial.h>


class RedShroom : public ModeleSpecial
{
    public:
        RedShroom();
        RedShroom(int cardNum, std::istream& fichier);
        virtual ~RedShroom();

        void StartAction(Player& ally, Player& enemy);
        void EndAction(Player& ally, Player& enemy);
};

#endif // REDSHROOM_H

