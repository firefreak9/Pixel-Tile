#include "tiles.h"
#include "weather.h"
#include "config.h"
#include "main.h"

static GFont s_font_lg;   // 20px  — big numbers
static GFont s_font_md;   // 14px  — medium labels/values
static GFont s_font_sm;   // 9px   — small labels, col headers
static Layer *s_tile_layer;

static GColor FG()  { return px_to_gcolor(g_config.color_fg); }
static GColor BG()  { return px_to_gcolor(g_config.color_bg); }
static GColor BDR() { return px_to_gcolor(g_config.color_border); }
static GColor ACC() { return px_to_gcolor(g_config.color_accent); }

// ─── Notch-corner tile (5px square cut from each corner) ─────────────────────
#define NOTCH 5

static void draw_tile_bg(GContext *ctx, GRect r) {
  int x=r.origin.x, y=r.origin.y, w=r.size.w, h=r.size.h;
  int n=NOTCH;
  GColor bg=BG(), bdr=BDR();

  // Fill main body (cross: horizontal slab + vertical slab)
  graphics_context_set_fill_color(ctx, bg);
  graphics_fill_rect(ctx, GRect(x+n, y,   w-n*2, h), 0, GCornerNone); // vertical strip
  graphics_fill_rect(ctx, GRect(x,   y+n, w,     h-n*2), 0, GCornerNone); // horizontal strip

  // Black out the actual corner squares (creates the notch)
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_rect(ctx, GRect(x,     y,     n, n), 0, GCornerNone); // TL
  graphics_fill_rect(ctx, GRect(x+w-n, y,     n, n), 0, GCornerNone); // TR
  graphics_fill_rect(ctx, GRect(x,     y+h-n, n, n), 0, GCornerNone); // BL
  graphics_fill_rect(ctx, GRect(x+w-n, y+h-n, n, n), 0, GCornerNone); // BR

  // Border lines — stop at notch
  graphics_context_set_stroke_color(ctx, bdr);
  graphics_context_set_stroke_width(ctx, 2);
  graphics_draw_line(ctx, GPoint(x+n,   y),     GPoint(x+w-n,   y));     // top
  graphics_draw_line(ctx, GPoint(x+n,   y+h-1), GPoint(x+w-n,   y+h-1));// bottom
  graphics_draw_line(ctx, GPoint(x,     y+n),   GPoint(x,       y+h-n));  // left
  graphics_draw_line(ctx, GPoint(x+w-1, y+n),   GPoint(x+w-1,   y+h-n)); // right
  graphics_context_set_stroke_width(ctx, 1);
}

static GRect tile_inner(GRect r) {
  int pad = NOTCH + 2;
  return GRect(r.origin.x+pad, r.origin.y+pad, r.size.w-pad*2, r.size.h-pad*2);
}

// ─── Shared helpers ───────────────────────────────────────────────────────────
static void fmt_temp(char *b, int len, int tf) {
  if(g_config.temp_unit==UNIT_C) snprintf(b,len,"%dC",(tf-32)*5/9);
  else snprintf(b,len,"%dF",tf);
}

static void txt(GContext *ctx, const char *s, GFont f, GRect r, GColor c, GTextAlignment a) {
  graphics_context_set_text_color(ctx, c);
  graphics_draw_text(ctx, s, f, r, GTextOverflowModeWordWrap, a, NULL);
}

// Centered text with known height; returns y after text
static void txt_center(GContext *ctx, const char *s, GFont f, int x, int y, int w, GColor c) {
  GSize sz = graphics_text_layout_get_content_size(s, f, GRect(0,0,w,100), GTextOverflowModeWordWrap, GTextAlignmentCenter);
  txt(ctx, s, f, GRect(x, y, w, sz.h+2), c, GTextAlignmentCenter);
}

static void divider_h(GContext *ctx, int x, int y, int w) {
  graphics_context_set_stroke_color(ctx, BDR());
  graphics_draw_line(ctx, GPoint(x,y), GPoint(x+w,y));
}
static void divider_v(GContext *ctx, int x, int y, int h) {
  graphics_context_set_stroke_color(ctx, BDR());
  graphics_draw_line(ctx, GPoint(x,y), GPoint(x,y+h));
}

