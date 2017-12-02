//Don't forget to include what's necessary
#include "Special.h"
#include "Player.h"

Special::Special(ModeleSpecial& _Modele)
    :m_Modele(_Modele)
{
    m_ActiveLeft = m_Modele.GetActiveLeft();
}

Special::~Special()
{
    //dtor
}


BITMAP *Special::GetCardFront()
{
    return m_Modele.GetCardFront();
}

void Special::StartTurn(Player& ally, Player& enemy)
{
    m_Modele.EndAction(ally, enemy);

    m_ActiveLeft--;

    if (m_ActiveLeft<0) //on sait jamais
        m_ActiveLeft = 0;
}

void Special::EndTurn(Player& ally, Player& enemy)
{
    m_Modele.StartAction(ally, enemy);
}

void Special::Reset()
{
    m_ActiveLeft = m_Modele.GetActiveLeft();
}

