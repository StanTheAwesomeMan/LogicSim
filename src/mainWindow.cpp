#include "../include/mainWindow.h"
#include <QTime>
#include <QTimer>
#include <chrono>
#include <iostream>
#include <qcoreevent.h>
#include <qevent.h>
#include <qglobal.h>
#include <qnamespace.h>
#include <qpainter.h>
#include <qpainterpath.h>
#include <qpalette.h>
#include <qtimer.h>
#include <qtransform.h>
#include <qwindowdefs.h>
#include <thread>
#include <vector>

MainWindow::MainWindow(QWidget *parent) {
  connect(timer, &QTimer::timeout, this, &MainWindow::timerEvent);
  timer->setInterval(0);
  timer->start();
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
  QMap<Qt::MouseButton, std::function<void()>> actions = {
      {Qt::LeftButton, [] { /* Left Button pressed */ }},
      {Qt::MiddleButton, [] { /* Middle Button pressed */ }},
      {Qt::RightButton, [] { /* Right Button pressed */ }}};

  if (actions.contains(event->button())) {
    actions[event->button()]();
  }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
  QMap<Qt::MouseButton, std::function<void()>> actions = {
      {Qt::LeftButton, [] { /* Left Button released */ }},
      {Qt::MiddleButton, [] { /* Middle Button released */ }},
      {Qt::RightButton, [] { /* Right Button released */ }}};

  if (actions.contains(event->button())) {
    actions[event->button()]();
  }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
  // Move
}

void MainWindow::resizeEvent(QResizeEvent *event) {
  // Stuff
  updateBorders();
}

void MainWindow::timerEvent() {
  // FrameRate
  time.setHMS(0, 0, 0, QTime::currentTime().msec());
  repaint();
  frametime = abs(QTime::currentTime().msec() - time.msec());
  if (frametime < 1000 / requestedFramerate) {
    std::this_thread::sleep_for(std::chrono::milliseconds(
        1000 / (int)requestedFramerate - (int)frametime));
  }
  frametime = abs(QTime::currentTime().msec() - time.msec());
  framerate = 1.0 / (frametime / 1000.0);
  std::cout << framerate << std::endl;
  time.setHMS(0, 0, 0, QTime::currentTime().msec());
}
