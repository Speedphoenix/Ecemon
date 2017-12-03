#include "GreenShroom.h"

#include "Player.h"

GreenShroom::GreenShroom()
    :ModeleSpecial()
{
    //ctor
}

GreenShroom::GreenShroom(int cardNum, std::istream& fichier)
    :ModeleSpecial(cardNum, fichier)
{
    //ctor
}

GreenShroom::~GreenShroom()
{
    //dtor
}

void GreenShroom::StartAction(KeepSpecial& keep, Player& ally, Player& enemy)
{
    for (int i=0;i<MAXACTIVE;i++)
    {
        if (ally.GetActive(i))
            ally.GetActive(i)->TakeDamage(-SHROOMHEAL); //heals the card
    }
}

void GreenShroom::EndAction(KeepSpecial& keep, Player& ally, Player& enemy)
{

}


