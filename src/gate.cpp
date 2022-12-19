#include "../include/gate.h"
#include "QMap"
#include <cstddef>
#include <functional>
#include <iostream>
#include <qnamespace.h>
#include <qpoint.h>
#include <qtextoption.h>

Gate::Gate() {
  painter = nullptr;
  inputs = {};
  gatePos = QPointF(0, 0);
  inputCount = 2;
  gateSize = QSizeF(60, 15 * inputCount);
}

void Gate::draw(int snappingDistance) {
  if (painter == nullptr)
    return;

  trueGatePos =
      QPointF(floor(gatePos.x() / snappingDistance) * snappingDistance +
                  snappingDistance / 2.0 - gateSize.width() / 2,
              floor(gatePos.y() / snappingDistance) * snappingDistance +
                  snappingDistance / 2.0 - gateSize.height() / 2);
  painter->setPen(Qt::transparent);
  painter->setBrush(*colors.getColor("accent"));
  painter->drawRoundedRect(QRectF(trueGatePos, gateSize), 7, 7);
  painter->setPen(*colors.getColor("base"));
  painter->drawText(QRectF(trueGatePos, gateSize), gateIdentifier,
                    QTextOption(Qt::AlignCenter));
}

bool Gate::output() {
  // Create a QMap to store the functions for each gate
  QMap<QString, std::function<bool()>> gates;
  gates["OR"] = [&]() {
    for (auto input : inputs) {
      if (input) {
        return true;
      }
    }
    return false;
  };
  gates["AND"] = [&]() {
    for (auto input : inputs) {
      if (!input) {
        return false;
      }
    }
    return true;
  };
  gates["NOT"] = [&]() { return inputs.empty() ? false : !inputs[0]; };
  gates["XOR"] = [&]() {
    bool result = false;
    for (auto input : inputs) {
      result = result ^ input();
    }
    return result;
  };

  // Check if the gateIdentifier is valid
  if (!gates.contains(gateIdentifier)) {
    std::cerr << gateIdentifier.toStdString() << " Does not Exist!"
              << std::endl;
  }

  // Call the function for the specified gate
  return gates[gateIdentifier]();
}

bool Gate::gatePressed(QPoint mousePos) {

  QRectF gateBounds = QRectF(trueGatePos, gateSize);
  if (gateBounds.contains(mousePos)) {
    return true;
  }
  return false;
}
