#include "Carte.h"

using namespace std;

Carte::Carte()
{
    //ctor
}

Carte::~Carte()
{
    //dtor
}

//les constantes utilisées dans cette fonction son dans defines.h, dans les valeurs graphiques

void Carte::Detail(BITMAP *fond, PlayerInput& p_input, const Sprites& sprites)
{
    BITMAP *buffer = create_bitmap(XSCREEN, YSCREEN);
    BITMAP *fenetre = create_bitmap(WFENETRE, HFENETRE);
    bool retours = false;

    rectfill(fenetre, 0,0, WFENETRE, HFENETRE, COL_UI_FOND); //fond de la fenetre

    draw_sprite(fenetre, GetCardFront(), 5, 5);

    //le bouton de retours
    rectfill(fenetre, XBRETOUR - XFENETRE, YBRETOUR - YFENETRE, XBRETOUR+WBRETOUR - XFENETRE, YBRETOUR+HBRETOUR - YFENETRE, COL_BRIDGE);

    //assemble la fenetre (drawsprite la carte, affiche en grand le nom et la description)
    textprintf_ex(fenetre, font, 60 + XTEXT, 50 + 1, BLANC, -1, "%s", GetModele().GetNom().c_str());    //nom

    vector<string>& description = GetModele().GetDescription();                                         //descirption
    for (int i=0;i<description.size();i++) //doing this as for an array cus we need the counter
    {
        textprintf_ex(fenetre, font, MARGIN, 2*MARGIN + CARDHEIGHT + 9*i, BLANC, -1, "%s", description[i].c_str());
    }

    //boucle evennementielle
    while (!retours)
    {
        blit(fond, buffer, 0, 0, 0, 0, XSCREEN, YSCREEN);
        blit(fenetre, buffer, 0, 0, XFENETRE, YFENETRE, WFENETRE, HFENETRE);

        if (mouse_b & 1)
        {
            if (!p_input.prevClick)
            {
                if (mouse_x>=XBRETOUR && mouse_x<(XBRETOUR+WBRETOUR) && mouse_y>=YBRETOUR && mouse_y<(YBRETOUR+HBRETOUR))
                {
                    retours = true;
                }
            }

            p_input.prevClick = true;
        }
        else
        {
            p_input.prevClick = false;
        }

        draw_sprite(buffer, sprites.souris, mouse_x, mouse_y);
        blit(buffer, screen,0,0, 0, 0, XSCREEN, YSCREEN);
    }

    destroy_bitmap(buffer);
    destroy_bitmap(fenetre);
}

