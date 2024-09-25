#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
#include<unistd.h>
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
    time_t date_ajt ;
    time_t date_traitement;
    char priority[50];
    char note[200];
}reclamation;

user users[max_users] ;
reclamation reclamations[max_rec];
int user_nb =0;
int reclamation_nb = 0;
int choix , ch1;

void menu(){
    printf("________________________________________\n");
    printf("___________       MENU       ___________\n");
    printf("________________________________________\n");
    printf(" 1  : Sign Up \n");
    printf(" 2  : Espace admin\n");
    printf(" 3  : Espace client\n");
    printf(" 4  : Espace agent de reclamation\n");
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
    if(n<8){
        printf("pasword invalide\n");
        return 0;
    }
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
        printf("utiliser les alphabet et les chifres et les symboles\n");
        return 0;
        
    }
    char mdp_p[100];
    char username_p[100];
    strcpy(mdp_p, mdp);
    strcpy(username_p, username);
    
    int m_p = strlen(mdp_p);
    int n_p = strlen(username_p);
    
    for (int i = 0; i < m_p; i++) {
        mdp_p[i] = tolower(mdp_p[i]);
    }
    for (int i = 0; i < n_p; i++) {
        username_p[i] = tolower(username_p[i]);
    }

    if (strstr(mdp_p, username_p) != NULL) {
        printf("Ne pas utiliser le nom dans le mot de passe\n");
        return 0;
    }
    
    return 1;
}

int verifiername(char *name){
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
    if(verifiername(username)==1) {
        printf("Nom invalide\n");
        return;
    }
    printf("Mot de passe : ");
    fgets(mdp, sizeof(mdp), stdin);
    mdp[strcspn(mdp, "\n")] = 0;
    if (motedepasse(mdp, username) != 1) {
        return;
    }
    strcpy(users[user_nb].name, username);
    strcpy(users[user_nb].mdp, mdp);
    strcpy(users[user_nb].role, "Client");
    user_nb++;
    printf("Inscription reussie\n");
}

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
    sleep(30);
    return -1;
}

void ordre_priorit(reclamation rec[], int index) {
    if (strstr(rec[index].description, "urgent") != NULL ||
        strstr(rec[index].motif, "grave") != NULL ||
        strstr(rec[index].description, "argent") != NULL ||
        strstr(rec[index].description, "critique") != NULL ||
        strstr(rec[index].description, "securite") != NULL) {
        strcpy(rec[index].priority, "haute");
    } else if (strstr(rec[index].description, "important") != NULL ||
               strstr(rec[index].motif, "modere") != NULL ||
               strstr(rec[index].description, "rappel") != NULL ||
               strstr(rec[index].description, "necessaire") != NULL) {
        strcpy(rec[index].priority, "moyenne");
    } else {
        strcpy(rec[index].priority, "basse");
    }
}

