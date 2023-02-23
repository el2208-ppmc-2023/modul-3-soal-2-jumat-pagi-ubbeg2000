/** EL2208 Praktikum Pemecahan Masalah dengan C 2022/2023
 *   Modul               : 
 *   Hari dan Tanggal    :
 *   Nama (NIM)          :
 *   Nama File           : main.c
 *   Deskripsi           :
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 255

void tambah_senjata(int* char_status, int no_senjata){
    /** @brief Fungsi digunakan untuk mengubah nilai status karakter berdasarkan pilihan senjata
     * @param char_status pointer menuju array yang berisi data status karakter
     * @param no_senjata nomor senjata yang dipilih oleh pengguna 
    **/
    // Data pertambahan nilai
    int atk_senjata[5] = {400,600,550,600,540};
    int critrate_senjata[5] = {28,0,0,0,0};
    int critdmg_senjata[5] = {0,66,88,0,0};
    int er_senjata[5] = {0,0,0,55,0};
    int em_senjata[5] = {0,0,0,0,265};

    // Jumlahkan status awal dengan pertambahan nilai, akses dengan pointer
    *(char_status+1) += *(atk_senjata + (no_senjata-1));
    *(char_status+2) += *(critrate_senjata + (no_senjata-1));
    *(char_status+3) += *(critdmg_senjata + (no_senjata-1));
    *(char_status+4) += *(er_senjata + (no_senjata-1));
    *(char_status+5) += *(em_senjata + (no_senjata-1));
}

void tambah_artifak(int* char_status, int artifak1, int artifak2){
    /** @brief Fungsi digunakan untuk mengubah nilai status karakter berdasarkan pilihan artifak karakter
     * @param char_status pointer menuju array yang berisi data status karakter
     * @param artifak1 set artifak pertama yang dipilih pengguna
     * @param artifak2 set artifak kedua yang dipilih pengguna
    */
    // Data pertambahan nilai
    int persenhp_artifak[5] = {20,0,0,0,0};
    int persenatk_artifak[5] = {20,0,0,15,20};
    int critrate_artifak[5] = {0,0,12,0,10};
    int critdmg_artifak[5] = {0,0,24,0,0};
    int er_artifak[5] = {0,20,0,0,0};
    int em_artifak[5] = {0,80,0,80,0};

    *(char_status+0) = (*(char_status+0))*(100 + *(persenhp_artifak + artifak1-1) + *(persenhp_artifak + artifak2-1))/100;
    *(char_status+1) = (*(char_status+1))*(100 + *(persenatk_artifak + artifak1-1) + *(persenatk_artifak + artifak2-1))/100;
    *(char_status+2) = (*(char_status+2)) + *(critrate_artifak + artifak1-1) + *(critrate_artifak + artifak2-1);
    *(char_status+3) = (*(char_status+3)) + *(critdmg_artifak + artifak1-1) + *(critdmg_artifak + artifak2-1);
    *(char_status+4) = (*(char_status+4)) + *(er_artifak + artifak1-1) + *(er_artifak + artifak2-1);
    *(char_status+5) = (*(char_status+5)) + *(em_artifak + artifak1-1) + *(em_artifak + artifak2-1);
}

int main(){
    // Deklarasi variabel
    char file_name[MAX_STRING];
    char each_line[MAX_STRING];
    char temp[MAX_STRING];
    char *token;
    int count = 0;

    // Input nama file
    printf("Gensin Impek - Berpetualang di Dunia Fantasi\n");
    printf("Masukkan nama file yang berisi status karakter: ");
    scanf("%s", file_name);

    // Buka File Eksternal
    FILE* file_char = fopen(file_name, "r") ;
    // printf("Nama File: %s\n",file_name); // Untuk Debugging

    // Validasi File 
    if(file_char == NULL){
        printf("File tidak dapat dibuka. Program Berakhir.");
        return 0;
    }

    // Baca nama karakter
    fgets(each_line,MAX_STRING,file_char);
    strcpy(temp,each_line);

    // Deklarasi variabel nama karakter dan status karakter
    char char_name[MAX_STRING];
    int char_status[6];
    int senjata, artifak1, artifak2;

    // Isi nama karakter
    strcpy(char_name,temp);
    strtok(char_name,"\n");

    // Lakukan pembacaan pada file
    while(fgets(each_line,MAX_STRING,file_char)){
        strcpy(temp,each_line);
        int column = 0;
        token = strtok(temp,",");
        while(token!=NULL){
            char_status[column] = atoi(token);
            column += 1;
            token = strtok(NULL,",");
        }
    }

    // Input nomor senjata dan set artifak
    printf("Masukkan nomor senjata, set artifak 1, dan set artifak 2: ");
    scanf(" %d %d %d",&senjata, &artifak1, &artifak2);
    // Print untuk debugging
    // printf("Nomor senjata: %d\n",senjata);
    // printf("Set artifak %d & %d\n",artifak1,artifak2);

    // Ubah status karakter berdasarkan senjata dan artifak
    tambah_senjata(char_status,senjata);
    tambah_artifak(char_status,artifak1,artifak2);
    
    // Print Akhir
    printf("Status akhir karakter %s setelah menggunakan senjata dan artifak adalah:\n",char_name);
    printf("HP: %d\n",char_status[0]);
    printf("ATK: %d\n",char_status[1]);
    printf("Crit Rate: %d%c\n",char_status[2],'%');
    printf("Crit Damage: %d%c\n",char_status[3],'%');
    printf("ER: %d%c\n",char_status[4],'%');
    printf("EM: %d\n",char_status[5]);

    // Tutup file dan akhiri program
    fclose(file_char);
    return 0;
}
