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
void calculerMoyenne(){}

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

        if (fscanf(f, ";%f", &e[i].moyenne) != 1)
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


int main()
{
    //mainloop();
   Etudiants etud[100];
   Etudiants *etudPtr = etud;
   int nbEtudiants = 1;
   int *nbEtPtr = &nbEtudiants;


   if(etudPtr == NULL){
        return 1;
   }

   load(etudPtr, nbEtPtr);
   int choix;
   char reponse;
   while(1){

   printf(" ================================= \n");
   printf("       GESTION ETUDIANTS           \n");
   printf(" =================================  \n");
   printf("       ***    MENU    ***       \n");
   printf("    1. Ajouter un étudiant         \n");
   printf("    2. Afficher les étudiants      \n");
   printf("    3. Rechercher un étudiant      \n");
   printf("    4. Modifier un étudiant       \n");
   printf("    5. Supprimer un étudiant       \n");
   printf("    6. Calculer les statistiques   \n");
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
            calculerMoyenne();
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
            scanf("%s", &reponse);
            if(reponse ==  'o'){
                save(etudPtr, nbEtudiants);
                quitter();
                break;
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
