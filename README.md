# 🎵 Arduino DFPlayer Strict Sequential Audio System

Sistem pemutar audio berbasis Arduino dengan logika **urutan ketat (strict sequential logic)** menggunakan modul DFPlayer Mini.

Project ini dirancang untuk kebutuhan pembelajaran interaktif, sistem evaluasi berbasis audio, serta aplikasi edukatif yang memerlukan kontrol urutan yang disiplin dan tidak dapat dilompati.

---

## 📌 Fitur Utama

- 🔢 10 Tombol Input (INPUT_PULLUP)
- 🔊 Pemutaran audio berdasarkan nomor tombol
- 🚫 Tidak bisa melompat urutan
- 🔁 Bisa mengulang tombol yang sama
- 🔄 Otomatis reset ke tombol 1 setelah tombol 10
- 🔔 Sistem notifikasi buzzer
- 📡 Deteksi lagu selesai menggunakan pin BUSY
- 🧠 Arsitektur modular (OOP)
- 🛠 Siap dikembangkan menjadi sistem quiz atau ujian

---

## 🎯 Konsep Sistem

Sistem menerapkan aturan berikut:

| Kondisi | Status |
|----------|---------|
| Tombol sesuai target | ✅ Diizinkan |
| Tombol berikutnya | ✅ Diizinkan |
| Tombol sebelumnya | ❌ Ditolak |
| Lompat lebih dari 1 | ❌ Ditolak |

Contoh:

Jika target saat ini = 3  
Maka hanya tombol berikut yang boleh ditekan:
- Tombol 3 (ulang)
- Tombol 4 (lanjut)

---

## 🔧 Hardware yang Dibutuhkan

- Arduino Uno / Nano
- DFPlayer Mini
- Speaker 3W (4–8 Ohm)
- 10 Push Button
- Buzzer aktif
- MicroSD Card (FAT32)
- Resistor 1K (disarankan pada RX DFPlayer)

---

## 🔌 Konfigurasi Pin

| Komponen | Pin Arduino |
|----------|-------------|
| DFPlayer RX | 6 |
| DFPlayer TX | 7 |
| DFPlayer BUSY | 10 |
| Buzzer | 11 |
| Tombol 1-4 | 2,3,4,5 |
| Tombol 5-10 | A5,A4,A3,A2,A1,A0 |

---

## 📂 Format File Audio (WAJIB)

MicroSD harus diformat FAT32.

Struktur file:
/mp3
0001.mp3
0002.mp3
...
0010.mp3
Nomor file harus sesuai dengan nomor tombol.

---

## 🔊 Sistem Notifikasi

| Kondisi | Bunyi |
|----------|--------|
| Tombol benar | Beep 150 ms |
| Lagu selesai | Beep 2x 50 ms |
| Salah urutan | Beep 500 ms |

---

### Module Breakdown

**ButtonManager**
- Membaca 10 tombol
- Debounce sederhana
- INPUT_PULLUP mode

**AudioManager**
- Mengontrol DFPlayer
- Mengatur volume
- Memutar track
- Membaca status BUSY

**BuzzerManager**
- Mengelola notifikasi bunyi

**main.ino**
- State-machine logic
- Mengatur sistem urutan ketat

---

## ⚙️ Cara Kerja

1. Sistem menyala.
2. Target awal adalah tombol 1.
3. Pengguna hanya bisa:
   - Mengulang tombol yang sama
   - Menekan tombol berikutnya
4. Jika menekan tombol yang salah → buzzer peringatan.
5. Setelah tombol 10 selesai → kembali ke tombol 1.

---

## 📦 Use Case

Project ini cocok untuk:

- 📚 Media pembelajaran interaktif
- 🧠 Sistem hafalan bertahap
- 🏫 Alat bantu guru di kelas
- 🎓 Sistem latihan soal berbasis audio
- 🕌 Media edukasi berbasis suara
- 🎮 Game edukatif berbasis urutan

---

## 🚀 Pengembangan Lanjutan

Beberapa fitur yang dapat ditambahkan:

- Mode Quiz (jawaban benar/salah)
- Sistem skor otomatis
- Penyimpanan progres EEPROM
- LCD 16x2
- OLED display
- Versi non-blocking (tanpa delay)
- Integrasi RFID
- Mode admin reset

---

## 🛠 Instalasi

1. Install Arduino IDE
2. Install library:
   - DFRobotDFPlayerMini
3. Upload kode ke board
4. Siapkan MicroSD sesuai format
5. Sambungkan wiring sesuai tabel

---

## ⚠️ Catatan Penting

- Gunakan resistor 1K pada jalur RX DFPlayer untuk stabilitas.
- Pastikan file audio bernama dengan format 4 digit.
- Gunakan speaker yang sesuai impedansi.

---

 ## 📧 **Contacs us :** 
* [Frendi RoboTech](https://www.instagram.com/frendi.co/)
* [Whatsapp : +6287888227410](https://wa.me/+6287888227410)
* [Email    : frendirobotech@gmail.com](https://mail.google.com/mail/u/0/?view=cm&tf=1&fs=1&to=frendirobotech@gmail.com) atau [Email    : frendix45@gmail.com](https://mail.google.com/mail/u/0/?view=cm&tf=1&fs=1&to=frendix45@gmail.com)

---

## 👨‍💻 Author
Dikembangkan oleh: **Imam Sa'id Nurfrendi**  
Komunitas: **Reog Robotic & Robotech Electronics**  
Lisensi: **Open Source (MIT)**
