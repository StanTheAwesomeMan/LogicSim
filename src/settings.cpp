#include "../include/settings.h"
#include <qnamespace.h>
#include <qtextoption.h>

Settings::Settings() {
  Button x;
  x.setButtonIdentifier("X");
  x.baseColor = colors.getColor("surface2");
  x.hoverColor = colors.getColor("surface0");
  x.pressedColor = x.baseColor;
  x.baseTextColor = colors.getColor("crust");
  x.hoverTextColor = colors.getColor("text");
  buttons.push_back(x);

  x = {};
  x.setButtonIdentifier("ACCENT");
  x.baseColor = colors.getColor("darkAccent");
  x.hoverColor = colors.getColor("accent");
  x.hoverTextColor = colors.getColor("crust");
  buttons.push_back(x);

  x = {};
  x.setButtonIdentifier("RESET CLOCKS");
  buttons.push_back(x);
}

void Settings::draw(QSize window) {
  if (!visible)
    return;

  // darken background
  painter->setPen(Qt::transparent);
  painter->setBrush(colors.withAlpha(*colors.getColor("crust"), 64));
  painter->drawRect(QRectF(0, 0, window.width(), window.height()));

  // Draw settings window
  QSize s(200, 30 + 5 + 40 * (buttons.size() - 1));
  settingsBounds =
      QRectF(settingsPos.x() - s.width() / 2.0,
             settingsPos.y() - s.height() / 2.0, s.width(), s.height());

  titleBarBounds =
      QRectF(settingsBounds.x(), settingsBounds.y(), s.width(), 30);

  buttons[0].setButtonBounds(
      QRectF(titleBarBounds.x() + titleBarBounds.width() - 30.25,
             titleBarBounds.y(), 30, 29.5));

  for (int i = 1; i < buttons.size(); i++) {
    Button &b = buttons[i];
    b.setButtonBounds(QRectF(settingsBounds.x() + 5,
                             settingsBounds.y() - 5 + 40 * i,
                             settingsBounds.width() - 10, 35));
  }

  QRectF textBounds(titleBarBounds.x(), titleBarBounds.y(), 85, 30);

  painter->setBrush(colors.withAlpha(*colors.getColor("surface0"), 128));
  painter->drawRect(settingsBounds);
  painter->setBrush(*colors.getColor("surface2"));
  painter->drawRect(titleBarBounds);
  painter->setPen(*colors.getColor("crust"));
  painter->drawText(textBounds, "SETTINGS", QTextOption(Qt::AlignCenter));

  for (Button &b : buttons) {
    b.draw();
  }
}

Button *Settings::buttonPressed(QPoint mousePos) {

  if (!visible)
    return nullptr;

  for (Button &b : buttons) {
    if (b.buttonPressed(mousePos))
      return &b;
  }

  return nullptr;
}

void Settings::buttonHovering(QPoint mousePos) {
  for (Button &b : buttons) {
    b.buttonHovering(mousePos);
  }
}
