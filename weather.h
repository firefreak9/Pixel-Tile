// Pixel Tiles — phone-side JS
// Weather: Open-Meteo (open-meteo.com) — no API key required, CC BY 4.0
// Clay config bridge for settings page

var Clay  = require('pebble-clay');
var clayConfig = require('./config.json');
var clay = new Clay(clayConfig);

// ── Open-Meteo WMO weather code → internal WeatherCondition enum ─────────────
// WMO codes: https://open-meteo.com/en/docs#weathervariables
function wmoToCondition(code, isNight) {
  if (code === 0)                    return isNight ? 2 : 1;  // clear
  if (code <= 2)                     return 3;                 // mainly clear / partly cloudy
  if (code === 3)                    return 4;                 // overcast
  if (code >= 45 && code <= 48)      return 10;               // fog / rime fog
  if (code >= 51 && code <= 57)      return 6;                // drizzle
  if (code >= 61 && code <= 67)      return 5;                // rain
  if (code >= 71 && code <= 77)      return 7;                // snow
  if (code >= 80 && code <= 82)      return 5;                // rain showers
  if (code === 85 || code === 86)    return 7;                // snow showers
  if (code >= 95 && code <= 99)      return 9;                // thunderstorm
  return 0; // unknown
}

// ── Find the hourly index closest to "now + offsetHours" ─────────────────────
function findHourlyIndex(times, offsetHours) {
  var targetMs = Date.now() + offsetHours * 3600 * 1000;
  var best = 0, bestDiff = Infinity;
  for (var i = 0; i < times.length; i++) {
    var diff = Math.abs(new Date(times[i]).getTime() - targetMs);
    if (diff < bestDiff) { bestDiff = diff; best = i; }
  }
  return best;
}

// ── Convert Celsius to Fahrenheit if needed ───────────────────────────────────
function maybeF(c, useFahrenheit) {
  return useFahrenheit ? Math.round(c * 9 / 5 + 32) : Math.round(c);
}

// ── Main fetch ────────────────────────────────────────────────────────────────
function fetchWeather() {
  var useFahrenheit = localStorage.getItem('temp_unit') !== '1';

  navigator.geolocation.getCurrentPosition(function(pos) {
    var lat = pos.coords.latitude.toFixed(4);
    var lon = pos.coords.longitude.toFixed(4);

    // Single request gets everything — current, 6 hourly slots, 3 daily days
    // We always fetch in Celsius and convert ourselves so we can store one copy
    var url = 'https://api.open-meteo.com/v1/forecast' +
      '?latitude=' + lat +
      '&longitude=' + lon +
      '&current=temperature_2m,apparent_temperature,relative_humidity_2m,weathercode,uv_index' +
      '&hourly=temperature_2m,weathercode,precipitation_probability' +
      '&daily=temperature_2m_max,temperature_2m_min,weathercode,precipitation_probability_max,sunrise,sunset' +
      '&timezone=auto' +
      '&forecast_days=3';

    var xhr = new XMLHttpRequest();
    xhr.open('GET', url);
    xhr.onload = function() {
      if (xhr.status !== 200) {
        console.log('Open-Meteo error: ' + xhr.status);
        return;
      }
      try {
        parseAndSend(JSON.parse(xhr.responseText), useFahrenheit);
      } catch(e) {
        console.log('Parse error: ' + e);
      }
    };
    xhr.onerror = function() { console.log('Network error fetching weather'); };
    xhr.send();

  }, function(err) {
    console.log('Geolocation error: ' + err.message);
  }, { timeout: 15000 });
}

