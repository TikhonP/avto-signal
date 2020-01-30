#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

#define SS_RX 3
#define SS_TX 2

SoftwareSerial playerSerial(SS_RX, SS_TX);  // RX, TX
DFRobotDFPlayerMini myDFPlayer;
int volume = 15;

void setup() {
        Serial.begin(9600); // Вывод
        Serial.println("Out 9600");

        playerSerial.begin(9600);
        Serial.println("playerSerial begin");

        delay(500);
        if (!myDFPlayer.begin(playerSerial)) { // запуск плеера//инициализац//более 2 секунд
                Serial.println(F("Ошибка подключения плеера:"));
                while(true);
        }
        Serial.println("Setting player");
        myDFPlayer.setTimeOut(500);
        myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
        myDFPlayer.volume(volume); //громкость (0~30).
        myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
        myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
        delay(200);
        Serial.println("Playing...");
        int track_count = myDFPlayer.readFileCountsInFolder(1);
        myDFPlayer.playFolder(1, random(track_count));
}

void loop() {
}
