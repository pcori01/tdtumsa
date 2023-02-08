#ifndef TVDUMSA_H
#define TVDUMSA_H

#include <QWizard>
#include <QtWidgets>
#include <QVariant>
#include <QDate>
#include <QTime>
//#include <QDomDocument>
//#include <QXmlStreamWriter>
//#include <QMap>
//#include <QScrollArea>
//#include "BasicXMLSyntaxHighlighter.h"
#include "KickPythonSyntaxHighlighter.h"
#include "hexspinbox.h"
#include "doubleslider.h"
#include "customwidgets.h"

QT_BEGIN_NAMESPACE
class QCheckBox;
class QLabel;
class QLineEdit;
class QRadioButton;
class QTabWidget;
class QGridLayout;
class QPushButton;
class QSlider;
class QFileDialog;
class QDoubleSpinBox;
class QSpinBox;
class QComboBox;
class QGroupBox;
class QSpacerItem;

QT_END_NAMESPACE

class QRegExpValidator;

class Tdtumsa : public QWizard
{
    //Averiguar Que hace
    Q_OBJECT

public:
    /**
     * @brief
     * Definimos las paginas a ser deplegadas por el Wizard
     */
    enum page { Page_Intro, Page_Plan, Page_Code, Page_Mux, Page_Tx,
           Page_Final };

    /**
     * @brief
     * Definimos la Interfaz del tipo widget
     * @param parent
     */
    Tdtumsa(QWidget *parent = nullptr);
};

/**
 * @brief
 *
 */
class IntroPage : public QWizardPage
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     * @param parent
     */
    IntroPage(QWidget *parent = nullptr);
    /**
     * @brief
     *
     * @return int
     */
    int nextId() const override;
    /**
     * @brief
     *
     */
    void initializePage() override;

private:
    QLabel *PresentationLabel; /**< TODO: describe */

};

/**
 * @brief
 *
 */
class PlanPage : public QWizardPage
{
    Q_OBJECT
    Q_PROPERTY(int indexPlan READ priorityChanged WRITE setPriority)
    Q_PROPERTY(int SevicesPlan READ SevicesPlan WRITE setSevicesPlan)


public:
    /**
     * @brief
     *
     * @param parent
     */
    PlanPage(QWidget *parent = nullptr);
    /**
     * @brief
     *
     */
    void cleanupPage() override;
    /**
     * @brief
     *
     */
    void initializePage() override;

    /**
     * @brief
     *
     * @return int
     */
    int nextId() const override;

    bool validatePage() override;

    void setPriority(int priority)
    {
        IndexP = priority;
    }
    /**
     * @brief
     *
     * @return QMap<QString, QVariant>
     */
    int priorityChanged(void)
    {
        return IndexP;
    }

    void setSevicesPlan(int value)
    {
        m_SevicesPlan = value;
    }
    /**
     * @brief
     *
     * @return QMap<QString, QVariant>
     */
    int SevicesPlan(void)
    {
        return m_SevicesPlan;
    }


private:
    QLabel *descriptionLabel; /**< TODO: describe */
    QLabel *optionLabel[4];
    QCheckBox *OneSegCheckBox;
    QRadioButton *optionRadioButton[4];
    int IndexP;
    int m_SevicesPlan;
    QWidget *services;

};

/**
 * @brief
 *
 */
