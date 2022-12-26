#pragma once

#include "button.h"
#include "colors.h"
#include <qpainter.h>
#include <vector>

class Menu {

public:
  Menu();
  void draw(QSize window);
  inline void setPos(QPointF p) { menuPos = std::move(p); }
  inline void setVisible(bool b) { visible = std::move(b); }
  inline void setType(QString s) { menuType = std::move(s); }
  inline QString getType() { return menuType; }
  Button *buttonPressed(QPoint mousePos);
  void buttonHovering(QPoint mousePos);
  QPainter *painter{};
  std::vector<Button> buttons;

protected:
private:
  bool visible{};
  QPointF menuPos{};
  QRectF menuBounds{};
  QString menuType{};
};
