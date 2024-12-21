#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

// Struktur untuk Ujian [alvin0]
typedef struct Ujian
{
    char namaUjian[50];
    int nilai;
    struct Ujian *next;
} Ujian;

// fungsi fitur ujian [alvin]
int isKelasSelesai(const char *namaKelas)
{
    KelasNode *current = daftarLearningPath;
    while (current != NULL)
    {
        if (strcmp(current->namaKelas, namaKelas) == 0)
        {
            Modul *currentModul = current->daftarModul;
            while (currentModul != NULL)
            {
                if (!currentModul->selesai)
                {
                    return 0; // Not all modules are completed
                }
                currentModul = currentModul->next;
            }
            return 1; // All modules are completed
        }
        current = current->next;
    }
    return 0; // Class not found
}

void tambahUjian(const char *namaKelas)
{
    Ujian *newUjian = (Ujian *)malloc(sizeof(Ujian));
    if (newUjian == NULL)
    {
        printf("Gagal mengalokasikan memori untuk ujian.\n");
        return;
    }

    sprintf(newUjian->namaUjian, "Ujian %s", namaKelas);
    newUjian->nilai = 0;
    newUjian->next = NULL;

    if (daftarUjian == NULL)
    {
        daftarUjian = newUjian;
    }
    else
    {
        Ujian *current = daftarUjian;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newUjian;
    }
}

void ikutUjian(const char *namaKelas)
{
    if (!isKelasSelesai(namaKelas))
    {
        printf("Anda belum menyelesaikan semua modul pada kelas %s.\n", namaKelas);
        return;
    }

    // Simulate an exam with random questions
    printf("\n=== Ujian Kelas %s ===\n", namaKelas);
    int totalPertanyaan = 5;
    int jawabanBenar = 0;

    for (int i = 1; i <= totalPertanyaan; i++)
    {
        int jawaban;
        printf("\nPertanyaan %d:\n", i);
        printf("Berapa hasil dari %d + %d?\n", i * 2, i * 3);
        printf("Jawaban Anda: ");
        scanf("%d", &jawaban);

        if (jawaban == i * 2 + i * 3)
        {
            jawabanBenar++;
        }
    }

    // Calculate and save the score
    int nilai = (jawabanBenar * 100) / totalPertanyaan;

    Ujian *current = daftarUjian;
    while (current != NULL)
    {
        if (strstr(current->namaUjian, namaKelas) != NULL)
        {
            current->nilai = nilai;
            break;
        }
        current = current->next;
    }

    printf("\nNilai Ujian: %d\n", nilai);

    // Record the activity
    char aktivitas[100];
    sprintf(aktivitas, "Mengikuti ujian %s dengan nilai %d", namaKelas, nilai);
    pushAktivitas(aktivitas);
}

void lihatHasilUjian()
{
    if (daftarUjian == NULL)
    {
        printf("Belum ada ujian yang diikuti.\n");
        return;
    }

    printf("\n=== Hasil Ujian ===\n");
    Ujian *current = daftarUjian;
    int no = 1;
    while (current != NULL)
    {
        printf("%d. %s\n", no++, current->namaUjian);
        printf("   Nilai: %d\n", current->nilai);
        current = current->next;
    }
}