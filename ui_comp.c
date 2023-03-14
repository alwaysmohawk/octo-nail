// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.1
// LVGL VERSION: 8.2.0
// PROJECT: octo_nail


#include "ui.h"
#include "ui_helpers.h"
#include "ui_comp.h"

uint32_t LV_EVENT_GET_COMP_CHILD;

typedef struct {
uint32_t child_idx;
lv_obj_t* child;
} ui_comp_get_child_t;

lv_obj_t * ui_comp_get_child(lv_obj_t *comp, uint32_t child_idx) {
ui_comp_get_child_t info;
info.child = NULL;
info.child_idx = child_idx;
lv_event_send(comp, LV_EVENT_GET_COMP_CHILD, &info);
 return info.child;
}

void get_component_child_event_cb(lv_event_t* e) {
lv_obj_t** c = lv_event_get_user_data(e);
ui_comp_get_child_t* info = lv_event_get_param(e);
info->child = c[info->child_idx];
 }

void del_component_child_event_cb(lv_event_t* e) {
lv_obj_t** c = lv_event_get_user_data(e);
lv_mem_free(c); 
}


// COMPONENT temp arc

lv_obj_t *ui_temp_arc_create(lv_obj_t *comp_parent) {

lv_obj_t *cui_temp_arc;
cui_temp_arc = lv_arc_create(comp_parent);
lv_obj_set_width( cui_temp_arc, 240);
lv_obj_set_height( cui_temp_arc, 240);
lv_obj_set_align( cui_temp_arc, LV_ALIGN_CENTER );
lv_arc_set_range(cui_temp_arc, 120,340);
lv_arc_set_value(cui_temp_arc, 220);
lv_obj_set_style_radius(cui_temp_arc, 200, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(cui_temp_arc, lv_color_hex(0x8304BD), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(cui_temp_arc, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_grad_color(cui_temp_arc, lv_color_hex(0x06BDE5), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_grad_dir(cui_temp_arc, LV_GRAD_DIR_VER, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(cui_temp_arc, 6, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(cui_temp_arc, 6, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(cui_temp_arc, 6, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(cui_temp_arc, 6, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_arc_color(cui_temp_arc, lv_color_hex(0x00FF3A), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_arc_opa(cui_temp_arc, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_arc_width(cui_temp_arc, 10, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_set_style_arc_color(cui_temp_arc, lv_color_hex(0xFF008E), LV_PART_INDICATOR | LV_STATE_DEFAULT );
lv_obj_set_style_arc_opa(cui_temp_arc, 255, LV_PART_INDICATOR| LV_STATE_DEFAULT);
lv_obj_set_style_arc_width(cui_temp_arc, 10, LV_PART_INDICATOR| LV_STATE_DEFAULT);

lv_obj_set_style_bg_color(cui_temp_arc, lv_color_hex(0x0019FF), LV_PART_KNOB | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(cui_temp_arc, 255, LV_PART_KNOB| LV_STATE_DEFAULT);
lv_obj_set_style_outline_color(cui_temp_arc, lv_color_hex(0x000000), LV_PART_KNOB | LV_STATE_DEFAULT );
lv_obj_set_style_outline_opa(cui_temp_arc, 255, LV_PART_KNOB| LV_STATE_DEFAULT);
lv_obj_set_style_outline_width(cui_temp_arc, 2, LV_PART_KNOB| LV_STATE_DEFAULT);
lv_obj_set_style_outline_pad(cui_temp_arc, 0, LV_PART_KNOB| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_color(cui_temp_arc, lv_color_hex(0x000000), LV_PART_KNOB | LV_STATE_DEFAULT );
lv_obj_set_style_shadow_opa(cui_temp_arc, 255, LV_PART_KNOB| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_width(cui_temp_arc, 15, LV_PART_KNOB| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_spread(cui_temp_arc, 3, LV_PART_KNOB| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_color(cui_temp_arc, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_FOCUSED );
lv_obj_set_style_shadow_opa(cui_temp_arc, 255, LV_PART_KNOB| LV_STATE_FOCUSED);

lv_obj_t ** children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_TEMP_ARC_NUM);
children[UI_COMP_TEMP_ARC_TEMP_ARC] = cui_temp_arc;
lv_obj_add_event_cb(cui_temp_arc, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
lv_obj_add_event_cb(cui_temp_arc, del_component_child_event_cb, LV_EVENT_DELETE, children);
return cui_temp_arc; 
}



// COMPONENT temp arc1

lv_obj_t *ui_temp_arc1_create(lv_obj_t *comp_parent) {

lv_obj_t *cui_temp_arc1;
cui_temp_arc1 = lv_arc_create(comp_parent);
lv_obj_set_width( cui_temp_arc1, 240);
lv_obj_set_height( cui_temp_arc1, 240);
lv_obj_set_align( cui_temp_arc1, LV_ALIGN_CENTER );
lv_arc_set_range(cui_temp_arc1, 120,340);
lv_arc_set_value(cui_temp_arc1, 220);
lv_obj_set_style_radius(cui_temp_arc1, 200, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(cui_temp_arc1, lv_color_hex(0x8304BD), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(cui_temp_arc1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_grad_color(cui_temp_arc1, lv_color_hex(0x06BDE5), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_grad_dir(cui_temp_arc1, LV_GRAD_DIR_VER, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(cui_temp_arc1, 6, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(cui_temp_arc1, 6, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(cui_temp_arc1, 6, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(cui_temp_arc1, 6, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_arc_color(cui_temp_arc1, lv_color_hex(0x00FF3A), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_arc_opa(cui_temp_arc1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_arc_width(cui_temp_arc1, 10, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_set_style_arc_color(cui_temp_arc1, lv_color_hex(0xFF008E), LV_PART_INDICATOR | LV_STATE_DEFAULT );
lv_obj_set_style_arc_opa(cui_temp_arc1, 255, LV_PART_INDICATOR| LV_STATE_DEFAULT);
lv_obj_set_style_arc_width(cui_temp_arc1, 10, LV_PART_INDICATOR| LV_STATE_DEFAULT);

lv_obj_set_style_bg_color(cui_temp_arc1, lv_color_hex(0x0019FF), LV_PART_KNOB | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(cui_temp_arc1, 255, LV_PART_KNOB| LV_STATE_DEFAULT);
lv_obj_set_style_outline_color(cui_temp_arc1, lv_color_hex(0x000000), LV_PART_KNOB | LV_STATE_DEFAULT );
lv_obj_set_style_outline_opa(cui_temp_arc1, 255, LV_PART_KNOB| LV_STATE_DEFAULT);
lv_obj_set_style_outline_width(cui_temp_arc1, 2, LV_PART_KNOB| LV_STATE_DEFAULT);
lv_obj_set_style_outline_pad(cui_temp_arc1, 0, LV_PART_KNOB| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_color(cui_temp_arc1, lv_color_hex(0x000000), LV_PART_KNOB | LV_STATE_DEFAULT );
lv_obj_set_style_shadow_opa(cui_temp_arc1, 255, LV_PART_KNOB| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_width(cui_temp_arc1, 15, LV_PART_KNOB| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_spread(cui_temp_arc1, 3, LV_PART_KNOB| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_color(cui_temp_arc1, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_FOCUSED );
lv_obj_set_style_shadow_opa(cui_temp_arc1, 255, LV_PART_KNOB| LV_STATE_FOCUSED);

lv_obj_t ** children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_TEMP_ARC1_NUM);
children[UI_COMP_TEMP_ARC1_TEMP_ARC1] = cui_temp_arc1;
lv_obj_add_event_cb(cui_temp_arc1, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
lv_obj_add_event_cb(cui_temp_arc1, del_component_child_event_cb, LV_EVENT_DELETE, children);
return cui_temp_arc1; 
}

