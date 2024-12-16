#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

// Struktur untuk Kelas (Double Linked List)


// Struktur untuk Stack Aktivitas


// Struktur untuk Queue Belajar (Queue)
typedef struct NodeQ{
    char materi[50];
    struct NodeQ *next;
}NodeQ;

typedef struct Que {
    NodeQ *frontQ;           // Elemen depan antrian
    NodeQ *rearQ;            // Elemen belakang antrian
    int count;              // Jumlah elemen dalam antrian
} Que;

// Struktur untuk Tugas (Single Linked List)


// Variabel Global




// menu utama


// Menu kelas 


// menu Aktifitas 


// menu antrian belajar (Queue)


// menu tugas 




// Fungsi kelas 


// Fungsi Aktifitas 


// Fungsi antrian belajar (queue)
void defineque(Que *q){
    q->count = 0;
    q->frontQ = NULL;
    q->rearQ = NULL;
}

void enqueue(Que *q){
    char inputMateri[50];
    printf("Masukkan nama materi: ");
    fgets(inputMateri, sizeof(inputMateri), stdin);
    inputMateri[strcspn(inputMateri, "\n")] = '\0';

    NodeQ *nodeQbaru = (NodeQ *)malloc(sizeof(NodeQ));
    if (nodeQbaru == NULL) {
        printf("Gagal mengalokasikan memori untuk node baru.\n");
        return;
    }
    strcpy(nodeQbaru->materi, inputMateri);
    nodeQbaru->next = NULL;

    if (q->rearQ == NULL) {  // Jika queue kosong
        q->frontQ = q->rearQ = nodeQbaru;
    } else {                // Jika queue tidak kosong
        q->rearQ->next = nodeQbaru;
        q->rearQ = nodeQbaru;
    }
    q->count++;
    printf("Materi '%s' berhasil ditambahkan.\n", inputMateri);
}

void dequeue(Que *q) {
    if (q->frontQ == NULL) {
        printf("Tidak ada materi yang tersedia untuk dipelajari.\n");
        return;
    }
    NodeQ *temp = q->frontQ;
    printf("Materi '%s' selesai dipelajari.\n", temp->materi);

    q->frontQ = q->frontQ->next;
    if (q->frontQ == NULL) { // Jika queue menjadi kosong
        q->rearQ = NULL;
    }
    free(temp);
    q->count--;
}

void tampilkanAntrianBelajar(Que *q) {
    if (q->frontQ == NULL) {
        printf("Queue kosong! Tidak ada materi yang tersedia.\n");
        return;
    }
    printf("Daftar materi belajar:\n");
    NodeQ *curr = q->frontQ;
    while (curr != NULL) {
        printf("- %s\n", curr->materi);
        curr = curr->next;
    }
}

void matericurrent(Que *q) {
    if (q->frontQ == NULL) {
        printf("Tidak ada materi yang sedang dipelajari.\n");
    } else {
        printf("Materi saat ini: %s\n", q->frontQ->materi);
    }
}

// Fungsi menu tugas 
