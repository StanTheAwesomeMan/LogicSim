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
  inline double map(double value, double inMin, double inMax, double outMin,
                    double outMax) {
    return (value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
  }

protected:
  void draw();
  void updateBorders();

  void paintEvent(QPaintEvent *event) override;
  void resizeEvent(QResizeEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;
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
  QRectF mouseBounds;
  std::vector<std::tuple<QRectF *, QRectF *, bool *> *> connections{};
  std::vector<QPainterPath *> wirePaths;
  std::vector<Gate> logicGates;
  bool creatingConnection;
};
