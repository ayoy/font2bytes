#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "conversionconfig.h"
#include <functional>
#include <QElapsedTimer>

class ConversionService;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();


protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void imageConverted(const QString &sourceCode, const ConverterError &error, qint64 elapsedTime);
    void updateConfig();
    void validateTextFieldInput();
    void loadImageFile(const QUrl &url);
    void setDropActionAvailable(bool available);
    void copyToClipboard();
    void openSaveDialog();

private:
    enum StackedWidgetPage { InfoLabel = 0, PromptLabel = 1, TextBrowser = 2 };
    void applyConfig(ConversionConfig config);
    void setupSourceCodeGenerators();
    void shake(QWidget *widget);

    Ui::MainWindow *ui;
    ConversionService *conversionService { nullptr };
    bool dropActionHidesTextBrowser { false };
};

#endif // MAINWINDOW_H
