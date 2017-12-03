#include "Player.h"

using namespace std;

//constructeur par défaud. ne pas l'utiliser
Player::Player()
    :m_Nom("Pas Moi"), m_HP(0), m_MaxHP(0)
{
    m_Enjeu = nullptr;

    for (int i=0;i<MAXSPECIAL;i++)
    {
        m_Special[i] = nullptr;
    }

    for (int i=0;i<MAXACTIVE;i++)
    {
        m_Active[i] = nullptr;
    }

    for (int i=0;i<NBDOMAINE;i++)
    {
        m_CurrentEnergy.value[i] = 0;
    }
}

Player::Player(map<int, ModeleCarte *> modeles)
    :m_HP(20), m_MaxHP(20), m_Money(0)
{
    m_Enjeu = nullptr;

    cin.ignore(1, '\n');

    cout << endl << "What is your name?" << endl;
    getline(cin, m_Nom);

    NewCol(modeles);

    for (int i=0;i<MAXSPECIAL;i++)
    {
        m_Special[i] = nullptr;
    }

    for (int i=0;i<MAXACTIVE;i++)
    {
        m_Active[i] = nullptr;
    }

    for (int i=0;i<NBDOMAINE;i++)
    {
        m_CurrentEnergy.value[i] = 0;
    }
}

Player::Player(istream& fichier, map<int, ModeleCarte *> modeles)
{
    ReadFile(fichier, modeles);

    m_HP = m_MaxHP;

    m_Enjeu = nullptr;

    for (int i=0;i<MAXSPECIAL;i++)
    {
        m_Special[i] = nullptr;
    }

    for (int i=0;i<MAXACTIVE;i++)
    {
        m_Active[i] = nullptr;
    }

    for (int i=0;i<NBDOMAINE;i++)
    {
        m_CurrentEnergy.value[i] = 0;
    }
}

Player::~Player()
{
    //dtor
}


void Player::WriteFile(ostream& fichier)
{
    fichier << endl  << m_Nom << endl;
    fichier << m_MaxHP << endl;
    fichier << m_Money << endl;

    m_Collection.WriteFile(fichier);
    fichier << endl;
}

void Player::ReadFile(istream& fichier, map<int, ModeleCarte *> modeles)
{
    fichier.ignore(1, '\n');
    getline(fichier, m_Nom);
    fichier >> m_MaxHP;
    m_HP = m_MaxHP;
    fichier >> m_Money;

    try{
        m_Collection.ReadFile(fichier, modeles);
    }
    catch (const out_of_range& e)
    {
        cerr << "for player " << m_Nom << endl;
        throw e;
    }

    fichier.ignore(1, '\n');
}

void Player::NewCol(map<int, ModeleCarte *> modeles)
{
    cout << "Please choose " << CSTARTSIZE << " cards amongst the following to create your collection" << endl
         << "PRESS ENTER TO CONTINUE" << endl;

    cin.ignore(1, '\n');

    for (const auto& elem : modeles)
    {
        cout << endl << elem.second->GetCardNum() << "\t" << elem.second->GetNom() << endl;
    }

    for (int i=0;i<CSTARTSIZE;i++)
    {
        bool works = false;
        do
        {
            int currNum;
            cin >> currNum;

            try{
                m_Collection.AddNewCard(modeles.at(currNum));
                works = true;
            }
            catch (const out_of_range& e)
            {
                cout << endl << "This/a card that you asked for doesn't exist" << endl;
                works = false;
            }
        } while (!works);
    }
}

void Player::NewGame(bool askChoose)
{
    if (askChoose)
        m_Collection.CreateDeck(m_Deck);
    else
        m_Collection.CreateDeck(m_Deck, 0);

    m_Enjeu = m_Deck.front();
    m_Deck.pop();

    m_Collection.RemoveCard(m_Enjeu); //l'enjeu n'exeiste que en jeu
}

