#include <QApplication>
#include <QFile>
#include <QStyleFactory>

#include "MainWindow.hh"
#include "Rayon.hh"

void setPalette(QApplication& app)
{
  QPalette darkPalette;
  darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
  darkPalette.setColor(QPalette::WindowText, Qt::white);
  darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
  darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
  darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
  darkPalette.setColor(QPalette::ToolTipText, Qt::white);
  darkPalette.setColor(QPalette::Text, Qt::white);
  darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
  darkPalette.setColor(QPalette::ButtonText, Qt::white);
  darkPalette.setColor(QPalette::BrightText, Qt::red);
  darkPalette.setColor(QPalette::Link, QColor(0x10, 0x4E, 0x8B));

  darkPalette.setColor(QPalette::Highlight, QColor(0x10, 0x4E, 0x8B));
  darkPalette.setColor(QPalette::HighlightedText, Qt::white);

  app.setPalette(darkPalette);

  QFile sheet(":/style/style/main.qss");
  sheet.open(QFile::ReadOnly);
  QString style(sheet.readAll());
  app.setStyleSheet(style);
}

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);
  app.setStyle(QStyleFactory::create("Fusion"));
  setPalette(app);

  MainWindow window;
  window.showMaximized();

  std::cout << std::flush;
  std::cerr << std::flush;

  return app.exec();
}