#ifndef MODELEENERGIE_H
#define MODELEENERGIE_H

#include "defines.h"
#include "ModeleCarte.h"

class ModeleEnergie : public ModeleCarte
{
    private:

    protected:
        /** à quel domaine cette carte appartient */
        int m_Domaine;

        /** la quantité d'énergie de cette carte*/
        int m_Energy;

    public:
        ModeleEnergie();
        ModeleEnergie(int cardNum, std::istream& fichier);
        virtual ~ModeleEnergie();

        /** écrit la carte dans un fichier. Ne servira à priori jamais */
        virtual void Write_file(std::ostream& fichier);

        /** lit la carte dans un fichier
        ON ASSUME QUE LE NUMÉRO DE LA CARTE A DÉJÀ ÉTÉ LU!!!*/
        virtual void Read_file(std::istream& fichier);

        //renvoie le type de carte
        virtual CardType GetCardType() { return ENERGIE; }

        //accesseurs
        int GetEnergy() { return m_Energy; }
        void SetEnergy(int val) { m_Energy = val; }
        int GetDomaine() { return m_Domaine; }
        void SetDomaine(int val) { m_Domaine = val; }
        BITMAP *GetCardFront() { return m_CardFront; }

};

#endif // MODELEENERGIE_H

