#ifndef DEFINES_H_INCLUDED
#define DEFINES_H_INCLUDED

///LINKERS/INCLUDES
#include <allegro.h>
#include <exception>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <map>


///Gameplay/balance
#define POWFREEZE 1 //nombre de tours que le pow freeze
#define SHROOMHEAL 2
#define SHROOMBUFF 2
#define COINHEAL 3

#define STARTENERGY 15


///MAGIC NUMBERS AND ENUMS
// le nombre max de cartes dans les differents endroits du plateau
#define MAXHAND 5
#define MAXACTIVE 5
#define MAXSPECIAL 1
#define MAXMOVES 2 //le nombre d'attaques max par créature

#define DECKSIZE 11
#define CSTARTSIZE 16

#define NBDOMAINE 4

enum CardType{
    ENERGIE = 0,
    CREATURE = 1,
    SPECIAL = 2
};

// enum pour les endroits sur le plateau
#define PENERGY 1
#define PACTIVE 2
#define PSPECIAL 3
#define PENJEU 4
#define PPIOCHE 5
#define PCIMETIERE 6
#define PMAIN 7
#define PPLAYER 8

// enum pour les endroits sur une carte
#define CNOTHING (-1)   //parentheses on sait jamais
#define CACTION 0
#define CATTACK1 0
#define CATTACK2 1
#define CDESCRI 2

// enum pour les modèles de cartes speciales
#define GREENSHROOM 8
#define REDSHROOM 1
#define FLOWER 4
#define COIN 5
#define STAR 6
#define POW 7

struct PlayerInput{
    bool whoTurn; //n'a rien à voir avec l'input, main un bon endroit pour la mettre

    bool prevClick;
    bool dragging;

    //au début du clic
    int startSide;      //vaut 0 si c'est le coté haut (ennemi) et 1 si c'est en bas (le joueur en question)
    int startX, startY;
    int startType;
    int startNum;       // que si clic sur active, special ou main
    int startCWhere;    // que si clic sur une carte de face

    //à la fin du clic
    int endSide; //vaut 0 si c'est le coté haut (ennemi) et 1 si c'est en bas (le joueur en question)
    int endX, endY;
    int endType;
    int endNum;        // que si clic sur active, special ou main
    int endCWhere;     // que si clic sur une carte de face
};

struct Domaines{
    int value[NBDOMAINE]; //la quantité d'énergie disponible pour chaque domaine
};


///GRAPHICS DIMENTIONS AND COORDINATES
#define XSCREEN (7*PDIST + MARGIN)
#define YSCREEN 1000

#define XPLAYERSIDE 0
#define YPLAYERSIDE (YSCREEN/2)
#define WPLAYERSIDE XSCREEN
#define HPLAYERSIDE (YSCREEN/2)

// les dimensions
#define CARDWIDTH 84
#define CARDHEIGHT 120
#define PDIST (CARDWIDTH + MARGIN)

#define MARGIN 10
#define XENERGY MARGIN
#define YENERGY MARGIN
#define XACTIVE (PDIST + MARGIN)
#define YACTIVE MARGIN
#define XSPECIAL (6*PDIST + MARGIN)
#define YSPECIAL MARGIN
#define XENJEU MARGIN
#define YENJEU (CARDHEIGHT + 2*MARGIN)
#define XPIOCHE ((PDIST*7 + MARGIN)/2 - CARDWIDTH/2)
#define YPIOCHE YENJEU
#define XCIMETIERE XSPECIAL
#define YCIMETIERE YENJEU
#define XMAIN XACTIVE
#define YMAIN (2*CARDHEIGHT + 3*MARGIN)

#define XPLAYER (PDIST + 45)
#define YPLAYER (YENJEU + MARGIN)
#define WPLAYER WENDTURN
#define HPLAYER HENDTURN

#define XENDTURN (XSCREEN/2 - WENDTURN/2)
#define YENDTURN (YSCREEN/2 - HENDTURN - MARGIN)
#define WENDTURN 50
#define HENDTURN 30


