#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

// --- KONFIGURASI PIN ---
#define PIN_RX_DFP 6    // Ke TX DFPlayer
#define PIN_TX_DFP 7    // Ke RX DFPlayer
#define PIN_BUSY   10   // Ke Pin BUSY DFPlayer
#define PIN_BUZZER 11   // Ke kaki positif Buzzer

// Penamaan Tombol
const int T_1  = 2;
const int T_2  = 3;
const int T_3  = 4;
const int T_4  = 5;
const int T_5  = A5;
const int T_6  = A4;
const int T_7  = A3;
const int T_8  = A2;
const int T_9  = A1;
const int T_10 = A0;

const int daftarTombol[] = {T_1, T_2, T_3, T_4, T_5, T_6, T_7, T_8, T_9, T_10};

SoftwareSerial mySoftwareSerial(PIN_RX_DFP, PIN_TX_DFP);
DFRobotDFPlayerMini myDFPlayer;

// Variabel Kontrol
bool statusPutarSebelumnya = false;
int nomorLaguAktif = 0;
int targetTombolBerikutnya = 0; // Mulai dari tombol 0

void setup() {
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);

  pinMode(PIN_BUSY, INPUT);
  pinMode(PIN_BUZZER, OUTPUT);

  for (int i = 0; i < 10; i++) {
    pinMode(daftarTombol[i], INPUT_PULLUP);
  }

  Serial.println(F("Inisialisasi DFPlayer..."));
  if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println(F("Gagal terhubung! Periksa SD Card."));
    while (true);
  }

  myDFPlayer.volume(25);
  Serial.println(F("Sistem Urutan Ketat Siap."));
  Serial.println(F("Silahkan tekan Tombol 1."));
}

void loop() {
  bool sedangPutarLagu = (digitalRead(PIN_BUSY) == LOW);

  // --- DETEKSI LAGU SELESAI ---
  if (statusPutarSebelumnya == true && sedangPutarLagu == false) {
    Serial.print(F(">> Playlist Ke-"));
    Serial.print(nomorLaguAktif);
    Serial.println(F(" Selesai."));

    // JIKA BARU SAJA SELESAI TOMBOL 10, RESET KE 1
    if (nomorLaguAktif == 10) {
      targetTombolBerikutnya = 1;
      Serial.println(F(">> SIKLUS SELESAI. Kembali ke Tombol 1."));
    } else {
      // Tombol yang boleh ditekan adalah tombol yang sama atau tombol berikutnya
      // (Berdasarkan permintaan: "bisa diulang, tapi tidak bisa melompat")
      Serial.print(F(">> Berikutnya: Tombol "));
      Serial.print(targetTombolBerikutnya);
      Serial.print(F(" atau "));
      Serial.println(targetTombolBerikutnya + 1);
    }

    // Beep 2x
    digitalWrite(PIN_BUZZER, HIGH); delay(50); digitalWrite(PIN_BUZZER, LOW);
    delay(50);
    digitalWrite(PIN_BUZZER, HIGH); delay(50); digitalWrite(PIN_BUZZER, LOW);

    nomorLaguAktif = 0;
  }

  statusPutarSebelumnya = sedangPutarLagu;

  // --- CEK INPUT TOMBOL ---
  if (!sedangPutarLagu) {
    for (int i = 0; i < 10; i++) {
      if (digitalRead(daftarTombol[i]) == LOW) {
        int tombolDitekan = i + 1;

        // LOGIKA: Boleh ditekan jika itu tombol yang sama (ulang)
        // ATAU tombol tepat setelahnya (berurutan)
        if (tombolDitekan == targetTombolBerikutnya || tombolDitekan == (targetTombolBerikutnya + 1)) {

          // Jika pengguna menekan tombol "baru" (bukan mengulang)
          if (tombolDitekan == targetTombolBerikutnya + 1) {
            targetTombolBerikutnya = tombolDitekan;
          }

          nomorLaguAktif = tombolDitekan;

          digitalWrite(PIN_BUZZER, HIGH);
          delay(150);
          digitalWrite(PIN_BUZZER, LOW);

          Serial.print(F("Tombol "));
          Serial.print(nomorLaguAktif);
          Serial.print(F(" ditekan memutar playlist ke "));
          Serial.println(nomorLaguAktif);

          myDFPlayer.play(nomorLaguAktif);
          delay(1000);
        }
        else {
          // Jika menekan tombol yang salah (melompat atau mundur)
          Serial.print(F("SALAH URUTAN! Tekan Tombol "));
          Serial.print(targetTombolBerikutnya);
          if (targetTombolBerikutnya < 10) {
            Serial.print(F(" atau "));
            Serial.print(targetTombolBerikutnya + 1);
          }
          Serial.println();

          // Buzzer peringatan (suara lebih panjang)
          digitalWrite(PIN_BUZZER, HIGH); delay(500); digitalWrite(PIN_BUZZER, LOW);
        }
        break;
      }
    }
  }
}
