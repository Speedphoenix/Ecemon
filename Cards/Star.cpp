#include "Star.h"

#include "Player.h"

Star::Star()
    :ModeleSpecial()
{
    //ctor
}

Star::Star(int cardNum, std::istream& fichier)
    :ModeleSpecial(cardNum, fichier)
{
    //ctor
}

Star::~Star()
{
    //dtor
}

void Star::StartAction(KeepSpecial& keep, Player& ally, Player& enemy)
{
    if (ally.GetMain().size()<MAXHAND)
    {
        if (ally.GetCimetiere())
        {
            ally.GetMain().push_back(ally.PopCimetiere());
        }
    }
}

void Star::EndAction(KeepSpecial& keep, Player& ally, Player& enemy)
{

}

