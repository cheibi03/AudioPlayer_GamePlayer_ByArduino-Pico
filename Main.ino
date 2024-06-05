#include <Adafruit_GFX.h> 
#include <Adafruit_ST7735.h>
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

//SPI0をコンストラクタに指定する
Adafruit_ST7735 tft = Adafruit_ST7735(&SPI, TFT_CS, TFT_DC, TFT_RST);

int SelectTab = 0;

int OpenWindow = 0;

String Starttab[3] = {"AudioPlay" , "GamePlay" , " moleskin-Com"};

void setup(void) 
{
  SPI.setTX(TFT_MOSI);                        //H/W SPI 設定
  SPI.setSCK(TFT_SCLK);

  tft.initR(INITR_BLACKTAB);                //Init ST7735S初期化
  
  tft.fillScreen(ST77XX_BLACK);               //背景の塗りつぶし

  //ボタンの設定
  PinMode(RIGH1_BUT,INPUT);
  PinMode(RIGH2_BUT,INPUT);
  PinMode(LEFT1_BUT,INPUT);
  PinMode(LEFT2_BUT,INPUT);
}

void loop()
{
}

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
}
