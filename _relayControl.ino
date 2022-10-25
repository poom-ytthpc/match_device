
void relayControl ()
{
  size_t n = sizeof(pin) / sizeof(pin[0]);
  for (int i = 0 ; i < n ; i++)
  {
    if (Auto)
    {
      if (sclState[i] && read_serial_count > 30)
      {
        if (SCL_TANK < 10)
        {
          updatePinState(pin[i], pinName[i], false);
        }
        else
        {
          ec_ph_state (i);
          timer_state(i);
        }
      }
      else if (bclState[i] && read_serial_count > 30)
      {
        if (BCL_TANK < 10)
        {
          updatePinState(pin[i], pinName[i], false);
        }
        else
        {
          ec_ph_state (i);
          timer_state(i);
        }
      }
      else
      {
        ec_ph_state (i);
        timer_state(i);
      }

      fan_state ();

    }/* END AUTO */

    mcp.digitalWrite(8, fan);
    mcp.digitalWrite(pin[i], state[i]); /* mcp state */

    updateRelayDisplay();

  }/* END FOR LOOP */
}

void fan_state ()
{
  if (PostBOARDTEMP >= 40)
  {
    if (fan != true)
    {
      updateFanState(true);
    }
  }
  if (PostBOARDTEMP <= 39)
  {
    if (fan != false)
    {
      updateFanState(false);
    }
  }
}

void timer_state (int i)
{
  if (timerState[i])
  {
    size_t m = sizeof(tStart[i]) / sizeof(tStart[i][0]);
    size_t n = sizeof(tStop[i]) / sizeof(tStop[i][0]);

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

    String newTime = Hours + ":" + Min;



    for (int j = 0 ; j < m ; j++)
    {
      size_t o = sizeof(tDays[i][j]) / sizeof(tDays[i][j][0]);

      if (String(tStart[i][j]) == String(newTime))
      {
        for (int k = 0 ; k < o ; k++)
        {
          if (String(tDays[i][j][k]) == String(DayOfWeek) || String(tDays[i][j][k]) == "Everyday")
          {
            if (state[i] != true)
            {
              updatePinState(pin[i], pinName[i], true);
            }
          }
        }
      }/* END TIMER START */
    }

    for (int j = 0 ; j < n ; j++)
    {
      size_t o = sizeof(tDays[i][j]) / sizeof(tDays[i][j][0]);

      if (String(tStop[i][j]) == String(newTime))
      {
        for (int k = 0 ; k < o ; k++)
        {
          if (String(tDays[i][j][k]) == String(DayOfWeek) || String(tDays[i][j][k]) == "Everyday")
          {
            if (state[i] != false)
            {
              updatePinState(pin[i], pinName[i], false);
            }
          }
        }
      }/* END TIMER STOP */
    }
  }/* END TIMER STATE */
}

