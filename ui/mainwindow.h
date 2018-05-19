#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "conversionconfig.h"
#include <functional>

class QThreadPool;
class ConversionRunnable;

namespace Ui {
class MainWindow;
}

struct SourceCodeGeneratorItem {
    QString title;
    std::function<SourceCodeGenerator * ()> createGenerator;
};

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
    void imageConverted();
    void setDropActionAvailable(bool available);

private:
    enum StackedWidgetPage { PromptLabel = 0, TextBrowser = 1 };

    Ui::MainWindow *ui;
    ConversionConfig config;
    bool dropActionHidesTextBrowser { false };
    ConversionRunnable *conversion { nullptr };
    QList<SourceCodeGeneratorItem> generators;

    void applyCurrentConfig();
    void setupSourceCodeGenerators();
};

#endif // MAINWINDOW_H
