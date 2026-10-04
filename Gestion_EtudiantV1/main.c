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
void pause_enter() { printf("\nAppuie sur Entree pour continuer..."); while (getchar()!='\n'); }

void ajouterEtudiant(Etudiants etud[100], int n){

    printf("Insertion de Donnee... ");
    for(int i = 0; i < n; i++){
        printf("ID Etudiant %d : ", i+1);
        scanf("%d", &etud[i].ID);

        printf("\n Nom Etudiant %d : ", i+1);
        scanf("%49s", etud[i].nom);

        printf("\n Prenoms Etudiant %d : ", i+1);
        scanf("%49s", etud[i].prenoms);

        printf("\n Age Etudiant %d : ", i+1);
        scanf("%d", &etud[i].age);

        printf("\n Filiere Etudiant %d : ", i+1);
        scanf("%10s", etud[i].filiere);

        printf("\n Notes Etudiant %d : ", i+1);
        for(int j= 0; j < 10;j++){
            printf("\nNote %d", j+1);
            scanf("%f", etud[i].notes);
        }
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
     printf("       ***    MENU    ***       \n");
}

void save(const Etudiants *e) {
    FILE *f = fopen(SAVEFILE, "wb");
    if (!f) { perror("Erreur sauvegarde"); return; }
    fwrite(e, sizeof(Etudiants), 1, f);
    fclose(f);
    printf("Partie sauvegardee (%s)\n", SAVEFILE);
}

int load(Etudiants *e) {
    FILE *f = fopen(SAVEFILE, "rb");
    if (!f) return 0;
    if (fread(e, sizeof(Etudiants)), 1, f) != 1) { fclose(f); return 0; }
    fclose(f);
    return 1;
}



int main()
{
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


   Etudiants etud[100];
   Etudiants *etudPtr = etud;
   int nbEtudiants = 0;


   if(etudPtr == NULL){
        return 1;
   }

   int choix;
   while(true){
    printf("Entrez votre choix : ");
    scanf("%d", &choix);

    switch(choix){

        case 1:
            nbEtudiants++;
            ajouterEtudiant(etud,nbEtudiants);
            pause_enter();

        case 2:
            afficherEtudiants(etud,nbEtudiants);
            pause_enter();

        case 3:
            rechercherEtudiant();
            pause_enter();


        case 7:
            save(etudPtr);
            pause_enter();

        case 8:
            load(etudPtr);
            pause_enter();




    }


   }





}
