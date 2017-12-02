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

void Coin::StartAction(Player& ally, Player& enemy)
{

}

void Coin::EndAction(Player& ally, Player& enemy)
{

}

