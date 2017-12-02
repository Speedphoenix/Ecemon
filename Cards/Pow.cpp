#include "Pow.h"

#include "Player.h"

Pow::Pow()
    :ModeleSpecial()
{
    //ctor
}

Pow::Pow(int cardNum, std::istream& fichier)
    :ModeleSpecial(cardNum, fichier)
{
    //ctor
}

Pow::~Pow()
{
    //dtor
}


void Pow::StartAction(KeepSpecial& keep, Player& ally, Player& enemy)
{
    Creature *inter = nullptr;

    for (int i=0;i<MAXACTIVE;i++)
    {
        inter = enemy.GetActive(i);
        if (inter)
            inter->AddFrozen(POWFREEZE);
    }
}

void Pow::EndAction(KeepSpecial& keep, Player& ally, Player& enemy)
{
    //active cards will unfreeze themselves on their own
}

