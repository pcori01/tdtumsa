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
    QLabel *PresentationLabel; /**< TODO: describe */
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
    QLabel *descriptionLabel; /**< TODO: describe */
    QLabel *optionLabel[4];
    QCheckBox *OneSegCheckBox;
    QRadioButton *optionRadioButton[4];
    int IndexP; /**< TODO: describe */
    int m_SevicesPlan; /**< TODO: describe */
    QWidget *services; /**< TODO: describe */

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
        QString name; /**< TODO: describe */
        int value; /**< TODO: describe */
        int type; /**< TODO: describe */
        int min; /**< TODO: describe */
        unsigned int max; /**< TODO: describe */
    };
    struct StringParam {
        QString name; /**< TODO: describe */
        QString text; /**< TODO: describe */
        int length;
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

    LabelHexSpinBox *PATServiceID[5]; /**< TODO: describe */
    LabelHexSpinBox *PATServicePID[5]; /**< TODO: describe */

    LabelHexSpinBox *NITNetworkID; /**< TODO: describe */
    SectionLoop *NITNetworkDescLoop; /**< TODO: describe */

    SectionDescriptor *NITNetworkDesc; /**< TODO: describe */
    LabelLineEdit *NITNetworkName; /**< TODO: describe */

    SectionDescriptor *NITSystemMngDesc; /**< TODO: describe */
    LabelHexSpinBox *NITSystemMngItem[3]; /**< TODO: describe */

    QList<LabelHexSpinBox*> *NITSystemMngDesc_widgets; /**< TODO: describe */
    QList<IntParam> NITSystemMngDesc_item = {{"broadcasting_flag",0,LabelHexSpinBox::HEXSPINBOX,0,0}, /**< TODO: describe */
                                            {"broadcasting_identifier",3,LabelHexSpinBox::HEXSPINBOX,0,3},
                                            {"additional_broadcasting_identification",1,LabelHexSpinBox::HEXSPINBOX,0,1},
                                            };

    SectionLoop *NITTSLoop; /**< TODO: describe */
    SectionLoop *NITTSLoopItem; /**< TODO: describe */

    ElementSectionDescriptor *NITTSItem; /**< TODO: describe */
    LabelHexSpinBox *NITTSID; /**< TODO: describe */
    LabelHexSpinBox *NITOriginNetworkID; /**< TODO: describe */

    SectionLoop *NITTSTransportDescLoop; /**< TODO: describe */
    SectionLoop *NITServiceListDesc; /**< TODO: describe */

    SectionDescriptor *NITService[5]; /**< TODO: describe */
    LabelHexSpinBox *NITServiceID[5]; /**< TODO: describe */
    LabelHexSpinBox *NITServiceType[5]; /**< TODO: describe */

    SectionDescriptor *NITTerrestrialDeliverySystemDesc; /**< TODO: describe */
    LabelHexSpinBox *NITAreaCode; /**< TODO: describe */

    SectionLoop *transport_stream_information_descriptor; /**< TODO: describe */
    ElementSectionDescriptor *transport_stream_information_descriptorItem;

    LabelHexSpinBox *remote_control_key_id; /**< TODO: describe */
    LabelLineEdit *ts_name; /**< TODO: describe */

    QFormLayout *TOT_Layout;
    QWidget *TOT_Widget;
    QStringList TOT_items={"year","month","day","hour","minute","second"}; /**< TODO: describe */
    QList<QLabel*> *TOT_Label; /**< TODO: describe */
    SectionLoop *TOT_descriptor_Loop; /**< TODO: describe */

    SectionDescriptor *TOT_local_time_offset_descriptor;
    LabelLineEdit *TOT_ISO_639_language_code;
    QList<LabelHexSpinBox*> *TOT_local_time_offset_descriptor_Widgets; /**< TODO: describe */
    QList<IntParam> TOT_local_time_offset_descriptor_item = {{"country_region_id",0x0C,LabelHexSpinBox::HEXSPINBOX,0,0xFF}, /**< TODO: describe */
                                                               {"local_time_offset_polarity",0,LabelHexSpinBox::HEXSPINBOX,0x0,0xFFFF},
                                                               {"local_time_offset_hour",0,LabelHexSpinBox::HEXSPINBOX,5,0xfff}, /**< TODO: describe */
                                                               {"local_time_offset_minute",0x8000000,LabelHexSpinBox::HEXSPINBOX,0x0,0xFFFFFFFF},
                                                               {"year_of_change",0xFFFFFF,LabelHexSpinBox::HEXSPINBOX,0x0,0xFFFFFFFF},
                                                               {"month_of_change",0,LabelHexSpinBox::HEXSPINBOX,0x0,0xFFFF},
                                                               {"day_of_change",0,LabelHexSpinBox::HEXSPINBOX,5,0xfff}, /**< TODO: describe */
                                                               {"hour_of_change",0x8000000,LabelHexSpinBox::HEXSPINBOX,0x0,0xFFFFFFFF},
                                                               {"minute_of_change",0xFFFFFF,LabelHexSpinBox::HEXSPINBOX,0x0,0xFFFFFFFF},
                                                               {"second_of_change",0,LabelHexSpinBox::HEXSPINBOX,5,0xfff}, /**< TODO: describe */
                                                               {"next_time_offset_hour",0x8000000,LabelHexSpinBox::HEXSPINBOX,0x0,0xFFFFFFFF},
                                                               {"next_time_offset_minute",0xFFFFFF,LabelHexSpinBox::HEXSPINBOX,0x0,0xFFFFFFFF},
                                                              };


    ElementSectionDescriptor *SDTItem; /**< TODO: describe */
    LabelHexSpinBox *SDTTSID; /**< TODO: describe */
    LabelHexSpinBox *SDTNetworkID; /**< TODO: describe */

    SectionLoop *SDTServiceLoop; /**< TODO: describe */

    SectionLoop *SDTServiceLoopItem[5]; /**< TODO: describe */
    ElementSectionDescriptor *SDTServiceLoopElement[5]; /**< TODO: describe */

    LabelHexSpinBox *SDTServiceLoopElementWidget[5][5]; /**< TODO: describe */

    SectionLoop *SDTServiceDescLoop[5]; /**< TODO: describe */

    SectionDescriptor *SDTServiceDesc[5]; /**< TODO: describe */

    LabelHexSpinBox *SDTServiceType[5]; /**< TODO: describe */
    LabelLineEdit *SDTServiceProviderName[5]; /**< TODO: describe */
    LabelLineEdit *SDTServiceName[5]; /**< TODO: describe */

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
    QList<LabelHexSpinBox*> *PMTAITWidgetItem[5]; /**< TODO: describe */
    QList<IntParam> PMTAIT_item = {{"Stream Type AIT",5,LabelHexSpinBox::HEXSPINBOX,5,5}, /**< TODO: describe */
                                   {"PID AIT",2001,LabelHexSpinBox::HEXSPINBOX,0x30,0x1FC7},
                                  };

    SectionLoop *PMTAITelement_info_descriptor_loop[5]; /**< TODO: describe */

    SectionDescriptor *PMTAITdata_component_descriptor[5];
    LabelHexSpinBox *PMTAITdata_component_descriptorItem[5];

    SectionDescriptor *PMTAITadditional_data_component_info[5]; /**< TODO: describe */
    SectionDescriptor *PMTAITait_identifier_info[5]; /**< TODO: describe */
    QLabel *PMTAITait_identifier_infoLabel[5][2]; /**< TODO: describe */
    HexSpinBox *PMTAITait_identifier_infoHexSpinBox[5][2]; /**< TODO: describe */

    SectionDescriptor *PMTAITapplication_signalling_descriptor[5]; /**< TODO: describe */
    QLabel *PMTAITapplication_signalling_descriptorLabel[5][2]; /**< TODO: describe */
    HexSpinBox *PMTAITapplication_signalling_descriptorHexSpinBox[5][2]; /**< TODO: describe */

    SectionLoop *PMTDSMCC[5]; /**< TODO: describe */
    ElementSectionDescriptor *PMTDSMCCItem[5];
    QList<LabelHexSpinBox*> *PMTDSMCCWidgetItem[5]; /**< TODO: describe */
    QList<IntParam> PMTDSMCC_item = {{"Stream Type DSMCC",0x0B,LabelHexSpinBox::HEXSPINBOX,0x0B,0x0B}, /**< TODO: describe */
                                   {"PID DSMCC",3001,LabelHexSpinBox::HEXSPINBOX,0x30,0x1FC7},
                                  };

    QLabel *PMTDSMCCLabelItem[5][2];
    HexSpinBox *PMTDSMCCHexspinBoxItem[5][2]; /**< TODO: describe */
    SectionLoop *PMTDSMCCelement_info_descriptor_loop[5]; /**< TODO: describe */

    SectionDescriptor *PMTDSMCCassociation_tag_descriptor[5];
    QList<LabelHexSpinBox*> *PMTDSMCCassociation_tag_descriptorWidgetItem[5]; /**< TODO: describe */
    QList<IntParam> PMTDSMCCassociation_tag_descriptor_item = {{"association_tag",0x0C,LabelHexSpinBox::HEXSPINBOX,0,0xFF}, /**< TODO: describe */
                                                               {"use",0,LabelHexSpinBox::HEXSPINBOX,0x0,0xFFFF},
                                                               {"selector_lenght",0,LabelHexSpinBox::HEXSPINBOX,5,0xfff}, /**< TODO: describe */
                                                               {"transaction_id",0x8000000,LabelHexSpinBox::HEXSPINBOX,0x0,0xFFFFFFFF},
                                                               {"timeout",0xFFFFFF,LabelHexSpinBox::HEXSPINBOX,0x0,0x7FFFFFFF},
                                                              };


    SectionDescriptor *PMTDSMCCstream_identifier_descriptor[5]; /**< TODO: describe */
    QLabel *PMTDSMCCstream_identifier_descriptorLabel[5]; /**< TODO: describe */
    HexSpinBox *PMTDSMCCstream_identifier_descriptorHexSpinBox[5]; /**< TODO: describe */


    SectionDescriptor *PMTDSMCCcarousel_identifier_descriptor[5]; /**< TODO: describe */
    QLabel *PMTDSMCCcarousel_identifier_descriptorLabel[5][2]; /**< TODO: describe */
    HexSpinBox *PMTDSMCCcarousel_identifier_descriptorHexSpinBox[5][2]; /**< TODO: describe */

    SectionDescriptor *PMTDSMCCdata_component_descriptor[5]; /**< TODO: describe */
    ElementSectionDescriptor *PMTDSMCCdata_component_descriptorItem[5]; /**< TODO: describe */
    LabelHexSpinBox *PMTDSMCCdata_component_id[5]; /**< TODO: describe */

    SectionDescriptor *PMTDSMCCadditional_data_component_info[5]; /**< TODO: describe */
    SectionDescriptor *PMTDSMCCadditional_ginga_j_info[5]; /**< TODO: describe */
    LabelHexSpinBox  *PMTDSMCCadditional_ginga_j_infoItem[5][5]; /**< TODO: describe */

    QLayout *AITLayout[5]; /**< TODO: describe */

    LabelHexSpinBox *AITApptype[5]; /**< TODO: describe */

    SectionLoop *AITApploop[5]; /**< TODO: describe */
    SectionLoop *AITApp[5]; /**< TODO: describe */
    ElementSectionDescriptor *AITAppElementSection[5]; /**< TODO: describe */

    QList<LabelHexSpinBox*> *AIT_app_item_widgets[5]; /**< TODO: describe */
    QList<IntParam> AIT_app_items = {{"Organization_ID",0x4E,LabelHexSpinBox::HEXSPINBOX,0x4E,0x4E}, /**< TODO: describe */
                                    {"AppID",0,LabelHexSpinBox::HEXSPINBOX,0x30,0x1FC7},
                                    {"Application Control Code",0,LabelHexSpinBox::HEXSPINBOX,0,65535},
                                    };

    LabelHexSpinBox *AITOrganizationID[5]; /**< TODO: describe */
    LabelHexSpinBox *AITAppID[5]; /**< TODO: describe */
    LabelHexSpinBox *AITAPPControlCode[5]; /**< TODO: describe */

    SectionLoop *AITApp_descriptors_loop[5];

    SectionDescriptor *AITTransportProtocolControlDesc[5]; /**< TODO: describe */
    QList<LabelHexSpinBox*> *AITTransportProtocolControlDesc_item_widgets[5]; /**< TODO: describe */
    QList<IntParam> AITTransportProtocolControlDesc_items = {{"protocol_id",0x4E,LabelHexSpinBox::HEXSPINBOX,0x4E,0x4E}, /**< TODO: describe */
                                                            {"transport_protocol_label",0,LabelHexSpinBox::HEXSPINBOX,0x30,0x1FC7},
                                                            {"remote_connection",0,LabelHexSpinBox::HEXSPINBOX,0,65535},
                                                            {"component_tag",0,LabelHexSpinBox::HEXSPINBOX,0,65535},
                                                            };
    LabelHexSpinBox *AITprotocol_id[5]; /**< TODO: describe */
    LabelHexSpinBox *AITtransport_protocol_label[5]; /**< TODO: describe */
    LabelHexSpinBox *AITremote_connection[5]; /**< TODO: describe */
    LabelHexSpinBox *AITcomponent_tag[5]; /**< TODO: describe */

    SectionDescriptor *AITAppDesc[5]; /**< TODO: describe */
    LabelHexSpinBox *AITapplication_profile[5]; /**< TODO: describe */
    LabelHexSpinBox *AITversion_major[5]; /**< TODO: describe */
    LabelHexSpinBox *AITversion_minor[5]; /**< TODO: describe */
    LabelHexSpinBox *AITversion_micro[5]; /**< TODO: describe */
    LabelHexSpinBox *AITservice_bound_flagr[5]; /**< TODO: describe */
    LabelHexSpinBox *AITvisibility[5]; /**< TODO: describe */
    LabelHexSpinBox *AITapplication_priority[5]; /**< TODO: describe */
    LabelHexSpinBox *AITtransport_protocol_labels[5]; /**< TODO: describe */

    SectionDescriptor *AITApp_name_descriptor[5]; /**< TODO: describe */
    LabelLineEdit *AITapplication_name[5]; /**< TODO: describe */

    SectionDescriptor *ginga_ncl_application_location_descriptor[5]; /**< TODO: describe */
    LabelLineEdit *AITbase_directory[5]; /**< TODO: describe */
    LabelLineEdit *class_path_extension[5]; /**< TODO: describe */
    LabelLineEdit *initial_class[5]; /**< TODO: describe */

    SectionLoop *EIT_loop[5]; /**< TODO: describe */
    SectionDescriptor *EIT_loop_item[5]; /**< TODO: describe */
    QList<LabelHexSpinBox*> *EITelements[5]; /**< TODO: describe */
    QList<IntParam> EIT_items = {{"table_id",0x4E,LabelHexSpinBox::HEXSPINBOX,0x4E,0x4E}, /**< TODO: describe */
                                 {"service_id",90,LabelHexSpinBox::HEXSPINBOX,0x30,0x1FC7},
                                 {"transport_stream_id",90,LabelHexSpinBox::HEXSPINBOX,0,65535},
                                 {"original_network_id",90,LabelHexSpinBox::HEXSPINBOX,0,65535},
                                };

    SectionLoop *EIT_event_loop[5]; /**< TODO: describe */
    SectionDescriptor *EIT_event_loop_item[5]; /**< TODO: describe */

    QList<LabelHexSpinBox*> *EIT_event_loop_widgets[5]; /**< TODO: describe */
    QList<IntParam> EIT_event_loop_items = {{"event_id",1,LabelHexSpinBox::HEXSPINBOX,0,255}, /**< TODO: describe */
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


    SectionLoop *EIT_event_descriptor_loop[5]; /**< TODO: describe */
    SectionDescriptor *EIT_short_event_descriptor[5]; /**< TODO: describe */
    QList<LabelLineEdit*> *EIT_short_event_descriptor_widgets[5]; /**< TODO: describe */


    QList<StringParam> EIT_short_event_descriptor_items = {{"ISO639_language_code","spa",3},
                                                          {"event_name","evento epg presente",25},
                                                          {"text"," Descipcion del evento epg presente",40},
                                                         };

    SectionLoop *EIT_follow_loop[5]; /**< TODO: describe */
    ElementSectionDescriptor *EIT_follow_loop_item[5]; /**< TODO: describe */
    QList<LabelHexSpinBox*> *EIT_follow_elements[5]; /**< TODO: describe */
    QList<IntParam> EIT_follow_items = {{"table_id",0x4E,LabelHexSpinBox::HEXSPINBOX,0x4E,0x4E}, /**< TODO: describe */
                                 {"service_id",80,LabelHexSpinBox::HEXSPINBOX,0x30,0x1FC7},
                                 {"transport_stream_id",80,LabelHexSpinBox::HEXSPINBOX,0,65535},
                                 {"original_network_id",80,LabelHexSpinBox::HEXSPINBOX,0,0xFFFF},
                                };

    SectionLoop *EIT_follow_event_loop[5]; /**< TODO: describe */
    SectionDescriptor *EIT_follow_event_loop_item[5]; /**< TODO: describe */

    QList<LabelHexSpinBox*> *EIT_follow_event_loop_widgets[5]; /**< TODO: describe */
    QList<IntParam> EIT_follow_event_loop_items = {{"event_id",1,LabelHexSpinBox::HEXSPINBOX,0,255}, /**< TODO: describe */
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


