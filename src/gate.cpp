#include "../include/gate.h"
#include "../include/colors.h"
#include <cstddef>
#include <iostream>
#include <qmap.h>
#include <qnamespace.h>
#include <qpoint.h>
#include <qsize.h>
#include <qtextoption.h>
#include <utility>

Gate::Gate() {}

void Gate::draw() {

  painter->setPen(Qt::transparent);
  painter->setBrush(*colors.getColor("accent"));
  painter->drawRoundedRect(gateBounds, 5, 5);

  for (int i = 0; i < inputs.size(); i++) {
    if (!inputs.empty()) {
      painter->setBrush(*colors.getColor("surface2"));
      painter->drawEllipse(inputBounds[i]);
    }
  }

  painter->drawEllipse(outputBounds);

  painter->setPen(*colors.getColor("crust"));
  painter->drawText(gateBounds, gateIdentifier, QTextOption(Qt::AlignCenter));
}

void Gate::update() {
  QMap<QString, int> types = {{"OR", 0}, {"AND", 1}, {"NOT", 2}, {"XOR", 3}};
  int type = types[gateIdentifier];

  switch (type) {
  case 0:
    output =
        std::any_of(inputs.begin(), inputs.end(), [](bool *in) { return *in; });
    break;
  case 1:
    output =
        std::all_of(inputs.begin(), inputs.end(), [](bool *in) { return *in; });
    break;
  case 2:
    output = inputs.empty() ? false : !*inputs[0];
    break;
  case 3:
    output = std::count_if(inputs.begin(), inputs.end(),
                           [](bool *in) { return *in; }) &
             1;
    break;
  default:
    break;
  }
  int inputCount = inputs.size();
  inputBounds.resize(inputCount);
  for (int i = 0; i < inputCount; ++i) {
    QPoint inputPos(gateBounds.x() - 5,
                    gateBounds.y() + (inputCount != 1 ? 2.5 : 10) + 15 * i);
    inputBounds[i] = QRectF(inputPos, QSize(10, 10));
  }

  outputBounds = QRectF(gateBounds.x() + gateBounds.width() - 5,
                        gateBounds.y() + gateBounds.height() / 2 - 5, 10, 10);
}

std::tuple<int, QRectF *, int> Gate::getClickedPin(QPoint mousePos) {
  if (outputBounds.contains(mousePos))
    return std::make_tuple(1, &outputBounds, -1);
  for (int i = 0; i < inputBounds.size(); i++) {
    if (inputBounds[i].contains(mousePos))
      return std::make_tuple(2, &inputBounds[i], i);
  }
  return std::make_tuple(0, nullptr, -1);
}
