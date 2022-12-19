#pragma once

#include "button.h"
#include "colors.h"
#include "gate.h"
#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>
#include <qcoreevent.h>
#include <qdatetime.h>
#include <qevent.h>
#include <qline.h>
#include <qpainter.h>
#include <qpainterpath.h>
#include <qpalette.h>
#include <qpoint.h>
#include <qsize.h>
#include <qtimer.h>
#include <qtransform.h>
#include <qwindowdefs.h>
#include <vector>

class MainWindow : public QWidget {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);

protected:
  void draw();
  void updateBorders();

  void bezierPath(QPainterPath *path, QPoint p1, QPoint p2);
  void paintEvent(QPaintEvent *event) override;
  void resizeEvent(QResizeEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void timerEvent();

private:
  QPainter painter;
  std::vector<QRectF> borderBounds;
  std::vector<QRectF> lineBounds;
  QTimer *timer;
  QTime time;
  qreal frametime;
  qreal framerate;
  qreal requestedFramerate;
  int snappingDistance;
  Button menuButton;
  Button xorButton;
  QPoint mousePos;

  bool creatingGate;
  bool movingGate;
  Gate *movedGate;

  std::vector<Gate> logicGates;
};
