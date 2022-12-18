#pragma once

#include "colors.h"
#include <qpainter.h>
#include <qpoint.h>
#include <qrect.h>

class Button {
public:
  void setButtonBounds();
  void setButtonIdentifier();
  bool buttonPressed(QPoint mousePos);
  void buttonHovering(QPoint mousePos);

  void draw();

protected:
private:
  QRectF buttonBounds;
  QString buttonIdentifier;
  QPainter painter;

  QColor *baseColor = colors.getColor("base");
};
