#include "hexspinbox.h"

HexSpinBox::HexSpinBox(QWidget *parent)
    : QSpinBox(parent)
{
    setRange(0,65535);
    setMaximumWidth(80);
    //validator = new QRegExpValidator(QRegExp("[0-9A-Fa-f]{1,8}"), this);
    validator = new QRegExpValidator(QRegExp("(?:0[xX])?[0-9A-Fa-f]{1,8}"), this);
    setPrefix("0x");
}

QValidator::State HexSpinBox::validate(QString &text, int &pos) const
{
    return validator->validate(text, pos);
}

int HexSpinBox::valueFromText(const QString &text) const
{
    bool ok;
    return text.toInt(&ok, 16);
}

QString HexSpinBox::textFromValue(int value) const
{
    return QString::number(value, 16).toUpper();
}
