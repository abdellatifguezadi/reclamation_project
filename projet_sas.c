#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>


typedef struct{
    char name[30];
    char prenom[30];
}user;

typedef struct{
    int id;
    char motif[100];
    char description[200];
    char categorie [50];
    char status[50];
    char date[20]
}reclamation;

user *users = NULL;
reclamation *reclamations = NULL;
int user_nb =0;
int reclamation_nb = 0;

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
}

