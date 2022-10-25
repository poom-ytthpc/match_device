/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p){
  uint16_t c;
  tft.startWrite(); /* Start new TFT transaction */
  tft.setAddrWindow(area->x1, area->y1, (area->x2 - area->x1 + 1), (area->y2 - area->y1 + 1)); /* set the working window */
  for (int y = area->y1; y <= area->y2; y++) {
    for (int x = area->x1; x <= area->x2; x++) {
      c = color_p->full;
      tft.writeColor(c, 1);
      color_p++;
    }
  }
  tft.endWrite(); /* terminate TFT transaction */
  lv_disp_flush_ready(disp); /* tell lvgl that flushing is done */
}

bool my_input_read(lv_indev_drv_t * indev, lv_indev_data_t *data) {
  static uint16_t prev_x, prev_y; 
  uint16_t X = 0, Y = 0;
  data->state = tft.getTouch(&X, &Y) ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL; 
  if(data->state == LV_INDEV_STATE_PR) {
    prev_x = X;
    prev_y = Y;
  }
  data->point.x = prev_x;
  data->point.y = prev_y; 
  /*No buffering so no more data read*/
  return false;        
}
