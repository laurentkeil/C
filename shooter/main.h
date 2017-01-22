void pause();
void event();
Uint32 bougerTank1(Uint32 intervalle, void *parametre);
Uint32 feu(Uint32 intervalle, void *parametre);

#define TAILLE_ECRAN_L 640
#define TAILLE_ECRAN_H 480


SDL_Rect posBalle;
int droite = true; //var booleenne globale
int balleLancee[3];
