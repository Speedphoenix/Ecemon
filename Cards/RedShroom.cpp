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

void RedShroom::StartAction(Player& ally, Player& enemy)
{

}

void RedShroom::EndAction(Player& ally, Player& enemy)
{

}

