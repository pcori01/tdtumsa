#ifndef DOUBLESLIDER_H
#define DOUBLESLIDER_H

#include <QtWidgets>

/**
 * @brief
 *
 * Slider Personalizado para manejar variables "Double".
 */
class DoubleSlider : public QSlider
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     * @param parent
     */
    DoubleSlider(QWidget *parent = nullptr);

signals:
    /**
     * @brief
     *
     * @param value
     */
    void doubleValueChanged(double value);
    /**
     * @brief
     *
     * @param value
     */
    void intValueChanged(int value);

public slots:
    /**
     * @brief
     *
     * @param value
     */
    void notifyValueChanged(int value) {
    double doubleValue = (QVariant(value).toDouble() / 10.0);
    emit doubleValueChanged(doubleValue);
     }
    /**
     * @brief
     *
     * @param value
     */
    void notifydoubleChanged(double value) {
    int intValue = QVariant(value*10.0).toInt();
    emit intValueChanged(intValue);
     }
};

#endif // DOUBLESLIDER_H
