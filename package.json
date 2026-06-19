#include <pebble.h>
#include "main.h"
#include "weather.h"
#include "tiles.h"
#include "config.h"

static Window *s_window;
static Layer  *s_top_bar_layer;
static Layer  *s_bottom_bar_layer;
static Layer  *s_time_layer;
static Layer  *s_tile_layer;

static GFont   s_font_large;
static GFont   s_font_med;
static GFont   s_font_sm;

static AppTimer *s_weather_timer;
static char s_time_buf[8];

// ── Color helpers ─────────────────────────────────────────────────────────────
static GColor cfg_fg()     { return px_to_gcolor(g_config.color_fg); }
static GColor cfg_bg()     { return px_to_gcolor(g_config.color_bg); }
static GColor cfg_border() { return px_to_gcolor(g_config.color_border); }
static GColor cfg_accent() { return px_to_gcolor(g_config.color_accent); }

// ── Progress bar: 28 individual segments, no border, each fills independently
static void draw_seg_bar(GContext *ctx, int x, int y, int w, int h, int pct, GColor fill_col) {
  int n = 28, gap = 1;
  int sw = (w - (n-1)*gap) / n;
  int filled = (n * pct) / 100;
  for (int i=0; i<n; i++) {
    int sx = x + i*(sw+gap);
    GColor col = (i < filled) ? fill_col : GColorDarkGray;
    graphics_context_set_fill_color(ctx, col);
    graphics_fill_rect(ctx, GRect(sx, y, sw, h), 0, GCornerNone);
  }
}

// Build side-label strings for a bar type
static void bar_labels(BarContent bc, int pct, char *lbuf, int ll, char *rbuf, int rl) {
  lbuf[0]=rbuf[0]='\0';
  switch(bc) {
    case BAR_SUN:
      if (g_weather.valid && g_weather.sunrise) {
        struct tm *sr = localtime(&g_weather.sunrise);
        struct tm *ss = localtime(&g_weather.sunset);
        strftime(lbuf, ll, g_config.use_24h ? "%H:%M" : "%l:%M%p", sr);
        strftime(rbuf, rl, g_config.use_24h ? "%H:%M" : "%l:%M%p", ss);
      } else { snprintf(lbuf,ll,"SUN"); }
      break;
    case BAR_STEPS:    snprintf(lbuf,ll,"STEPS"); snprintf(rbuf,rl,"%d%%",pct); break;
    case BAR_CALORIES: snprintf(lbuf,ll,"CAL");   snprintf(rbuf,rl,"%d%%",pct); break;
    case BAR_BATTERY:  snprintf(lbuf,ll,"BAT");   snprintf(rbuf,rl,"%d%%",pct); break;
    default: break;
  }
}

static int compute_bar_pct(BarContent bc) {
  switch(bc) {
    case BAR_SUN: {
      if (!g_weather.valid || g_weather.sunrise==0) return 50;
      time_t now = time(NULL);
      time_t sr  = g_weather.sunrise;
      time_t ss  = g_weather.sunset;
      if (now < sr) return 0;
      if (now > ss) return 100;
      return (int)((now - sr) * 100 / (ss - sr));
    }
    case BAR_STEPS: {
#if defined(PBL_HEALTH)
      HealthMetric m = HealthMetricStepCount;
      HealthServiceAccessibilityMask ok =
        health_service_metric_accessible(m, time_start_of_today(), time(NULL));
      if (ok & HealthServiceAccessibilityMaskAvailable) {
        int steps = (int)health_service_sum_today(m);
        int goal  = g_config.step_goal > 0 ? g_config.step_goal : 10000;
        int pct   = steps * 100 / goal;
        return pct > 100 ? 100 : pct;
      }
#endif
      return 0;
    }
    case BAR_CALORIES: {
#if defined(PBL_HEALTH)
      HealthMetric m = HealthMetricActiveKCalories;
      HealthServiceAccessibilityMask ok =
        health_service_metric_accessible(m, time_start_of_today(), time(NULL));
      if (ok & HealthServiceAccessibilityMaskAvailable) {
        int cal  = (int)health_service_sum_today(m);
        int goal = g_config.cal_goal > 0 ? g_config.cal_goal : 500;
        int pct  = cal * 100 / goal;
        return pct > 100 ? 100 : pct;
      }
#endif
      return 0;
    }
    case BAR_BATTERY: {
      return battery_state_service_peek().charge_percent;
    }
    default: return 0;
  }
}

