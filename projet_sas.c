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
    char date[50];
    char date_r[20];
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
    printf(" 1  : Sign Up \n");
    printf(" 2  : Espace admin\n");
    printf(" 3  : Espace agent de reclamation\n");
    printf(" 4  : Espace client\n");
    printf(" 5 : Quitter\n");
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
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;
    printf("Mot de passe : ");
    fgets(mdp, sizeof(mdp), stdin);
    mdp[strcspn(mdp, "\n")] = 0;
    if (motedepasse(mdp, username) != 1) {
        printf("Mot de passe invalide\n");
        return;
    }
    strcpy(users[user_nb].name, username);
    strcpy(users[user_nb].mdp, mdp);
    strcpy(users[user_nb].role, "Client");
    user_nb++;
    printf("Inscription réussie\n");
}

#include <unistd.h>

int signin() {
    char username[50];
    char mdp[50];
    int tentative = 0;
    while (tentative < 3) {
        printf("Nom d'utilisateur : ");
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = 0;
        printf("Mot de passe : ");
        fgets(mdp, sizeof(mdp), stdin);
        mdp[strcspn(mdp, "\n")] = 0;
        for (int i = 0; i < user_nb; i++) {
            if (strcmp(users[i].name, username) == 0 && strcmp(users[i].mdp, mdp) == 0) {
                return i;
            }
        }
        tentative++;
        printf("Nom d'utilisateur ou mot de passe incorrect\n");
    }
    printf("Compte verrouille. Attendez 5 minutes...\n");
    sleep(5 * 60);
    return -1;
}



void ordre_priorit(reclamation *rec) {
    if (strstr(rec->description, "urgent") != NULL ||
        strstr(rec->motif, "grave") != NULL ||
        strstr(rec->description, "argent") != NULL ||
        strstr(rec->description, "critique") != NULL ||
        strstr(rec->description, "securite") != NULL) {
        strcpy(rec->priority, "haute");
    } else if (strstr(rec->description, "important") != NULL ||
               strstr(rec->motif, "modere") != NULL ||
               strstr(rec->description, "important") != NULL ||
               strstr(rec->description, "necessaire") != NULL) {
        strcpy(rec->priority, "moyenne");
    } else {
        strcpy(rec->priority, "basse");
    }
}


void ajouter_reclamation(char username[]) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    reclamations[reclamation_nb].id = reclamation_nb + 1;
    strcpy(reclamations[reclamation_nb].name, username);
    strcpy( users[reclamation_nb].name , reclamations[reclamation_nb].name);
    
    printf("ajouter un motif : ");
    fgets(reclamations[reclamation_nb].motif, 50, stdin);
    reclamations[reclamation_nb].motif[strcspn(reclamations[reclamation_nb].motif, "\n")] = 0;

    printf("ajouter une description : ");
    fgets(reclamations[reclamation_nb].description, 200, stdin);
    reclamations[reclamation_nb].description[strcspn(reclamations[reclamation_nb].description, "\n")] = 0;

    printf("ajouter une categorie : ");
    fgets(reclamations[reclamation_nb].categorie, 50, stdin);
    reclamations[reclamation_nb].categorie[strcspn(reclamations[reclamation_nb].categorie, "\n")] = 0;

    strcpy(reclamations[reclamation_nb].status, "en cours");    
    sprintf(reclamations[reclamation_nb].date, "%02d-%02d-%04d %02d:%02d:%02d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    sprintf(reclamations[reclamation_nb].date_r, "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    
    ordre_priorit(&reclamations[reclamation_nb]);
    reclamation_nb++;
    printf("Reclamation ajoutee\n");
}


void afficherreclamation() {
    int i;
    if (reclamation_nb==0)
    printf("il ya aucune reclamation");
    for (i = 0; i < reclamation_nb; i++) {

        printf("ID: %d, nom: %s, motif: %s, description: %s, categorie: %s, statut: %s, date: %s, priorite: %s\n",
            reclamations[i].id, reclamations[i].name, reclamations[i].motif, reclamations[i].description,
            reclamations[i].categorie, reclamations[i].status, reclamations[i].date, reclamations[i].priority);
    }
}