function parseAndSend(d, useFahrenheit) {
  var now      = d.current;
  var hourly   = d.hourly;
  var daily    = d.daily;
  var nowHour  = new Date().getHours();
  var isNight  = nowHour >= 20 || nowHour < 6;

  // ── Message dict ──────────────────────────────────────────────────────────
  var msg = {};

  // Current conditions (keys 30-37)
  msg[30] = maybeF(now.temperature_2m, useFahrenheit);
  msg[31] = wmoToCondition(now.weathercode, isNight);
  msg[32] = maybeF(daily.temperature_2m_max[0], useFahrenheit);  // today's hi
  msg[33] = maybeF(daily.temperature_2m_min[0], useFahrenheit);  // today's lo
  msg[34] = Math.round(now.uv_index || 0);
  msg[35] = Math.round(now.relative_humidity_2m || 0);

  // Sunrise / sunset as unix timestamps (daily gives ISO strings like "2025-06-18T05:47")
  msg[36] = daily.sunrise[0] ? Math.floor(new Date(daily.sunrise[0]).getTime() / 1000) : 0;
  msg[37] = daily.sunset[0]  ? Math.floor(new Date(daily.sunset[0]).getTime()  / 1000) : 0;

  // ── Hourly: 6 slots at +0h, +2h, +4h, +6h, +8h, +10h ─────────────────────
  // hourly.time is an array of ISO strings one per hour starting at midnight today
  var offsets = [0, 2, 4, 6, 8, 10];
  for (var s = 0; s < 6; s++) {
    var idx  = findHourlyIndex(hourly.time, offsets[s]);
    var base = 40 + s * 3;  // keys 40,41,42 / 43,44,45 / ...
    msg[base]     = maybeF(hourly.temperature_2m[idx], useFahrenheit);
    msg[base + 1] = wmoToCondition(hourly.weathercode[idx], false);
    msg[base + 2] = Math.round(hourly.precipitation_probability[idx] || 0);
  }

  // ── Daily: 3 days (today, tomorrow, day after) ─────────────────────────────
  for (var day = 0; day < 3; day++) {
    var dbase = 60 + day * 4;  // keys 60,61,62,63 / 64,65,66,67 / ...
    msg[dbase]     = maybeF(daily.temperature_2m_max[day], useFahrenheit);
    msg[dbase + 1] = maybeF(daily.temperature_2m_min[day], useFahrenheit);
    msg[dbase + 2] = wmoToCondition(daily.weathercode[day], false);
    msg[dbase + 3] = Math.round(daily.precipitation_probability_max[day] || 0);
  }

  Pebble.sendAppMessage(msg,
    function()    { console.log('Weather sent OK'); },
    function(err) { console.log('Weather send failed: ' + JSON.stringify(err)); }
  );
}

// ── Pebble events ─────────────────────────────────────────────────────────────
Pebble.addEventListener('ready', function() {
  console.log('PebbleKit JS ready — fetching weather via Open-Meteo');
  fetchWeather();
});

Pebble.addEventListener('appmessage', function(e) {
  // Watch requests a refresh (key 0)
  if (e.payload[0] === 1) fetchWeather();
});

Pebble.addEventListener('webviewclosed', function(e) {
  if (!e || !e.response) return;
  var cfg = clay.getSettings(e.response);

  // Persist unit so fetchWeather() picks it up
  localStorage.setItem('temp_unit', cfg.TEMP_UNIT.value || '0');

  Pebble.sendAppMessage({
    1:  cfg.USE_24H.value         ? 1 : 0,
    2:  parseInt(cfg.TEMP_UNIT.value       || '0'),
    3:  parseInt(cfg.TILE0.value           || '1'),
    4:  parseInt(cfg.TILE1.value           || '2'),
    5:  parseInt(cfg.TILE2.value           || '3'),
    6:  parseInt(cfg.TILE3.value           || '5'),
    7:  cfg.HOURLY_NOW.value      ? 1 : 0,
    8:  parseInt(cfg.HEALTH_SLOT_A.value   || '0'),
    9:  parseInt(cfg.HEALTH_SLOT_B.value   || '1'),
    10: parseInt(cfg.HEALTH_SLOT_C.value   || '4'),
    17: parseInt(cfg.STEP_GOAL.value       || '10000'),
    18: parseInt(cfg.CAL_GOAL.value        || '500'),
    19: parseInt(cfg.TOP_BAR.value         || '1'),
    20: parseInt(cfg.BOT_BAR.value         || '2'),
    21: parseInt(cfg.COLOR_BG.value        || '1'),
    22: parseInt(cfg.COLOR_BORDER.value    || '0'),
    23: parseInt(cfg.COLOR_FG.value        || '63'),
    24: parseInt(cfg.COLOR_ACCENT.value    || '13'),
  });

  // Re-fetch weather in case units changed
  fetchWeather();
});
