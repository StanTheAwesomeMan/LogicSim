#include "../include/mainWindow.h"
#include <QTime>
#include <QTimer>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <qcolor.h>
#include <qcoreevent.h>
#include <qevent.h>
#include <qglobal.h>
#include <qnamespace.h>
#include <qnumeric.h>
#include <qpainter.h>
#include <qpainterpath.h>
#include <qpalette.h>
#include <qpen.h>
#include <qpoint.h>
#include <qsize.h>
#include <qtimer.h>
#include <qtransform.h>
#include <qwindowdefs.h>
#include <thread>
#include <tuple>
#include <utility>
#include <variant>
#include <vector>

MainWindow::MainWindow(QWidget *parent) {
  // Timer for Framerate
  timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &MainWindow::timerEvent);
  timer->setInterval(0);
  timer->start();

  creatingConnection = false;

  frametime = framerate = 0;
  requestedFramerate = 165;
  snappingDistance = 15;

  // Buttons
  menuButton.setButtonIdentifier("MENU");
  xorButton.setButtonIdentifier("XOR");

  // Mouse position
  mousePos = QPoint(0, 0);

  Gate g1;
  Gate g2;
  Gate g3;

  g2.setGateIdentifier("XOR");
  for (int i = 0; i < 2; i++) {
    g2.inputs.push_back(new bool(false));
  }

  g3.setGateIdentifier("AND");
  for (int i = 0; i < 2; i++) {
    g3.inputs.push_back(new bool(false));
  }

  g1.setGateIdentifier("NOT");
  for (int i = 0; i < 1; i++) {
    g1.inputs.push_back(new bool(false));
  }
  // Update gate Bounds

  g2.setGateBounds(
      QRectF(30, 30, 45, (g2.inputs.size() < 2) ? 30 : 15 * g2.inputs.size()));
  g3.setGateBounds(QRectF(200, 200, 45,
                          (g3.inputs.size() < 2) ? 30 : 15 * g3.inputs.size()));
  g1.setGateBounds(QRectF(150, 100, 45,
                          (g1.inputs.size() < 2) ? 30 : 15 * g1.inputs.size()));

  logicGates.push_back(g1);
  logicGates.push_back(g2);
  logicGates.push_back(g3);
}

void MainWindow::paintEvent(QPaintEvent *event) {
  // Unused Event
  Q_UNUSED(event);

  // Begin painter and initialize
  painter.begin(this);
  painter.setRenderHint(QPainter::Antialiasing);

  // initialize Painter
  menuButton.painter = &painter;
  xorButton.painter = &painter;

  // Gates
  for (Gate &g : logicGates) {
    g.painter = &painter;
  }

  // Draw
  draw();

  // End painter
  painter.end();
}

void MainWindow::draw() {

  // Set the pen color
  painter.setPen(*colors.getColor("base"));
  painter.setBrush(Qt::transparent);

  // Calculate the number of lines to draw
  int numLines = std::max(this->height(), this->width()) / snappingDistance;

  // Draw the lines
  for (int i = 0; i <= numLines; i++) {
    QPointF start(i * snappingDistance, 0);
    QPointF end(i * snappingDistance, this->height());
    painter.drawLine(start, end);

    start = QPointF(0, i * snappingDistance);
    end = QPointF(this->width(), i * snappingDistance);
    painter.drawLine(start, end);
  }

  // Borders
  QPainterPath path{};
  painter.setBrush(*colors.getColor("surface0"));
  painter.setPen(Qt::transparent);

  path.setFillRule(Qt::WindingFill);
  for (QRectF borderRect : borderBounds) {
    path.addRect(borderRect);
  }
  painter.drawPath(path);

  // ButtonBar
  painter.setBrush(*colors.getColor("mantle"));
  painter.drawRect(0, this->height() - 40, this->width(), 40);

  // Buttons
  menuButton.draw();
  xorButton.draw();

  // Gates
  for (Gate &g : logicGates) {
    g.update();
  }

  wirePaths.clear();
  for (auto c : connections) {
    path.clear();
    QRectF c1 = *std::get<0>(*c);
    QRectF c2 = *std::get<1>(*c);
    bool s = *std::get<2>(*c);

    // Calculate the center point of c1
    int c1x = c1.x() + c1.width() / 2;
    int c1y = c1.y() + c1.height() / 2;
    QPoint p1(c1x, c1y);

    // Calculate the center point of c2
    int c2x = c2.x() + c2.width() / 2;
    int c2y = c2.y() + c2.height() / 2;
    QPoint p2(c2x, c2y);

    // Calculate the maximum distance between p1 and p2
    int max_distance = std::max(abs(p2.x() - p1.x()), 50);

    // Calculate the control point for p1
    int cp1x = p1.x() + max_distance - 5;
    int cp1y = p1.y();
    QPoint cp1(cp1x, cp1y);

    // Calculate the control point for p2
    int cp2x = p2.x() - max_distance + 5;
    int cp2y = p2.y();
    QPoint cp2(cp2x, cp2y);

    // Path generation
    path.moveTo(p1);
    path.cubicTo(cp1, cp2, p2);

    // Wire Drawing
    painter.setBrush(Qt::transparent);
    QColor col =
        (s) ? *colors.getColor("accent") : *colors.getColor("darkAccent");
    painter.setPen(QPen(col, 4));
    painter.drawPath(path);
    wirePaths.push_back(&path);
  }

  for (Gate &g : logicGates) {
    g.draw();
  }
}

