#include "Flower.h"

#include "Player.h"

Flower::Flower()
    :ModeleSpecial()
{
    //ctor
}

Flower::Flower(int cardNum, std::istream& fichier)
    :ModeleSpecial(cardNum, fichier)
{
    //ctor
}

Flower::~Flower()
{
    //dtor
}

void Flower::StartAction(Player& ally, Player& enemy)
{

}

void Flower::EndAction(Player& ally, Player& enemy)
{

}