void ajouter_reclamation(char username[]) {
     if (reclamation_nb >= max_rec) {
        printf("aucune espace pour nouvelle reclamation\n");
        return;
    }
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    reclamations[reclamation_nb].id = rand() % 10000 + 1;
    strcpy(reclamations[reclamation_nb].name, username);
    
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
    sprintf(reclamations[reclamation_nb].date, "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    reclamations[reclamation_nb].date_ajt = time(NULL);
    ordre_priorit(reclamations, reclamation_nb);
    reclamation_nb++;
    printf("Reclamation ajoutee\n");
}

void afficherreclamation() {
    int i;
    if (reclamation_nb==0)
    printf("il ya aucune reclamation\n");
    for (i = 0; i < reclamation_nb; i++) {

        printf("ID: %d, nom: %s, motif: %s, description: %s, categorie: %s, statut: %s, date: %s, priorite: %s\n",
            reclamations[i].id, reclamations[i].name, reclamations[i].motif, reclamations[i].description,
            reclamations[i].categorie, reclamations[i].status, reclamations[i].date, reclamations[i].priority);

        if(strcmp(reclamations[i].status,"en cours") !=0){
            printf("note : %s\n",reclamations[i].note);
        }
    }
}

void afficherreclamationclient(char username[]) {
    int i;
    int trouve = 0;
    if (reclamation_nb == 0) {
        printf("Il n'y a aucune reclamation.\n");
    } else {
        for (i = 0; i < reclamation_nb; i++) {
            if (strcmp(username, reclamations[i].name) == 0) {
                trouve = 1;
                printf("ID: %d, nom: %s, motif: %s, description: %s, categorie: %s, statut: %s, date: %s\n",
                    reclamations[i].id, reclamations[i].name, reclamations[i].motif, reclamations[i].description,
                    reclamations[i].categorie, reclamations[i].status, reclamations[i].date);
            }
            if(strcmp(reclamations[i].status,"en cours") !=0){
            printf("note : %s\n",reclamations[i].note);
        }
        }
        if (trouve==0) {
            printf("Aucune réclamation trouvée pour l'utilisateur %s.\n", username);
        }
    }
}

void modifier_reclamation() {
    int id, i, s, ind=0;
    printf("ID de la reclamation a modifier : ");
    scanf("%d", &id);
    getchar();
    for (i = 0; i < reclamation_nb; i++) {
        if (reclamations[i].id == id)  {
            ind++;
            printf("pour changer le motif : 1\npour changer description: 2\npour changer categorie  : 3\npour changer tous : 4\n");
            scanf("%d",&s);
            getchar();
            if(s==1){
                printf("modifier un motif : ");
                fgets(reclamations[i].motif, 50, stdin);
                reclamations[i].motif[strcspn(reclamations[i].motif, "\n")] = 0;
                printf("reclamation modifiee\n");
                ordre_priorit(reclamations, i);
            }else if(s==2){
                printf("modifier une description : ");
                fgets(reclamations[i].description, 200, stdin);
                reclamations[i].description[strcspn(reclamations[i].description, "\n")] = 0;
                printf("reclamation modifiee\n");
                ordre_priorit(reclamations, i);
            }else if(s==3){
                printf("modifier une categorie : ");
                fgets(reclamations[i].categorie, 50, stdin);
                reclamations[i].categorie[strcspn(reclamations[i].categorie, "\n")] = 0;
                printf("reclamation modifiee\n");
            }else if(s==4){
                printf("modifier un motif : ");
                fgets(reclamations[i].motif, 50, stdin);
                reclamations[i].motif[strcspn(reclamations[i].motif, "\n")] = 0;
                printf("modifier une description : ");
                fgets(reclamations[i].description, 200, stdin);
                reclamations[i].description[strcspn(reclamations[i].description, "\n")] = 0;
                printf("modifier une categorie : ");
                fgets(reclamations[i].categorie, 50, stdin);
                reclamations[i].categorie[strcspn(reclamations[i].categorie, "\n")] = 0;
                printf("reclamation modifiee\n");
                ordre_priorit(reclamations, i);
            }else{
                printf("le choix est invalide\n");
            }
            return;
        }
    }
    if(ind==0){
        printf("reclamation non trouvee \n");
    }
    
}

int espaceadmin(){
    char nom[50];
    char mdp[50];
    printf("Nom d'admin : ");
    scanf("%s",nom);
    printf("Mot de passe : ");
    scanf("%s",mdp);

    if(strcmp(nom,"admin")==0 && strcmp(mdp,"admin@1234")==0){
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
    printf(" 7. Supprimer reclamation\n");
    printf(" 8. Changer de role\n");
    printf(" 9. Statistique\n");
    printf(" 10. Deconnexion\n");
    printf("________________________________________\n");
    printf("_______     choiser un choix     _______\n");
    printf("________________________________________\n");
    scanf("%d", &ch1); 
    getchar();   
}

void menuagent(){
    printf("________________________________________\n");
    printf("___________       MENU       ___________\n");
    printf("________________________________________\n");
    printf(" 1. Ajouter  reclamation\n");
    printf(" 2. Afficher reclamations\n");
    printf(" 3. Modifier reclamation\n");
    printf(" 4. Traiter  reclamation\n");
    printf(" 5. Rechercher reclamation\n");
    printf(" 6. Supprimer reclamation\n");
    printf(" 7. Deconnexion\n");
    printf("________________________________________\n");
    printf("_______     choiser un choix     _______\n");
    printf("________________________________________\n");
    scanf("%d", &ch1); 
    getchar();   
}

void menuclient(){
    printf("________________________________________\n");
    printf("___________       MENU       ___________\n");
    printf("________________________________________\n");
    printf(" 1. Ajouter  reclamation\n");
    printf(" 2. Afficher reclamations\n");
    printf(" 3. Supprimer reclamation\n");
    printf(" 4. Modifier reclamation\n");
    printf(" 5. Deconnexion\n");
    printf("________________________________________\n");
    printf("_______     choiser un choix     _______\n");
    printf("________________________________________\n");
    scanf("%d", &ch1); 
    getchar();   
}

void traiter_reclamation() {
    int id, i,s,d=0;
    printf("ID de la reclamation a traiter : ");
    scanf("%d", &id);
    getchar();
    for (i = 0; i < reclamation_nb; i++) {
        if ((reclamations[i].id == id)) {
            printf("Changer le statut choiser 1 pour rejete et 2 resoule : ");
            scanf("%d",&s);
            getchar();
            if(s==1){
                strcpy(reclamations[i].status,"rejete");
                d++;
                printf("ajouter une note : ");
                fgets(reclamations[i].note,200,stdin);
                reclamations[i].note[strcspn(reclamations[i].note,"\n")]=0;
            }else if(s==2){
                strcpy(reclamations[i].status,"resolue");
                d++;
                printf("ajouter une note : ");
                fgets(reclamations[i].note,200,stdin);
                reclamations[i].note[strcspn(reclamations[i].note,"\n")]=0;
            }else{
                printf("le choix est invalide\n");
            }
            if(d !=0){
            reclamations[i].date_traitement = time(NULL);
            }
            return;
        }
    }
    printf("reclamation non trouvee \n");
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
        if (strcmp(reclamations[i].date, date) == 0) {
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
    printf("statut de la reclamation a rechercher (en cours, resolue, rejete) : ");
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

void afficher_Priorite() {
    int i, j;
 reclamation temp;

    printf("Le tri par priorit est termine\n");
    for (i = 0; i < reclamation_nb; i++) {
        if(strcmp(reclamations[i].priority, "haute") == 0){
            printf("ID: %d, nom: %s, motif: %s, description: %s, categorie: %s, statut: %s, date: %s, priorite: %s\n",
                reclamations[i].id, reclamations[i].name, reclamations[i].motif, reclamations[i].description,
                reclamations[i].categorie, reclamations[i].status, reclamations[i].date, reclamations[i].priority);
        }
    }
    for (i = 0; i < reclamation_nb; i++) {
        if(strcmp(reclamations[i].priority, "moyenne") == 0){
            printf("ID: %d, nom: %s, motif: %s, description: %s, categorie: %s, statut: %s, date: %s, priorite: %s\n",
                reclamations[i].id, reclamations[i].name, reclamations[i].motif, reclamations[i].description,
                reclamations[i].categorie, reclamations[i].status, reclamations[i].date, reclamations[i].priority);
        }
    }
    for (i = 0; i < reclamation_nb; i++) {
         if(strcmp(reclamations[i].priority, "basse") == 0){
            printf("ID: %d, nom: %s, motif: %s, description: %s, categorie: %s, statut: %s, date: %s, priorite: %s\n",
                reclamations[i].id, reclamations[i].name, reclamations[i].motif, reclamations[i].description,
                reclamations[i].categorie, reclamations[i].status, reclamations[i].date, reclamations[i].priority);
         }
    }
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

   printf("Total des reclamations : %d\n", total_rec);

if (total_rec > 0) {
    printf("Reclamations resolues : %d (%.2f%%)\n", rec_resolues, (rec_resolues / (float)total_rec) * 100);
    printf("Reclamations rejete : %d (%.2f%%)\n", rec_rejete, (rec_rejete / (float)total_rec) * 100);
    printf("Reclamations en cours : %d (%.2f%%)\n", rec_cours, (rec_cours / (float)total_rec) * 100);
} else {
    printf("Aucune reclamation pour calculer le taux.\n");
    printf("Reclamations resolues : %d (0,00%%) \n", rec_resolues);
    printf("Reclamations rejete : %d (0,00%%)\n", rec_rejete);
    printf("Reclamations en cours : %d (0,00%%)\n", rec_cours);
}
}

void supprimer_reclamation() {
    int id ;
    printf("ID de la reclamation a supprimer : ");
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
        printf("reclamation supprimee \n");
    } else {
        printf("reclamation introuvable.\n");
    }
}

void changetrole(){
    int i;
    char name[50];
    char role[50];
    printf("Entrez le nom : ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; 

    for(i = 0; i < user_nb; i++){
        if (strcmp(name, users[i].name) == 0){
            strcpy(users[i].role,"Agent");
            printf("Role mis a jour avec succes.\n");
            return; 
        }
    }
    printf("nom non trouve.\n");
}

void supprimer_reclamationclient(char username[]) {
    int id;
    time_t now = time(NULL);
    printf("ID de la reclamation a supprimer : ");
    scanf("%d", &id);
    getchar();
    int ind = -1;

    for (int i = 0; i < reclamation_nb; i++) {
        if (reclamations[i].id == id && strcmp(reclamations[i].name, username) == 0 && strcmp(reclamations[i].status,"en cours")==0) {
            double diff = difftime(now, reclamations[i].date_ajt );
            if (diff <= 24*3600) {
                ind = i;
                break;
            } else {
                printf("la reclamation a plus de 24 heures\n");
                return;
            }
        }
    }

    if (ind != -1) {
        for (int i = ind; i < reclamation_nb - 1; i++) {
            reclamations[i] = reclamations[i + 1];
        }
        reclamation_nb--;
        printf("reclamation supprimee \n");
    } else {
        printf("reclamation non trouvee ou acces refuse\n");
    }
}

void modifier_reclamationclient(char username[]) {
    int id, i, s , ind=0;
    time_t now = time(NULL);
    printf("ID de la reclamation a modifier : ");
    scanf("%d", &id);
    getchar();

    for (i = 0; i < reclamation_nb; i++) {
        if (reclamations[i].id == id && strcmp(reclamations[i].name, username) == 0 && strcmp(reclamations[i].status,"en cours")==0) {
            double diff = difftime(now, reclamations[i].date_ajt);
            if (diff <= 24*3600) {
                ind++;
                printf("pour changer le motif : 1\npour changer description: 2\npour changer categorie  : 3\npour changer tous : 4\n");
                scanf("%d",&s);
                getchar();
                if(s==1){
                    printf("modifier un motif : ");
                    fgets(reclamations[i].motif, 50, stdin);
                    reclamations[i].motif[strcspn(reclamations[i].motif, "\n")] = 0;
                    printf("reclamation modifiee\n");
                    ordre_priorit(reclamations, i);
                }else if(s==2){
                    printf("modifier une description : ");
                    fgets(reclamations[i].description, 200, stdin);
                    reclamations[i].description[strcspn(reclamations[i].description, "\n")] = 0;
                    printf("reclamation modifiee\n");
                    ordre_priorit(reclamations, i);
                }else if(s==3){
                    printf("modifier une categorie : ");
                    fgets(reclamations[i].categorie, 50, stdin);
                    reclamations[i].categorie[strcspn(reclamations[i].categorie, "\n")] = 0;
                    printf("reclamation modifiee\n");
                }else if(s==4){
                    printf("modifier un motif : ");
                    fgets(reclamations[i].motif, 50, stdin);
                    reclamations[i].motif[strcspn(reclamations[i].motif, "\n")] = 0;
                    printf("modifier une description : ");
                    fgets(reclamations[i].description, 200, stdin);
                    reclamations[i].description[strcspn(reclamations[i].description, "\n")] = 0;
                    printf("modifier une categorie : ");
                    fgets(reclamations[i].categorie, 50, stdin);
                    reclamations[i].categorie[strcspn(reclamations[i].categorie, "\n")] = 0;
                    printf("reclamation modifiee\n");
                    ordre_priorit(reclamations, i);
                }else{
                    printf("le choix est invalide\n");
                }
                return;
            }
        }
    }
    if(ind==0){
        printf("reclamation non trouvee ou acces refuse\n");
    }
}

void afficher_delai() {
    double total_delai = 0;
    int nb = 0;

    for (int i = 0; i < reclamation_nb; i++) {
        if (strcmp(reclamations[i].status, "en cours") != 0) {
            double delai = difftime(reclamations[i].date_traitement, reclamations[i].date_ajt);
            total_delai = total_delai + delai;
            nb++;
        }
    }

    if (nb > 0) {
        double delai_moyen = total_delai / nb;
        printf("Delai moyen de traitement : %.2f secondes\n", delai_moyen);
    } else {
        printf("Aucune reclamation traitee pour calculer le delai moyen.\n");
    }
}


void rapport_journalier() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char date_today[20];
    sprintf(date_today, "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    sprintf(reclamations[reclamation_nb].date, "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    FILE *fichier ;
    
    fichier= fopen("rapport_journalier.txt", "w");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier\n");
        return;
    }

    fprintf(fichier, "Rapport journalier pour le %s :\n", date_today);
    fprintf(fichier, "Nouvelles reclamations :\n");

    for (int i = 0; i < reclamation_nb; i++) {
             if (strcmp(date_today,reclamations[i].date)==0) { 
                    fprintf(fichier, "ID: %d, nom: %s, motif: %s, description: %s, categorie: %s, statut: %s, priorite: %s\n",
                    reclamations[i].id, reclamations[i].name, reclamations[i].motif, reclamations[i].description,
                    reclamations[i].categorie, reclamations[i].status, reclamations[i].priority);
     }
    }

    fprintf(fichier, "\nReclamations resolues :\n");
    for (int i = 0; i < reclamation_nb; i++) {
        if (strcmp(reclamations[i].status, "resolue") == 0 && 
            strcmp(date_today,reclamations[i].date)==0) {
            fprintf(fichier, "ID: %d, mom: %s, motif: %s, description: %s, categorie: %s, statut: %s, priorite: %s\n",
                    reclamations[i].id, reclamations[i].name, reclamations[i].motif, reclamations[i].description,
                    reclamations[i].categorie, reclamations[i].status, reclamations[i].priority);
        }
    }

    fclose(fichier);
    printf("rapport journalier genere avec succes.\n");
}

int main(){
    char role[50];
    char username[50];
    int new;
    int indclt = 0 ;
    int indagnt = 0;


    do{
        menu();
        switch (choix){
        case 1:
                signup();
            break;
        case 2 : 
               if(espaceadmin()==1){
                    do{
                        menuadmin();
                        switch (ch1){
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
                                printf("pour recherche par ID choiser 1 et par name choiser 2 et pare date 3 et par categorie choiser 4 et par status choiser 5 \n ");
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
                                            printf("le choix est invalide\n");
                                        break;
                                }
                                break;
                            case 6:
                                afficher_Priorite();
                                break;
                            case 7:
                                supprimer_reclamation();
                                break;
                            case 8:
                                changetrole();
                                break;
                            case 9:
                                printf("pour total et taux des reclamation choiser 1:\npour delai choiser 2:\npour rapport journalier choiser 3 :\n "); 
                                int p ;
                                scanf("%d",&p);
                                if(p==1){
                                        afficher_statistiques();
                                }else if(p==2){
                                        afficher_delai();
                                }else if(p==3){
                                        rapport_journalier(); 
                                }else{
                                    printf("le choixe et invalide\n");
                                }
                                break;
                            case 10: 
                                    break;
                            default:
                                printf("le choix est invalide\n");
                                break;
                        }
                    } while (ch1 !=10 );
    
               }
            break;
        case 3:
            new = signin();
               strcpy(username, users[new].name);
                

                for(int i=0;i<user_nb;i++){
                    if(strcmp(users[new].role,"Client")==0){
                        indclt=1;
                    }
                }
                if (indclt != 0){
                        do{
                        menuclient();
                        switch (ch1){
                            case 1:
                                ajouter_reclamation(username);
                                break;
                            case 2:
                                afficherreclamationclient(username);
                                break;
                            case 3 : 
                                supprimer_reclamationclient(username);
                                break;
                            case 4:
                                modifier_reclamationclient(username);
                                break;
                            case 5:
                                indclt = 0 ;
                                break;
                            default:
                                printf("le choix est invalide\n");
                                break;
                        }
                    } while (ch1 != 5 );
                }else{
                    printf("acces impossible\n");
                }
            break;
        case 4:
            new = signin();
               strcpy(username, users[new].name);
                

                for(int i=0;i<user_nb;i++){
                    if(strcmp(users[new].role,"Agent")==0){
                        indagnt=1;
                    }
                }
                if (indagnt!= 0){
                        do{
                        menuagent();
                        switch (ch1){
                            case 1:
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
                                printf("pour recherche par ID choiser 1 et par name choiser 2 et pare date 3 et par categorie choiser 4 et par status choiser 5  \n");
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
                                            printf("le choix est invalide\n");
                                        break;
                                }
                                break;
                            case 6:
                                supprimer_reclamation();
                                break;

                            case 7:
                                indagnt = 0 ;
                                break;
                            default:
                                printf("le choix est invalide\n");
                                break;
                        }
                    } while (ch1 !=7 );
    
               }else{
                printf("acces impossible\n");
               }
            break;
        case 5:
                printf("merci ,a bientot \n");
                break;
        default:
                printf("le choix est invalide\n");
            break;
        }
    } while (choix !=5 );
    
}