// ─── Pixel-art weather icons (procedural) ────────────────────────────────────
static void px_fill(GContext *ctx,int x,int y,GColor c){graphics_context_set_fill_color(ctx,c);graphics_fill_rect(ctx,GRect(x,y,1,1),0,GCornerNone);}
static void circ(GContext *ctx,int cx,int cy,int r,GColor c){for(int dy=-r;dy<=r;dy++)for(int dx=-r;dx<=r;dx++)if(dx*dx+dy*dy<=r*r)px_fill(ctx,cx+dx,cy+dy,c);}

static void draw_icon(GContext *ctx, WeatherCondition cond, int ox, int oy, int size) {
  // Icons drawn in a ~18×18 space, then we offset by ox,oy
  // size param unused here but reserved for scaling future
  GColor f=FG(), a=ACC();
  switch(cond){
    case COND_CLEAR_DAY:
      circ(ctx,ox+9,oy+9,5,f);
      for(int i=0;i<8;i++){float ang=i*3.14159f/4;int rx=(int)(9+8*0.866f*(i%2==0?1:0.707f));int ry=(int)(9+8*0.866f*(i%2==0?1:0.707f));(void)rx;(void)ry;}
      // simpler rays: 4 cardinal + 4 diagonal
      for(int d=0;d<4;d++){int dx[]={0,1,0,-1},dy[]={-1,0,1,0};for(int s=6;s<=8;s++)px_fill(ctx,ox+9+dx[d]*s,oy+9+dy[d]*s,f);}
      for(int d=0;d<4;d++){int dx[]={1,1,-1,-1},dy[]={-1,1,1,-1};for(int s=5;s<=6;s++)px_fill(ctx,ox+9+dx[d]*s,oy+9+dy[d]*s,f);}
      break;
    case COND_CLEAR_NIGHT:
      for(int dy=-6;dy<=6;dy++)for(int dx=-6;dx<=6;dx++){if(dx*dx+dy*dy>36)continue;if((dx-3)*(dx-3)+(dy+2)*(dy+2)>25)px_fill(ctx,ox+8+dx,oy+8+dy,f);}
      break;
    case COND_PARTLY_CLOUDY:
      circ(ctx,ox+6,oy+6,4,a);
      for(int d=0;d<4;d++){int ddx[]={0,1,0,-1},ddy[]={-1,0,1,0};for(int s=5;s<=6;s++)px_fill(ctx,ox+6+ddx[d]*s,oy+6+ddy[d]*s,a);}
      circ(ctx,ox+5,oy+12,3,f);circ(ctx,ox+9,oy+10,4,f);circ(ctx,ox+13,oy+12,3,f);
      graphics_context_set_fill_color(ctx,f);graphics_fill_rect(ctx,GRect(ox+3,oy+12,12,5),0,GCornerNone);
      break;
    case COND_CLOUDY:
      circ(ctx,ox+5,oy+11,3,GColorDarkGray);circ(ctx,ox+9,oy+9,4,GColorDarkGray);circ(ctx,ox+13,oy+11,3,GColorDarkGray);
      graphics_context_set_fill_color(ctx,GColorDarkGray);graphics_fill_rect(ctx,GRect(ox+3,oy+11,12,5),0,GCornerNone);
      circ(ctx,ox+5,oy+9,3,f);circ(ctx,ox+9,oy+7,4,f);circ(ctx,ox+13,oy+9,3,f);
      graphics_context_set_fill_color(ctx,f);graphics_fill_rect(ctx,GRect(ox+3,oy+9,12,5),0,GCornerNone);
      break;
    case COND_DRIZZLE:
    case COND_RAIN:{
      circ(ctx,ox+5,oy+7,3,f);circ(ctx,ox+9,oy+5,4,f);circ(ctx,ox+13,oy+7,3,f);
      graphics_context_set_fill_color(ctx,f);graphics_fill_rect(ctx,GRect(ox+3,oy+7,12,5),0,GCornerNone);
      int drops=cond==COND_DRIZZLE?3:5; int xs[]={4,7,10,13,6};
      for(int i=0;i<drops;i++)for(int dy=0;dy<4;dy++)px_fill(ctx,ox+xs[i],oy+13+dy,GColorBlueMoon);
      break;}
    case COND_SNOW:{
      circ(ctx,ox+5,oy+7,3,f);circ(ctx,ox+9,oy+5,4,f);circ(ctx,ox+13,oy+7,3,f);
      graphics_context_set_fill_color(ctx,f);graphics_fill_rect(ctx,GRect(ox+3,oy+7,12,5),0,GCornerNone);
      int xs[]={3,8,13,6,11}; for(int i=0;i<4;i++){graphics_context_set_fill_color(ctx,GColorCeleste);graphics_fill_rect(ctx,GRect(ox+xs[i],oy+13,3,3),0,GCornerNone);}
      break;}
    case COND_THUNDERSTORM:{
      circ(ctx,ox+5,oy+7,3,GColorDarkGray);circ(ctx,ox+9,oy+5,4,GColorDarkGray);circ(ctx,ox+13,oy+7,3,GColorDarkGray);
      graphics_context_set_fill_color(ctx,GColorDarkGray);graphics_fill_rect(ctx,GRect(ox+3,oy+7,12,5),0,GCornerNone);
      // bolt
      int bx=ox+7,by=oy+12;
      GColor y=GColorYellow;
      int bp[][2]={{2,0},{1,1},{2,1},{0,2},{1,2},{1,3},{2,3},{0,4},{1,4}};
      for(int i=0;i<9;i++)px_fill(ctx,bx+bp[i][0],by+bp[i][1],y);
      break;}
    case COND_FOGGY:
      for(int row=0;row<5;row++){graphics_context_set_fill_color(ctx,f);graphics_fill_rect(ctx,GRect(ox+row%2*2,oy+2+row*3,16-row*2,2),0,GCornerNone);}
      break;
    case COND_SLEET:{
      circ(ctx,ox+5,oy+7,3,f);circ(ctx,ox+9,oy+5,4,f);circ(ctx,ox+13,oy+7,3,f);
      graphics_context_set_fill_color(ctx,f);graphics_fill_rect(ctx,GRect(ox+3,oy+7,12,5),0,GCornerNone);
      for(int dy=0;dy<4;dy++){px_fill(ctx,ox+4,oy+13+dy,GColorBlueMoon);px_fill(ctx,ox+10,oy+13+dy,GColorBlueMoon);}
      graphics_context_set_fill_color(ctx,GColorCeleste);graphics_fill_rect(ctx,GRect(ox+7,oy+14,3,3),0,GCornerNone);
      break;}
    case COND_WINDY:
      for(int row=0;row<5;row++){graphics_context_set_fill_color(ctx,f);graphics_fill_rect(ctx,GRect(ox,oy+1+row*4,14+row%2*3,2),0,GCornerNone);}
      break;
    default:
      txt(ctx,"?",fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD),GRect(ox+4,oy+2,14,16),f,GTextAlignmentLeft);
  }
}

