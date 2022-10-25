void phMeter ()
{
  //////////////////////////////////////////////////////////////////////////////////////////////////////
  lmeter_ph = lv_linemeter_create(tab1, NULL);
  lv_linemeter_set_range(lmeter_ph, 1, 14);                   /*Set the range*/

  /*Set the current value*/
  lv_linemeter_set_scale(lmeter_ph, 260, 14);                  /*Set the angle and number of lines*/
  lv_obj_set_size(lmeter_ph, 100, 100);
  lv_obj_align(lmeter_ph, obj1, LV_ALIGN_OUT_BOTTOM_LEFT, 5, 10);

  label_ph = lv_label_create(tab1, NULL);
  lv_obj_set_style_local_text_font(label_ph, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, &lv_font_rsu_24);
  lv_label_set_text(label_ph, "PH");
  lv_obj_align(label_ph, lmeter_ph, LV_ALIGN_CENTER, 0, 0);

  label_ph_value = lv_label_create(tab1, NULL);
  lv_obj_set_style_local_text_font(label_ph_value, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, &lv_font_rsu_24);
  char TMP_PH[10];
  Serial.print("POST PH IN DISPLAYS : ");
  Serial.println(PostPH);
  dtostrf( PostPH, 2, 1, TMP_PH);
  lv_label_set_text(label_ph_value, TMP_PH);
  lv_obj_align(label_ph_value, label_ph, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);


  ///////////////////////////////////////////////////////////////////////////////////////////////////////

  lmeter_ph_temp = lv_linemeter_create(tab1, NULL);
  lv_linemeter_set_range(lmeter_ph_temp, 1, 100);                   /*Set the range*/
  lv_linemeter_set_scale(lmeter_ph_temp, 260, 14);                  /*Set the angle and number of lines*/
  lv_obj_set_size(lmeter_ph_temp, 100, 100);
  lv_obj_align(lmeter_ph_temp, lmeter_ph, LV_ALIGN_OUT_BOTTOM_LEFT, 5, 5);

  label_ph_temp = lv_label_create(tab1, NULL);
  lv_obj_set_style_local_text_font(label_ph_temp, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, &lv_font_rsu_24);
  lv_label_set_text(label_ph_temp, "PT");
  lv_obj_align(label_ph_temp, lmeter_ph_temp, LV_ALIGN_CENTER, 0, 0);

  label_ph_temp_value = lv_label_create(tab1, NULL);
  lv_obj_set_style_local_text_font(label_ph_temp_value, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, &lv_font_rsu_24);
  char TMP_PH_TEMP[10];
  Serial.print("POST PH TEMP IN DISPLAYS : ");
  Serial.println(PostPHTEMP);
  dtostrf(PostPHTEMP , 2, 1, TMP_PH_TEMP);
  lv_label_set_text(label_ph_temp_value, TMP_PH_TEMP);
  lv_obj_align(label_ph_temp_value, label_ph_temp, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
  lv_linemeter_set_value(lmeter_ph_temp, PostPHTEMP);

}
