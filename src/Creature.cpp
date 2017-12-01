#include "Creature.h"

#include "Player.h"

using namespace std;

Creature::Creature(ModeleCreature& _Modele)
    :m_Modele(_Modele), m_HP(_Modele.GetHP()), m_Attack(false), m_Cible(0), m_Frozen(0)
{
    for (int i=0;i<MAXMOVES;i++)
    {
        m_Moves[i] = _Modele.GetMove(i); //l'operateur = est overloadé proprement
    }
}

Creature::~Creature()
{
    //dtor
}


BITMAP *Creature::GetCardFront()
{
    return m_Modele.GetCardFront();
}

void Creature::SetAttack(int who, int _move)
{
    if (!m_Frozen)
    {
        m_Attack = true;
        m_Cible = who;
        m_AttackMove = _move;
    }
}

void Creature::AddFrozen(int quant)
{
    if (quant>0)
    {
        m_Frozen += quant;
    }
    else
        throw quant;
}

int Creature::TakeDamage(int quant)
{
    if (m_HP>=quant)
    {
        m_HP -= quant;
        return 0;
    }
    else
    {
        int rep = quant - m_HP;
        m_HP = 0;
        return rep;
    }
}

void Creature::EndTurn(Player& ally, Player& enemy)
{
    if (m_Frozen>0)
    {
        m_Frozen--;
        return;
    }

    if (m_Attack)
    {
        m_Moves[m_AttackMove].Attack(ally, enemy, m_Cible);

        m_Attack = false;
    }
}

void Creature::Reset()
{
    m_HP = m_Modele.GetHP();

    for (int i=0;i<MAXMOVES;i++)
    {
        m_Moves[i] = m_Modele.GetMove(i);
    }

    m_Attack = false;
    m_Cible = 0;
    m_AttackMove = 0;
    m_Frozen = 0;
}



