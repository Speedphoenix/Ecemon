#include "ModeleCreature.h"
///declaration de la classe Move dans ModeleCreature.h

#include "Player.h"

using namespace std;

Move::Move()
    :m_Damage(0)
{
    for (int i=0;i<NBDOMAINE;i++)
    {
        m_Consomation.value[i] = 0;
    }
}

Move::Move(int _Damage, Domaines& consomation)
    :m_Damage(_Damage)
{
    SetConsomation(consomation);
}

Move::Move(const Move& other)
    :m_Damage(other.GetDamage())
{
    SetConsomation(other.GetConsomation());
}

Move& Move::operator=(const Move& other)
{
    if (this == &other)
    {
        return *this; // handle self assignment
    }
    else
    {
        m_Damage = other.GetDamage();
        SetConsomation(other.GetConsomation());
    }
    //assignment operator
    return *this;
}

Move::Move(istream& fichier)
{
    Read_file(fichier);
}

Move::~Move()
{
    //dtor
}


void Move::Write_file(ostream& fichier)
{
    fichier << m_Damage << endl;

    for (int i=0;i<NBDOMAINE;i++)
    {
        fichier << m_Consomation.value[i] << " ";
    }


    fichier << endl;
}

void Move::Read_file(istream& fichier)
{
    fichier >> m_Damage;

    for (int i=0;i<NBDOMAINE;i++)
    {
        fichier >> m_Consomation.value[i];
    }
}


void Move::Attack(Player& ally, Player& enemy, int who)
{
    Domaines& fuel = ally.GetCurrentEnergy();

    //check pour voir si y'a assez d'energie
    bool canAttack = true;
    for (int i=0;i<NBDOMAINE;i++)
    {
        if (fuel.value[i]<m_Consomation.value[i])
            canAttack = false;
    }

    if (canAttack)
    {
        if (who==-1)
        {
            enemy.TakeDamage(m_Damage);
        }
        else
        {
            int retenue = enemy.GetActive(who)->TakeDamage(m_Damage);

            if (retenue)
            {
                enemy.TakeDamage(retenue);
            }
        }

        for (int i=0;i<NBDOMAINE;i++)
        {
            fuel.value[i] -= m_Consomation.value[i];
        }
    }

}

void Move::SetConsomation(Domaines conso)
{
    for (int i=0;i<NBDOMAINE;i++)
    {
        m_Consomation.value[i] = conso.value[i];
    }
}

