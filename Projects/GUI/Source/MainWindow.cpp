#include "MainWindow.hh"

#include <QComboBox>
#include <QImage>

#include "./ui_MainWindow.h"
#include "Color.hh"
#include "Materials/Plain.hh"
#include "Object.hh"
#include "Registry.hh"
#include "SceneParse.hh"

auto rawScene = R"rawScene(
cubemap:
  back: "./files/scenes/textures/cubemap/stormydays_bk.jpg"
  down: "./files/scenes/textures/cubemap/stormydays_dn.jpg"
  front: "./files/scenes/textures/cubemap/stormydays_ft.jpg"
  left: "./files/scenes/textures/cubemap/stormydays_lf.jpg"
  right: "./files/scenes/textures/cubemap/stormydays_rt.jpg"
  up: "./files/scenes/textures/cubemap/stormydays_up.jpg"
eye:
  position:
    z: -5
lights:
  - position:
      x: 2
      y: 2.8
      z: -3
    color: white
    type: Sun
objects:
  - material:
      type: Plain
      color: aqua
    radius: 1
    type: Sphere
)rawScene";

void populateFlags(QLayout* parentLayout, QWidget* parent)
{
  for (auto&& flags : Rayon::RTMaterial::strToFlag)
  {
    auto* checkBox = new QCheckBox(parent);

    checkBox->setObjectName(flags.first.c_str() + QString::fromUtf8("CheckBox"));
    checkBox->setText(flags.first.c_str());
    parentLayout->addWidget(checkBox);
  }
}

// 2316, 1317
MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , _engine(Rayon::Config(1024, 1024, 8).setSilent(true))
{
  Rayon::registry().registerDefaults();
  Rayon::readSceneFromString(_scene, rawScene);
  _scene.preprocess();

  _material = static_cast<Rayon::Plain*>(_scene.lastObject()->getMaterial());

  ui->setupUi(this);
  populateFlags(ui->flagsGroupLayout, ui->flagsGroupBox);

  delete ui->placeHolderCheckBox;
  ui->placeHolderCheckBox = nullptr;

  ui->imageLabel->setPixmap(QPixmap());

  connectSignals();
  refreshRender();
}

void MainWindow::connectSignals()
{
  _engine.sigFinished.connect(
    [this] { QMetaObject::invokeMethod(this, "renderFinished", Qt::AutoConnection); });
}

void MainWindow::refreshRender()
{
  ui->statusbar->showMessage("Canceling previous rendering...");
  _engine.stop();

  ui->statusbar->showMessage("Rendering...");
  _engine.runAsync(_img, _scene, false);
}

void MainWindow::renderFinished()
{
  ui->statusbar->showMessage("Preparing image to show...");

  QImage qimg(_img.width(), _img.height(), QImage::Format_RGB32);

  for (auto i = 0u; i < _img.width(); ++i)
  {
    for (auto j = 0u; j < _img.height(); ++j)
    {
      auto pixel = _img.pixel(i, j);

      qimg.setPixel(i, j, pixel.intValue());
    }
  }

  ui->imageLabel->setPixmap(QPixmap::fromImage(qimg));
  ui->statusbar->showMessage("All is done!");
}

void MainWindow::colorChanged(const Rayon::Color& newColor)
{
  _material->setColor(newColor);
  refreshRender();
}

void MainWindow::reflexionChanged(double newReflexion)
{
  _material->setReflexion(newReflexion);
  refreshRender();
}

void MainWindow::transparencyChanged(double newTransparency)
{
  _material->setTransparency(newTransparency);
  refreshRender();
}

void MainWindow::refractionChanged(double newRefraction)
{
  _material->setRefraction(newRefraction);
  refreshRender();
}

void MainWindow::glossinessChanged(double newGlossiness)
{
  _material->setGlossiness(newGlossiness);
  refreshRender();
}

void MainWindow::shininessChanged(double newShininess)
{
  _material->setShininess(newShininess);
  refreshRender();
}

void MainWindow::ambientChanged(double newAmbient)
{
  _material->setAmbient(newAmbient);
  refreshRender();
}

MainWindow::~MainWindow()
{
  delete ui;
}
