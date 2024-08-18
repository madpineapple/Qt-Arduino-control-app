#ifndef WIDGET_H
#define WIDGET_H
#include <QSerialPort>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_onButton_clicked();
    void on_offButton_clicked();
    void update_lights(QString);

private:
    Ui::Widget *ui;
    QSerialPort *arduino;
    static const quint16 arduinoUnoVendorID = 9025;
    static const quint16 arduinoUnoProductID = 67;
    QString arduinoPortName;
    bool arduinoIsAvailable;

};
#endif // WIDGET_H