// ─────────────────────────────────────────────────────────────────────────────
//  TILE 1: Current Weather — full layout using space-evenly
// ─────────────────────────────────────────────────────────────────────────────
static void draw_tile_weather_now(GContext *ctx, GRect r) {
  GRect in = tile_inner(r);
  if(!g_weather.valid){txt(ctx,"...",s_font_sm,in,FG(),GTextAlignmentCenter);return;}
  CurrentWeather *cw = &g_weather.current;

  int x=in.origin.x, y=in.origin.y, w=in.size.w, h=in.size.h;

  // Top half: icon left + big temp right + hi/lo stacked
  int top_h = h * 11 / 20;
  draw_icon(ctx, cw->condition, x, y+2, 18);

  char tbuf[8]; fmt_temp(tbuf,sizeof(tbuf),cw->temp);
  txt(ctx, tbuf, s_font_lg, GRect(x+20,y,w-20,top_h), FG(), GTextAlignmentLeft);

  char hibuf[7],lobuf[7];
  fmt_temp(hibuf,sizeof(hibuf),cw->hi); fmt_temp(lobuf,sizeof(lobuf),cw->lo);
  txt(ctx, hibuf, s_font_sm, GRect(x+20, y+16, w-20, 12), ACC(), GTextAlignmentLeft);
  txt(ctx, lobuf, s_font_sm, GRect(x+20, y+26, w-20, 12), GColorBlueMoon, GTextAlignmentLeft);

  // Divider
  int div_y = y + top_h + 1;
  divider_h(ctx, x, div_y, w);

  // Bottom row: UV | HUM | FEELS — evenly split
  int bot_y = div_y + 3;
  int bot_h = y + h - bot_y;
  int col_w = w / 3;
  const char *labels[] = {"UV","HUM","FEEL"};
  char vals[3][8];
  snprintf(vals[0],8,"%d",cw->uv_index);
  snprintf(vals[1],8,"%d%%",cw->humidity);
  // feels-like: simple wind chill approximation just for display
  int feels = cw->temp - (g_config.temp_unit==UNIT_C ? 1 : 2);
  fmt_temp(vals[2],8,feels);

  for(int i=0;i<3;i++){
    int cx = x + i*col_w;
    if(i>0) divider_v(ctx, cx, bot_y, bot_h);
    txt(ctx, labels[i], s_font_sm, GRect(cx+1,bot_y,col_w-2,10), ACC(), GTextAlignmentCenter);
    txt(ctx, vals[i],   s_font_sm, GRect(cx+1,bot_y+12,col_w-2,12), FG(), GTextAlignmentCenter);
  }
}

