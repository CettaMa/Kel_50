#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Mahasiswa{
        char  nama[40];
        int  nim;
        char indeks[5];
        float ipk;
    }mhs[50],temp;

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
                scanf("%*c");
                printf("Regestrasi Berhasil!\n");
                fprintf(fp,"%d %s %s %s",nim,username,pass,"useradmin\n");
            } else {
                printf("Kata kunci salah, kamu bohong!\n");
            }
        } else {
            printf("Masukan NIM\t:");
            scanf("%d",&nim);
            scanf("%*c");
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
    int option,i,j=0,k,N,cari,indeks=-1,loop,piledit;
    FILE *fpm;
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
        printf("Daftar Mahasiswa\t:\n");
        while (!feof(fpm) && (fread(&mhs[i],sizeof(mhs[i]),1,fpm))!=NULL)
        {
            i++;
        }

        for ( j = 0; j < i-1; j++)
        {
            for ( k = 0; k < i-j-1; k++)
            {
                if (mhs[k].nim>mhs[k+1].nim)
                {
                    temp = mhs[k];
                    mhs[k] = mhs[k+1];
                    mhs[k+1] = temp;
                }
            }
        }
        
        for ( j = 0; j < i; j++)
        {
            printf("%d\t%s\t%.2f\t%s\n",mhs[j].nim,mhs[j].nama,mhs[j].ipk,mhs[j].indeks);
        }
        fclose(fpm);
        break;
    //Menghapus Data Mahasiswa
    case 2:
        i=0;
        fpm=fopen("mahasiswa.txt","r");
        while (!feof(fpm) && (fread(&mhs[i],sizeof(mhs[i]),1,fpm))!=NULL)
        {
            printf("%d %s\n",mhs[i].nim,mhs[i].nama);
            i++;
        }
        fclose(fpm);
        fpm=fopen("mahasiswa.txt","w+");
        printf("Masukan NIM mahasiswa yang anda ingin Hapus: ");
        scanf("%d",&cari);
        //Searching 
        for ( j = 0; j < i; j++)
        {
            if (cari==mhs[j].nim)
            {
                indeks=j;
                break;
            }
        }
        if (indeks==-1)
        {
            printf("Mahasiswa tidak ditemukan!\n");
        } else {
            printf("Penghapusan data mahasiswa dimulai..\n");
            strcpy(mhs[indeks].nama,"\0");
            mhs[indeks].ipk=0;
            mhs[indeks].nim=0;
            strcpy(mhs[indeks].indeks,"\0");
            printf("Penghapusan selesai\n");
        }
        printf("Mengurutkan..\n");
        for ( j = 0; j < i-1; j++)
        {
            for ( k = 0; k < i-j-1; k++)
            {
                if (mhs[k].nim>mhs[k+1].nim)
                {
                    temp = mhs[k];
                    mhs[k] = mhs[k+1];
                    mhs[k+1] = temp;
                }
            }
        }
        for ( j = 1; j < i; j++)
        {
            printf("%d\t%s\t%.2f\t%s\n",mhs[j].nim,mhs[j].nama,mhs[j].ipk,mhs[j].indeks);
            fwrite(&mhs[j],sizeof(mhs[j]),1,fpm);
        }
        fclose(fpm);
        break;
    //Mengedit Data Mahasiswa
    case 3:
        i=0;
        fpm=fopen("mahasiswa.txt","r");
        while (!feof(fpm) && (fread(&mhs[i],sizeof(mhs[i]),1,fpm))!=NULL)
        {
            printf("%d %s\n",mhs[i].nim,mhs[i].nama);
            i++;
        }
        fclose(fpm);
        fpm=fopen("mahasiswa.txt","w+");
        printf("Masukan NIM mahasiswa yang anda ingin Edit datanya: ");
        scanf("%d",&cari);
        //Searching 
        for ( j = 0; j < i; j++)
        {
            if (cari==mhs[j].nim)
            {
                indeks=j;
                break;
            }
        }
        if (indeks==-1)
        {
            printf("Mahasiswa tidak ditemukan!\n");
            for ( j = 0; j < i; j++)
            {
            fwrite(&mhs[j],sizeof(mhs[j]),1,fpm);
            }
        } else {
            printf("Mahasiswa ditemukan :\n%d\t%s\t%f\n",mhs[indeks].nim,mhs[indeks].nama,mhs[indeks].ipk);
            printf("Apa yang ingin anda edit?\n[1] Nama\n[2] NIM\n[3] IPK\n");
            scanf("%d",&piledit);
            scanf("%*c");
            switch (piledit)
            {
            case 1:
                printf("Masukan nama baru :");
                fgets(mhs[indeks].nama,40,stdin);
                strtok(mhs[indeks].nama,"\n");
                break;
            
            case 2:
                printf("Masukan NIM Baru :");
                scanf("%d",&mhs[indeks].nim);
                break;

            default:
                printf("Masukan nilai IPK baru :");
                scanf("%f",&mhs[indeks].ipk);
                if (mhs[indeks].ipk>=3.67 && mhs[indeks].ipk<=4.00)
            {
                strcpy(mhs[indeks].indeks,"A");
            } else if (mhs[indeks].ipk>=3.34 && mhs[indeks].ipk<=3.66)
            {
                strcpy(mhs[indeks].indeks,"A-");
            } else if (mhs[indeks].ipk>=3.01 && mhs[indeks].ipk<=3.33)
            {
                strcpy(mhs[indeks].indeks,"B+");
            } else if (mhs[indeks].ipk>=2.67 && mhs[indeks].ipk<=3.00)
            {
                strcpy(mhs[indeks].indeks,"B");
            } else if (mhs[indeks].ipk>=2.34 && mhs[indeks].ipk<=2.66)
            {
                strcpy(mhs[indeks].indeks,"B-");
            } else if (mhs[indeks].ipk>=2.01 && mhs[indeks].ipk<=2.33)
            {
                strcpy(mhs[indeks].indeks,"C+");
            } else if (mhs[indeks].ipk>=1.67 && mhs[indeks].ipk<=2.00)
            {
                strcpy(mhs[indeks].indeks,"C");
            } else if (mhs[indeks].ipk>=1.34 && mhs[indeks].ipk<=1.66)
            {
                strcpy(mhs[indeks].indeks,"C-");
            } else if (mhs[indeks].ipk>=1.00 && mhs[indeks].ipk<=1.33)
            {
                strcpy(mhs[indeks].indeks,"D+");
            } else if (mhs[indeks].ipk<=1.00) {
                strcpy(mhs[indeks].indeks,"D");
            }
                break;
            }

            for ( j = 0; j < i; j++){
                printf("%d\t%s\t%.2f\t%s\n",mhs[j].nim,mhs[j].nama,mhs[j].ipk,mhs[j].indeks);
                fwrite(&mhs[j],sizeof(mhs[j]),1,fpm);
            }

        }
        fclose(fpm);
        break;
        
    //Registrasi Mahasiswa
    case 4:
        i=0;
        fpm=fopen("mahasiswa.txt","a+");
        printf("Masukkan jumlah mahasiswa yang ingin diinputkan datanya: ");
        scanf("%d", &N);
        scanf("%*c");
        for (j=0;j<N;j++){ 
        printf("Masukkan Nama Mahasiswa ");
        fflush(stdin);
        fgets(temp.nama, 40, stdin);
        strtok(temp.nama,"\n");
        printf("Masukkan NIM Mahasiswa : ");
        scanf("%d", &temp.nim);
        scanf("%*c");
        fwrite(&temp,sizeof(temp),1,fpm);
        }
        //Menampilkan Daftar setelah penambahan
        rewind(fpm);
        printf("Daftar Mahasiswa\t:\n");
        while (!feof(fpm) && (fread(&mhs[i],sizeof(mhs[i]),1,fpm))!=NULL)
        {
            printf("%d\t%s\t%.2f\t%s\n",mhs[i].nim,mhs[i].nama,mhs[i].ipk,mhs[i].indeks);
            i++;
        }
        fclose(fpm);
        break;
    //Mengisi Nilai Mahasiswa
    case 5:
        i=0;
        fpm=fopen("mahasiswa.txt","r");
        while (!feof(fpm) && (fread(&mhs[i],sizeof(mhs[i]),1,fpm))!=NULL)
        {
            printf("%d %s\n",mhs[i].nim,mhs[i].nama);
            i++;
        }
        fclose(fpm);
        fpm=fopen("mahasiswa.txt","w+");
        printf("Masukan NIM mahasiswa yang anda ingin isi Nilainya:");
        scanf("%d",&cari);
        //Searching 
        for ( j = 0; j < i; j++)
        {
            if (cari==mhs[j].nim)
            {
                indeks=j;
                break;
            }
        }
        if (indeks==-1)
        {
            printf("Mahasiswa tidak ditemukan!\n");
            for ( j = 0; j < i; j++)
            {
            fwrite(&mhs[j],sizeof(mhs[j]),1,fpm);
            }
        } else {
            printf("Mahasiswa Ditemukan\n%d\t%s\n",mhs[indeks].nim,mhs[indeks].nama);
            printf("Masukan nilai IPK\t:");
            scanf("%f",&mhs[indeks].ipk);
            if (mhs[indeks].ipk>=3.67 && mhs[indeks].ipk<=4.00)
            {
                strcpy(mhs[indeks].indeks,"A");
            } else if (mhs[indeks].ipk>=3.34 && mhs[indeks].ipk<=3.66)
            {
                strcpy(mhs[indeks].indeks,"A-");
            } else if (mhs[indeks].ipk>=3.01 && mhs[indeks].ipk<=3.33)
            {
                strcpy(mhs[indeks].indeks,"B+");
            } else if (mhs[indeks].ipk>=2.67 && mhs[indeks].ipk<=3.00)
            {
                strcpy(mhs[indeks].indeks,"B");
            } else if (mhs[indeks].ipk>=2.34 && mhs[indeks].ipk<=2.66)
            {
                strcpy(mhs[indeks].indeks,"B-");
            } else if (mhs[indeks].ipk>=2.01 && mhs[indeks].ipk<=2.33)
            {
                strcpy(mhs[indeks].indeks,"C+");
            } else if (mhs[indeks].ipk>=1.67 && mhs[indeks].ipk<=2.00)
            {
                strcpy(mhs[indeks].indeks,"C");
            } else if (mhs[indeks].ipk>=1.34 && mhs[indeks].ipk<=1.66)
            {
                strcpy(mhs[indeks].indeks,"C-");
            } else if (mhs[indeks].ipk>=1.00 && mhs[indeks].ipk<=1.33)
            {
                strcpy(mhs[indeks].indeks,"D+");
            } else if (mhs[indeks].ipk<=1.00) {
                strcpy(mhs[indeks].indeks,"D");
            }
            
            for ( j = 0; j < i; j++)
            {
                printf("%d\t%s\t%.2f\t%s\n",mhs[j].nim,mhs[j].nama,mhs[j].ipk,mhs[j].indeks);
                fwrite(&mhs[j],sizeof(mhs[j]),1,fpm);
            }
        }
        //Sorting
        fclose(fpm);
        break;
    default:
        printf("Error..\n");
        break;
    }//end swict

    printf("\nApakah Anda sudah selesai?\n[1] Ya\n[2] Tidak\n");
    scanf("%d",&loop);
    if (loop==2)
    {
        administrator();
    } else {
        printf("Operasi selesai!\n");
    }
}

