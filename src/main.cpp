#include "../include/mainWindow.h"
#include <QApplication>
#include <QFont>
#include <QResource>
#include <qnamespace.h>

int main(int argc, char *argv[]) {
  // Create the application object and enable AA
  QApplication app(argc, argv);

  // Load the font from the fonts.qrc file
  QResource::registerResource("../font/fonts.qrc");
  QFont font;
  font.setFamily(":/fonts/KawkabMono-Regular.ttf");

  // Create the main window
  MainWindow window;
  window.setWindowTitle("Logic Simulator");
  window.setFont(font);
  window.resize(1920, 1080);
  window.setUpdatesEnabled(true);

  // Set background color
  QPalette palette = window.palette();
  palette.setColor(QPalette::Window, colors.getColor("crust")->rgb());
  window.setPalette(palette);

  // Show the window
  window.show();

  // Run the application event loop
  return app.exec();
}