// ─────────────────────────────────────────────────────────────────────────────
//  TILE 2: Hourly — 3 columns, icon centred, all rows evenly spaced
// ─────────────────────────────────────────────────────────────────────────────
static void draw_tile_weather_hourly(GContext *ctx, GRect r) {
  GRect in = tile_inner(r);
  if(!g_weather.valid){txt(ctx,"...",s_font_sm,in,FG(),GTextAlignmentCenter);return;}

  int x=in.origin.x, y=in.origin.y, w=in.size.w, h=in.size.h;
  int cw = w/3;
  int slots[3] = {0,2,4};
  if(!g_config.hourly_show_current_first){slots[0]=1;slots[1]=2;slots[2]=3;}

  // Row heights: label(10) + icon(18) + temp(12) + precip(10) = 50  → distribute remaining evenly
  int row_gap = (h - 50) / 4;  // 4 gaps around 4 rows

  for(int c=0;c<3;c++){
    HourlyWeather *hw = &g_weather.hourly[slots[c]];
    int cx = x + c*cw;
    if(c>0) divider_v(ctx, cx, y+2, h-4);

    time_t now=time(NULL); struct tm *t=localtime(&now);
    int hour=(t->tm_hour+hw->hour_offset)%24;
    char hbuf[7];
    if(g_config.hourly_show_current_first&&c==0) snprintf(hbuf,sizeof(hbuf),"NOW");
    else if(g_config.use_24h) snprintf(hbuf,sizeof(hbuf),"%02d",hour);
    else snprintf(hbuf,sizeof(hbuf),"%d%s",hour%12==0?12:hour%12,hour<12?"a":"p");

    int ry = y + row_gap;
    txt(ctx, hbuf, s_font_sm, GRect(cx+1,ry,cw-2,10), ACC(), GTextAlignmentCenter);
    ry += 10 + row_gap;
    draw_icon(ctx, hw->condition, cx+(cw-16)/2, ry, 16);
    ry += 18 + row_gap;
    char tbuf[8]; fmt_temp(tbuf,sizeof(tbuf),hw->temp);
    txt(ctx, tbuf, s_font_sm, GRect(cx+1,ry,cw-2,12), FG(), GTextAlignmentCenter);
    ry += 12 + row_gap;
    if(hw->precip_chance>0){char pbuf[6];snprintf(pbuf,sizeof(pbuf),"%d%%",hw->precip_chance);txt(ctx,pbuf,s_font_sm,GRect(cx+1,ry,cw-2,10),GColorBlueMoon,GTextAlignmentCenter);}
  }
}

