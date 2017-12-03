#include "RedShroom.h"

#include "Player.h"

RedShroom::RedShroom()
    :ModeleSpecial()
{
    //ctor
}

RedShroom::RedShroom(int cardNum, std::istream& fichier)
    :ModeleSpecial(cardNum, fichier)
{
    //ctor
}

RedShroom::~RedShroom()
{
    //dtor
}

void RedShroom::StartAction(KeepSpecial& keep, Player& ally, Player& enemy)
{
    keep.couldAct = false;

    for (int i=0;i<MAXACTIVE;i++)
    {
        if (ally.GetActive(i))
        {
            keep.theOne = ally.GetActive(i);
            keep.theOne->GetMove(0).SetDamage(keep.theOne->GetMove(0).GetDamage() + SHROOMBUFF); //increase the damage of each move
            keep.theOne->GetMove(1).SetDamage(keep.theOne->GetMove(1).GetDamage() + SHROOMBUFF);
            keep.couldAct = true;
            break;
        }
    }
}

void RedShroom::EndAction(KeepSpecial& keep, Player& ally, Player& enemy)
{
    if (keep.couldAct)
    {
        keep.theOne->GetMove(0).SetDamage(keep.theOne->GetMove(0).GetDamage() - SHROOMBUFF); //remove the increased damage
        keep.theOne->GetMove(1).SetDamage(keep.theOne->GetMove(1).GetDamage() - SHROOMBUFF);
        keep.couldAct = false;
    }
}