void modifier_reclamation() {
    int id, i;
    printf("ID de la reclamation a modifier : ");
    scanf("%d", &id);
    getchar();
    for (i = 0; i < reclamation_nb; i++) {
        if (reclamations[i].id == id)  {
            printf("modifier un motif : ");
            fgets(reclamations[i].motif, 50, stdin);
            reclamations[i].motif[strcspn(reclamations[i].motif, "\n")] = 0;

            printf("modifier une description : ");
            fgets(reclamations[i].description, 200, stdin);
            reclamations[i].description[strcspn(reclamations[i].description, "\n")] = 0;

            printf("modifier une categorie : ");
            fgets(reclamations[i].categorie, 50, stdin);
            reclamations[i].categorie[strcspn(reclamations[i].categorie, "\n")] = 0;

            printf("modifier status : ");
            fgets(reclamations[i].status, 50, stdin);
            reclamations[i].status[strcspn(reclamations[i].status, "\n")] = 0;

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
    printf(" 1. Ajouter  reclamation\n");
    printf(" 2. Afficher reclamations\n");
    printf(" 3. Modifier reclamation\n");
    printf(" 4. Traiter  reclamation\n");
    printf(" 5. Rechercher reclamation\n");
    printf(" 6. trie par priorite\n");
    printf(" 7. Statistiques\n");
    printf(" 8. Supprimer reclamation\n");
    printf(" 9. Deconnexion\n");
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
    getchar();
    for (i = 0; i < reclamation_nb; i++) {
        if (reclamations[i].id == id) {
            printf("Changer le statut : ");
            fgets(reclamations[i].status, 50, stdin);
            reclamations[i].status[strcspn(reclamations[i].status, "\n")] = 0;
            printf("reclamation traitee\n");
            return;
        }
    }
    printf("reclamation non trouvee\n");
}


void recherchid_Reclamation() {
    int id, i , trouve=0;
    printf("ID de la reclamation a rechercher : ");
    scanf("%d", &id);
    getchar();
    for (i = 0; i < reclamation_nb; i++) {
        if (reclamations[i].id == id) {
            printf("ID: %d\n, nom: %s\n motif: %s\n description: %s\n categorie: %s\n statut: %s\n date: %s\n",
                reclamations[i].id, reclamations[i].name, reclamations[i].motif, reclamations[i].description,
                reclamations[i].categorie, reclamations[i].status, reclamations[i].date);
            trouve++;
        }
    }
    if (trouve==0) {
        printf("reclamation non trouvee\n");
    }
}
void recherchname_Reclamation() {
    char name[50];
    int trouve = 0;
    getchar();
    printf("reclamation username : ");
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = 0;

    for (int i = 0; i < reclamation_nb; i++) {
        if (strcmp(reclamations[i].name, name) == 0) {
            printf("ID: %d\n, nom: %s\n motif: %s\n description: %s\n categorie: %s\n statut: %s\n date: %s\n",
                   reclamations[i].id, reclamations[i].name, reclamations[i].motif, reclamations[i].description,
                   reclamations[i].categorie, reclamations[i].status, reclamations[i].date);
            trouve++;
        }
    }
    
    if (trouve == 0) {
        printf("reclamation non trouvee\n");
    }
}

void recherchdate_Reclamation() {
    char date[20];
    int trouve = 0;
    getchar();
    printf("date de la reclamation a rechercher : ");
    fgets(date, 20, stdin);
    date[strcspn(date, "\n")] = 0;

    for (int i = 0; i < reclamation_nb; i++) {
        if (strcmp(reclamations[i].date_r, date) == 0) {
            printf("ID: %d\n, nom: %s\n motif: %s\n description: %s\n categorie: %s\n statut: %s\n date: %s\n",
                   reclamations[i].id, reclamations[i].name, reclamations[i].motif, reclamations[i].description,
                   reclamations[i].categorie, reclamations[i].status, reclamations[i].date);
            trouve++;
        }
    }

    if (trouve == 0) {
        printf("reclamation non trouvee\n");
    }
}

void recherchstatut_Reclamation() {
    char statut[50];
    int trouve = 0;
    getchar();
    printf("statut de la reclamation a rechercher (en cours, resolu, rejete) : ");
    fgets(statut, 50, stdin);
    statut[strcspn(statut, "\n")] = 0;

    for (int i = 0; i < reclamation_nb; i++) {
        if (strcmp(reclamations[i].status, statut) == 0) {
            printf("ID: %d\n, nom: %s\n motif: %s\n description: %s\n categorie: %s\n statut: %s\n date: %s\n",
                   reclamations[i].id, reclamations[i].name, reclamations[i].motif, reclamations[i].description,
                   reclamations[i].categorie, reclamations[i].status, reclamations[i].date);
            trouve++;
        }
    }

    if (trouve == 0) {
        printf("reclamation non trouvee\n");
    }
}


void recherchcategorie_Reclamation() {
    char categorie[50];
    int trouve = 0;
    getchar();
    printf("categorie de la reclamation a rechercher : ");
    fgets(categorie, 50, stdin);
    categorie[strcspn(categorie, "\n")] = 0;

    for (int i = 0; i < reclamation_nb; i++) {
        if (strcmp(reclamations[i].categorie, categorie) == 0) {
            printf("ID: %d\n, nom: %s\n motif: %s\n description: %s\n categorie: %s\n statut: %s\n date: %s\n",
                   reclamations[i].id, reclamations[i].name, reclamations[i].motif, reclamations[i].description,
                   reclamations[i].categorie, reclamations[i].status, reclamations[i].date);
            trouve++;
        }
    }

    if (trouve == 0) {
        printf("reclamation non trouvee\n");
    }
}


void trier_Priorite() {
    int i, j;
    reclamation temp;

    for (i = 0; i < reclamation_nb - 1; i++) {
        for (j = 0; j < reclamation_nb - i - 1; j++) {
            if (strcmp(reclamations[j].priority, "basse") == 0 && 
                (strcmp(reclamations[j + 1].priority, "moyenne") == 0 || 
                 strcmp(reclamations[j + 1].priority, "haute") == 0)) {
                temp = reclamations[j];
                reclamations[j] = reclamations[j + 1];
                reclamations[j + 1] = temp;
            } else if (strcmp(reclamations[j].priority, "moyenne") == 0 && 
                       strcmp(reclamations[j + 1].priority, "haute") == 0) {
                temp = reclamations[j];
                reclamations[j] = reclamations[j + 1];
                reclamations[j + 1] = temp;
            }
        }
    }

    printf("Le tri par priorité est terminé\n");
}

void afficher_statistiques() {
    int total_rec = reclamation_nb;
    int rec_resolues = 0;
    int rec_rejete = 0;
    int rec_cours = 0;

    for (int i = 0; i < reclamation_nb; i++) {
        if (strcmp(reclamations[i].status, "resolue") == 0)
            rec_resolues++;
        if (strcmp(reclamations[i].status, "rejete") == 0)
            rec_rejete++;
        if (strcmp(reclamations[i].status, "en cours") == 0)
            rec_cours++;
    }

    printf("total des reclamations : %d\n", total_rec);
    printf("reclamations resolues : %d\n", rec_resolues);
    printf("reclamations rejete : %d\n", rec_rejete);
    printf("reclamations en cours : %d\n", rec_cours);
}

void supprimer_reclamation() {
    int id ;
    printf("ID de la reclamation a rechercher : ");
    scanf("%d",&id);
    int index = -1;
    for (int i = 0; i < reclamation_nb; i++) {
        if (reclamations[i].id == id) {
            index = i;
            break;
        }
    }
    if (index != -1) {
        for (int i = index; i < reclamation_nb - 1; i++) {
            reclamations[i] = reclamations[i + 1];
        }
        reclamation_nb--;
        printf("reclamation supprimee avec succès.\n");
    } else {
        printf("reclamation introuvable.\n");
    }
}

void rapport_journalier() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char date_aujourdhui[20];
    sprintf(date_aujourdhui, "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    printf("Rapport journalier pour le %s :\n", date_aujourdhui);
    printf("Nouvelles réclamations :\n");

    int nouvelles_reclamations = 0;
    int reclamations_traitees = 0;

    for (int i = 0; i < reclamation_nb; i++) {
        if (strcmp(reclamations[i].date_r, date_aujourdhui) == 0) {
            printf("ID: %d, Nom: %s, Motif: %s, Description: %s, Catégorie: %s, Statut: %s, Priorité: %s\n",
                   reclamations[i].id, reclamations[i].name, reclamations[i].motif, reclamations[i].description,
                   reclamations[i].categorie, reclamations[i].status, reclamations[i].priority);
            nouvelles_reclamations++;
        }
    }
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
                                printf("pour recherche par ID choiser 1 et par name choiser 2 et pare date 3 et par categorie choiser 4 et par status choiser 5  ");
                                int ch ;
                                scanf("%d",&ch);
                                switch (ch)
                                {
                                    case 1 :
                                            recherchid_Reclamation();
                                        break;
                                    case 2 :
                                            recherchname_Reclamation();
                                        break;
                                    case 3 :
                                            recherchdate_Reclamation();
                                        break;
                                    case 4 :
                                            recherchcategorie_Reclamation();
                                        break;
                                    case 5 :
                                            recherchstatut_Reclamation();
                                        break;
                                    default:
                                            printf("le choix est invalide");
                                        break;
                                }
                                break;
                            case 6:
                                trier_Priorite();
                                break;
                            case 7:
                                afficher_statistiques();
                                break;
                            case 8:
                                supprimer_reclamation();
                                break;
                            case 9:
                                break;
                            default:
                                printf("le choix est invalide");
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
                        printf("menu agent");
                    }
                }
            break;
        case 6:
                printf("Quitter");
        default:
                printf("le choix est invalide");
            break;
        }
    } while (choix !=6 );
    
}
