
#include "main.h"

using namespace std;

int main()
{
    //bases();
    //fichier();
    //TPmotMyst();
    POO();


    return 0;
}

void POO() {
    Personnage goliath("Épée aiguisée", 20);
    //Création de 2 objets de type Personnage : david et goliath
    Personnage david(goliath); //constructeur de copie

    goliath.attaquer(david); //goliath attaque david
    david.boirePotionDeVie(20); //david récupère 20 de vie en buvant une potion
    goliath.attaquer(david); //goliath réattaque david
    david.attaquer(goliath); //david contre-attaque... c'est assez clair non ?
    goliath.changerArme("Double hache tranchante vénéneuse de la mort", 40);
    goliath.attaquer(david);

    //Temps mort ! Voyons voir la vie de chacun…
    cout << "David" << endl;
    david.afficherEtat();
    cout << endl << "Goliath" << endl;
    goliath.afficherEtat();
}

string melangerLettres(string mot) {
   string melange;
   int position(0);

   //Tant qu'on n'a pas extrait toutes les lettres du mot
   while (mot.size() != 0)
   {
      //On choisit un numéro de lettre au hasard dans le mot
      position = rand() % mot.size();
      //On ajoute la lettre dans le mot mélangé
      melange += mot[position];
      //On retire cette lettre du mot mystère
      //Pour ne pas la prendre une deuxième fois
        mot.erase(position, 1);
    }

   //On renvoie le mot mélangé
   return melange;
}

void TPmotMyst() {

   string motMystere, motMelange, motUtilisateur;

   //Initialisation des nombres aléatoires
   srand(time(0));

   //1 : On demande de saisir un mot
   cout << "Saisissez un mot" << endl;
   cin >> motMystere;

   //2 : On récupère le mot avec les lettres mélangées dans motMelange
   motMelange = melangerLettres(motMystere);

   //3 : On demande à l'utilisateur quel est le mot mystère
   do
   {
      cout << endl << "Quel est ce mot ? " << motMelange << endl;
      cin >> motUtilisateur;

      if (motUtilisateur == motMystere)
      {
         cout << "Bravo !" << endl;
      }
      else
      {
         cout << "Ce n'est pas le mot !" << endl;
      }
   }while (motUtilisateur != motMystere);
   //On recommence tant qu'il n'a pas trouvé

}

void fichier(){
    string const nomFichier("scores.txt");
    ofstream monFlux(nomFichier.c_str()); // ios::app en 2e param pour add a la fin

    if(monFlux)
    {
        monFlux << "Bonjour, je suis une phrase écrite dans un fichier." << endl;
        monFlux << 42.1337 << endl;
        int age(23);
        monFlux << "J'ai " << age << " ans." << endl;
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }

   ifstream fichier("scores.txt");

   if(fichier)
   {
      //L'ouverture s'est bien passée, on peut donc lire

      string ligne; //Une variable pour stocker les lignes lues

      while(getline(fichier, ligne)) //Tant qu'on n'est pas à la fin, on lit
      {
         cout << ligne << endl;
                 //Et on l'affiche dans la console

            int position = fichier.tellg(); //On récupére la position
            cout << "Nous nous situons au " << position << "eme caractere du fichier." << endl;
      }
   }
   else
   {
      cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
   }

   fichier.close();
}

void bases() {
    cout << "Quel est votre nom ?" << endl;
    string nomUtilisateur("Sans nom"); //On crée une case mémoire pour contenir une chaine de caractères
    getline(cin, nomUtilisateur); //On remplit cette case avec toutela ligne que l'utilisateur a écrit

    nomUtilisateur[0] = 'L';  //On modifie la première lettre
    //cin.ignore(); si cin avant et getline apres

    cout << "Combien vaut pi ?" << endl;
    double piUtilisateur(-1.); //On crée une case mémoire pour stockerun nombre réel
    cin >> piUtilisateur; //Et on remplit cette case avec ce qu'écritl'utilisateur

    cout << "Vous vous appelez " << nomUtilisateur << " et vous pensez que pivaut " << piUtilisateur << "." << endl;

    cout << "Quel age avez-vous ?" << endl;
    int ageUtilisateur(0); //On prepare une case mémoire pour stocker un entier
    cin >> ageUtilisateur; //On fait entrer un nombre dans cette case
    cout << "Vous avez " << ageUtilisateur << " ans !" <<  endl; //Et on l'affiche

    int nbEnfants(0);

    do
    {
        cout << "Combien d'enfants avez-vous ?" << endl;
        cin >> nbEnfants;
    } while (nbEnfants < 0);

    cout << "Merci d'avoir indique un nombre d'enfants correct. Vous en avez " << nbEnfants << endl;


       int const nombreNotes(6);
       double notes[nombreNotes];

       notes[0] = 12.5;
       notes[1] = 19.5;  //Bieeeen !
       notes[2] = 6.;    //Pas bien !
       notes[3] = 12;
       notes[4] = 14.5;
       notes[5] = 15;

       double moyenne(0);
       for(int i(0); i<nombreNotes; ++i)
       {
          moyenne += notes[i];   //On additionne toutes les notes
       }
       //En arrivant ici, la variable moyenne contient la somme des notes (79.5)
       //Il ne reste donc qu'à diviser par le nombre de notes
       moyenne /= nombreNotes;

       cout << "Votre moyenne est : " << moyenne << endl;

        int const tailleX(5);
        int const tailleY(4);
        int tableauMulti[tailleX][tailleY];

       vector<int> tableau(5, 3);  //Crée un tableau dynamique de 5 entiers valant tous 3
       vector<string> listeNoms(12, "Sans nom"); //Crée un tableau de 12 strings valant toutes « Sans nom »

        tableau.pop_back(); //Et hop ! Plus que 2 cases
        tableau.push_back(8);
        //On ajoute une 3ème case au tableau qui contient la valeur 8

    //pointeurs
    string reponseA, reponseB, reponseC;
    reponseA = "La peur des jeux de loterie";
    reponseB = "La peur du noir";
    reponseC = "La peur des vendredis treize";

    cout << "Qu'est-ce que la 'kenophobie' ? " << endl; //On pose la question
    cout << "A) " << reponseA << endl; //Et on affiche les trois propositions
    cout << "B) " << reponseB << endl;
    cout << "C) " << reponseC << endl;

    char reponse;
    cout << "Votre reponse (A,B ou C) : ";
    cin >> reponse; //On récupère la réponse de l'utilisateur

    string *reponseUtilisateur(0); //Un pointeur qui pointera sur la réponse choisie
    switch(reponse)
    {
    case 'A':
        reponseUtilisateur = &reponseA; //On déplace le pointeur sur la réponse choisie
        break;
    case 'B':
        reponseUtilisateur = &reponseB;
        break;
    case 'C':
        reponseUtilisateur = &reponseC;
        break;
    }

    //On peut alors utiliser le pointeur pour afficher la réponse choisie
    cout << "Vous avez choisi la reponse : " << *reponseUtilisateur << endl;
}
