#pragma once

#include "colors.h"
#include <qcolor.h>
#include <qpainter.h>
#include <qpoint.h>
#include <qrect.h>

class Button {
public:
  Button();
  inline void setButtonBounds(QRectF bounds) { buttonBounds = bounds; }
  inline void setButtonIdentifier(QString ident) { buttonIdentifier = ident; }
  inline QString getButtonIdentifier() { return buttonIdentifier; }
  inline void setPressed(bool b) { pressed = b; }
  inline bool isPressed() { return pressed; };
  bool buttonPressed(QPoint mousePos);
  void buttonHovering(QPoint mousePos);

  void draw();
  QPainter *painter;

protected:
private:
  bool pressed;
  bool hovering;
  QRectF buttonBounds;
  QString buttonIdentifier;
  QColor *baseColor;
  QColor *hoverColor;
  QColor *pressedColor;
  QColor *baseTextColor;
  QColor *hoverTextColor;
  QColor *pressedTextColor;
};
