//Don't forget to include what's necessary
#include "ModeleCreature.h"

using namespace std;

///ATTENTION L'implementation de ModeleCreature et Move ne sont pas dans les mêmes fichiers

ModeleCreature::ModeleCreature()
    :ModeleCarte(10)
{
    m_CardFront = load_bitmap(FCARDT, NULL); ERR_CHARG(m_CardFront) ///À ENLEVER

    rectfill(m_CardFront, XDESCRI, YDESCRI, XDESCRI + WDESCRI, YDESCRI + HDESCRI, ROUGE);



}


ModeleCreature::ModeleCreature(int cardNum, istream& fichier)
    :ModeleCarte(cardNum)
{
    Read_file(fichier);

    textprintf_ex(m_CardFront, font, 67, 68, NOIR, -1, "%d", m_Moves[0].GetDamage());
    for (int i=0;i<NBDOMAINE;i++)
    {
        if (m_Moves[0].GetConsomation().value[i])
        {
            int col = i==0?VERT:i==1?COL_ROCK:i==2?NOIR:ROUGE;
            textprintf_ex(m_CardFront, font, 42, 68, col, -1, "%d", m_Moves[0].GetConsomation().value[i]);

        }
    }

    textprintf_ex(m_CardFront, font, 67, 96, NOIR, -1, "%d", m_Moves[1].GetDamage());
    for (int i=0;i<NBDOMAINE;i++)
    {
        if (m_Moves[1].GetConsomation().value[i])
        {
            int col = i==0?VERT:i==1?COL_ROCK:i==2?NOIR:ROUGE;
            textprintf_ex(m_CardFront, font, 42, 96, col, -1, "%d", m_Moves[1].GetConsomation().value[i]);

        }
    }
}

ModeleCreature::~ModeleCreature()
{
    //dtor
}

void ModeleCreature::Write_file(ostream& fichier)
{
    ModeleCarte::Write_file(fichier);

    fichier << m_HP << endl;

    fichier << MAXMOVES << endl; //le nombre de moves dans cette créature. sauf changements on mettra MAXMOVES

    for (int i=0;i<MAXMOVES;i++)
    {
        m_Moves[i].Write_file(fichier);
    }
}

void ModeleCreature::Read_file(istream& fichier)
{
    ModeleCarte::Read_file(fichier);

    fichier >> m_HP;

    int nbMoves; //sera généralement 2

    fichier >> nbMoves;

    if (nbMoves>MAXMOVES)
        throw nbMoves;

    for (int i=0;i<nbMoves;i++)
    {
        m_Moves[i] = Move(fichier);
    }

    for (int i=nbMoves;i<MAXMOVES;i++) //cette boucle n'aura généralement pas lieu
    {
        m_Moves[i] = Move(); //initialise à la valeur par défaud de move (damage = 0)
    }
}

