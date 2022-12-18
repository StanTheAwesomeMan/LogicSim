#include "../include/button.h"

Button::Button() {
  baseColor = colors.getColor("base");
  buttonBounds = QRectF(0, 0, 0, 0);
}
