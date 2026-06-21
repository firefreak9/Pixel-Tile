#pragma once
#include <pebble.h>
#define SCREEN_W    200
#define SCREEN_H    228
#define BAR_H        16
#define TIME_H       52
#define TILE_AREA_H  (SCREEN_H - BAR_H*2 - TIME_H)
#define TILE_W       (SCREEN_W/2)
#define TILE_H       (TILE_AREA_H/2)

#define MESSAGE_KEY_FETCH_WEATHER  0
#define MESSAGE_KEY_USE_24H        1
#define MESSAGE_KEY_TEMP_UNIT      2
#define MESSAGE_KEY_TILE0          3
#define MESSAGE_KEY_TILE1          4
#define MESSAGE_KEY_TILE2          5
#define MESSAGE_KEY_TILE3          6
#define MESSAGE_KEY_HOURLY_NOW     7
#define MESSAGE_KEY_HEALTH_SLOT_A  8
#define MESSAGE_KEY_HEALTH_SLOT_B  9
#define MESSAGE_KEY_HEALTH_SLOT_C  10
#define MESSAGE_KEY_STEP_GOAL      17
#define MESSAGE_KEY_CAL_GOAL       18
#define MESSAGE_KEY_TOP_BAR        19
#define MESSAGE_KEY_BOT_BAR        20
#define MESSAGE_KEY_COLOR_BG       21
#define MESSAGE_KEY_COLOR_BORDER   22
#define MESSAGE_KEY_COLOR_FG       23
#define MESSAGE_KEY_COLOR_ACCENT   24

#define MESSAGE_KEY_WX_TEMP        30
#define MESSAGE_KEY_WX_COND        31
#define MESSAGE_KEY_WX_HI          32
#define MESSAGE_KEY_WX_LO          33
#define MESSAGE_KEY_WX_UV          34
#define MESSAGE_KEY_WX_HUMIDITY    35
#define MESSAGE_KEY_WX_SUNRISE     36
#define MESSAGE_KEY_WX_SUNSET      37
#define MESSAGE_KEY_WX_H_BASE      40
#define MESSAGE_KEY_WX_D_BASE      60
