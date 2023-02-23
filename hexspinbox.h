#ifndef HEXSPINBOX_H
#define HEXSPINBOX_H

#include <QtWidgets>

QT_BEGIN_NAMESPACE
class QSpinBox;
QT_END_NAMESPACE

class QRegExpValidator;


/**
 * @brief
 * SpinBox Personalizado para usar numeros Hexadecimales
 */
class HexSpinBox : public QSpinBox
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     * @param parent
     */
    HexSpinBox(QWidget *parent = nullptr);
    void setMAXRange(unsigned int max);

protected:
    /**
     * @brief
     *
     * @param text
     * @param pos
     * @return QValidator::State
     */
    QValidator::State validate(QString &text, int &pos) const;
    /**
     * @brief
     *
     * @param text
     * @return int
     */
    int valueFromText(const QString &text) const;
    /**
     * @brief
     *
     * @param value
     * @return QString
     */
    QString textFromValue(int value) const;

private:
    QRegExpValidator *validator; /**< TODO: describe */
    unsigned int m_maxRange = UINT_MAX;
};

#endif // HEXSPINBOX_H
