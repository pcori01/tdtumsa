#ifndef TVDUMSA_H
#define TVDUMSA_H

#include <QWizard>
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

/**
 * @brief
 *
 */
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
    QLabel *PresentationLabel;
    LabelLineEdit *WorkDirectory;
    QPushButton *WorkDirectory_button;
    QLabel *CreditLabel;
public slots:
     /**
     * @brief
     *
     */
    void notifyFileLoad();
};

/**
 * @brief
 *
 */
class PlanPage : public QWizardPage
{
    Q_OBJECT
    Q_PROPERTY(int indexPlan READ indexPlan WRITE setindexPlan)
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
    /**Audiolayout
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

    /**
     * @brief
     * Funcion para guardar el indice de los modelos de Planificacion del canal Radioelectrico
     * @param indexPlan
     */
    void setindexPlan(int indexPlan)
    {
        IndexP = indexPlan;
    }
    /**
     * @brief
     *
     * @return QMap<QString, QVariant>
     */
    int indexPlan(void)
    {
        return IndexP;
    }

    /**
     * @brief
     *
     * @param value
     */
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
    QLabel *descriptionLabel;
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

    QTabWidget *CodeTab;
    QGridLayout *layoutTab[5];
    QWidget *tabWidget[5];
    QLabel *videoLabel[5];
    QLineEdit *videoLineEdit[5];
    QPushButton *videoButton[5];
    QLabel *videoBitrateLabel[5];

    QGroupBox *File[5];
    QGridLayout *Filelayout[5];

    QGroupBox *Video[5];
    QGridLayout *Videolayout[5];

    DoubleSlider *videoSlider[5];
    QDoubleSpinBox *videoSpinBox[5];
    QLabel *vResolutionLabel[5];
    QComboBox *vResolutionComboBox[5];
    QLabel *videoFPSLabel[5];
    QComboBox *videoFPSComboBox[5];
    QLabel *videoRALabel[5];
    QComboBox *videoRAComboBox[5];
    QLabel *videoPerfilLabel[5];
    QComboBox *videoPerfilComboBox[5];
    QLabel *videoNivelLabel[5];
    QComboBox *videoNivelComboBox[5];

    QGroupBox *Audio[5];
    QGridLayout *Audiolayout[5];

    QLabel *audioBitrateLabel[5];
    QSlider *audioSlider[5];
    QSpinBox *audioSpinBox[5];
    QLabel *aSampleRateLabel[5];
    QComboBox *aSampleRateComboBox[5];
    QLabel *aChanelsLabel[5];
    QComboBox *aChanelsComboBox[5];
    QLabel *aCodecLabel[5];
    QComboBox *aCodecComboBox[5];

    QCheckBox *GingaCheckBox[5];
    QGridLayout *Gingalayout[5];

    QGroupBox *Ginga[5];

    QLabel *GingaLabel[5];
    QLineEdit *GingaLineEdit[5];
    QPushButton *GingaButton[5];
    DoubleSlider *GingaSlider[5];
    QLabel *GingaRateLabel[5];
    QDoubleSpinBox *GingaSpinBox[5];


private:
public slots:
    /**
     * @brief
     *
     * @param value1
     * @param value2
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
    /**
     * @brief
     *
     */
    struct IntParam {
        QString name;
        int value;
        int type;
        int min;
        unsigned int max;
    };
    struct StringParam {
        QString name;
        QString text;
        int length;
    };
    QTabWidget *MuxTab;
    QVBoxLayout *layoutTab[18];
    QWidget *tabWidget[18];

    QScrollArea *scrollArea[18];

    QGroupBox *PATService[5];
    QGridLayout *PATlayout[5];

    LabelHexSpinBox *PATTSID;

    SectionLoop *PATProgramLoop;

    SectionDescriptor *PATprogram_loop_item[5];

    LabelHexSpinBox *PATServiceID[5];
    LabelHexSpinBox *PATServicePID[5];

    LabelHexSpinBox *NITNetworkID;
    SectionLoop *NITNetworkDescLoop;

    SectionDescriptor *NITNetworkDesc;
    LabelLineEdit *NITNetworkName;

    SectionDescriptor *NITSystemMngDesc;
    LabelHexSpinBox *NITSystemMngItem[3];

    QList<LabelHexSpinBox*> *NITSystemMngDesc_widgets;
    QList<IntParam> NITSystemMngDesc_item = {{"broadcasting_flag",0,LabelHexSpinBox::HEXSPINBOX,0,0},
                                            {"broadcasting_identifier",3,LabelHexSpinBox::HEXSPINBOX,0,3},
                                            {"additional_broadcasting_identification",1,LabelHexSpinBox::HEXSPINBOX,0,1},
                                            };

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
    QList<LabelHexSpinBox*> *NITTerrestrialDeliverySystemDesc_widgets;
    QList<IntParam> NITTerrestrialDeliverySystemDesc_item = {{"area_code",0,LabelHexSpinBox::HEXSPINBOX,0,0},
                                                            {"guard_interval",3,LabelHexSpinBox::HEXSPINBOX,0,3},
                                                            {"transmission_mode",1,LabelHexSpinBox::HEXSPINBOX,0,3},
                                                            {"frecuency",509,LabelHexSpinBox::SPINBOX,177,803},
                                                            };


