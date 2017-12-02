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

}

void GreenShroom::EndAction(KeepSpecial& keep, Player& ally, Player& enemy)
{

}


