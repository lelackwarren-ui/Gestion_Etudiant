#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#ifdef _WIN32
  #include <windows.h>
  #define CLEAR_CMD "cls"
#else
  #define CLEAR_CMD "clear"
#endif
#define SAVEFILE "Etudiants.txt"


#define ANSI_RESET   "\x1b[0m"
#define ANSI_BOLD    "\x1b[1m"
#define ANSI_RED     "\x1b[31m"
#define ANSI_GREEN   "\x1b[32m"
#define ANSI_YELLOW  "\x1b[33m"
#define ANSI_BLUE    "\x1b[34m"
#define ANSI_MAGENTA "\x1b[35m"
#define ANSI_CYAN    "\x1b[36m"
#define ANSI_WHITE   "\x1b[37m"
#define ANSI_ORANGE  "\x1b[38m"
#define ANSI_GREY    "\x1b[39m"



typedef struct{
    int ID;
    char nom[50];
    char prenoms[50];
    int age;
    char filiere[10];
    float notes[10];
    float moyenne;
} Etudiants;

void clear_screen() { system(CLEAR_CMD); }
void pause_enter() {
    int c;
    printf("\nAppuie sur Entree pour continuer...\n");
    while ((c = getchar()) != '\n' && c != EOF);
// Attendre que l'utilisateur appuie sur Entree
    while ((c = getchar()) != '\n' && c != EOF);
     clear_screen();
}

void ajouterEtudiant(Etudiants etud[100], int n){

     printf("Insertion de l'etudiant...\n");

    printf("ID : ");
    scanf("%d", &etud[n].ID);

    printf("Nom : ");
    scanf("%49s", etud[n].nom);

    printf("Prenoms : ");
    scanf("%49s", etud[n].prenoms);

    printf("Age : ");
    scanf("%d", &etud[n].age);

    printf("Filiere : ");
    scanf("%9s", etud[n].filiere);

    printf("Notes :\n");

    for(int i = 0; i < 10; i++)
    {
        printf("Note %d : ", i + 1);
        scanf("%f", &etud[n].notes[i]);
    }
    //calculerMoyenne(etud, n);
    //printf("Moyenne : %f \n", &etud[n].moyenne );

}

void afficherEtudiants(Etudiants etud[100], int n){

    for(int i = 0; i < n; i++){
        printf("=== Etudiant %d === \n", i+1);
        printf("ID : %d \n", etud[i].ID);
        printf("Nom : %s \n", etud[i].nom);
        printf("Prenoms : %s \n", etud[i].prenoms);
        printf("Age : %d \n", etud[i].age);
        printf("Filiere : %s \n", etud[i].filiere);
        for(int j= 0; j < 10;j++){
            printf("Note %d : %f \n", j+1, etud[i].notes[j]);
        }
        printf("Moyenne : %f \n", etud[i].moyenne);

    }
}

void rechercherEtudiant(){
     printf("       *** RECHERCHER  ***       \n");

}


void modifierEtudiant(){}
void supprimerEtudiants(){}
float calculerMoyenne(Etudiants etud[100], int n){
    if(n = 0){
        printf("Aucun étudiant enregistré \n");
        return 1;
    }

    for(int i = 0; i < n - 1; i++)
    {

        float somme = 0;
        for(int j = 0; j < 9; j++)
        {
            somme = somme + etud[i].notes[j];
        }

        etud[i].moyenne = somme/10;

    printf("Moyenne de l'etudiant %d : %f", i+1, etud[i].moyenne);
    }

}

void save(const Etudiants *e, int nbEtudiant)
{
    FILE *f = fopen(SAVEFILE, "w");

    if (f == NULL)
    {
        perror("Erreur sauvegarde");
        return;
    }

    fprintf(f, "%d\n", nbEtudiant);

    for (int i = 0; i < nbEtudiant; i++)
    {
        fprintf(f, "%d;%s;%s;%d;%s",
                e[i].ID,
                e[i].nom,
                e[i].prenoms,
                e[i].age,
                e[i].filiere);

        for (int j = 0; j < 10; j++)
        {
            fprintf(f, ";%.2f", e[i].notes[j]);
        }

        fprintf(f, ";%.2f\n", e[i].moyenne);
    }

    fclose(f);

    printf("Donnees sauvegardees dans %s\n", SAVEFILE);
}


