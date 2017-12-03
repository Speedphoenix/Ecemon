#include "Collection.h"

using namespace std;

Collection::Collection()
{
    //ctor
}

Collection::~Collection()
{
    for (const auto& elem : m_Cartes)
    {
        delete(elem);
    }
}

void Collection::CreateDeck(queue<Carte *>& deck, int a)
{
    vector<Carte *> newOne;

    for (int i=0;i<DECKSIZE;i++)
    {
        newOne.push_back(m_Cartes.at(i));
    }

    random_shuffle (newOne.begin(), newOne.end());

    while (!deck.empty()) //on vide le deck précédent (sais jamais)
        deck.pop();

    for (const auto& elem : newOne)
        deck.push(elem);
}

void Collection::CreateDeck(queue<Carte *>& deck)
{
    cout << "Please choose " << DECKSIZE << " cards amongst the following to create your deck" << endl
         << "PRESS ENTER TO CONTINUE" << endl;

    cin.ignore(1, '\n');

    for (int i=0;i<m_Cartes.size();i++)
    {
        cout << endl << i << "\t" << m_Cartes.at(i)->GetModele().GetNom() << endl;
    }

    vector<Carte *> newOne;

    for (int i=0;i<DECKSIZE;i++)
    {
        bool works = false;

        Carte *currCard;
        do
        {
            int currNum;
            cin >> currNum;

            try{
                currCard = m_Cartes.at(currNum);
                works = true;

                vector<Carte *>::iterator it;
                for (it = newOne.begin();it!=newOne.end();it++)
                {
                    if (*it==currCard) //on compare le pointeur, pas la carte elle meme
                    {
                        works = false;
                        cout << endl << "You already added this card" << endl;
                        break;
                    }
                }
            }
            catch (const out_of_range& e)
            {
                cout << endl << "This/a card that you asked for doesn't exist" << endl;
                works = false;
            }
        } while (!works);

        newOne.push_back(currCard);
    }

    random_shuffle (newOne.begin(), newOne.end());

    while (!deck.empty()) //on vide le deck précédent (sais jamais)
        deck.pop();

    for (const auto& elem : newOne)
        deck.push(elem);
}

void Collection::WriteFile(std::ostream& fichier)
{
    fichier << endl << m_Cartes.size() << endl;

    //might've been good counting the amount of instances of a single card and then print that, but in case we
    //decide to save an ongoing game making it card by card is better (could make a custom amount of current hp this way
    for (const auto& elem : m_Cartes)
    {
        fichier << elem->GetModele().GetCardNum() << endl;
    }
}

void Collection::AddCard(Carte *ajout)
{
    if (ajout)
    {
        m_Cartes.push_back(ajout);
    }
    else
    {
        throw invalid_argument("null pointer");
    }
}

void Collection::AddNewCard(ModeleCarte *ajout)
{
    switch (ajout->GetCardType())
    {
        case CREATURE:
        m_Cartes.push_back(new Creature(*dynamic_cast<ModeleCreature *>(ajout)));
    break;

        case ENERGIE:
        m_Cartes.push_back(new Energie(*dynamic_cast<ModeleEnergie *>(ajout)));
    break;

        case SPECIAL:
        m_Cartes.push_back(new Special(*dynamic_cast<ModeleSpecial *>(ajout)));
    break;
    }
}

void Collection::RemoveCard(Carte *takeOut)
{
    vector<Carte *>::iterator it;
    for (it = m_Cartes.begin();it!=m_Cartes.end();it++)
    {
        if (*it==takeOut)
        {
            m_Cartes.erase(it);
            break;
        }
    }
}

void Collection::ReadFile(std::istream& fichier, std::map<int, ModeleCarte *> modeles) //pas oublier de vider le vecteur
{
    if (!m_Cartes.empty())
    {
        for (const auto& elem : m_Cartes)
        {
            delete(elem);
        }
        m_Cartes.clear();
    }

    int nbCartes;

    fichier >> nbCartes;

    for (int i=0;i<nbCartes;i++)
    {
        int currNum;
        ModeleCarte *currModele = nullptr;

        fichier >> currNum;

        try
        {
            currModele = modeles.at(currNum);
        }
        catch (const out_of_range& e)
        {
            cerr << endl << "THIS FILE ASKS FOR A CARD THAT DOES NOT EXIST" << endl << i << "th card, number" << currNum << endl;
            throw e;
        }

        AddNewCard(currModele);
    }

    //so that reading the next player doesn't create problems with getline
    fichier.ignore(1, '\n');
}

void Collection::Reset()
{
    for (const auto& elem : m_Cartes)
    {
        elem->Reset();
    }
}

