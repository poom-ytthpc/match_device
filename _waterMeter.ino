void waterMeter (void)
{

  /////////////////////////////////////////////////////// WATER METER ///////////////////////////////////////////////////////////////////////////////

  lmeter_wt = lv_linemeter_create(tab1, NULL);
  lv_linemeter_set_range(lmeter_wt, 0, 100);                   /*Set the range*/
  //  lv_linemeter_set_value(lmeter_wt, PostWaterFlow);                       /*Set the current value*/
  lv_linemeter_set_value(lmeter_wt, SCL_TANK);
  lv_linemeter_set_scale(lmeter_wt, 260, 14);                  /*Set the angle and number of lines*/
  lv_obj_set_size(lmeter_wt, 100, 100);
  lv_obj_align(lmeter_wt, lmeter_ec, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

  label_wt = lv_label_create(tab1, NULL);
  lv_obj_set_style_local_text_font(label_wt, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, &lv_font_rsu_24);
  //  lv_label_set_text(label_wt, "WF");
  lv_label_set_text(label_wt, "SCL");

  lv_obj_align(label_wt, lmeter_wt, LV_ALIGN_CENTER, 0, 0);

  label_wt_value = lv_label_create(tab1, NULL);
  lv_obj_set_style_local_text_font(label_wt_value, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, &lv_font_rsu_24);
  char TMP_WATER_FLOW[10];
  Serial.print("POST WATER FLOW IN DISPLAYS : ");
  Serial.println(PostWaterFlow);
  //  dtostrf( PostWaterFlow, 2, 1, TMP_WATER_FLOW);
  dtostrf(SCL_TANK, 2, 1, TMP_WATER_FLOW);
  lv_label_set_text(label_wt_value, TMP_WATER_FLOW);
  lv_obj_align(label_wt_value, label_wt, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
  ///////////////////////////////////////////////////////////////////////////////////////////////////////

  lmeter_wt_total = lv_linemeter_create(tab1, NULL);
  lv_linemeter_set_range(lmeter_wt_total, 0, 100);                   /*Set the range*/
  //  lv_linemeter_set_value(lmeter_wt_total, PostWaterTotal);                       /*Set the current value*/
  lv_linemeter_set_value(lmeter_wt_total, BCL_TANK);                       /*Set the current value*/
  lv_linemeter_set_scale(lmeter_wt_total, 260, 14);                  /*Set the angle and number of lines*/
  lv_obj_set_size(lmeter_wt_total, 100, 100);
  lv_obj_align(lmeter_wt_total, lmeter_wt, LV_ALIGN_OUT_BOTTOM_RIGHT, 5, 5);

  label_wt_total = lv_label_create(tab1, NULL);
  lv_obj_set_style_local_text_font(label_wt_total, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, &lv_font_rsu_24);
  //  lv_label_set_text(label_wt_total, "WT");
  lv_label_set_text(label_wt_total, "BCL");

  lv_obj_align(label_wt_total, lmeter_wt_total, LV_ALIGN_CENTER, 0, 0);

  label_wt_total_value = lv_label_create(tab1, NULL);
  lv_obj_set_style_local_text_font(label_wt_total_value, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, &lv_font_rsu_24);
  char TMP_WATER_TOTAL[10];
  Serial.print("POST WATER TOTAL IN DISPLAYS : ");
  Serial.println(PostWaterFlow);
  //  dtostrf( PostWaterTotal, 2, 0, TMP_WATER_TOTAL);
  dtostrf(BCL_TANK, 2, 0, TMP_WATER_TOTAL);
  lv_label_set_text(label_wt_total_value, TMP_WATER_TOTAL);
  lv_obj_align(label_wt_total_value, label_wt_total, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
