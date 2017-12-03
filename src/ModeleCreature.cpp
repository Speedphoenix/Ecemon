//Don't forget to include what's necessary
#include "ModeleCreature.h"

using namespace std;

///ATTENTION L'implementation de ModeleCreature et Move ne sont pas dans les mêmes fichiers

ModeleCreature::ModeleCreature()
    :ModeleCarte(10)
{
    m_CardFront = load_bitmap(FCARDT, NULL); ERR_CHARG(m_CardFront) ///À ENLEVER

    rectfill(m_CardFront, XDESCRI, YDESCRI, XDESCRI + WDESCRI, YDESCRI + HDESCRI, ROUGE);

    for (int i=0;i<MAXMOVES;i++)
        textprintf_ex(m_CardFront, font, XTEXT + 4, YACTION + i*HATTACK + 6, NOIR, -1, "%dDMG", m_Moves[i].GetDamage());

}


ModeleCreature::ModeleCreature(int cardNum, istream& fichier)
    :ModeleCarte(cardNum)
{
    Read_file(fichier);

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