Carte *Player::LoseEnjeu()
{
    Carte *rep = m_Enjeu;
    m_Enjeu = nullptr;

    //maintenant la variable locale rep est le seul pointeur sur cette carte

    return rep;
}

void Player::WinGame(Player& loser)
{
    m_Collection.AddCard(loser.LoseEnjeu());
    m_Money++;
}

void Player::Reset()
{
    m_HP = m_MaxHP;

    //on vide tout. les pointeurs sont conservés dans la colléction
    while (!m_Deck.empty())
        m_Deck.pop();

    while (!m_Cimetiere.empty())
        m_Cimetiere.pop();

    m_Main.clear();


    for (int i=0;i<MAXSPECIAL;i++)
        m_Special[i] = nullptr;

    for (int i=0;i<MAXACTIVE;i++)
        m_Active[i] = nullptr;

    while (!m_Energie.empty())
        m_Energie.pop();

    for (int i=0;i<NBDOMAINE;i++)
    {
        m_CurrentEnergy.value[i] = 0; //pourrait être changeable si peach pour le royaume champi par exemple
    }

    if (m_Enjeu) //si l'enjeu n'est pas perdu on le garde
    {
        m_Collection.AddCard(m_Enjeu);
        m_Enjeu = nullptr;
    }

    m_Collection.Reset();
}

void Player::Shopping(map<int, ModeleCarte *> modeles)
{
    cout << endl << "You have " << m_Money << " money, you can" << (m_Money?"":"'t") << " buy another card" << endl;

    if (m_Money)
    {
        cout << "Choose a card" << endl;
        for (const auto& elem : modeles)
            cout << elem.second->GetCardNum() << "\t" << elem.second->GetNom() << endl;

        bool works = false;
        do{
            int Num;
            cin >> Num;

            try{
                m_Collection.AddNewCard(modeles.at(Num));
                works = true;
            }
            catch (const out_of_range& e)
            {
                cout << endl << "This/a card that you asked for doesn't exist" << endl;
                works = false;
            }
        } while (!works);
        m_Money--;
    }
}


void Player::TakeDamage(int quant)
{
    m_HP -= quant;

    if (m_HP<0)
        m_HP = 0;
}

bool Player::GetDead()
{
    if (m_HP<=0)
        return true;

    if (!m_Main.empty())
        return false;
    if (!m_Deck.empty())
        return false;

    for (int i=0;i<MAXACTIVE;i++)
    {
        if (m_Active[i])
            return false;
    }

    for (int i=0;i<MAXSPECIAL;i++)
    {
        if (m_Special[i])
            return false;
    }

    return true;
}



void Player::EndTurn(Player& enemy)
{
    //update de toutes les cartes

    for (int i=0;i<MAXSPECIAL;i++)
    {
        if (m_Special[i])
        {
            m_Special[i]->EndTurn(*this, enemy);
        }
    }

    //TOUJOURS FAIRE LES SPECIALES AVANT LES AUTRES

    for (int i=0;i<MAXACTIVE;i++)
    {
        if (m_Active[i])
        {
            m_Active[i]->EndTurn(*this, enemy);
        }
    }

}

void Player::StartTurn(Player& enemy)
{
    if (m_Main.size()<MAXHAND && !m_Deck.empty())
    {
        m_Main.push_back(m_Deck.front()); //on met la carte en haut de la pioche dans la main
        m_Deck.pop(); //on enlève la carte d'en haut de la pioche
    }

    for (int i=0;i<MAXSPECIAL;i++)
    {
        if (m_Special[i])
        {
            m_Special[i]->StartTurn(*this, enemy);

            if (!m_Special[i]->GetActiveLeft()) //si la carte a expiré, faut l'enlever
            {
                m_Cimetiere.push(m_Special[i]);
                m_Special[i] = nullptr;
            }
        }
    }

    //check des créatures en jeu
    for (int i=0;i<MAXACTIVE;i++)
    {
        if (m_Active[i])
        {
            if (!m_Active[i]->GetHP()) //si hp=0 de la carte, faut l'enlever
            {
                m_Cimetiere.push(m_Active[i]);
                m_Active[i] = nullptr;
            }
        }
    }
}

