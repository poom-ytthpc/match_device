void tankMeter(void)
{

  static lv_style_t style, style_indic;
  lv_style_init(&style);
  lv_style_init(&style_indic);

  lv_style_set_radius(&style, LV_STATE_DEFAULT, 5);
  lv_style_set_radius(&style_indic, LV_STATE_DEFAULT, 5);

  lv_style_set_bg_color(&style, LV_STATE_DEFAULT , lv_color_hex(0xADF5FF));
  lv_style_set_bg_grad_color(&style, LV_STATE_DEFAULT , lv_color_hex(0x05ace3));
  lv_style_set_text_color(&style, LV_STATE_DEFAULT , lv_color_hex(0x5c459b));

  tank1 = lv_bar_create(tab1, NULL);

  lv_obj_set_style_local_bg_color(tank1, LV_BAR_PART_INDIC, LV_STATE_DEFAULT, lv_color_hex(0x05ace3));

  lv_obj_add_style(tank1 , LV_OBJ_PART_MAIN , &style);
  lv_obj_add_style(tank1 , LV_BAR_PART_INDIC , &style_indic);

  lv_obj_set_size(tank1, 80, 100);
  lv_bar_set_range(tank1, 0, 100);
  lv_obj_align(tank1, lmeter_ec, LV_ALIGN_OUT_RIGHT_MID, 15, 0);
  lv_bar_set_anim_time(tank1, 2000);
  lv_bar_set_value(tank1, 100, LV_ANIM_ON);

  label_tank1 = lv_label_create(tab1, NULL);
  lv_obj_set_style_local_text_font(label_tank1, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, &lv_font_rsu_24);
  lv_label_set_text(label_tank1, "SCL");

  lv_obj_align(label_tank1, tank1, LV_ALIGN_CENTER, 0, 0);
  lv_obj_add_style(label_tank1 , LV_OBJ_PART_MAIN , &style);

  label_tank1_value = lv_label_create(tab1, NULL);
  lv_obj_add_style(label_tank1_value , LV_OBJ_PART_MAIN , &style);

  lv_obj_set_style_local_text_font(label_tank1_value, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, &lv_font_rsu_24);
  char TMP_TANK1[10];

  dtostrf(SCL_TANK, 2, 0, TMP_TANK1);
  lv_label_set_text(label_tank1_value, TMP_TANK1);
  lv_obj_align(label_tank1_value, label_tank1, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

  /*************************************************************************************************************/

  tank2 = lv_bar_create(tab1, NULL);

  lv_obj_set_style_local_bg_color(tank2, LV_BAR_PART_INDIC, LV_STATE_DEFAULT, lv_color_hex(0x05ace3));

  lv_obj_add_style(tank2 , LV_OBJ_PART_MAIN , &style);
  lv_obj_add_style(tank2 , LV_BAR_PART_INDIC , &style_indic);

  lv_obj_set_size(tank2, 80, 100);
  lv_bar_set_range(tank2, 0, 100);
  lv_obj_align(tank2, tank1, LV_ALIGN_OUT_BOTTOM_RIGHT, 0, 5);
  lv_bar_set_anim_time(tank2, 2000);
  lv_bar_set_value(tank2, 100, LV_ANIM_ON);

  label_tank2 = lv_label_create(tab1, NULL);
  lv_obj_set_style_local_text_font(label_tank2, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, &lv_font_rsu_24);
  lv_label_set_text(label_tank2, "BCL");

  lv_obj_align(label_tank2, tank2, LV_ALIGN_CENTER, 0, 0);
  lv_obj_add_style(label_tank2 , LV_OBJ_PART_MAIN , &style);

  label_tank2_value = lv_label_create(tab1, NULL);
  lv_obj_add_style(label_tank2_value , LV_OBJ_PART_MAIN , &style);

  lv_obj_set_style_local_text_font(label_tank2_value, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, &lv_font_rsu_24);
  char TMP_TANK2[10];

  dtostrf(SCL_TANK, 2, 0, TMP_TANK2);
  lv_label_set_text(label_tank1_value, TMP_TANK2);
  lv_obj_align(label_tank1_value, label_tank1, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
}
