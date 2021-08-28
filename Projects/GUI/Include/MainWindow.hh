#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QTimer>
#include <memory>

#include "Rayon.hh"
#include "Batch/LocalBatchGenerator.hh"

namespace Rayon
{
  class Plain;
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
  void connectSignals();
  void drawImage();

public slots:
  void colorChanged(const Rayon::Color& newColor);
  void reflexionChanged(double newReflexion);
  void transparencyChanged(double newTransparency);
  void refractionChanged(double newRefraction);
  void glossinessChanged(double newGlossiness);
  void shininessChanged(double newShininess);
  void ambientChanged(double newAmbient);

private slots:
  void renderFinished();

private:
  Ui::MainWindow*                             ui;
  Rayon::Rayon                                _engine;
  Rayon::Scene                                _scene;
  Rayon::Plain*                               _material;
  Rayon::RawImage                             _img;
  std::unique_ptr<Rayon::LocalBatchGenerator> _batchGenerator;
  QTimer                                      _refreshTimer;
};
#endif  // MAINWINDOW_HH
