// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.1
// LVGL VERSION: 8.2.0
// PROJECT: 240240proj

#ifndef _240240PROJ_UI_H
#define _240240PROJ_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined __has_include
  #if __has_include("lvgl.h")
    #include "lvgl.h"
  #elif __has_include("lvgl/lvgl.h")
    #include "lvgl/lvgl.h"
  #else
    #include "lvgl.h"
  #endif
#else
  #include "lvgl.h"
#endif

extern lv_obj_t *ui_home_;
void ui_event_tempArc( lv_event_t * e);
extern lv_obj_t *ui_tempArc;
extern lv_obj_t *ui_actualLabel;
extern lv_obj_t *ui_octonailLabel;
void ui_event_targetAKAsetpoint( lv_event_t * e);
extern lv_obj_t *ui_targetAKAsetpoint;
extern lv_obj_t *ui_targetLabel;
extern lv_obj_t *ui_actual;
void ui_event_power( lv_event_t * e);
extern lv_obj_t *ui_power;
void ui_event_Slider2( lv_event_t * e);
extern lv_obj_t *ui_Slider2;
void ui_event_Button2( lv_event_t * e);
extern lv_obj_t *ui_Button2;
extern lv_obj_t *ui_settings;
extern lv_obj_t *ui_Roller2;
extern lv_obj_t *ui_Screen1;
extern lv_obj_t *ui_Spinner1;
extern lv_obj_t *ui_octoNailIsLoading;

void getNewSetpoint(lv_event_t * e);
void runDaPID(lv_event_t * e);

extern bool PIDrunning;




void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
