#include "config.h"
#define CONFIG_KEY 0x4CF4
WatchConfig g_config;
void config_load(void){
  if(persist_exists(CONFIG_KEY)){persist_read_data(CONFIG_KEY,&g_config,sizeof(WatchConfig));}
  else{
    g_config.use_24h=false; g_config.temp_unit=UNIT_F;
    g_config.tile[0]=TILE_WEATHER_NOW; g_config.tile[1]=TILE_WEATHER_HOURLY;
    g_config.tile[2]=TILE_WEATHER_DAILY; g_config.tile[3]=TILE_HEALTH;
    g_config.hourly_show_current_first=true;
    g_config.health_slot_a=HSLOT_STEPS; g_config.health_slot_b=HSLOT_CALORIES;
    g_config.health_slot_c=HSLOT_HEART_RATE;
    g_config.step_goal=10000; g_config.cal_goal=500;
    g_config.top_bar_progress=BAR_SUN; g_config.bot_bar_progress=BAR_STEPS;
    g_config.color_bg=PX_OXFORD_BLUE; g_config.color_border=PX_BLACK;
    g_config.color_fg=PX_WHITE; g_config.color_accent=PX_MALACHITE;
  }
}
void config_save(void){persist_write_data(CONFIG_KEY,&g_config,sizeof(WatchConfig));}
