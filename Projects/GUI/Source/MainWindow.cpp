#include "MainWindow.hh"

#include <QComboBox>
#include <QImage>

#include "./ui_MainWindow.h"
#include "Color.hh"
#include "Material.hh"
#include "Registry.hh"
#include "SceneParse.hh"

auto rawScene = R"json(
{
	"eye" : 
	{
		"position" : 
		{
			"z" : -5
		}
	},
	"lights" : 
	[
		{
			"position" : 
			{
				"x" : 2,
				"y" : 2.8,
				"z" : -3
			},
			"color":"white",
			"type" : "Sun"
		}
	],
	"objects" : 
	[
		
		{
			"material" : 
			{
				"color" : "aqua"
			},
			"radius":1,
			"type" : "Sphere"
		}
	]
}
)json";

void populateColors(QComboBox* colorComboBox)
{
  for (auto&& colors : Rayon::colors())
  {
    colorComboBox->addItem(colors.first.c_str());
  }
}

void populateFlags(QLayout* parentLayout, QWidget* parent)
{
  for (auto&& flags : Rayon::Material::strToFlag)
  {
    auto* checkBox = new QCheckBox(parent);

    checkBox->setObjectName(flags.first.c_str() + QString::fromUtf8("CheckBox"));
    checkBox->setText(flags.first.c_str());
    parentLayout->addWidget(checkBox);
  }
}

// 2316, 1317
MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent), ui(new Ui::MainWindow), _engine({1024, 1024})
{
  ui->setupUi(this);
  populateColors(ui->colorComboBox);
  populateFlags(ui->flagsGroupLayout, ui->flagsGroupBox);

  delete ui->placeHolderCheckBox;
  ui->placeHolderCheckBox = nullptr;

  ui->imageLabel->setPixmap(QPixmap());

  Rayon::registry().registerDefaults();
  Rayon::readSceneFromString(_scene, rawScene);
  _scene.preprocess();

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

MainWindow::~MainWindow()
{
  delete ui;
}
