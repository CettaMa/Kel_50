#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i,j,k;

int login(int *login){

    FILE *user;
    char username[20],inputusername[20],pass[20],inputpass[20];

    printf("==- MENU LOG-IN -==\n");
    printf("Masukan Username anda\t:");
    fgets(inputusername,20,stdin);
    strtok(inputusername,"\n");
    printf("Masukan Password anda\t:");
    fgets(inputpass,20,stdin);
    strtok(inputpass,"\n");

    if ((user=fopen("user.txt","r"))==NULL)
    {
        printf("File Error!\n");
    } else {
        while (!feof(user) && *login==0){
        fscanf(user,"%s %s",username,pass);
        if (strcmp(inputusername,username)==0){
            if (strcmp(pass,inputpass)==0){
                printf("log in berhasil!\n");
                *login=1;
            } else if (feof(user)) {
                printf("Password salah!\n");
            }
        } else if(feof(user)) {
            printf("Password atau Username salah..\n");
        }
        }
    }
}

int main() {
    int login_mode=0;
     login(&login_mode);
     printf("%d\n",login_mode);
}