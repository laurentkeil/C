#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "main.h"

int main(int argc, char *argv[])
{
    //premierEcran();
    //images();
    event();
    return EXIT_SUCCESS;
}

void event(){

    SDL_Surface *ecran = NULL, *zozor = NULL, *zozor2 = NULL, *zozor3 = NULL;
    SDL_Rect positionZozor, positionZozor2, positionZozor3;
    SDL_Event event; // Cette variable servira plus tard à gérer les événements
    SDL_Event eventCourant;
    SDL_TimerID timer; /* Variable pour stocker le numéro du timer */
    int continuer = 1;
    int tempsPrecedent = 0, tempsActuel = 0;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL");
        exit(EXIT_FAILURE);
    }
    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
    if (ecran == NULL) // Si l'ouverture a échoué, on le note et on arrête
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_WM_SetCaption("Gestion des evenemvfcents en SDL", NULL);


    /* Chargement de Zozor */
    zozor = SDL_LoadBMP("img/zozor.bmp");
    SDL_SetColorKey(zozor, SDL_SRCCOLORKEY, SDL_MapRGB(zozor->format, 0, 0, 255));

    /* Chargement de Zozor 2*/
    zozor2 = SDL_LoadBMP("img/zozor.bmp");
    SDL_SetColorKey(zozor2, SDL_SRCCOLORKEY, SDL_MapRGB(zozor2->format, 0, 0, 255));

    /* Chargement de Zozor 3*/
    zozor3 = SDL_LoadBMP("img/zozor.bmp");
    SDL_SetColorKey(zozor3, SDL_SRCCOLORKEY, SDL_MapRGB(zozor3->format, 0, 0, 255));

    /* On centre Zozor à l'écran */
    positionZozor.x = ecran->w / 2 - zozor->w / 2;
    positionZozor.y = ecran->h / 2 - zozor->h / 2;

    positionZozor2.x = 0;
    positionZozor2.y = 0;

    positionZozor3.x = 0;
    positionZozor3.y = 0;


    SDL_EnableKeyRepeat(10, 10); /* Activation de la répétition des touches */

    int stop = false, slow = false, fast = false;
    int vitesse = 10;

    /**
        Boucle d'event
    */
    while (continuer) {
        //SDL_WaitEvent(&eventCourant); /* Récupération de l'événement dans event */
        while(SDL_PollEvent(&event)){ /* On utilise PollEvent et non WaitEvent pour ne pas bloquer le programme */
            /**timer*/
            timer = SDL_AddTimer(100, bougerZozor, &positionZozor2); /* Démarrage du timer */

            switch(event.type) /* Test du type d'événement */
            {
                case SDL_QUIT: /* Si c'est un événement de type "Quitter" */
                    continuer = 0;
                    break;

                case SDL_VIDEORESIZE:
                    positionZozor.x = event.resize.w / 2 - zozor->w / 2;
                    positionZozor.y = event.resize.h / 2 - zozor->h / 2;
                    break;

                case SDL_KEYDOWN: /* Si appui sur une touche */
                     switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrête le programme */
                            continuer = 0;
                            break;
                        case SDLK_UP: // Flèche haut
                            positionZozor.y--;
                            fast = true;
                            break;
                        case SDLK_DOWN: // Flèche bas
                            positionZozor.y++;
                            slow = true;
                            break;
                        case SDLK_RIGHT: // Flèche droite
                            positionZozor.x++;
                            break;
                        case SDLK_LEFT: // Flèche gauche
                            positionZozor.x--;
                            break;
                        case SDLK_SPACE :
                            SDL_WarpMouse(ecran->w / 2, ecran->h / 2);
                            break;
                        case SDLK_KP1 :
                            SDL_Delay(2000);
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
                    if (event.button.button == SDL_BUTTON_RIGHT)
                        SDL_ShowCursor(SDL_DISABLE); //désactive la souris
                    else
                        SDL_ShowCursor(SDL_ENABLE); //active le curseur souris
                    break;

                case SDL_MOUSEMOTION:
                    positionZozor.x = event.motion.x;
                    positionZozor.y = event.motion.y;
                    break;
            }
        }

        /**
            Evenement qui se deroule toujours
        */
        tempsActuel = SDL_GetTicks();
        if (tempsActuel - tempsPrecedent > 30) {/* Si 30 ms se sont écoulées depuis le dernier tour de boucle */
            if(!stop) {
                if(positionZozor2.x >= ecran->w - zozor2->w){
                    positionZozor2.x = 0;
                } else if (positionZozor2.x <= 0){
                    positionZozor2.x = ecran->w - zozor2->w;
                }
                if(fast){
                    vitesse++;
                }
                fast = false;
                if(slow){
                    vitesse--;
                }
                slow = false;
                positionZozor2.x+=vitesse; /* On bouge Zozor 2*/
            }
            tempsPrecedent = tempsActuel; /* Le temps "actuel" devient le temps "precedent" pour nos futurs calculs */
        } else { /* Si ça fait moins de 30 ms depuis le dernier tour de boucle, on endort le programme le temps qu'il faut */
            SDL_Delay(30 - (tempsActuel - tempsPrecedent));
        }
        stop = false;

        /* On efface l'écran */
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        /* On place Zozor à sa nouvelle position */
        SDL_BlitSurface(zozor, NULL, ecran, &positionZozor);
        SDL_BlitSurface(zozor2, NULL, ecran, &positionZozor2);
        SDL_BlitSurface(zozor3, NULL, ecran, &positionZozor3);
        /* On met à jour l'affichage */
        SDL_Flip(ecran);
    }

    SDL_RemoveTimer(timer);
    SDL_FreeSurface(zozor);
    SDL_FreeSurface(zozor2);
    SDL_FreeSurface(zozor3);
    SDL_Quit();

}

