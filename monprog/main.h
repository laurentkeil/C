void Bases(); //prototype exo fonctions de base
void choixMenu(); //proto de la fonction choixMenu
void TPPlusMoins(); //proto TP 1
void decoupeMinutes(int* pointeurHeures, int* pointeurMinutes);
void afficheTableau(int *tableau, int taille);
void manipChar();
void structure();
void fichier();
void pointeur();
void allocDyn();
void saisieSecur();
void viderBuffer();
int lire(char *chaine, int longueur);
long lireLong();
char lireCaractere();
void TPPendu();


typedef struct Personne Personne; // alias
struct Personne // structure de données
{
    char nom[100];
    char prenom[100];
    char adresse[1000];

    int age;
    int garcon; // Booléen : 1 = garçon, 0 = fille
};

typedef struct Coordonnees Coordonnees; // alias
struct Coordonnees // structure de données
{
    int x;
    int y;
};

typedef enum Volume Volume;
enum Volume
{
    FAIBLE = 10, MOYEN = 50, FORT = 100
};

typedef struct Element Element;
struct Element
{
    int nombre;
    Element *suivant;
};

typedef struct Liste Liste;
struct Liste
{
    Element *premier;
};


void listes();
Liste *initialisation();
void insertion(Liste *liste, int nvNombre);
void suppression(Liste *liste);
void afficherListe(Liste *liste);

void initialiserCoordonnees(Coordonnees* point);