// ── Top bar ──────────────────────────────────────────────────────────────────
static void top_bar_update_proc(Layer *layer, GContext *ctx) {
  GRect b = layer_get_bounds(layer);
  graphics_context_set_fill_color(ctx, cfg_border());
  graphics_fill_rect(ctx, b, 0, GCornerNone);
  graphics_context_set_stroke_color(ctx, cfg_accent());
  graphics_draw_line(ctx, GPoint(0, b.size.h-1), GPoint(b.size.w-1, b.size.h-1));

  BarContent bc = g_config.top_bar_progress;
  bool has_bar = (bc != BAR_NONE);
  int text_y = 1, text_h = 11;

  if (!has_bar) {
    // No bar: show date left + battery right across full width
    time_t now=time(NULL); struct tm *t=localtime(&now);
    char dbuf[14]; strftime(dbuf,sizeof(dbuf),g_config.use_24h?"%a %d %b":"%a %b %d",t);
    graphics_context_set_text_color(ctx, cfg_fg());
    graphics_draw_text(ctx,dbuf,s_font_sm,GRect(3,text_y,120,text_h),GTextOverflowModeWordWrap,GTextAlignmentLeft,NULL);
    char bbuf[6]; snprintf(bbuf,sizeof(bbuf),"%d%%",battery_state_service_peek().charge_percent);
    graphics_draw_text(ctx,bbuf,s_font_sm,GRect(b.size.w-34,text_y,30,text_h),GTextOverflowModeWordWrap,GTextAlignmentRight,NULL);
  } else {
    // Bar mode: left-label ─── segments ─── right-label, date/bat squeezed to ends
    int pct = compute_bar_pct(bc);
    char lbuf[10]="", rbuf[10]="";
    bar_labels(bc, pct, lbuf, sizeof(lbuf), rbuf, sizeof(rbuf));
    int lw=38, rw=28, gap=2, bh=5;
    int bx = lw+gap, bw = b.size.w-lw-rw-gap*2;
    int by = (b.size.h-bh)/2 + 1;
    graphics_context_set_text_color(ctx, cfg_fg());
    graphics_draw_text(ctx,lbuf,s_font_sm,GRect(2,text_y,lw,text_h),GTextOverflowModeWordWrap,GTextAlignmentLeft,NULL);
    graphics_context_set_text_color(ctx, cfg_accent());
    graphics_draw_text(ctx,rbuf,s_font_sm,GRect(b.size.w-rw-2,text_y,rw,text_h),GTextOverflowModeWordWrap,GTextAlignmentRight,NULL);
    draw_seg_bar(ctx, bx, by, bw, bh, pct, cfg_accent());
  }
}

// ── Bottom bar ───────────────────────────────────────────────────────────────
static void bottom_bar_update_proc(Layer *layer, GContext *ctx) {
  GRect b = layer_get_bounds(layer);
  graphics_context_set_fill_color(ctx, cfg_border());
  graphics_fill_rect(ctx, b, 0, GCornerNone);
  graphics_context_set_stroke_color(ctx, cfg_accent());
  graphics_draw_line(ctx, GPoint(0, 0), GPoint(b.size.w-1, 0));

  bool connected = connection_service_peek_pebble_app_connection();
  BarContent bc = g_config.bot_bar_progress;
  bool has_bar = (bc != BAR_NONE);
  int text_y = 2, text_h = 11;

  // BT dot always far left
  graphics_context_set_fill_color(ctx, connected ? GColorGreen : GColorRed);
  graphics_fill_rect(ctx, GRect(2, text_y+3, 4, 4), 0, GCornerNone);

  if (!has_bar) {
#if defined(PBL_HEALTH)
    HealthMetric m = HealthMetricStepCount;
    HealthServiceAccessibilityMask ok = health_service_metric_accessible(m, time_start_of_today(), time(NULL));
    if (ok & HealthServiceAccessibilityMaskAvailable) {
      char sbuf[18]; snprintf(sbuf,sizeof(sbuf),"%d steps",(int)health_service_sum_today(m));
      graphics_context_set_text_color(ctx, cfg_fg());
      graphics_draw_text(ctx,sbuf,s_font_sm,GRect(10,text_y,b.size.w-14,text_h),GTextOverflowModeWordWrap,GTextAlignmentCenter,NULL);
    }
#endif
  } else {
    int pct = compute_bar_pct(bc);
    char lbuf[10]="", rbuf[10]="";
    bar_labels(bc, pct, lbuf, sizeof(lbuf), rbuf, sizeof(rbuf));
    int lw=38, rw=28, gap=2, bh=5;
    int bx = 8+lw+gap, bw = b.size.w-8-lw-rw-gap*2;
    int by = (b.size.h-bh)/2;
    graphics_context_set_text_color(ctx, cfg_fg());
    graphics_draw_text(ctx,lbuf,s_font_sm,GRect(8,text_y,lw,text_h),GTextOverflowModeWordWrap,GTextAlignmentLeft,NULL);
    graphics_context_set_text_color(ctx, cfg_accent());
    graphics_draw_text(ctx,rbuf,s_font_sm,GRect(b.size.w-rw-2,text_y,rw,text_h),GTextOverflowModeWordWrap,GTextAlignmentRight,NULL);
    draw_seg_bar(ctx, bx, by, bw, bh, pct, cfg_accent());
  }
}

