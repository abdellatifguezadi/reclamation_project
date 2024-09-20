#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
#define max_users 100
#define max_rec 100



typedef struct{
    char name[50];
    char role[50];
    char mdp[50];
}user;

typedef struct{
    int id;
    char name[50];
    char motif[100];
    char description[200];
    char categorie [50];
    char status[50];
    char date[20];
    char priority[50];
}reclamation;

user users[max_users] ;
reclamation reclamations[max_rec];
int user_nb =0;
int reclamation_nb = 0;
int choix;

void menu(){
    printf("________________________________________\n");
    printf("___________       MENU       ___________\n");
    printf("________________________________________\n");
    printf(" 1  : Sign Up __________________________\n");
    printf(" 2  : Sign In __________________________\n");
    printf(" 3  : Espace admin______________________\n");
    printf(" 4  : Espace agent de reclamation_______\n");
    printf(" 5  : Espace client_____________________\n");
    printf(" 6  : Quitter___________________________\n");
    printf("________________________________________\n");
    printf("_______     choiser un choix     _______\n");
    printf("________________________________________\n");
    scanf("%d",&choix);
    getchar();
    printf("________________________________________\n");

}

int motedepasse(char mdp[] , char username[]){
     int n = strlen(mdp);
     if(n<8)
        return 0;
    int a=0,b=0,c=0,d=0;
    for(int i=0;i<n;i++){
        if(isupper(mdp[i])){
            a=1;
        }else if(islower(mdp[i])){
            b=1;
        }else if(isdigit(mdp[i])){
            c=1;
        }else{ 
            d=1;
        }
    }
    if(!a || !b || !c || !d ){
        return 0;
        printf("utiliser les alphabet et les chifres et les symboles");
    }
    if(strstr(mdp,username)!=NULL){
        printf("ne utiliser pas le nom dans pasword\n");
        return 0;
    }   
    return 1;
}
int username(char *name){
    for(int i=0;i<user_nb;i++){
        if(strcmp(users[i].name,name)==0){
            return 1 ;
        }
    }
    return 0;
}
void signup() {
    char username[50];
    char mdp[50]; 
    printf("Nom d'utilisateur : ");
    scanf("%s",username);
    printf("Mot de passe : ");
    scanf("%s",mdp);
    if (motedepasse(mdp, username)!=1) {
        printf("Mot de passe invalide\n");
        return;
    }
    strcpy(users[user_nb].name, username);
    strcpy(users[user_nb].mdp, mdp);
    strcpy(users[user_nb].role, "Client");
    user_nb++;
    printf("Inscription reussie\n");
}

int signin(){
    char username[50];
    char mdp[50];
    int tentative=0 ;

    while (tentative < 3) {
        printf("Nom d'utilisateur : ");
        fgets(username,50,stdin);
        printf("Mot de passe : ");
        fgets(mdp,50,stdin);
        for (int i = 0; i < user_nb; i++) {
            if (strcmp(users[i].name, username) == 0 && strcmp(users[i].mdp, mdp) == 0) {
                return i;
            }
        }
        tentative++;
        printf("Nom d'utilisateur ou mot de passe incorrect\n");
    }
    printf("Compte verrouille\n");
    return -1;
        
}

void ordre_priorit(reclamation* reclamation) {
    if (strstr(reclamation->description, "urgent") != NULL || strstr(reclamation->motif, "grave") != NULL)
        strcpy(reclamation->priority, "haute");
    else if (strstr(reclamation->description, "important") != NULL || strstr(reclamation->motif, "modéré") != NULL)
        strcpy(reclamation->priority, "moyenne");
    else
        strcpy(reclamation->priority, "basse");
}

void ajouter_reclamation(char* username) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    reclamations[reclamation_nb].id = reclamation_nb + 1;
    strcpy(reclamations[reclamation_nb].name, username);
    printf("ajouter un motif : ");
    fgets(reclamations[reclamation_nb].motif,50,stdin);
    printf("ajouter une description : ");
    fgets(reclamations[reclamation_nb].description,200,stdin);
    printf("ajouter une categorie : ");
    fgets(reclamations[reclamation_nb].categorie,50,stdin);
    strcpy(reclamations[reclamation_nb].status, "en attente");
    sprintf(reclamations[reclamation_nb].date, "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    ordre_priorit(&reclamations[reclamation_nb]);
    reclamation_nb++;
    printf("Reclamation ajoutee\n");
}

void afficherreclamation() {
    int i;
    if (reclamation_nb==0)
    printf("il ya aucune reclamation");
    for (i = 0; i < reclamation_nb; i++) {

        printf("ID: %d, Username: %s, Motif: %s, Description: %s, Categorie: %s, Statut: %s, Date: %s, Priorite: %s\n",
            reclamations[i].id, reclamations[i].name, reclamations[i].motif, reclamations[i].description,
            reclamations[i].categorie, reclamations[i].status, reclamations[i].date, reclamations[i].priority);
    }
}

