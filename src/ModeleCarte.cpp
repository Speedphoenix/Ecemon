#include "ModeleCarte.h"

using namespace std;

ModeleCarte::ModeleCarte(int _CardNum)
    :m_CardNum(_CardNum)
{
    //ctor
}

ModeleCarte::~ModeleCarte()
{
    //dtor
}

// écrit la carte dans un fichier
void ModeleCarte::Write_file(ostream& fichier)
{
    fichier << endl << GetCardType() << endl;
    fichier << m_CardNum << endl;
    fichier << m_Nom << endl;

    fichier << m_Description.size() << endl;
    for (int i=0;i<m_Description.size();i++)
        fichier << m_Description.at(i) << endl;
}

// lit la carte dans un fichier
void ModeleCarte::Read_file(istream& fichier)
{
    fichier.ignore(1, '\n');

    getline(fichier, m_Nom);

    int lineNum;
    fichier >> lineNum;
    fichier.ignore(1, '\n');
    for (int i=0;i<lineNum;i++)
    {
        string inter;
        getline(fichier, inter);
        m_Description.push_back(inter);
    }
}

