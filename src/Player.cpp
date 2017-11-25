#include "Player.h"

using namespace std;

Player::Player()
    :m_HP(20), m_MaxHP(20)
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


    m_Deck.push(new Creature(*(new ModeleCreature(0))));
    m_Deck.push(new Creature(*(new ModeleCreature(0))));
    m_Deck.push(new Energie(*(new ModeleEnergie)));
    m_Deck.push(new Creature(*(new ModeleCreature(0))));
    m_Deck.push(new Special(*(new ModeleSpecial)));
    m_Deck.push(new Special(*(new ModeleSpecial)));
    m_Deck.push(new Creature(*(new ModeleCreature(0))));
    m_Deck.push(new Creature(*(new ModeleCreature(0))));

    m_Exclusive = nullptr;

    for (int i=0;i<NBDOMAINE;i++)
    {
        m_CurrentEnergy.value[i] = 0;
    }
}

Player::~Player()
{
    //dtor
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

void Player::StartTurn()
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
            m_Special[i]->StartTurn();

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

bool ChoiceCheck(int& choiceType, int& choiceNum, int& side)
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

    if (x<0 || x>=WPLAYERSIDE || y<0 || y>=HPLAYERSIDE)
        return false;

    //test de chaque case. pourrait être fait avec des modulos + switch mais vu qu'on va peut être pas aligner les cartes...
    if (x>=XENERGY && x<XENERGY+CARDWIDTH && y>=YENERGY && y<YENERGY+CARDHEIGHT)
    {
        choiceType = PENERGY;
        return true;
    }
    else if (x>=XACTIVE && x<(XACTIVE + MAXACTIVE*PDIST) && y>=YACTIVE && y<(YACTIVE+CARDHEIGHT))
    {

        if ((x-XACTIVE)%PDIST < CARDWIDTH)
        {
            choiceType = PACTIVE;
            choiceNum = (int)((x-XACTIVE)/PDIST);
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
        return true;
    }
    else if (side && x>=XMAIN && x<(XMAIN+MAXHAND*PDIST) && y>=YMAIN && y<(YMAIN+CARDHEIGHT))
    {

        if ((x-XMAIN)%PDIST < CARDWIDTH)
        {
            choiceType = PMAIN;
            choiceNum = (int)((x-XMAIN)/PDIST);
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


bool Player::InputCheck(PlayerInput& p_input)
{
    bool rep = false;

    if (mouse_b&1)
    {
        if (!p_input.prevClick)
        {
            int choiceType, choiceNum;
            if (ChoiceCheck(choiceType, choiceNum, p_input.startSide)) //blindage QUE pour les cartes qui existent
            {

                bool couldClick = false;

                switch (choiceType)
                {
                    case PENERGY:
                    case PENJEU:
                    case PPIOCHE:
                    case PCIMETIERE:
                    case PPLAYER:
                    couldClick = true;
                break;

                    case PSPECIAL:
                    if (m_Special[choiceNum])
                        couldClick = true;
                    break;

                    case PACTIVE:
                    if (m_Active[choiceNum])
                        couldClick = true;
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

            int choiceType, choiceNum;
            if (ChoiceCheck(choiceType, choiceNum, p_input.endSide)) // on blinde PAS les qui existent/n'existent pas
            {
                rep = true;

                p_input.endType = choiceType;
                p_input.endNum = choiceNum;
                p_input.endX = mouse_x;
                p_input.endY = mouse_y;

            }
        }

        p_input.prevClick = false;
    }
    return rep;
}

///contient la boucle evennementielle
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
        //cout << mouse_x << " " << mouse_y << endl;

        draw_sprite(buffer, sprites.souris, mouse_x, mouse_y);
        blit(buffer, screen, 0, 0, 0, 0, XSCREEN, YSCREEN);

        if (mouse_b&1)
        {
            if (!p_input.prevClick)
            {
                if (mouse_x>=XENDTURN && mouse_x<=(XENDTURN+WENDTURN) && mouse_y>=YENDTURN && mouse_y<=(YENDTURN+HENDTURN))
                    endTurn = true;
            }
        }

        if (InputCheck(p_input))
        {
            if (p_input.startSide)
            {
                switch (p_input.startType)
                {
                    case PENERGY:
                    case PENJEU:
                    case PPIOCHE:
                    case PCIMETIERE:
                    case PPLAYER:

                break;

                    case PACTIVE:
//                    if (!m_Active[p_input.endNum]) //on blinde si la carte n'éxistait pas
//                        break;

                    if (!p_input.endSide) //si on lache le drag dans le camp adversaire
                    {
                        if (p_input.endType==PACTIVE)
                        {
                            if (opponent.GetActive(p_input.endNum))
                            {
                                this->m_Active[p_input.startNum]->SetAttack(p_input.endNum);
                            }
                        }
                        else if (p_input.endType==PPLAYER)
                        {
                            this->m_Active[p_input.startNum]->SetAttack(-1);//on lui dit d'attaquer le joueur ennemi
                        }
                    }
                    else// si on lache le drag dans le camp allié
                    {
                        if (p_input.endType==PCIMETIERE)
                        {
                            m_Cimetiere.push(m_Active[p_input.startNum]);
                            m_Active[p_input.startNum] = nullptr;
                        }
                    }
                break;

                    case PSPECIAL: //SI PSPECIAL OU PACTIVE!!!! (on a pas break; le PACTIVE)
                    if (!m_Special[p_input.endNum]) //on blinde si la carte n'éxistait pas
                        break;
                    if (p_input.endSide)
                    {
                        if (p_input.endType==PCIMETIERE)
                        {
                            m_Cimetiere.push(m_Special[p_input.startNum]);
                            m_Special[p_input.startNum] = nullptr;
                        }
                    }

                break;

                    case PMAIN: //drag depuis la main
                    if (p_input.endSide)
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

                            case PENJEU:
                            case PPIOCHE:
                            case PPLAYER:
                            case PMAIN:

                        break;
                        }
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

void Player::Draw(BITMAP *dest, bool turn, const Sprites& sprites, const PlayerInput& p_input)
{
    int col = 0;
    BITMAP *rep = create_bitmap(dest->w, dest->h);
    rectfill(rep, 0, 0, dest->w, dest->h, BLANC);

    rect(rep, XENERGY, YENERGY, XENERGY+CARDWIDTH, YENERGY+CARDHEIGHT, NOIR);
    if (!m_Energie.empty())
        rectfill(rep, XENERGY, YENERGY, XENERGY+CARDWIDTH, YENERGY+CARDHEIGHT, NOIR);

    for (int i=0;i<MAXACTIVE;i++)
    {
        rect(rep, i*(CARDWIDTH+MARGIN) + XACTIVE, YACTIVE, i*(CARDWIDTH+MARGIN) + XACTIVE+CARDWIDTH, YACTIVE+CARDHEIGHT, ROUGE);
        if (m_Active[i])
        {
            rectfill(rep, i*(CARDWIDTH+MARGIN) + XACTIVE, YACTIVE, i*(CARDWIDTH+MARGIN) + XACTIVE+CARDWIDTH, YACTIVE+CARDHEIGHT, ROUGE);
            textprintf_ex(rep, font, i*(CARDWIDTH+MARGIN) + XACTIVE, YACTIVE + MARGIN, NOIR, -1, " HP: %d", m_Active[i]->GetHP());
            textprintf_ex(rep, font, i*(CARDWIDTH+MARGIN) + XACTIVE, YACTIVE + 2*MARGIN, NOIR, -1, " AD: %d", m_Active[i]->GetAD());
        }
    }

    for (int i=0;i<MAXSPECIAL;i++)
    {
        rect(rep, i*(CARDWIDTH+MARGIN) + XSPECIAL, YSPECIAL, i*(CARDWIDTH+MARGIN) + XSPECIAL+CARDWIDTH, YSPECIAL+CARDHEIGHT, BLEU);
        if (m_Special[i])
            rectfill(rep, i*(CARDWIDTH+MARGIN) + XSPECIAL, YSPECIAL, i*(CARDWIDTH+MARGIN) + XSPECIAL+CARDWIDTH, YSPECIAL+CARDHEIGHT, BLEU);
    }

    rect(rep, XENJEU, YENJEU, XENJEU+CARDWIDTH, YENJEU+CARDHEIGHT, VERT);
    if (m_Enjeu)
        rectfill(rep, XENJEU, YENJEU, XENJEU+CARDWIDTH, YENJEU+CARDHEIGHT, VERT);

    rect(rep, XPIOCHE, YPIOCHE, XPIOCHE+CARDWIDTH, YPIOCHE+CARDHEIGHT, MAG);
    if (!m_Deck.empty())
        rectfill(rep, XPIOCHE, YPIOCHE, XPIOCHE+CARDWIDTH, YPIOCHE+CARDHEIGHT, MAG);

    rect(rep, XCIMETIERE, YCIMETIERE, XCIMETIERE+CARDWIDTH, YCIMETIERE+CARDHEIGHT, COL_SAND);
    if (!m_Cimetiere.empty())
        rectfill(rep, XCIMETIERE, YCIMETIERE, XCIMETIERE+CARDWIDTH, YCIMETIERE+CARDHEIGHT, COL_SAND);

    rectfill(rep, XPLAYER, YPLAYER, XPLAYER+WPLAYER-1, YPLAYER+HPLAYER-1, (p_input.whoTurn^turn)?COL_P1_FOND:COL_P2_FOND);
    draw_sprite(rep, sprites.buttonPlayer, XPLAYER, YPLAYER);

    textprintf_ex(rep, font, XPLAYER, YPLAYER + HPLAYER + MARGIN, NOIR, -1, "HP: %d/%d", m_HP, m_MaxHP);

    if (turn)
    {
        for (unsigned int i = 0;i<m_Main.size();i++) //m_Main est un vecteur (données contingues en mémoire)
        {
            switch (m_Main.at(i)->GetCardType())
            {
                case ENERGIE:
                col = NOIR;
            break;

                case CREATURE:
                col = ROUGE;
            break;

                case SPECIAL:
                col = BLEU;
            break;
            }

            rect(rep, i*(CARDWIDTH+MARGIN) + XMAIN, YMAIN, i*(CARDWIDTH+MARGIN) + XMAIN+CARDWIDTH, YMAIN+CARDHEIGHT, COL_MOUNTAIN);

            rectfill(rep, i*(CARDWIDTH+MARGIN) + XMAIN + 1, YMAIN +1, i*(CARDWIDTH+MARGIN) + XMAIN+CARDWIDTH - 1, YMAIN+CARDHEIGHT - 1, col);
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

void Player::TakeDamage(int quant)
{
    m_HP -= quant;

    if (m_HP<0)
        m_HP = 0;
}

void Player::ResetHP()
{
    m_HP = m_MaxHP;
}


