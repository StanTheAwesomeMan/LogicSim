#include "../include/button.h"
#include <qcolor.h>
#include <qnamespace.h>
#include <qtextoption.h>
#include <tuple>

Button::Button() {
  baseColor = colors.getColor("base");
  baseTextColor = colors.getColor("text");
  hoverColor = colors.getColor("surface0");
  hoverTextColor = colors.getColor("text");
  pressedColor = colors.getColor("accent");
  pressedTextColor = colors.getColor("base");
  buttonBounds = QRectF(0, 0, 0, 0);
  painter = nullptr;
  pressed = false;
  hovering = false;
}

void Button::draw() {
  painter->setPen(Qt::transparent);
  QColor c = pressed ? *pressedColor : (hovering ? *hoverColor : *baseColor);
  painter->setBrush(c);
  painter->drawRect(buttonBounds);
  c = pressed ? *pressedTextColor
              : (hovering ? *hoverTextColor : *baseTextColor);
  painter->setPen(c);
  painter->drawText(buttonBounds, buttonIdentifier,
                    QTextOption(Qt::AlignCenter));
}

bool Button::buttonPressed(QPoint mousePos) {
  if (buttonBounds.contains(mousePos)) {
    pressed = !pressed;
  }
  return pressed;
}

void Button::buttonHovering(QPoint mousePos) {
  if (buttonBounds.contains(mousePos)) {
    hovering = true;
    return;
  }
  hovering = false;
}
