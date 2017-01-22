#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "main.h"

int main(int argc, char *argv[])
{
    event();
    return EXIT_SUCCESS;
}

void event(){

    SDL_Surface *imageDeFond = NULL, *ecran = NULL, *tankJoueur = NULL, *tankEnnemi1 = NULL,
    *tankMort = NULL, *viseur = NULL, *balle = NULL;
    SDL_Rect positionFond, posTankJ, posTank1, posViseur, directionBalle;
    SDL_Event event; // Cette variable servira plus tard à gérer les événements
    SDL_TimerID timer; /* Variable pour stocker le numéro du timer */
    int continuer = 1;
    int tempsPrecedent = 0, tempsActuel = 0;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL");
        exit(EXIT_FAILURE);
    }
    ecran = SDL_SetVideoMode(TAILLE_ECRAN_L, TAILLE_ECRAN_H, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (ecran == NULL) // Si l'ouverture a échoué, on le note et on arrête
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_WM_SetCaption("Jeu de shoot 2D", NULL);


    /* Chargement des images */

    positionFond.x = 0;
    positionFond.y = 0;
    imageDeFond = SDL_LoadBMP("img/fond.bmp");

    viseur = SDL_LoadBMP("img/viseur.bmp");
    SDL_SetColorKey(viseur, SDL_SRCCOLORKEY, SDL_MapRGB(viseur->format, 255, 255, 255));

    tankJoueur = SDL_LoadBMP("img/tankJoueur.bmp");
    SDL_SetColorKey(tankJoueur, SDL_SRCCOLORKEY, SDL_MapRGB(tankJoueur->format, 255, 255, 255));

    tankEnnemi1 = SDL_LoadBMP("img/tankEnnemi1.bmp");
    SDL_SetColorKey(tankEnnemi1, SDL_SRCCOLORKEY, SDL_MapRGB(tankEnnemi1->format, 255, 255, 255));


    posTankJ.x = ecran->w / 2 - tankJoueur->w;
    posTankJ.y = ecran->h - tankJoueur->h;

    posTank1.x = 200;
    posTank1.y = 200;

    posViseur.x = ecran->w / 2 - viseur->w / 2;
    posViseur.y = ecran->h / 2 - viseur->h / 2;

    SDL_ShowCursor(SDL_DISABLE); //désactive la souris

    SDL_EnableKeyRepeat(20, 20); /* Activation de la répétition des touches */

    int stop = false;
    /**timer*/
    timer = SDL_AddTimer(30, bougerTank1, &posTank1); /* Démarrage du timer */
    balleLancee[0] = 0;
    balleLancee[1] = 0;
    balleLancee[2] = 0;

    /**
        Boucle d'event
    */
    while (continuer) {
        while(SDL_PollEvent(&event)){ /* On utilise PollEvent et non WaitEvent pour ne pas bloquer le programme */

            switch(event.type) /* Test du type d'événement */
            {
                case SDL_QUIT: /* Si c'est un événement de type "Quitter" */
                    continuer = 0;
                    break;

                case SDL_KEYDOWN: /* Si appui sur une touche */
                     switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrête le programme */
                            continuer = 0;
                            break;
                        case SDLK_UP: // Flèche haut
                            posTankJ.y--;
                            break;
                        case SDLK_DOWN: // Flèche bas
                            posTankJ.y++;
                            break;
                        case SDLK_RIGHT: // Flèche droite
                            posTankJ.x++;
                            break;
                        case SDLK_LEFT: // Flèche gauche
                            posTankJ.x--;
                            break;
                        case SDLK_SPACE :
                            SDL_WarpMouse(ecran->w / 2, ecran->h / 2);
                            break;
                        case SDLK_p :
                            if(stop == false) {
                                stop = true;
                            } else {
                                stop = false;
                            }
                            break;
                     }
                    break;

                case SDL_MOUSEBUTTONUP:
                    if (event.button.button == SDL_BUTTON_LEFT){
                        if(!balleLancee[0] || !balleLancee[1] || !balleLancee[2]) {
                            balle = SDL_LoadBMP("img/balle.bmp");
                            SDL_SetColorKey(balle, SDL_SRCCOLORKEY, SDL_MapRGB(balle->format, 255, 255, 255));
                            posBalle.x = posTankJ.x;
                            posBalle.y = posTankJ.y - tankJoueur->h;
                            if(!balleLancee[0]) {
                                balleLancee[0] = 1;
                            } else if (!balleLancee[1]) {
                                balleLancee[1] = 1;
                            } else {
                                balleLancee[2] = 1;
                            }
                            directionBalle.x = posViseur.x - posBalle.x;
                            directionBalle.y = posViseur.y - posBalle.y;
                            timer = SDL_AddTimer(50, feu, &directionBalle); /* Démarrage du timer */
                        }
                    }
                    break;

                case SDL_MOUSEMOTION:
                    posViseur.x = event.motion.x - (viseur->w / 2);
                    posViseur.y = event.motion.y - (viseur->h / 2);
                    break;
            }

        }

        /* On efface l'écran */
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        /* On place les tank à leur nouvelle position */

        SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
        SDL_BlitSurface(tankJoueur, NULL, ecran, &posTankJ);
        if (posBalle.x >= posTank1.x - 20 && posBalle.x <= posTank1.x + 20 && posBalle.y >= posTank1.y - 20 && posBalle.y <= posTank1.y + 20) {
                tankMort = SDL_LoadBMP("img/tankMort.bmp");
                SDL_SetColorKey(tankMort, SDL_SRCCOLORKEY, SDL_MapRGB(tankMort->format, 255, 255, 255));
                SDL_BlitSurface(tankMort, NULL, ecran, &posTank1);
                SDL_Flip(ecran);
                SDL_Delay(1000);
                balleLancee[0] = 1;
        } else {
            SDL_BlitSurface(tankEnnemi1, NULL, ecran, &posTank1);
        }
        SDL_BlitSurface(viseur, NULL, ecran, &posViseur);
        SDL_BlitSurface(balle, NULL, ecran, &posBalle);
        /* On met à jour l'affichage */
        SDL_Flip(ecran);
    }

    SDL_RemoveTimer(timer);
    SDL_FreeSurface(imageDeFond);
    SDL_FreeSurface(balle);
    SDL_FreeSurface(tankJoueur);
    SDL_FreeSurface(tankEnnemi1);
    SDL_FreeSurface(viseur);
    SDL_Quit();

}

/* Fonction de callback (sera appelée toutes les 30 ms) */
Uint32 bougerTank1(Uint32 intervalle, void *parametre){
    SDL_Rect* posTank1 = (SDL_Rect*)parametre; /* Conversion de void* en SDL_Rect* */
    if(posTank1->x >= TAILLE_ECRAN_L - 40){
        droite = false;
    } else if (posTank1->x <= 1) {
        droite = true;
    }
    if (droite) {
        posTank1->x+=5;
    } else {
        posTank1->x-=7;
    }

    return intervalle;
}

/* Fonction de callback (sera appelée toutes les 100 ms) */
Uint32 feu(Uint32 intervalle, void *parametre){
    SDL_Rect* directionBalle = (SDL_Rect*)parametre; /* Conversion de void* en SDL_Rect* */

    posBalle.x = posBalle.x + (directionBalle->x / 30);
    posBalle.y = posBalle.y + (directionBalle->y / 30);

    return intervalle;
}


void pause() {
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}
