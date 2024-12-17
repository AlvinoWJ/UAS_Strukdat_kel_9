#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

// Struktur untuk Kelas (Double Linked List)
typedef struct NodeKelas
{
    char namaKelas[50];
    struct NodeKelas *prev;
    struct NodeKelas *next;
} NodeKelas;

// Fungsi untuk memvalidasi nama kelas yang unik

// Fungsi untuk mengedit nama kelas

// Struktur untuk Stack Aktivitas

// Struktur untuk Queue Belajar (Queue)
typedef struct NodeQ
{
    char materi[50];
    struct NodeQ *next;
} NodeQ;

typedef struct Que
{
    NodeQ *frontQ; // Elemen depan antrian
    NodeQ *rearQ;  // Elemen belakang antrian
    int count;     // Jumlah elemen dalam antrian
} Que;

// Struktur untuk Tugas (Single Linked List)

// Variabel Global

// menu utama

// Menu kelas
void menuKelas(DaftarKelas *daftar)
{
    int pilihan;
    do
    {
        printf("\n--- Menu Kelas ---\n");
        printf("1. Tambah Kelas\n");
        printf("2. Hapus Kelas\n");
        printf("3. Kembali ke Menu Utama\n");
        printf("Pilih menu (1-3): ");
        scanf("%d", &pilihan);
        getchar(); // Membersihkan newline

        switch (pilihan)
        {
        case 1:
            tambahKelas(daftar);
            break;
        case 2:
            hapusKelas(daftar);
            break;
        case 3:
            printf("Kembali ke Menu Utama.\n");
            break;
        default:
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    } while (pilihan != 4);
}

// menu Aktifitas
void menuAktivitas()
{
    int pilihan;
    char deskripsi[100];

    do
    {
        printf("\n--- Menu Aktivitas ---\n");
        printf("1. Tambah Aktivitas\n");
        printf("2. Hapus Aktivitas\n");
        printf("3. Lihat Riwayat Aktivitas\n");
        printf("4. Kembali ke Menu Utama\n");
        printf("Pilih menu (1-4): ");
        scanf("%d", &pilihan);
        getchar();

        switch (pilihan)
        {
        case 1:
            printf("Masukkan deskripsi aktivitas: ");
            fgets(deskripsi, sizeof(deskripsi), stdin);
            deskripsi[strcspn(deskripsi, "\n")] = '\0';
            pushAktivitas(deskripsi);
            break;

        case 2:
            popAktivitas();
            break;

        case 3:
            tampilkanAktivitas();
            break;

        case 4:
            printf("Kembali ke Menu Utama.\n");
            break;

        default:
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }

    } while (pilihan != 4);
}

// menu antrian belajar (Queue)

// menu tugas

// Fungsi kelas
void tambahKelas(DaftarKelas *daftar)
{
    char namaKelas[50];
    printf("Masukkan nama kelas baru: ");
    fgets(namaKelas, sizeof(namaKelas), stdin);
    namaKelas[strcspn(namaKelas, "\n")] = '\0';

    NodeKelas *kelasBaruNode = (NodeKelas *)malloc(sizeof(NodeKelas));
    if (kelasBaruNode == NULL)
    {
        printf("Gagal mengalokasikan memori untuk kelas baru.\n");
        return;
    }

    strcpy(kelasBaruNode->namaKelas, namaKelas);
    kelasBaruNode->prev = NULL;
    kelasBaruNode->next = NULL;

    if (daftar->head == NULL)
    {
        // Jika daftar kosong
        daftar->head = kelasBaruNode;
        daftar->tail = kelasBaruNode;
    }
    else
    {
        // Tambahkan di akhir daftar
        kelasBaruNode->prev = daftar->tail;
        daftar->tail->next = kelasBaruNode;
        daftar->tail = kelasBaruNode;
    }

    daftar->count++;
    printf("Kelas '%s' berhasil ditambahkan.\n", namaKelas);
}

// Fungsi untuk menghapus kelas
void hapusKelas(DaftarKelas *daftar)
{
    if (daftar->head == NULL)
    {
        printf("Tidak ada kelas untuk dihapus.\n");
        return;
    }

    char namaKelas[50];
    printf("Masukkan nama kelas yang akan dihapus: ");
    fgets(namaKelas, sizeof(namaKelas), stdin);
    namaKelas[strcspn(namaKelas, "\n")] = '\0';

    NodeKelas *current = daftar->head;
    while (current != NULL)
    {
        if (strcmp(current->namaKelas, namaKelas) == 0)
        {
            // Hapus node yang ditemukan
            if (current->prev != NULL)
            {
                current->prev->next = current->next;
            }
            else
            {
                // Jika node adalah head
                daftar->head = current->next;
            }

            if (current->next != NULL)
            {
                current->next->prev = current->prev;
            }
            else
            {
                // Jika node adalah tail
                daftar->tail = current->prev;
            }

            free(current);
            daftar->count--;
            printf("Kelas '%s' berhasil dihapus.\n", namaKelas);
            return;
        }
        current = current->next;
    }

    printf("Kelas '%s' tidak ditemukan.\n", namaKelas);
}

// Fungsi Aktifitas
typedef struct Aktivitas
{
    char deskripsi[100];
    struct Aktivitas *next;
} Aktivitas;

Aktivitas *top = NULL;

void pushAktivitas(const char *deskripsi)
{
    if (strlen(deskripsi) >= 100)
    {
        printf("Deskripsi terlalu panjang. Maksimum 100 karakter.\n");
        return;
    }

    Aktivitas *aktivitasBaru = (Aktivitas *)malloc(sizeof(Aktivitas));
    if (aktivitasBaru == NULL)
    {
        printf("Gagal mengalokasikan memori untuk aktivitas baru.\n");
        return;
    }

    strncpy(aktivitasBaru->deskripsi, deskripsi, sizeof(aktivitasBaru->deskripsi) - 1);
    aktivitasBaru->deskripsi[sizeof(aktivitasBaru->deskripsi) - 1] = '\0';

    aktivitasBaru->next = top;
    top = aktivitasBaru;

    printf("Aktivitas '%s' berhasil ditambahkan.\n", deskripsi);
}

void popAktivitas()
{
    if (top == NULL)
    {
        printf("Tidak ada aktivitas untuk dihapus.\n");
        return;
    }

    Aktivitas *temp = top;
    top = top->next;

    printf("Aktivitas '%s' berhasil dihapus.\n", temp->deskripsi);
    free(temp);
}

void tampilkanAktivitas()
{
    if (top == NULL)
    {
        printf("Tidak ada riwayat aktivitas.\n");
        return;
    }

    Aktivitas *temp = top;
    int count = 0;

    printf("Riwayat Aktivitas:\n");
    while (temp != NULL)
    {
        printf("%d. %s\n", ++count, temp->deskripsi);
        temp = temp->next;
    }
}

// Fungsi antrian belajar (queue)
void defineque(Que *q)
{
    q->count = 0;
    q->frontQ = NULL;
    q->rearQ = NULL;
}

void enqueue(Que *q)
{
    char inputMateri[50];
    printf("Masukkan nama materi: ");
    fgets(inputMateri, sizeof(inputMateri), stdin);
    inputMateri[strcspn(inputMateri, "\n")] = '\0';

    NodeQ *nodeQbaru = (NodeQ *)malloc(sizeof(NodeQ));
    if (nodeQbaru == NULL)
    {
        printf("Gagal mengalokasikan memori untuk node baru.\n");
        return;
    }
    strcpy(nodeQbaru->materi, inputMateri);
    nodeQbaru->next = NULL;

    if (q->rearQ == NULL)
    { // Jika queue kosong
        q->frontQ = q->rearQ = nodeQbaru;
    }
    else
    { // Jika queue tidak kosong
        q->rearQ->next = nodeQbaru;
        q->rearQ = nodeQbaru;
    }
    q->count++;
    printf("Materi '%s' berhasil ditambahkan.\n", inputMateri);
}

void dequeue(Que *q)
{
    if (q->frontQ == NULL)
    {
        printf("Tidak ada materi yang tersedia untuk dipelajari.\n");
        return;
    }
    NodeQ *temp = q->frontQ;
    printf("Materi '%s' selesai dipelajari.\n", temp->materi);

    q->frontQ = q->frontQ->next;
    if (q->frontQ == NULL)
    { // Jika queue menjadi kosong
        q->rearQ = NULL;
    }
    free(temp);
    q->count--;
}

void tampilkanAntrianBelajar(Que *q)
{
    if (q->frontQ == NULL)
    {
        printf("Queue kosong! Tidak ada materi yang tersedia.\n");
        return;
    }
    printf("Daftar materi belajar:\n");
    NodeQ *curr = q->frontQ;
    while (curr != NULL)
    {
        printf("- %s\n", curr->materi);
        curr = curr->next;
    }
}

void matericurrent(Que *q)
{
    if (q->frontQ == NULL)
    {
        printf("Tidak ada materi yang sedang dipelajari.\n");
    }
    else
    {
        printf("Materi saat ini: %s\n", q->frontQ->materi);
    }
}

// Fungsi menu tugas
