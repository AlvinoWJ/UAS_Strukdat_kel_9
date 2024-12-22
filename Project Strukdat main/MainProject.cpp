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

// Struktur untuk Daftar Kelas yang Diambil User (Double Linked List) [rafif]
typedef struct NodeKelas {
    char namaKelas[50];
    int progress; // Persentase progress (0-100)
    struct NodeKelas *prev;
    struct NodeKelas *next;
} NodeKelas;

typedef struct DaftarKelas {
    NodeKelas *head;
    NodeKelas *tail;
    int count;
} DaftarKelas;

// Struktur untuk Stack Aktivitas [yazid]
typedef struct Aktivitas {
    char deskripsi[100];
    struct Aktivitas *next;
} Aktivitas;

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

typedef struct Soal {
    char pertanyaan[200];
    char pilihan[4][100];
    int jawabanBenar;
} Soal;

// Bank soal untuk setiap kelas
Soal soalWebProgramming[] = {
    {
        "Apa kepanjangan dari HTML?",
        {"HyperText Markup Language", "HighText Modern Language", "HyperText Modern Link", "HighText Markup Link"},
        0
    },
    {
        "Properti CSS yang digunakan untuk mengatur jarak antara elemen adalah?",
        {"spacing", "margin", "padding", "border"},
        1
    },
    {
        "Fungsi JavaScript yang digunakan untuk menampilkan dialog konfirmasi adalah?",
        {"alert()", "prompt()", "confirm()", "message()"},
        2
    },
    {
        "Framework JavaScript yang populer untuk pengembangan frontend adalah?",
        {"Django", "Flask", "Laravel", "React"},
        3
    },
    {
        "Metode HTTP yang digunakan untuk mengirim data form adalah?",
        {"POST", "GET", "PUT", "DELETE"},
        0
    }
};

Soal soalMobileDevelopment[] = {
    {
        "Bahasa pemrograman utama untuk pengembangan Android native adalah?",
        {"Swift", "Kotlin", "JavaScript", "Python"},
        1
    },
    {
        "Framework cross-platform untuk pengembangan mobile adalah?",
        {"Angular", "Vue", "React Native", "Laravel"},
        2
    },
    {
        "Tool untuk mendesain UI/UX mobile app adalah?",
        {"Figma", "WordPress", "Visual Studio", "NetBeans"},
        0
    },
    {
        "Database yang sering digunakan dalam pengembangan mobile adalah?",
        {"MongoDB", "SQLite", "Redis", "Cassandra"},
        1
    },
    {
        "Komponen Android yang berfungsi sebagai layar/halaman adalah?",
        {"Service", "Activity", "Content Provider", "Broadcast Receiver"},
        1
    }
};

// Variabel Global [cludia]
Aktivitas *top = NULL;
KelasNode* daftarLearningPath = NULL;
Ujian* daftarUjian = NULL;

//fungsi 
void tambahKelas(DaftarKelas *daftar, const char *namaKelas);
void updateProgress(DaftarKelas *daftar, const char *namaKelas, int newProgress);
void lihatDaftarKelas(DaftarKelas *daftar);
void inisialisasiLearningPath();
void tampilkanLearningPath();
void pushAktivitas(const char *deskripsi);
void lihatAktivitas();
void enqueue(Que *q, char *materi);
void dequeue(Que *q, DaftarKelas *daftar, const char *namaKelas);
int isKelasSelesai(const char *namaKelas, DaftarKelas *daftar);
void tambahUjian(const char *namaKelas);
void ikutUjian(const char *namaKelas);
void lihatHasilUjian();
void aksesMateriPembelajaran(DaftarKelas *kelasUser, Que *antrianBelajar, char *kelasSekarang);
void mainMenu();

