// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.2.2
// LVGL version: 8.2.0
// Project name: octo_nail

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t *ui_home_;
lv_obj_t *ui_tempArc1;
lv_obj_t *ui_actualLabel;
void ui_event_targetAKAsetpoint( lv_event_t * e);
lv_obj_t *ui_targetAKAsetpoint;
lv_obj_t *ui_targetLabel;
lv_obj_t *ui_actual;
void ui_event_power( lv_event_t * e);
lv_obj_t *ui_power;
void ui_event_buttonForGoingToSettings( lv_event_t * e);
lv_obj_t *ui_buttonForGoingToSettings;
void ui_event_octonailLabel( lv_event_t * e);
lv_obj_t *ui_octonailLabel;
lv_obj_t *ui_settings;
lv_obj_t *ui_Roller2;
lv_obj_t *ui_Spinner2;
lv_obj_t *ui____initial_actions0;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=1
    #error "LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_targetAKAsetpoint( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_VALUE_CHANGED) {
      getNewSetpoint( e );
}
}
void ui_event_power( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      runDaPID( e );
}
}
void ui_event_buttonForGoingToSettings( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( ui_settings, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0);
}
}
void ui_event_octonailLabel( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( ui_settings, LV_SCR_LOAD_ANIM_NONE, 0, 0);
}
}