// ─────────────────────────────────────────────────────────────────────────────
//  TILE 3: 3-day — 3 columns, 5 rows each (day/icon/hi/lo/precip)
// ─────────────────────────────────────────────────────────────────────────────
static void draw_tile_weather_daily(GContext *ctx, GRect r) {
  GRect in = tile_inner(r);
  if(!g_weather.valid){txt(ctx,"...",s_font_sm,in,FG(),GTextAlignmentCenter);return;}

  int x=in.origin.x, y=in.origin.y, w=in.size.w, h=in.size.h;
  int cw=w/3;
  time_t now=time(NULL);
  char dy1[4],dy2[4];
  time_t t1=now+86400,t2=now+172800;
  strftime(dy1,sizeof(dy1),"%a",localtime(&t1));
  strftime(dy2,sizeof(dy2),"%a",localtime(&t2));
  const char *labels[]={"NOW",dy1,dy2};

  // 5 content items: label(8)+icon(18)+hi(10)+lo(10)+precip(8) = 54; rest = gaps
  int total_content = 8+18+10+10+8;
  int gap = (h - total_content) / 5;

  for(int c=0;c<3;c++){
    DailyWeather *dw=&g_weather.daily[c];
    int cx=x+c*cw;
    if(c>0) divider_v(ctx,cx,y+2,h-4);

    int ry=y+gap;
    txt(ctx,labels[c],s_font_sm,GRect(cx+1,ry,cw-2,8),ACC(),GTextAlignmentCenter);
    ry+=8+gap;
    draw_icon(ctx,dw->condition,cx+(cw-16)/2,ry,16);
    ry+=18+gap;
    char hibuf[7]; fmt_temp(hibuf,sizeof(hibuf),dw->hi);
    txt(ctx,hibuf,s_font_sm,GRect(cx+1,ry,cw-2,10),FG(),GTextAlignmentCenter);
    ry+=10+gap;
    char lobuf[7]; fmt_temp(lobuf,sizeof(lobuf),dw->lo);
    txt(ctx,lobuf,s_font_sm,GRect(cx+1,ry,cw-2,10),GColorBlueMoon,GTextAlignmentCenter);
    ry+=10+gap;
    if(dw->precip_chance>0){char pbuf[6];snprintf(pbuf,sizeof(pbuf),"%d%%",dw->precip_chance);txt(ctx,pbuf,s_font_sm,GRect(cx+1,ry,cw-2,8),GColorBabyBlueEyes,GTextAlignmentCenter);}
  }
}

// ─────────────────────────────────────────────────────────────────────────────
//  TILE 4: Date
// ─────────────────────────────────────────────────────────────────────────────
static void draw_tile_date(GContext *ctx, GRect r) {
  GRect in=tile_inner(r);
  int x=in.origin.x,y=in.origin.y,w=in.size.w,h=in.size.h;
  time_t now=time(NULL); struct tm *t=localtime(&now);
  char wday[10],mday[4],mon[8],yr[6];
  strftime(wday,sizeof(wday),"%A",t);
  strftime(mday,sizeof(mday),"%d",t);
  strftime(mon,sizeof(mon),"%B",t);
  strftime(yr,sizeof(yr),"%Y",t);
  // Distribute: day-name / big date number / month / year
  int gap=(h-8-24-10-8)/4;
  int ry=y+gap;
  txt(ctx,wday,s_font_sm,GRect(x,ry,w,8),ACC(),GTextAlignmentCenter); ry+=8+gap;
  txt(ctx,mday,s_font_lg,GRect(x,ry,w,24),FG(),GTextAlignmentCenter); ry+=24+gap;
  txt(ctx,mon, s_font_sm,GRect(x,ry,w,10),FG(),GTextAlignmentCenter); ry+=10+gap;
  txt(ctx,yr,  s_font_sm,GRect(x,ry,w,8), ACC(),GTextAlignmentCenter);
}

