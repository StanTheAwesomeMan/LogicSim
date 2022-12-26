#pragma once

#include "colors.h"
#include <chrono>
#include <qglobal.h>
#include <qpainter.h>
#include <qpoint.h>

class Toggle {

public:
  Toggle();
  void draw(bool selected, __int128 framecount);
  void toggleAreaClicked(QPoint mousePos);
  QRectF *outputClicked(QPoint mousePos);
  bool bodyClicked(QPoint mousePos);
  inline void setPos(QPointF p) { togglePos = std::move(p); }
  inline QSizeF getToggleSize() { return toggleBounds.size(); }
  inline void setToggleMode(QString s) { toggleMode = std::move(s); };

  QPainter *painter;
  bool output{};
  QRectF outputBounds{};
  int period{};

protected:
private:
  QString toggleMode;
  QPointF togglePos;
  QRectF toggleBounds;
  QRectF toggleArea;
  QRectF dragArea;
};
