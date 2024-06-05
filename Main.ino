#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <DFPlayerMini_Fast.h>
#include <SPI.h>

//ピン番号設定
#define TFT_DC      28  // DC
#define TFT_CS      17  // CS
#define TFT_SCLK    18  // Clock
#define TFT_MOSI    19  // MOSI
#define TFT_RST     22  // Reset 

//ボタンのピン設定
#define RIGH1_BUT
#define RIGH2_BUT
#define LEFT1_BUT
#define LEFT2_BUT

//DFPlayerのピン設定
#define DFPLAYER_RX_PIN 0
#define DFPLAYER_TX_PIN 1

//SPI0をコンストラクタに指定する
Adafruit_ST7735 tft = Adafruit_ST7735(&SPI, TFT_CS, TFT_DC, TFT_RST);

//DFPlayerを定義
DFPlayerMini_Fast myDFPlayer;

int SelectTab = 0;
int OpenWindow = 0;
String Starttab[3] = {"AudioPlay" , "GamePlay" , " moleskin-Com"};

//実行関数
void startView()
{
  //音楽　ゲーム　モールス通信
  if(digitalRead(LEFT1_BUT) == HIGH)
  {
    if(SelectTab <= 0){
      SelectTab = 3;
    }else{
      SelectTab++;
    }
  }
  
  if(digitalRead(LEFT2_BUT) == HIGH)
  {
    if(SelectTab >= 3){
      SelectTab = 0;
    }else{
      SelectTab--;
    }
  }

  if(digitalRead(RIGH1_BUT) == HIGH)
  {
    OpenWindow = SelectTab + 1;
  }
}

//ポインターを定義
typedef void (*FunctionPointer)();

//関数を格納


void setup(void) 
{
  Serial.begin(9600);
  
  SPI.setTX(TFT_MOSI);                        //H/W SPI 設定
  SPI.setSCK(TFT_SCLK);

  tft.initR(INITR_BLACKTAB);                //Init ST7735S初期化
  
  tft.fillScreen(ST77XX_BLACK);               //背景の塗りつぶし

  
  Serial1.begin(9600, SERIAL_8N1, DFPLAYER_RX_PIN, DFPLAYER_TX_PIN);

  // DFPlayer Miniを初期化
  if (!myDFPlayer.begin(Serial1)) {
    Serial.println("DFPlayer Mini initialization failed!");
    while (true);
  }

  Serial.println("DFPlayer Mini initialized.");
  
  // ボリューム設定（0-30の範囲）
  myDFPlayer.volume(20);

  //ボタンの設定
  PinMode(RIGH1_BUT,INPUT);
  PinMode(RIGH2_BUT,INPUT);
  PinMode(LEFT1_BUT,INPUT);
  PinMode(LEFT2_BUT,INPUT);
}

void loop()
{
    myDFPlayer.play(1); // 1番目の曲を再生
}