//positions des differents trucs sur une carte
#define XACTION 4
#define YACTION 60
#define WACTION 77
#define HACTION 52
#define HATTACK (HACTION/2)

#define XDESCRI 4 //L'IMAGE
#define YDESCRI 12
#define WDESCRI 76
#define HDESCRI 48

//pour la fenetre de déscription d'une carte, dans Carte.cpp
#define XFENETRE 105
#define YFENETRE 140
#define WFENETRE 460
#define HFENETRE 620

#define XBRETOUR 390
#define YBRETOUR 650
#define WBRETOUR 150
#define HBRETOUR 100


///COLORS
// des couleurs
#define BLANC makecol(255,255,255)
#define NOIR makecol(0,0,0)
#define ROUGE makecol(255,0,0)
#define BLEU makecol(0,0,255)
#define VERT makecol(0,255,0)
#define MAG makecol (255,0,255)         //magenta

#define COL_P1_ACC makecol(199,0,0)     //plus rouge
#define COL_P1_FOND makecol(203,106,106)//plus rose/beige?
#define COL_P2_ACC makecol(0,64,64)     //plus bleu cool foncé
#define COL_P2_FOND makecol(0,114,144)  //plus bleu cool clair

/// ces couleurs sont celles qu'on utilisait dans le projet ECEcraft. Quand besoin on peut les réutiliser
#define COL_UI_FOND makecol(1,87,155)
#define COL_UI_ACC makecol(79,195,247)  //un joli bleu clair (je crois)
#define COL_SAND makecol(194,132,80)
#define COL_BRIDGE makecol(122,61,0)
//#define COL_GRASS makecol(110,130,51)
//#define COL_WATER makecol(48,140,187)
#define COL_MOUNTAIN makecol(83,83,83)
#define COL_ROCK makecol(128,128,128)
//#define COL_TREEL makecol(78,145,101)   //arbre feuillu
//#define COL_TREEP makecol(58,99,58)     //conifere
//#define COL_CONSTR COL_UI_ACC           //couleur d'un batiment
//#define COL_ENEMY ROUGE
//#define COL_PEASANT makecol(34,93,255)
//#define COL_SOLDIER BLEU


///FILE NAMES

#ifdef _WINDOWS

#define FSOURIS "Res\\mario_mouse_cursor.bmp"   //32x30
#define FENDTURN "Res\\End_Turn_Button.bmp"     //50x30
#define FPLAYER "Res\\Player_Button.bmp"        //50x30
#define FCARDB "Res\\Card_Back.bmp"             //70x100
#define FFOND "Res\\Fond.bmp"                   //668x1000

#define FMODELES "Saves\\Modeles.txt"           //contient les infos des cartes
#define FPINFO "Saves\\P_info.txt"              //contient l'info des joueurs (les cartes, hp etc)

#else

#define FSOURIS "Res/mario_mouse_cursor.bmp"    //32x30
#define FENDTURN "Res/End_Turn_Button.bmp"      //50x30
#define FPLAYER "Res/Player_Button.bmp"         //50x30
#define FCARDB "Res/Card_Back.bmp"              //70x100
#define FCARDT "Res/Card_Template.bmp"          //70x100
#define FFOND "Res/Fond.bmp"                    //668x1000

#define FMODELES "Saves/Modeles.txt"            //contient les infos des cartes
#define FPINFO "Saves/P_info.txt"               //contient l'info des joueurs (les cartes, hp etc)

#endif // _WINDOWS


#define PRINT(x) {cerr<<endl<<x<<endl;}

// renvoie une erreur de chargement
#define ERR_CHARG(x) {if(!x){cerr<<"probleme de chargement: " #x " \n";throw 1;}}

struct Sprites{
    BITMAP *souris;
    BITMAP *buttonEndTurn;
    BITMAP *buttonPlayer;
    BITMAP *cardBack;
    BITMAP *cardTemplate;
    BITMAP *fond;
};

#endif //DEFINES_H_INCLUDED

