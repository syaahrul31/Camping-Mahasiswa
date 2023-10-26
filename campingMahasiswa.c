/* ============================
Nama    : Syahrul Hidayat
NPM     : 20081010076
Matkul  : Struktur Data E081
===============================*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>

// Struktur Mahasiswa
struct Mhs{
    char nama[50];
    char jenis_kelamin;
    struct Mhs *next;
};
typedef struct Mhs Mhs;

//============================================================

// Fungsi kelola Mahasiswa
void tambahMhs(Mhs **pListAll);
void hapusMhs(Mhs **pListAll);
void tampilkanDaftar(Mhs *pList);
void giliranNyanyiMhs(Mhs **pListAll, Mhs **currentSinger);
void siapaNyanyiMhs(Mhs *currentSinger);
void pisahCircle(Mhs **pListAll, Mhs **pListMhs, Mhs **pListMhsi);

//============================================================

int main(){
    Mhs *pListAll = NULL;
    Mhs *pListMhs = NULL;
    Mhs *pListMhsi = NULL;
    Mhs *currentSinger = NULL;
    
    int menu;

    do{
        system("cls");
        printf("\n\t ============================================= \n");
        printf("\t\t Camping Api Unggun Mahasiswa\n");
        printf("\t\t      by Syahrul Hidayat\n");
        printf("\t ============================================= \n\n");

        printf("\t 1. Tambah Mahasiswa ke Lingkaran\n");
        printf("\t 2. Hapus Mahasiswa dari Lingkaran\n");
        printf("\t 3. Tampilkan Mahasiswa di Lingkaran\n");
        printf("\t 4. Pindah urutan Bernyanyi\n");
        printf("\t 5. Lihat siapa Bernyanyi\n");
        printf("\t 6. Pisahkan Lingkaran Mahasiswa/i\n");
        printf("\t 7. Matikan Api Unggun\n");

        printf("\n\t Masukkan Pilihan Menu : ");
        scanf("%d", &menu);

        if(menu == 1){
            tambahMhs(&pListAll);
        } else if(menu == 2){
            hapusMhs(&pListAll);
        } else if(menu == 3){
            system("cls");
            printf("\n\t [ Daftar Mahasiswa dalam Lingkaran ]\n");
            tampilkanDaftar(pListAll);
        } else if(menu == 4){
            giliranNyanyiMhs(&pListAll, &currentSinger);
        }else if(menu == 5){
            siapaNyanyiMhs(currentSinger);
        } else if(menu == 6){
            pisahCircle(&pListAll, &pListMhs, &pListMhsi);
        } else if(menu == 7){
            // Pembebasan memori
            while(pListAll != NULL){
                Mhs *temp = pListAll;
                pListAll = pListAll -> next;
                free(temp);
            }
            while(pListMhs != NULL){
                Mhs *temp = pListMhs;
                pListMhs = pListMhs -> next;
                free(temp);
            }
            while(pListMhsi != NULL){
                Mhs *temp = pListMhsi;
                pListMhsi = pListMhsi -> next;
                free(temp);
            }
            printf("\n\t ================================\n");
            printf("\t\t Camping Selesai\n");
            printf("\t ================================\n\n");
            return 0;
        }
    } while(1);

    return 0;
}

//============================================================

void tambahMhs(Mhs **pListAll) {
    Mhs *pNew = (Mhs *)malloc(sizeof(Mhs));

    if (pNew == NULL) {
        printf("\n\t Alokasi Memori gagal!\n");
        getch();
        return;
    }

    system("cls");

    printf("\n\t Masukkan Nama Mahasiswa : ");
    scanf("%s", pNew->nama);

    getchar();

    printf("\t Masukkan Jenis Kelamin (L/P) : ");
    scanf("%c", &pNew->jenis_kelamin);

    if (toupper(pNew->jenis_kelamin) != 'L' && toupper(pNew->jenis_kelamin) != 'P') {
        printf("\n\t Data invalid!\n");
        free(pNew);
    } else if (*pListAll != NULL && strcasecmp(pNew->nama, "CINDY") == 0 && toupper((*pListAll)->jenis_kelamin) == 'L') {
        printf("\n\t Cindy tidak bisa bergandengan tangan dengan mahasiswa laki-laki\n");
        free(pNew);
    } else {
        pNew->next = *pListAll;
        *pListAll = pNew;

        printf("\n\t %s berhasil ditambahkan ke lingkaran!\n", pNew->nama);
    }

    getch();
}

//============================================================

void hapusMhs(Mhs **pListAll){
    char nama[50];

    system("cls");

    Mhs *pCur = *pListAll;
    Mhs *pPre = NULL; 

    if(pCur == NULL){
        printf("\n\t Tidak ada Mahasiswa, Tidak ada Lingkaran!\n");
        getch();
        return;
    }
    
    printf("\n\t Masukkan Nama Mahasiswa : ");
    scanf("%s", nama);

    while (pCur != NULL){
        if(strcmp(pCur -> nama, nama) == 0){
            if(pPre == NULL){
                *pListAll = pCur -> next;
            } else{
                pPre -> next = pCur -> next;
            }
            
            free(pCur);
            printf("\n\t %s berhasil dihapus dari lingkaran!\n", nama);
            getch();
            return;
        }

        pPre = pCur;
        pCur = pCur -> next;
    }

    printf("\n\t %s tidak ditemukan dalam lingkaran!\n", nama);
    getch();
}

//============================================================

void tampilkanDaftar(Mhs *pList) {
    Mhs *curMhs = pList;
    int count = 1;

    if (curMhs == NULL) {
        printf("\n\t NULL!\n");
        getch();
    } else{
        while (curMhs != NULL) {
            printf("\n\n\t [ MAHASISWA KE-%d ]", count);
            printf("\n\t Nama : %s", curMhs->nama);
            printf("\n\t Jenis Kelamin : %c", curMhs->jenis_kelamin);
            curMhs = curMhs->next;
            count++;
        }

        getch();
    }
}

//============================================================

void giliranNyanyiMhs(Mhs **pListAll, Mhs **currentSinger){
    system("cls");
    
    if (*pListAll == NULL) {
        printf("\n\t Tidak ada Mahasiswa yang akan Bernyanyi!\n");
    } else{
        if (*currentSinger != NULL) {
            *currentSinger = (*currentSinger) -> next;
            if (*currentSinger == NULL) {
                *currentSinger = *pListAll; 
            }
        } else{
                *currentSinger = *pListAll;
            }
        
        printf("\n\t [ Mahasiswa yang bernyanyi berikutnya ]\n");
        printf("\n\t Nama: %s", (*currentSinger) -> nama);
        printf("\n\t Jenis Kelamin: %c", (*currentSinger) -> jenis_kelamin);
    }
    
    getch();
}

//============================================================

void siapaNyanyiMhs(Mhs *currentSinger){
    system("cls");

    if(currentSinger == NULL){
        printf("\n\t Tidak ada Mahasiswa yang sedang Bernyanyi!\n");
    } else{
        printf("\n\t [ Mahasiswa yang bernyanyi saat ini ]\n");
        printf("\n\t Nama: %s", currentSinger-> nama);
        printf("\n\t Jenis Kelamin: %c", currentSinger -> jenis_kelamin);
    }
    
    getch();
}

//============================================================

void pisahCircle(Mhs **pListAll, Mhs **pListMhs, Mhs **pListMhsi) {
    Mhs *curAll = *pListAll;
    Mhs *prevAll = NULL;
    
    system("cls");

    if (*pListAll == NULL) {
        printf("\n\t Tidak ada Lingkaran Mahasiswa!\n");
        getch();
        return;
    }

    *pListMhs = NULL; 
    *pListMhsi = NULL;

    while (curAll != NULL) {
        Mhs *temp = curAll -> next;

        // Buat salinan
        Mhs *newNode = (Mhs *)malloc(sizeof(Mhs));

        if (newNode == NULL) {
            printf("\n\t Alokasi Memori gagal!\n");
            getch();
            return;
        }

        // Salin data ke newNode
        strcpy(newNode -> nama, curAll -> nama);
        newNode -> jenis_kelamin = curAll -> jenis_kelamin;
        newNode -> next = NULL;

        if (toupper(curAll -> jenis_kelamin) == 'L') {
            // Tambah Mhs laki-laki ke list Mahasiswa
            if (*pListMhs == NULL) {
                *pListMhs = newNode;
            } else {
                newNode -> next = *pListMhs;
                *pListMhs = newNode;
            }
        } else if (toupper(curAll -> jenis_kelamin) == 'P') {
            // Tambah Mhs perempuan ke list Mahasiswi
            if (*pListMhsi == NULL) {
                *pListMhsi = newNode;
            } else {
                newNode -> next = *pListMhsi;
                *pListMhsi = newNode;
            }
        }

        curAll = temp;
    }
    
    // Menampilkan daftar Mahasiswa
    printf("\n\t ====================");
    printf("\n\t Lingkaran Mahasiswa");
    printf("\n\t ====================");
    tampilkanDaftar(*pListMhs);

    // Menampilkan daftar Mahasiswi
    printf("\n\n\t ====================");
    printf("\n\t Lingkaran Mahasiswi");
    printf("\n\t ====================");
    tampilkanDaftar(*pListMhsi);

}
