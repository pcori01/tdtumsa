#include "customwidgets.h"

LabelHexSpinBox::LabelHexSpinBox(QWidget *parent, QString text, int value) : QWidget(parent)
{
    type = value;
    m_Label= new QLabel(text);
    (type==0)?m_HexSpinBox = new HexSpinBox:m_QSpinBox = new QSpinBox;
    m_Label->setBuddy((type==0)?m_HexSpinBox:m_QSpinBox);
    m_HBoxLayout= new QHBoxLayout;
    m_HBoxLayout->setSizeConstraint(QLayout::SetFixedSize);
    m_HBoxLayout->addWidget(m_Label);
    m_HBoxLayout->addWidget((type==0)?m_HexSpinBox:m_QSpinBox);
    (type==0)?connect(m_HexSpinBox,SIGNAL(valueChanged(int)),this,SLOT(setValue(int))):
               connect(m_QSpinBox,SIGNAL(valueChanged(int)),this,SLOT(setValue(int)));
    (type==0)?connect(this,SIGNAL(valueChanged(int)),m_HexSpinBox,SLOT(setValue(int))):
                connect(this,SIGNAL(valueChanged(int)),m_QSpinBox,SLOT(setValue(int)));
    this->setLayout(m_HBoxLayout);
}
void LabelHexSpinBox::setRange(int value1,int value2)
{
    (type==0)?m_HexSpinBox->setRange(value1,value2):m_QSpinBox->setRange(value1,value2);
}

SectionDescriptor::SectionDescriptor(QWidget *parent, QString text)
    : QGroupBox(parent)
{
    this->setTitle(text);
    m_HBoxLayout= new QHBoxLayout;
    m_HBoxLayout->setSizeConstraint(QLayout::SetFixedSize);
    this->setLayout(m_HBoxLayout);
}

SectionLoop::SectionLoop(QWidget *parent, QString text)
    : QGroupBox(parent)
{

    this->setTitle(text);
    m_VBoxLayout= new QVBoxLayout;
    m_VBoxLayout->setSizeConstraint(QLayout::SetFixedSize);
    this->setLayout(m_VBoxLayout);
}

ElementSectionDescriptor::ElementSectionDescriptor(QWidget *parent)
    : QWidget(parent)
{
    m_HBoxLayout = new QHBoxLayout;
    m_HBoxLayout->setSizeConstraint(QLayout::SetFixedSize);
    this->setLayout(m_HBoxLayout);
}

ElementDescriptor::ElementDescriptor(QWidget *parent, QStringList *StringList)
    : QWidget(parent)
{

    m_HBoxLayout = new QHBoxLayout;
    m_HBoxLayout->setSizeConstraint(QLayout::SetFixedSize);
    this->setLayout(m_HBoxLayout);

    m_QStringList=*StringList;

    if(StringList->size()>2)
    {
       foreach (QString string, m_QStringList) {
        qDebug()<<string<<m_QStringList.size();
        m_HBoxLayout->addWidget(new QLabel(string));
        m_HBoxLayout->addWidget(new HexSpinBox);
        }
    }
}

LabelLineEdit::LabelLineEdit(QWidget *parent, QString text)
 : QWidget(parent)
{
    m_Label = new QLabel(text);
    m_LineEdit = new QLineEdit;
    m_Label->setBuddy(m_LineEdit);
    m_HBoxLayout = new QHBoxLayout;
    m_HBoxLayout->setSizeConstraint(QLayout::SetFixedSize);
    m_HBoxLayout->addWidget(m_Label);
    m_HBoxLayout->addWidget(m_LineEdit);
    connect(m_LineEdit,SIGNAL(textChanged(QString)),this,SLOT(setText(QString)));
    connect(this,SIGNAL(textChanged(QString)),m_LineEdit,SLOT(setText(QString)));

    this->setLayout(m_HBoxLayout);
}

