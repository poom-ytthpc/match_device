void mqtt_init()
{
    mqtt_connect();
}

void mqtt_connect()
{

  if ((WiFi.status() == WL_CONNECTED) && (pingTest || startUp))
  {
    if (!client.connected() && device_id != "" && mqtt_con >= 5)
    {
      Serial.print("DEVICE-ID->");
      Serial.println(device_id);
      Serial.print("TRY TO CONNECT... ");
      Serial.println(MQTT_BROKER);
      setTopic ();

      String payload = "{\"device_id\": \"" + String(device_id) + "\"}";
      if (client.connect(device_id, MQTT_BROKER_USER , MQTT_BROKER_PASS, willTopic.c_str(), 0, false, payload.c_str()))
      {
        Serial.println("CLIENT CONNECT");
        messageBoxStartUp ();
        checkIn ();
        subScript();
        stuCount += 1;
        messageBoxCloseUp();
        startUp = false;
      }
      mqtt_con = 0;
    }

    mqtt_con += 1;
  }
  else
  {
    if (stuCount >= 1 && !(WiFi.status() == WL_CONNECTED))
    {
      onlineCheck();
      pinCheckCount = 0;
      inputCheckCount = 0;
    }
  }
}

void setTopic ()
{
  gpioInTopic = "device/" + String(device_id) + "/receive" + "/gpio";
  gpioDataInTopic = "device/" + String(device_id) + "/receive" + "/gpio" + "/data";
  deviceInTopic = "device/" + String(device_id) + "/receive" + "/device";
  gpioTimerInTopic = "device/" + String(device_id) + "/receive" + "/gpio" + "/timer";
  deviceSensorInTopic = "device/" + String(device_id) + "/receive" + "/device" + "/sensor";
  fanInTopic = "device/" + String(device_id) + "/receive/fan";

  checkinTopic = "device/" + String(device_id) + "/checkin";
  gpioOutCheckinTopic = "device/" + String(device_id) + "/checkin" + "/gpio";
  sensorOutCheckinTopic = "device/" + String(device_id) + "/checkin" + "/sensor";

  outTopic = "device/" + String(device_id) + "/notify";
  gpioOutTopic = "device/" + String(device_id) + "/notify" + "/gpio";
  autoOutTopic = "device/" + String(device_id) + "/notify" + "/device";
  sensorOutTopic = "device/" + String(device_id) + "/notify" + "/sensor";
  sensorStatusOutTopic = "device/" + String(device_id) + "/notify" + "/sensor" + "/status";
  fanOutTopic = "device/" + String(device_id) + "/notify" + "/fan";

  willTopic = "device/" + String(device_id) + "/will";
}

String gpioJsonCreate(String index , String title)
{
  String text;
  text += "{";
  text += "\"device_id\":\"" + String(device_id) + "\"" + ",";
  text += "\"index\":" + index + ",";
  text += "\"title\":\"" + title + "\"";
  text += "}";
  return text;
}

String sensorJsonCreate(String index , String title)
{
  String text;
  text += "{";
  text += "\"device_id\":\"" + String(device_id) + "\"" + ",";
  text += "\"index\":" + index + ",";
  text += "\"name\":\"" + title + "\"";
  text += "}";
  return text;
}


void onlineCheck()
{
  state_check_online = true;
  input_check_online = true;
  auto_check_online = true;
}

void subScript()
{
  client.subscribe(gpioInTopic.c_str());
  client.subscribe(gpioDataInTopic.c_str());
  client.subscribe(deviceInTopic.c_str());
  client.subscribe(gpioTimerInTopic.c_str());
  client.subscribe(deviceSensorInTopic.c_str());
  client.subscribe(fanInTopic.c_str());
}

void checkIn ()
{
  String payload = "{\"device_id\": \"" + String(device_id) + "\"}";
  client.publish(checkinTopic.c_str(), payload.c_str());
  client.publish(gpioOutCheckinTopic.c_str(), gpioJsonCreate("0", "R1").c_str());
  client.publish(gpioOutCheckinTopic.c_str(), gpioJsonCreate("1", "R2").c_str());
  client.publish(gpioOutCheckinTopic.c_str(), gpioJsonCreate("2", "R3").c_str());
  client.publish(gpioOutCheckinTopic.c_str(), gpioJsonCreate("3", "ALERT").c_str());
  client.publish(sensorOutCheckinTopic.c_str(), sensorJsonCreate("1", "PH SENSOR").c_str());
  client.publish(sensorOutCheckinTopic.c_str(), sensorJsonCreate("2", "EC SENSOR").c_str());
  client.publish(sensorOutCheckinTopic.c_str(), sensorJsonCreate("3", "WATER SENSOR").c_str());
  client.publish(sensorOutCheckinTopic.c_str(), sensorJsonCreate("5", "XY-MD02 SENSOR").c_str());
  client.publish(sensorOutCheckinTopic.c_str(), sensorJsonCreate("6", "ULTRASONIC SENSOR").c_str());
}
