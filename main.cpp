#include "defines.h"
#include "Player.h"

/**
  * il aurait fallu depuis le début faire une classe bouton avec une fonction bool clicked() mais bon
  */


using namespace std;

//initialisation de allegro
void init_alleg(int sizex, int sizey);
void load_sprites(Sprites& sprites);
void load_modeles(map<int, ModeleCarte*>& dest);
void load_players(vector<Player *>& players, map<int, ModeleCarte *> modeles);

int main()
{
    init_alleg(XSCREEN, YSCREEN); //doit être avant d'utiliser des fonctions d'alleg (create_bitmap par exemple)

    BITMAP *buffer;
    Sprites sprites;
    map<int, ModeleCarte *> modeles;
    vector<Player *> playerList;
    PlayerInput p_input;
    Player *players[2];
    bool endGame = false;

    load_sprites(sprites);
    load_modeles(modeles);
    load_players(playerList, modeles);

    buffer = create_bitmap(XSCREEN, YSCREEN);

    //préparation à la partie
    players[0] = playerList.at(0);
    players[1] = playerList.at(1);

    players[0]->NewGame();
    players[1]->NewGame();

    p_input.dragging = false;
    p_input.prevClick = false;

    while (!key[KEY_ESC] && !endGame)
    {
        for (int i=0;i<2;i++)
        {
            players[i]->StartTurn(*players[!i]);

            p_input.whoTurn = i;

            players[i]->Turn(*players[!i], buffer, sprites, p_input);

            if (key[KEY_ESC])
            {
                cout << endl << "Pressed ESC!!!!!" << endl;
                break;
            }

            players[i]->EndTurn(*players[!i]);

            if (players[0]->GetDead() || players[1]->GetDead())
            {
                endGame = true;
                cout << endl << "partie terminée!!" << endl;

                if (players[0]->GetDead() && players[1]->GetDead())
                   cout << "\x1B[36m FELICITATIONS VOUS AVEZ RÉUSSI À FAIRE UN MATCH NUL!!!!!! \x1B[0m" << endl;
                else
                {
                    int winner = players[0]->GetDead();
                    cout << "Le joueur " << (!winner?"1":"2") << " a gagné!!" << endl;

                    players[winner]->WinGame(*players[!winner]);
                }

                break;
            }
        }
    }

    ofstream pfichier(FPINFO, ios::out | ios::trunc);

    pfichier << playerList.size() << endl;

    for (const auto& elem : playerList)
    {
        elem->WriteFile(pfichier);
        delete(elem);
    }

    pfichier.close();

    for (const auto& elem : modeles)
    {
        delete(elem.second);
    }

    return 0;
}


void load_sprites(Sprites& sprites)
{
    sprites.souris = load_bitmap(FSOURIS, nullptr);ERR_CHARG(sprites.souris)
    sprites.buttonEndTurn = load_bitmap(FENDTURN, nullptr);ERR_CHARG(sprites.buttonEndTurn)
    sprites.buttonPlayer= load_bitmap(FPLAYER, nullptr);ERR_CHARG(sprites.buttonPlayer)
    sprites.cardBack = load_bitmap(FCARDB, NULL); ERR_CHARG(sprites.cardBack)
    sprites.cardTemplate = load_bitmap(FCARDT, NULL); ERR_CHARG(sprites.cardTemplate)
}

ModeleCarte *WhatCard(CardType type, int cardNum, istream& fichier)
{
    switch (type)
    {
        case ENERGIE:
        return new ModeleEnergie(cardNum, fichier);
    break;

        case CREATURE:
        return new ModeleCreature(cardNum, fichier);
    break;

        case SPECIAL:
        switch (cardNum)
        {
            case GREENSHROOM:
            return new GreenShroom(cardNum, fichier);
        break;

            case REDSHROOM:
            return new RedShroom(cardNum, fichier);
        break;

            case FLOWER:
            return new Flower(cardNum, fichier);
        break;

            case COIN:
            return new Coin(cardNum, fichier);
        break;

            case STAR:
            return new Star(cardNum, fichier);
        break;

            case POW:
            return new Pow(cardNum, fichier);
        break;

            default:
            return new ModeleSpecial(cardNum, fichier);
        }
    break;

        default:
        throw type;
    }
}

void load_modeles(map<int, ModeleCarte*>& dest)
{
    ifstream fichier(FMODELES, ios::in); ERR_CHARG(fichier.is_open())

    int nbModeles;

    fichier >> nbModeles;

    try{
        for (int i=0;i<nbModeles;i++)
        {
            int currType;
            int currNum; //le nuléro du modele de la carte

            fichier >> currType;
            fichier >> currNum;

            try{
                dest[currNum] = WhatCard((CardType) currType, currNum, fichier);
            }
            catch (int a)
            {
                cerr << endl << "file asked for a card type that does not exist:  " << a << endl;
                throw a;
            }
        }
    }
    catch (const exception& e)
    {
        fichier.close();
        throw e;
    }
    catch (int a)
    {
        fichier.close();
        throw a;
    }

    fichier.close();
}

void load_players(vector<Player *>& players, map<int, ModeleCarte *> modeles)
{
    ifstream fichier(FPINFO, ios::in); ERR_CHARG(fichier.is_open())

    int nbPlayer;

    fichier >> nbPlayer;

    fichier.ignore(1, '\n');

    for (int i=0;i<nbPlayer;i++)
    {
        try{
            players.push_back(new Player(fichier, modeles));
        }
        catch (const out_of_range& e)
        {
            cerr << "for the " << i << "th player" << endl;
            fichier.close();
            throw e;
        }
    }
    fichier.close();
}

//initialisation de allegro
void init_alleg(int sizex, int sizey)
{
    allegro_init();

    install_keyboard();
    install_mouse();

    install_timer();
    srand(time(nullptr));

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, sizex, sizey, 0, 0))
    {
        allegro_message("erreur gfx");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}

