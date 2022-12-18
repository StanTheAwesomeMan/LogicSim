#pragma once

#include <QColor>

class Colors {

public:
  Colors();
  QColor withAlpha(QColor, int);
  void cycleAccent();
  QColor *getColor(const std::string &colorName);

private:
  QColor rosewater;
  QColor flamingo;
  QColor pink;
  QColor mauve;
  QColor red;
  QColor maroon;
  QColor peach;
  QColor yellow;
  QColor green;
  QColor teal;
  QColor sky;
  QColor sapphire;
  QColor blue;
  QColor lavender;
  QColor text;
  QColor subtext1;
  QColor subtext0;
  QColor overlay2;
  QColor overlay1;
  QColor overlay0;
  QColor surface2;
  QColor surface1;
  QColor surface0;
  QColor base;
  QColor mantle;
  QColor crust;
  QColor accent;
  QColor darkAccent;
};

extern Colors colors;
