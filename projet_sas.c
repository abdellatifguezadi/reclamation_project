#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
#define max_users 100


typedef struct{
    char name[30];
    char prenom[30];
    char role[30];
    char mdp[30];
}user;

typedef struct{
    int id;
    char motif[100];
    char description[200];
    char categorie [50];
    char status[50];
    char date[20];
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
        printf("saiser username :  ");
        scanf("%s",nv_user.name);
        int ind=0;
        if (username(nv_user.name)==1){
           printf("username deja utiliser\n");
           count++;
           ind++;
           continue;
        }
        printf("saiser mote de passe\n");
        scanf("%s",nv_user.mdp);
        
        if (motedepasse(nv_user.mdp,nv_user.name)==0){
           printf("le mote de passe est invalide\n");
            count++;
            ind++;
        }
        users[user_nb++]=nv_user;
        if(ind == 0){
           printf("inscription reussie\n");
           break;
        }
    } 
    
}

int main(){
    
    do{
        menu();
        switch (choix){
        case 1:
            signup();
            break;
        case 6:
            printf("quitter");
        default:
            break;
        }
    } while (choix !=6 );
    
}