//en dessous de ce point les fonctions servent à la fonction Turn ou en dessous uniquement

void Player::ShowDescription(Player& opponent, BITMAP *fond, const Sprites& sprites, PlayerInput& p_input)
{
    Carte *inter = nullptr;
    switch (p_input.endType)
    {
        case PENERGY: //existence PAS déjà blindée
        if (p_input.endSide)
        {
            if (!m_Energie.empty())
                inter = m_Energie.top();
        }
        else
            inter = opponent.GetEnergie();
    break;

        case PCIMETIERE: //existence PAS déjà blindée
        if (p_input.endSide)
        {
            if (!m_Cimetiere.empty())
                inter = m_Cimetiere.top();
        }
        else
            inter = opponent.GetCimetiere();
    break;

        case PACTIVE: //existence déjà blindée
        inter = p_input.endSide ? m_Active[p_input.endNum] : opponent.GetActive(p_input.endNum);
    break;

        case PSPECIAL: //existence déjà blindée
        inter = p_input.endSide ? m_Special[p_input.endNum] : opponent.GetSpecial(p_input.endNum);
    break;

        case PMAIN: //existence déjà blindée
        inter = m_Main.at(p_input.endNum);
    break;

        default: //n'arrivera à priori jamais
        inter = nullptr;
    break;
    }

    if (inter)
        inter->Detail(fond, p_input, sprites); //on appelle la fonction qui montre les détails de la carte
}

int CardButtonCheck(int x, int y, int precision)
{
    if (x>=XDESCRI && x<(XDESCRI+WDESCRI) && y>=YDESCRI && y<(YDESCRI+HDESCRI))
    {
        return CDESCRI;
    }

    if (precision==PACTIVE || precision==PSPECIAL)
    {
        if (x>=XACTION && x<(XACTION+WACTION) && y>=YACTION && y<(YACTION+HACTION))
        {
            if (precision==PSPECIAL)
                return CACTION;
            else
            {
                if (y<(YACTION + HATTACK))
                    return CATTACK1;
                else
                    return CATTACK2;
            }
        }
    }

    return CNOTHING;
}

