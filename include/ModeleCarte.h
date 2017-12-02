//Don't forget to include what's necessary
#ifndef MODELECARTE_H
#define MODELECARTE_H

#include "defines.h"

class ModeleCarte
{
    private:

    protected:
        /** le numéro de la carte (dans la map) */
        int m_CardNum;

        std::string m_Nom;
        std::vector<std::string> m_Description; //chaque string est une ligne
        BITMAP *m_CardFront;

    public:
        ModeleCarte(int _CardNum);
        virtual ~ModeleCarte();

        /** écrit la carte dans un fichier. Ne servira à priori jamais */
        virtual void Write_file(std::ostream& fichier);

        /** lit la carte dans un fichier
        ON ASSUME QUE LE NUMÉRO DE LA CARTE A DÉJÀ ÉTÉ LU!!!*/
        virtual void Read_file(std::istream& fichier);

        /** renvoie le type de carte (creature, energie, special) */
        virtual CardType GetCardType() = 0;


        int GetCardNum() { return m_CardNum; }
        std::string GetNom() { return m_Nom; }
        void SetNom(std::string val) { m_Nom = val; }
        std::vector<std::string>& GetDescription() { return m_Description; }
};

#endif // MODELECARTE_H
