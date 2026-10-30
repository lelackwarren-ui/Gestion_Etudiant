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
     printf("Saisir l'ID de l'etudiant : ");
     scanf("%d", &id);


    bool trouve = false;
    for(int i = 0; i < n+1; i++)
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
     printf("Saisir l'ID de l'etudiant : ");
     scanf("%d", &id);


    bool trouve = false;
    int choix;
    for(int i = 0; i < n+1; i++)
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
           printf(ANSI_BOLD ANSI_ORANGE "  *** MENU DE MODIFICATION ***  \n" ANSI_RESET ANSI_RESET);
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
        }while(choix = 6);

        }
    }

}

void supprimerEtudiants(Etudiants etud[100], int n){}


float calculerMoyenne(Etudiants etud[100], int n)
{
    printf("\n  *** CALCULER MOYENNES ***  \n");

    if (n == 0)
    {
        printf("Aucun etudiant enregistre.\n");
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



int load(Etudiants *e, int *nbEtPtr)
{
    FILE *f = fopen(SAVEFILE, "r");

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

   if(nbEtPtr == NULL){
        return 1;
   }
   load(etud, &nbEtudiants);
   pause_enter();

   int choix;
   char reponse;
   while(1){

   printf(ANSI_BOLD" ================================= \n"ANSI_RESET);
   printf(ANSI_BOLD"       GESTION ETUDIANTS           \n" ANSI_RESET);
   printf(ANSI_BOLD" =================================  \n"ANSI_RESET);
   printf(ANSI_BOLD ANSI_YELLOW "       ***    MENU    ***       \n"ANSI_RESET ANSI_RESET );
   printf("    1. Ajouter un étudiant         \n");
   printf("    2. Afficher les étudiants      \n");
   printf("    3. Rechercher un étudiant      \n");
   printf("    4. Modifier un étudiant       \n");
   printf("    5. Supprimer un étudiant       \n");
   printf("    6. Calculer les moyennes     \n");
   printf("    7. Sauvegarder                \n");
   printf("    8. Charger                     \n");
   printf("    9. Quitter                    \n\n");

   printf(ANSI_CYAN "Nombre d'etudiants : %d\n" ANSI_RESET , nbEtudiants);

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
            printf("Nombre d'etudiants : %d\n", nbEtudiants);
            save(etudPtr, nbEtudiants);
            pause_enter();
            break;

        case 8:
            load(etud, &nbEtudiants);
            pause_enter();
            break;

        case 9:
            printf(ANSI_GREEN "Vous etes sur de quitter le logiciel ? \n -- "ANSI_RESET);

            char reponse;
            char sur;

            scanf(" %c", &reponse);

            if (reponse == 'o' || reponse == 'O')
            {
                printf(ANSI_GREEN "Voulez-vous sauvegarder les donnees ? \n -- " ANSI_RESET);

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
