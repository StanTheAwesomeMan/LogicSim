#include "../include/mainWindow.h"
#include <QTime>
#include <QTimer>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <qcolor.h>
#include <qcoreevent.h>
#include <qevent.h>
#include <qglobal.h>
#include <qmap.h>
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
#include <qwidget.h>
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

  frametime = framerate = framecount = 0;
  requestedFramerate = 165;
  snappingDistance = 15;

  start = std::chrono::steady_clock::now();

  // Buttons
  menuButton.setButtonIdentifier("MENU");
  gateButton.setButtonIdentifier("GATE");
  inputsButton.setButtonIdentifier("INPUTS");

  // Mouse position
  mousePos = QPoint(0, 0);

  // Moved gatge
  movedGate = nullptr;
  movedToggle = nullptr;
}

void MainWindow::paintEvent(QPaintEvent *event) {
  // Unused Event
  Q_UNUSED(event);

  // Begin painter and initialize
  painter.begin(this);
  painter.setRenderHint(QPainter::Antialiasing);

  // initialize Painter
  menuButton.painter = &painter;
  gateButton.painter = &painter;
  inputsButton.painter = &painter;
  gateMenu.painter = &painter;
  inputsMenu.painter = &painter;
  gateMenu.orButton.painter = &painter;
  gateMenu.andButton.painter = &painter;
  gateMenu.notButton.painter = &painter;
  gateMenu.xorButton.painter = &painter;
  inputsMenu.toggleButton.painter = &painter;
  inputsMenu.clockButton.painter = &painter;

  // Gates
  for (Gate &g : logicGates) {
    g.painter = &painter;
  }

  // Toggles
  for (Toggle &t : toggles) {
    t.painter = &painter;
  }

  // Keep wires functioning
  keepConnectionsIntact();

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
  gateButton.draw();
  inputsButton.draw();

  gateMenu.draw();
  inputsMenu.draw();

  // Gates
  for (Gate &g : logicGates) {
    g.update();
  }

  wirePaths.clear();
  for (auto c : connections) {
    path.clear();
    QRectF c1 = *std::get<0>(std::get<0>(*c));
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

    bool selected = false;

    int tolerance = 5;

    if (!selectedWire.isEmpty()) {
      QRectF boundingRectA(selectedWire.currentPosition().x() - tolerance,
                           selectedWire.currentPosition().y() - tolerance,
                           tolerance, tolerance);
      QRectF boundingRectB(selectedWire.elementAt(0).x - tolerance,
                           selectedWire.elementAt(0).y - tolerance, tolerance,
                           tolerance);

      if (boundingRectA.contains(p2) && boundingRectB.contains(p1))
        selected = true;
    }

    // Wire Drawing
    painter.setBrush(Qt::transparent);
    QColor col =
        (s) ? *colors.getColor("accent") : *colors.getColor("darkAccent");
    painter.setPen(QPen(col.lighter((selected) ? ((s) ? 120 : 150) : 100),
                        (selected) ? 5 : 4, Qt::SolidLine));
    painter.drawPath(path);
    wirePaths.push_back(path);
  }

  for (Gate &g : logicGates) {
    g.draw((&g == selectedGate));
  }

  // Toggles
  for (Toggle &t : toggles) {
    t.draw((&t == selectedToggle), framecount);
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

    // Predefine things i guess
    std::tuple<int, QRectF *, int> c;
    int type;
    QRectF *bounds;
    int input;
    int tolerance = 10;
    QRectF boundingRect;
    Button *b;
    Gate ng;
    bool clicked = false;
    QMap<QString, int> inputCount = {
        {"OR", 2},
        {"AND", 2},
        {"XOR", 2},
        {"NOT", 1},
    };

    // switch mouse Buttons
    switch (actions[event->button()]) {
    case 1:
      // Left mouse button
      gateMenu.setVisible(false);
      inputsMenu.setVisible(false);
      if (menuButton.buttonPressed(mousePos)) {
        // Show menu
        menuButton.setPressed(true);
        inputsMenu.setVisible(false);
        gateButton.setPressed(false);
        inputsButton.setPressed(false);
      }
      if (gateButton.buttonPressed(mousePos)) {
        // Show gate window
        gateButton.setPressed(true);
        gateMenu.setVisible(true);
        menuButton.setPressed(false);
        inputsMenu.setVisible(false);
        inputsButton.setPressed(false);
      }
      if (inputsButton.buttonPressed(mousePos)) {
        // Show inputs window
        inputsButton.setPressed(true);
        inputsMenu.setVisible(true);
        menuButton.setPressed(false);
        gateButton.setPressed(false);
        gateMenu.setVisible(false);
      }

      // Check for clicked logic Gate
      clicked = false;
      for (Gate &g : logicGates) {
        if (g.gateClicked(mousePos)) {
          clicked = true;
          if (selectedGate == &g && movedGate == nullptr) {
            movedGate = &g;
          } else if (selectedGate == nullptr && movedGate == nullptr) {
            selectedGate = &g;
          } else {
            clicked = false;
          }
          break;
        }
      }

      if (clicked == false) {
        selectedGate = nullptr;
        movedGate = nullptr;
      }

      for (Toggle &t : toggles) {
        t.toggleAreaClicked(mousePos);
        // check for clicked Toggle body
        clicked = false;
        if (t.bodyClicked(mousePos)) {
          clicked = true;
          if (selectedToggle == &t && movedToggle == nullptr) {
            movedToggle = &t;
          } else if (selectedToggle == nullptr && movedToggle == nullptr) {
            selectedToggle = &t;
          } else {
            clicked = false;
          }
          break;
        }
      }

      if (clicked == false) {
        selectedToggle = nullptr;
        movedToggle = nullptr;
      }

      // More button shenanigans
      b = gateMenu.buttonPressed(mousePos);
      if (b != nullptr) {
        b->setPressed(false); // Add or gate
        ng.setGateIdentifier(b->getButtonIdentifier());
        for (int i = 0; i < inputCount[b->getButtonIdentifier()]; i++) {
          ng.inputs.push_back(new bool(false));
        }
        ng.setGatePos(QPointF(mousePos.x() - 45 / 2.0, mousePos.y() - 15));
        logicGates.push_back(ng);
        movedGate = &logicGates.back();
        selectedGate = movedGate;
        b = nullptr;
      }

      // Input button pain
      b = inputsMenu.buttonPressed(mousePos);
      if (b != nullptr) {
        b->setPressed(false);
        if (b->getButtonIdentifier() == "TOGGLE") {
          // create toggle
          Toggle tg;
          tg.setToggleMode("MANUAL");
          tg.setPos(mousePos);
          toggles.push_back(tg);
          movedToggle = &toggles.back();
          selectedToggle = movedToggle;
        } else if (b->getButtonIdentifier() == "CLOCK") {
          // create toggle
          Toggle tg;
          tg.setToggleMode("CLOCK");
          tg.period = 165 / 2;
          tg.setPos(mousePos);
          toggles.push_back(tg);
          movedToggle = &toggles.back();
          selectedToggle = movedToggle;
        }
      }

      for (Toggle &t : toggles) {
        // Check for clicked Toggle output
        if (t.outputClicked(mousePos) != nullptr) {
          if (!creatingConnection) {
            connections.push_back(
                new std::tuple<std::pair<QRectF *, int>, QRectF *, bool *>(
                    std::make_pair(t.outputClicked(mousePos), -1), &mouseBounds,
                    &t.output));
            creatingConnection = true;
          }
          return;
        }
      }

      // Check for clicked Logic Gate pins
      for (Gate &g : logicGates) {
        c = g.getClickedPin(mousePos);
        type = std::get<0>(c);
        bounds = std::get<1>(c);
        input = std::get<2>(c);
        // Switch individual pin types
        switch (type) {
        case 0:
          // Not clicked
          break;
        case 1:
          // Output clicked
          if (!creatingConnection) {
            connections.push_back(
                new std::tuple<std::pair<QRectF *, int>, QRectF *, bool *>(
                    std::make_pair(bounds, input), &mouseBounds, &g.output));
            creatingConnection = true;
          }
          return;
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
              std::get<1>(std::get<0>(*connections.back())) = input;
              g.inputs[input] = std::get<2>(*connections.back());
              creatingConnection = false;
            }
          }
          return;
        }
      }

      // Wires
      boundingRect = QRectF(mousePos.x() - tolerance, mousePos.y() - tolerance,
                            tolerance * 2, tolerance * 2);

      if (!selectedWire.isEmpty())
        selectedWire.clear();
      for (QPainterPath &p : wirePaths) {
        if (p.intersects(boundingRect)) {
          if (!selectedWire.isEmpty())
            selectedWire.clear();
          else
            selectedWire = p;
        }
      }
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
      if (selectedGate != nullptr && movedGate != nullptr)
        movedGate = nullptr;
      if (selectedToggle != nullptr && movedToggle != nullptr)
        movedToggle = nullptr;
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
    // Add exit confirmation
    exit(0);
  }

  // Handle delete key (backspace)
  if (event->key() == Qt::Key_Backspace) {
    // Cancelling Connections
    if (creatingConnection) {
      creatingConnection = false;
      connections.pop_back();

      // Deleting Wires
    } else if (!selectedWire.isEmpty()) {
      int index = -1;
      for (int i = 0; i < connections.size(); ++i) {
        QRectF *startRect = std::get<0>(std::get<0>(*connections[i]));
        QRectF *endRect = std::get<1>(*connections[i]);
        if (startRect->contains(selectedWire.elementAt(0)) &
            endRect->contains(selectedWire.currentPosition())) {
          // Connection found
          index = i;
          int inputIndex = -1;
          for (int j = 0; j < logicGates.size(); ++j) {
            for (int k = 0; k < logicGates[j].inputBounds.size(); ++k) {
              QRectF inputBounds = logicGates[j].inputBounds[k];
              if (endRect->contains(inputBounds)) {
                // Input found
                inputIndex = k;
                break;
              }
            }
            if (inputIndex >= 0) {
              // Update input value
              logicGates[j].inputs[inputIndex] = new bool(false);
              break;
            }
          }
          break;
        }
      }
      if (index > -1) {
        connections.erase(connections.begin() + index);
      }
      selectedWire.clear();
    }

    // Handle toggle deletion
    if (selectedToggle != nullptr && movedToggle == nullptr) {
      // Delete connections
      for (int i = 0; i < connections.size(); i++) {
        QRectF *startRect = std::get<0>(std::get<0>(*connections[i]));
        if (startRect->contains(selectedToggle->outputBounds)) {
          // Connection found
          QRectF *endRect = std::get<1>(*connections[i]);
          connections.erase(connections.begin() + i);
          i--;
          // Update input of the gate connected to the end point
          for (int j = 0; j < logicGates.size(); j++) {
            for (int k = 0; k < logicGates[j].inputBounds.size(); k++) {
              QRectF inputBounds = logicGates[j].inputBounds[k];
              if (endRect->contains(inputBounds)) {
                // Input found
                logicGates[j].inputs[k] = new bool(false);
                continue;
              }
            }
          }
        }
      }
      if (selectedToggle != nullptr) {
        for (int i = 0; i < toggles.size(); i++) {
          if (&toggles[i] == selectedToggle) {
            selectedToggle = nullptr;
            toggles.erase(toggles.begin() + i);
            break;
          }
        }
      }
    }

    // Handle gate deletion
    if (selectedGate != nullptr && movedGate == nullptr) {
      // Delete connections with selected gate as start point
      for (int i = 0; i < connections.size(); i++) {
        QRectF *startRect = std::get<0>(std::get<0>(*connections[i]));
        if (startRect->contains(selectedGate->outputBounds)) {
          // Connection found
          QRectF *endRect = std::get<1>(*connections[i]);
          connections.erase(connections.begin() + i);
          i--;
          // Update input of the gate connected to the end point
          for (int j = 0; j < logicGates.size(); j++) {
            for (int k = 0; k < logicGates[j].inputBounds.size(); k++) {
              QRectF inputBounds = logicGates[j].inputBounds[k];
              if (endRect->contains(inputBounds)) {
                // Input found
                logicGates[j].inputs[k] = new bool(false);
                continue;
              }
            }
          }
        }
      }
      // Delete connections with selected gate as end point
      for (int i = 0; i < connections.size(); i++) {
        QRectF *endRect = std::get<1>(*connections[i]);
        for (int h = 0; h < selectedGate->inputBounds.size(); h++) {
          if (endRect->contains(selectedGate->inputBounds[h])) {
            // Connection found
            connections.erase(connections.begin() + i);
            i--;
          }
        }
      }
      // Delete selected gate
      for (int i = 0; i < logicGates.size(); i++) {
        if (&logicGates[i] == selectedGate) {
          selectedGate = nullptr;
          logicGates.erase(logicGates.begin() + i);
          break;
        }
      }
    }
  }
  // Handle up arrow key
  if (event->key() == Qt::Key_Up) {
    if (selectedGate != nullptr && movedGate == nullptr) {
      // Do something when the up arrow key is pressed
      if (selectedGate->getGateIdentifier() != "NOT" &&
          selectedGate->inputs.size() < 8) {
        int x = -1, y = -1, z = -1;
        std::vector<std::pair<int, int>> f;
        for (int i = 0; i < connections.size(); i++) {
          QRectF *startRect = std::get<0>(std::get<0>(*connections[i]));
          QRectF *endRect = std::get<1>(*connections[i]);
          for (int z = 0; z < selectedGate->inputBounds.size(); z++) {
            QRectF inputBounds = selectedGate->inputBounds[z];
            if (endRect->contains(inputBounds)) {
              x = std::get<1>(std::get<0>(*connections[i]));
              y = i;
              f.emplace_back(x, y);
            }
          }
          if (startRect->contains(selectedGate->outputBounds)) {
            z = i;
          }
        }
        selectedGate->inputs.emplace_back(new bool(false));
        selectedGate->update();
        for (const auto &[x, y] : f) {
          std::get<1>(*connections[y]) = &selectedGate->inputBounds[x];
        }
        if (z != -1) {
          std::get<0>(std::get<0>(*connections[z])) =
              &selectedGate->outputBounds;
        }
      }
    }

    if (selectedToggle != nullptr) {
      selectedToggle->period = selectedToggle->period + 1;
    }
  }

  // Handle down arrow key
  if (event->key() == Qt::Key_Down) {
    if (selectedGate != nullptr && movedGate == nullptr) {
      if (selectedGate->inputs.size() > 2) {
        for (int i = 0; i < connections.size(); i++) {
          QRectF *endRect = std::get<1>(*connections[i]);
          QRectF inputBounds =
              selectedGate->inputBounds[selectedGate->inputs.size() - 1];
          if (endRect->contains(inputBounds)) {
            connections.erase(connections.begin() + i);
          }
        }
        selectedGate->inputs.erase(selectedGate->inputs.end() - 1);
      }
    }

    if (selectedToggle != nullptr) {
      selectedToggle->period = std::max(selectedToggle->period - 1, 1);
    }
  }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
  mousePos = event->pos();
  mouseBounds = QRectF(mousePos, QSize(1, 1));
  menuButton.buttonHovering(mousePos);
  gateButton.buttonHovering(mousePos);
  inputsButton.buttonHovering(mousePos);
  gateMenu.buttonHovering(mousePos);
  inputsMenu.buttonHovering(mousePos);

  if (movedGate != nullptr) {
    QSizeF gateSize = movedGate->getGateSize();
    QPointF gatePos = QPointF(mousePos.x() - gateSize.width() / 2,
                              mousePos.y() - gateSize.height() / 2);
    movedGate->setGatePos(gatePos);
  } else if (movedToggle != nullptr) {
    QSizeF toggleSize = movedToggle->getToggleSize();
    QPointF togglePos = QPointF(mousePos.x() - toggleSize.width() / 2,
                                mousePos.y() - toggleSize.height() / 2);
    movedToggle->setPos(togglePos);
  }
}

