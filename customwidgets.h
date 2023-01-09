#ifndef CUSTOMWIDGETS_H
#define CUSTOMWIDGETS_H

//#include <QWidget>
#include <QtWidgets>
#include "hexspinbox.h"

class LabelHexSpinBox : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int value READ Value WRITE setValue NOTIFY valueChanged)

public:

    LabelHexSpinBox(QWidget *parent = nullptr,QString text=nullptr);
    void setRange(int,int);

    int Value() const {
        return m_value;
    }

private:

    int m_value=0;
    QLabel *m_Label; /**< TODO: describe */
    HexSpinBox *m_HexSpinBox; /**< TODO: describe */
    QHBoxLayout *m_HBoxLayout;

signals:
    void valueChanged(int);

public slots:
    void setValue(int value)
    {
        if(m_value!=value){
            m_value = value;
            m_HexSpinBox->setValue(value);
            emit valueChanged(value);
        }
    }

};

class LabelLineEdit : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString text READ Text WRITE setText NOTIFY textChanged)

public:

    LabelLineEdit(QWidget *parent = nullptr,QString text=nullptr);

    QString Text() const
    {
        return m_text;
    }

private:

    QString m_text;

    QLabel *m_Label; /**< TODO: describe */
    QLineEdit *m_LineEdit; /**< TODO: describe */
    QHBoxLayout *m_HBoxLayout;

signals:
    void textChanged(QString);

public slots:
    void setText(QString text)
    {
        if(m_text!=text){
            m_text = text;
            m_LineEdit->setText(text);
            emit textChanged(text);
        }
    }

};


/**
 * @brief
 * Definimos la clase principal para el Wizard
 */

class SectionDescriptor : public QGroupBox
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     * @param parent
     */
    SectionDescriptor(QWidget *parent = nullptr,QString text=nullptr);
    /**
     * @brief
     *
     */

public slots:
    /**
     * @brief
     *
     */
private:

    QHBoxLayout *m_HBoxLayout; /**< TODO: describe */
    QGroupBox *m_GroupBox; /**< TODO: describe */

};

class SectionLoop : public QGroupBox
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     * @param parent
     */
    SectionLoop(QWidget *parent = nullptr,QString text=nullptr);
    /**
     * @brief
     *
     */
public slots:
    /**
     * @brief
     *
     */
private:

    QVBoxLayout *m_VBoxLayout; /**< TODO: describe */
    QGroupBox *m_GroupBox; /**< TODO: describe */

};

class ElementSectionDescriptor : public virtual QWidget
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     * @param parent
     */
    ElementSectionDescriptor(QWidget *parent = nullptr);
    /**
     * @brief
     *
     */
public slots:
    /**
     * @brief
     *
     */

private:
    QHBoxLayout *m_HBoxLayout;
};

class ElementDescriptor : public virtual QWidget
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     * @param parent
     */
    ElementDescriptor(QWidget *parent = nullptr, QStringList *StringList= nullptr);
    /**
     * @brief
     *
     */
public slots:
    /**
     * @brief
     *
     */

private:
    QHBoxLayout *m_HBoxLayout;
    QStringList m_QStringList;
};


#endif // CUSTOMWIDGETS_H