//aurait pu être fait avec une classe bouton...
bool ChoiceCheck(int& choiceType, int& choiceNum, int& side, int& cWhere)
{
    int x = mouse_x - XPLAYERSIDE;
    int y = mouse_y;

    if (y<YPLAYERSIDE)
    {
        side = 0;
    }
    else
    {
        y -= YPLAYERSIDE;
        side = 1;
    }

    choiceNum = 0;
    cWhere = -1;

    //deprecated, but you never know...
    if (x<0 || x>=WPLAYERSIDE || y<0 || y>=HPLAYERSIDE)
        return false;

    //test de chaque case. pourrait être fait avec des modulos + switch mais vu qu'on va peut être pas aligner les cartes...
    if (x>=XENERGY && x<XENERGY+CARDWIDTH && y>=YENERGY && y<YENERGY+CARDHEIGHT)
    {
        choiceType = PENERGY;
        cWhere = CardButtonCheck(x-XENERGY, y-YENERGY, choiceType);
        return true;
    }
    else if (x>=XACTIVE && x<(XACTIVE + MAXACTIVE*PDIST) && y>=YACTIVE && y<(YACTIVE+CARDHEIGHT))
    {
        if ((x-XACTIVE)%PDIST < CARDWIDTH)
        {
            choiceType = PACTIVE;
            choiceNum = (int)((x-XACTIVE)/PDIST);
            cWhere = CardButtonCheck(x-XACTIVE - choiceNum*PDIST, y-YACTIVE, choiceType);
            return true;
        }
        else
            return false;
    }
    else if (x>=XSPECIAL && x<(XSPECIAL+MAXSPECIAL*PDIST) && y>=YSPECIAL && y<(YSPECIAL+CARDHEIGHT))
    {
        if ((x-XSPECIAL)%PDIST < CARDWIDTH)
        {
            choiceType = PSPECIAL;
            choiceNum = (int)((x-XSPECIAL)/PDIST);
            cWhere = CardButtonCheck(x-XSPECIAL- choiceNum*PDIST, y-YSPECIAL, choiceType);
            return true;
        }
        else
            return false;
    }
    else if (x>=XENJEU && x<(XENJEU+CARDWIDTH) && y>=YENJEU && y<(YENJEU+CARDHEIGHT))
    {
        choiceType = PENJEU;
        return true;
    }
    else if (x>=XPIOCHE && x<(XPIOCHE+CARDWIDTH) && y>=YPIOCHE && y<(YPIOCHE+CARDHEIGHT))
    {
        choiceType = PPIOCHE;
        return true;
    }
    else if (x>=XCIMETIERE && x<(XCIMETIERE+CARDWIDTH) && y>=YCIMETIERE && y<(YCIMETIERE+CARDHEIGHT))
    {
        choiceType = PCIMETIERE;
        cWhere = CardButtonCheck(x-XCIMETIERE, y-YCIMETIERE, choiceType);
        return true;
    }
    else if (side && x>=XMAIN && x<(XMAIN+MAXHAND*PDIST) && y>=YMAIN && y<(YMAIN+CARDHEIGHT))
    {

        if ((x-XMAIN)%PDIST < CARDWIDTH)
        {
            choiceType = PMAIN;
            choiceNum = (int)((x-XMAIN)/PDIST);
            cWhere = CardButtonCheck(x-XMAIN - choiceNum*PDIST, y-YMAIN, choiceType);
            return true;
        }
        else
            return false;
    }
    else if (x>=XPLAYER && x<(XPLAYER+WPLAYER) && y>=YPLAYER && y<(YPLAYER+HPLAYER))
    {
        choiceType = PPLAYER;
        return true;
    }

    return false;
}

bool Player::InputCheck(PlayerInput& p_input, Player& opponent)
{
    bool rep = false;

    if (mouse_b&1)
    {
        if (!p_input.prevClick)
        {
            int choiceType, choiceNum;
            if (ChoiceCheck(choiceType, choiceNum, p_input.startSide, p_input.startCWhere)) //blindage QUE pour les cartes qui existent
            {
                bool couldClick = false;
                switch (choiceType)
                {
                    default: //PENERGY, PENJEU, PPIOCHE, PCIMETIERE, PPLAYER
                    couldClick = true;
                break;

                    case PACTIVE:
                    couldClick = (bool)(p_input.startSide ? m_Active[choiceNum] : opponent.GetActive(choiceNum));
                break;

                    case PSPECIAL:
                    couldClick = (bool)(p_input.startSide ? m_Special[choiceNum] : opponent.GetSpecial(choiceNum));
                break;

                    case PMAIN:
                    if (p_input.startSide && choiceNum < m_Main.size()) //on ne prend la main que du joueur
                        couldClick = true;
                break;
                }
                if (couldClick)
                {
                    p_input.startType = choiceType;
                    p_input.startNum = choiceNum;
                    p_input.startX = mouse_x;
                    p_input.startY = mouse_y;
                    p_input.dragging = true;
                }
            }
        }
        p_input.prevClick = true;
    }
    else
    {
        if (p_input.dragging)
        {
            p_input.dragging = false;
            if (ChoiceCheck(p_input.endType, p_input.endNum, p_input.endSide, p_input.endCWhere)) // on blinde PAS les qui existent/n'existent pas
            {
                rep = true;

                p_input.endX = mouse_x;
                p_input.endY = mouse_y;
            }
        }
        p_input.prevClick = false;
    }
    return rep;
}

