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

}

void Star::EndAction(KeepSpecial& keep, Player& ally, Player& enemy)
{

}