class CodePage : public QWizardPage
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     * @param parent
     */
    CodePage(QWidget *parent = nullptr);
    /**
     * @brief
     *
     */
    void initializePage() override;
    /**
     * @brief
     *
     * @return int
     */
    int nextId() const override;
    /**
     * @brief
     *
     */
    void cleanupPage() override;
    bool validatePage() override;

    QTabWidget *CodeTab; /**< TODO: describe */
    QGridLayout *layoutTab[5]; /**< TODO: describe */
    QWidget *tabWidget[5]; /**< TODO: describe */
    QLabel *videoLabel[5]; /**< TODO: describe */
    QLineEdit *videoLineEdit[5]; /**< TODO: describe */
    QPushButton *videoButton[5]; /**< TODO: describe */
    QLabel *videoBitrateLabel[5]; /**< TODO: describe */

    QGroupBox *File[5]; /**< TODO: describe */
    QGridLayout *Filelayout[5]; /**< TODO: describe */

    QGroupBox *Video[5]; /**< TODO: describe */
    QGridLayout *Videolayout[5]; /**< TODO: describe */

    DoubleSlider *videoSlider[5]; /**< TODO: describe */
    QDoubleSpinBox *videoSpinBox[5]; /**< TODO: describe */
    QLabel *vResolutionLabel[5]; /**< TODO: describe */
    QComboBox *vResolutionComboBox[5]; /**< TODO: describe */
    QLabel *videoFPSLabel[5]; /**< TODO: describe */
    QComboBox *videoFPSComboBox[5]; /**< TODO: describe */
    QLabel *videoRALabel[5]; /**< TODO: describe */
    QComboBox *videoRAComboBox[5]; /**< TODO: describe */
    QLabel *videoPerfilLabel[5]; /**< TODO: describe */
    QComboBox *videoPerfilComboBox[5]; /**< TODO: describe */
    QLabel *videoNivelLabel[5]; /**< TODO: describe */
    QComboBox *videoNivelComboBox[5]; /**< TODO: describe */

    QGroupBox *Audio[5]; /**< TODO: describe */
    QGridLayout *Audiolayout[5]; /**< TODO: describe */

    QLabel *audioBitrateLabel[5]; /**< TODO: describe */
    QSlider *audioSlider[5]; /**< TODO: describe */
    QSpinBox *audioSpinBox[5]; /**< TODO: describe */
    QLabel *aSampleRateLabel[5]; /**< TODO: describe */
    QComboBox *aSampleRateComboBox[5]; /**< TODO: describe */
    QLabel *aChanelsLabel[5]; /**< TODO: describe */
    QComboBox *aChanelsComboBox[5]; /**< TODO: describe */
    QLabel *aCodecLabel[5]; /**< TODO: describe */
    QComboBox *aCodecComboBox[5]; /**< TODO: describe */

    QCheckBox *GingaCheckBox[5]; /**< TODO: describe */
    QGridLayout *Gingalayout[5]; /**< TODO: describe */

    QGroupBox *Ginga[5]; /**< TODO: describe */

    QLabel *GingaLabel[5]; /**< TODO: describe */
    QLineEdit *GingaLineEdit[5]; /**< TODO: describe */
    QPushButton *GingaButton[5]; /**< TODO: describe */
    DoubleSlider *GingaSlider[5]; /**< TODO: describe */
    QLabel *GingaRateLabel[5]; /**< TODO: describe */
    QDoubleSpinBox *GingaSpinBox[5]; /**< TODO: describe */


private:
public slots:
    /**
     * @brief
     *
     * @param value1
     * @param value2
     */
    void audioSpinBoxsetrange(int value1, int value2);
    /**
     * @brief
     *
     * @param value
     */
    void notifyAudioChanges();
    /**
     * @brief
     *
     */
    void notifyFileLoad();
    /**
     * @brief
     *
     */
};

/**
 * @brief
 *
 */
class MuxPage : public QWizardPage
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     * @param parent
     */
    MuxPage(QWidget *parent = nullptr);

    /**
     * @brief
     *
     * @return int
     */
    int nextId() const override;
    /**
     * @brief
     *
     */
    void initializePage() override;
    bool validatePage() override;
    void cleanupPage() override;

