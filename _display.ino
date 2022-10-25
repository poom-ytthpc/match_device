void create_object ()
{
  lv_main_tabview();
  task_init ();

}

static lv_obj_t *mbox;
static lv_obj_t *mbox1;
void messageBoxClose()
{
  lv_msgbox_start_auto_close(mbox, 700);
}

void messageBox ()
{
  mbox = lv_msgbox_create(lv_scr_act(), NULL);
  lv_msgbox_set_text(mbox, "          PLAESE WAIT!          ");
  lv_obj_set_width(mbox, 300);
  lv_obj_align(mbox, NULL, LV_ALIGN_CENTER, 0, 0);

}

void messageBoxCloseUp()
{
  lv_msgbox_start_auto_close(mbox1, 20 * 1000);
}

void messageBoxStartUp ()
{
  mbox1 = lv_msgbox_create(lv_scr_act(), NULL);
  lv_msgbox_set_text(mbox1, "          PLAESE WAIT!          ");
  lv_obj_set_width(mbox1, 300);

  lv_obj_align(mbox1, NULL, LV_ALIGN_CENTER, 0, 0);

}

/*-------- OBJECT ------------*/
lv_obj_t *tabview;

lv_obj_t *tab1;
lv_obj_t *tab2;
lv_obj_t *tab3;




lv_obj_t *label_tab3;
lv_obj_t * btn_resetWiFi;

/*-------------------------*/
static void event_handler(lv_obj_t * obj, lv_event_t e) {

  if (e == LV_EVENT_VALUE_CHANGED) {
    messageBox ();

    uint8_t data = *((uint8_t *)lv_obj_get_user_data(obj));
    printf("State: %s\nData: %d\n", lv_switch_get_state(obj) ? "ON" : "OFF", data);
    if (pinCheckCount == 0 || inputCheckCount == 0 || auto_check_online == true)
    {
      pinCheckCount = 5;
      inputCheckCount = 4;
      auto_check_online = false;
    }

    if (data == 0)
    {
      if (state[data])
      {
        updatePinState(pin[data], pinName[data], false);
        mcp.digitalWrite(pin[data], false);
        messageBoxClose();
      }
      else
      {
        updatePinState(pin[data], pinName[data], true);
        mcp.digitalWrite(pin[data], true);
        messageBoxClose();
      }
    }

    if (data == 1)
    {
      if (state[data])
      {
        updatePinState(pin[data], pinName[data], false);
        mcp.digitalWrite(pin[data], false);
        messageBoxClose();
      }
      else
      {
        updatePinState(pin[data], pinName[data], true);
        mcp.digitalWrite(pin[data], true);
        messageBoxClose();
      }
    }

    if (data == 2)
    {
      if (state[data])
      {
        updatePinState(pin[data], pinName[data], false);
        mcp.digitalWrite(pin[data], false);
        messageBoxClose();
      }
      else
      {
        updatePinState(pin[data], pinName[data], true);
        mcp.digitalWrite(pin[data], true);
        messageBoxClose();
      }
    }

    if (data == 3)
    {
      if (state[data])
      {
        updatePinState(pin[data], pinName[data], false);
        mcp.digitalWrite(pin[data], false);
        messageBoxClose();
      }
      else
      {
        updatePinState(pin[data], pinName[data], true);
        mcp.digitalWrite(pin[data], true);
        messageBoxClose();
      }
    }

    if (data == 4)
    {
      if (Auto)
      {
        Auto = false;
        updateAutoState(false);
        messageBoxClose();
      }
      else
      {
        Auto = true;
        if (PostBOARDTEMP >= 35)
        {
          if (fan != true)
          {
            updateFanState(true);
          }
        }
        if (PostBOARDTEMP <= 33)
        {
          if (fan != false)
          {
            updateFanState(false);
          }
        }
        updateAutoState(true);
        messageBoxClose();
      }
    }

    if (data == 5)
    {
      if (phInputState)
      {
        phInputState = false;
        updateSensorState(1, 0); /* index state */
        messageBoxClose();
      }
      else
      {
        phInputState = true;
        updateSensorState(1, 1); /* index state */
        messageBoxClose();
      }
    }

    if (data == 6)
    {
      if (ecInputState)
      {
        ecInputState = false;
        updateSensorState(2, 0); /* index state */
        messageBoxClose();
      }
      else
      {
        ecInputState = true;
        updateSensorState(2, 1); /* index state */
        messageBoxClose();
      }
    }

    if (data == 7)
    {
      if (tempHumInputState)
      {
        tempHumInputState = false;
        updateSensorState(5, 0); /* index state */
        messageBoxClose();
      }
      else
      {
        tempHumInputState = true;
        updateSensorState(5, 1); /* index state */
        messageBoxClose();
      }
    }

    if (data == 8)
    {
      if (fan)
      {
        updateFanState(false);
        mcp.digitalWrite(8, false);
        messageBoxClose();
      }
      else
      {
        updateFanState(true);
        mcp.digitalWrite(8, true);
        messageBoxClose();
      }
    }



    if (data == 9)
    {
      if (ultraSonicInputState)
      {
        ultraSonicInputState = false;
        updateSensorState(6, 0); /* index state */
        messageBoxClose();
      }
      else
      {
        ultraSonicInputState = true;
        updateSensorState(6, 1); /* index state */
        messageBoxClose();
      }
    }

    //    if (data == 9)
    //    {
    //      if (waterInputState)
    //      {
    //        waterInputState = false;
    //        updateSensorState(3, 0); /* index state */
    //        messageBoxClose();
    //      }
    //      else
    //      {
    //        waterInputState = true;
    //        updateSensorState(3, 1); /* index state */
    //        messageBoxClose();
    //      }
    //    }
  }
}


