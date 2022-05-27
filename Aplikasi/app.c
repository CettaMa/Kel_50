#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i,j,k;

int login(int *login,int *profilmode){

    FILE *user;
    char username[20],inputusername[20],pass[20],inputpass[20],mode[10];

    printf("==- MENU LOGIN -==\n");
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
        fscanf(user,"%s %s %s",username,pass,mode);
        if (strcmp(inputusername,username)==0){
            if (strcmp(pass,inputpass)==0){
                printf("log in berhasil!\n\n");
                if (strcmp(mode,"useradmin")==0){
                    printf("Selamat datang %s, Anda Login sebagai Admin\n\n",username);
                    *profilmode=1;} 
                    else {
                    printf("Selamat datang %s, Anda Login sebagai Mahasiswa\n\n",username);
                    *profilmode=2;
                }
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

int administrator() {
    //kode untuk login sebagai administrator
    int option;
    printf("\t== Option ==\n");
    printf("[1] Daftar Mahasiswa\n[2] Cari Mahasiswa\n[3]---\n[4]---\n[5]---\n[6]---\n");
}

int mahasiswa(){
    int option;
    //kode untuk login sebagai user biasa
    printf("\t== Option ==\n\n");
    printf("[1] Mahasiswa\n[2] Cari Mahasiswa\n[3]---\n[4]---\n[5]---\n[6]---\n");
}

int main() {
    int status=0,mode=0;
     login(&status,&mode);

     switch (mode)
     {
     case 1:
        administrator();
         break;
     
     default:
        mahasiswa();
         break;
     }
}