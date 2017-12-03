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

void Flower::StartAction(KeepSpecial& keep, Player& ally, Player& enemy)
{
    bool dealtPlayer = false;
    for (int i=0;i<MAXACTIVE;i++)
    {
        if (enemy.GetActive(i))
        {
            enemy.GetActive(i)->TakeDamage(1);
        }
        else if (!dealtPlayer)
        {
            enemy.TakeDamage(1);
        }
    }
}

void Flower::EndAction(KeepSpecial& keep, Player& ally, Player& enemy)
{

}