private:
    struct IntParam {
        QString name;
        int value;
        int type;
        int min;
        int max;
    };
    QTabWidget *MuxTab; /**< TODO: describe */
    QVBoxLayout *layoutTab[18]; /**< TODO: describe */
    QWidget *tabWidget[18]; /**< TODO: describe */

    QScrollArea *scrollArea[18];

    QGroupBox *PATService[5]; /**< TODO: describe */
    QGridLayout *PATlayout[5]; /**< TODO: describe */

    LabelHexSpinBox *PATTSID;

    SectionLoop *PATProgramLoop;/**< TODO: describe */

    SectionDescriptor *PATprogram_loop_item[5];

    LabelHexSpinBox *PATServiceID[5];

    LabelHexSpinBox *PATServicePID[5];

    LabelHexSpinBox *NITNetworkID;
    SectionLoop *NITNetworkDescLoop;

    SectionDescriptor *NITNetworkDesc;
    LabelLineEdit *NITNetworkName;

    SectionDescriptor *NITSystemMngDesc;
    LabelHexSpinBox *NITSystemMngItem[3];

    SectionLoop *NITTSLoop;
    SectionLoop *NITTSLoopItem;

    ElementSectionDescriptor *NITTSItem;
    LabelHexSpinBox *NITTSID;
    LabelHexSpinBox *NITOriginNetworkID;

    SectionLoop *NITTSTransportDescLoop;
    SectionLoop *NITServiceListDesc;

    SectionDescriptor *NITService[5];
    LabelHexSpinBox *NITServiceID[5];
    LabelHexSpinBox *NITServiceType[5];

    SectionDescriptor *NITTerrestrialDeliverySystemDesc;
    LabelHexSpinBox *NITAreaCode; /**< TODO: describe */

    SectionLoop *transport_stream_information_descriptor; /**< TODO: describe */
    ElementSectionDescriptor *transport_stream_information_descriptorItem;

    LabelHexSpinBox *remote_control_key_id; /**< TODO: describe */
    LabelLineEdit *ts_name; /**< TODO: describe */

    QFormLayout *TOT_Layout;
    QWidget *TOT_Widget;
    QStringList TOT_items={"year","month","day","hour","minute","second"};
    QList<QLabel*> *TOT_Label;
    SectionLoop *TOT_descriptor_Loop;

    ElementSectionDescriptor *SDTItem;
    LabelHexSpinBox *SDTTSID;
    LabelHexSpinBox *SDTNetworkID;

    SectionLoop *SDTServiceLoop;

    SectionLoop *SDTServiceLoopItem[5];
    ElementSectionDescriptor *SDTServiceLoopElement[5];

    LabelHexSpinBox *SDTServiceLoopElementWidget[5][5];

    SectionLoop *SDTServiceDescLoop[5];

    SectionDescriptor *SDTServiceDesc[5];

    LabelHexSpinBox *SDTServiceType[5];
    LabelLineEdit *SDTServiceProviderName[5];
    LabelLineEdit *SDTServiceName[5];

    QGroupBox *PMTServiceLoop[5]; /**< TODO: describe */
    QGridLayout *PMTServiceLooplayout[5]; /**< TODO: describe */

    LabelHexSpinBox *PMTProgramNumber[5]; /**< TODO: describe */

    QLabel *PMTProgramNumberLabel[5]; /**< TODO: describe */
    HexSpinBox *PMTProgramNumberHexspinBox[5]; /**< TODO: describe */

    QLabel *PMTPCRLabel[5]; /**< TODO: describe */
    HexSpinBox *PMTPCRHexspinBox[5]; /**< TODO: describe */

    SectionLoop *PMTStreamLoop[5];/**< TODO: describe */

    SectionDescriptor *PMTVideo[5]; /**< TODO: describe */
    LabelHexSpinBox *PMTVideoItem[5][2];

    SectionDescriptor *PMTAudio[5]; /**< TODO: describe */
    LabelHexSpinBox *PMTAudioItem[5][2];

    SectionLoop *PMTAIT[5]; /**< TODO: describe */
    ElementSectionDescriptor *PMTAITItem[5];
    LabelHexSpinBox *PMTAITWidgetItem[5][2];

    SectionLoop *PMTAITelement_info_descriptor_loop[5]; /**< TODO: describe */

    SectionDescriptor *PMTAITdata_component_descriptor[5];
    LabelHexSpinBox *PMTAITdata_component_descriptorItem[5];


    SectionDescriptor *PMTAITadditional_data_component_info[5];
    SectionDescriptor *PMTAITait_identifier_info[5];
    QLabel *PMTAITait_identifier_infoLabel[5][2];
    HexSpinBox *PMTAITait_identifier_infoHexSpinBox[5][2];

    SectionDescriptor *PMTAITapplication_signalling_descriptor[5];
    QLabel *PMTAITapplication_signalling_descriptorLabel[5][2];
    HexSpinBox *PMTAITapplication_signalling_descriptorHexSpinBox[5][2];

    SectionLoop *PMTDSMCC[5]; /**< TODO: describe */
    ElementSectionDescriptor *PMTDSMCCItem[5];
    QLabel *PMTDSMCCLabelItem[5][2];
    HexSpinBox *PMTDSMCCHexspinBoxItem[5][2]; /**< TODO: describe */
    SectionLoop *PMTDSMCCelement_info_descriptor_loop[5]; /**< TODO: describe */

    SectionDescriptor *PMTDSMCCassociation_tag_descriptor[5];
    QLabel *PMTDSMCCassociation_tag_descriptorLabel[5][5];
    HexSpinBox *PMTDSMCCassociation_tag_descriptorHexSpinBox[5][5];
    SectionDescriptor *PMTDSMCCstream_identifier_descriptor[5];
    QLabel *PMTDSMCCstream_identifier_descriptorLabel[5];
    HexSpinBox *PMTDSMCCstream_identifier_descriptorHexSpinBox[5];

    SectionDescriptor *PMTDSMCCcarousel_identifier_descriptor[5];
    QLabel *PMTDSMCCcarousel_identifier_descriptorLabel[5][2];
    HexSpinBox *PMTDSMCCcarousel_identifier_descriptorHexSpinBox[5][2];

    SectionDescriptor *PMTDSMCCdata_component_descriptor[5];
    ElementSectionDescriptor *PMTDSMCCdata_component_descriptorItem[5];
    LabelHexSpinBox *PMTDSMCCdata_component_id[5];

    SectionDescriptor *PMTDSMCCadditional_data_component_info[5];
    SectionDescriptor *PMTDSMCCadditional_ginga_j_info[5];
    LabelHexSpinBox  *PMTDSMCCadditional_ginga_j_infoItem[5][5];

    QLayout *AITLayout[5];

    LabelHexSpinBox *AITApptype[5];

    SectionLoop *AITApploop[5];
    SectionLoop *AITApp[5];
    ElementSectionDescriptor *AITAppElementSection[5];

    QList<LabelHexSpinBox*> *AIT_app_item_widgets[5];
    QList<IntParam> AIT_app_items = {{"Organization_ID",0x4E,LabelHexSpinBox::HEXSPINBOX,0x4E,0x4E},
                                    {"AppID",0,LabelHexSpinBox::HEXSPINBOX,0x30,0x1FC7},
                                    {"Application Control Code",0,LabelHexSpinBox::HEXSPINBOX,0,65535},
                                    };

    LabelHexSpinBox *AITOrganizationID[5]; /**< TODO: describe */
    LabelHexSpinBox *AITAppID[5]; /**< TODO: describe */
    LabelHexSpinBox *AITAPPControlCode[5]; /**< TODO: describe */

    SectionLoop *AITApp_descriptors_loop[5];

    SectionDescriptor *AITTransportProtocolControlDesc[5];
    QList<LabelHexSpinBox*> *AITTransportProtocolControlDesc_item_widgets[5];
    QList<IntParam> AITTransportProtocolControlDesc_items = {{"protocol_id",0x4E,LabelHexSpinBox::HEXSPINBOX,0x4E,0x4E},
                                                            {"transport_protocol_label",0,LabelHexSpinBox::HEXSPINBOX,0x30,0x1FC7},
                                                            {"remote_connection",0,LabelHexSpinBox::HEXSPINBOX,0,65535},
                                                            {"component_tag",0,LabelHexSpinBox::HEXSPINBOX,0,65535},
                                                            };
    LabelHexSpinBox *AITprotocol_id[5];
    LabelHexSpinBox *AITtransport_protocol_label[5];
    LabelHexSpinBox *AITremote_connection[5];
    LabelHexSpinBox *AITcomponent_tag[5];

    SectionDescriptor *AITAppDesc[5];
    LabelHexSpinBox *AITapplication_profile[5];
    LabelHexSpinBox *AITversion_major[5];
    LabelHexSpinBox *AITversion_minor[5];
    LabelHexSpinBox *AITversion_micro[5];
    LabelHexSpinBox *AITservice_bound_flagr[5];
    LabelHexSpinBox *AITvisibility[5];
    LabelHexSpinBox *AITapplication_priority[5];
    LabelHexSpinBox *AITtransport_protocol_labels[5];

    SectionDescriptor *AITApp_name_descriptor[5];
    LabelLineEdit *AITapplication_name[5];

    SectionDescriptor *ginga_ncl_application_location_descriptor[5];
    LabelLineEdit *AITbase_directory[5];
    LabelLineEdit *class_path_extension[5];
    LabelLineEdit *initial_class[5];

    SectionLoop *EIT_loop[5];
    SectionDescriptor *EIT_loop_item[5];
    QList<LabelHexSpinBox*> *EITelements[5];
    QList<IntParam> EIT_items = {{"table_id",0x4E,LabelHexSpinBox::HEXSPINBOX,0x4E,0x4E},
                                 {"service_id",0,LabelHexSpinBox::HEXSPINBOX,0x30,0x1FC7},
                                 {"transport_stream_id",0,LabelHexSpinBox::HEXSPINBOX,0,65535},
                                 {"original_network_id",0,LabelHexSpinBox::HEXSPINBOX,0,65535},
                                };

    SectionLoop *EIT_event_loop[5];
    SectionDescriptor *EIT_event_loop_item[5];

    QList<LabelHexSpinBox*> *EIT_event_loop_widgets[5];
    QList<IntParam> EIT_event_loop_items = {{"event_id",1,LabelHexSpinBox::HEXSPINBOX,0,255},
                                            {"start_year",QDate::currentDate().year()-1900,LabelHexSpinBox::SPINBOX,0,65535},
                                            {"start_month",QDate::currentDate().month(),LabelHexSpinBox::SPINBOX,0,12},
                                            {"start_day",QDate::currentDate().day(),LabelHexSpinBox::SPINBOX,0,31},
                                            {"start_hours",QTime::currentTime().hour(),LabelHexSpinBox::SPINBOX,0,23},
                                            {"start_minutes",0,LabelHexSpinBox::SPINBOX,0,59},
                                            {"start_seconds",0,LabelHexSpinBox::SPINBOX,0,59},
                                            {"duration_hours",0,LabelHexSpinBox::SPINBOX,0,23},
                                            {"duration_minutes",30,LabelHexSpinBox::SPINBOX,0,59},
                                            {"duration_seconds",0,LabelHexSpinBox::SPINBOX,0,59},
                                            {"running_status",4,LabelHexSpinBox::HEXSPINBOX,0,7},
                                            {"free_CA_mode",0,LabelHexSpinBox::HEXSPINBOX,0,0},
                                           };

    SectionLoop *EIT_follow_loop[5];
    ElementSectionDescriptor *EIT_follow_loop_item[5];
    QList<LabelHexSpinBox*> *EIT_follow_elements[5];
    QList<IntParam> EIT_follow_items = {{"table_id",0x4E,LabelHexSpinBox::HEXSPINBOX,0x4E,0x4E},
                                 {"service_id",0,LabelHexSpinBox::HEXSPINBOX,0x30,0x1FC7},
                                 {"transport_stream_id",0,LabelHexSpinBox::HEXSPINBOX,0,65535},
                                 {"original_network_id",0,LabelHexSpinBox::HEXSPINBOX,0,65535},
                                };



    SectionLoop *EIT_follow_event_loop[5];
    SectionDescriptor *EIT_follow_event_loop_item[5];

    QList<LabelHexSpinBox*> *EIT_follow_event_loop_widgets[5];
    QList<IntParam> EIT_follow_event_loop_items = {{"event_id",1,LabelHexSpinBox::HEXSPINBOX,0,255},
                                            {"start_year",QDate::currentDate().year()-1900,LabelHexSpinBox::SPINBOX,0,65535},
                                            {"start_month",QDate::currentDate().month(),LabelHexSpinBox::SPINBOX,0,12},
                                            {"start_day",QDate::currentDate().day(),LabelHexSpinBox::SPINBOX,0,31},
                                            {"start_hours",QTime::currentTime().hour(),LabelHexSpinBox::SPINBOX,0,23},
                                            {"start_minutes",0,LabelHexSpinBox::SPINBOX,0,59},
                                            {"start_seconds",0,LabelHexSpinBox::SPINBOX,0,59},
                                            {"duration_hours",0,LabelHexSpinBox::SPINBOX,0,23},
                                            {"duration_minutes",30,LabelHexSpinBox::SPINBOX,0,59},
                                            {"duration_seconds",0,LabelHexSpinBox::SPINBOX,0,59},
                                            {"running_status",4,LabelHexSpinBox::HEXSPINBOX,0,7},
                                            {"free_CA_mode",0,LabelHexSpinBox::HEXSPINBOX,0,0},
                                           };

public slots:
    /**
     * @brief
     *
     * @param value1
     * @param value2
     */
    void MuxChanges(int value);
};

/**
 * @brief
 *
 */
class FinalPage : public QWizardPage
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     * @param parent
     */
    FinalPage(QWidget *parent = nullptr);
    /**
     * @brief
     *
     */
    void initializePage() override;
public slots:
    /**
     * @brief
     *
     */
    void execute();
private:
    QTabWidget *FinalTab; /**< TODO: describe */
    QGridLayout *layoutTab[3]; /**< TODO: describe */
    QWidget *tabWidget[3]; /**< TODO: describe */

    QTextEdit *Text[3]; /**< TODO: describe */
    QPushButton *execButton; /**< TODO: describe */
    KickPythonSyntaxHighlighter *pythonHighlighter; /**< TODO: describe */

};

#endif // TVDUMSA_H