int load(Etudiants *e, int *nbEtPtr)
{
    FILE *f = fopen(SAVEFILE, "r");

    if (f == NULL)
    {
        perror("Erreur chargement");
        return 0;
    }

    int nombre;


    if (fscanf(f, "%d", &nombre) != 1)
    {
        fclose(f);
        printf("Erreur : nombre d'etudiants invalide.\n");
        return 0;
    }


    if (nombre < 0 || nombre > 100)
    {
        fclose(f);
        printf("Erreur : nombre d'etudiants invalide.\n");
        return 0;
    }

    for (int i = 0; i < nombre; i++)
    {
        int resultat = fscanf(f,
            " %d;%49[^;];%49[^;];%d;%9[^;]",
            &e[i].ID,
            e[i].nom,
            e[i].prenoms,
            &e[i].age,
            e[i].filiere);

        if (resultat != 5)
        {
            fclose(f);
            printf("Erreur lors de la lecture de l'etudiant %d.\n", i + 1);
            return 0;
        }

        for (int j = 0; j < 10; j++)
        {
            if (fscanf(f, ";%f", &e[i].notes[j]) != 1)
            {
                fclose(f);
                printf("Erreur lors de la lecture des notes.\n");
                return 0;
            }

        if (fscanf(f, ";%f", &e[i].moyenne) != -1)
        {
            fclose(f);
            printf("Erreur lors de la lecture de la moyenne.\n");
            return 0;
        }
    }

    fclose(f);


    *nbEtPtr = nombre;

    printf("Chargement reussi !\n");

    return 1;
}
}

void quitter(){
    printf("Fermeture du programme...\n");
    exit(0);
}


/*void mainload(Etudiants *e, int *nbEtPtr){

    printf(ANSI_BOLD " *** Demarrage des donnees ***" ANSI_RESET "\n\n");
    printf("1) Nouvelle partie   2) Charger\n> ");
    int choice = 1;
    if (scanf("%d", &choice) == 1) {
        while (getchar()!='\n');
        if (choice == 2) {
            load(e, nbEtPtr);


            if(e == NULL){
             return 1;
            }

        if (load(e, nbEtPtr)) {
            printf("Chargement des etudiants reussi.\n");
        }
        else {
            printf("Aucune sauvegarde valide n'a ete chargee.\n");
        }
        }

        }
     else { while (getchar()!='\n'); }

}*/

int main()
{

   Etudiants etud[100] = {0};
   int nbEtudiants = 0;

   Etudiants *etudPtr = etud;
   int *nbEtPtr = &nbEtudiants;

   //mainload(etudPtr,nbEtPtr);


   if(etudPtr == NULL){
        return 1;
   }

   int choix;
   char reponse;
   while(1){

   printf(ANSI_BOLD" ================================= \n"ANSI_RESET);
   printf(ANSI_BOLD"       GESTION ETUDIANTS           \n" ANSI_RESET);
   printf(ANSI_BOLD" =================================  \n"ANSI_RESET);
   printf("       ***    MENU    ***       \n");
   printf("    1. Ajouter un étudiant         \n");
   printf("    2. Afficher les étudiants      \n");
   printf("    3. Rechercher un étudiant      \n");
   printf("    4. Modifier un étudiant       \n");
   printf("    5. Supprimer un étudiant       \n");
   printf("    6. Calculer les moyennes     \n");
   printf("    7. Sauvegarder                \n");
   printf("    8. Charger                     \n");
   printf("    9. Quitter                    \n");


    printf("Entrez votre choix : ");
    scanf("%d", &choix);

    switch(choix){

        case 1:
            if(nbEtudiants < 100)
            {
                ajouterEtudiant(etud, nbEtudiants);
                nbEtudiants++;
            }
            else
            {
                printf("Tableau plein !\n");
            }

            pause_enter();
            break;


        case 2:
            afficherEtudiants(etud,nbEtudiants);
            pause_enter();
            break;


        case 3:
            rechercherEtudiant();
            pause_enter();
            break;

        case 4:
            modifierEtudiant();
            pause_enter();
            break;

        case 5:
            supprimerEtudiants();
            pause_enter();
            break;

        case 6:
            calculerMoyenne(etud,nbEtudiants);
            pause_enter();
            break;

        case 7:
            save(etudPtr, nbEtudiants);
            pause_enter();
            break;

        case 8:
            load(etudPtr, nbEtPtr);
            pause_enter();
            break;

        case 9:
            printf("Vous etes sur de quitter le logiciel ? \n -- ");
            char reponse;
            char sur;
            scanf("%s", &reponse);
            if(reponse ==  'o'){
                printf(ANSI_GREEN "Voulez vous sauvergarder les donnees ? \n"ANSI_RESET);
                scanf("%s", &sur);
                if(sur == 'o'){
                    save(etudPtr, nbEtudiants);
                    quitter();
                break;
                }
            }
            else{
                quitter();
                break;
            }

        default:
            printf("Choix Invalide...");
            pause_enter();

    }

   }
}
