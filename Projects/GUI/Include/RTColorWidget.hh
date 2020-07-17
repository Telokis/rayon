#ifndef RT_COLOR_WIDGET_HH
#define RT_COLOR_WIDGET_HH

#include <QWidget>

#include "Color.hh"

QT_BEGIN_NAMESPACE
namespace Ui
{
  class RTColorWidget;
}
QT_END_NAMESPACE

class RTColorWidget : public QWidget
{
  Q_OBJECT

public:
  RTColorWidget(QWidget* parent = nullptr);
  ~RTColorWidget();

private:
  void refreshRender();

signals:
  void colorChanged(const Rayon::Color& newColor);

public slots:
  void hexChanged(const QString& newHex);
  void colorStringChanged(const QString& newColor);
  void redChanged(int newRed);
  void greenChanged(int newGreen);
  void blueChanged(int newBlue);

private:
  Ui::RTColorWidget* ui;
  Rayon::Color       _color;
};
#endif  // RT_COLOR_WIDGET_HH