    LabelHexSpinBox *NITAreaCode;

    SectionLoop *transport_stream_information_descriptor;
    ElementSectionDescriptor *transport_stream_information_descriptorItem;

    LabelHexSpinBox *remote_control_key_id;
    LabelLineEdit *ts_name;

    QFormLayout *TOT_Layout;
    QWidget *TOT_Widget;
    QStringList TOT_items={"year","month","day","hour","minute","second"};
    QList<QLabel*> *TOT_Label;
    SectionLoop *TOT_descriptor_Loop;

    SectionDescriptor *TOT_local_time_offset_descriptor;
    LabelLineEdit *TOT_ISO_639_language_code;
    QList<LabelHexSpinBox*> *TOT_local_time_offset_descriptor_Widgets;
    QList<IntParam> TOT_local_time_offset_descriptor_item = {{"country_region_id",0x0,LabelHexSpinBox::HEXSPINBOX,0x0,0xFFFF},
                                                               {"local_time_offset_polarity",1,LabelHexSpinBox::HEXSPINBOX,0,1},
                                                               {"local_time_offset_hour",4,LabelHexSpinBox::HEXSPINBOX,0,13},
                                                               {"local_time_offset_minute",0,LabelHexSpinBox::HEXSPINBOX,0,59},
                                                               {"year_of_change",0,LabelHexSpinBox::HEXSPINBOX,0,0xFFFF},
                                                               {"month_of_change",1,LabelHexSpinBox::HEXSPINBOX,1,12},
                                                               {"day_of_change",1,LabelHexSpinBox::HEXSPINBOX,1,31},
                                                               {"hour_of_change",0,LabelHexSpinBox::HEXSPINBOX,0,23},
                                                               {"minute_of_change",0,LabelHexSpinBox::HEXSPINBOX,0,59},
                                                               {"second_of_change",0,LabelHexSpinBox::HEXSPINBOX,5,0xfff},
                                                               {"next_time_offset_hour",4,LabelHexSpinBox::HEXSPINBOX,0,13},
                                                               {"next_time_offset_minute",0,LabelHexSpinBox::HEXSPINBOX,0,59},
                                                              };


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

    QGroupBox *PMTServiceLoop[5];
    QGridLayout *PMTServiceLooplayout[5];

    LabelHexSpinBox *PMTProgramNumber[5];

    QLabel *PMTProgramNumberLabel[5];
    HexSpinBox *PMTProgramNumberHexspinBox[5];

    QLabel *PMTPCRLabel[5];
    HexSpinBox *PMTPCRHexspinBox[5];

    SectionLoop *PMTStreamLoop[5];

    SectionDescriptor *PMTVideo[5];
    LabelHexSpinBox *PMTVideoItem[5][2];

    SectionDescriptor *PMTAudio[5];
    LabelHexSpinBox *PMTAudioItem[5][2];

    SectionLoop *PMTAIT[5];
    ElementSectionDescriptor *PMTAITItem[5];
    QList<LabelHexSpinBox*> *PMTAITWidgetItem[5];
    QList<IntParam> PMTAIT_item = {{"Stream Type AIT",5,LabelHexSpinBox::HEXSPINBOX,5,5},
                                   {"PID AIT",2001,LabelHexSpinBox::HEXSPINBOX,0x30,0x1FC7},
                                  };

    SectionLoop *PMTAITelement_info_descriptor_loop[5];

    SectionDescriptor *PMTAITdata_component_descriptor[5];
    LabelHexSpinBox *PMTAITdata_component_descriptorItem[5];

    SectionDescriptor *PMTAITadditional_data_component_info[5];
    SectionDescriptor *PMTAITait_identifier_info[5];
    QLabel *PMTAITait_identifier_infoLabel[5][2];
    HexSpinBox *PMTAITait_identifier_infoHexSpinBox[5][2];

    SectionDescriptor *PMTAITapplication_signalling_descriptor[5];
    QLabel *PMTAITapplication_signalling_descriptorLabel[5][2];
    HexSpinBox *PMTAITapplication_signalling_descriptorHexSpinBox[5][2];

    SectionLoop *PMTDSMCC[5];
    ElementSectionDescriptor *PMTDSMCCItem[5];
    QList<LabelHexSpinBox*> *PMTDSMCCWidgetItem[5];
    QList<IntParam> PMTDSMCC_item = {{"Stream Type DSMCC",0x0B,LabelHexSpinBox::HEXSPINBOX,0x0B,0x0B},
                                   {"PID DSMCC",3001,LabelHexSpinBox::HEXSPINBOX,0x30,0x1FC7},
                                  };