void modifier_reclamation() {
    int id, i;
    printf("ID de la reclamation a modifier : ");
    scanf("%d", &id);
    getchar();
    for (i = 0; i < reclamation_nb ; i++) {
        if (reclamations[i].id == id)  {
                printf("modifier un motif : ");
                fgets(reclamations[i].motif,50,stdin);
                printf("modifier une description : ");
                fgets(reclamations[i].description,200,stdin);
                printf("modifier une categorie : ");
                fgets(reclamations[i].categorie,50,stdin);
                printf("modifier status");
                fgets(reclamations[i].status,50,stdin);
            printf("reclamation modifiee\n");
            return;
        }
    }
    printf("reclamation non trouvee ou acces refuse\n");
}
int espaceadmin(){
    char nom[50];
    char mdp[50];
    printf("Nom d'admin : ");
    scanf("%s",nom);
    printf("Mot de passe : ");
    scanf("%s",mdp);

    if(strcmp(nom,"admin")==0 && strcmp(mdp,"Admin@1234")==0){
            printf("bonjour admin\n");
            return 1 ;
    }else{
        printf("Nom d'utilisateur ou mot de passe incorrect\n");
        return 0;
    }
    
}

void menuadmin(){
    printf("________________________________________\n");
    printf("___________       MENU       ___________\n");
    printf("________________________________________\n");
    printf(" 1. Ajouter  reclamation________________\n");
    printf(" 2. Afficher reclamations_______________\n");
    printf(" 3. Modifier reclamation________________\n");
    printf(" 4. Traiter  reclamation________________\n");
    printf(" 5. Rechercher reclamation______________\n");
    printf(" 6. Afficher par priorite_______________\n");
    printf(" 7. Statistiques________________________\n");
    printf(" 8. Rapport journalier__________________\n");
    printf(" 9. Deconnexion_________________________\n");
    printf("________________________________________\n");
    printf("_______     choiser un choix     _______\n");
    printf("________________________________________\n");
    scanf("%d", &choix); 
    getchar();   
}

void traiter_reclamation() {
    int id, i;
    printf("ID de la reclamation a traiter : ");
    scanf("%d", &id);
    for (i = 0; i < reclamation_nb; i++) {
        if (reclamations[i].id == id) {
            printf("Changer le statut : ");
            fgets(reclamations[i].status,50,stdin);
            printf("reclamation traitee\n");
            return;
        }
    }
    printf("reclamation non trouvee\n");
}


void recherch_Reclamation() {
    int id, i;
    printf("ID de la réclamation à rechercher : ");
    scanf("%d", &id);
    for (i = 0; i < reclamation_nb; i++) {
        if (reclamations[i].id == id) {
            printf("ID: %d\n, Utilisateur: %s\n Motif: %s\n Description: %s\n Catégorie: %s\n Statut: %s\n Date: %s\n",
                reclamations[i].id, reclamations[i].name, reclamations[i].motif, reclamations[i].description,
                reclamations[i].categorie, reclamations[i].status, reclamations[i].date);
            return;
        }
    }
    printf("Réclamation non trouvée\n");
}


int main(){
    char role[50];
    char username[50];
    int new;


    do{
        menu();
        switch (choix){
        case 1:
                signup();
            break;
        case 2:
                signin();
            break;
        case 3 : 
               if(espaceadmin()==1){

                    do{
                        menuadmin();
                        switch (choix){
                            case 1:
                                    strcpy(username,"admin");
                                    ajouter_reclamation(username);
                                break;
                            case 2:
                                    afficherreclamation();
                                break;
                            case 3 : 
                                modifier_reclamation();
                                break;
                            case 4:
                                traiter_reclamation();
                                break;
                            case 5:
                                afficherreclamation();
                                break;
                            case 6:

                                break;
                            case 7:
                                break;
                            case 8:
                                break;
                            case 9:
                                break;
                            default:
                                break;
                        }
                    } while (choix !=9 );
    
               }
            break;
        case 4:
               new = signin();
               strcpy(username, users[new].name);
                printf("Bonjour, %s \n", username);
                

                for(int i=0;i<user_nb;i++){
                    if(strcmp(users[i].role,"Client")==0){
                        printf("menu clt");
                    }
                }
            break;
        case 5:
               new = signin();
               strcpy(username, users[new].name);
                printf("Bonjour, %s \n", username);
                

                for(int i=0;i<user_nb;i++){
                    if(strcmp(users[i].role,"Agent")==0){
                        printf("menu clt");
                    }
                }
            break;
        case 6:
                printf("Quitter");
        default:
            break;
        }
    } while (choix !=6 );
    
}