///////////////////// SCREENS ////////////////////
void ui_home__screen_init(void)
{
ui_home_ = lv_obj_create(NULL);
lv_obj_clear_flag( ui_home_, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM );    /// Flags

ui_tempArc1 = lv_arc_create(ui_home_);
lv_obj_set_width( ui_tempArc1, 240);
lv_obj_set_height( ui_tempArc1, 240);
lv_obj_set_align( ui_tempArc1, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_tempArc1, LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_tempArc1, LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN );    /// Flags
lv_arc_set_range(ui_tempArc1, 100,420);
lv_arc_set_value(ui_tempArc1, 260);
lv_obj_set_style_radius(ui_tempArc1, 200, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_tempArc1, lv_color_hex(0x8304BD), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_tempArc1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_grad_color(ui_tempArc1, lv_color_hex(0x06BDE5), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_grad_dir(ui_tempArc1, LV_GRAD_DIR_VER, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_tempArc1, 6, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_tempArc1, 6, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_tempArc1, 6, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_tempArc1, 6, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_arc_color(ui_tempArc1, lv_color_hex(0x00FF3A), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_arc_opa(ui_tempArc1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_arc_width(ui_tempArc1, 10, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_set_style_arc_color(ui_tempArc1, lv_color_hex(0xFF008E), LV_PART_INDICATOR | LV_STATE_DEFAULT );
lv_obj_set_style_arc_opa(ui_tempArc1, 255, LV_PART_INDICATOR| LV_STATE_DEFAULT);
lv_obj_set_style_arc_width(ui_tempArc1, 10, LV_PART_INDICATOR| LV_STATE_DEFAULT);

lv_obj_set_style_bg_color(ui_tempArc1, lv_color_hex(0x0019FF), LV_PART_KNOB | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_tempArc1, 255, LV_PART_KNOB| LV_STATE_DEFAULT);
lv_obj_set_style_outline_color(ui_tempArc1, lv_color_hex(0x000000), LV_PART_KNOB | LV_STATE_DEFAULT );
lv_obj_set_style_outline_opa(ui_tempArc1, 255, LV_PART_KNOB| LV_STATE_DEFAULT);
lv_obj_set_style_outline_width(ui_tempArc1, 2, LV_PART_KNOB| LV_STATE_DEFAULT);
lv_obj_set_style_outline_pad(ui_tempArc1, 0, LV_PART_KNOB| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_color(ui_tempArc1, lv_color_hex(0x000000), LV_PART_KNOB | LV_STATE_DEFAULT );
lv_obj_set_style_shadow_opa(ui_tempArc1, 255, LV_PART_KNOB| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_width(ui_tempArc1, 15, LV_PART_KNOB| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_spread(ui_tempArc1, 3, LV_PART_KNOB| LV_STATE_DEFAULT);
lv_obj_set_style_outline_color(ui_tempArc1, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_CHECKED );
lv_obj_set_style_outline_opa(ui_tempArc1, 255, LV_PART_KNOB| LV_STATE_CHECKED);
lv_obj_set_style_shadow_color(ui_tempArc1, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_PRESSED );
lv_obj_set_style_shadow_opa(ui_tempArc1, 255, LV_PART_KNOB| LV_STATE_PRESSED);
lv_obj_set_style_shadow_color(ui_tempArc1, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_FOCUSED );
lv_obj_set_style_shadow_opa(ui_tempArc1, 120, LV_PART_KNOB| LV_STATE_FOCUSED);
lv_obj_set_style_shadow_width(ui_tempArc1, 30, LV_PART_KNOB| LV_STATE_FOCUSED);
lv_obj_set_style_shadow_spread(ui_tempArc1, 15, LV_PART_KNOB| LV_STATE_FOCUSED);

ui_actualLabel = lv_label_create(ui_home_);
lv_obj_set_width( ui_actualLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_actualLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_actualLabel, 1 );
lv_obj_set_y( ui_actualLabel, 29 );
lv_obj_set_align( ui_actualLabel, LV_ALIGN_CENTER );
lv_label_set_text(ui_actualLabel,"actual");
lv_obj_clear_flag( ui_actualLabel, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN );    /// Flags
lv_obj_set_style_text_font(ui_actualLabel, &lv_font_montserrat_20, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_targetAKAsetpoint = lv_label_create(ui_home_);
lv_obj_set_width( ui_targetAKAsetpoint, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_targetAKAsetpoint, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_targetAKAsetpoint, -1 );
lv_obj_set_y( ui_targetAKAsetpoint, -72 );
lv_obj_set_align( ui_targetAKAsetpoint, LV_ALIGN_CENTER );
lv_label_set_text(ui_targetAKAsetpoint,"");
lv_obj_clear_flag( ui_targetAKAsetpoint, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN );    /// Flags
lv_obj_set_style_text_font(ui_targetAKAsetpoint, &lv_font_montserrat_36, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_targetLabel = lv_label_create(ui_home_);
lv_obj_set_width( ui_targetLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_targetLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_targetLabel, -1 );
lv_obj_set_y( ui_targetLabel, -50 );
lv_obj_set_align( ui_targetLabel, LV_ALIGN_CENTER );
lv_label_set_text(ui_targetLabel,"target");
lv_obj_clear_flag( ui_targetLabel, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN );    /// Flags
lv_obj_set_style_text_font(ui_targetLabel, &lv_font_montserrat_16, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_actual = lv_label_create(ui_home_);
lv_obj_set_width( ui_actual, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_actual, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_actual, LV_ALIGN_CENTER );
lv_label_set_text(ui_actual,"");
lv_obj_clear_flag( ui_actual, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN );    /// Flags
lv_obj_set_style_text_font(ui_actual, &lv_font_montserrat_48, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_power = lv_switch_create(ui_home_);
lv_obj_set_width( ui_power, 50);
lv_obj_set_height( ui_power, 29);
lv_obj_set_x( ui_power, 1 );
lv_obj_set_y( ui_power, -45 );
lv_obj_set_align( ui_power, LV_ALIGN_BOTTOM_MID );

lv_obj_set_style_shadow_color(ui_power, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_FOCUSED );
lv_obj_set_style_shadow_opa(ui_power, 120, LV_PART_INDICATOR| LV_STATE_FOCUSED);
lv_obj_set_style_shadow_width(ui_power, 30, LV_PART_INDICATOR| LV_STATE_FOCUSED);
lv_obj_set_style_shadow_spread(ui_power, 15, LV_PART_INDICATOR| LV_STATE_FOCUSED);

ui_buttonForGoingToSettings = lv_btn_create(ui_home_);
lv_obj_set_width( ui_buttonForGoingToSettings, 100);
lv_obj_set_height( ui_buttonForGoingToSettings, 31);
lv_obj_set_x( ui_buttonForGoingToSettings, 1 );
lv_obj_set_y( ui_buttonForGoingToSettings, 94 );
lv_obj_set_align( ui_buttonForGoingToSettings, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_buttonForGoingToSettings, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_buttonForGoingToSettings, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_buttonForGoingToSettings, lv_color_hex(0xFF00F7), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_buttonForGoingToSettings, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_buttonForGoingToSettings, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_buttonForGoingToSettings, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_buttonForGoingToSettings, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_buttonForGoingToSettings, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_align(ui_buttonForGoingToSettings, LV_TEXT_ALIGN_AUTO, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_decor(ui_buttonForGoingToSettings, LV_TEXT_DECOR_NONE, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_color(ui_buttonForGoingToSettings, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_FOCUSED );
lv_obj_set_style_shadow_opa(ui_buttonForGoingToSettings, 255, LV_PART_MAIN| LV_STATE_FOCUSED);
lv_obj_set_style_shadow_width(ui_buttonForGoingToSettings, 4, LV_PART_MAIN| LV_STATE_FOCUSED);
lv_obj_set_style_shadow_spread(ui_buttonForGoingToSettings, 6, LV_PART_MAIN| LV_STATE_FOCUSED);

ui_octonailLabel = lv_label_create(ui_buttonForGoingToSettings);
lv_obj_set_width( ui_octonailLabel, LV_SIZE_CONTENT);  /// 120
lv_obj_set_height( ui_octonailLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_octonailLabel, 0 );
lv_obj_set_y( ui_octonailLabel, -5 );
lv_obj_set_align( ui_octonailLabel, LV_ALIGN_BOTTOM_MID );
lv_label_set_long_mode(ui_octonailLabel,LV_LABEL_LONG_SCROLL_CIRCULAR);
lv_label_set_text(ui_octonailLabel,"octo-nail");
lv_obj_clear_flag( ui_octonailLabel, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN );    /// Flags
lv_obj_set_style_text_color(ui_octonailLabel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_octonailLabel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_octonailLabel, &lv_font_montserrat_20, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_add_event_cb(ui_targetAKAsetpoint, ui_event_targetAKAsetpoint, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_power, ui_event_power, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_octonailLabel, ui_event_octonailLabel, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_buttonForGoingToSettings, ui_event_buttonForGoingToSettings, LV_EVENT_ALL, NULL);

}
void ui_settings_screen_init(void)
{
ui_settings = lv_obj_create(NULL);
lv_obj_clear_flag( ui_settings, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Roller2 = lv_roller_create(ui_settings);
lv_roller_set_options( ui_Roller2, "ui\nchime\ncalibrate\nhome", LV_ROLLER_MODE_NORMAL );
lv_obj_set_width( ui_Roller2, 240);
lv_obj_set_height( ui_Roller2, 240);
lv_obj_set_align( ui_Roller2, LV_ALIGN_CENTER );
lv_obj_set_style_radius(ui_Roller2, 800, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_Roller2, lv_color_hex(0xFF008E), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Roller2, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_set_style_text_color(ui_Roller2, lv_color_hex(0x000000), LV_PART_SELECTED | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_Roller2, 255, LV_PART_SELECTED| LV_STATE_DEFAULT);
lv_obj_set_style_radius(ui_Roller2, 400, LV_PART_SELECTED| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_Roller2, lv_color_hex(0x00FF3A), LV_PART_SELECTED | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Roller2, 255, LV_PART_SELECTED| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_Roller2, lv_color_hex(0x000000), LV_PART_SELECTED | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_Roller2, 255, LV_PART_SELECTED| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_Roller2, 2, LV_PART_SELECTED| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_color(ui_Roller2, lv_color_hex(0x000000), LV_PART_SELECTED | LV_STATE_DEFAULT );
lv_obj_set_style_shadow_opa(ui_Roller2, 255, LV_PART_SELECTED| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_width(ui_Roller2, 100, LV_PART_SELECTED| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_spread(ui_Roller2, 15, LV_PART_SELECTED| LV_STATE_DEFAULT);

ui_Spinner2 = lv_spinner_create(ui_settings,1000,90);
lv_obj_set_width( ui_Spinner2, 31);
lv_obj_set_height( ui_Spinner2, 33);
lv_obj_set_x( ui_Spinner2, 14 );
lv_obj_set_y( ui_Spinner2, -74 );
lv_obj_set_align( ui_Spinner2, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_Spinner2, LV_OBJ_FLAG_CLICKABLE );    /// Flags

}

void ui_init( void )
{LV_EVENT_GET_COMP_CHILD = lv_event_register_id();

lv_disp_t *dispp = lv_disp_get_default();
lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
lv_disp_set_theme(dispp, theme);
ui_home__screen_init();
ui_settings_screen_init();
ui____initial_actions0 = lv_obj_create(NULL);
lv_disp_load_scr( ui_home_);
}
