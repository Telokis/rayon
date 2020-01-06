#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>

#include "Rayon.hh"

namespace Rayon
{
  class Material;
}

QT_BEGIN_NAMESPACE
namespace Ui
{
  class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

private:
  void refreshRender();

public slots:
  void changeColor(const QString& newColor);

private:
  Ui::MainWindow*  ui;
  Rayon::Rayon     _engine;
  Rayon::Scene     _scene;
  Rayon::Material* _material;
};
#endif  // MAINWINDOW_HH
