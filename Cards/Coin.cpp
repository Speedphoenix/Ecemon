#include "Coin.h"

#include "Player.h"

Coin::Coin()
    :ModeleSpecial()
{
    //ctor
}

Coin::Coin(int cardNum, std::istream& fichier)
    :ModeleSpecial(cardNum, fichier)
{
    //ctor
}

Coin::~Coin()
{
    //dtor
}

void Coin::StartAction(KeepSpecial& keep, Player& ally, Player& enemy)
{
    keep.couldAct = false;

    for (int i=0;i<MAXACTIVE;i++)
    {
        if (ally.GetActive(i))
        {
            keep.theOne = ally.GetActive(i);
            keep.theOne->TakeDamage(-COINHEAL); //heal for -3
            keep.couldAct = true;
            break;
        }
    }
}

void Coin::EndAction(KeepSpecial& keep, Player& ally, Player& enemy)
{
    if (keep.couldAct)
    {
        keep.theOne->TakeDamage(COINHEAL);
        keep.couldAct = false;
    }
}

