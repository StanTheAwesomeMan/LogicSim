#include "../include/inputsMenu.h"
#include <qnamespace.h>
#include <qpainter.h>

IMenu::IMenu() {
  toggleButton.setButtonIdentifier("TOGGLE");
  clockButton.setButtonIdentifier("CLOCK");
}

void IMenu::draw() {
  // draw
  if (!visible)
    return;

  menuBounds = QRectF(menuPos, QSizeF(80, 5 + 40 * 2));

  toggleButton.setButtonBounds(QRectF(menuBounds.x() + 5, menuBounds.y() + 5,
                                      menuBounds.width() - 10, 35));

  clockButton.setButtonBounds(QRectF(menuBounds.x() + 5, menuBounds.y() + 45,
                                     menuBounds.width() - 10, 35));

  painter->setPen(Qt::transparent);
  painter->setBrush(*colors.getColor("surface1"));
  painter->drawRect(menuBounds);

  toggleButton.draw();
  clockButton.draw();
}

void IMenu::buttonHovering(QPoint mousePos) {
  // butons
  toggleButton.buttonHovering(mousePos);
}

Button *IMenu::buttonPressed(QPoint mousePos) {
  if (!visible)
    return nullptr;
  // Buttons
  if (toggleButton.buttonPressed(mousePos))
    return &toggleButton;
  if (clockButton.buttonPressed(mousePos))
    return &clockButton;

  return nullptr;
}
