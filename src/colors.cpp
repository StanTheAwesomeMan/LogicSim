#include "../include/colors.h"
#include <QMap>
#include <qcolor.h>

Colors::Colors() {
  rosewater = QColor::fromRgb(245, 224, 220);
  flamingo = QColor::fromRgb(242, 205, 205);
  pink = QColor::fromRgb(245, 194, 231);
  mauve = QColor::fromRgb(203, 166, 247);
  red = QColor::fromRgb(243, 139, 168);
  maroon = QColor::fromRgb(235, 160, 172);
  peach = QColor::fromRgb(250, 179, 135);
  yellow = QColor::fromRgb(249, 226, 175);
  green = QColor::fromRgb(166, 227, 161);
  teal = QColor::fromRgb(148, 226, 213);
  sky = QColor::fromRgb(137, 220, 235);
  sapphire = QColor::fromRgb(116, 199, 236);
  blue = QColor::fromRgb(137, 180, 250);
  lavender = QColor::fromRgb(180, 190, 254);
  text = QColor::fromRgb(205, 214, 244);
  subtext1 = QColor::fromRgb(186, 194, 222);
  subtext0 = QColor::fromRgb(166, 173, 200);
  overlay2 = QColor::fromRgb(147, 153, 178);
  overlay1 = QColor::fromRgb(127, 132, 156);
  overlay0 = QColor::fromRgb(108, 112, 134);
  surface2 = QColor::fromRgb(88, 91, 112);
  surface1 = QColor::fromRgb(69, 71, 90);
  surface0 = QColor::fromRgb(49, 50, 68);
  base = QColor::fromRgb(30, 30, 46);
  mantle = QColor::fromRgb(24, 24, 37);
  crust = QColor::fromRgb(17, 17, 27);

  accent = blue;
  darkAccent = accent.darker(200);
}

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
  colorMap["accent"] = &accent;
  colorMap["darkAccent"] = &darkAccent;

  if (colorMap.contains(colorName)) {
    return colorMap[colorName];
  }
  return &crust;
}

Colors colors;
