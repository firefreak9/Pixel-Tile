#pragma once
#include <pebble.h>
void tiles_init(Layer *layer, GFont font_lg, GFont font_md, GFont font_sm);
void tiles_deinit(void);
void tiles_refresh(void);