void lv_main_tabview()
{


  /*Create a Tab view object*/


  static lv_style_t style , style_t2;
  lv_style_init(&style);
  lv_style_init(&style_t2);


  lv_obj_clean(lv_scr_act());


  tabview = lv_tabview_create(lv_scr_act(), NULL);
  lv_style_set_bg_color(&style, LV_STATE_DEFAULT , lv_color_hex(0x5c459b));
  lv_style_set_text_color(&style, LV_STATE_DEFAULT , lv_color_hex(0x05ace3));

  lv_obj_add_style(tabview , LV_IMG_PART_MAIN , &style);
  messageBox ();
  /*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/
  tab1 = lv_tabview_add_tab(tabview, LV_SYMBOL_HOME);


  tab2 = lv_tabview_add_tab(tabview, LV_SYMBOL_SETTINGS);
  lv_style_set_text_color(&style_t2, LV_STATE_DEFAULT , LV_COLOR_WHITE);
  lv_obj_add_style(tab2 , LV_IMG_PART_MAIN , &style_t2);
  tab3 = lv_tabview_add_tab(tabview, LV_SYMBOL_WIFI);




  tab_1();
  tab_2();
  tab_3();
  messageBoxClose();






  /*Add content to the tabs*/
  //  lv_obj_t * label1 = lv_label_create(tab1, NULL);
  //  lv_label_set_text(label1, "This the first tab\n\n"
  //                    "If the content\n"
  //                    "of a tab\n"
  //                    "become too long\n"
  //                    "the it \n"
  //                    "automatically\n"
  //                    "become\n"
  //                    "scrollable.");




  //  labelt = lv_label_create(tab2, NULL);
  //  lv_label_set_text(labelt, "Second tab");







}

/* tab1 Object */

lv_obj_t * label_time;
lv_obj_t * label_wifi;
lv_obj_t * obj1;
/* ph */
lv_obj_t * lmeter_ph;
lv_obj_t * lmeter_ph_temp;
lv_obj_t *label_ph;
lv_obj_t *label_ph_value;
lv_obj_t *label_ph_temp;
lv_obj_t *label_ph_temp_value;
/*-------------------------*/

/* ec */
lv_obj_t * lmeter_ec;
lv_obj_t * lmeter_ec_temp;
lv_obj_t *label_ec;
lv_obj_t *label_ec_value;
lv_obj_t *label_ec_temp;
lv_obj_t *label_ec_temp_value;
/*-------------------------*/


/* water */
lv_obj_t * lmeter_wt;
lv_obj_t * lmeter_wt_total;
lv_obj_t *label_wt;
lv_obj_t *label_wt_value;
lv_obj_t *label_wt_total;
lv_obj_t *label_wt_total_value;
/*-------------------------*/

/* tank */
lv_obj_t * tank1;
lv_obj_t *label_tank1;
lv_obj_t *label_tank1_value;

lv_obj_t * tank2;
lv_obj_t *label_tank2;
lv_obj_t *label_tank2_value;

/*********/
lv_obj_t * gauge1;
lv_obj_t * label_gauge1_value;

/*-----------*/

