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

}

void Coin::EndAction(KeepSpecial& keep, Player& ally, Player& enemy)
{

}

