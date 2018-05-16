#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "conversionconfig.h"

class QIntValidator;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void updateConfig();
    void validateTextFieldInput();

private:
    Ui::MainWindow *ui;
    ConversionConfig config;

    void applyCurrentConfig();
};

#endif // MAINWINDOW_H