bool Clicked(const PlayerInput& p_input)
{
    return (p_input.endCWhere==p_input.startCWhere
            && p_input.endNum==p_input.startNum
            && p_input.endSide==p_input.startSide
            && p_input.endType==p_input.startType);
}

//contient la boucle evennementielle
void Player::Turn(Player& opponent, BITMAP *buffer, const Sprites& sprites, PlayerInput& p_input)
{
    bool endTurn = false;
    BITMAP *playerView = create_bitmap(XSCREEN, YSCREEN/2);

    do
    {
        this->Draw(playerView, true, sprites, p_input);
        blit(playerView, buffer, 0, 0, 0, YSCREEN/2, XSCREEN, YSCREEN/2);

        opponent.Draw(playerView, false, sprites, p_input);
        blit(playerView, buffer, 0, 0, 0, 0, XSCREEN, YSCREEN/2);

        line(buffer, 0, YSCREEN/2, XSCREEN, YSCREEN/2, NOIR);

        draw_sprite(buffer, sprites.buttonEndTurn, XENDTURN, YENDTURN);
     //   cout << mouse_x << " " << mouse_y << endl;

        draw_sprite(buffer, sprites.souris, mouse_x, mouse_y);
        blit(buffer, screen, 0, 0, 0, 0, XSCREEN, YSCREEN);

        if (mouse_b&1) //pour la fin du tour
        {
            if (!p_input.prevClick)
            {
                if (mouse_x>=XENDTURN && mouse_x<=(XENDTURN+WENDTURN) && mouse_y>=YENDTURN && mouse_y<=(YENDTURN+HENDTURN))
                    endTurn = true;
            }
        }

        if (InputCheck(p_input, opponent))
        {
            if (p_input.endCWhere==CDESCRI && Clicked(p_input)) //click sur la description. CWhere sont déjà à -1 si la carte est face cachée
            {
                //test de si c'est une carte face visible + description
                ShowDescription(opponent, buffer, sprites, p_input);
            }
            else if (p_input.startSide)
            {
                switch (p_input.startType)
                {
                    default: //PENERGY, PENJEU, PPIOCHE, PCIMETIERE, PPLAYER
                break;

                    case PACTIVE: //l'existance de la carte est déjà blindé
                    case PSPECIAL: //l'éxistance de la carte est déjà blindé
                    if (p_input.endSide && p_input.endType==PCIMETIERE)
                    {
                        if (p_input.startType==PACTIVE)
                        {
                            m_Cimetiere.push(m_Active[p_input.startNum]);
                            m_Active[p_input.startNum] = nullptr;
                        }
                        else
                        {
                            m_Cimetiere.push(m_Special[p_input.startNum]);
                            m_Special[p_input.startNum] = nullptr;
                        }
                    }
                    else
                    {
                        CardAction(p_input, opponent);
                    }
                break;


                    case PMAIN: //drag depuis la main
                    if (p_input.endSide)
                    {
                        MoveHand(p_input);
                    }
                break;
                }
            }
        }

        rest(20);

        if (key[KEY_ESC])
            break;

    }while (!endTurn);

    p_input.dragging = false;
}

/** que si part de pactive ou pspecial */
void Player::CardAction(PlayerInput& p_input, Player& opponent)
{
    if (p_input.startCWhere==CATTACK1 || p_input.startCWhere==CATTACK2) //rappel que le CACTION des cartes spéciales est le même que CATTACK1
    {
        if (p_input.startType==PSPECIAL)
            m_Special[p_input.startNum]->SetAction(*this, opponent, p_input);
        else if (p_input.startType==PACTIVE)
        {
            //si on lache le drag dans le camp adversaire
            if (!p_input.endSide)
            {
                if (p_input.endType==PACTIVE)
                {
                    if (opponent.GetActive(p_input.endNum)) //si la carte visée existe
                    {
                        this->m_Active[p_input.startNum]->SetAttack(p_input.endNum, p_input.startCWhere);
                    }
                }
                else if (p_input.endType==PPLAYER)
                {
                    this->m_Active[p_input.startNum]->SetAttack(-1, p_input.startCWhere);//on lui dit d'attaquer le joueur ennemi
                }
            }
        }
    }
}

