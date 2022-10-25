#define LVGL_TICK_PERIOD  1
#ifdef BOARD_HAS_PSRAM
#define HOR_RES_MAX       LV_HOR_RES_MAX * 240
#else
#define HOR_RES_MAX       LV_HOR_RES_MAX * 10
#endif
#define BUFFER_MAX        HOR_RES_MAX * (LV_COLOR_SIZE / 8)
#define LANDSCAPE         1
#define VERTICAL          2
#define ORIENTATION       LANDSCAPE

static lv_disp_buf_t disp_buf;
//static lv_color_t * buf[BUFFER_MAX];
static lv_color_t * buf = (lv_color_t *)malloc(BUFFER_MAX);
/* Interrupt driven periodic handler */
static void lv_tick_handler(void)
{
  lv_tick_inc(LVGL_TICK_PERIOD);
}

#if USE_RTOS_VGL_TASK
void vLvglTask(void* pvParameters) {
  while (true) {
    lv_task_handler(); /* let the GUI do its work */
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}
#endif

void _lv_init() {
#ifdef BOARD_HAS_PSRAM
  Serial.println("PSRAM Supported");
  static lv_color_t * buf = (lv_color_t *)heap_caps_malloc(BUFFER_MAX, MALLOC_CAP_SPIRAM);
#else
  Serial.println("PSRAM Not supported");
  static lv_color_t * buf = (lv_color_t *)malloc(BUFFER_MAX);
  //  static lv_color_t * buf[BUFFER_MAX];
#endif
  Serial.println("+++++++++++++++++++++++++++++++++++++");
  lv_init();
  /* TFT init */
  tft.begin();
  /* Landscape orientation */
  tft.setRotation(ORIENTATION);
  // tft.setTouch(calData);
  touch_calibrate();
  /*Initialize the display*/
  lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * 5);
  lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
#ifdef ILI9488_DRIVER
#if ORIENTATION == LANDSCAPE
  disp_drv.hor_res = 480;
  disp_drv.ver_res = 320;
#else
  disp_drv.hor_res = 320;
  disp_drv.ver_res = 480;
#endif
#endif

#ifdef ILI9341_DRIVER
#if ORIENTATION == LANDSCAPE
  disp_drv.hor_res = 320;
  disp_drv.ver_res = 240;
#else
  disp_drv.hor_res = 240;
  disp_drv.ver_res = 320;
#endif
#endif
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.buffer = &disp_buf;
  lv_disp_drv_register(&disp_drv);
  // Initialize the touch pad
  lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_input_read;
  lv_indev_drv_register(&indev_drv);
  /*Initialize the graphics object*/
  create_object();
  /*Initialize the graphics library's tick*/
  tick.attach_ms(LVGL_TICK_PERIOD, lv_tick_handler);
#if USE_RTOS_VGL_TASK
  // tskNO_AFFINITY
  xTaskCreatePinnedToCore(vLvglTask, "vLvglTask", 1024 * 5, NULL, tskIDLE_PRIORITY, NULL, 0);
#endif


}
