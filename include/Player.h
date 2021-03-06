#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "defines.h"
#include "Collection.h"

class Player
{
    private:
        std::string m_Nom;                  //le nom
        Collection m_Collection;            //la collection de cartes appartenant au joueur
        std::queue<Carte *> m_Deck;         //la piohe du joueur
        std::stack<Carte *> m_Cimetiere;    //le cimetière dans la partie
        std::vector<Carte *> m_Main;        //les cartes dans la main du joueur
        Carte *m_Enjeu;                     //l'enjeu
        Special *m_Special[MAXSPECIAL];     //la/les spéciales persistantes
        Creature *m_Active[MAXACTIVE];      //la/les créatures actives
        std::stack<Energie *> m_Energie;    //la/les cartes énergies consommées
        Carte *m_Exclusive;                 //la carte exclusive à ce joueur (bowser n'a pas mario etc)

        Domaines m_CurrentEnergy;           //la quantité d'énergie disponible pour chaque domaine
        int m_HP;
        int m_MaxHP;
        int m_Money;

        /** une fonction pour avoir l'action du joueur. */
        bool InputCheck(PlayerInput& p_input, Player& opponent);
        /** une fonction pour choisir et afficher la description d'une carte */
        void ShowDescription(Player& opponent, BITMAP *fond, const Sprites& sprites, PlayerInput& p_input);
        /** une fonction qui donne des ordres aux active (créatures, spéciales) */
        void CardAction(PlayerInput& p_input, Player& opponent);
        /** une fonction pour voir s'il faut placer une carte depuis la main */
        void MoveHand(PlayerInput& p_input);

    protected:

    public:
        [[deprecated]]
        Player();
        Player(std::map<int, ModeleCarte *> modeles);
        Player(std::istream& fichier, std::map<int, ModeleCarte *> modeles);
        virtual ~Player();

        /** met le joueur en place pour une nouvelle partie (battre le deck et placer l'enjeu) */
        void NewGame(bool askChoose);

        /** dessine un demi écran pour le joueur en cours.
        turn est vraie si c'est au tour de ce joueur */
        void Draw(BITMAP *dest, bool turn, const Sprites& sprites, const PlayerInput& p_input); //affiche les cartes sur la bitmap en paramètre

        /** Fait toutes les actions à faire après que le joueur ait joué */
        void EndTurn(Player& enemy);

        /** Fait toutes les actions à faire avant que le joueur ait joué */
        void StartTurn(Player& enemy);

        /** La boucle évennementielle. effectue aussi les action à partir de ce que le joueur choisit */
        void Turn(Player& opponent, BITMAP *buffer, const Sprites& sprites, PlayerInput& p_input);

        /** Pour recevoir des degats */
        void TakeDamage(int quant);

        /** perd l'enjeu et le renvoie */
        Carte *LoseEnjeu();

        /** le gain de l'enjeu */
        void WinGame(Player& loser);

        /** Sauvegarde le joueur (PAS LA PARTIE) */
        void WriteFile(std::ostream& fichier);

        /** Charge un joueur (PAS LA PARTIE) */
        void ReadFile(std::istream& fichier, std::map<int, ModeleCarte *> modeles);

        /** entreer les cartes pour une nouvelle collection depuis l'utilisateur */
        void NewCol(std::map<int, ModeleCarte *> modeles);

        //accesseurs "utiles"/"necessaires"

        /** revoie true si le joueur a perdu */
        bool GetDead();

        /** remet à MaxHP l'HP du joueur */
        void Reset();

        /** pour pouvoir acheter une carte de plus et l'ajouter à la collection */
        void Shopping(std::map<int, ModeleCarte *> modeles);

        Carte* PopCimetiere();
        //getters/setters
        Creature* GetActive(int num) { return m_Active[num]; }
        Special* GetSpecial(int num) { return m_Special[num]; }
        Energie* GetEnergie() { return m_Energie.empty()?nullptr:m_Energie.top(); }
        Carte* GetCimetiere() { return m_Cimetiere.empty()?nullptr:m_Cimetiere.top(); }
        Domaines& GetCurrentEnergy() { return m_CurrentEnergy; }
        std::vector<Carte*>& GetMain() { return m_Main; }

        std::string GetNom() { return m_Nom; }
        void SetNom(std::string val) { m_Nom = val; }
        Collection& GetCollection() { return m_Collection; }
        void SetCollection(Collection val) { m_Collection = val; }
        std::queue<Carte*> GetDeck() { return m_Deck; }
        void SetDeck(std::queue<Carte*> val) { m_Deck = val; }
        Carte* GetEnjeu() { return m_Enjeu; }
        void SetEnjeu(Carte* val) { m_Enjeu = val; }
        Carte* GetExclusive() { return m_Exclusive; }
        void SetExclusive(Carte* val) { m_Exclusive = val; }
        int GetHP() { return m_HP; }
};

#endif // PLAYER_H_INCLUDED
