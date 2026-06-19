[
  {
    "type": "heading",
    "defaultValue": "Pixel Tiles"
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Clock & Units",
        "size": 3
      },
      {
        "type": "toggle",
        "messageKey": "USE_24H",
        "label": "24-Hour Clock",
        "defaultValue": false
      },
      {
        "type": "select",
        "messageKey": "TEMP_UNIT",
        "label": "Temperature",
        "defaultValue": "0",
        "options": [
          {
            "label": "\u00b0F Fahrenheit",
            "value": "0"
          },
          {
            "label": "\u00b0C Celsius",
            "value": "1"
          }
        ]
      }
    ]
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Tile Contents",
        "size": 3
      },
      {
        "type": "text",
        "defaultValue": "Pick what each of the 4 tiles shows."
      },
      {
        "type": "select",
        "messageKey": "TILE0",
        "label": "Top-Left",
        "defaultValue": "1",
        "options": [
          {
            "label": "Empty",
            "value": "0"
          },
          {
            "label": "\u2600 Current Weather",
            "value": "1"
          },
          {
            "label": "\u23f1 Hourly Forecast",
            "value": "2"
          },
          {
            "label": "\ud83d\udcc5 3-Day Forecast",
            "value": "3"
          },
          {
            "label": "\ud83d\udcc6 Date",
            "value": "4"
          },
          {
            "label": "\u2764 Health",
            "value": "5"
          },
          {
            "label": "\ud83d\udd0b Battery",
            "value": "6"
          }
        ]
      },
      {
        "type": "select",
        "messageKey": "TILE1",
        "label": "Top-Right",
        "defaultValue": "2",
        "options": [
          {
            "label": "Empty",
            "value": "0"
          },
          {
            "label": "\u2600 Current Weather",
            "value": "1"
          },
          {
            "label": "\u23f1 Hourly Forecast",
            "value": "2"
          },
          {
            "label": "\ud83d\udcc5 3-Day Forecast",
            "value": "3"
          },
          {
            "label": "\ud83d\udcc6 Date",
            "value": "4"
          },
          {
            "label": "\u2764 Health",
            "value": "5"
          },
          {
            "label": "\ud83d\udd0b Battery",
            "value": "6"
          }
        ]
      },
      {
        "type": "select",
        "messageKey": "TILE2",
        "label": "Bottom-Left",
        "defaultValue": "3",
        "options": [
          {
            "label": "Empty",
            "value": "0"
          },
          {
            "label": "\u2600 Current Weather",
            "value": "1"
          },
          {
            "label": "\u23f1 Hourly Forecast",
            "value": "2"
          },
          {
            "label": "\ud83d\udcc5 3-Day Forecast",
            "value": "3"
          },
          {
            "label": "\ud83d\udcc6 Date",
            "value": "4"
          },
          {
            "label": "\u2764 Health",
            "value": "5"
          },
          {
            "label": "\ud83d\udd0b Battery",
            "value": "6"
          }
        ]
      },
      {
        "type": "select",
        "messageKey": "TILE3",
        "label": "Bottom-Right",
        "defaultValue": "5",
        "options": [
          {
            "label": "Empty",
            "value": "0"
          },
          {
            "label": "\u2600 Current Weather",
            "value": "1"
          },
          {
            "label": "\u23f1 Hourly Forecast",
            "value": "2"
          },
          {
            "label": "\ud83d\udcc5 3-Day Forecast",
            "value": "3"
          },
          {
            "label": "\ud83d\udcc6 Date",
            "value": "4"
          },
          {
            "label": "\u2764 Health",
            "value": "5"
          },
          {
            "label": "\ud83d\udd0b Battery",
            "value": "6"
          }
        ]
      }
    ]
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Hourly Tile",
        "size": 3
      },
      {
        "type": "toggle",
        "messageKey": "HOURLY_NOW",
        "label": "Show Now as first column (off = full 6h ahead)",
        "defaultValue": true
      }
    ]
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Health Tile",
        "size": 3
      },
      {
        "type": "text",
        "defaultValue": "Choose what fills each of the 3 zones: top-left, bottom-left, and the right column. Set right to None to expand left side to full width."
      },
      {
        "type": "select",
        "messageKey": "HEALTH_SLOT_A",
        "label": "Top-left stat",
        "defaultValue": "0",
        "options": [
          {
            "label": "Steps",
            "value": "0"
          },
          {
            "label": "Calories",
            "value": "1"
          },
          {
            "label": "Distance",
            "value": "2"
          },
          {
            "label": "Sleep",
            "value": "3"
          },
          {
            "label": "Heart Rate",
            "value": "4"
          },
          {
            "label": "Battery",
            "value": "5"
          }
        ]
      },
      {
        "type": "select",
        "messageKey": "HEALTH_SLOT_B",
        "label": "Bottom-left stat",
        "defaultValue": "1",
        "options": [
          {
            "label": "Steps",
            "value": "0"
          },
          {
            "label": "Calories",
            "value": "1"
          },
          {
            "label": "Distance",
            "value": "2"
          },
          {
            "label": "Sleep",
            "value": "3"
          },
          {
            "label": "Heart Rate",
            "value": "4"
          },
          {
            "label": "Battery",
            "value": "5"
          }
        ]
      },
      {
        "type": "select",
        "messageKey": "HEALTH_SLOT_C",
        "label": "Right column",
        "defaultValue": "4",
        "options": [
          {
            "label": "Steps",
            "value": "0"
          },
          {
            "label": "Calories",
            "value": "1"
          },
          {
            "label": "Distance",
            "value": "2"
          },
          {
            "label": "Sleep",
            "value": "3"
          },
          {
            "label": "Heart Rate",
            "value": "4"
          },
          {
            "label": "Battery",
            "value": "5"
          },
          {
            "label": "None (full width left)",
            "value": "6"
          }
        ]
      }
    ]
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Goals",
        "size": 3
      },
      {
        "type": "input",
        "messageKey": "STEP_GOAL",
        "label": "Daily Step Goal",
        "defaultValue": "10000",
        "attributes": {
          "type": "number",
          "min": "1000",
          "max": "50000"
        }
      },
      {
        "type": "input",
        "messageKey": "CAL_GOAL",
        "label": "Active Calorie Goal",
        "defaultValue": "500",
        "attributes": {
          "type": "number",
          "min": "100",
          "max": "3000"
        }
      }
    ]
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Progress Bars",
        "size": 3
      },
      {
        "type": "text",
        "defaultValue": "Bars show a label on the left and value on the right, with 28 segments between them."
      },
      {
        "type": "select",
        "messageKey": "TOP_BAR",
        "label": "Top Bar Progress",
        "defaultValue": "1",
        "options": [
          {
            "label": "None",
            "value": "0"
          },
          {
            "label": "\u2600 Sunrise \u2192 Sunset",
            "value": "1"
          },
          {
            "label": "\ud83d\udc5f Step Goal",
            "value": "2"
          },
          {
            "label": "\ud83d\udd25 Calorie Goal",
            "value": "3"
          },
          {
            "label": "\ud83d\udd0b Battery",
            "value": "4"
          }
        ]
      },
      {
        "type": "select",
        "messageKey": "BOT_BAR",
        "label": "Bottom Bar Progress",
        "defaultValue": "2",
        "options": [
          {
            "label": "None",
            "value": "0"
          },
          {
            "label": "\u2600 Sunrise \u2192 Sunset",
            "value": "1"
          },
          {
            "label": "\ud83d\udc5f Step Goal",
            "value": "2"
          },
          {
            "label": "\ud83d\udd25 Calorie Goal",
            "value": "3"
          },
          {
            "label": "\ud83d\udd0b Battery",
            "value": "4"
          }
        ]
      }
    ]
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Colors",
        "size": 3
      },
      {
        "type": "text",
        "defaultValue": "Full 64-color Pebble Time 2 palette. All 4 channels are independent."
      },
      {
        "type": "select",
        "messageKey": "COLOR_BG",
        "label": "Background (tile fill)",
        "defaultValue": "1",
        "options": [
          {
            "label": "Black",
            "value": "0"
          },
          {
            "label": "Oxford Blue",
            "value": "1"
          },
          {
            "label": "Duke Blue",
            "value": "2"
          },
          {
            "label": "Blue",
            "value": "3"
          },
          {
            "label": "Dark Green",
            "value": "4"
          },
          {
            "label": "Midnight Green",
            "value": "5"
          },
          {
            "label": "Cobalt Blue",
            "value": "6"
          },
          {
            "label": "Blue Moon",
            "value": "7"
          },
          {
            "label": "Islamic Green",
            "value": "8"
          },
          {
            "label": "Jaeger Green",
            "value": "9"
          },
          {
            "label": "Tiffany Blue",
            "value": "10"
          },
          {
            "label": "Vivid Cerulean",
            "value": "11"
          },
          {
            "label": "Green",
            "value": "12"
          },
          {
            "label": "Malachite",
            "value": "13"
          },
          {
            "label": "Med Aquamarine",
            "value": "14"
          },
          {
            "label": "Electric Blue",
            "value": "15"
          },
          {
            "label": "Ox Blood",
            "value": "16"
          },
          {
            "label": "Indigo",
            "value": "17"
          },
          {
            "label": "Duke Violet",
            "value": "18"
          },
          {
            "label": "Vivid Violet",
            "value": "19"
          },
          {
            "label": "Army Green",
            "value": "20"
          },
          {
            "label": "Dark Gray",
            "value": "21"
          },
          {
            "label": "Liberty",
            "value": "22"
          },
          {
            "label": "Very Light Blue",
            "value": "23"
          },
          {
            "label": "Kelp",
            "value": "24"
          },
          {
            "label": "Zinc",
            "value": "25"
          },
          {
            "label": "Blue Gray",
            "value": "26"
          },
          {
            "label": "Light Blue",
            "value": "27"
          },
          {
            "label": "Bright Green",
            "value": "28"
          },
          {
            "label": "Screamin Green",
            "value": "29"
          },
          {
            "label": "Med Spring Green",
            "value": "30"
          },
          {
            "label": "Cyan",
            "value": "31"
          },
          {
            "label": "Folly Red",
            "value": "32"
          },
          {
            "label": "Jazzberry Jam",
            "value": "33"
          },
          {
            "label": "Purpureus",
            "value": "34"
          },
          {
            "label": "Electric Violet",
            "value": "35"
          },
          {
            "label": "Windsor Tan",
            "value": "36"
          },
          {
            "label": "Bittersweet",
            "value": "37"
          },
          {
            "label": "Lavender Indigo",
            "value": "38"
          },
          {
            "label": "Heliotrope",
            "value": "39"
          },
          {
            "label": "Limerick",
            "value": "40"
          },
          {
            "label": "Brass",
            "value": "41"
          },
          {
            "label": "Light Gray",
            "value": "42"
          },
          {
            "label": "Baby Blue Eyes",
            "value": "43"
          },
          {
            "label": "Spring Bud",
            "value": "44"
          },
          {
            "label": "Inchworm",
            "value": "45"
          },
          {
            "label": "Celeste",
            "value": "46"
          },
          {
            "label": "Celeste Light",
            "value": "47"
          },
          {
            "label": "Red",
            "value": "48"
          },
          {
            "label": "Torch Red",
            "value": "49"
          },
          {
            "label": "Shocking Pink",
            "value": "50"
          },
          {
            "label": "Magenta",
            "value": "51"
          },
          {
            "label": "Orange",
            "value": "52"
          },
          {
            "label": "Sunset Orange",
            "value": "53"
          },
          {
            "label": "Brilliant Rose",
            "value": "54"
          },
          {
            "label": "Violet",
            "value": "55"
          },
          {
            "label": "Chrome Yellow",
            "value": "56"
          },
          {
            "label": "Rajah",
            "value": "57"
          },
          {
            "label": "Melon",
            "value": "58"
          },
          {
            "label": "Lavender Rose",
            "value": "59"
          },
          {
            "label": "Yellow",
            "value": "60"
          },
          {
            "label": "Laser Lemon",
            "value": "61"
          },
          {
            "label": "Pale Canary",
            "value": "62"
          },
          {
            "label": "White",
            "value": "63"
          }
        ]
      },
      {
        "type": "select",
        "messageKey": "COLOR_BORDER",
        "label": "Border (tile edge & bars)",
        "defaultValue": "0",
        "options": [
          {
            "label": "Black",
            "value": "0"
          },
          {
            "label": "Oxford Blue",
            "value": "1"
          },
          {
            "label": "Duke Blue",
            "value": "2"
          },
          {
            "label": "Blue",
            "value": "3"
          },
          {
            "label": "Dark Green",
            "value": "4"
          },
          {
            "label": "Midnight Green",
            "value": "5"
          },
          {
            "label": "Cobalt Blue",
            "value": "6"
          },
          {
            "label": "Blue Moon",
            "value": "7"
          },
          {
            "label": "Islamic Green",
            "value": "8"
          },
          {
            "label": "Jaeger Green",
            "value": "9"
          },
          {
            "label": "Tiffany Blue",
            "value": "10"
          },
          {
            "label": "Vivid Cerulean",
            "value": "11"
          },
          {
            "label": "Green",
            "value": "12"
          },
          {
            "label": "Malachite",
            "value": "13"
          },
          {
            "label": "Med Aquamarine",
            "value": "14"
          },
          {
            "label": "Electric Blue",
            "value": "15"
          },
          {
            "label": "Ox Blood",
            "value": "16"
          },
          {
            "label": "Indigo",
            "value": "17"
          },
          {
            "label": "Duke Violet",
            "value": "18"
          },
          {
            "label": "Vivid Violet",
            "value": "19"
          },
          {
            "label": "Army Green",
            "value": "20"
          },
          {
            "label": "Dark Gray",
            "value": "21"
          },
          {
            "label": "Liberty",
            "value": "22"
          },
          {
            "label": "Very Light Blue",
            "value": "23"
          },
          {
            "label": "Kelp",
            "value": "24"
          },
          {
            "label": "Zinc",
            "value": "25"
          },
          {
            "label": "Blue Gray",
            "value": "26"
          },
          {
            "label": "Light Blue",
            "value": "27"
          },
          {
            "label": "Bright Green",
            "value": "28"
          },
          {
            "label": "Screamin Green",
            "value": "29"
          },
          {
            "label": "Med Spring Green",
            "value": "30"
          },
          {
            "label": "Cyan",
            "value": "31"
          },
          {
            "label": "Folly Red",
            "value": "32"
          },
          {
            "label": "Jazzberry Jam",
            "value": "33"
          },
          {
            "label": "Purpureus",
            "value": "34"
          },
          {
            "label": "Electric Violet",
            "value": "35"
          },
          {
            "label": "Windsor Tan",
            "value": "36"
          },
          {
            "label": "Bittersweet",
            "value": "37"
          },
          {
            "label": "Lavender Indigo",
            "value": "38"
          },
          {
            "label": "Heliotrope",
            "value": "39"
          },
          {
            "label": "Limerick",
            "value": "40"
          },
          {
            "label": "Brass",
            "value": "41"
          },
          {
            "label": "Light Gray",
            "value": "42"
          },
          {
            "label": "Baby Blue Eyes",
            "value": "43"
          },
          {
            "label": "Spring Bud",
            "value": "44"
          },
          {
            "label": "Inchworm",
            "value": "45"
          },
          {
            "label": "Celeste",
            "value": "46"
          },
          {
            "label": "Celeste Light",
            "value": "47"
          },
          {
            "label": "Red",
            "value": "48"
          },
          {
            "label": "Torch Red",
            "value": "49"
          },
          {
            "label": "Shocking Pink",
            "value": "50"
          },
          {
            "label": "Magenta",
            "value": "51"
          },
          {
            "label": "Orange",
            "value": "52"
          },
          {
            "label": "Sunset Orange",
            "value": "53"
          },
          {
            "label": "Brilliant Rose",
            "value": "54"
          },
          {
            "label": "Violet",
            "value": "55"
          },
          {
            "label": "Chrome Yellow",
            "value": "56"
          },
          {
            "label": "Rajah",
            "value": "57"
          },
          {
            "label": "Melon",
            "value": "58"
          },
          {
            "label": "Lavender Rose",
            "value": "59"
          },
          {
            "label": "Yellow",
            "value": "60"
          },
          {
            "label": "Laser Lemon",
            "value": "61"
          },
          {
            "label": "Pale Canary",
            "value": "62"
          },
          {
            "label": "White",
            "value": "63"
          }
        ]
      },
      {
        "type": "select",
        "messageKey": "COLOR_FG",
        "label": "Foreground (text & icons)",
        "defaultValue": "63",
        "options": [
          {
            "label": "Black",
            "value": "0"
          },
          {
            "label": "Oxford Blue",
            "value": "1"
          },
          {
            "label": "Duke Blue",
            "value": "2"
          },
          {
            "label": "Blue",
            "value": "3"
          },
          {
            "label": "Dark Green",
            "value": "4"
          },
          {
            "label": "Midnight Green",
            "value": "5"
          },
          {
            "label": "Cobalt Blue",
            "value": "6"
          },
          {
            "label": "Blue Moon",
            "value": "7"
          },
          {
            "label": "Islamic Green",
            "value": "8"
          },
          {
            "label": "Jaeger Green",
            "value": "9"
          },
          {
            "label": "Tiffany Blue",
            "value": "10"
          },
          {
            "label": "Vivid Cerulean",
            "value": "11"
          },
          {
            "label": "Green",
            "value": "12"
          },
          {
            "label": "Malachite",
            "value": "13"
          },
          {
            "label": "Med Aquamarine",
            "value": "14"
          },
          {
            "label": "Electric Blue",
            "value": "15"
          },
          {
            "label": "Ox Blood",
            "value": "16"
          },
          {
            "label": "Indigo",
            "value": "17"
          },
          {
            "label": "Duke Violet",
            "value": "18"
          },
          {
            "label": "Vivid Violet",
            "value": "19"
          },
          {
            "label": "Army Green",
            "value": "20"
          },
          {
            "label": "Dark Gray",
            "value": "21"
          },
          {
            "label": "Liberty",
            "value": "22"
          },
          {
            "label": "Very Light Blue",
            "value": "23"
          },
          {
            "label": "Kelp",
            "value": "24"
          },
          {
            "label": "Zinc",
            "value": "25"
          },
          {
            "label": "Blue Gray",
            "value": "26"
          },
          {
            "label": "Light Blue",
            "value": "27"
          },
          {
            "label": "Bright Green",
            "value": "28"
          },
          {
            "label": "Screamin Green",
            "value": "29"
          },
          {
            "label": "Med Spring Green",
            "value": "30"
          },
          {
            "label": "Cyan",
            "value": "31"
          },
          {
            "label": "Folly Red",
            "value": "32"
          },
          {
            "label": "Jazzberry Jam",
            "value": "33"
          },
          {
            "label": "Purpureus",
            "value": "34"
          },
          {
            "label": "Electric Violet",
            "value": "35"
          },
          {
            "label": "Windsor Tan",
            "value": "36"
          },
          {
            "label": "Bittersweet",
            "value": "37"
          },
          {
            "label": "Lavender Indigo",
            "value": "38"
          },
          {
            "label": "Heliotrope",
            "value": "39"
          },
          {
            "label": "Limerick",
            "value": "40"
          },
          {
            "label": "Brass",
            "value": "41"
          },
          {
            "label": "Light Gray",
            "value": "42"
          },
          {
            "label": "Baby Blue Eyes",
            "value": "43"
          },
          {
            "label": "Spring Bud",
            "value": "44"
          },
          {
            "label": "Inchworm",
            "value": "45"
          },
          {
            "label": "Celeste",
            "value": "46"
          },
          {
            "label": "Celeste Light",
            "value": "47"
          },
          {
            "label": "Red",
            "value": "48"
          },
          {
            "label": "Torch Red",
            "value": "49"
          },
          {
            "label": "Shocking Pink",
            "value": "50"
          },
          {
            "label": "Magenta",
            "value": "51"
          },
          {
            "label": "Orange",
            "value": "52"
          },
          {
            "label": "Sunset Orange",
            "value": "53"
          },
          {
            "label": "Brilliant Rose",
            "value": "54"
          },
          {
            "label": "Violet",
            "value": "55"
          },
          {
            "label": "Chrome Yellow",
            "value": "56"
          },
          {
            "label": "Rajah",
            "value": "57"
          },
          {
            "label": "Melon",
            "value": "58"
          },
          {
            "label": "Lavender Rose",
            "value": "59"
          },
          {
            "label": "Yellow",
            "value": "60"
          },
          {
            "label": "Laser Lemon",
            "value": "61"
          },
          {
            "label": "Pale Canary",
            "value": "62"
          },
          {
            "label": "White",
            "value": "63"
          }
        ]
      },
      {
        "type": "select",
        "messageKey": "COLOR_ACCENT",
        "label": "Accent (labels, hi-temp, HR)",
        "defaultValue": "13",
        "options": [
          {
            "label": "Black",
            "value": "0"
          },
          {
            "label": "Oxford Blue",
            "value": "1"
          },
          {
            "label": "Duke Blue",
            "value": "2"
          },
          {
            "label": "Blue",
            "value": "3"
          },
          {
            "label": "Dark Green",
            "value": "4"
          },
          {
            "label": "Midnight Green",
            "value": "5"
          },
          {
            "label": "Cobalt Blue",
            "value": "6"
          },
          {
            "label": "Blue Moon",
            "value": "7"
          },
          {
            "label": "Islamic Green",
            "value": "8"
          },
          {
            "label": "Jaeger Green",
            "value": "9"
          },
          {
            "label": "Tiffany Blue",
            "value": "10"
          },
          {
            "label": "Vivid Cerulean",
            "value": "11"
          },
          {
            "label": "Green",
            "value": "12"
          },
          {
            "label": "Malachite",
            "value": "13"
          },
          {
            "label": "Med Aquamarine",
            "value": "14"
          },
          {
            "label": "Electric Blue",
            "value": "15"
          },
          {
            "label": "Ox Blood",
            "value": "16"
          },
          {
            "label": "Indigo",
            "value": "17"
          },
          {
            "label": "Duke Violet",
            "value": "18"
          },
          {
            "label": "Vivid Violet",
            "value": "19"
          },
          {
            "label": "Army Green",
            "value": "20"
          },
          {
            "label": "Dark Gray",
            "value": "21"
          },
          {
            "label": "Liberty",
            "value": "22"
          },
          {
            "label": "Very Light Blue",
            "value": "23"
          },
          {
            "label": "Kelp",
            "value": "24"
          },
          {
            "label": "Zinc",
            "value": "25"
          },
          {
            "label": "Blue Gray",
            "value": "26"
          },
          {
            "label": "Light Blue",
            "value": "27"
          },
          {
            "label": "Bright Green",
            "value": "28"
          },
          {
            "label": "Screamin Green",
            "value": "29"
          },
          {
            "label": "Med Spring Green",
            "value": "30"
          },
          {
            "label": "Cyan",
            "value": "31"
          },
          {
            "label": "Folly Red",
            "value": "32"
          },
          {
            "label": "Jazzberry Jam",
            "value": "33"
          },
          {
            "label": "Purpureus",
            "value": "34"
          },
          {
            "label": "Electric Violet",
            "value": "35"
          },
          {
            "label": "Windsor Tan",
            "value": "36"
          },
          {
            "label": "Bittersweet",
            "value": "37"
          },
          {
            "label": "Lavender Indigo",
            "value": "38"
          },
          {
            "label": "Heliotrope",
            "value": "39"
          },
          {
            "label": "Limerick",
            "value": "40"
          },
          {
            "label": "Brass",
            "value": "41"
          },
          {
            "label": "Light Gray",
            "value": "42"
          },
          {
            "label": "Baby Blue Eyes",
            "value": "43"
          },
          {
            "label": "Spring Bud",
            "value": "44"
          },
          {
            "label": "Inchworm",
            "value": "45"
          },
          {
            "label": "Celeste",
            "value": "46"
          },
          {
            "label": "Celeste Light",
            "value": "47"
          },
          {
            "label": "Red",
            "value": "48"
          },
          {
            "label": "Torch Red",
            "value": "49"
          },
          {
            "label": "Shocking Pink",
            "value": "50"
          },
          {
            "label": "Magenta",
            "value": "51"
          },
          {
            "label": "Orange",
            "value": "52"
          },
          {
            "label": "Sunset Orange",
            "value": "53"
          },
          {
            "label": "Brilliant Rose",
            "value": "54"
          },
          {
            "label": "Violet",
            "value": "55"
          },
          {
            "label": "Chrome Yellow",
            "value": "56"
          },
          {
            "label": "Rajah",
            "value": "57"
          },
          {
            "label": "Melon",
            "value": "58"
          },
          {
            "label": "Lavender Rose",
            "value": "59"
          },
          {
            "label": "Yellow",
            "value": "60"
          },
          {
            "label": "Laser Lemon",
            "value": "61"
          },
          {
            "label": "Pale Canary",
            "value": "62"
          },
          {
            "label": "White",
            "value": "63"
          }
        ]
      }
    ]
  },
  {
    "type": "submit",
    "defaultValue": "Save Settings"
  }
]