#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>

#include "Rayon.hh"

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
  void d();

private:
  Ui::MainWindow* ui;
  Rayon::Rayon    _engine;
  Rayon::Scene    _scene;
};
#endif  // MAINWINDOW_HH
