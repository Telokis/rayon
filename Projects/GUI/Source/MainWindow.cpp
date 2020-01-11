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
  back: "./files/textures/cubemap/stormydays_bk.tga"
  down: "./files/textures/cubemap/stormydays_dn.tga"
  front: "./files/textures/cubemap/stormydays_ft.tga"
  left: "./files/textures/cubemap/stormydays_lf.tga"
  right: "./files/textures/cubemap/stormydays_rt.tga"
  up: "./files/textures/cubemap/stormydays_up.tga"
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
      color: aqua
    radius: 1
    type: Sphere
)rawScene";

void populateColors(QComboBox* colorComboBox)
{
  for (auto&& colors : Rayon::colors())
  {
    colorComboBox->addItem(colors.first.c_str());
  }
}

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
  populateColors(ui->colorComboBox);
  populateFlags(ui->flagsGroupLayout, ui->flagsGroupBox);

  delete ui->placeHolderCheckBox;
  ui->placeHolderCheckBox = nullptr;

  ui->imageLabel->setPixmap(QPixmap());

  refreshRender();
}

void MainWindow::refreshRender()
{
  Rayon::RawImage img;
  _engine.run(img, _scene, false);

  QImage qimg(img.width(), img.height(), QImage::Format_RGB32);

  for (auto i = 0u; i < img.width(); ++i)
  {
    for (auto j = 0u; j < img.height(); ++j)
    {
      auto pixel = img.pixel(i, j);

      qimg.setPixel(i, j, pixel.intValue());
    }
  }

  ui->imageLabel->setPixmap(QPixmap::fromImage(qimg));
}

void MainWindow::colorChanged(const QString& newColor)
{
  auto colorStr = newColor.toStdString();

  if (Rayon::colors().count(colorStr))
  {
    _material->setColor(Rayon::colors().at(colorStr));
    refreshRender();
  }
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
