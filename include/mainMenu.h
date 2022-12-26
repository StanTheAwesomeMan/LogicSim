#pragma once

#include "button.h"
#include "colors.h"
#include <qpainter.h>

class MMenu {

public:
  MMenu();
  void draw();
  inline void setPos(QPointF p) { menuPos = std::move(p); }
  inline void setVisible(bool b) { visible = std::move(b); }
  Button *buttonPressed(QPoint mousePos);
  void buttonHovering(QPoint mousePos);
  QPainter *painter{};
  Button settingsButton{};
  Button quitButton{};

protected:
private:
  bool visible{};
  QPointF menuPos{};
  QRectF menuBounds{};
};