    QLabel *PMTDSMCCLabelItem[5][2];
    HexSpinBox *PMTDSMCCHexspinBoxItem[5][2];
    SectionLoop *PMTDSMCCelement_info_descriptor_loop[5];

    SectionDescriptor *PMTDSMCCassociation_tag_descriptor[5];
    QList<LabelHexSpinBox*> *PMTDSMCCassociation_tag_descriptorWidgetItem[5];
    QList<IntParam> PMTDSMCCassociation_tag_descriptor_item = {{"association_tag",0x0C,LabelHexSpinBox::HEXSPINBOX,0,0xFF},
                                                               {"use",0,LabelHexSpinBox::HEXSPINBOX,0x0,0xFFFF},
                                                               {"selector_lenght",0,LabelHexSpinBox::HEXSPINBOX,5,0xfff},
                                                               {"transaction_id",0x8000000,LabelHexSpinBox::HEXSPINBOX,0x0,0xFFFFFFFF},
                                                               {"timeout",0xFFFFFF,LabelHexSpinBox::HEXSPINBOX,0x0,0x7FFFFFFF},
                                                              };


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

    LabelHexSpinBox *AITOrganizationID[5];
    LabelHexSpinBox *AITAppID[5];
    LabelHexSpinBox *AITAPPControlCode[5];

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
                                 {"service_id",90,LabelHexSpinBox::HEXSPINBOX,0x30,0x1FC7},
                                 {"transport_stream_id",90,LabelHexSpinBox::HEXSPINBOX,0,65535},
                                 {"original_network_id",90,LabelHexSpinBox::HEXSPINBOX,0,65535},
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


    SectionLoop *EIT_event_descriptor_loop[5];
    SectionDescriptor *EIT_short_event_descriptor[5];
    QList<LabelLineEdit*> *EIT_short_event_descriptor_widgets[5];
    QList<StringParam> EIT_short_event_descriptor_items = {{"ISO639_language_code","spa",3},
                                                          {"event_name","evento epg presente",25},
                                                          {"text"," Descipcion del evento epg presente",40},
                                                         };

    SectionLoop *EIT_follow_loop[5];
    ElementSectionDescriptor *EIT_follow_loop_item[5];
    QList<LabelHexSpinBox*> *EIT_follow_elements[5];
    QList<IntParam> EIT_follow_items = {{"table_id",0x4E,LabelHexSpinBox::HEXSPINBOX,0x4E,0x4E},
                                 {"service_id",80,LabelHexSpinBox::HEXSPINBOX,0x30,0x1FC7},
                                 {"transport_stream_id",80,LabelHexSpinBox::HEXSPINBOX,0,65535},
                                 {"original_network_id",80,LabelHexSpinBox::HEXSPINBOX,0,0xFFFF},
                                };

    SectionLoop *EIT_follow_event_loop[5];
    SectionDescriptor *EIT_follow_event_loop_item[5];

    QList<LabelHexSpinBox*> *EIT_follow_event_loop_widgets[5];
    QList<IntParam> EIT_follow_event_loop_items = {{"event_id",1,LabelHexSpinBox::HEXSPINBOX,0,255},
                                            {"start_year",QDate::currentDate().year()-1900,LabelHexSpinBox::SPINBOX,0,65535},
                                            {"start_month",QDate::currentDate().month(),LabelHexSpinBox::SPINBOX,0,12},
                                            {"start_day",QDate::currentDate().day(),LabelHexSpinBox::SPINBOX,0,31},
                                            {"start_hours",QTime::currentTime().hour(),LabelHexSpinBox::SPINBOX,0,23},
                                            {"start_minutes",30,LabelHexSpinBox::SPINBOX,0,59},
                                            {"start_seconds",0,LabelHexSpinBox::SPINBOX,0,59},
                                            {"duration_hours",0,LabelHexSpinBox::SPINBOX,0,23},
                                            {"duration_minutes",30,LabelHexSpinBox::SPINBOX,0,59},
                                            {"duration_seconds",0,LabelHexSpinBox::SPINBOX,0,59},
                                            {"running_status",4,LabelHexSpinBox::HEXSPINBOX,0,7},
                                            {"free_CA_mode",0,LabelHexSpinBox::HEXSPINBOX,0,0},
                                           };

    SectionLoop *EIT_follow_event_descriptor_loop[5];
    SectionDescriptor *EIT_follow_short_event_descriptor[5];
    QList<LabelLineEdit*> *EIT_follow_short_event_descriptor_widgets[5];
    QList<StringParam> EIT_follow_short_event_descriptor_items = {{"ISO639_language_code","spa",3},
                                                                  {"event_name","evento epg presente",25},
                                                                  {"text"," Descipcion del evento epg presente",40},
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
    QTabWidget *FinalTab;
    QGridLayout *layoutTab[3];
    QWidget *tabWidget[3];

    QTextEdit *Text[3];
    QPushButton *execButton;
    KickPythonSyntaxHighlighter *pythonHighlighter;

};

#endif // TVDUMSA_H


