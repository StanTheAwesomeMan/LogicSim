#include "../include/menu.h"
#include <qnamespace.h>
#include <qpainter.h>

Menu::Menu() {}

void Menu::draw(QSize window) {
  // draw
  if (!visible)
    return;

  menuBounds = QRectF(QPointF(15, window.height() - 60 - 40 * buttons.size()),
                      QSizeF(100, 5 + 40 * buttons.size()));

  for (int i = 0; i < buttons.size(); i++) {
    Button &b = buttons[i];
    b.setButtonBounds(QRectF(menuBounds.x() + 5, menuBounds.y() + 5 + 40 * i,
                             menuBounds.width() - 10, 35));
  }

  painter->setPen(Qt::transparent);
  painter->setBrush(*colors.getColor("surface1"));
  painter->drawRect(menuBounds);

  for (Button &b : buttons) {
    b.draw();
  }
}

void Menu::buttonHovering(QPoint mousePos) {
  // butons
  for (Button &b : buttons) {
    b.buttonHovering(mousePos);
  }
}

Button *Menu::buttonPressed(QPoint mousePos) {
  if (!visible)
    return nullptr;
  // Buttons
  for (Button &b : buttons) {
    if (b.buttonPressed(mousePos))
      return &b;
  }

  return nullptr;
}