void MainWindow::resizeEvent(QResizeEvent *event) {
  // Stuff
  updateBorders();
  menuButton.setButtonBounds(QRectF(5, height() - 35, 60, 30));
  gateButton.setButtonBounds(QRectF(70, height() - 35, 55, 30));
  inputsButton.setButtonBounds(QRectF(130, height() - 35, 65, 30));
  gateMenu.setPos(QPointF(15, height() - 220));
  inputsMenu.setPos(QPointF(15, height() - 140));
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

  // increase framecount
  framecount++;
}

void MainWindow::keepConnectionsIntact() {
  for (Gate &g : logicGates) {
    int f = -1, x = -1, y = -1, a = -1;
    std::vector<std::pair<int, int>> d;
    for (int i = 0; i < connections.size(); i++) {
      QRectF *startRect = std::get<0>(std::get<0>(*connections[i]));
      QRectF *endRect = std::get<1>(*connections[i]);
      for (int z = 0; z < g.inputBounds.size(); z++) {
        QRectF inputBounds = g.inputBounds[z];
        if (endRect->contains(inputBounds)) {
          x = std::get<1>(std::get<0>(*connections[i]));
          y = i;
          d.emplace_back(x, y);
        }
      }
      if (startRect->contains(g.outputBounds)) {
        f = i;
      }
    }
    if (f != -1) {
      std::get<0>(std::get<0>(*connections[f])) = &g.outputBounds;
      std::get<2>(*connections[f]) = &g.output;
    }
    if (!creatingConnection)
      for (const auto &[x, y] : d) {
        std::get<1>(*connections[y]) = &g.inputBounds[x];
        g.inputs[x] = std::get<2>(*connections[y]);
      }
  }
  for (Toggle &t : toggles) {
    int f = -1;
    for (int i = 0; i < connections.size(); i++) {
      QRectF *startRect = std::get<0>(std::get<0>(*connections[i]));
      if (startRect->contains(t.outputBounds)) {
        f = i;
      }
    }
    if (f != -1) {
      std::get<0>(std::get<0>(*connections[f])) = &t.outputBounds;
      std::get<2>(*connections[f]) = &t.output;
    }
  }
}