void MainWindow::updateBorders() {

  QRectF borderTop(0, 0, width(), 15);
  QRectF borderLeft(0, 0, 15, height());
  QRectF borderRight(width() - 15, 0, 15, height());
  QRectF borderBottom(0, height() - 55, width(), 15);

  borderBounds =
      std::vector<QRectF>{borderTop, borderLeft, borderBottom, borderRight};
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
  QMap<Qt::MouseButton, int> actions = {
      {Qt::LeftButton, 1}, {Qt::MiddleButton, 2}, {Qt::RightButton, 3}};

  if (actions.contains(event->button())) {

    std::tuple<int, QRectF *, int> c;
    int type;
    QRectF *bounds;
    int input;
    switch (actions[event->button()]) {
    case 1:
      // Left mouse button
      if (menuButton.buttonPressed(mousePos)) {
        // Show menu
        break;
      }
      if (xorButton.buttonPressed(mousePos)) {
        xorButton.setPressed(false);
        break;
      }

      for (Gate &g : logicGates) {
        c = g.getClickedPin(mousePos);
        type = std::get<0>(c);
        bounds = std::get<1>(c);
        input = std::get<2>(c);
        switch (type) {
        case 0:
          // Not clicked
          break;
        case 1:
          // Output clicked
          if (!creatingConnection) {
            connections.push_back(new std::tuple<QRectF *, QRectF *, bool *>(
                bounds, &mouseBounds, &g.output));
            creatingConnection = true;
          }
          break;
        case 2:
          // Input Clicked
          if (creatingConnection) {
            bool connectionExists = false;
            for (const auto &connection : connections) {
              if (std::get<1>(*connection) == bounds) {
                connectionExists = true;
                break;
              }
            }
            if (!connectionExists) {
              std::get<1>(*connections.back()) = bounds;
              g.inputs[input] = std::get<2>(*connections.back());
              creatingConnection = false;
            }
          }
          break;
        case 3:
          // Right mouse button
          break;
        }
      }
    }
  }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
  QMap<Qt::MouseButton, int> actions = {
      {Qt::LeftButton, 1}, {Qt::MiddleButton, 2}, {Qt::RightButton, 3}};

  if (actions.contains(event->button())) {
    switch (actions[event->button()]) {
    case 1:
      // Left mouse button
      break;
    case 2:
      // Middle mouse button
      break;
    case 3:
      // Right mouse button
      break;
    }
  }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  // Handle escape key
  if (event->key() == Qt::Key_Escape) {
    // Do something when the escape key is pressed
  }

  // Handle delete key (backspace)
  if (event->key() == Qt::Key_Backspace) {
    // Do something when the delete key is pressed
  }

  // Handle up arrow key
  if (event->key() == Qt::Key_Up) {
    // Do something when the up arrow key is pressed
  }

  // Handle down arrow key
  if (event->key() == Qt::Key_Down) {
    // Do something when the down arrow key is pressed
  }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
  mousePos = event->pos();
  mouseBounds = QRectF(mousePos, QSize(1, 1));
  menuButton.buttonHovering(mousePos);
  xorButton.buttonHovering(mousePos);
}

void MainWindow::resizeEvent(QResizeEvent *event) {
  // Stuff
  updateBorders();
  menuButton.setButtonBounds(QRectF(5, height() - 35, 60, 30));
  xorButton.setButtonBounds(QRectF(70, height() - 35, 50, 30));
}

void MainWindow::timerEvent() {
  // Repaint the Screen
  repaint();

  // Get the time it took to draw the screen
  frametime = abs(QTime::currentTime().msec() - time.msec());

  // If its less than the frametime of the requested framerate,
  // sleep for the rest of the time
  if (frametime < 1000 / requestedFramerate) {
    std::this_thread::sleep_for(std::chrono::milliseconds(
        1000 / (int)requestedFramerate - (int)frametime));
  }

  // Get the frametime
  frametime = abs(QTime::currentTime().msec() - time.msec());

  // Calculate framerate
  framerate = 1.0 / (frametime / 1000.0);

  // Set the current milliseconds
  time.setHMS(0, 0, 0, QTime::currentTime().msec());
}