int mahasiswa(int NIM){
    int option,i,cari,j,indeks=-1,loop;
    FILE *fpm;
    //kode untuk login sebagai user biasa
    printf("\t== Option ==\n");
    printf("[1] Data diri\n[2] Lihat Nilai\n");
    scanf("%d",&option);
    scanf("%*c");
    switch (option)
    {
    ///Melihat data diri
    case 1: 
        i=0;
        fpm=fopen("mahasiswa.txt","r");
        while (!feof(fpm) && (fread(&mhs[i],sizeof(mhs[i]),1,fpm))!=NULL)
        {
            i++;
        }
        cari=NIM;
        //Searching 
        for ( j = 0; j < i; j++)
        {
            if (cari==mhs[j].nim)
            {
                indeks=j;
                break;
            }
        }
        if (indeks==-1)
        {
            printf("Mahasiswa tidak ditemukan!\n");
        } else {
            printf("Mahasiswa :\nNama\t:%s\nNIM\t:%d\n",mhs[indeks].nama,mhs[indeks].nim);
        }
        break;
    case 2:
        i=0;
        fpm=fopen("mahasiswa.txt","r");
        while (!feof(fpm) && (fread(&mhs[i],sizeof(mhs[i]),1,fpm))!=NULL)
        {
            i++;
        }
        cari=NIM;
        //Searching 
        for ( j = 0; j < i; j++)
        {
            if (cari==mhs[j].nim)
            {
                indeks=j;
                break;
            }
        }
        if (indeks==-1)
        {
            printf("Mahasiswa tidak ditemukan!\n");
        } else {
            printf("Mahasiswa %d :\nIPK\t:%.2f\nGrade\t:%s\n",mhs[indeks].nim,mhs[indeks].ipk,mhs[indeks].indeks);
        }
        break;
    }
    printf("\nApakah Anda sudah selesai?\n[1] Ya\n[2] Tidak\n");
    scanf("%d",&loop);
    if (loop==2)
    {
        mahasiswa(cari);
    } else {
        printf("Operasi selesai!\n");
    }
}


int main() {
    int status=0,mode=0, pilihan, nim,lanjut=1;

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
     
     case 2:
            mahasiswa(nim);
        break;
     default:
        printf("Terjadi error!!\n");
         break;
     }
}