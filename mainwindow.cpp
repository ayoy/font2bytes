#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "conversionrunnable.h"
#include <QDebug>
#include <QThreadPool>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->widthLineEdit, SIGNAL(editingFinished()), this, SLOT(validateTextFieldInput()));
    connect(ui->heightLineEdit, SIGNAL(editingFinished()), this, SLOT(validateTextFieldInput()));

    connect(ui->topBottomRadioButton, SIGNAL(clicked(bool)), this, SLOT(updateConfig()));
    connect(ui->invertBitsCheckBox, SIGNAL(clicked(bool)), this, SLOT(updateConfig()));
    connect(ui->bitNumberingCheckBox, SIGNAL(clicked(bool)), this, SLOT(updateConfig()));

    connect(ui->stackedWidget, SIGNAL(dropActionAvailableChanged(bool)), ui->promptLabel, SLOT(setDropActionAvailable(bool)));
    connect(ui->stackedWidget, SIGNAL(imageFileDropped(QUrl)), this, SLOT(loadImageFile(QUrl)));

    config.loadFromSettings();
}

MainWindow::~MainWindow()
{
    if (conversion && !conversion->isFinished()) {
        conversion->setCanceled(true);
        conversion = nullptr;
    }
    delete ui;
}

void MainWindow::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    applyCurrentConfig();
}

void MainWindow::updateConfig()
{
    bool converted = false;
    int intValue = ui->widthLineEdit->text().toInt(&converted);
    config.fontWidth = converted ? (uint8_t)intValue : 0;

    converted = false;
    intValue = ui->heightLineEdit->text().toInt(&converted);
    config.fontHeight = converted ? (uint8_t)intValue : 0;

    config.readingMode = ui->topBottomRadioButton->isChecked() ?
                ConversionConfig::ReadingMode::TopToBottom :
                ConversionConfig::ReadingMode::LeftToRight;

    config.shouldInvertBits = ui->invertBitsCheckBox->isChecked();

    config.bitNumbering = ui->bitNumberingCheckBox->isChecked() ?
                ConversionConfig::BitNumbering::MSB :
                ConversionConfig::BitNumbering::LSB;

    config.saveToSettings();
}

void MainWindow::validateTextFieldInput()
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit *>(sender());

    bool converted = false;
    int intValue = lineEdit->text().toInt(&converted);

    if (converted) {
        intValue = qMax(intValue, 8);
        intValue = qMin(intValue, 255);
        lineEdit->setText(QString::number(intValue));
    } else {
        lineEdit->setText(nullptr);
    }

    updateConfig();
    applyCurrentConfig();
}

void MainWindow::applyCurrentConfig()
{
    if (config.isValid()) {
        ui->promptLabel->setText(tr("Drop your\nPNG file here!"));
    } else {
        ui->promptLabel->setText(tr("First, set up font conversion parameters\non the left."));
    }

    QString fontString = config.isWidthValid() ? QString::number(config.fontWidth) : "";
    ui->widthLineEdit->setText(fontString);
    fontString = config.isHeightValid() ? QString::number(config.fontHeight) : "";
    ui->heightLineEdit->setText(fontString);

    switch (config.readingMode) {
    case ConversionConfig::ReadingMode::TopToBottom:
        ui->topBottomRadioButton->setChecked(true);
        break;
    case ConversionConfig::ReadingMode::LeftToRight:
        ui->leftRightRadioButton->setChecked(true);
        break;
    }

    ui->invertBitsCheckBox->setChecked(config.shouldInvertBits);
    ui->bitNumberingCheckBox->setChecked(config.bitNumbering == ConversionConfig::BitNumbering::MSB);
}

void MainWindow::loadImageFile(const QUrl &url)
{
    QImage image(url.path());
    if (image.isNull()) {
        qDebug() << "image is null ._.";
    } else {
        qDebug() << image.size();
        if (conversion && !conversion->isFinished()) {
            conversion->setCanceled(true);
        }

        conversion = new ConversionRunnable();
        conversion->imageConverter()->setConfig(config);
        conversion->imageConverter()->setImage(image);

        connect(conversion->imageConverter(), SIGNAL(conversionFinished()),
                this, SLOT(imageConverted()),
                Qt::BlockingQueuedConnection);

        QThreadPool::globalInstance()->start(conversion);
    }
}

void MainWindow::imageConverted()
{
    Q_ASSERT(conversion->isFinished());
    qDebug() << __PRETTY_FUNCTION__;

    conversion = nullptr;
}