// ── Time layer ────────────────────────────────────────────────────────────────
static char s_date_buf[20];

static void time_layer_update_proc(Layer *layer, GContext *ctx) {
  GRect b = layer_get_bounds(layer);
  graphics_context_set_fill_color(ctx, cfg_bg());
  graphics_fill_rect(ctx, b, 0, GCornerNone);
  graphics_context_set_stroke_color(ctx, cfg_border());
  graphics_draw_line(ctx, GPoint(0,0), GPoint(b.size.w,0));
  graphics_draw_line(ctx, GPoint(0,b.size.h-1), GPoint(b.size.w,b.size.h-1));

  // Time + date stacked, vertically centred together
  // Time ~32px tall, date ~9px, gap 2px → total ~43
  int total_h = 36 + 2 + 9;
  int time_y = (b.size.h - total_h) / 2;
  int date_y = time_y + 36 + 2;

  graphics_context_set_text_color(ctx, cfg_fg());
  graphics_draw_text(ctx, s_time_buf, s_font_large,
    GRect(0, time_y, b.size.w, 38), GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);

  graphics_context_set_text_color(ctx, cfg_accent());
  graphics_draw_text(ctx, s_date_buf, s_font_sm,
    GRect(0, date_y, b.size.w, 10), GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
}

static void update_time(struct tm *t) {
  strftime(s_time_buf, sizeof(s_time_buf), g_config.use_24h ? "%H:%M" : "%I:%M", t);
  strftime(s_date_buf, sizeof(s_date_buf), "%A · %b %d", t);
  layer_mark_dirty(s_time_layer);
}

// ── Window lifecycle ──────────────────────────────────────────────────────────
static void window_load(Window *window) {
  Layer *root = window_get_root_layer(window);

  s_font_large = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_48));
  s_font_med   = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_20));
  s_font_sm    = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_14));

  s_top_bar_layer = layer_create(GRect(0, 0, SCREEN_W, BAR_H));
  layer_set_update_proc(s_top_bar_layer, top_bar_update_proc);
  layer_add_child(root, s_top_bar_layer);

  s_time_layer = layer_create(GRect(0, BAR_H, SCREEN_W, TIME_H));
  layer_set_update_proc(s_time_layer, time_layer_update_proc);
  layer_add_child(root, s_time_layer);

  s_tile_layer = layer_create(GRect(0, BAR_H+TIME_H, SCREEN_W, TILE_AREA_H));
  tiles_init(s_tile_layer, s_font_large, s_font_med, s_font_sm);
  layer_add_child(root, s_tile_layer);

  s_bottom_bar_layer = layer_create(GRect(0, SCREEN_H-BAR_H, SCREEN_W, BAR_H));
  layer_set_update_proc(s_bottom_bar_layer, bottom_bar_update_proc);
  layer_add_child(root, s_bottom_bar_layer);

  time_t now=time(NULL);
  update_time(localtime(&now));
}

