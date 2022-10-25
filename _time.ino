void timeSet ()
{
  if ((WiFi.status() == WL_CONNECTED) && pingTest)
  {
    if (RTC.begin())
    {
      configTime(timezone, dst, "pool.ntp.org", "time.nist.gov");
      time_t now = time(nullptr);
      struct tm* timeinfo = localtime(&now);
      time_count += 1;
      Serial.println(timeinfo->tm_year + 1900);
      if ((timeinfo->tm_year + 1900) >= 2022)
      {
        RTC.adjust(DateTime(timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec));
        time_count = 0;
      }
    }
  }

}

void restart_daily ()
{
  String DayOfWeek = "";
  String Day = "";
  String Month = "";
  String Year = "";
  String Hours = "";
  String Min = "";
  String Sec = "";
  if (RTC.begin())
  {
    DateTime now = RTC.now();
    Day = String(now.day());
    Month = String(now.month());
    Year = String(now.year());
    Hours = String(now.hour());
    Min = String(now.minute());
    Sec = String(now.second());
    DayOfWeek = String(daysOfTheWeek[now.dayOfTheWeek()]);
  }
  else if (WiFi.status() == WL_CONNECTED && !RTC.begin())
  {
    configTime(timezone, dst, "pool.ntp.org", "time.nist.gov");
    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now);
    Day = String(timeinfo -> tm_mday);
    Month = String( timeinfo->tm_mon + 1 );
    Year = String(timeinfo->tm_year + 1900);
    Hours = String(timeinfo->tm_hour);
    Min = String(timeinfo->tm_min);
    Sec = String(timeinfo->tm_sec);
    char tmp_timeofweek[10];
    strftime(tmp_timeofweek, 10, "%A", timeinfo);
    DayOfWeek = String(tmp_timeofweek);
  }

  Day = DateTimeNewFormat(Day);
  Month = DateTimeNewFormat(Month);
  Hours = DateTimeNewFormat(Hours);
  Min = DateTimeNewFormat(Min);

  if ((Hours == "14") || (Hours == "08" || Hours == "8") || (Hours == "02" || Hours == "2") || (Hours == "05" || Hours == "5") || (Hours == "11") || (Hours == "20") || (Hours == "23") || (Hours == "17"))
  {
    restart = true;
  }

  if ((Hours == "12" || (Hours == "00" || Hours == "0") || Hours == "21" || (Hours == "09" || Hours == "9") || (Hours == "03" || Hours == "3") || Hours == "15" || Hours == "18" || (Hours == "06" || Hours == "6")) && restart)
  {
    if ((WiFi.status() == WL_CONNECTED) && client.connected())
    {
      client.publish(outTopic.c_str(), creatDataPayload(PostPH, PostPHTEMP, PostEC, PostECTEMP, PostBOARDTEMP, PostBOARDHUM, PostWaterFlow, PostWaterTotal , SCL_TANK , BCL_TANK , true).c_str());
    }
    delay(1000);
    ESP.restart();
  }

}

String DateTimeNewFormat(String txt)
{
  if (txt.length() == 1)
  {
    return txt = "0" + txt;
  } else {
    return txt;
  }
}
