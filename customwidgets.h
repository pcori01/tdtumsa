#ifndef CUSTOMWIDGETS_H
#define CUSTOMWIDGETS_H

#include "hexspinbox.h"

/**
 * @brief
 *
 */
class LabelHexSpinBox : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int value READ Value WRITE setValue NOTIFY valueChanged)

public:

    /**
     * @brief
     *
     * @param parent
     * @param text
     * @param valuetype
     */
    LabelHexSpinBox(QWidget *parent = nullptr,QString text=nullptr,int valuetype=0);
    /**
     * @brief
     *
     * @param int
     * @param int
     */
    void setRange(int,unsigned int);
    const static int HEXSPINBOX = 0; /**< TODO: describe */
    const static int SPINBOX = 1; /**< TODO: describe */
    /**
     * @brief
     *
     * @return int
     */
    int Value() const {
        return m_value;
    }

private:

    int m_value=0; /**< TODO: describe */
    int type=0; /**< TODO: describe */
    QLabel *m_Label; /**< TODO: describe */
    HexSpinBox *m_HexSpinBox; /**< TODO: describe */
    QSpinBox *m_QSpinBox;
    QHBoxLayout *m_HBoxLayout;

signals:
    /**
     * @brief
     *
     * @param int
     */
    void valueChanged(int);

public slots:
    /**
     * @brief
     *
     * @param value
     */
    void setValue(int value)
    {
        if(m_value!=value){
            m_value = value;
            (type==0)?m_HexSpinBox->setValue(value):m_QSpinBox->setValue(value);
            emit valueChanged(value);
        }
    }

};

/**
 * @brief
 *
 */
class LabelLineEdit : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString text READ Text WRITE setText NOTIFY textChanged)

public:

    /**
     * @brief
     *
     * @param parent
     * @param text
     */
    LabelLineEdit(QWidget *parent = nullptr,QString text=nullptr);

    /**
     * @brief
     *
     * @return QString
     */
    QString Text() const
    {
        return m_text;
    }


private:

    QString m_text; /**< TODO: describe */

    QLabel *m_Label; /**< TODO: describe */
    QLineEdit *m_LineEdit; /**< TODO: describe */
    QHBoxLayout *m_HBoxLayout;

signals:
    /**
     * @brief
     *
     * @param QString
     */
    void textChanged(QString);

public slots:
    /**
     * @brief
     *
     * @param text
     */
    void setText(QString text)
    {
        if(m_text!=text){
            m_text = text;
            m_LineEdit->setText(text);
            emit textChanged(text);
        }
    }
    void setLength(int length);

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

/**
 * @brief
 *
 */
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

/**
 * @brief
 *
 */
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

/**
 * @brief
 *
 */
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
    QStringList m_QStringList; /**< TODO: describe */
};


#endif // CUSTOMWIDGETS_H