static void window_unload(Window *window) {
  fonts_unload_custom_font(s_font_large);
  fonts_unload_custom_font(s_font_med);
  fonts_unload_custom_font(s_font_sm);
  tiles_deinit();
  layer_destroy(s_top_bar_layer);
  layer_destroy(s_time_layer);
  layer_destroy(s_tile_layer);
  layer_destroy(s_bottom_bar_layer);
}

// ── Event handlers ────────────────────────────────────────────────────────────
static void tick_handler(struct tm *t, TimeUnits u) {
  update_time(t);
  layer_mark_dirty(s_bottom_bar_layer);
  layer_mark_dirty(s_top_bar_layer);
  // refresh health tile each minute
  tiles_refresh();
}

static void battery_handler(BatteryChargeState s)  { layer_mark_dirty(s_top_bar_layer); }
static void connection_handler(bool c)              { layer_mark_dirty(s_bottom_bar_layer); vibes_short_pulse(); }

static void request_weather(void *data) {
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);
  dict_write_uint8(iter, MESSAGE_KEY_FETCH_WEATHER, 1);
  app_message_outbox_send();
  s_weather_timer = app_timer_register(30*60*1000, request_weather, NULL);
}

static void inbox_received_handler(DictionaryIterator *iter, void *ctx) {
  Tuple *t;
  #define CFG_INT(key, field) t=dict_find(iter,key); if(t){g_config.field=(typeof(g_config.field))t->value->int32; config_save();}
  CFG_INT(MESSAGE_KEY_USE_24H,       use_24h)
  CFG_INT(MESSAGE_KEY_TEMP_UNIT,     temp_unit)
  CFG_INT(MESSAGE_KEY_TILE0,         tile[0])
  CFG_INT(MESSAGE_KEY_TILE1,         tile[1])
  CFG_INT(MESSAGE_KEY_TILE2,         tile[2])
  CFG_INT(MESSAGE_KEY_TILE3,         tile[3])
  CFG_INT(MESSAGE_KEY_HOURLY_NOW,    hourly_show_current_first)
  CFG_INT(MESSAGE_KEY_HEALTH_SLOT_A, health_slot_a)
  CFG_INT(MESSAGE_KEY_HEALTH_SLOT_B, health_slot_b)
  CFG_INT(MESSAGE_KEY_HEALTH_SLOT_C, health_slot_c)
  CFG_INT(MESSAGE_KEY_STEP_GOAL,     step_goal)
  CFG_INT(MESSAGE_KEY_CAL_GOAL,      cal_goal)
  CFG_INT(MESSAGE_KEY_TOP_BAR,       top_bar_progress)
  CFG_INT(MESSAGE_KEY_BOT_BAR,       bot_bar_progress)
  CFG_INT(MESSAGE_KEY_COLOR_BG,      color_bg)
  CFG_INT(MESSAGE_KEY_COLOR_BORDER,  color_border)
  CFG_INT(MESSAGE_KEY_COLOR_FG,      color_fg)
  CFG_INT(MESSAGE_KEY_COLOR_ACCENT,  color_accent)
  #undef CFG_INT

  weather_handle_inbox(iter);
  tiles_refresh();
  layer_mark_dirty(s_time_layer);
  layer_mark_dirty(s_top_bar_layer);
  layer_mark_dirty(s_bottom_bar_layer);
}

// ── Init / Deinit ─────────────────────────────────────────────────────────────
static void init(void) {
  config_load();
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  window_set_window_handlers(s_window, (WindowHandlers){
    .load=window_load, .unload=window_unload });
  window_stack_push(s_window, true);
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  battery_state_service_subscribe(battery_handler);
  connection_service_subscribe((ConnectionHandlers){
    .pebble_app_connection_handler=connection_handler });
  app_message_register_inbox_received(inbox_received_handler);
  app_message_open(768, 64);
  s_weather_timer = app_timer_register(2000, request_weather, NULL);
}

static void deinit(void) {
  if(s_weather_timer) app_timer_cancel(s_weather_timer);
  tick_timer_service_unsubscribe();
  battery_state_service_unsubscribe();
  connection_service_unsubscribe();
  window_destroy(s_window);
}

int main(void) { init(); app_event_loop(); deinit(); return 0; }
