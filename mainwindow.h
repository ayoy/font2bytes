#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "conversionconfig.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void updateConfig();
    void validateTextFieldInput();
    void loadImageFile(const QUrl &url);

private:
    Ui::MainWindow *ui;
    ConversionConfig config;

    void applyCurrentConfig();
};

#endif // MAINWINDOW_H
