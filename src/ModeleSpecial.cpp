#include "ModeleSpecial.h"

using namespace std;

ModeleSpecial::ModeleSpecial()
    :ModeleCarte(1), m_ActiveLeft(3)
{
    m_Nom = "Second Name";
    m_Description = "another description";
    m_CardFront = load_bitmap(FCARDT, NULL); ERR_CHARG(m_CardFront) ///À ENLEVER

    rectfill(m_CardFront, XDESCRI, YDESCRI, XDESCRI + WDESCRI, YDESCRI + HDESCRI, BLEU);
}

ModeleSpecial::ModeleSpecial(int cardNum, istream& fichier)
    :ModeleCarte(cardNum)
{
    Read_file(fichier);

    m_CardFront = load_bitmap(FCARDT, NULL); ERR_CHARG(m_CardFront) ///À ENLEVER

    rectfill(m_CardFront, XDESCRI, YDESCRI, XDESCRI + WDESCRI, YDESCRI + HDESCRI, BLEU);
}

ModeleSpecial::~ModeleSpecial()
{
    //dtor
}

void ModeleSpecial::StartAction()
{

}

void ModeleSpecial::EndAction()
{

}

void ModeleSpecial::Write_file(ostream& fichier)
{
    ModeleCarte::Write_file(fichier);

    fichier << m_ActiveLeft << endl;
}

void ModeleSpecial::Read_file(istream& fichier)
{
    ModeleCarte::Read_file(fichier);

    fichier >> m_ActiveLeft;
}

