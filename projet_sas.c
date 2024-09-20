#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
#define max_users 100


typedef struct{
    char name[30];
    char role[30];
    char mdp[30];
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
reclamation *reclamations = NULL;
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

int motedepasse(char *mdp , char *username){
     int n = strlen(mdp);
     if(n<8)
        return 0;
    if(strstr(mdp,username)!=NULL)
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
    if((a=1) && (b=1) && (c=1) && (d=1) ){
        return 1;
    }else{
        return 0 ;
    }
}
int username(char *name){
    for(int i=0;i<user_nb;i++){
        if(strcmp(users[i].name,name)==0){
            return 1 ;
        }
    }
    return 0;
}

void signup(){
    user nv_user;
    int count=0;
    while (count <3) {
        printf("saiser nom d'utilisateur :  ");
        fgets(nv_user.name,50,stdin);
        int ind=0;
        if (username(nv_user.name)==1){
           printf("nom deja utiliser\n");
           count++;
           ind++;
           continue;
        }
        printf("saiser mote de passe\n");
        fgets(nv_user.name,50,stdin);
        
        if (motedepasse(nv_user.mdp,nv_user.name)==0){
           printf("le mote de passe est invalide\n");
            count++;
            ind++;
        }
        users[user_nb++]=nv_user;
        if(ind == 0){
           printf("inscription reussie\n");
           strcpy(nv_user.role,"client");
           break;
        }
    } 
    
}

void signin(){
        char username[50];
        char mdp[50];
        int tentative=0 ;
        printf("entrer nom d'utilisateur");
        fgets(username,50,stdin);
        int ind = -1 ;
        for(int i=0; i<user_nb ; i++){
            if(strcmp(users[i].name,username)==0){
                ind=i;
                break;
            }
        }
        if(ind = -1){
            printf(" le nom d'utilisateur introvable");
            return;
        }

        do
        {
        printf("entrer le mote de passe ");
        fgets(mdp,50,stdin);
            if(strcmp(users[ind].mdp,mdp)==0){
                printf("connexion reussie");
                 return;
            }else{
                 printf("mote de passe inccorect il reste que %d tentative", 2-tentative);
            }
        } while (tentative=2);
        
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
    scanf(reclamations[reclamation_nb].description,200,stdin);
    printf("ajouter une categorie : ");
    scanf(reclamations[reclamation_nb].categorie,50,stdin);
    strcpy(reclamations[reclamation_nb].status, "en attente");
    sprintf(reclamations[reclamation_nb].date, "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    ordre_priorit(&reclamations[reclamation_nb]);
    reclamation_nb++;
    printf("Réclamation ajoutee\n");
}

int main(){
    
    do{
        menu();
        switch (choix){
        case 1:
            signup();
            break;
        case 2:
            signin();
            break;
        case 3:
            printf("Quitter");
        default:
            break;
        }
    } while (choix !=3 );
    
}

