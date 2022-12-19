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
  inline void setQPainter(QPainter *p) { painter = p; }
  inline QPainter *getQPainter() { return painter; }
  inline void setPressed(bool b) { pressed = b; }
  bool buttonPressed(QPoint mousePos);
  void buttonHovering(QPoint mousePos);

  void draw();

protected:
private:
  bool pressed;
  bool hovering;
  QRectF buttonBounds;
  QString buttonIdentifier;
  QPainter *painter;
  QColor *baseColor;
  QColor *hoverColor;
  QColor *pressedColor;
  QColor *baseTextColor;
  QColor *hoverTextColor;
  QColor *pressedTextColor;
};
