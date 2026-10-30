#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>

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
    printf(ANSI_ORANGE "\nAppuie sur Entree pour continuer...\n"ANSI_RESET );
    while ((c = getchar()) != '\n' && c != EOF);

    while ((c = getchar()) != '\n' && c != EOF);
     clear_screen();
}

void ajouterEtudiant(Etudiants etud[100], int n){

     printf(ANSI_BLUE "Insertion de l'etudiant...\n"ANSI_RESET );

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
    float somme = 0;

    for (int j = 0; j < 10; j++)
    {
        somme += etud[n].notes[j];
    }
    etud[n].moyenne = somme / 10;
        printf("Moyenne de l'etudiant %d : %.2f\n", n, etud[n].moyenne);

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

void rechercherEtudiant(Etudiants etud[100], int n){
     printf(ANSI_BOLD ANSI_WHITE "       *** RECHERCHER ETUDIANT ***       \n" ANSI_RESET ANSI_RESET);
     if(n = 0){printf(ANSI_RED "Aucun etudiant enregistre"ANSI_RESET);}

     int id;
     printf(ANSI_GREEN ANSI_BOLD "Saisir l'ID de l'etudiant : ");
     scanf("%d", &id);


    bool trouve = false;
    for(int i = 0; i < n+2; i++)
    {
        if(etud[i].ID == id)
        {
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
              trouve = true;
              break;
        }
    }


    if(trouve == false){
        printf("Etudiant introuvable");
    }
}


void modifierEtudiant(Etudiants etud[100], int n){
    printf(ANSI_BOLD ANSI_WHITE "       *** MODIFIER ETUDIANT  ***       \n" ANSI_RESET ANSI_RESET);
     if(n = 0){printf(ANSI_RED "Aucun etudiant enregistre"ANSI_RESET);}

     int id;
     printf(ANSI_GREEN ANSI_BOLD"Saisir l'ID de l'etudiant : ");
     scanf("%d", &id);


    bool trouve = false;
    int choix;
    for(int i = 0; i < n+2; i++)
    {
        if(etud[i].ID == id)
        {
            trouve = true;

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

         do{
           printf(ANSI_YELLOW ANSI_BOLD  "  *** MENU DE MODIFICATION ***  \n" ANSI_RESET ANSI_RESET);
           printf("    1. Modifier le nom             \n");
           printf("    2. Modifier le prenom          \n");
           printf("    3. Modifier l'age              \n");
           printf("    4. Modifier la filiere         \n");
           printf("    5. Modifier les notes          \n");
           printf("    6. Terminer la modification  \n\n");

           printf(ANSI_WHITE "Entrez votre choix : " ANSI_RESET);
           scanf("%d", &choix);

           switch(choix){
            case 1:
                char nouveauNom[50];
                printf("Insere le nouveau nom : ");
                scanf("%49s", nouveauNom);
                strcpy(etud[i].nom,nouveauNom);
                break;

            case 2:
                char nouveauPrenom[50];
                printf("Insere le nouveau prenom : ");
                scanf("%49s", nouveauPrenom);
                strcpy(etud[i].prenoms,nouveauPrenom);
                break;

            case 3:
                int nouveauAge;
                printf("Insere le nouveau age: ");
                scanf("%d", &nouveauAge);
                etud[i].age = nouveauAge;
                break;

            case 4:
                char nouveauFiliere[10];
                printf("Insere le nouveau filiere : ");
                scanf("%9s", nouveauFiliere);
                strcpy(etud[i].filiere,nouveauFiliere);
                break;
            case 5:
                printf("Inserer les nouvelles notes : ");
                for(int j = 0; j < 10; j++)
                {
                    printf("Nouvelle Note %d : ", j + 1);
                    scanf("%f", &etud[i].notes[j]);
                }

                float somme = 0;

                for (int j = 0; j < 10; j++)
                {
                    somme += etud[i].notes[j];
                }

                etud[i].moyenne = somme / 10;
                printf("Moyenne de l'etudiant %d : %.2f\n", id, etud[i].moyenne);

            case 6:
                printf("=== Etudiant %d === \n", id);
                printf("ID : %d \n", etud[i].ID);
                printf("Nom : %s \n", etud[i].nom);
                printf("Prenoms : %s \n", etud[i].prenoms);
                printf("Age : %d \n", etud[i].age);
                printf("Filiere : %s \n", etud[i].filiere);
                for(int j= 0; j < 10;j++){
                    printf("Note %d : %f \n", j+1, etud[i].notes[j]);
                }
                  printf("Moyenne : %f \n", etud[i].moyenne);
                  break;

            default:
                printf(ANSI_RED "Choix invalide" ANSI_RESET);


           }
        }while(choix != 6);

        }
    }

}

void supprimerEtudiants(Etudiants etud[100], int n){
     printf(ANSI_BOLD ANSI_WHITE "       *** SUPPRIMER ETUDIANT  ***       \n" ANSI_RESET ANSI_RESET);
     if(n = 0){printf(ANSI_RED "Aucun etudiant enregistre"ANSI_RESET);}

     int id;
     printf(ANSI_GREEN ANSI_BOLD"Saisir l'ID de l'etudiant : ");
     scanf("%d", &id);


    bool trouve = false;
    for(int i = 0; i < n+2; i++)
    {
      if(etud[i].ID == id)
      {
          trouve = true;
          printf("\n=== Etudiant %d === \n", id);
          printf("ID : %d \n", etud[i].ID);
          printf("Nom : %s \n", etud[i].nom);
          printf("Prenoms : %s \n", etud[i].prenoms);
          printf("Age : %d \n", etud[i].age);
          printf("Filiere : %s \n", etud[i].filiere);
          for(int j= 0; j < 10;j++){
           printf("Note %d : %f \n", j+1, etud[i].notes[j]);
          }
          printf("Moyenne : %f \n\n\n", etud[i].moyenne);


          char choix;
          printf("Etes-vous sur ? \n -- ");
          scanf(" %c", &choix);

          if(choix == 'o' || choix == 'O')
          {
             for(int j = i; j < n-1; j++)
             {
                etud[j] = etud[j + 1];
             }

             n--;
             printf(ANSI_GREEN "Suppression reussi!\n"ANSI_RESET );
          }

          else{
             printf(ANSI_YELLOW "Suppression annulee!\n" ANSI_RESET);
          }

          break;

      }
    }
    if(trouve == false)
        printf(ANSI_RED "Etudiant introvable. \n" ANSI_RESET);

}


float calculerMoyenne(Etudiants etud[100], int n)
{
    printf(ANSI_WHITE ANSI_BOLD "\n  *** CALCULER MOYENNES ***  \n" ANSI_RESET ANSI_RESET);

    if (n == 0)
    {
        printf(ANSI_RED "Aucun etudiant enregistre.\n" ANSI_RESET);
        return 0;
    }

    for (int i = 0; i < n; i++)
    {
        float somme = 0;

        for (int j = 0; j < 10; j++)
        {
            somme += etud[i].notes[j];
        }

        etud[i].moyenne = somme / 10;

        printf("Moyenne de l'etudiant %d : %.2f\n",i + 1, etud[i].moyenne);
    }

    return 1;
}

void triFiliere(Etudiants etud[100], int n)
{
     if(n = 0){printf(ANSI_RED "Aucun etudiant enregistre\n"ANSI_RESET);}

     for(int i = 0; i < n+2; i++)
     {
       int positionMin = i;

       for(int j = i+1; j <= n+1; j++)
       {
           if(etud[j].filiere < etud[positionMin].filiere)
            {
               positionMin = j;
            }
       }

       if(positionMin != i)
        {
            Etudiants temp = etud[i];
            etud[i] = etud[positionMin];
            etud[positionMin] = temp;
        }
     }
     printf(ANSI_GREEN "\n *** TRI PAR FILIERE *** \n" ANSI_RESET);
     for(int i = 0; i < n+2; i++)
     {
        printf("=== Etudiant %d === \n", i+1);
        printf("ID : %d \n", etud[i].ID);
        printf("Nom : %s \n", etud[i].nom);
        printf("Prenoms : %s \n", etud[i].prenoms);
        printf("Age : %d \n", etud[i].age);
        printf("Filiere : %s \n\n", etud[i].filiere);

        printf(ANSI_CYAN "-----------------------------------------------\n" ANSI_RESET);
     }
}

void triRang(Etudiants etud[100], int n)
{
     if(n = 0){printf(ANSI_RED "Aucun etudiant enregistre. \n"ANSI_RESET);}

     for(int i = 0; i < n+2; i++)
     {
       int positionMax = i;

       for(int j = i+1; j <=n+1; j++)
       {
           if(etud[j].moyenne > etud[positionMax].moyenne)
           {
               positionMax = j;
           }
       }

       if(positionMax != i)
        {
            Etudiants temp = etud[i];
            etud[i] = etud[positionMax];
            etud[positionMax] = temp;
        }
     }
     printf(ANSI_GREEN "\n ***  CLASSEMENT DES ETUDIANTS  ***\n "ANSI_RESET);
     for(int i = 0; i < n+1; i++)
     {
         printf("Rang : %d\n", i+1);
         printf("Mr/Mme : %s %s\n",etud[i].nom, etud[i].prenoms);
         printf("Moyenne : %f\n\n", etud[i].moyenne);

         printf(ANSI_CYAN "-----------------------------------------------\n" ANSI_RESET);
     }
}

void triAge(Etudiants etud[100], int n)
{
     if(n = 0){printf(ANSI_RED "Aucun etudiant enregistre. \n"ANSI_RESET);}

     for(int i = 0; i < n+2; i++)
     {
       int positionMin = i;

       for(int j = i+1; j <= n+1; j++)
       {
           if(etud[j].filiere < etud[positionMin].filiere)
            {
               positionMin = j;
            }
       }

       if(positionMin != i)
        {
            Etudiants temp = etud[i];
            etud[i] = etud[positionMin];
            etud[positionMin] = temp;
        }
     }
     printf(ANSI_GREEN "\n *** CLASSEMENT PAR AGE *** \n"ANSI_RESET);
    for(int i = 0; i < n+2; i++)
     {
         printf("Nom : %s\n",etud[i].nom);
         printf("Prenoms :  %s\n", etud[i].prenoms);
         printf("Age : %d\n\n", etud[i].age);
     }
}

void afficherAdmisNonAdmis(Etudiants etud[100], int n)
{
     if(n = 0){printf(ANSI_RED "Aucun etudiant enregistre. \n"ANSI_RESET);}
     int admis = 0;
     int nonAdmis = 0;

     printf(ANSI_GREEN " \n *** ETUDIANTS ADMIS *** \n" ANSI_RESET);

     for(int i = 0; i <= n+2; i++)
     {
        if(etud[i].moyenne >= 10){


        printf("ID : %d \n", etud[i].ID);
        printf("Nom : %s \n", etud[i].nom);
        printf("Prenoms : %s \n", etud[i].prenoms);
        printf("Age : %d \n", etud[i].age);
        printf("Filiere : %s \n\n", etud[i].filiere);

        printf(ANSI_CYAN "-----------------------------------------------\n" ANSI_RESET);

        admis= admis + 1;
        }
     }

     printf(ANSI_RED " *** ETUDIANTS NON ADMIS *** \n" ANSI_RESET);

     for(int i = 0; i < n+2; i++)
     {
        if(etud[i].moyenne <= 10){

        printf("ID : %d \n", etud[i].ID);
        printf("Nom : %s \n", etud[i].nom);
        printf("Prenoms : %s \n", etud[i].prenoms);
        printf("Age : %d \n", etud[i].age);
        printf("Filiere : %s \n\n", etud[i].filiere);

        nonAdmis = nonAdmis + 1;
        }
     }

       printf("Nombre d'admis : %d\n", admis);
       printf("Nombre d'admis : %d\n", nonAdmis);
}

void bulletinIndividuel(Etudiants etud[100], int nbEtudiants)
{
    int idRecherche;
    int position = -1;

    if (nbEtudiants == 0) {
        printf(ANSI_RED "\nAucun etudiant enregistre !\n" ANSI_RESET);
        return;
    }

    printf(ANSI_BOLD ANSI_WHITE"\n");
    printf("============================================\n");
    printf("             BULLETIN DE NOTES              \n");
    printf("============================================\n");
    printf(ANSI_RESET);

    printf("Entrez l'ID de l'etudiant : ");

    if (scanf("%d", &idRecherche) != 1) {
        while (getchar() != '\n');
        printf(ANSI_RED "\nID invalide !\n" ANSI_RESET);
        return;
    }

    while (getchar() != '\n');

    for (int i = 0; i < nbEtudiants; i++) {

        if (etud[i].ID == idRecherche) {
            position = i;
            break;
        }
    }

    if (position == -1) {
        printf(ANSI_RED "\nEtudiant introuvable !\n" ANSI_RESET);
        return;
    }


    printf(ANSI_GREEN ANSI_BOLD "\nETUDIANT TROUVE !\n" ANSI_RESET);

    printf(ANSI_CYAN "\nID       : " ANSI_RESET "%d\n", etud[position].ID);
    printf(ANSI_CYAN "Nom      : " ANSI_RESET "%s\n", etud[position].nom);
    printf(ANSI_CYAN "Prenoms  : " ANSI_RESET "%s\n", etud[position].prenoms);
    printf(ANSI_CYAN "Age      : " ANSI_RESET "%d ans\n", etud[position].age);
    printf(ANSI_CYAN "Filiere  : " ANSI_RESET "%s\n", etud[position].filiere);

    printf(ANSI_BOLD ANSI_BLUE "\n--------------- NOTES ----------------\n" ANSI_RESET);

    for (int j = 0; j < 10; j++) {
        printf(ANSI_WHITE "Matiere %02d : " ANSI_RESET "%.2f / 20\n",
               j + 1, etud[position].notes[j]);
    }

    printf(ANSI_BLUE "--------------------------------------\n" ANSI_RESET);

    printf(ANSI_BOLD ANSI_YELLOW "\nMoyenne : " ANSI_RESET);
    printf(ANSI_GREEN "%.2f / 20\n", etud[position].moyenne);

    if (etud[position].moyenne >= 10) {
        printf(ANSI_GREEN ANSI_BOLD "\nRESULTAT : ADMIS\n" ANSI_RESET);
    } else {
        printf(ANSI_RED ANSI_BOLD "\nRESULTAT : NON ADMIS\n" ANSI_RESET);
    }

    printf(ANSI_CYAN "============================================\n" ANSI_RESET);
}

void trouverMentions(Etudiants etud[100], int nbEtudiants)
{
    if (nbEtudiants == 0) {
        printf(ANSI_RED "\nAucun etudiant enregistre !\n" ANSI_RESET);
        return;
    }

    printf(ANSI_BOLD ANSI_CYAN "\n");
    printf("============================================================\n");
    printf("                  MENTIONS DES ETUDIANTS                    \n");
    printf("============================================================\n");
    printf(ANSI_RESET);

    for (int i = 0; i < nbEtudiants; i++) {

        float moyenne = etud[i].moyenne;
        char *mention;
        char *couleur;

        if (moyenne < 10) {
            mention = "Non admis";
            couleur = ANSI_RED;
        }
        else if (moyenne < 12) {
            mention = "Passable";
            couleur = ANSI_YELLOW;
        }
        else if (moyenne < 14) {
            mention = "Assez bien";
            couleur = ANSI_CYAN;
        }
        else if (moyenne < 16) {
            mention = "Bien";
            couleur = ANSI_GREEN;
        }
        else {
            mention = "Tres bien";
            couleur = ANSI_BOLD ANSI_GREEN;
        }

        printf(ANSI_BLUE "\nEtudiant %d\n" ANSI_RESET, i + 1);

        printf(ANSI_WHITE "ID       : " ANSI_RESET "%d\n", etud[i].ID);
        printf(ANSI_WHITE "Nom      : " ANSI_RESET "%s %s\n",
               etud[i].nom, etud[i].prenoms);

        printf(ANSI_WHITE "Moyenne  : " ANSI_RESET "%.2f / 20\n", moyenne);

        printf(ANSI_WHITE "Mention  : " ANSI_RESET "%s%s%s\n",
               couleur, mention, ANSI_RESET);

        printf(ANSI_CYAN "-----------------------------------------------\n" ANSI_RESET);
    }

    printf(ANSI_BOLD ANSI_GREEN "\nCalcul des mentions termine !\n" ANSI_RESET);
}

void tableauBord(Etudiants etud[100], int nbEtudiants)
{
    if (nbEtudiants == 0) {
        printf(ANSI_RED "\nAucun etudiant enregistre !\n" ANSI_RESET);
        return;
    }

    float somme = 0;
    float meilleureMoyenne = etud[0].moyenne;
    float faibleMoyenne = etud[0].moyenne;

    int admis = 0;
    int nonAdmis = 0;


    for (int i = 0; i < nbEtudiants; i++) {

        somme += etud[i].moyenne;

        if (etud[i].moyenne > meilleureMoyenne) {
            meilleureMoyenne = etud[i].moyenne;
        }

        if (etud[i].moyenne < faibleMoyenne) {
            faibleMoyenne = etud[i].moyenne;
        }

        if (etud[i].moyenne >= 10) {
            admis++;
        }
        else {
            nonAdmis++;
        }
    }

    float moyenneGenerale = somme / nbEtudiants;

    printf(ANSI_BOLD ANSI_CYAN "\n");
    printf("====================================================\n");
    printf("                 TABLEAU DE BORD                    \n");
    printf("====================================================\n");
    printf(ANSI_RESET);

    printf(ANSI_BOLD ANSI_BLUE "\n              STATISTIQUES GENERALES\n\n" ANSI_RESET);

    printf(ANSI_WHITE "Nombre total d'etudiants : " ANSI_RESET);
    printf(ANSI_GREEN "%d\n", nbEtudiants);

    printf(ANSI_WHITE "Moyenne generale         : " ANSI_RESET);
    printf(ANSI_GREEN "%.2f / 20\n", moyenneGenerale);

    printf(ANSI_WHITE "Meilleure moyenne        : " ANSI_RESET);
    printf(ANSI_GREEN "%.2f / 20\n", meilleureMoyenne);

    printf(ANSI_WHITE "Plus faible moyenne      : " ANSI_RESET);
    printf(ANSI_RED "%.2f / 20\n", faibleMoyenne);

    printf(ANSI_CYAN "\n----------------------------------------------------\n" ANSI_RESET);

    printf(ANSI_BOLD ANSI_BLUE "\n              RESULTATS ACADEMIQUES\n\n" ANSI_RESET);

    printf(ANSI_WHITE "Etudiants admis           : " ANSI_RESET);
    printf(ANSI_GREEN "%d\n", admis);

    printf(ANSI_WHITE "Etudiants non admis       : " ANSI_RESET);
    printf(ANSI_RED "%d\n", nonAdmis);

    printf(ANSI_CYAN "\n----------------------------------------------------\n" ANSI_RESET);

    float tauxReussite = ((float)admis / nbEtudiants) * 100;

    printf(ANSI_WHITE "Taux de reussite          : " ANSI_RESET);
    printf(ANSI_GREEN "%.2f %%\n", tauxReussite);

    printf(ANSI_WHITE "Taux d'echec              : " ANSI_RESET);
    printf(ANSI_RED "%.2f %%\n", 100.0 - tauxReussite);

    printf(ANSI_CYAN "\n====================================================\n" ANSI_RESET);
    printf(ANSI_BOLD ANSI_GREEN "          TABLEAU DE BORD TERMINE !\n" ANSI_RESET);
    printf(ANSI_CYAN "====================================================\n" ANSI_RESET);
}

void save(const Etudiants *e, int nbEtudiant)
{
    FILE *f = fopen(SAVEFILE, "w");

    if (f == NULL)
    {
        perror(ANSI_RED "Erreur sauvegarde"ANSI_RESET );
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

    printf(ANSI_BLUE "Donnees sauvegardees dans %s\n" ANSI_RESET , SAVEFILE);
}

int load(const char *chemin, Etudiants *e, int *nbEtPtr)
{
    FILE *f = fopen(chemin, "r");

    if (f == NULL)
    {
        perror(ANSI_RED "Erreur chargement"ANSI_RESET );
        return 0;
    }

    int nombre;


    if (fscanf(f, "%d", &nombre) != 1)
    {
        fclose(f);
        printf(ANSI_RED "Erreur : nombre d'etudiants invalide.\n"ANSI_RESET );
        return 0;
    }

    if (nombre < 0 || nombre > 100)
    {
        fclose(f);
        printf(ANSI_RED "Erreur : nombre d'etudiants invalide.\n"ANSI_RESET );
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
            printf(ANSI_RED "Erreur lors de la lecture de l'etudiant %d.\n" ANSI_RESET, i + 1);
            return 0;
        }

        for (int j = 0; j < 10; j++)
        {
            if (fscanf(f, ";%f", &e[i].notes[j]) != 1)
            {
                fclose(f);
                printf(ANSI_RED "Erreur lors de la lecture de la note %d de l'etudiant %d.\n"ANSI_RESET , j + 1, i + 1);
                return 0;
            }
        }


        if (fscanf(f, ";%f", &e[i].moyenne) != 1)
        {
            fclose(f);
            printf(ANSI_RED "Erreur lors de la lecture de la moyenne de l'etudiant %d.\n" ANSI_RESET , i + 1);
            return 0;
        }
    }

    fclose(f);

    *nbEtPtr = nombre;

    printf(ANSI_CYAN "Chargement reussi !\n"ANSI_RESET );

    return 1;
}

void quitter(){
    printf(ANSI_MAGENTA ANSI_BOLD "Fermeture du programme...\n"ANSI_RESET ANSI_RESET);
    exit(0);
}

int backup(void)
{
    FILE *source = fopen("Etudiants.txt", "r");

    if (source == NULL) {
        printf("Aucun fichier a sauvegarder.\n");
        return 0;
    }


    if (mkdir("BACKUP", 0777) != 0 && errno != EEXIST) {
        perror("Erreur de creation du dossier");
        fclose(source);
        return 0;
    }


    time_t maintenant = time(NULL);
    struct tm *date = localtime(&maintenant);

    char nomFichier[150];


    strftime(nomFichier, sizeof(nomFichier),
             "BACKUP/Etudiants_%Y-%m-%d_%H-%M-%S.txt", date);


    FILE *destination = fopen(nomFichier, "w");

    if (destination == NULL) {
        perror("Erreur de creation du backup");
        fclose(source);
        return 0;
    }


    int caractere;

    while ((caractere = fgetc(source)) != EOF) {
        if (fputc(caractere, destination) == EOF) {
            printf("Erreur pendant la copie.\n");
            fclose(source);
            fclose(destination);
            return 0;
        }
    }

    fclose(source);
    fclose(destination);

    printf("\nBackup cree avec succes !\n");
    printf("Fichier : %s\n", nomFichier);

    return 1;
}

int chargerBackup(Etudiants *e, int *nbEtPtr)
{
    DIR *dossier = opendir("BACKUP");

    if (dossier == NULL)
    {
        printf(ANSI_RED "Erreur : le dossier BACKUP n'existe pas.\n" ANSI_RESET);
        return 0;
    }

    struct dirent *entree;

    char fichiers[100][256];
    int nombreFichiers = 0;

    printf("\n" ANSI_BOLD ANSI_MAGENTA);
    printf("============================================\n");
    printf("           RESTAURATION BACKUP              \n");
    printf("============================================\n" ANSI_RESET);

    while ((entree = readdir(dossier)) != NULL)
    {
        if (strncmp(entree->d_name, "Etudiants_", 10) == 0)
        {
            const char *extension = strrchr(entree->d_name, '.');

            if (extension != NULL && strcmp(extension, ".txt") == 0)
            {
                if (nombreFichiers < 100)
                {
                    strcpy(fichiers[nombreFichiers], entree->d_name);
                    nombreFichiers++;
                }
            }
        }
    }

    closedir(dossier);

    if (nombreFichiers == 0)
    {
        printf(ANSI_YELLOW "\nAucun backup disponible.\n" ANSI_RESET);
        printf("Creation du backup ...");
        backup();
        return 0;
    }

    printf("\n" ANSI_CYAN ANSI_BOLD "Sauvegardes disponibles :\n\n" ANSI_RESET);

    for (int i = 0; i < nombreFichiers; i++)
    {
        printf(ANSI_GREEN " [%d] " ANSI_RESET, i + 1);
        printf("%s\n", fichiers[i]);
    }

    printf("\n" ANSI_RED " [0] Retour\n" ANSI_RESET);

    int choix;

    printf("\n" ANSI_YELLOW "Choisissez un backup : " ANSI_RESET);

    if (scanf("%d", &choix) != 1)
    {
        while (getchar() != '\n');
        printf(ANSI_RED "Choix invalide.\n" ANSI_RESET);
        return 0;
    }

    while (getchar() != '\n');

    if (choix == 0)
    {
        printf(ANSI_BLUE "\nRetour au menu principal...\n" ANSI_RESET);
        return 0;
    }

    if (choix < 1 || choix > nombreFichiers)
    {
        printf(ANSI_RED "\nChoix invalide !\n" ANSI_RESET);
        return 0;
    }

    char chemin[300];

    snprintf(chemin, sizeof(chemin),
             "BACKUP/%s", fichiers[choix - 1]);

    printf(ANSI_GREEN "\nChargement du backup en cours...\n" ANSI_RESET);

    if (load(chemin, e, nbEtPtr))
    {
        printf(ANSI_GREEN ANSI_BOLD "\nBackup restaure avec succes !\n" ANSI_RESET);

        printf(ANSI_CYAN "Nombre d'etudiants charges : " ANSI_RESET);
        printf(ANSI_GREEN "%d\n" ANSI_RESET, *nbEtPtr);

        return 1;
    }

    printf(ANSI_RED ANSI_BOLD "\nErreur lors de la restauration du backup.\n" ANSI_RESET);

    return 0;
}

void mainload(Etudiants *e, int *nbEtPtr)
{
    clear_screen();
    int choix;

    printf(ANSI_BOLD ANSI_CYAN);
    printf("\t ============================================\n");
    printf("\t              GESTION ETUDIANTS              \n");
    printf("\t ============================================\n");printf(ANSI_RESET);
    printf(ANSI_YELLOW  ANSI_BOLD "\t       ***   MENU DE DEMARRAGE   ***   \n" ANSI_RESET);

    printf(ANSI_BOLD);
    printf("\t\t 1. Nouvelle partie\n");
    printf("\t\t 2. Charger les donnees\n");
    printf("\t\t 3. Restaurer un backup\n");
    printf("\t\t 4. Quitter\n");
    printf(ANSI_RESET);

    printf(ANSI_BOLD ANSI_GREEN "\n Votre choix : " ANSI_RESET);

    if (scanf("%d", &choix) != 1)
    {
        while (getchar() != '\n');

        printf(ANSI_RED "\nErreur : choix invalide !\n" ANSI_RESET);
        return;
    }

    while (getchar() != '\n');

    switch (choix)
    {
        case 1:
            printf("Vous etes sur de d'ouvrir un nouveau tableau de bord?\n  --");
            char reponse;
            scanf(" %c", &reponse);
            if(reponse == 'o' || reponse == 'O')
            {
            printf(ANSI_GREEN "\nDemarrage d'une nouvelle partie...\n" ANSI_RESET);

             if (chargerBackup(e, nbEtPtr))
            {
                printf(ANSI_GREEN "Anciennes donnees sauvegardees.\n" ANSI_RESET);
            }

            *nbEtPtr = 0;

            printf(ANSI_GREEN ANSI_BOLD "\nNouvelle partie demarree !\n" ANSI_RESET);
            }
            break;

        case 2:

            printf(ANSI_BLUE "\nChargement des donnees...\n" ANSI_RESET);

            if (load(SAVEFILE, e, nbEtPtr))
            {
                printf(ANSI_MAGENTA "\n Nombre d'etudiants : " ANSI_RESET);
                printf(ANSI_GREEN "%d\n" ANSI_RESET, *nbEtPtr);
            }
            else
            {
                printf(ANSI_RED "\nAucune sauvegarde valide n'a ete chargee.\n" ANSI_RESET);
            }

            break;

        case 3:

            printf(ANSI_MAGENTA "\nOuverture des sauvegardes...\n" ANSI_RESET);

            chargerBackup(e, nbEtPtr);

            break;

        case 0:

            printf(ANSI_YELLOW "\nFermeture du logiciel...\n" ANSI_RESET);

            quitter();

            break;

        default:

            printf(ANSI_RED "\nChoix invalide ! Veuillez reessayer.\n" ANSI_RESET);

            break;
    }
}

int main()
{

   Etudiants etud[100] = {0};
   int nbEtudiants = 0;

   Etudiants *etudPtr = etud;
   int *nbEtPtr = &nbEtudiants;

   mainload(etudPtr,nbEtPtr);
   pause_enter();

   if(etudPtr == NULL){
        return 1;
   }

   if(nbEtPtr == NULL){
        return 1;
   }


   int choix;
   char reponse;
   while(1){

   printf(ANSI_BOLD ANSI_CYAN "\t============================================  \n"ANSI_RESET);
   printf(ANSI_BOLD ANSI_WHITE "\t||          GESTION ETUDIANTS             ||  \n" ANSI_RESET);
   printf(ANSI_BOLD ANSI_CYAN "\t============================================  \n"ANSI_RESET);
   printf(ANSI_BOLD ANSI_YELLOW "\t\t***    MENU PRINCIPAL   ***       \n\n"ANSI_RESET ANSI_RESET );

   printf(ANSI_BOLD ANSI_MAGENTA "\t ACADEMIQUE       \n"ANSI_RESET ANSI_RESET );
   printf(ANSI_WHITE "\t    1. Ajouter un étudiant         \n"ANSI_RESET);
   printf(ANSI_WHITE "\t    2. Afficher les étudiants      \n"ANSI_RESET);
   printf(ANSI_WHITE "\t    3. Rechercher un étudiant      \n"ANSI_RESET);
   printf(ANSI_WHITE "\t    4. Modifier un étudiant        \n"ANSI_RESET);
   printf(ANSI_WHITE "\t    5. Supprimer un étudiant       \n"ANSI_RESET);
   printf(ANSI_WHITE "\t    6. Calculer les moyennes       \n"ANSI_RESET);
   printf(ANSI_WHITE "\t    7. Trier les Etudiants par filiere        \n"ANSI_RESET);
   printf(ANSI_WHITE "\t    8. Trier Etudiants par rang    \n"ANSI_RESET);
   printf(ANSI_WHITE "\t    9. Trier Etudiants par age    \n"ANSI_RESET);
   printf(ANSI_WHITE "\t    10. Admis ou Non Admis    \n"ANSI_RESET);
   printf(ANSI_WHITE "\t    11. Bulletin de notes (Individuelle)   \n"ANSI_RESET);
   printf(ANSI_WHITE "\t    12. Trouver Mentions    \n"ANSI_RESET);
   printf(ANSI_WHITE "\t    13. Tableau de Bord             \n\n"ANSI_RESET);

   printf(ANSI_BOLD ANSI_MAGENTA "\t SAUVERGARDE      \n"ANSI_RESET ANSI_RESET );
   printf(ANSI_WHITE "\t    14. Sauvegarder                \n"ANSI_RESET);
   printf(ANSI_WHITE "\t    15. Charger                    \n"ANSI_RESET);
   printf(ANSI_WHITE "\t    16. Charger les BackUp         \n"ANSI_RESET);
   printf(ANSI_WHITE "\t    17. Quitter                  \n\n"ANSI_RESET);

   printf(ANSI_CYAN "Nombre d'etudiants : %d\n" ANSI_RESET , nbEtudiants);

    printf(ANSI_BOLD ANSI_GREEN "Entrez votre choix : "ANSI_RESET);
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
            rechercherEtudiant(etud,nbEtudiants);
            pause_enter();
            break;

        case 4:
            modifierEtudiant(etud,nbEtudiants);
            pause_enter();
            break;

        case 5:
            supprimerEtudiants(etud,nbEtudiants);
            pause_enter();
            break;

        case 6:
            calculerMoyenne(etud,nbEtudiants);
            pause_enter();
            break;


        case 7:
          triFiliere(etud, nbEtudiants);
          pause_enter();
          break;

        case 8:
            triRang(etud, nbEtudiants);
            pause_enter();
            break;

        case 9:
            triAge(etud, nbEtudiants);
            pause_enter();
            break;

        case 10:
            afficherAdmisNonAdmis(etud, nbEtudiants);
            pause_enter();
            break;

        case 11:
            bulletinIndividuel(etud, nbEtudiants);
            pause_enter();
            break;

        case 12:
            trouverMentions(etud, nbEtudiants);
            pause_enter();
            break;

       case 13:
          tableauBord(etud, nbEtudiants);
          pause_enter();
          break;

        case 14:
            printf("Nombre d'etudiants : %d\n", nbEtudiants);
            save(etudPtr, nbEtudiants);
            pause_enter();
            break;

        case 15:
            load(SAVEFILE, etud, &nbEtudiants);
            pause_enter();
            break;

        case 16:
            chargerBackup(etud, &nbEtudiants);
            pause_enter();
            break;

        case 17:
            printf(ANSI_GREEN "\n Vous etes sur de quitter le logiciel ? \n -- "ANSI_RESET);

            char reponse;
            char sur;

            scanf(" %c", &reponse);

            if (reponse == 'o' || reponse == 'O')
            {
                printf(ANSI_YELLOW " Voulez-vous sauvegarder les donnees ? \n -- " ANSI_RESET);

                scanf(" %c", &sur);

                if (sur == 'o' || sur == 'O')
                {
                    save(etudPtr, nbEtudiants);
                    quitter();
                    break;
                }
                else
                {
                    quitter();
                    break;
                }
            }
            else
            {
                break;
            }

        default:
            printf(ANSI_RED "Choix Invalide..."ANSI_RESET);
            pause_enter();

    }

   }
}
