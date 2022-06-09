#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Mahasiswa{
        char  nama[40];
        int  nim;
        int nilai;
        char indeks;
    }mhs[50],temp;

struct Data{
        int   nim;
        int   nilai;
        float ipk;
        char  grade[2];
    }nilai;

int i,j,k;

void regestrasi(){

    FILE *fp;
    fp=fopen("user.txt","a");

    char username[20],pass[20],passcheck[20],konci[20];
    int pilihan,nim;

    printf("Masukan username anda\t:");
    fgets(username,20,stdin);
    strtok(username,"\n");
    printf("Masukan password anda\t:");
    fgets(pass,20,stdin);
    strtok(pass,"\n");
    printf("Masukan kembali password anda\t:");
    fgets(passcheck,20,stdin);
    strtok(passcheck,"\n");
    if (strcmp(pass,passcheck)==0)
    {
        printf("Satu langkah lagi..\n");
        printf("Anda berperan sebagai?\n[1].Admin\n[2].Mahasiswa\n");
        scanf("%d",&pilihan);
        scanf("%*c");
        if (pilihan==1)
        {
            printf("Masukan kata kunci!\n");
            fgets(konci,20,stdin);
            strtok(konci,"\n");
            if (strcmp(konci,"admin_plz")==0)
            {
                printf("Masukan Nomor Induk\t:");
                scanf("%d",&nim);
                printf("Regestrasi Berhasil!\n");
                fprintf(fp,"%d %s %s %s",nim,username,pass,"useradmin\n");
            } else {
                printf("Kata kunci salah, kamu bohong!\n");
            }
        } else {
            printf("Masukan NIM\t:");
            scanf("%d",&nim);
            fprintf(fp,"%d %s %s %s",nim,username,pass,"user\n");
        }
    }
    printf("%d",nim);
    fclose(fp);
}

int login(int *login,int *profilmode,int *NIM){

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
        fscanf(user,"%i %s %s %s",*&NIM,username,pass,mode);
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
    printf("%d",*NIM);
    fclose(user);
}



//kode untuk login sebagai administrator
int administrator() {
    int option,i,N;
    FILE *fpm;
    //struct Mahasiswa mhs[i],arrmhs[i]; (struct mahasiswa nanti dipindah ke global ae, dibawah include)
    printf("\t== Option ==\n");
    printf("[1] Daftar Mahasiswa\n[2] Menghapus Data Mahasiswa\n[3] Mengedit Data Mahasiswa\n[4] Regristasi Mahasiswa\n[5] Mengisi Nilai Mahasiswa\n");
    scanf("%d",&option);
    scanf("%*c");
    switch (option)
    {
    //Melihat Daftar Mahasiswa
    case 1:
        i=0;
        fpm=fopen("mahasiswa.txt","r");
        printf("Daftar Mahasiswa\t:");
        while (!feof(fpm))
        {
            fread(&mhs[i],sizeof(mhs[i]),1,fpm);
            printf("%d %s\n",mhs[i].nim,mhs[i].nama);
        }
        /*
        //Sorting 
        for(data=0;data<5;data++){ //~
        for(i=0;i<5;i++){ //Ganti ke while(!feof(fpm))//
            if(mhs[i].nama[0]>mhs[data].nama[0]){ //Ganti ke .nim//
                temp = mhs[data]; 
                mhs[data] = mhs[i];
                mhs[i] = temp;
            }
        }
        }
        */
        //Searching
        fclose(fpm);
        break;
    //Menghapus Data Mahasiswa
    case 2:
        i=0;
        fpm=fopen("mahasiswa.txt","r+");
        printf("Daftar Mahasiswa\t:");
        while (!feof(fpm))
        {
            fread(&mhs[i],sizeof(mhs[i]),1,fpm);
            printf("%d %s\n",mhs[i].nim,mhs[i].nama);
        }
        //Sorting
        //Searching
        fclose(fpm);
        break;
    //Mengedit Data Mahasiswa
    case 3:
        i=0;
        fpm=fopen("mahasiswa.txt","r+");
        printf("Daftar Mahasiswa\t:");
        while (!feof(fpm))
        {
            fread(&mhs[i],sizeof(mhs[i]),1,fpm);
            printf("%d %s\n",mhs[i].nim,mhs[i].nama);
        }
        //Sorting
        //Searching
        break;
    //Registrasi Mahasiswa
    case 4:
        fpm=fopen("mahasiswa.txt","a+");
        printf("Masukkan jumlah mahasiswa yang ingin diinputkan datanya: ");
        scanf("%d", &N);
        scanf("%*c");
        for (i=0;i<N;i++){ //i++? ato i--?
        printf("Masukkan Nama Mahasiswa ");
        fflush(stdin);
        fgets(temp.nama, 40, stdin);
        strtok(temp.nama,"\n");
        printf("Masukkan NIM Mahasiswa : ");
        scanf("%d", &temp.nim);
        scanf("%*c");
        printf("Masukkan Nilai : ");
        scanf("%d", &temp.nilai);
        scanf("%*c");
        fwrite(&temp,sizeof(temp),1,fpm);
        }
        //Menampilkan Daftar setelah penambahan
        /*
        i=0;
        printf("Daftar Mahasiswa\t:");
        while (!feof(fpm))
        {
            fread(&mhs[i],sizeof(mhs[i]),1,fpm);
            printf("%d %s\n",mhs[i].nim,mhs[i].nama);
        }
        */
        fclose(fpm);
        break;
    //Mengisi Nilai Mahasiswa
    default:
        fpm=fopen("mahasiswa.txt","a+");
        //Sorting
        //Searching 
        fclose(fpm);
        break;
    }
}


int mahasiswa(){
    int option;
    FILE *fm;
    //kode untuk login sebagai user biasa
    printf("\t== Option ==\n");
    printf("[1] Data diri\n[2] Lihat Nilai\n");
    scanf("%d",&option);
    scanf("%*c");
    switch (option)
    {
    ///Melihat data diri
    case 1: 
    fm=fopen("data diri.txt","r");
        while (!feof(fm)){
        fscanf(fm, "%s %d",temp.nama, &temp.nim);
        printf("%s %d\n", temp.nama, temp.nim);
        }
        fclose(fm);
        break;
    case 2:
    fm=fopen("data nilai.txt","r");
        while (!feof(fm)){
        fscanf(fm, "%d %f %s %d", &nilai.nim, &nilai.ipk, nilai.grade, &nilai.nilai);
        printf("%d %.2f %s %d\n", nilai.nim, nilai.ipk, nilai.grade, nilai.nilai);
        }
        fclose(fm);
        break;
    }
}


int main() {
    int status=0,mode=0, pilihan, nim;

    printf("sudah punya akun?~\n[1].Sudah\n[2].Belum\n");
    scanf("%d",&pilihan);
    scanf("%*c");
    switch (pilihan)
    {
    case 1:
        login(&status,&mode,&nim);
        break;

    case 2:
        regestrasi();
        login(&status,&mode,&nim);
        break;
    
    default:
        printf("Terjadi error!!\n");
        break;
    }

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