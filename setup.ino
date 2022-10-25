void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 23, 22); //RX-23 TX-22 Serial2
  Serial2.setTimeout(300);
  //  while (!Serial2) {
  //    Serial.println("loop Serial");
  //  }
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);
  Wire.setPins(SDA_PIN, SCL_PIN);
  RTC.begin();
  RTC.disable32K();
  DateTime now = RTC.now();
  mcp.begin_I2C();
  mcp.pinMode(p0, OUTPUT);
  mcp.pinMode(p1, OUTPUT);
  mcp.pinMode(p2, OUTPUT);
  mcp.pinMode(p3, OUTPUT);
  mcp.pinMode(p8, OUTPUT);
  //  mcp.pinMode(p9, OUTPUT);
  //  mcp.pinMode(p10, OUTPUT);
  //  mcp.pinMode(p11, OUTPUT);
  //  mcp.pinMode(p12, OUTPUT);
  //  mcp.pinMode(p13, OUTPUT);
  //  mcp.pinMode(p14, OUTPUT);
  //  mcp.pinMode(p15, OUTPUT);

  mcp.digitalWrite(p0, LOW);
  mcp.digitalWrite(p1, LOW);
  mcp.digitalWrite(p2, LOW);
  mcp.digitalWrite(p3, LOW);
  mcp.digitalWrite(p8, LOW);
  //  mcp.digitalWrite(p9, LOW);
  //  mcp.digitalWrite(p10, LOW);
  //  mcp.digitalWrite(p11, LOW);
  //  mcp.digitalWrite(p12, LOW);
  //  mcp.digitalWrite(p13, LOW);
  //  mcp.digitalWrite(p14, LOW);
  //  mcp.digitalWrite(p15, LOW);

  client.setServer(MQTT_BROKER, 1883);
  client.setCallback(callback);
  client.setBufferSize(2048);
  client.setKeepAlive(10);

  tft_startup();

  setupSpiffs();

  wifi_init();

  WiFi.mode(WIFI_AP_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
  }

  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);

  shouldReadGpioApi = true;
  shouldReadGpioDataApi = true;
  shouldReadDeviceApi = true;
  shouldReadGpioTimerApi = true;
  shouldReadSensorStateApi = true;
  shouldReadFanApi = true;

  startUp = true;

  _lv_init();

  WiFi.begin(ssid , pass);



}
