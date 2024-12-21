#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

// Struktur untuk Modul Pembelajaran [efandy]
typedef struct Modul {
    char namaModul[100];
    int selesai; // Flag untuk menandai modul yang sudah selesai
    struct Modul* next;
} Modul;

// Struktur untuk Kelas (Learning Path) [efandy]
typedef struct KelasNode {
    char namaKelas[50];
    Modul* daftarModul;
    struct KelasNode* next;
} KelasNode;

// Struktur untuk (antrian) Queue Belajar [wardhana]
typedef struct NodeQ {
    char materi[50];
    struct NodeQ *next;
} NodeQ;

typedef struct Que {
    NodeQ *frontQ;
    NodeQ *rearQ;
    int count;
} Que;

// Struktur untuk Ujian [alvin0]
typedef struct Ujian
{
    char namaUjian[50];
    int nilai;
    struct Ujian *next;
} Ujian;

// Inisialisasi Learning Path dengan Modul-modulnya [efandy]
void inisialisasiLearningPath() {
    // Web Programming
    KelasNode* webProg = (KelasNode*)malloc(sizeof(KelasNode));
    strcpy(webProg->namaKelas, "Web Programming");
    webProg->daftarModul = NULL;
    
    Modul* modulWeb[] = {
        (Modul*)malloc(sizeof(Modul)),
        (Modul*)malloc(sizeof(Modul)),
        (Modul*)malloc(sizeof(Modul)),
        (Modul*)malloc(sizeof(Modul))
    };
    
    strcpy(modulWeb[0]->namaModul, "HTML & CSS Dasar");
    strcpy(modulWeb[1]->namaModul, "JavaScript Fundamental");
    strcpy(modulWeb[2]->namaModul, "Backend Development");
    strcpy(modulWeb[3]->namaModul, "Frontend Framework");
    
    for(int i = 0; i < 4; i++) {
        modulWeb[i]->selesai = 0;
    }
    
    for(int i = 0; i < 3; i++) {
        modulWeb[i]->next = modulWeb[i+1];
    }
    modulWeb[3]->next = NULL;
    webProg->daftarModul = modulWeb[0];
    
    // Mobile Development
    KelasNode* mobile = (KelasNode*)malloc(sizeof(KelasNode));
    strcpy(mobile->namaKelas, "Mobile Development");
    mobile->daftarModul = NULL;
    
    Modul* modulMobile[] = {
        (Modul*)malloc(sizeof(Modul)),
        (Modul*)malloc(sizeof(Modul)),
        (Modul*)malloc(sizeof(Modul)),
        (Modul*)malloc(sizeof(Modul))
    };
    
    strcpy(modulMobile[0]->namaModul, "Mobile UI/UX");
    strcpy(modulMobile[1]->namaModul, "Native Development");
    strcpy(modulMobile[2]->namaModul, "Cross Platform Development");
    strcpy(modulMobile[3]->namaModul, "Mobile Backend Integration");
    
    for(int i = 0; i < 4; i++) {
        modulMobile[i]->selesai = 0;
    }
    
    for(int i = 0; i < 3; i++) {
        modulMobile[i]->next = modulMobile[i+1];
    }
    modulMobile[3]->next = NULL;
    mobile->daftarModul = modulMobile[0];
    
        // Data Analysis
    KelasNode* dataAnalysis = (KelasNode*)malloc(sizeof(KelasNode));
    strcpy(dataAnalysis->namaKelas, "Data Analysis");
    dataAnalysis->daftarModul = NULL;
    
    Modul* modulDA[] = {
        (Modul*)malloc(sizeof(Modul)),
        (Modul*)malloc(sizeof(Modul)),
        (Modul*)malloc(sizeof(Modul)),
        (Modul*)malloc(sizeof(Modul))
    };
    
    strcpy(modulDA[0]->namaModul, "Statistical Analysis");
    strcpy(modulDA[1]->namaModul, "Data Visualization");
    strcpy(modulDA[2]->namaModul, "Machine Learning Basics");
    strcpy(modulDA[3]->namaModul, "Big Data Processing");
    
    for(int i = 0; i < 3; i++) {
        modulDA[i]->next = modulDA[i+1];
    }
    modulDA[3]->next = NULL;
    dataAnalysis->daftarModul = modulDA[0];
    
    // Software Developer
    KelasNode* softDev = (KelasNode*)malloc(sizeof(KelasNode));
    strcpy(softDev->namaKelas, "Software Developer");
    softDev->daftarModul = NULL;
    
    Modul* modulSD[] = {
        (Modul*)malloc(sizeof(Modul)),
        (Modul*)malloc(sizeof(Modul)),
        (Modul*)malloc(sizeof(Modul)),
        (Modul*)malloc(sizeof(Modul))
    };
    
    strcpy(modulSD[0]->namaModul, "Programming Fundamentals");
    strcpy(modulSD[1]->namaModul, "Data Structures & Algorithms");
    strcpy(modulSD[2]->namaModul, "Software Architecture");
    strcpy(modulSD[3]->namaModul, "Software Testing");
    
    for(int i = 0; i < 3; i++) {
        modulSD[i]->next = modulSD[i+1];
    }
    modulSD[3]->next = NULL;
    softDev->daftarModul = modulSD[0];

    
    webProg->next = mobile;
    mobile->next = NULL; // Untuk contoh ini kita singkat menjadi 2 kelas saja
    
    daftarLearningPath = webProg;
}

void tampilkanLearningPath() {
    KelasNode* current = daftarLearningPath;
    int nomor = 1;
    
    printf("\n=== Learning Path yang Tersedia ===\n");
    while(current != NULL) {
        printf("\n%d. %s\n", nomor++, current->namaKelas);
        printf("   Modul-modul:\n");
        
        Modul* currentModul = current->daftarModul;
        int nomorModul = 1;
        while(currentModul != NULL) {
            printf("   %d.%d. %s", nomor-1, nomorModul++, currentModul->namaModul);
            if(currentModul->selesai) printf(" [✓]");
            printf("\n");
            currentModul = currentModul->next;
        }
        current = current->next;
    }
}

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
