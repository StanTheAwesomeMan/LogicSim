#include "../include/colors.h"
#include <QMap>
#include <qcolor.h>

QColor Colors::withAlpha(QColor c, int a) {
  int r = c.red();
  int g = c.green();
  int b = c.blue();
  return QColor::fromRgb(r, g, b, a);
}

void Colors::cycleAccent() {
  static int accentIndex = 0;

  QList<QColor> accentColors = {lavender, flamingo, pink,   mauve, red,
                                maroon,   peach,    yellow, green, teal,
                                sky,      sapphire, blue};

  accent = accentColors[accentIndex];
  darkAccent = accent.darker(250);
  accentIndex = (int)((accentIndex + 1) % accentColors.size());
}

QColor *Colors::getColor(const std::string &colorName) {
  QMap<std::string, QColor *> colorMap;
  colorMap["rosewater"] = &rosewater;
  colorMap["flamingo"] = &flamingo;
  colorMap["pink"] = &pink;
  colorMap["mauve"] = &mauve;
  colorMap["red"] = &red;
  colorMap["maroon"] = &maroon;
  colorMap["peach"] = &peach;
  colorMap["yellow"] = &yellow;
  colorMap["green"] = &green;
  colorMap["teal"] = &teal;
  colorMap["sky"] = &sky;
  colorMap["sapphire"] = &sapphire;
  colorMap["blue"] = &blue;
  colorMap["lavender"] = &lavender;
  colorMap["text"] = &text;
  colorMap["subtext1"] = &subtext1;
  colorMap["subtext0"] = &subtext0;
  colorMap["overlay2"] = &overlay2;
  colorMap["overlay1"] = &overlay1;
  colorMap["overlay0"] = &overlay0;
  colorMap["surface2"] = &surface2;
  colorMap["surface1"] = &surface1;
  colorMap["surface0"] = &surface0;
  colorMap["base"] = &base;
  colorMap["mantle"] = &mantle;
  colorMap["crust"] = &crust;

  if (colorMap.contains(colorName)) {
    return colorMap[colorName];
  }
  return nullptr;
}

Colors colors;
