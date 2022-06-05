#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i,j,k;

void regestrasi(){

    FILE *fp;
    fp=fopen("user.txt","a");

    char username[20],pass[20],passcheck[20],konci[20];
    int pilihan;

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
                printf("Regestrasi Berhasil!\n");
                fprintf(fp,"%s %s %s", username,pass,"useradmin\n");
            } else {
                printf("Kata kunci salah, kamu bohong!\n");
            }
        } else {
            fprintf(fp,"%s %s %s", username,pass,"user\n");
        }
    }
    fclose(fp);
}

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
   ///CATATAN
    /*
    1. Gw Bikin file baru buat  data Mahasiswa, ribet nyarinya nanti kalo dicampur(gw masih mikir mikir kalo yg dicampur)
    2. Masih bingung cara nempelin data-data ke nama mahasiswa lewat arrStruct
    3. Itu Pak, file yg mahasiswa.txt larinya kemana ye?
    4. ~(0_0)~ lagi gw lanjutin, masih nyoba nyoba dicodeblocks 
    */
    //kode untuk login sebagai administrator
    FILE *fpm;
    fpm=fopen("mahasiswa.txt","r");
    int option,i,N;
    struct Mahasiswa{
        char  nama[40];
        int  nim;
        int nilai;
        char indeks;
    }mhs[i];
    //struct Mahasiswa mhs[i],arrmhs[i];

    printf("\t== Option ==\n");
    printf("[1] Daftar Mahasiswa\n[2] Menghapus Data Mahasiswa\n[3] Mengedit Data Mahasiswa\n[4] Regristasi Mahasiswa\n[5] Mengisi Nilai Mahasiswa\n");
    scanf("%d",&option);
    scanf("%*c");
    switch (option)
    {
    //Melihat Daftar Mahasiswa
    case 1:
        while (!feof(fpm)){
        fgets(mhs[i].nama, sizeof(mhs[i].nama), (FILE*)fpm);
        fscanf(fpm, "%d\n", &mhs[i].nim);
        fscanf(fpm, "%d\n", &mhs[i].nilai);
        }
        fclose(fpm);
        break;
    //Menghapus Data Mahasiswa
    case 2:
        fclose(fpm);
        break;
    //Mengedit Data Mahasiswa
    case 3:
        fclose(fpm);
        break;
    //Registrasi Mahasiswa
    case 4:
        printf("Masukkan jumlah mahasiswa yang ingin diinputkan datanya: ");
        scanf("%d", &N);
        scanf("%*c");
        i=N;
        for (i=0;i<N;i++){
        printf("Masukkan Nama Mahasiswa ");
        fflush(stdin);
        fgets(mhs[i].nama, 40, stdin);
        strtok(mhs[i].nama,"\n");
        printf("Masukkan NIM Mahasiswa : ");
        scanf("%d", &mhs[i].nim);
        scanf("%*c");
        printf("Masukkan Nilai : ");
        scanf("%d", &mhs[i].nilai);
        scanf("%*c");

        fprintf(fpm,"%s\n",mhs[i].nama);
        fprintf(fpm,"%d\n",mhs[i].nim);
        fprintf(fpm,"%d\n",mhs[i].nilai);
        }
        fclose(fpm);
        break;
    //Mengisi Nilai Mahasiswa
    default:

        break;
    }
}

int mahasiswa(){
    int option;
    //kode untuk login sebagai user biasa
    printf("\t== Option ==\n\n");
    printf("[1] Mahasiswa\n[2] Cari Mahasiswa\n[3]---\n[4]---\n[5]---\n[6]---\n");
}

int main() {
    int status=0,mode=0, pilihan;

    printf("sudah punya akun?~\n[1].Sudah\n[2].Belum\n");
    scanf("%d",&pilihan);
    scanf("%*c");
    switch (pilihan)
    {
    case 1:
        login(&status,&mode);
        break;
    
    default:
        regestrasi();
        login(&status,&mode);
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