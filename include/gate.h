#pragma once

#include "colors.h"
#include <qpainter.h>
#include <qpainterpath.h>
#include <qpoint.h>
#include <vector>

class Gate {
public:
  Gate();
  inline void setQPainter(QPainter *p) { painter = p; }
  inline QPainter *getQPainter() { return painter; }
  inline void setGatePos(QPointF pos) { gatePos = pos; }
  inline void setGateIdentifier(QString ident) { gateIdentifier = ident; };
  void draw(int snappingDistance);
  bool output();

  bool gatePressed(QPoint mousePos);

protected:
private:
  QPointF gatePos;
  QPointF trueGatePos;
  QSizeF gateSize;
  QString gateIdentifier;
  std::vector<bool (*)()> inputs;
  QPainter *painter;
  int inputCount;
};
