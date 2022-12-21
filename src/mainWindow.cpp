#include "../include/mainWindow.h"
#include <QTime>
#include <QTimer>
#include <chrono>
#include <cstddef>
#include <iostream>
#include <qcoreevent.h>
#include <qevent.h>
#include <qglobal.h>
#include <qnamespace.h>
#include <qnumeric.h>
#include <qpainter.h>
#include <qpainterpath.h>
#include <qpalette.h>
#include <qpoint.h>
#include <qsize.h>
#include <qtimer.h>
#include <qtransform.h>
#include <qwindowdefs.h>
#include <thread>
#include <variant>
#include <vector>

MainWindow::MainWindow(QWidget *parent) {
  timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &MainWindow::timerEvent);
  timer->setInterval(0);
  timer->start();

  frametime = framerate = 0;
  requestedFramerate = 165;
  snappingDistance = 15;

  menuButton.setButtonIdentifier("MENU");
  xorButton.setButtonIdentifier("XOR");

  mousePos = QPoint(0, 0);
}

void MainWindow::paintEvent(QPaintEvent *event) {
  // Unused Event
  Q_UNUSED(event);

  // Begin painter and initialize
  painter.begin(this);
  painter.setRenderHint(QPainter::Antialiasing);

  // Draw
  draw();

  // End painter
  painter.end();
}

void MainWindow::draw() {

  // initialize Painter
  if (menuButton.getQPainter() == nullptr) {
    menuButton.setQPainter(&painter);
    xorButton.setQPainter(&painter);
  }

  // Lines
  painter.setPen(*colors.getColor("base"));
  for (int i = 0; i < this->height() / snappingDistance; i++) {
    painter.drawLine(0, i * snappingDistance, this->width(),
                     i * snappingDistance);
  }
  for (int i = 0; i < this->width() / snappingDistance; i++) {
    painter.drawLine(i * snappingDistance, 0, i * snappingDistance,
                     this->height());
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
}

void MainWindow::updateBorders() {
  int width = this->width();
  int height = this->height();

  QRectF borderTop(0, 0, width, 15);
  QRectF borderLeft(0, 0, 15, height);
  QRectF borderRight(width - 15, 0, 15, height);
  QRectF borderBottom(0, height - 55, width, 15);

  borderBounds =
      std::vector<QRectF>{borderTop, borderLeft, borderBottom, borderRight};
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
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

void MainWindow::mouseMoveEvent(QMouseEvent *event) { mousePos = event->pos(); }

void MainWindow::resizeEvent(QResizeEvent *event) {
  // Stuff
  updateBorders();
  menuButton.setButtonBounds(QRectF(5, this->height() - 35, 60, 30));
  xorButton.setButtonBounds(QRectF(70, this->height() - 35, 50, 30));
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
