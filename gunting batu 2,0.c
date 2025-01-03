#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

void bersihkanLayar() {
    system("cls");
}

void setWarna(int warna) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), warna);
}

void tampilkanScoreboardRec(FILE *file) {
    char nama[50];
    int skor;

    if (fscanf(file, "%s %d", nama, &skor) == 2) {
        printf("%s - %d\n", nama, skor);
        tampilkanScoreboardRec(file);
    }
}

void tampilkanScoreboard() {
    FILE *file = fopen("scoreboard.txt", "r");
    if (file == NULL) {
        printf("Tidak ada data scoreboard.\n");
        return;
    }

    printf("\nScoreboard:\n");
    printf("Nama Pemain - Kemenangan\n");

    tampilkanScoreboardRec(file);

    fclose(file);
}

void simpanScoreboard(const char *nama, int kemenangan) {
    FILE *file = fopen("scoreboard.txt", "r+");
    if (file == NULL) {
        printf("Gagal membuka file scoreboard.\n");
        return;
    }

    char buffer[50];
    int found = 0;
    int tempScores[50];
    char tempNames[50][50];
    int i = 0;

    while (fscanf(file, "%s %d", tempNames[i], &tempScores[i]) == 2) {
        if (strcmp(tempNames[i], nama) == 0) {
            tempScores[i] += 1;
            found = 1;
        }
        i++;
    }

    fclose(file);

    file = fopen("scoreboard.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file scoreboard.\n");
        return;
    }

    int j;
    for (j = 0; j < i; j++) {
        fprintf(file, "%s %d\n", tempNames[j], tempScores[j]);
    }

    if (!found) {
        fprintf(file, "%s %d\n", nama, 1);
    }

    fclose(file);
}

void tampilkanPilihan(int *pilihan) {
    const char *pilihanList[] = {"Gunting", "Batu", "Kertas"};
    int i;

    for (i = 0; i < 3; i++) {
        if (i == *pilihan) {
            setWarna(12);
        } else {
            setWarna(7);
        }
        printf(">>> %s\n", pilihanList[i]);
    }
    setWarna(7);
}

void tampilkanPilihanDanHasil(int *pilihanPemain1, int *pilihanPemain2, char *namaPemain1, char *namaPemain2) {
    const char *pilihanList[] = {"Gunting", "Batu", "Kertas"};
    
    printf("\n%s memilih: %s\n", namaPemain1, pilihanList[*pilihanPemain1]);
    printf("%s memilih: %s\n", namaPemain2, pilihanList[*pilihanPemain2]);
}

int main() {
    int scorePemain1 = 0, scorePemain2 = 0;
    int targetScore;
    int pilihanPemain1 = 0, pilihanPemain2 = 0;
    int round = 1;
    char namaPemain1[50], namaPemain2[50];
    int bermainLagi = 1;

    while (bermainLagi) {
        tampilkanScoreboard();
        printf("\nApakah Anda ingin memulai permainan? (1: Ya, 0: Tidak): ");
        int mulai;
        scanf("%d", &mulai);
        
        if (mulai != 1) {
            return 0;
        }

        printf("Masukkan nama Pemain 1: ");
        scanf("%s", namaPemain1);
        printf("Masukkan nama Pemain 2: ");
        scanf("%s", namaPemain2);

        printf("Masukkan skor yang diperlukan untuk menang: ");
        scanf("%d", &targetScore);

        bersihkanLayar();

        while (scorePemain1 < targetScore && scorePemain2 < targetScore) {
            printf("\nRound %d\n", round);

            printf("%s, pilih pilihan (gunakan panah atas dan bawah):\n", namaPemain1);
            while (1) {
                tampilkanPilihan(&pilihanPemain1);
                int key = getch();
                if (key == 224) {
                    key = getch();
                    if (key == 72) {
                        pilihanPemain1 = (pilihanPemain1 == 0) ? 2 : pilihanPemain1 - 1;
                    } else if (key == 80) {
                        pilihanPemain1 = (pilihanPemain1 == 2) ? 0 : pilihanPemain1 + 1;
                    }
                }
                if (key == 13) break;
                bersihkanLayar();
                printf("%s, pilih pilihan (gunakan panah atas dan bawah):\n", namaPemain1);
            }

            bersihkanLayar();

            printf("%s, pilih pilihan (gunakan panah atas dan bawah):\n", namaPemain2);
            while (1) {
                tampilkanPilihan(&pilihanPemain2);
                int key = getch();
                if (key == 224) {
                    key = getch();
                    if (key == 72) {
                        pilihanPemain2 = (pilihanPemain2 == 0) ? 2 : pilihanPemain2 - 1;
                    } else if (key == 80) {
                        pilihanPemain2 = (pilihanPemain2 == 2) ? 0 : pilihanPemain2 + 1;
                    }
                }
                if (key == 13) break;
                bersihkanLayar();
                printf("%s, pilih pilihan (gunakan panah atas dan bawah):\n", namaPemain2);
            }

            bersihkanLayar();

            tampilkanPilihanDanHasil(&pilihanPemain1, &pilihanPemain2, namaPemain1, namaPemain2);

            if (pilihanPemain1 == pilihanPemain2) {
                printf("Hasil: Seri!\n");
            } else if ((pilihanPemain1 == 0 && pilihanPemain2 == 2) ||
                    (pilihanPemain1 == 1 && pilihanPemain2 == 0) ||
                    (pilihanPemain1 == 2 && pilihanPemain2 == 1)) {
                printf("%s menang!\n", namaPemain1);
                scorePemain1++;
            } else {
                printf("%s menang!\n", namaPemain2);
                scorePemain2++;
            }

            printf("Skor: %s: %d, %s: %d\n", namaPemain1, scorePemain1, namaPemain2, scorePemain2);
            printf("Tekan Enter untuk melanjutkan ke ronde berikutnya...\n");
            getchar();
            getchar();
            round++;
            bersihkanLayar();
        }

        if (scorePemain1 >= targetScore) {
            printf("\nSelamat! %s menang dengan skor %d!\n", namaPemain1, scorePemain1);
            simpanScoreboard(namaPemain1, scorePemain1);
        } else {
            printf("\nSelamat! %s menang dengan skor %d!\n", namaPemain2, scorePemain2);
            simpanScoreboard(namaPemain2, scorePemain2);
        }

        printf("\nApakah Anda ingin bermain lagi/melihat scoreboard? (1: Ya, 0: Tidak): ");
        scanf("%d", &bermainLagi);
        bersihkanLayar();
        if (bermainLagi) {
            scorePemain1 = 0;
            scorePemain2 = 0;
            round = 1;
        } else {
            printf("Terima kasih sudah bermain!\n");
        }
    }

    return 0;
}

