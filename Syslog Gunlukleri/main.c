#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOG_MESAJ_BOYUTU 512
#define SYSLOG_DOSYA "/var/log/syslog"

// Syslog kaydi icin bagli liste dugum yapisi
typedef struct LogDugum {
    char mesaj[LOG_MESAJ_BOYUTU];
    struct LogDugum* sonraki;
} LogDugum;

// Yeni bir dugum olusturup dugumu listenin basina ekler
void basaEkle(LogDugum** head, const char* msg) {
    LogDugum* yeniDugum = (LogDugum*)malloc(sizeof(LogDugum)); // Yeni bir dugum icin dinamik bellek tahsis edilir
    if (yeniDugum == NULL) {
        perror("Bellek tahsisi basarisiz");
        exit(EXIT_FAILURE);
    }
    strncpy(yeniDugum->mesaj, msg, LOG_MESAJ_BOYUTU - 1);  // Syslog mesaji dugumun icine kopyalanir
    yeniDugum->mesaj[LOG_MESAJ_BOYUTU - 1] = '\0';  // Guvenlik icin sonlandirici karakter
    yeniDugum->sonraki = *head; 
    *head = yeniDugum; // Yeni dugum listenin bas isaretcisi olur
}

// Syslog mesajlarini yazdirir
void loglariYazdir(LogDugum* head) {
    LogDugum* gecici = head;
    while (gecici != NULL) {  // Listenin sonuna gelene kadar mesajlari sirayla yazdiran dongu
        printf("%s\n", gecici->mesaj);
        gecici = gecici->sonraki;
    }
}

// Baðli listeyi temizler
void loglariTemizle(LogDugum* head) {
    LogDugum* gecici;
    while (head != NULL) {  // Listenin sonuna gelene kadar listenin basini kaydirip onceki bas dugumun bellegini serbest birakan dongu
        gecici = head;
        head = head->sonraki;
        free(gecici);
    }
}

// Syslog dosyasini okur ve loglari listeye ekler
void syslogOku(LogDugum** logListe) {
    FILE* dosya = fopen(SYSLOG_DOSYA, "r");
    if (dosya == NULL) {
        perror("Syslog dosyasi acilamadi");
        return;
    }
    char buffer[LOG_MESAJ_BOYUTU];
    while (fgets(buffer, LOG_MESAJ_BOYUTU, dosya) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0'; // Yeni satir karakterini temizle
        basaEkle(logListe, buffer); // Yeni loglari basa ekle
    }
    fclose(dosya);
}

int main() {
    LogDugum* logListe = NULL;
    
    // Syslog dosyasini oku
    syslogOku(&logListe);
    
    // Loglari yazdir
    printf("Syslog Mesajlari:\n");
    loglariYazdir(logListe);
    
    // Bellegi temizle
    loglariTemizle(logListe);
    
    return 0;
}