static void updateRs485Value(lv_task_t *task) {
  // Print the count to the Serial monitor

  // Update the text of the label
  char TMP_PH[10];
  Serial.print("POST PH IN DISPLAYS : ");
  Serial.println(PostPH);
  dtostrf( PostPH, 2, 1, TMP_PH);
  lv_label_set_text(label_ph_value, TMP_PH);
  lv_obj_align(label_ph_value, label_ph, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

  lv_linemeter_set_value(lmeter_ph, PostPH );

  char TMP_PH_TEMP[10];
  Serial.print("POST PH TEMP IN DISPLAYS : ");
  Serial.println(PostPHTEMP);
  dtostrf(PostPHTEMP , 2, 1, TMP_PH_TEMP);
  lv_label_set_text(label_ph_temp_value, TMP_PH_TEMP);
  lv_obj_align(label_ph_temp_value, label_ph_temp, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

  lv_linemeter_set_value(lmeter_ph_temp, PostPHTEMP);

  char TMP_EC[10];
  Serial.print("POST EC IN DISPLAYS : ");
  Serial.println(PostEC);
  dtostrf(PostEC, 2, 1, TMP_EC);
  lv_label_set_text(label_ec_value, TMP_EC);
  lv_obj_align(label_ec_value, label_ec, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

  lv_linemeter_set_value(lmeter_ec, PostEC );

  char TMP_EC_TEMP[10];
  Serial.print("POST EC TEMP IN DISPLAYS : ");
  Serial.println(PostECTEMP);
  dtostrf(PostECTEMP , 2, 1, TMP_EC_TEMP);
  lv_label_set_text(label_ec_temp_value, TMP_EC_TEMP);
  lv_obj_align(label_ec_temp_value, label_ec_temp, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

  lv_linemeter_set_value(lmeter_ec_temp, PostECTEMP);



  lv_bar_set_value(tank1, SCL_TANK, LV_ANIM_ON);

  char TMP_TANK1[10];

  dtostrf(SCL_TANK, 2, 0, TMP_TANK1);
  lv_label_set_text(label_tank1_value, TMP_TANK1);
  lv_obj_align(label_tank1_value, label_tank1, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

  lv_bar_set_value(tank2, BCL_TANK, LV_ANIM_ON);

  char TMP_TANK2[10];

  dtostrf(BCL_TANK, 2, 0, TMP_TANK2);
  lv_label_set_text(label_tank2_value, TMP_TANK2);
  lv_obj_align(label_tank2_value, label_tank2, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);


  //    char TMP_WATER_FLOW[10];
  //    Serial.print("POST WATER FLOW IN DISPLAYS : ");
  //    Serial.println(PostWaterFlow);
  //    //  dtostrf( PostWaterFlow, 2, 1, TMP_WATER_FLOW);
  //    dtostrf(SCL_TANK, 2, 0, TMP_WATER_FLOW);
  //    lv_label_set_text(label_wt_value, TMP_WATER_FLOW);
  //    lv_obj_align(label_wt_value, label_wt, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
  //
  //    //  lv_linemeter_set_value(lmeter_wt,  PostWaterFlow);
  //    lv_linemeter_set_value(lmeter_wt,  SCL_TANK);
  //
  //    char TMP_WATER_TOTAL[10];
  //    Serial.print("POST WATER TOTAL IN DISPLAYS : ");
  //    Serial.println(PostWaterFlow);
  //    //  dtostrf( PostWaterTotal, 2, 0, TMP_WATER_TOTAL);
  //    dtostrf(BCL_TANK, 2, 0, TMP_WATER_TOTAL);
  //    lv_label_set_text(label_wt_total_value, TMP_WATER_TOTAL);
  //    lv_obj_align(label_wt_total_value, label_wt_total, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
  //
  //
  //  //  lv_linemeter_set_value(lmeter_wt_total, PostWaterTotal);
  //  lv_linemeter_set_value(lmeter_wt_total, BCL_TANK);


  char TMP_BOARD_TEMP[10];
  char TMP_BOARD_HUM[10];
  char TMP_BOARD_TEMP_TEST[10];

  Serial.print("POST BOARD TEMP IN DISPLAYS : ");
  Serial.println(PostBOARDTEMP);
  dtostrf(PostBOARDTEMP , 2, 1, TMP_BOARD_TEMP);
  dtostrf(PostBOARDHUM , 2, 1, TMP_BOARD_HUM);
  //  dtostrf(TEMP_TEST , 2, 1, TMP_BOARD_TEMP_TEST);

  String BT_DISPLAY = String(TMP_BOARD_TEMP) + "*C|" + String(TMP_BOARD_HUM) + "%";
  lv_label_set_text(label_gauge1_value, BT_DISPLAY.c_str());
  lv_obj_align(label_gauge1_value, gauge1, LV_ALIGN_IN_BOTTOM_MID, 0, -20);

  lv_gauge_set_value(gauge1, 0, PostBOARDTEMP);
  lv_gauge_set_value(gauge1, 1, PostBOARDHUM);


}

static void updateTime(lv_task_t *task) {
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
    if ((timeinfo->tm_year + 1900) >= 2022)
    {
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
  }

  Day = DateTimeNewFormat(Day);
  Month = DateTimeNewFormat(Month);
  Hours = DateTimeNewFormat(Hours);
  Min = DateTimeNewFormat(Min);
  Sec = DateTimeNewFormat(Sec);



  String newTime = Hours + ":" + Min + ":" + Sec;
  String newDate = "DATE-TIME: " + Day + "/" + Month + "/" + Year + "|" + newTime;

  //  Serial.println("DAY : " + String(data->tm_mday) + " MONTH : " + String(data -> tm_mon) + " YEAR : " + String(data -> tm_year));
  //  Serial.println();
  //  Serial.print("NOW : ");
  //  Serial.println(now);


  lv_label_set_text(label_time, newDate.c_str());
  lv_obj_align(label_time, obj1, LV_ALIGN_IN_TOP_MID, 0, 0);
  lv_label_set_recolor(label_wifi, true);
  lv_label_set_text(label_wifi, (WiFi.status() == WL_CONNECTED) ? "#009933 WIFI CONNECT#" : "#cc0000 WIFI NOT CONNECT#");
  lv_obj_align(label_wifi, label_time, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

}



void tab_1 ()
{
  obj1 = lv_obj_create(tab1, NULL);
  lv_obj_set_size(obj1, 310, 60);
  lv_obj_align(obj1, NULL, LV_ALIGN_IN_TOP_MID, 0, 10);

  label_time = lv_label_create(tab1, NULL);
  lv_obj_set_style_local_text_font(label_time, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, &lv_font_rsu_24);
  lv_label_set_text(label_time, "DATE-TIME: ");
  lv_obj_align(label_time, obj1, LV_ALIGN_IN_TOP_MID, 0, 0);

  label_wifi = lv_label_create(tab1, NULL);
  lv_obj_set_style_local_text_font(label_wifi, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, &lv_font_rsu_24);
  lv_label_set_text(label_wifi, "WIFI STATUS");
  lv_obj_align(label_wifi, label_time, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
  /////////////////////////////////////////////////////// PH METER ///////////////////////////////////////////////////////////////////////////////
  phMeter();
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////// EC METER ///////////////////////////////////////////////////////////////////////////////
  ecMeter();
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////// WATER METER ///////////////////////////////////////////////////////////////////////////////
  //  waterMeter();
  tankMeter();
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  static lv_color_t needle_colors[3];
  needle_colors[0] = LV_COLOR_PURPLE;
  needle_colors[1] = LV_COLOR_BLUE;


  /*Create a gauge*/
  gauge1 = lv_gauge_create(tab1, NULL);
  lv_gauge_set_needle_count(gauge1, 2, needle_colors);
  lv_gauge_set_range(gauge1, 0, 100);
  lv_obj_set_size(gauge1, 200, 200);
  lv_obj_align(gauge1, lmeter_ec_temp , LV_ALIGN_OUT_BOTTOM_MID, 5, 15);



  label_gauge1_value = lv_label_create(tab1, NULL);
  lv_obj_set_style_local_text_font( label_gauge1_value, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, &lv_font_rsu_24);
  char TMP_BOARD_TEMP[10];
  Serial.print("POST BOARD TEMP IN DISPLAYS : ");
  Serial.println(PostBOARDTEMP);
  dtostrf(PostBOARDTEMP , 2, 1, TMP_BOARD_TEMP);
  lv_label_set_text(label_gauge1_value, TMP_BOARD_TEMP);
  lv_obj_align(label_gauge1_value, gauge1, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
  /*Set the values*/
  lv_gauge_set_value(gauge1, 0, PostBOARDTEMP);
  lv_gauge_set_value(gauge1, 1, PostBOARDHUM);

}

/* tab 2 Object */
lv_obj_t * sw_auto;
lv_obj_t * sw_ph;
lv_obj_t * sw_ec;
lv_obj_t * sw_th;
lv_obj_t * sw_wt;
lv_obj_t * sw1;
lv_obj_t * sw2;
lv_obj_t * sw3;
lv_obj_t * sw4;
lv_obj_t * sw_fan;
/* ----------- */

void updateRelayDisplay() {
  // Print the count to the Serial monitor
  if (state[0]) {
    lv_switch_on(sw1, LV_ANIM_ON);
  } else {
    lv_switch_off(sw1, LV_ANIM_ON);
  }
  if (state[1]) {
    lv_switch_on(sw2, LV_ANIM_ON);
  } else {
    lv_switch_off(sw2, LV_ANIM_ON);
  }
  if (state[2]) {
    lv_switch_on(sw3, LV_ANIM_ON);
  } else {
    lv_switch_off(sw3, LV_ANIM_ON);
  }
  if (state[3]) {
    lv_switch_on(sw4, LV_ANIM_ON);
  } else {
    lv_switch_off(sw4, LV_ANIM_ON);
  }

  if (Auto)
  {
    lv_switch_on(sw_auto, LV_ANIM_ON);
  }
  else
  {
    lv_switch_off(sw_auto, LV_ANIM_ON);
  }

  if (phInputState) {
    lv_switch_on(sw_ph, LV_ANIM_ON);
  } else {
    lv_switch_off(sw_ph, LV_ANIM_ON);
  }

  if (ecInputState) {
    lv_switch_on(sw_ec, LV_ANIM_ON);
  } else {
    lv_switch_off(sw_ec, LV_ANIM_ON);
  }

  if (tempHumInputState) {
    lv_switch_on(sw_th, LV_ANIM_ON);
  } else {
    lv_switch_off(sw_th, LV_ANIM_ON);
  }

  if (fan) {
    lv_switch_on(sw_fan, LV_ANIM_ON);
  } else {
    lv_switch_off(sw_fan, LV_ANIM_ON);
  }

  if (ultraSonicInputState) {
    lv_switch_on(sw_wt, LV_ANIM_ON);
  } else {
    lv_switch_off(sw_wt, LV_ANIM_ON);
  }


}

lv_obj_t *label_Switch;
lv_obj_t *label_Switch_Auto;
lv_obj_t *label_Switch_ph;
lv_obj_t *label_Switch_ec;
lv_obj_t *label_Switch_th;
lv_obj_t *label_Switch_wt;
lv_obj_t *label_Switch1;
lv_obj_t *label_Switch2;
lv_obj_t *label_Switch3;
lv_obj_t *label_Switch_fan;
static void relaynametask (lv_task_t *task)
{


  lv_label_set_text(label_Switch1, pinName[0]);
  lv_obj_align(label_Switch1, sw1, LV_ALIGN_OUT_LEFT_MID, -10, 0);

  lv_label_set_text(label_Switch2, pinName[1]);
  lv_obj_align(label_Switch2, sw2, LV_ALIGN_OUT_LEFT_MID, -10, 0);

  lv_label_set_text(label_Switch3, pinName[2]);
  lv_obj_align(label_Switch3, sw3, LV_ALIGN_OUT_LEFT_MID, -10, 0);

  lv_label_set_text(label_Switch, "ALERT");
  lv_obj_align(label_Switch, sw4, LV_ALIGN_OUT_LEFT_MID, -10, 0);

}

void tab_2()
{

  sw1 = lv_switch_create(tab2, NULL);
  lv_obj_align(sw1, NULL, LV_ALIGN_IN_TOP_MID, 20, 50);
  lv_obj_set_user_data(sw1, (void*)&p0);
  lv_obj_set_event_cb(sw1, event_handler);
  if (state[0]) {
    lv_switch_on(sw1, LV_ANIM_ON);
  } else {
    lv_switch_off(sw1, LV_ANIM_ON);
  }

  label_Switch_Auto = lv_label_create(tab2, NULL);
  lv_obj_set_style_local_text_font(label_Switch_Auto, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, &lv_font_rsu_24);
  lv_label_set_recolor(label_Switch_Auto, true);
  lv_label_set_text(label_Switch_Auto, "#000099 A##6600cc U##000099 T##6600cc O#");
  lv_obj_align(label_Switch_Auto, sw1 , LV_ALIGN_OUT_RIGHT_MID, 20, 0);

  sw_auto = lv_switch_create(tab2, NULL);
  lv_obj_align(sw_auto, label_Switch_Auto, LV_ALIGN_OUT_RIGHT_MID, 55, 0);
  lv_obj_set_user_data(sw_auto, (void*)&p4);
  lv_obj_set_event_cb(sw_auto, event_handler);
  if (Auto) {
    lv_switch_on(sw_auto, LV_ANIM_ON);
  } else {
    lv_switch_off(sw_auto, LV_ANIM_ON);
  }




  sw2 = lv_switch_create(tab2, NULL);
  lv_obj_align(sw2, sw1, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
  lv_obj_set_event_cb(sw2, event_handler);
  lv_obj_set_user_data(sw2, (void*)&p1);
  if (state[1]) {
    lv_switch_on(sw2, LV_ANIM_ON);
  } else {
    lv_switch_off(sw2, LV_ANIM_ON);
  }


  label_Switch_ph = lv_label_create(tab2, NULL);
  lv_obj_set_style_local_text_font(label_Switch_ph, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, &lv_font_rsu_24);
  lv_label_set_recolor(label_Switch_ph, true);
  lv_label_set_text(label_Switch_ph, "PH INPUT");
  lv_obj_align(label_Switch_ph, sw2 , LV_ALIGN_OUT_RIGHT_MID, 20, 0);

  sw_ph = lv_switch_create(tab2, NULL);
  lv_obj_align(sw_ph, label_Switch_ph, LV_ALIGN_OUT_RIGHT_MID, 20, 0);
  lv_obj_set_user_data(sw_ph, (void*)&p5);
  lv_obj_set_event_cb(sw_ph, event_handler);
  if (phInputState) {
    lv_switch_on(sw_ph, LV_ANIM_ON);
  } else {
    lv_switch_off(sw_ph, LV_ANIM_ON);
  }

  sw3 = lv_switch_create(tab2, NULL);
  lv_obj_align(sw3, sw2, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
  lv_obj_set_event_cb(sw3, event_handler);
  lv_obj_set_user_data(sw3, (void*)&p2);
  if (state[2]) {
    lv_switch_on(sw3, LV_ANIM_ON);
  } else {
    lv_switch_off(sw3, LV_ANIM_ON);
  }

  label_Switch_ec = lv_label_create(tab2, NULL);
  lv_obj_set_style_local_text_font(label_Switch_ec, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, &lv_font_rsu_24);
  lv_label_set_recolor(label_Switch_ec, true);
  lv_label_set_text(label_Switch_ec, "EC INPUT");
  lv_obj_align(label_Switch_ec, sw3 , LV_ALIGN_OUT_RIGHT_MID, 20, 0);

  sw_ec = lv_switch_create(tab2, NULL);
  lv_obj_align(sw_ec, label_Switch_ec, LV_ALIGN_OUT_RIGHT_MID, 20, 0);
  lv_obj_set_user_data(sw_ec, (void*)&p6);
  lv_obj_set_event_cb(sw_ec, event_handler);
  if (ecInputState) {
    lv_switch_on(sw_ec, LV_ANIM_ON);
  } else {
    lv_switch_off(sw_ec, LV_ANIM_ON);
  }

  sw4 = lv_switch_create(tab2, NULL);
  lv_obj_align(sw4, sw3, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
  lv_obj_set_event_cb(sw4, event_handler);
  lv_obj_set_user_data(sw4, (void*)&p3);
  if (state[3]) {
    lv_switch_on(sw4, LV_ANIM_ON);
  } else {
    lv_switch_off(sw4, LV_ANIM_ON);
  }

  label_Switch_th = lv_label_create(tab2, NULL);
  lv_obj_set_style_local_text_font(label_Switch_th, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, &lv_font_rsu_24);
  lv_label_set_recolor(label_Switch_th, true);
  lv_label_set_text(label_Switch_th, "TH INPUT");
  lv_obj_align(label_Switch_th, sw4 , LV_ALIGN_OUT_RIGHT_MID, 20, 0);

  sw_th = lv_switch_create(tab2, NULL);
  lv_obj_align(sw_th, label_Switch_th, LV_ALIGN_OUT_RIGHT_MID, 17, 0);
  lv_obj_set_user_data(sw_th, (void*)&p7);
  lv_obj_set_event_cb(sw_th, event_handler);
  if (tempHumInputState) {
    lv_switch_on(sw_th, LV_ANIM_ON);
  } else {
    lv_switch_off(sw_th, LV_ANIM_ON);
  }

  sw_fan = lv_switch_create(tab2, NULL);
  lv_obj_align(sw_fan, sw4, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
  lv_obj_set_event_cb(sw_fan, event_handler);
  lv_obj_set_user_data(sw_fan, (void*)&p8);
  if (fan) {
    lv_switch_on(sw_fan, LV_ANIM_ON);
  } else {
    lv_switch_off(sw_fan, LV_ANIM_ON);
  }

  label_Switch_wt = lv_label_create(tab2, NULL);
  lv_obj_set_style_local_text_font(label_Switch_wt, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, &lv_font_rsu_24);
  lv_label_set_recolor(label_Switch_wt, true);
  lv_label_set_text(label_Switch_wt, "US INPUT");
  lv_obj_align(label_Switch_wt, sw_fan , LV_ALIGN_OUT_RIGHT_MID, 20, 0);

  sw_wt = lv_switch_create(tab2, NULL);
  lv_obj_align(sw_wt, label_Switch_wt, LV_ALIGN_OUT_RIGHT_MID, 17, 0);
  lv_obj_set_user_data(sw_wt, (void*)&p9);
  lv_obj_set_event_cb(sw_wt, event_handler);
  if (ultraSonicInputState) {
    lv_switch_on(sw_wt, LV_ANIM_ON);
  } else {
    lv_switch_off(sw_wt, LV_ANIM_ON);
  }

  label_Switch = lv_label_create(tab2, NULL);
  lv_obj_set_style_local_text_font(label_Switch, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, &lv_font_rsu_24);
  lv_label_set_text(label_Switch, "MANUAL CONTROL");
  lv_obj_align(label_Switch, NULL, LV_ALIGN_IN_TOP_MID, 0, 10);

  label_Switch1 = lv_label_create(tab2, NULL);
  lv_obj_set_style_local_text_font(label_Switch1, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, &lv_font_rsu_24);
  lv_label_set_text(label_Switch1, pinName[0]);
  lv_obj_align(label_Switch1, sw1, LV_ALIGN_OUT_LEFT_MID, -10, 0);

  label_Switch2 = lv_label_create(tab2, NULL);
  lv_obj_set_style_local_text_font(label_Switch2, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, &lv_font_rsu_24);
  lv_label_set_text(label_Switch2, pinName[1]);
  lv_obj_align(label_Switch2, sw2, LV_ALIGN_OUT_LEFT_MID, -10, 0);

  label_Switch3 = lv_label_create(tab2, NULL);
  lv_obj_set_style_local_text_font(label_Switch3, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, &lv_font_rsu_24);
  lv_label_set_text(label_Switch3, pinName[2]);
  lv_obj_align(label_Switch3, sw3, LV_ALIGN_OUT_LEFT_MID, -10, 0);

  label_Switch = lv_label_create(tab2, NULL);
  lv_obj_set_style_local_text_font(label_Switch, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, &lv_font_rsu_24);
  lv_label_set_text(label_Switch, "ALERT");
  lv_obj_align(label_Switch, sw4, LV_ALIGN_OUT_LEFT_MID, -10, 0);

  label_Switch_fan = lv_label_create(tab2, NULL);
  lv_obj_set_style_local_text_font(label_Switch_fan, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, &lv_font_rsu_24);
  lv_label_set_text(label_Switch_fan, "FAN");
  lv_obj_align(label_Switch_fan, sw_fan, LV_ALIGN_OUT_LEFT_MID, -10, 0);
}


/* tab3 Object */
lv_obj_t * obj_wifi;
lv_obj_t * info;
lv_obj_t * mbox_tab3;
lv_style_t style_modal;
lv_obj_t *label_tab3_wifi_ssid;
lv_obj_t *label_tab3_wifi_ssid_name;
lv_obj_t *label_tab3_bid;
lv_obj_t *label_tab3_bname;
lv_obj_t *label_tab3_ver;
lv_obj_t *btn_clear;
/* ---------- */

static void mbox_event_cb(lv_obj_t *obj, lv_event_t evt)
{
  if (evt == LV_EVENT_DELETE)
  {
    /* Delete the parent modal background */
    lv_obj_del_async(lv_obj_get_parent(mbox_tab3));
    mbox_tab3 = NULL;

  }

  if (evt == LV_EVENT_VALUE_CHANGED)
  {
    /* A button was clicked */

    lv_msgbox_start_auto_close(mbox_tab3, 0);

    printf("Button: %s\n", lv_msgbox_get_active_btn_text(obj));

    if (lv_msgbox_get_active_btn_text(obj) == "Ok")
    {
      Serial.println(" RESSET WIFI ");
      resetWifi();
    }
  }
}

static void button_event_handler(lv_obj_t *obj, lv_event_t e) {
  if (e == LV_EVENT_CLICKED) {

    /* Create a base object for the modal background */
    lv_obj_t *obj = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_reset_style_list(obj, LV_OBJ_PART_MAIN);
    lv_obj_add_style(obj, LV_OBJ_PART_MAIN, &style_modal);
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, LV_HOR_RES, LV_VER_RES);

    static const char * btns2[] = {"Ok", "Cancel", ""};

    /* Create the message box as a child of the modal background */
    mbox_tab3 = lv_msgbox_create(obj, NULL);
    lv_msgbox_add_btns(mbox_tab3, btns2);
    lv_msgbox_set_text(mbox_tab3, "Reset Wifi?");
    lv_obj_align(mbox_tab3, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_event_cb(mbox_tab3, mbox_event_cb);

    printf("Reset WIFI\n");
  }
}

static void button_clear_event_handler(lv_obj_t *obj, lv_event_t e) {
  if (e == LV_EVENT_CLICKED) {
    clearAll();
    printf("CLEAR ALL\n");
  }
}

static void updateWiFiStatus(lv_task_t *task) {
  // Print the count to the Serial monitor
  String ssidName = "";
  ssidName.concat(ssid);
  String text = "SSID : " + ssidName ;

  lv_label_set_text(label_tab3_wifi_ssid, text.c_str());
  lv_obj_align(label_tab3_wifi_ssid, obj_wifi , LV_ALIGN_IN_TOP_MID, 0, 10);

  lv_label_set_text(label_tab3, (WiFi.status() == WL_CONNECTED) ? "#009933 WIFI CONNECT#" : "#cc0000 WIFI NOT CONNECT#");
  lv_obj_align(label_tab3, label_tab3_wifi_ssid, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

  String b_id = "";
  b_id.concat(device_id);
  String text2 = "BOARD ID : " + b_id;
  lv_label_set_text(label_tab3_bid, text2.c_str());
  lv_obj_align(label_tab3_bid, label_tab3, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);

  String b_name = "";
  b_name.concat(device_name);
  String text3 = "BOARD NAME : " + b_name;

  lv_label_set_text(label_tab3_bname, text3.c_str());
  lv_obj_align(label_tab3_bname, label_tab3_bid, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);

  String v = "VERSION : #cc6600 " + ver + "#";

  lv_label_set_text(label_tab3_ver, v.c_str());
  lv_obj_align(label_tab3_ver, label_tab3_bname, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);

}




void tab_3 ()
{
  obj_wifi = lv_obj_create(tab3, NULL);
  lv_obj_set_size(obj_wifi, 310, 140);
  lv_obj_align(obj_wifi, NULL, LV_ALIGN_IN_TOP_MID, 0, 10);

  btn_resetWiFi = lv_btn_create(tab3, NULL);
  lv_obj_set_event_cb(btn_resetWiFi, button_event_handler);
  lv_obj_align(btn_resetWiFi, obj_wifi, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

  lv_obj_t *btn1_label = lv_label_create(btn_resetWiFi, NULL);
  lv_label_set_text(btn1_label, "RESET WIFI");


  //  btn_clear = lv_btn_create(tab3, NULL);
  //  lv_obj_set_event_cb(btn_clear, button_clear_event_handler);
  //  lv_obj_align(btn_clear, btn_resetWiFi, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
  //
  //  lv_obj_t *btn_clear_label = lv_label_create(btn_clear, NULL);
  //  lv_label_set_text(btn_clear_label, "CLEAR ALL");

  label_tab3 = lv_label_create(tab3, NULL);
  lv_label_set_recolor(label_tab3, true);
  lv_obj_set_style_local_text_font(label_tab3, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, &lv_font_rsu_24);


  label_tab3_wifi_ssid = lv_label_create(tab3, NULL);
  lv_label_set_text(label_tab3_wifi_ssid, ssid);

  String b_id = "";
  b_id.concat(device_id);

  label_tab3_bid = lv_label_create(tab3, NULL);
  lv_label_set_text(label_tab3_bid, b_id.c_str());
  lv_obj_align(label_tab3_bid, label_tab3, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);

  String b_name = "";
  b_name.concat(device_name);

  label_tab3_bname = lv_label_create(tab3, NULL);
  lv_label_set_text(label_tab3_bname, b_name.c_str());
  lv_obj_align(label_tab3_bname, label_tab3_bid, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);


  String v = "VERSION : " + ver;

  label_tab3_ver = lv_label_create(tab3, NULL);
  lv_label_set_recolor(label_tab3_ver, true);

  lv_label_set_text(label_tab3_ver, v.c_str());
  lv_obj_align(label_tab3_ver, label_tab3_bname, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);

}
