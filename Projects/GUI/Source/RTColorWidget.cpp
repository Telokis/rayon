#include "RTColorWidget.hh"

#include "./ui_RTColorWidget.h"

namespace
{
  void populateColors(QComboBox* colorComboBox)
  {
    for (auto&& colors : Rayon::namedColors())
    {
      colorComboBox->addItem(colors.first.c_str());
    }

    colorComboBox->addItem("Custom");
  }

  void setCustomText(Ui::RTColorWidget* ui)
  {
    ui->colorComboBox->blockSignals(true);
    ui->colorComboBox->setCurrentText("Custom");
    ui->colorComboBox->blockSignals(false);
  }

  void setRGB(Ui::RTColorWidget* ui, const Rayon::Color& color)
  {
    ui->redSpinBox->blockSignals(true);
    ui->redSpinBox->setValue(color.red());
    ui->redSpinBox->blockSignals(false);

    ui->greenSpinBox->blockSignals(true);
    ui->greenSpinBox->setValue(color.green());
    ui->greenSpinBox->blockSignals(false);

    ui->blueSpinBox->blockSignals(true);
    ui->blueSpinBox->setValue(color.blue());
    ui->blueSpinBox->blockSignals(false);
  }

  void setHex(Ui::RTColorWidget* ui, const Rayon::Color& color)
  {
    ui->hexInput->blockSignals(true);
    ui->hexInput->setText(
      "0x" + QString("%1").arg(color.intValue() & 0xffffff, 6, 16, QChar('0')).toUpper());
    ui->hexInput->blockSignals(false);
  }
}  // namespace

RTColorWidget::RTColorWidget(QWidget* parent) : QWidget(parent), ui(new Ui::RTColorWidget)
{
  ui->setupUi(this);
  populateColors(ui->colorComboBox);
}

RTColorWidget::~RTColorWidget()
{
  delete ui;
}

void RTColorWidget::colorStringChanged(const QString& newColor)
{
  auto colorStr = newColor.toStdString();

  if (Rayon::namedColors().count(colorStr))
  {
    _color = Rayon::namedColors().at(colorStr);

    setRGB(ui, _color);
    setHex(ui, _color);

    emit colorChanged(_color);
  }
}

void RTColorWidget::hexChanged(const QString& newHex)
{
  _color = newHex.toUInt(nullptr, 16);

  setCustomText(ui);
  setRGB(ui, _color);

  emit colorChanged(_color);
}

void RTColorWidget::redChanged(int newRed)
{
  _color.setRed(newRed);

  setCustomText(ui);
  setHex(ui, _color);

  emit colorChanged(_color);
}

void RTColorWidget::greenChanged(int newGreen)
{
  _color.setGreen(newGreen);

  setCustomText(ui);
  setHex(ui, _color);

  emit colorChanged(_color);
}

void RTColorWidget::blueChanged(int newBlue)
{
  _color.setBlue(newBlue);

  setCustomText(ui);
  setHex(ui, _color);

  emit colorChanged(_color);
}
