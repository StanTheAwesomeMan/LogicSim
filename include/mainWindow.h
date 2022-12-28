#pragma once

#include "button.h"
#include "colors.h"
#include "gate.h"
#include "menu.h"
#include "settings.h"
#include "toggle.h"
#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>
#include <chrono>
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
  void keepConnectionsIntact();
  void handleButtonBar();
  void deleteWire(std::pair<QRectF, QRectF> a);
  int insertIntoGap(
      std::vector<std::tuple<std::pair<QRectF *, int>, QRectF *, bool *> *>
          &connections,
      std::tuple<std::pair<QRectF *, int>, QRectF *, bool *> *connection);

  void paintEvent(QPaintEvent *event) override;
  void resizeEvent(QResizeEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;
  void timerEvent();

private:
  std::chrono::time_point<std::chrono::steady_clock> start;
  QPainter painter;
  std::vector<QRectF> borderBounds;
  std::vector<QRectF> lineBounds;
  QTimer *timer;
  QTime time;
  qreal frametime;
  qreal framerate;
  qreal requestedFramerate;
  __int128 framecount;
  int snappingDistance;
  Button menuButton;
  Button gateButton;
  Button inputsButton;
  QPoint mousePos;
  Settings settings;
  QRectF mouseBounds;
  std::vector<std::tuple<std::pair<QRectF *, int>, QRectF *, bool *> *>
      connections{};
  std::vector<QPainterPath> wirePaths;
  std::vector<Gate *> logicGates;
  std::vector<Toggle *> toggles;
  std::vector<Menu> menus;
  bool creatingConnection;
  QPainterPath selectedWire;
  Gate *movedGate;
  Gate *selectedGate;
  Toggle *movedToggle;
  Toggle *selectedToggle;
  bool draggingSettings;
};
