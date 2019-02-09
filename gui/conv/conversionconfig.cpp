#include "conversionconfig.h"
#include <QSettings>

static const QString SettingsFontWidthKey = "fontWidth";
static const QString SettingsFontHeightKey = "fontHeight";
static const QString SettingsReadingModeKey = "readingMode";
static const QString SettingsShouldInvertBitsKey = "shouldInvertBits";
static const QString SettingsBitNumberingKey = "bitNumbering";
static const QString SettingsSourceCodeGeneratorIndexKey = "sourceCodeGeneratorIndex";

void ConversionConfig::loadFromSettings()
{
    QSettings settings;
    settings.sync();
    fontWidth = settings.value(SettingsFontWidthKey, 0).toUInt();
    fontHeight = settings.value(SettingsFontHeightKey, 0).toUInt();
    readingMode = static_cast<FixedConverter::ReadingMode>(
                settings.value(SettingsReadingModeKey, FixedConverter::TopToBottom).toUInt());
    shouldInvertBits = settings.value(SettingsShouldInvertBitsKey, false).toBool();
    bitNumbering = static_cast<SourceCodeOptions::BitNumbering>(
                settings.value(SettingsBitNumberingKey, SourceCodeOptions::LSB).toUInt());
    sourceCodeGeneratorIndex = settings.value(SettingsSourceCodeGeneratorIndexKey, 0).toInt();
}

void ConversionConfig::saveToSettings() const
{
    QSettings settings;
    settings.setValue(SettingsFontWidthKey, fontWidth);
    settings.setValue(SettingsFontHeightKey, fontHeight);
    settings.setValue(SettingsReadingModeKey, readingMode);
    settings.setValue(SettingsShouldInvertBitsKey, shouldInvertBits);
    settings.setValue(SettingsBitNumberingKey, bitNumbering);
    settings.setValue(SettingsSourceCodeGeneratorIndexKey, sourceCodeGeneratorIndex);
    settings.sync();
}
