#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "conversionconfig.h"
#include <functional>
#include <QElapsedTimer>

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
    void imageConverted(const QString &sourceCode, const ConverterError &error);
    void setDropActionAvailable(bool available);

private:
    enum StackedWidgetPage { InfoLabel = 0, PromptLabel = 1, TextBrowser = 2 };
    void applyCurrentConfig();
    void setupSourceCodeGenerators();
    void shake(QWidget *widget);

    Ui::MainWindow *ui;
    ConversionConfig config;
    bool dropActionHidesTextBrowser { false };
    ConversionRunnable *conversion { nullptr };
    QList<SourceCodeGeneratorItem> generators;
    QElapsedTimer conversionTimer;
    QTimer *statusBarTimer { nullptr };
};

#endif // MAINWINDOW_H
