#include "ModeleEnergie.h"

using namespace std;

ModeleEnergie::ModeleEnergie()
    :ModeleCarte(2), m_Domaine(1), m_Energy(3)
{
    m_Nom = "thyird Name";
    m_Description = "yet another description";

}

ModeleEnergie::ModeleEnergie(int cardNum, istream& fichier)
    :ModeleCarte(cardNum)
{
    Read_file(fichier);

    m_CardFront = load_bitmap(FCARDT, NULL); ERR_CHARG(m_CardFront) ///À ENLEVER

    rectfill(m_CardFront, XDESCRI, YDESCRI, XDESCRI + WDESCRI, YDESCRI + HDESCRI, NOIR);
}

ModeleEnergie::~ModeleEnergie()
{
    //dtor
}

void ModeleEnergie::Write_file(ostream& fichier)
{
    ModeleCarte::Write_file(fichier);

    fichier << m_Domaine << endl;
    fichier << m_Energy << endl;
}

void ModeleEnergie::Read_file(istream& fichier)
{
    ModeleCarte::Read_file(fichier);

    fichier >> m_Domaine;
    fichier >> m_Energy;
}