// ─────────────────────────────────────────────────────────────────────────────
//  TILE 5: Health — fully customisable 3-slot layout
// ─────────────────────────────────────────────────────────────────────────────
#if defined(PBL_HEALTH)
static bool get_slot_data(HealthSlot slot, char *vbuf, int vlen, char *lbuf, int llen, bool *is_hr) {
  *is_hr = false;
  if(slot==HSLOT_NONE){snprintf(lbuf,llen,"");snprintf(vbuf,vlen,"");return false;}
  if(slot==HSLOT_HEART_RATE){
    *is_hr=true; snprintf(lbuf,llen,"HR");
    HealthMetric m=HealthMetricHeartRateBPM;
    HealthServiceAccessibilityMask ok=health_service_metric_accessible(m,time(NULL)-60,time(NULL));
    if(ok&HealthServiceAccessibilityMaskAvailable)snprintf(vbuf,vlen,"%d",(int)health_service_peek_current_value(m));
    else snprintf(vbuf,vlen,"--");
    return true;
  }
  if(slot==HSLOT_BATTERY){
    snprintf(lbuf,llen,"BAT"); snprintf(vbuf,vlen,"%d%%",battery_state_service_peek().charge_percent);
    return true;
  }
  HealthMetric m; const char *l;
  switch(slot){
    case HSLOT_STEPS:    m=HealthMetricStepCount;          l="STEPS"; break;
    case HSLOT_CALORIES: m=HealthMetricActiveKCalories;    l="CAL";   break;
    case HSLOT_DISTANCE: m=HealthMetricWalkedDistanceMeters; l="DIST"; break;
    case HSLOT_SLEEP:    m=HealthMetricSleepSeconds;       l="SLEEP"; break;
    default: snprintf(vbuf,vlen,"--"); return false;
  }
  snprintf(lbuf,llen,"%s",l);
  HealthServiceAccessibilityMask ok=health_service_metric_accessible(m,time_start_of_today(),time(NULL));
  if(ok&HealthServiceAccessibilityMaskAvailable){
    int v=(int)health_service_sum_today(m);
    if(slot==HSLOT_DISTANCE)snprintf(vbuf,vlen,"%dm",v);
    else if(slot==HSLOT_SLEEP)snprintf(vbuf,vlen,"%dh%dm",v/3600,(v%3600)/60);
    else snprintf(vbuf,vlen,"%d",v);
  } else snprintf(vbuf,vlen,"N/A");
  return true;
}
#endif

