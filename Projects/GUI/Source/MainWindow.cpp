#include "MainWindow.hh"

#include <QComboBox>

#include "./ui_MainWindow.h"
#include "Color.hh"
#include "Material.hh"

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

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  populateColors(ui->colorComboBox);
  populateFlags(ui->flagsGroupLayout, ui->flagsGroupBox);

  delete ui->placeHolderCheckBox;
  ui->placeHolderCheckBox = nullptr;
}

MainWindow::~MainWindow()
{
  delete ui;
}
