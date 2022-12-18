#pragma once

#include <QColor>

class Colors {

public:
  QColor withAlpha(QColor, int);

  void cycleAccent();

  QColor *getColor(const std::string &colorName);

private:
  QColor rosewater = QColor::fromRgb(245, 224, 220);
  QColor flamingo = QColor::fromRgb(242, 205, 205);
  QColor pink = QColor::fromRgb(245, 194, 231);
  QColor mauve = QColor::fromRgb(203, 166, 247);
  QColor red = QColor::fromRgb(243, 139, 168);
  QColor maroon = QColor::fromRgb(235, 160, 172);
  QColor peach = QColor::fromRgb(250, 179, 135);
  QColor yellow = QColor::fromRgb(249, 226, 175);
  QColor green = QColor::fromRgb(166, 227, 161);
  QColor teal = QColor::fromRgb(148, 226, 213);
  QColor sky = QColor::fromRgb(137, 220, 235);
  QColor sapphire = QColor::fromRgb(116, 199, 236);
  QColor blue = QColor::fromRgb(137, 180, 250);
  QColor lavender = QColor::fromRgb(180, 190, 254);
  QColor text = QColor::fromRgb(205, 214, 244);
  QColor subtext1 = QColor::fromRgb(186, 194, 222);
  QColor subtext0 = QColor::fromRgb(166, 173, 200);
  QColor overlay2 = QColor::fromRgb(147, 153, 178);
  QColor overlay1 = QColor::fromRgb(127, 132, 156);
  QColor overlay0 = QColor::fromRgb(108, 112, 134);
  QColor surface2 = QColor::fromRgb(88, 91, 112);
  QColor surface1 = QColor::fromRgb(69, 71, 90);
  QColor surface0 = QColor::fromRgb(49, 50, 68);
  QColor base = QColor::fromRgb(30, 30, 46);
  QColor mantle = QColor::fromRgb(24, 24, 37);
  QColor crust = QColor::fromRgb(17, 17, 27);

  QColor accent = blue;
  QColor darkAccent = accent.darker(200);
};

extern Colors colors;
