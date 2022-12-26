#pragma once

#include "button.h"
#include "colors.h"
#include <qpainter.h>
#include <vector>

class Settings {

public:
  Settings();
  void draw(QSize window);
  inline void setPos(QPointF p) { settingsPos = std::move(p); }
  inline void setVisible(bool b) { visible = std::move(b); }
  inline QSizeF getSize() { return settingsBounds.size(); }
  inline bool titleBarPressed(QPoint mousePos) {
    return (titleBarBounds.contains(mousePos) && visible);
  }
  Button *buttonPressed(QPoint mousePos);
  void buttonHovering(QPoint mousePos);
  QPainter *painter{};
  std::vector<Button> buttons;
  bool visible{};

protected:
private:
  QPointF settingsPos{};
  QRectF settingsBounds{};
  QString settingsType{};
  QRectF titleBarBounds{};
};