void Player::MoveHand(PlayerInput& p_input)
{
    CardType type = m_Main[p_input.startNum]->GetCardType();

    switch (p_input.endType)
    {
        case PENERGY:
        if (type==ENERGIE)
        {
            m_Energie.push(dynamic_cast<Energie *>(m_Main.at(p_input.startNum)));
            m_Main.erase(m_Main.begin() + p_input.startNum);
            m_Energie.top()->Use(m_CurrentEnergy); //on active la nouvelle carte
        }
    break;

        case PACTIVE:
        if (type==CREATURE && m_Active[p_input.endNum]==nullptr) // si il n'y a pas déjà une carte là
        {
            m_Active[p_input.endNum] = dynamic_cast<Creature *>(m_Main.at(p_input.startNum));
            m_Main.erase(m_Main.begin() + p_input.startNum);
        }
    break;

        case PSPECIAL:
        if (type==SPECIAL && m_Special[p_input.endNum]==nullptr)
        {
            m_Special[p_input.endNum] = dynamic_cast<Special *>(m_Main.at(p_input.startNum));
            m_Main.erase(m_Main.begin() + p_input.startNum);
        }
    break;

        case PCIMETIERE:
        m_Cimetiere.push(m_Main.at(p_input.startNum));
        m_Main.erase(m_Main.begin() + p_input.startNum);
    break;

        default: //PENJEU, PPIOCHE, PPLAYER, PMAIN
    break;
    }
}