//fungsi utama
int main() {
    inisialisasiLearningPath();
    mainMenu();
    return 0;
}
// Main Menu [claudia]
void mainMenu() {
    DaftarKelas kelasUser = {NULL, NULL, 0};
    Que antrianBelajar = {NULL, NULL, 0};
    char kelasSekarang[50] = "";
    int pilihan;
    
    do {
        system("cls");
        printf("\n=== Learning Management System ===\n");
        printf("1. Lihat Learning Path yang Tersedia\n");
        printf("2. Daftar Kelas Baru\n");
        printf("3. Lihat Kelas yang Diambil\n");
        printf("4. Lihat Riwayat Aktivitas\n");
        printf("5. Akses Materi Pembelajaran\n");
        printf("6. Ikut Ujian\n");
        printf("7. Lihat Hasil Ujian\n");
        printf("8. Keluar\n");
        printf("Pilihan Anda: ");
        scanf("%d", &pilihan);
        getchar();
        system("cls");
        
        switch(pilihan) {
            case 1:
                tampilkanLearningPath();
                printf("\nTekan Enter untuk kembali ke menu...");
                getchar();
                break;
                
            case 2: {
                tampilkanLearningPath();
                char namaKelas[50];
                printf("\nMasukkan nama kelas yang ingin diikuti\n(nama kelas harus sama dengan yang ditampilkan): ");
                fgets(namaKelas, sizeof(namaKelas), stdin);
                namaKelas[strcspn(namaKelas, "\n")] = '\0';
                
                // Cek apakah kelas tersedia
                KelasNode* kelas = daftarLearningPath;
                int kelasValid = 0;
                while(kelas != NULL) {
                    if(strcmp(kelas->namaKelas, namaKelas) == 0) {
                        kelasValid = 1;
                        // Tambahkan ke daftar kelas user
                        tambahKelas(&kelasUser, namaKelas);
                        strcpy(kelasSekarang, namaKelas);
                        
                        // Tambahkan modul-modul ke antrian belajar
                        Modul* modul = kelas->daftarModul;
                        while(modul != NULL) {
                            enqueue(&antrianBelajar, modul->namaModul);
                            modul = modul->next;
                        }
                        
                        // Catat aktivitas
                        char aktivitas[100];
                        sprintf(aktivitas, "Mendaftar ke kelas: %s", namaKelas);
                        pushAktivitas(aktivitas);
                        break;
                    }
                    kelas = kelas->next;
                }
                
                if(!kelasValid) {
                    printf("Kelas tidak ditemukan!\n");
                }
                printf("\nTekan Enter untuk kembali ke menu...");
                getchar();
                break;
            }
                
            case 3:
                lihatDaftarKelas(&kelasUser);
                printf("\nTekan Enter untuk kembali ke menu...");
                getchar();
                break;
                
            case 4:
                lihatAktivitas();
                printf("\nTekan Enter untuk kembali ke menu...");
                getchar();
                break;
                
            case 5:
                aksesMateriPembelajaran(&kelasUser, &antrianBelajar, kelasSekarang);
                break;
            case 6: {
                if(kelasUser.head == NULL) {
                    printf("Anda belum mengambil kelas apapun.\n");
                    printf("\nTekan Enter untuk kembali ke menu...");
                    getchar();
                    break;
                }

                printf("\n=== Pilih Kelas untuk Ujian ===\n");
                NodeKelas *current = kelasUser.head;
                int no = 1;
                // Tampilkan hanya kelas dengan progress 100%
                while(current != NULL) {
                    printf("%d. %s (Progress: %d%%)", no++, current->namaKelas, current->progress);
                    if(current->progress == 100) {
                        printf(" [SIAP UJIAN]");
                    }
                    printf("\n");
                    current = current->next;
                }

                int pilihanKelas;
                printf("\nPilih nomor kelas (0 untuk kembali): ");
                scanf("%d", &pilihanKelas);
                getchar();

                if(pilihanKelas == 0) {
                    break;
                }

                if(pilihanKelas < 1 || pilihanKelas > kelasUser.count) {
                    printf("Pilihan kelas tidak valid!\n");
                    printf("\nTekan Enter untuk kembali ke menu...");
                    getchar();
                    break;
                }

                // Dapatkan kelas yang dipilih
                current = kelasUser.head;
                for(int i = 1; i < pilihanKelas; i++) {
                    current = current->next;
                }

                // Cek progress kelas
                if(current->progress < 100) {
                    printf("\nAnda belum menyelesaikan semua materi pada kelas %s.\n", current->namaKelas);
                    printf("Progress saat ini: %d%%\n", current->progress);
                    printf("Selesaikan semua materi terlebih dahulu untuk mengikuti ujian.\n");
                } else {
                    printf("\nMemulai Ujian untuk kelas %s...\n", current->namaKelas);
                    ikutUjian(current->namaKelas);
                }
                
                printf("\nTekan Enter untuk kembali ke menu...");
                getchar();
                break;
            }
            case 7:
                lihatHasilUjian();
                printf("\nTekan Enter untuk kembali ke menu...");
                getchar();
                break;
                
            case 8:
                printf("Terima kasih telah menggunakan sistem ini.\n");
                printf("\nTekan Enter untuk kembali ke menu...");
                getchar();
                break;
                
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while(pilihan != 8);
}

void aksesMateriPembelajaran(DaftarKelas *kelasUser, Que *antrianBelajar, char *kelasSekarang) {
    if(kelasUser->head == NULL) {
        printf("Anda belum mengambil kelas apapun.\n");
        printf("\nTekan Enter untuk kembali ke menu...");
        getchar();
        return;
    }
    
    // Jika hanya ada satu kelas
    if(kelasUser->count == 1) {
        strcpy(kelasSekarang, kelasUser->head->namaKelas);
    } 
    // Jika ada lebih dari satu kelas
    else {
        printf("\n=== Pilih Kelas ===\n");
        NodeKelas *current = kelasUser->head;
        int no = 1;
        while(current != NULL) {
            printf("%d. %s (Progress: %d%%)\n", no++, current->namaKelas, current->progress);
            current = current->next;
        }
        
        int pilihanKelas;
        printf("\nPilih nomor kelas: ");
        scanf("%d", &pilihanKelas);
        system("cls");
        getchar();
        
        // Validasi pilihan dan set kelasSekarang
        if(pilihanKelas >= 1 && pilihanKelas <= kelasUser->count) {
            current = kelasUser->head;
            for(int i = 1; i < pilihanKelas; i++) {
                current = current->next;
            }
            strcpy(kelasSekarang, current->namaKelas);
        } else {
            printf("Pilihan kelas tidak valid!\n");
            printf("\nTekan Enter untuk kembali ke menu...");
            getchar();
            return;
        }
    }

    // Cek apakah kelas sudah 100%
    NodeKelas *currentKelas = kelasUser->head;
    while(currentKelas != NULL && strcmp(currentKelas->namaKelas, kelasSekarang) != 0) {
        currentKelas = currentKelas->next;
    }
    
    if(currentKelas != NULL && currentKelas->progress == 100) {
        printf("\nSelamat! Anda telah menyelesaikan semua modul di kelas %s!\n", kelasSekarang);
        printf("1. Ambil Ujian\n");
        printf("2. Kembali ke Menu Utama\n");
        printf("Pilihan Anda: ");
        int pilihanSelesai;
        scanf("%d", &pilihanSelesai);
        getchar();
        
        if(pilihanSelesai == 1) {
            printf("\nMemulai Ujian untuk kelas %s...\n", kelasSekarang);
            ikutUjian(kelasSekarang);
        }
        printf("\nTekan Enter untuk kembali ke menu...");
        getchar();
        return;
    }
    
    // Menampilkan dan mengakses materi
    int lanjutBelajar = 1;
    while(lanjutBelajar) {
        if(antrianBelajar->frontQ != NULL) {
            printf("\nMateri yang sedang dipelajari: %s\n", antrianBelajar->frontQ->materi);
            printf("1. Selesai mempelajari\n");
            printf("2. Kembali ke menu utama\n");
            printf("Pilihan Anda: ");
            int pilihanMateri;
            scanf("%d", &pilihanMateri);
            getchar();
            
            if(pilihanMateri == 1) {
                printf("\n");
                dequeue(antrianBelajar, kelasUser, kelasSekarang);
                
                // Cek kembali progress setelah dequeue
                currentKelas = kelasUser->head;
                while(currentKelas != NULL && strcmp(currentKelas->namaKelas, kelasSekarang) != 0) {
                    currentKelas = currentKelas->next;
                }
                
                if(currentKelas != NULL && currentKelas->progress == 100) {
                    printf("\nSelamat! Anda telah menyelesaikan semua modul di kelas %s!\n", kelasSekarang);
                    printf("1. Ambil Ujian\n");
                    printf("2. Kembali ke Menu Utama\n");
                    printf("Pilihan Anda: ");
                    int pilihanSelesai;
                    scanf("%d", &pilihanSelesai);
                    getchar();
                    
                    if(pilihanSelesai == 1) {
                        printf("\nMemulai Ujian untuk kelas %s...\n", kelasSekarang);
                        ikutUjian(kelasSekarang);
                    }
                    lanjutBelajar = 0;
                } else if(antrianBelajar->frontQ != NULL) {
                    printf("\nApakah Anda ingin melanjutkan belajar?\n");
                    printf("1. Ya\n");
                    printf("2. Tidak, kembali ke menu utama\n");
                    printf("Pilihan Anda: ");
                    int pilihanLanjut;
                    scanf("%d", &pilihanLanjut);
                    system("cls");
                    getchar();
                    
                    if(pilihanLanjut != 1) {
                        lanjutBelajar = 0;
                    }
                }
            } else {
                lanjutBelajar = 0;
            }
        } else {
            printf("Selamat! Anda telah menyelesaikan semua materi di kelas ini.\n");
            printf("1. Ambil Ujian\n");
            printf("2. Kembali ke Menu Utama\n");
            printf("Pilihan Anda: ");
            int pilihanSelesai;
            scanf("%d", &pilihanSelesai);
            getchar();
            
            if(pilihanSelesai == 1) {
                printf("\nMemulai Ujian untuk kelas %s...\n", kelasSekarang);
                ikutUjian(kelasSekarang);
            }
            lanjutBelajar = 0;
        }
    }
    printf("\nTekan Enter untuk kembali ke menu...");
    getchar();
}

// Fungsi untuk DaftarKelas [rafif]
void tambahKelas(DaftarKelas *daftar, const char *namaKelas) {
    NodeKelas *newNode = (NodeKelas*)malloc(sizeof(NodeKelas));
    strcpy(newNode->namaKelas, namaKelas);
    newNode->progress = 0;
    newNode->prev = NULL;
    newNode->next = NULL;

    if (daftar->head == NULL) {
        daftar->head = daftar->tail = newNode;
    } else {
        newNode->prev = daftar->tail;
        daftar->tail->next = newNode;
        daftar->tail = newNode;
    }
    daftar->count++;
    printf("\nKelas %s berhasil ditambahkan ke daftar kelas Anda.\n", namaKelas);
}

void updateProgress(DaftarKelas *daftar, const char *namaKelas, int newProgress) {
    NodeKelas *current = daftar->head;
    while (current != NULL) {
        if (strcmp(current->namaKelas, namaKelas) == 0) {
            current->progress = newProgress;
            printf("Progress kelas %s diperbarui menjadi %d%%\n", namaKelas, newProgress);
            return;
        }
        current = current->next;
    }
    printf("Kelas %s tidak ditemukan dalam daftar kelas Anda.\n", namaKelas);
}

void lihatDaftarKelas(DaftarKelas *daftar) {
    if (daftar->head == NULL) {
        printf("Anda belum mengambil kelas apapun.\n");
        return;
    }

    printf("\n=== Daftar Kelas yang Diambil ===\n");
    NodeKelas *current = daftar->head;
    int no = 1;
    while (current != NULL) {
        printf("%d. %s (Progress: %d%%)\n", no++, current->namaKelas, current->progress);
        current = current->next;
    }
}


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
// Fungsi untuk mencatat aktivitas (Stack) [yazid]
void pushAktivitas(const char *deskripsi) {
    Aktivitas *aktivitasBaru = (Aktivitas *)malloc(sizeof(Aktivitas));
    if (aktivitasBaru == NULL) {
        printf("Gagal mengalokasikan memori.\n");
        return;
    }
    
    strncpy(aktivitasBaru->deskripsi, deskripsi, sizeof(aktivitasBaru->deskripsi) - 1);
    aktivitasBaru->deskripsi[sizeof(aktivitasBaru->deskripsi) - 1] = '\0';
    aktivitasBaru->next = top;
    top = aktivitasBaru;
}

void lihatAktivitas() {
    if (top == NULL) {
        printf("Tidak ada riwayat aktivitas.\n");
        return;
    }
    
    printf("\n=== Riwayat Aktivitas ===\n");
    Aktivitas* temp = top;
    int i = 1;
    while(temp != NULL) {
        printf("%d. %s\n", i++, temp->deskripsi);
        temp = temp->next;
    }
}

// Fungsi untuk antrian belajar (Queue) [wardhana]
void enqueue(Que *q, char *materi) {
    NodeQ *newNode = (NodeQ*)malloc(sizeof(NodeQ));
    strcpy(newNode->materi, materi);
    newNode->next = NULL;
    
    if(q->rearQ == NULL) {
        q->frontQ = q->rearQ = newNode;
    } else {
        q->rearQ->next = newNode;
        q->rearQ = newNode;
    }
    q->count++;
}

void dequeue(Que *q, DaftarKelas *daftar, const char *namaKelas) {
    if(q->frontQ == NULL) {
        printf("Antrian belajar kosong.\n");
        return;
    }
    
    NodeQ *temp = q->frontQ;
    printf("Selesai mempelajari: %s\n", temp->materi);
    
    // Update progress kelas
    NodeKelas *kelas = daftar->head;
    while(kelas != NULL) {
        if(strcmp(kelas->namaKelas, namaKelas) == 0) {
            int newProgress = kelas->progress + 25; // Setiap modul bernilai 25%
            if(newProgress > 100) newProgress = 100;
            updateProgress(daftar, namaKelas, newProgress);
            break;
        }
        kelas = kelas->next;
    }
    
    q->frontQ = q->frontQ->next;
    if(q->frontQ == NULL) {
        q->rearQ = NULL;
    }
    
    free(temp);
    q->count--;
    
    // Catat aktivitas
    char aktivitas[100];
    sprintf(aktivitas, "Menyelesaikan modul: %s", temp->materi);
    pushAktivitas(aktivitas);
}

// fungsi fitur ujian [alvin]
int isKelasSelesai(const char *namaKelas, DaftarKelas *daftar)
{
    NodeKelas *current = daftar->head;
    while (current != NULL)
    {
        if (strcmp(current->namaKelas, namaKelas) == 0)
        {
            return (current->progress == 100);   
        }
        current = current->next;
    }
    return 0; // Class not found
}

void tambahUjian(const char *namaKelas)
{
    // Cek apakah ujian untuk kelas ini sudah ada
    Ujian *current = daftarUjian;
    while (current != NULL) {
        if (strstr(current->namaUjian, namaKelas) != NULL) {
            // Ujian sudah ada, tidak perlu menambahkan lagi
            return;
        }
        current = current->next;
    }

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
        current = daftarUjian;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newUjian;
    }
}

void ikutUjian(const char *namaKelas)
{
    // Cek apakah ujian sudah ada, jika belum, tambahkan
    tambahUjian(namaKelas);
    system("cls");
    printf("\n=== Ujian %s ===\n", namaKelas);

    // Pilih bank soal berdasarkan kelas
    Soal *bankSoal;
    int jumlahSoal = 5;


        if (strcmp(namaKelas, "Web Programming") == 0) {
        bankSoal = soalWebProgramming;
    } else if (strcmp(namaKelas, "Mobile Development") == 0) {
        bankSoal = soalMobileDevelopment;
    } else {
        printf("Kelas tidak valid\n");
        return;
    }

    int jawabanBenar = 0;

    // Tampilkan soal
    for (int i = 0; i < jumlahSoal; i++) {
        printf("\nSoal %d:\n", i + 1);
        printf("%s\n", bankSoal[i].pertanyaan);
        
        for (int j = 0; j < 4; j++) {
            printf("%d. %s\n", j + 1, bankSoal[i].pilihan[j]);
        }

        int jawaban;
        do {
            printf("Masukkan jawaban (1-4): ");
            scanf("%d", &jawaban);
            getchar(); // Bersihkan buffer
            
            if (jawaban < 1 || jawaban > 4) {
                printf("Jawaban tidak valid. Silakan masukkan angka 1-4.\n");
            }
        } while (jawaban < 1 || jawaban > 4);

        if (jawaban - 1 == bankSoal[i].jawabanBenar) {
            jawabanBenar++;
        }
    }
    // Menghitung nilai
    int nilai = (jawabanBenar * 100) / jumlahSoal;

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

    printf("\n=== Hasil Ujian ===\n");
    printf("Jawaban benar: %d dari %d soal\n", jawabanBenar, jumlahSoal);
    printf("Nilai akhir: %d\n", nilai);
    printf("Status: %s\n", (nilai >= 70) ? "LULUS" : "TIDAK LULUS");

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
        printf("   Status\t: %s\n", (current->nilai >= 70) ? "LULUS" : "TIDAK LULUS");
        printf("   Keterangan\t: ");

        if (current->nilai >= 90) {
            printf("Sangat Baik");
        } else if (current->nilai >= 80) {
            printf("Baik");
        } else if (current->nilai >= 70) {
            printf("Cukup");
        } else {
            printf("Perlu Perbaikan");
        }
        printf("\n");

        current = current->next;
    }
}


