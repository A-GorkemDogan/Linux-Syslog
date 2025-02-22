# Syslog Kayıtlarını Bağlı Liste ile İşleme

Bu proje, **C programlama dili** kullanılarak **Linux işletim sisteminde syslog kayıtlarını** okuyup işleyebilen bir **tek yönlü bağlı liste** uygulamasıdır. Yeni syslog kayıtları **listenin başına** eklenir ve en güncel kayıtlar en önce görüntülenir.

## 📌 Özellikler
- `/var/log/syslog` dosyasını okuyarak kayıtları işler.
- **Tek yönlü bağlı liste** veri yapısını kullanır.
- **Yeni kayıtları en üste ekleyerek (O(1)) hız sağlar.**
- **Bellek sızıntısını önlemek için dinamik bellek yönetimi içerir.**

## 🚀 Kurulum ve Çalıştırma

### **1️⃣ Gerekli Paketleri Yükleyin**

sudo apt update && sudo apt install build-essential


### **2️⃣ Projeyi Klonlayın**

git clone https://github.com/kullaniciadi/syslog-bagli-liste.git
cd syslog-bagli-liste


### **3️⃣ Kaynak Kodunu Derleyin**

gcc -o syslog_reader syslog_reader.c


### **4️⃣ Programı Çalıştırın**

./syslog_reader


## 📜 Kullanım
Program çalıştırıldığında, **syslog kayıtlarını okuyarak** aşağıdaki formatta ekrana yazdırır:

[Tarih] [IP] [Olay Bilgisi]

Örneğin:

Feb 21 14:55:32 192.168.1.10 SSH login success
Feb 21 14:50:10 192.168.1.11 Failed password attempt


## 🛠 Fonksiyonlar

| Fonksiyon | Açıklama |
|-----------|----------|
| basaEkle() | Yeni bir syslog kaydını bağlı listenin başına ekler. |
| loglariYazdir() | Tüm syslog kayıtlarını ekrana yazdırır. |
| loglariTemizle() | Bellekteki tüm syslog kayıtlarını serbest bırakır. |
