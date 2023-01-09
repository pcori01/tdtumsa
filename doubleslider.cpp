#include "doubleslider.h"

DoubleSlider::DoubleSlider(QWidget *parent)
    : QSlider(parent)
{
    setMaximumWidth(100);
    //setSingleStep(1);
    setOrientation(Qt::Horizontal);
}
