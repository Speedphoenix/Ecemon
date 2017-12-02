#ifndef COIN_H
#define COIN_H

#include <ModeleSpecial.h>


class Coin : public ModeleSpecial
{
    public:
        Coin();
        Coin(int cardNum, std::istream& fichier);
        virtual ~Coin();

        void StartAction(Player& ally, Player& enemy);
        void EndAction(Player& ally, Player& enemy);
};

#endif // COIN_H

