#pragma once
#include <qpainter.h>
#include <qpoint.h>
#include <utility>
#include <vector>

class Gate {

public:
  Gate();
  void draw();
  void update();
  std::tuple<int, QRectF *, int> getClickedPin(QPoint mousePos);
  inline void setGateIdentifier(QString s) { gateIdentifier = std::move(s); };
  inline void setGateBounds(QRectF r) { gateBounds = std::move(r); };
  QPainter *painter{};
  std::vector<bool *> inputs{};
  std::vector<QRectF> inputBounds{};
  bool output{};
  QRectF outputBounds{};

protected:
  QString gateIdentifier{};
  QRectF gateBounds{};
};
