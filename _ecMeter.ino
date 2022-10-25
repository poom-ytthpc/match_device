void ecMeter()
{
  /////////////////////////////////////////////////////// EC METER ///////////////////////////////////////////////////////////////////////////////
  lmeter_ec = lv_linemeter_create(tab1, NULL);
  lv_linemeter_set_range(lmeter_ec, 0, 10000);                   /*Set the range*/
  lv_linemeter_set_value(lmeter_ec, PostEC);                       /*Set the current value*/
  lv_linemeter_set_scale(lmeter_ec, 260, 14);                  /*Set the angle and number of lines*/
  lv_obj_set_size(lmeter_ec, 100, 100);
  lv_obj_align(lmeter_ec,lmeter_ph , LV_ALIGN_OUT_RIGHT_MID, 5, 0);

  label_ec = lv_label_create(tab1, NULL);
  lv_obj_set_style_local_text_font(label_ec, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, &lv_font_rsu_24);
  lv_label_set_text(label_ec, "EC");
  lv_obj_align(label_ec, lmeter_ec, LV_ALIGN_CENTER, 0, 0);

  label_ec_value = lv_label_create(tab1, NULL);
  lv_obj_set_style_local_text_font(label_ec_value, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, &lv_font_rsu_24);

  char TMP_EC[10];
  Serial.print("POST EC IN DISPLAYS : ");
  Serial.println(PostEC);
  dtostrf( PostEC, 2, 1, TMP_EC);
  lv_label_set_text(label_ec_value, TMP_EC);
  lv_obj_align(label_ec_value, label_ec, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  lmeter_ec_temp = lv_linemeter_create(tab1, NULL);
  lv_linemeter_set_range(lmeter_ec_temp, 0, 100);                   /*Set the range*/
  lv_linemeter_set_value(lmeter_ec_temp, PostECTEMP);                       /*Set the current value*/
  lv_linemeter_set_scale(lmeter_ec_temp, 260, 14);                  /*Set the angle and number of lines*/
  lv_obj_set_size(lmeter_ec_temp, 100, 100);
  lv_obj_align(lmeter_ec_temp, lmeter_ec, LV_ALIGN_OUT_BOTTOM_MID, 5, 5);

  label_ec_temp = lv_label_create(tab1, NULL);
  lv_obj_set_style_local_text_font(label_ec_temp, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, &lv_font_rsu_24);
  lv_label_set_text(label_ec_temp, "ET");
  lv_obj_align(label_ec_temp, lmeter_ec_temp, LV_ALIGN_CENTER, 0, 0);

  label_ec_temp_value = lv_label_create(tab1, NULL);
  lv_obj_set_style_local_text_font(label_ec_temp_value, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, &lv_font_rsu_24);
  char TMP_EC_TEMP[10];
  Serial.print("POST EC TEMP IN DISPLAYS : ");
  Serial.println(PostECTEMP);
  dtostrf(PostECTEMP , 2, 1, TMP_EC_TEMP);
  lv_label_set_text(label_ec_temp_value, TMP_EC_TEMP);
  lv_obj_align(label_ec_temp_value, label_ec_temp, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
