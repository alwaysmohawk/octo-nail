// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.1
// LVGL VERSION: 8.2.0
// PROJECT: 128160

#include "ui.h"
#include "octo-nail.h"
void turn_on_nail(lv_event_t * e)
{
	// Your code here
}

void getNewSetpoint(lv_event_t * e)
{
	// Your code here
}

void runDaPID(lv_event_t * e)
{
	if(!PIDrunning) PIDrunning = 1;
  else PIDrunning = 0;
}
