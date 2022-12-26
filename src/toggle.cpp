#include "../include/toggle.h"
#include <chrono>
#include <iostream>
#include <qnamespace.h>
#include <qpen.h>
#include <qtextoption.h>
#include <string>

Toggle::Toggle() { period = 1; }

void Toggle::draw(bool selected = false, __int128 framecount = 0) {
  toggleBounds = QRectF(togglePos, QSizeF(55, 30));

  toggleArea = QRectF(toggleBounds.x() + 5, toggleBounds.y() + 5, 20,
                      toggleBounds.height() - 10);

  outputBounds =
      QRectF(toggleBounds.x() + toggleBounds.width() - 5,
             toggleBounds.y() + toggleBounds.height() / 2 - 5, 10, 10);

  if (toggleMode == "CLOCK")
    if ((int)framecount % period == 0) {
      output = !output;
    }

  // draw toggle
  painter->setBrush(*colors.getColor("text"));
  painter->setPen(QPen(*colors.getColor("text"), 4, Qt::SolidLine));
  painter->drawLine(QRectF(toggleBounds.topLeft(), QSizeF(30, 30)).center(),
                    outputBounds.center());
  painter->setPen(QPen(selected ? *colors.getColor("text") : Qt::transparent, 2,
                       Qt::SolidLine));
  painter->drawEllipse(QRectF(toggleBounds.topLeft(), QSizeF(30, 30)));

  painter->setBrush((output) ? *colors.getColor("accent")
                             : *colors.getColor("darkAccent"));
  painter->drawEllipse(toggleArea);

  painter->setBrush(*colors.getColor("surface2"));
  painter->drawEllipse(outputBounds);

  if (toggleMode == "CLOCK") {
    QString str = QString("T: %1").arg(period);
    painter->setPen(*colors.getColor("text"));
    painter->setBrush(*colors.getColor("text"));
    painter->drawText(QRectF(toggleBounds.x(),
                             toggleBounds.y() - toggleBounds.height(), 60, 30),
                      str, QTextOption(Qt::AlignCenter));
  }
}

void Toggle::toggleAreaClicked(QPoint mousePos) {
  if (toggleArea.contains(mousePos) && toggleMode == "MANUAL") {
    output = !output;
  }
}

QRectF *Toggle::outputClicked(QPoint mousePos) {
  if (outputBounds.contains(mousePos)) {
    return &outputBounds;
  }
  return nullptr;
}

bool Toggle::bodyClicked(QPoint mousePos) {
  return (toggleBounds.contains(mousePos) &&
          (!toggleArea.contains(mousePos) || toggleMode != "MANUAL") &&
          !outputBounds.contains(mousePos));
}
