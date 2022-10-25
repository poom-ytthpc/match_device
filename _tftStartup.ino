
void tft_startup()
{
  tft.init();

  //  //  ////////// SETUP SPIFFS ///////////////////

  ///////////////////////////////////////////
  // Set the rotation before we calibrate
  tft.setRotation(1); // 270
  // call screen calibration

  // clear screen
  tft.fillScreen(TFT_BLACK);
  tft.setTextDatum(MC_DATUM);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  tft.setTextFont(2);
  tft.setTextSize(2);
  tft.drawString("WELCOME", 160, 90, 2);// Print the string name of the font

  tft.drawString("MATCHCHEMICAL", 160, 140, 2);
  delay(1000);
}
