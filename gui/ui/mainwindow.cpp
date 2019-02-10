#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "conversionservice.h"
#include "conversionrunnable.h"
#include "shakeanimation.h"
#include <f2b.h>
#include <QDebug>
#include <QThreadPool>
#include <QFontDatabase>
#include <QElapsedTimer>
#include <QClipboard>
#include <QFileDialog>
#include <QSaveFile>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui { new Ui::MainWindow },
    conversionService { new ConversionService(this) }
{
    ui->setupUi(this);

    for (auto generatorItem : conversionService->generators()) {
        ui->formatComboBox->addItem(generatorItem.title);
    }

    QFont fixedFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    fixedFont.setPixelSize(13);
    ui->textBrowser->setFont(fixedFont);
    QFont infoFont = ui->infoLabel->font();
    infoFont.setPixelSize(32);
    ui->infoLabel->setFont(infoFont);

    connect(ui->widthLineEdit, SIGNAL(editingFinished()), this, SLOT(validateTextFieldInput()));
    connect(ui->heightLineEdit, SIGNAL(editingFinished()), this, SLOT(validateTextFieldInput()));

    connect(ui->topBottomRadioButton, SIGNAL(clicked(bool)), this, SLOT(updateConfig()));
    connect(ui->invertBitsCheckBox, SIGNAL(clicked(bool)), this, SLOT(updateConfig()));
    connect(ui->bitNumberingCheckBox, SIGNAL(clicked(bool)), this, SLOT(updateConfig()));
    connect(ui->formatComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateConfig()));

    connect(ui->stackedWidget, SIGNAL(dropActionAvailableChanged(bool)), this, SLOT(setDropActionAvailable(bool)));
    connect(ui->stackedWidget, SIGNAL(imageFileDropped(QUrl)), this, SLOT(loadImageFile(QUrl)));

    connect(ui->copyButton, SIGNAL(clicked(bool)), this, SLOT(copyToClipboard()));
    connect(ui->saveAsButton, SIGNAL(clicked(bool)), this, SLOT(openSaveDialog()));

    connect(conversionService, SIGNAL(conversionComplete(QString,ConverterError,qint64)),
            this, SLOT(imageConverted(QString,ConverterError,qint64)));
}

MainWindow::~MainWindow()
{
    if (ui != nullptr) {
        delete ui;
        ui = nullptr;
    }
}


void MainWindow::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    applyConfig(conversionService->config());
}

void MainWindow::updateConfig()
{
    ConversionConfig config;

    bool converted = false;
    int intValue = ui->widthLineEdit->text().toInt(&converted);
    config.fontWidth = converted ? (uint8_t)intValue : 0;

    converted = false;
    intValue = ui->heightLineEdit->text().toInt(&converted);
    config.fontHeight = converted ? (uint8_t)intValue : 0;

    config.readingMode = ui->topBottomRadioButton->isChecked() ?
                FixedWidthFontConverter::TopToBottom :
                FixedWidthFontConverter::LeftToRight;

    config.shouldInvertBits = ui->invertBitsCheckBox->isChecked();

    config.bitNumbering = ui->bitNumberingCheckBox->isChecked() ?
                SourceCodeOptions::MSB :
                SourceCodeOptions::LSB;

    config.sourceCodeGeneratorIndex = ui->formatComboBox->currentIndex();

    conversionService->setConfig(config);
}

void MainWindow::validateTextFieldInput()
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit *>(sender());

    bool converted = false;
    int intValue = lineEdit->text().toInt(&converted);

    if (converted) {
        intValue = qMax(intValue, 1);
        intValue = qMin(intValue, 255);
        lineEdit->setText(QString::number(intValue));
    } else {
        lineEdit->setText(nullptr);
    }

    updateConfig();
    applyConfig(conversionService->config());
}