/* Fonction de callback (sera appelée toutes les 30 ms) */
Uint32 bougerZozor(Uint32 intervalle, void *parametre){
    SDL_Rect* positionZozor2 = (SDL_Rect*)parametre; /* Conversion de void* en SDL_Rect* */
    if(positionZozor2->y >= 480){
        positionZozor2->y = 0;
    } else if (positionZozor2->y <= 0){
        positionZozor2->y = 480;
    }
    positionZozor2->y++;

    return intervalle;
}

void images(){

    SDL_Surface *ecran = NULL, *imageDeFond = NULL, *zozor = NULL;
    SDL_Rect positionFond, positionZozor;

    positionFond.x = 0;
    positionFond.y = 0;
    positionZozor.x = 500;
    positionZozor.y = 260;

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL");
        exit(EXIT_FAILURE);
    }

    /* Chargement de l'icône AVANT SDL_SetVideoMode */
    SDL_WM_SetIcon(SDL_LoadBMP("img/sdl_icone.bmp"), NULL);

    ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);
    if (ecran == NULL) // Si l'ouverture a échoué, on le note et on arrête
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_WM_SetCaption("Chargement d'images en SDL", NULL);

    /* Chargement d'une image Bitmap dans une surface */
    imageDeFond = SDL_LoadBMP("img/lac_en_montagne.bmp");
    /* On blitte par-dessus l'écran */
    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);

    /* Chargement et blittage de Zozor sur la scène */
    zozor = SDL_LoadBMP("img/zozor.bmp");
    /* On rend le bleu derrière Zozor transparent : */
    SDL_SetColorKey(zozor, SDL_SRCCOLORKEY, SDL_MapRGB(zozor->format, 0, 0, 255));
    /* Transparence Alpha moyenne (128) :
    SDL_SetAlpha(zozor, SDL_SRCALPHA, 128);*/
    SDL_BlitSurface(zozor, NULL, ecran, &positionZozor);

    SDL_Flip(ecran);
    pause();

    SDL_FreeSurface(imageDeFond); /* On libère la surface */
    SDL_Quit();

}

void premierEcran(){

    SDL_Surface *ecran = NULL, *rectangle = NULL;
    SDL_Rect position;

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL");
        exit(EXIT_FAILURE);
    }

    ecran = SDL_SetVideoMode(1280, 840, 32, SDL_HWSURFACE);
    if (ecran == NULL) // Si l'ouverture a échoué, on le note et on arrête
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    // Allocation de la surface
    rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, 220, 180, 32, 0, 0, 0, 0);
    SDL_WM_SetCaption("Ma super fenetre SDL !", NULL);

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 112));

    position.x = (1280 / 2) - (220 / 2);
    position.y = (840 / 2) - (180 / 2);
    // Remplissage de la surface avec du blanc
    SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    SDL_BlitSurface(rectangle, NULL, ecran, &position); // Collage de la surface sur l'écran

    SDL_Flip(ecran); // Mise à jour de l'écran

    pause();

    SDL_FreeSurface(rectangle); // Libération de la surface
    SDL_Quit();
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
