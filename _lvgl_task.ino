void task_init ()
{
  lv_task_create(controlTask, 1000, LV_TASK_PRIO_MID, NULL);
  lv_task_create(mqttTask, 20 , LV_TASK_PRIO_MID, NULL);
  lv_task_create(readSensorTask, 1000, LV_TASK_PRIO_MID, NULL);
  lv_task_create(timesetTask, 1000 * 60 , LV_TASK_PRIO_LOWEST, NULL);
  lv_task_create(filecheckTask, 1000 * 3 , LV_TASK_PRIO_MID, NULL);
  lv_task_create(pubDataTask, 1000 , LV_TASK_PRIO_MID, NULL);
  lv_task_create(saveDataTask, 1000 * 15 * 60, LV_TASK_PRIO_MID, NULL);
  lv_task_create(updateTask, 1000 * 3 * 60, LV_TASK_PRIO_MID, NULL);
  lv_task_create(pingTestTask, 1000 * 30, LV_TASK_PRIO_LOW, NULL);
  lv_task_create(reconnectWifiTask, 1000 * 1, LV_TASK_PRIO_LOW, NULL);
  lv_task_create(updateRs485Value, 1000, LV_TASK_PRIO_LOW, NULL);
  lv_task_create(relaynametask, 1000, LV_TASK_PRIO_LOW, NULL);
  lv_task_create(updateTime, 1000, LV_TASK_PRIO_LOW, NULL);
  lv_task_create(updateWiFiStatus, 1000, LV_TASK_PRIO_LOW, NULL);

}

void pubDataTask (lv_task_t *task)
{
  if (client.connected())
  {
    client.publish(outTopic.c_str(), creatDataPayload(PostPH, PostPHTEMP, PostEC, PostECTEMP, PostBOARDTEMP, PostBOARDHUM, PostWaterFlow, PostWaterTotal , SCL_TANK , BCL_TANK , false).c_str());
  }

  if (client.connected() && data_save)
  {
    client.publish(outTopic.c_str(), creatDataPayload(PostPH, PostPHTEMP, PostEC, PostECTEMP, PostBOARDTEMP, PostBOARDHUM, PostWaterFlow, PostWaterTotal , SCL_TANK , BCL_TANK , true).c_str());
    data_save = false;
  }
}

void reconnectWifiTask (lv_task_t *task)
{
  if (!(WiFi.status() == WL_CONNECTED))
  {

    if (recon_wifi_conut > 10) {
      Serial.println("Trying to Reconnect");
      WiFi.begin(ssid , pass);
      recon_wifi_conut = 0;
    }

    recon_wifi_conut += 1;
  }

}

void pingTestTask (lv_task_t *task)
{
  if ((WiFi.status() == WL_CONNECTED))
  {
    bool success = Ping.ping("www.google.com", 3);
    if (!success) {
      Serial.println("Ping failed");
      WiFi.disconnect();
      pingTest = false;
    } else {
      pingTest = true;
      Serial.println("Ping succesful.");
    }
  } else {
    pingTest = false;

  }


}

void saveDataTask (lv_task_t *task)
{
  if (!data_save)
  {
    data_save = true;
  }
}

void controlTask (lv_task_t *task)
{
  reConect();
  restart_daily();
  readApi();
  relayControl ();

}

void updateTask (lv_task_t *task)
{
  updateVersion();
}

void mqttTask (lv_task_t *task)
{
  if (client.connected())
  {
    client.loop();
  }
  else
  {
    mqtt_init();
  }
}

void timesetTask (lv_task_t *task)
{
  timeSet ();
}

void readSensorTask (lv_task_t *task)
{
  readSensor ();
}

void filecheckTask (lv_task_t *task)
{
  if (SPIFFS.begin())
  {
    Serial.println("");
    Serial.print("DEVICE-ID->");
    Serial.println(device_id);
    Serial.print("STUCOUNT->");
    Serial.println(stuCount);
    Serial.print("PINCOUNT->");
    Serial.println(pinCheckCount);
    Serial.print("INPUTCOUNT->");
    Serial.println(inputCheckCount);
    Serial.print("USED : ");
    float usedBytes = SPIFFS.usedBytes() / 1000;
    Serial.print(usedBytes);
    Serial.println(" kb");
    float totalBytes = SPIFFS.totalBytes() / 1000;
    Serial.print("TOTAL SPACE : ");
    Serial.print(totalBytes);
    Serial.println(" kb");
    float freeBytes = (SPIFFS.totalBytes() - SPIFFS.usedBytes()) / 1000;
    Serial.print("FREE SPACE : ");
    Serial.print(freeBytes);
    Serial.println(" kb");

    for (int i = 0 ; i < 4 ; i++)
    {
      Serial.print("PIN " + String(i) + " NAME :");
      Serial.println(pinName[i]);
    }

  }
}
