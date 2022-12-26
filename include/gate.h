#pragma once
#include <qpainter.h>
#include <qpoint.h>
#include <utility>
#include <vector>

class Gate {

public:
  Gate();
  void draw(bool selected);
  void update();
  std::tuple<int, QRectF *, int> getClickedPin(QPoint mousePos);
  bool gateClicked(QPoint mousePos);
  inline void setGateIdentifier(QString s) { gateIdentifier = std::move(s); };
  inline QString getGateIdentifier() { return gateIdentifier; };
  inline void setGatePos(QPointF p) { gatePos = std::move(p); };
  inline QSizeF getGateSize() { return gateBounds.size(); };
  QPainter *painter{};
  std::vector<bool *> inputs{};
  std::vector<QRectF> inputBounds{};
  bool output{};
  QRectF outputBounds{};

protected:
  QString gateIdentifier{};
  QPointF gatePos{};
  QRectF gateBounds{};
};
