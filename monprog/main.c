#include <stdio.h>
#include <stdlib.h>
#include <math.h> //fonctions math
#include <string.h> //chaine de char
#include "main.h"

#define TAILLE_MAX 100
#define NBCOUPSMAX 10

int main(int argc, char *argv[]) {

    //Bases(); //appel exo fonctions de base + saisie de texte secu
    //choixMenu(); //appel de la fonction choixMenu
    //TPPlusMoins(); //appel TP 1
    //pointeur();
    //manipChar();
    //structure();
    //fichier();
    //allocDyn();
    //saisieSecur();
    //TPPendu();
    //listes();

    return 0;
}

void listes(){
    Liste *maListe = initialisation();

    insertion(maListe, 4);
    insertion(maListe, 8);
    insertion(maListe, 15);
    suppression(maListe);

    afficherListe(maListe);
}

Liste *initialisation()
{
    Liste *liste = malloc(sizeof(*liste));
    Element *element = malloc(sizeof(*element));

    if (liste == NULL || element == NULL)
    {
        exit(EXIT_FAILURE);
    }

    element->nombre = 0;
    element->suivant = NULL;
    liste->premier = element;

    return liste;
}

void insertion(Liste *liste, int nvNombre)
{
    /* Création du nouvel élément */
    Element *nouveau = malloc(sizeof(*nouveau));
    if (liste == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
    nouveau->nombre = nvNombre;

    /* Insertion de l'élément au début de la liste */
    nouveau->suivant = liste->premier;
    liste->premier = nouveau;
}

void suppression(Liste *liste)
{
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    if (liste->premier != NULL)
    {
        Element *aSupprimer = liste->premier;
        liste->premier = liste->premier->suivant;
        free(aSupprimer);
    }
}

void afficherListe(Liste *liste)
{
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Element *actuel = liste->premier;

    while (actuel != NULL)
    {
        printf("%d -> ", actuel->nombre);
        actuel = actuel->suivant;
    }
    printf("NULL\n");
}

void TPPendu(){

    FILE *fichier = NULL;

    int nbrMots = 0, indiceMot = 0;

    char motSecret[TAILLE_MAX] = "";
    fichier = fopen("dictionnaire.txt", "r");//lecture
    if (fichier != NULL) {
        while (fgets(motSecret, TAILLE_MAX, fichier) != NULL) { // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
            nbrMots++;
        }
    }

    const int MAX = nbrMots, MIN = 1;
    // Génération du nombre aléatoire
    srand(time(NULL));
    indiceMot = (rand() % (MAX - MIN + 1)) + MIN;

    rewind(fichier);
    if (fichier != NULL) {
        int i=1;
        while (i!=indiceMot) { // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
            fgets(motSecret, TAILLE_MAX, fichier);
            i++;
        }
        fgets(motSecret, TAILLE_MAX, fichier);
    }
    fclose(fichier);

    /*Bug avec 1 carac en + ...*/
    char motJoueur[TAILLE_MAX] = "";
    int i;
    for(i=0 ; i<strlen(motSecret) ; i++) {
        motJoueur[i] = '*';
    }
    char maLettre;
    int nbCoups = 0;

    printf("Bienvenue dans le jeu du Pendu !");

    for(nbCoups = 0 ; (nbCoups < NBCOUPSMAX) && (strcmp(motJoueur, motSecret) != 0) ; nbCoups++) {
        printf("\n\nIl vous reste %d coups a jouer", NBCOUPSMAX - nbCoups);
        printf("\nQuel est le mot secret ? %s", motJoueur);
        printf("\nProposez une lettre : ");
        maLettre = lireCaractere();

        int i=0;
        while (i<=strlen(motSecret)-1) {
            if(maLettre == motSecret[i]){
                motJoueur[i] = maLettre;
            }
            i++;
        }
    }

    if (strcmp(motJoueur, motSecret) == 0) {
        printf("\nBravo, vous avez trouve le mot : %s\n", motSecret);
    } else {
        printf("\nVous avez ete pendu ! Le mot etait : %s\n", motSecret);
    }

}

char lireCaractere() // fonction pour lire un caractere dans le pendu
{
    char caractere = 0;

    caractere = getchar(); // On lit le premier caractère
    caractere = toupper(caractere); // On met la lettre en majuscule si elle ne l'est pas déjà

    // On lit les autres caractères mémorisés un à un jusqu'au \n (pour les effacer)
    while (getchar() != '\n') ;

    return caractere; // On retourne le premier caractère qu'on a lu
}

void saisieSecur() {

    /*alternative au scanf : fgets (securise)*/
    char nom[10];

    printf("Quel est votre nom ? ");
    lire(nom, 10);
    printf("Ah ! Vous vous appelez donc %s !\n\n", nom);

    long age2 = 0;

    printf("Quel est votre age ? ");
    age2 = lireLong(); //conversion en long
    printf("Ah ! Vous avez donc %d ans !\n", age2);

}

void allocDyn() {
int nombreDAmis = 0, i = 0;
    int* ageAmis = NULL; // Ce pointeur va servir de tableau après l'appel du malloc

    // On demande le nombre d'amis à l'utilisateur
    printf("Combien d'amis avez-vous ? ");
    scanf("%d", &nombreDAmis);

    if (nombreDAmis > 0) // Il faut qu'il ait au moins un ami (je le plains un peu sinon :p)
    {
        ageAmis = malloc(nombreDAmis * sizeof(int)); // On alloue de la mémoire pour le tableau
        /*alloc dyn*/
        if (ageAmis == NULL) // On vérifie si l'allocation a marché ou non
        {
            exit(0); // On arrête tout
        }

        // On demande l'âge des amis un à un
        for (i = 0 ; i < nombreDAmis ; i++)
        {
            printf("Quel age a l'ami numero %d ? ", i + 1);
            scanf("%d", &ageAmis[i]);
        }

        // On affiche les âges stockés un à un
        printf("\n\nVos amis ont les ages suivants :\n");
        for (i = 0 ; i < nombreDAmis ; i++)
        {
            printf("%d ans\n", ageAmis[i]);
        }

        // On libère la mémoire allouée avec malloc, on n'en a plus besoin
        free(ageAmis);
    }
}

void fichier() {
    FILE* fichier = NULL;
    int age;
    int score[3] = {0};

    fichier = fopen("test.txt", "w");//ecriture

    if (fichier != NULL) {
        fputc('A', fichier); // Écriture du caractère A
        fputs("\nSalut les Zér0s\nComment allez-vous ?", fichier);

        // On demande l'âge
        printf("Quel age avez-vous ? ");
        scanf("%d", &age);

        // On l'écrit dans le fichier
        fprintf(fichier, "\nLe Monsieur qui utilise le programme, il a %d ans", age);
        fprintf(fichier, "\n%d %d %d", 1, 2, 3);

        fclose(fichier);
    } else {
        // On affiche un message d'erreur
        printf("Impossible d'ouvrir le fichier test.txt");
    }


    char chaine[TAILLE_MAX] = "";

    fichier = fopen("test.txt", "r");//lecture

    if (fichier != NULL)
    {
        while (fgets(chaine, TAILLE_MAX, fichier) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
        {
            printf("%s", chaine); // On affiche la chaîne qu'on vient de lire
        }

        printf("\nposition : %d", ftell(fichier));
        fseek(fichier, -5, SEEK_CUR); //positionne le curseur 8 avant
        printf("\nposition : %d", ftell(fichier));

        fscanf(fichier, "%d %d %d", &score[0], &score[1], &score[2]);
        printf("\nLes meilleurs scores sont : %d, %d et %d", score[0], score[1], score[2]);

        fclose(fichier);
    }

    remove("test.txt");
}

void structure() {

    Personne utilisateur;

    printf("Quel est votre nom ? ");
    scanf("%s", utilisateur.nom);
    printf("Votre prenom ? ");
    scanf("%s", utilisateur.prenom);

    printf("Vous vous appelez %s %s", utilisateur.prenom, utilisateur.nom);

    Coordonnees monPoint;

    initialiserCoordonnees(&monPoint);

    printf("\nVoici vos coordonnées : %d %d", monPoint.x, monPoint.y);

    Volume musique = MOYEN;
}

void initialiserCoordonnees(Coordonnees* point)
{
    point->x = 10;
    point->y = 0;
}

void manipChar(){

    char prenom[TAILLE_MAX], copie[TAILLE_MAX];
    printf("Comment t'appelles-tu petit Zero ? ");
    scanf("%s", prenom);
    sprintf(prenom, "%s keil", prenom);
    printf("Salut %s, je suis heureux de te rencontrer !\n", prenom);

    // On affiche la longueur de la chaîne
    printf("La chaine fait %d caracteres de long", strlen(prenom));
    strcpy(copie, prenom);
    printf("\ncopie : %s et original : %s", copie, prenom);
    strcat(copie, " bonjour");
    printf("\n%s",copie);
    if(!strcmp(copie, prenom)) printf("\n identique");
    printf("\nfin de la chaine a partir de u : %s", strchr(prenom, 'u'));
}

void afficheTableau(int tableau[], int taille){
    int i;
    for(i=0 ; i<taille ; i++){
        printf("\n%d", tableau[i]);
    }
}

void pointeur(){
    int heures = 0, minutes = 0;

    printf("\nCombien de minutes ? ");
    scanf("%d", &minutes);

    // APPEL DE FCT (pointeurs) On envoie l'adresse de heures et minutes
    decoupeMinutes(&heures, &minutes);

    // Cette fois, les valeurs ont été modifiées !
    printf("%d heures et %d minutes", heures, minutes);

    int tableau[4] = {0}; // Toutes les cases du tableau seront initialisées à 0
    tableau[2] = heures;
    tableau[3] = minutes;

    // On affiche le contenu du tableau
    afficheTableau(tableau, 4);
}

void decoupeMinutes(int* pointeurHeures, int* pointeurMinutes) {
    *pointeurHeures = *pointeurMinutes / 60;
    *pointeurMinutes = *pointeurMinutes % 60;
}

 void TPPlusMoins () {

    int nombreMystere = 0, nombreEntre = 0;
    const int MAX = 100, MIN = 1;

    // Génération du nombre aléatoire

    srand(time(NULL));
    nombreMystere = (rand() % (MAX - MIN + 1)) + MIN;

    /* La boucle du programme. Elle se répète tant que l'utilisateur n'a pas trouvé le nombre mystère */

    do
    {
        // On demande le nombre
        printf("Quel est le nombre ? ");
        scanf("%d", &nombreEntre);

        // On compare le nombre entré avec le nombre mystère

        if (nombreMystere > nombreEntre)
            printf("C'est plus !\n\n");
        else if (nombreMystere < nombreEntre)
            printf("C'est moins !\n\n");
        else
            printf ("Bravo, vous avez trouve le nombre mystere !!!\n\n");
    } while (nombreEntre != nombreMystere);

 }

void choixMenu(){

      int choixMenu;

      printf("\n=== Menu ===\n\n");
      printf("1. Royal Cheese\n");
      printf("2. Mc Deluxe\n");
      printf("3. Mc Bacon\n");
      printf("4. Big Mac\n");
      printf("\nVotre choix ? ");
      scanf("%d", &choixMenu);

      printf("\n");

      switch (choixMenu)
      {
        case 1:
           printf("Vous avez choisi le Royal Cheese. Bon choix !");
           break;
        case 2:
           printf("Vous avez choisi le Mc Deluxe. Berk, trop de sauce...");
           break;
        case 3:
           printf("Vous avez choisi le Mc Bacon. Bon, ca passe encore ca ;o)");
           break;
        case 4:
           printf("Vous avez choisi le Big Mac. Vous devez avoir tres faim !");
           break;
        default:
           printf("Vous n'avez pas rentre un nombre correct. Vous ne mangerez rien du tout !");
           break;
      }

      printf("\n\n");

}

void Bases(){

    int nombreDeVies = 5; // Au départ, le joueur a 5 vies

    printf("Vous avez %d vies\n", nombreDeVies);
    printf("**** B A M ****\n"); // Là il se prend un grand coup sur la tête
    nombreDeVies--; // Il vient de perdre une vie !
    printf("Ah desole, il ne vous reste plus que %d vies maintenant !\n\n", nombreDeVies);

    int age = 0; // On initialise la variable à 0

    printf("Quel age avez-vous ? ");
    scanf("%d", &age); // On demande d'entrer l'âge avec scanf
    printf("Ah ! Vous avez donc %d ans !\n\n", age);

    if (age >= 18) // Si l'âge est supérieur ou égal à 18
    {
      printf ("Vous etes majeur !");
    }
    else if ( age > 4 ) // Sinon, si l'âge est au moins supérieur à 4
    {
      printf ("Bon t'es pas trop jeune quand meme...");
    }
    else // Sinon...
    {
      printf ("Aga gaa aga gaaa"); // Langage bébé, vous pouvez pas comprendre
    }

    int resultat = 0, nombre1 = 0, nombre2 = 0;

    while (resultat != 40){

      printf("\n\n Le resultat des 2 nombres doit etre egal a 40");
      // On demande les nombres 1 et 2 à l'utilisateur :

      printf("\n\nEntrez le nombre 1 : ");
      scanf("%d", &nombre1);
      printf("Entrez le nombre 2 : ");
      scanf("%d", &nombre2);

      // On fait le calcul :

      resultat = nombre1 + nombre2;

      // Et on affiche l'addition à l'écran :

      printf ("%d + %d = %d", nombre1, nombre2, resultat);
    }

}

void viderBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

int lire(char *chaine, int longueur) {//fonction qui permet de lire une entrée de facon sécurisée.
    char *positionEntree = NULL;

    // On lit le texte saisi au clavier
    if (fgets(chaine, longueur, stdin) != NULL)  // Pas d'erreur de saisie ?
    {
        positionEntree = strchr(chaine, '\n'); // On recherche l'"Entrée"
        if (positionEntree != NULL) // Si on a trouvé le retour à la ligne
        {
            *positionEntree = '\0'; // On remplace ce caractère par \0
        }
        else
        {
            viderBuffer();
        }
        return 1; // On renvoie 1 si la fonction s'est déroulée sans erreur
    }
    else
    {
        viderBuffer();
        return 0; // On renvoie 0 s'il y a eu une erreur
    }
}

long lireLong()
{
    char nombreTexte[20] = {0}; // 100 cases devraient suffire

    if (lire(nombreTexte, 20))
    {
        // Si lecture du texte ok, convertir le nombre en long et le retourner
        return strtol(nombreTexte, NULL, 10);
    }
    else
    {
        // Si problème de lecture, renvoyer 0
        return 0;
    }
}

