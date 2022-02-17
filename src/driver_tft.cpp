#include "driver_tft.h"

TFT_eSPI tft = TFT_eSPI();

int i;

void tft_init()
{
    tft.begin();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE);
    tft.setCursor(0, 0);
}

void tft_show()
{
    tft.drawString("Count: ", 25, 5);
    tft.drawNumber(i++, 100, 5);
    delay(200);
    tft.fillRoundRect(100, 5, 50, 15, 0, TFT_BLACK);
}