void ec_ph_state (int i)
{
  if (ecState[i])
  {
    if (maxEc[i] > minEc[i])
    {
      if (PostEC >= maxEc[3])
      {
        if (ecSend && LINE_TOKEN != "") {
          LINE.notify("------- SATRT MESSAGE ---------");
          String bn = "";
          bn.concat(device_name);
          String m1 = "SEND FORM : " + bn ;
          LINE.notify(m1);
          LINE.notify("ค่า CONDUCTIVITY สูงเกินค่าที่กำหนด");
          String e = "";
          e.concat(PostEC);
          String m2 = "ค่า CONDUCTIVITY : " + e;
          LINE.notify(m2);
          LINE.notify("------- END MESSAGE ----------");
          ecSend = false;
        } else {
          if (millis() - time_updateecsend > INTERVAL_ECSEND) {
            ecSend = true;
            time_updateecsend = millis();
          }
        }
      }
      if (PostEC >= maxEc[i])
      {
        if (state[i] != true)
        {
          updatePinState(pin[i], pinName[i], true);
        }
      }
      else if (PostEC <= minEc[i])
      {
        if (state[i] != false)
        {
          updatePinState(pin[i], pinName[i], false);
        }
      }
    }/* EMD EC MAX > MIN */

    if (maxEc[i] < minEc[i])
    {
      if (PostEC <= minEc[3])
      {
        if (ecSend && LINE_TOKEN != "") {
          LINE.notify("------- SATRT MESSAGE ---------");
          String bn = "";
          bn.concat(device_name);
          String m1 = "SEND FORM : " + bn ;
          LINE.notify(m1);
          LINE.notify("ค่า CONDUCTIVITY ต่ำเกินกว่าค่าที่กำหนด");
          String e = "";
          e.concat(PostEC);
          String m2 = "ค่า CONDUCTIVITY : " + e;
          LINE.notify(m2);
          LINE.notify("------- END MESSAGE ----------");
          ecSend = false;
        } else {
          if (millis() - time_updateecsend > INTERVAL_ECSEND) {
            ecSend = true;
            time_updateecsend = millis();
          }
        }
      }

      if (PostEC <= minEc[i])
      {
        if (state[i] != true)
        {
          updatePinState(pin[i], pinName[i], true);
        }

      }
      else if (PostEC >= maxEc[i])
      {
        if (state[i] != false)
        {
          updatePinState(pin[i], pinName[i], false);
        }
      }
    }/* EMD EC MAX < MIN */
  }/* END EC STATE */

  if (phState[i])
  {
    if (maxPh[i] > minPh[i])
    {
      if (PostPH >= maxPh[3])
      {
        if (phSend && LINE_TOKEN != "") {
          LINE.notify("------- SATRT MESSAGE ---------");
          String bn = "";
          bn.concat(device_name);
          String m1 = "SEND FORM : " + bn ;
          LINE.notify(m1);
          LINE.notify("ALERT PH MORE THAN MAX");
          String p = "";
          p.concat(PostPH);
          String m2 = "PH : " + p;
          LINE.notify(m2);
          LINE.notify("------- END MESSAGE ----------");
          phSend = false;
        } else {
          if (millis() - time_updatephsend > INTERVAL_PHSEND) {
            phSend = true;
            time_updatephsend = millis();
          }

        }
      }

      if (PostPH >= maxPh[i])
      {
        if (state[i] != true)
        {
          updatePinState(pin[i], pinName[i], true);
        }
      }
      else if (PostPH <= minPh[i])
      {
        if (state[i] != false)
        {
          updatePinState(pin[i], pinName[i], false);
        }
      }
    }/* END PH MAX > MIN */

    if (maxPh[i] < minPh[i])
    {
      if (PostPH <= minPh[3])
      {
        if (phSend && LINE_TOKEN != "") {
          LINE.notify("------- SATRT MESSAGE ---------");
          String bn = "";
          bn.concat(device_name);
          String m1 = "SEND FORM : " + bn ;
          LINE.notify(m1);
          LINE.notify("ALERT PH MORE THAN MIN");
          String p = "";
          p.concat(PostPH);
          String m2 = "PH : " + p;
          LINE.notify(m2);
          LINE.notify("------- END MESSAGE ----------");
          phSend = false;
        } else {
          if (millis() - time_updatephsend > INTERVAL_PHSEND) {
            phSend = true;
            time_updatephsend = millis();
          }

        }
      }

      if (PostPH <= minPh[i])
      {
        if (state[i] != true)
        {
          updatePinState(pin[i], pinName[i], true);
        }
      }
      else if (PostPH >= maxPh[i])
      {
        if (state[i] != false)
        {
          updatePinState(pin[i], pinName[i], false);
        }
      }
    }/* END PH MAX < MIN */
  }/* END PH STATE */
}