static void draw_slot(GContext *ctx, GRect r, HealthSlot slot) {
#if defined(PBL_HEALTH)
  char vbuf[16]="--",lbuf[8]="";
  bool is_hr=false;
  get_slot_data(slot,vbuf,sizeof(vbuf),lbuf,sizeof(lbuf),&is_hr);
  int x=r.origin.x,y=r.origin.y,w=r.size.w,h=r.size.h;
  if(is_hr){
    // HR: heart + big number + BPM label, all vertically centred
    int total=12+14+8, gap=(h-total)/3;
    int ry=y+gap;
    // pixel heart (7×6 px)
    int hx=x+(w-7)/2,hy=ry;
    int hp[][2]={{1,0},{2,0},{4,0},{5,0},{0,1},{1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{0,2},{1,2},{2,2},{3,2},{4,2},{5,2},{6,2},{1,3},{2,3},{3,3},{4,3},{5,3},{2,4},{3,4},{4,4},{3,5}};
    for(int i=0;i<27;i++){graphics_context_set_fill_color(ctx,GColorRed);graphics_fill_rect(ctx,GRect(hx+hp[i][0],hy+hp[i][1],1,1),0,GCornerNone);}
    ry+=12+gap;
    txt(ctx,vbuf,s_font_lg,GRect(x,ry,w,14),GColorRed,GTextAlignmentCenter);
    ry+=14+gap;
    txt(ctx,"BPM",s_font_sm,GRect(x,ry,w,8),FG(),GTextAlignmentCenter);
  } else {
    // Standard: label on top, value below, centred vertically
    int total=8+12, gap=(h-total)/3;
    int ry=y+gap;
    txt(ctx,lbuf,s_font_sm,GRect(x,ry,w,8),ACC(),GTextAlignmentCenter);
    ry+=8+gap;
    txt(ctx,vbuf,s_font_md,GRect(x,ry,w,12),FG(),GTextAlignmentCenter);
  }
#else
  txt(ctx,"N/A",s_font_sm,r,FG(),GTextAlignmentCenter);
#endif
}

static void draw_tile_health(GContext *ctx, GRect r) {
  GRect in=tile_inner(r);
  bool show_c=(g_config.health_slot_c!=HSLOT_NONE);
  int left_w=show_c ? in.size.w*56/100 : in.size.w;
  int right_w=in.size.w-left_w;
  int half_h=in.size.h/2;

  // Top-left slot
  GRect slot_a=GRect(in.origin.x,in.origin.y,left_w,half_h);
  divider_h(ctx,in.origin.x,in.origin.y+half_h,left_w);
  draw_slot(ctx,slot_a,g_config.health_slot_a);

  // Bottom-left slot
  GRect slot_b=GRect(in.origin.x,in.origin.y+half_h,left_w,half_h);
  draw_slot(ctx,slot_b,g_config.health_slot_b);

  // Right slot
  if(show_c){
    divider_v(ctx,in.origin.x+left_w,in.origin.y,in.size.h);
    GRect slot_c=GRect(in.origin.x+left_w+1,in.origin.y,right_w-1,in.size.h);
    draw_slot(ctx,slot_c,g_config.health_slot_c);
  }
}

// ─────────────────────────────────────────────────────────────────────────────
//  TILE 6: Battery
// ─────────────────────────────────────────────────────────────────────────────
static void draw_tile_battery(GContext *ctx, GRect r) {
  GRect in=tile_inner(r);
  int x=in.origin.x,y=in.origin.y,w=in.size.w,h=in.size.h;
  int pct=battery_state_service_peek().charge_percent;
  char buf[8]; snprintf(buf,sizeof(buf),"%d%%",pct);
  // Distribute: label / big% / bar
  int gap=(h-8-20-6)/3;
  int ry=y+gap;
  txt(ctx,"BATTERY",s_font_sm,GRect(x,ry,w,8),ACC(),GTextAlignmentCenter); ry+=8+gap;
  txt(ctx,buf,s_font_lg,GRect(x,ry,w,20),pct>20?ACC():GColorRed,GTextAlignmentCenter); ry+=20+gap;
  int fill=(w*pct)/100;
  graphics_context_set_fill_color(ctx,GColorDarkGray);
  graphics_fill_rect(ctx,GRect(x,ry,w,6),0,GCornerNone);
  graphics_context_set_fill_color(ctx,pct>20?ACC():GColorRed);
  graphics_fill_rect(ctx,GRect(x,ry,fill,6),0,GCornerNone);
}

// ─────────────────────────────────────────────────────────────────────────────
//  Main tile layer
// ─────────────────────────────────────────────────────────────────────────────
static void tile_layer_update_proc(Layer *layer, GContext *ctx) {
  GRect b=layer_get_bounds(layer);
  int tw=b.size.w/2,th=b.size.h/2;
  GRect rects[4]={GRect(0,0,tw,th),GRect(tw,0,tw,th),GRect(0,th,tw,th),GRect(tw,th,tw,th)};
  for(int i=0;i<4;i++){
    draw_tile_bg(ctx,rects[i]);
    switch(g_config.tile[i]){
      case TILE_WEATHER_NOW:    draw_tile_weather_now(ctx,rects[i]);    break;
      case TILE_WEATHER_HOURLY: draw_tile_weather_hourly(ctx,rects[i]); break;
      case TILE_WEATHER_DAILY:  draw_tile_weather_daily(ctx,rects[i]);  break;
      case TILE_DATE:           draw_tile_date(ctx,rects[i]);           break;
      case TILE_HEALTH:         draw_tile_health(ctx,rects[i]);         break;
      case TILE_BATTERY:        draw_tile_battery(ctx,rects[i]);        break;
      default: break;
    }
  }
}

void tiles_init(Layer *layer, GFont flg, GFont fmd, GFont fsm) {
  s_tile_layer=layer; s_font_lg=flg; s_font_md=fmd; s_font_sm=fsm;
  layer_set_update_proc(layer,tile_layer_update_proc);
}
void tiles_deinit(void){}
void tiles_refresh(void){if(s_tile_layer)layer_mark_dirty(s_tile_layer);}
