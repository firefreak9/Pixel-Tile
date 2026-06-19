#pragma once
#include <pebble.h>

#define HOURLY_SLOTS 6
#define DAILY_SLOTS  3

typedef enum {
  COND_UNKNOWN        = 0,
  COND_CLEAR_DAY      = 1,
  COND_CLEAR_NIGHT    = 2,
  COND_PARTLY_CLOUDY  = 3,
  COND_CLOUDY         = 4,
  COND_RAIN           = 5,
  COND_DRIZZLE        = 6,
  COND_SNOW           = 7,
  COND_SLEET          = 8,
  COND_THUNDERSTORM   = 9,
  COND_FOGGY          = 10,
  COND_WINDY          = 11,
} WeatherCondition;

typedef struct {
  int              temp;
  WeatherCondition condition;
  int              hi;
  int              lo;
  int              uv_index;    // 0-11
  int              humidity;    // 0-100%
} CurrentWeather;

typedef struct {
  int              temp;
  WeatherCondition condition;
  int              hour_offset;   // 0, 2, 4, 6, 8, 10
  int              precip_chance; // 0-100%
} HourlyWeather;

typedef struct {
  int              hi;
  int              lo;
  WeatherCondition condition;
  int              precip_chance;
} DailyWeather;

typedef struct {
  bool           valid;
  CurrentWeather current;
  HourlyWeather  hourly[HOURLY_SLOTS];
  DailyWeather   daily[DAILY_SLOTS];
  // sun times (unix timestamps)
  time_t         sunrise;
  time_t         sunset;
} WeatherData;

extern WeatherData g_weather;

void weather_handle_inbox(DictionaryIterator *iter);