//pourrait etre plus DRY mais bon
void Player::Draw(BITMAP *dest, bool turn, const Sprites& sprites, const PlayerInput& p_input)
{
    BITMAP *rep = create_bitmap(dest->w, dest->h);
    blit(sprites.fond, rep, XPLAYERSIDE, turn?YPLAYERSIDE:0, 0, 0, dest->w, dest->h);

    int  x, y;

    x = XENERGY;//pour être dans le réfferentiel de la carte
    y = YENERGY;
    //la face de la carte en haut + infos
    rect(rep, x-1, y-1, x+CARDWIDTH, y+CARDHEIGHT, NOIR);
    if (!m_Energie.empty())
    {
        draw_sprite(rep, m_Energie.top()->GetCardFront(), x, y);
    }

    //face de la carte + infos
    for (int i=0;i<MAXACTIVE;i++)
    {
        x = XACTIVE + i*(CARDWIDTH+MARGIN); //pour être dans le réfferentiel de la carte
        y = YACTIVE;

        rect(rep, x - 1 , y - 1, x + CARDWIDTH, y + CARDHEIGHT, ROUGE);

        if (m_Active[i])
        {
            if (m_Active[i]->IsFrozen()) // si la carte est freeze on change la couleur du contour
                rect(rep, x - 1 , y - 1, x + CARDWIDTH, y + CARDHEIGHT, COL_UI_ACC);

            draw_sprite(rep, m_Active[i]->GetCardFront(), x, y);

            textprintf_ex(rep, font, x + 19, y +30, NOIR, -1, "%d", m_Active[i]->GetHP());
            //textprintf_ex(rep, font, x + XTEXT + 4, y + YACTION + 6, NOIR, -1, "%dDMG", m_Active[i]->GetAD());
        }
    }

    //face de la carte + infos
    for (int i=0;i<MAXSPECIAL;i++)
    {
        x = XSPECIAL + i*(CARDWIDTH+MARGIN);//pour être dans le réfferentiel de la carte
        y = YSPECIAL;

        rect(rep, x-1, y-1, x+CARDWIDTH, y+CARDHEIGHT, BLEU);
        if (m_Special[i])
        {
            draw_sprite(rep, m_Special[i]->GetCardFront(), x, y);

            textprintf_ex(rep, font, x + 61, y + 22, NOIR, -1, "%d", m_Special[i]->GetActiveLeft());
        }
    }

    x = XENJEU;//pour être dans le réfferentiel de la carte
    y = YENJEU;
    //carte face cachée
    rect(rep, x-1, y-1, x+CARDWIDTH, y+CARDHEIGHT, VERT);
    if (m_Enjeu)
        draw_sprite(rep, sprites.cardBack, x, y); //rectfill(rep, x, y, x+CARDWIDTH, y+CARDHEIGHT, VERT);

    x = XPIOCHE;//pour être dans le réfferentiel de la carte
    y = YPIOCHE;
    //carte face cachée
    rect(rep, x-1, y-1, x+CARDWIDTH, y+CARDHEIGHT, MAG);
    if (!m_Deck.empty())
        draw_sprite(rep, sprites.cardBack, x, y); //rectfill(rep, x, y, x+CARDWIDTH, y+CARDHEIGHT, MAG);

    x = XCIMETIERE;//pour être dans le réfferentiel de la carte
    y = YCIMETIERE;
    //face de la carte en haut de la pile + infos
    rect(rep, x-1, y-1, x+CARDWIDTH, y+CARDHEIGHT, COL_SAND);
    if (!m_Cimetiere.empty())
    {
        draw_sprite(rep, m_Cimetiere.top()->GetCardFront(), x, y);
    }

    rectfill(rep, XPLAYER, YPLAYER, XPLAYER+WPLAYER-1, YPLAYER+HPLAYER-1, (p_input.whoTurn^turn)?COL_P1_FOND:COL_P2_FOND);
    draw_sprite(rep, sprites.buttonPlayer, XPLAYER, YPLAYER);

    textprintf_ex(rep, font, XPLAYER, YPLAYER + HPLAYER + MARGIN, NOIR, -1, "HP: %d/%d", m_HP, m_MaxHP);
    textprintf_ex(rep, font, XPLAYER, YPLAYER + HPLAYER + 2*MARGIN, VERT, -1, "Shroom energy: %d", m_CurrentEnergy.value[0]);
    textprintf_ex(rep, font, XPLAYER, YPLAYER + HPLAYER + 3*MARGIN, COL_ROCK, -1, "Cave energy: %d", m_CurrentEnergy.value[1]);
    textprintf_ex(rep, font, XPLAYER, YPLAYER + HPLAYER + 4*MARGIN, NOIR, -1, "Cloud energy: %d", m_CurrentEnergy.value[2]);
    textprintf_ex(rep, font, XPLAYER, YPLAYER + HPLAYER + 5*MARGIN, ROUGE, -1, "Bowser energy: %d", m_CurrentEnergy.value[3]);


    if (turn)
    {
        for (unsigned int i = 0;i<m_Main.size();i++) //m_Main est un vecteur (données contingues en mémoire)
        {
            x = XMAIN + i*(CARDWIDTH+MARGIN);
            y = YMAIN;

            rect(rep, x-1, y-1, x+CARDWIDTH, y+CARDHEIGHT, COL_MOUNTAIN);

            draw_sprite(rep, m_Main.at(i)->GetCardFront(), x, y);

            /// FAIRE LES HP ET NB RESTANT
        }

        if (p_input.dragging)
            line(rep, p_input.startX - XPLAYERSIDE, p_input.startY - YPLAYERSIDE, mouse_x, mouse_y-YSCREEN/2, NOIR);

    }
    else
    {

        if (p_input.dragging)
            line(rep, p_input.startX , p_input.startY , mouse_x, mouse_y, NOIR);

        //rotate_sprite(dest, rep, 0, 0, 128); //rotation complète
    }

    blit(rep, dest, 0, 0, 0, 0, dest->w, dest->h);

    destroy_bitmap(rep);
}