void MainWindow::applyConfig(ConversionConfig config)
{
    if (ui->stackedWidget->currentIndex() != TextBrowser) {
        if (config.isValid()) {
            ui->stackedWidget->setCurrentIndex(PromptLabel);
        } else {
            ui->stackedWidget->setCurrentIndex(InfoLabel);
        }
    }
    ui->stackedWidget->setAcceptDrops(config.isValid());

    QString fontString = config.isWidthValid() ? QString::number(config.fontWidth) : "";
    ui->widthLineEdit->setText(fontString);
    fontString = config.isHeightValid() ? QString::number(config.fontHeight) : "";
    ui->heightLineEdit->setText(fontString);

    switch (config.readingMode) {
    case FixedWidthFontConverter::TopToBottom:
        ui->topBottomRadioButton->setChecked(true);
        break;
    case FixedWidthFontConverter::LeftToRight:
        ui->leftRightRadioButton->setChecked(true);
        break;
    }

    ui->invertBitsCheckBox->setChecked(config.shouldInvertBits);
    ui->bitNumberingCheckBox->setChecked(config.bitNumbering == SourceCodeOptions::MSB);

    if (config.sourceCodeGeneratorIndex < ui->formatComboBox->count()
            and config.sourceCodeGeneratorIndex > 0)
    {
        ui->formatComboBox->setCurrentIndex(config.sourceCodeGeneratorIndex);
    }
}

void MainWindow::setDropActionAvailable(bool available)
{
    ui->promptLabel->setDropActionAvailable(available);
    if (available and ui->stackedWidget->currentIndex() == TextBrowser) {
        dropActionHidesTextBrowser = true;
        ui->stackedWidget->setCurrentIndex(PromptLabel);
    } else if (!available and dropActionHidesTextBrowser) {
        dropActionHidesTextBrowser = false;
        ui->stackedWidget->setCurrentIndex(TextBrowser);
    }
}

void MainWindow::loadImageFile(const QUrl &url)
{
    QImage image(url.path());
    if (image.isNull()) {
        ShakeAnimation *shakeAnimation = new ShakeAnimation(ui->promptLabel);
        shakeAnimation->start(ShakeAnimation::DeleteWhenStopped);
        ui->statusBar->showMessage(tr("Couldn't read image from provided file"), Qt::darkRed, 5000);
    } else {
        auto generator = conversionService->generators().at(ui->formatComboBox->currentIndex());
        conversionService->convert(image, generator);
    }
}

void MainWindow::imageConverted(const QString &sourceCode, const ConverterError &error, qint64 elapsedTime)
{
    if (error == ConverterError::NoError) {
        ui->statusBar->showMessage(tr("%1x%2 font generated in %3ms")
                                   .arg(QString::number(conversionService->config().fontHeight),
                                        QString::number(conversionService->config().fontWidth),
                                        QString::number(elapsedTime)));

        ui->stackedWidget->setCurrentIndex(TextBrowser);
        ui->textBrowser->setText(sourceCode);
    } else {
        ShakeAnimation *shakeAnimation = new ShakeAnimation(ui->promptLabel);
        shakeAnimation->start(ShakeAnimation::DeleteWhenStopped);
        ui->statusBar->showMessage(QString::fromStdString(error.description), Qt::darkRed, 5000);
    }
}

void MainWindow::copyToClipboard()
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(ui->textBrowser->toPlainText());
    ui->statusBar->showMessage(tr("Source code copied to clipboard."), 3000);
}

void MainWindow::openSaveDialog()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As..."), QDir::homePath());
    QSaveFile *file = new QSaveFile(fileName);
    if (!file->open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::critical(this, tr("Save As"),
                              tr("Couldn't access file at \"%1\": %2").arg(fileName, file->errorString()));
        ui->statusBar->showMessage(tr("Failed to save source code to file."), Qt::darkRed, 5000);
    } else {

        bool writeSuccessful = file->write(ui->textBrowser->toPlainText().toUtf8()) != -1;

        if (!writeSuccessful) {
            QMessageBox::critical(this, tr("Save As"),
                                  tr("Couldn't write to file at \"%1\": %2").arg(fileName, file->errorString()));
            ui->statusBar->showMessage(tr("Failed to save source code to file."), Qt::darkRed, 5000);
        }

        bool saveSuccessful = file->commit();

        if (saveSuccessful) {
            ui->statusBar->showMessage(tr("Saved source code to file at \"%1\".").arg(fileName), Qt::darkGreen, 5000);
        } else {
            QMessageBox::critical(this, tr("Save As"),
                                  tr("Couldn't save file at \"%1\": %2").arg(fileName, file->errorString()));
            ui->statusBar->showMessage(tr("Failed to save source code to file."), Qt::darkRed, 5000);
        }
    }
}