void updatePinState (int p , String t , bool s)
{
  if (client.connected() && (WiFi.status() == WL_CONNECTED))
  {
    client.publish(gpioOutTopic.c_str(), createGpioPayload(p, t, s).c_str());
  }
  createGpioApi(createGpioPayload(p, t, s));
}

void updateAutoState (int s)
{
  if (client.connected() && (WiFi.status() == WL_CONNECTED))
  {
    client.publish(autoOutTopic.c_str() , createDevicePayload (String(device_name), s , fan).c_str());
  }
  createDeviceApi(createDevicePayload(String(device_name), s , fan));
}

void updateSensorState (int i , int s)
{
  if (client.connected() && (WiFi.status() == WL_CONNECTED))
  {
    client.publish(sensorOutTopic.c_str(), createSensorPayload(i, s).c_str());
  }
  createSensorStateApi(createSensorPayload(i, s));
}

void updateFanState (int f)
{
  if (client.connected() && (WiFi.status() == WL_CONNECTED))
  {
    client.publish(fanOutTopic.c_str(), createDevicePayload (String(device_name), Auto , f).c_str());
  }
  createFanApi(createDevicePayload(String(device_name), Auto , f));
}

String createSensorPayload (int i , int s)
{
  String txt;
  txt += "{";
  txt += "\"device_id\":\"";
  txt += String(device_id);
  txt += "\",";
  txt += "\"";
  txt += "index\":";
  txt += String(i);
  txt +=  ",";
  txt += "\"" ;
  txt += "state\":";
  txt +=  String(s);
  txt += "}";
  return txt;
}


String creatDataPayload (float ph , float phTemp , float ec , float ecTemp , float temp , float hum , float flow , float total , int st , int bt , bool sve)
{
  String txt;
  txt += "{";
  txt += "\"device_id\":\"";
  txt += String(device_id);
  txt += "\",";
  txt += "\"";
  txt += "ph\":";
  txt += String(ph);
  txt += ",";
  txt += "\"";
  txt += "phTemp\":";
  txt += String(phTemp);
  txt += ",";
  txt += "\"";
  txt += "ec\":";
  txt += String(ec);
  txt += ",";
  txt += "\"";
  txt += "ecTemp\":";
  txt += String(ecTemp);
  txt += ",";
  txt += "\"";
  txt += "temperature\":";
  txt += String(temp);
  txt += ",";
  txt += "\"";
  txt += "humidity\":";
  txt += String(hum);
  txt += ",";
  txt += "\"";
  txt += "waterFlow\":";
  txt += String(flow);
  txt += ",";
  txt += "\"";
  txt += "waterTotal\":";
  txt += String(total);
  txt += ",";
  txt += "\"scl_tank\":" + String(st) + ",";
  txt += "\"bcl_tank\":" + String(bt) + ",";
  txt += "\"";
  txt += "save\":";
  txt += String(sve);
  txt += "}";
  return txt;
}

String createGpioPayload (int p , String t , bool s)
{
  String txt;
  txt += "{";
  txt += "\"device_id\":\"";
  txt += String(device_id);
  txt += "\",";
  txt += "\"";
  txt += "index\":";
  txt += String(p);
  txt += ",";
  txt += "\"";
  txt += "title\":";
  txt += "\"";
  txt += t;
  txt += "\"";
  txt +=  ",";
  txt += "\"" ;
  txt += "state\":";
  txt +=  String(s);
  txt += "}";
  return txt;
}

String createDevicePayload (String n , bool s , bool f)
{
  String txt;
  txt += "{";
  txt += "\"device_id\":\"";
  txt += String(device_id);
  txt += "\",";
  txt += "\"";
  txt += "name\":";
  txt += "\"";
  txt += n;
  txt += "\"";
  txt +=  ",";
  txt += "\"" ;
  txt += "auto\":";
  txt +=  String(s);
  txt +=  ",";
  txt += "\"" ;
  txt += "fan\":";
  txt +=  String(f);
  txt += "}";
  return txt;
}
