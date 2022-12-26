#include "../include/gateMenu.h"
#include <optional>
#include <qnamespace.h>
#include <qsize.h>

GMenu::GMenu() {
  orButton.setButtonIdentifier("OR");
  andButton.setButtonIdentifier("AND");
  notButton.setButtonIdentifier("NOT");
  xorButton.setButtonIdentifier("XOR");
}

void GMenu::draw() {

  if (!visible)
    return;

  // Menu Bounds
  menuBounds = QRectF(menuPos, QSizeF(55, 5 + 40 * 4));

  // Buttons
  orButton.setButtonBounds(QRectF(menuBounds.x() + 5, menuBounds.y() + 5,
                                  menuBounds.width() - 10, 35));

  andButton.setButtonBounds(QRectF(menuBounds.x() + 5, menuBounds.y() + 45,
                                   menuBounds.width() - 10, 35));

  notButton.setButtonBounds(QRectF(menuBounds.x() + 5, menuBounds.y() + 85,
                                   menuBounds.width() - 10, 35));

  xorButton.setButtonBounds(QRectF(menuBounds.x() + 5, menuBounds.y() + 125,
                                   menuBounds.width() - 10, 35));

  // Menu background colors
  painter->setPen(Qt::transparent);
  painter->setBrush(*colors.getColor("surface1"));

  painter->drawRect(menuBounds);
  orButton.draw();
  andButton.draw();
  notButton.draw();
  xorButton.draw();
}

Button *GMenu::buttonPressed(QPoint mousePos) {
  if (!visible)
    return nullptr;
  else if (orButton.buttonPressed(mousePos))
    return &orButton;
  else if (andButton.buttonPressed(mousePos))
    return &andButton;
  else if (notButton.buttonPressed(mousePos))
    return &notButton;
  else if (xorButton.buttonPressed(mousePos))
    return &xorButton;
  return nullptr;
}

void GMenu::buttonHovering(QPoint mousePos) {
  orButton.buttonHovering(mousePos);
  xorButton.buttonHovering(mousePos);
  andButton.buttonHovering(mousePos);
  notButton.buttonHovering(mousePos);
}
