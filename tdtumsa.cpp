//#include <QtWidgets>

#include "tdtumsa.h"

Tdtumsa::Tdtumsa(QWidget *parent)
    : QWizard(parent)
{
    setPage(Page_Intro, new IntroPage);
    setPage(Page_Plan, new PlanPage);
    setPage(Page_Code, new CodePage);
    setPage(Page_Mux, new MuxPage);
    setPage(Page_Final, new FinalPage);
    setStartId(Page_Intro);

#ifndef Q_OS_MACOS
    setWizardStyle(ModernStyle);
#endif
    setPixmap(QWizard::LogoPixmap, QPixmap(":/images/logo.png"));

    setWindowTitle(tr("Televisión Dígital UMSA"));
    setMinimumSize(14*77,9*77);

}

IntroPage::IntroPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Introducción"));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark.png"));
    setSubTitle(tr("El Presente programa le permitirá operar el equipo transmisor de "
                   "televisión digital terrestre a través de todos los procesos."));
    /************************************************
     *  ... Agregar Directorio de Trabajo
     ***********************************************/
    PresentationLabel = new QLabel(tr("Introduzca el \"Directorio de Salida\" para el Paquete TS"));
    PresentationLabel->setWordWrap(true);
    QVBoxLayout *layout = new QVBoxLayout;
    WorkDirectory = new LabelLineEdit(this,tr("Directorio de Trabajo"));
    WorkDirectory_button  = new QPushButton(tr("Buscar"));
    WorkDirectory->setMaximumWidth(700);
    WorkDirectory->layout()->addWidget(WorkDirectory_button); 
    QString uname = qgetenv("USER");
    WorkDirectory->setText("/home/"+uname+"/tdt\n");
    connect(WorkDirectory_button,SIGNAL(clicked()),this,SLOT(notifyFileLoad()));
    /************************************************
     *  ... Agregar Creditos
     ***********************************************/
    CreditLabel = new QLabel(tr("<p><em><span style='color:#ff0000'><strong>Interfaz Desarrollada por Paul Cori. Cualquier consulta o reporte a pcori01@gmail.com</strong></span></em></p>"));
    CreditLabel->setTextFormat(Qt::RichText);
    /************************************************
     *  ... Agrega Elementos al layout
     ***********************************************/
    layout->addWidget(PresentationLabel);
    layout->addWidget(WorkDirectory);
    layout->addWidget(CreditLabel);
    setLayout(layout);
    /************************************************
     *  ... Registra el Directorio de Trabajo
     ***********************************************/
    registerField("WorkDirectory", WorkDirectory,"text");
}

int IntroPage::nextId() const

{
     return Tdtumsa::Page_Plan;
}

void IntroPage::initializePage()

{
}

void IntroPage::notifyFileLoad()
{
    QString Path = QFileDialog::getExistingDirectory(this,tr("Seleccionar Directorio de Trabajo"), "");
    WorkDirectory->setText(Path);
}

PlanPage::PlanPage(QWidget *parent)
    : QWizardPage(parent)
{
    registerField("indexPlan",this,"indexPlan");
    registerField("SevicesPlan",this,"SevicesPlan");

    setTitle(tr("Planificacion Radioelectrica"));
    setSubTitle(tr("Seleccione el Tipo de Planificación que desea utilizar "
                   "para ser transmitida."));
    QGridLayout *layout = new QGridLayout;
    OneSegCheckBox = new QCheckBox(tr("Servicio One-Seg"));
    layout->addWidget(OneSegCheckBox, 0, 1);
    registerField("1seg", OneSegCheckBox);



    for(int i=0;i<5;i++)
           {
                optionRadioButton[i] = new QRadioButton;
                layout->addWidget(optionRadioButton[i], i+1, 1);
                QString namefield = "option"+QVariant(i).toString();
                registerField("option"+QVariant(i).toString(), optionRadioButton[i]);
           }

    optionRadioButton[0]->setText(tr("1 Servicio Full HD (p)"));
    optionRadioButton[0]->setChecked(true);
    optionRadioButton[1]->setText(tr("1 Servicio Full HD (i) + 1 Servicio HD"));
    optionRadioButton[2]->setText(tr("2 Servicios HD"));
    optionRadioButton[3]->setText(tr("1 Servicio HD + 2 Servicios SD"));
    optionRadioButton[4]->setText(tr("4 Servicios SD"));

    setLayout(layout);
}

void PlanPage::initializePage()

{

}

void PlanPage::cleanupPage()
{
}

bool PlanPage::validatePage()
{
    if(field("option0").toBool())
    {
        IndexP=0;
        setSevicesPlan(2);
    }
    if(field("option1").toBool())
    {
        IndexP=1;
        setSevicesPlan(3);
    }
    if(field("option2").toBool())
    {
        IndexP=2;
        setSevicesPlan(3);
    }
    if(field("option3").toBool())
    {
        IndexP=3;
        setSevicesPlan(4);
    }
    if(field("option4").toBool())
    {
        IndexP=4;
        setSevicesPlan(5);
    }
    return  true;
}

int PlanPage::nextId() const
{
    return Tdtumsa::Page_Code;
}

CodePage::CodePage(QWidget *parent)
    : QWizardPage(parent)
{
    QMap<QString,int> bitrate;
    bitrate["One-Seg"]=220;
    bitrate["full-Seg"]=320;

    setTitle(tr("Establesca los parametros de Codificación;"));
    setSubTitle(tr("Seleccione los parámetros"
                   " de Audio y Video. Active la Interactividad si desea enviar una Aplicación Ginga"));
    QGridLayout *layout = new QGridLayout;
    CodeTab = new QTabWidget;
    layout->addWidget(CodeTab, 0, 0);
    for(int i=0;i<5;i++)
    {
        layoutTab[i]=new QGridLayout;
        Filelayout[i]=new QGridLayout;
        Videolayout[i]=new QGridLayout;
        Audiolayout[i]=new QGridLayout;
        Gingalayout[i]=new QGridLayout;

        File[i]=new QGroupBox(tr("Parametros de Video"));
        File[i]->setLayout(Filelayout[i]);

        Video[i]=new QGroupBox(tr("Parametros de Video"));
        Video[i]->setLayout(Videolayout[i]);

        Audio[i]=new QGroupBox(tr("Parametros de Audio"));
        Audio[i]->setLayout(Audiolayout[i]);

        GingaCheckBox[i] = new QCheckBox(tr("Interactividad"));
        registerField("GingaApp"+QVariant(i).toString(), GingaCheckBox[i]);

        Ginga[i]=new QGroupBox(tr("Interactividad"));
        Ginga[i]->setLayout(Gingalayout[i]);
        Ginga[i]->setDisabled(true);

        tabWidget[i]=new QWidget;
        CodeTab->addTab(tabWidget[i], tr("Servicio"));

        videoLabel[i] = new QLabel(tr("&Archivo \nde Video:"));
        videoLineEdit[i] = new QLineEdit;        
        videoLabel[i]->setBuddy(videoLineEdit[i]);
        registerField("File"+QVariant(i).toString(),videoLineEdit[i]);
        videoButton[i] = new QPushButton(tr("Buscar"));

        videoBitrateLabel[i] = new QLabel(tr("Bitrate \nVideo [Mbps]:"));
        videoSlider[i] = new DoubleSlider;
        videoSpinBox[i] = new QDoubleSpinBox;
        videoSpinBox[i]->setMaximumWidth(80);
        vResolutionLabel[i] = new QLabel(tr("Resolución"));
        vResolutionComboBox[i] = new QComboBox;
        videoFPSLabel[i] = new QLabel(tr("Frames \npor Segundo"));
        videoFPSComboBox[i] = new QComboBox;
        videoRALabel[i] = new QLabel(tr("Relacion \nde Apecto"));
        videoRAComboBox[i] = new QComboBox;
        videoRAComboBox[i]->addItem(tr("16:9"));
        videoPerfilLabel[i] = new QLabel(tr("Perfil \nH.264"));
        videoPerfilComboBox[i] = new QComboBox;
        videoNivelLabel[i] = new QLabel(tr("Nivel \nH.264"));
        videoNivelComboBox[i] = new QComboBox;
        videoNivelComboBox[i]->addItem(tr("4.0"));

        registerField("VideoBitRate"+QVariant(i).toString(), videoSpinBox[i],"value","valueChanged");
        registerField("VideoResolution"+QVariant(i).toString(),vResolutionComboBox[i],"currentText",SIGNAL(valueChanged(int)));
        registerField("VideoFPS"+QVariant(i).toString(),videoFPSComboBox[i],"currentText",SIGNAL(valueChanged(int)));
        registerField("VideoRA"+QVariant(i).toString(),videoRAComboBox[i],"currentText",SIGNAL(valueChanged(int)));
        registerField("VideoPerfil"+QVariant(i).toString(),videoPerfilComboBox[i],"currentText",SIGNAL(valueChanged(int)));
        registerField("VideoLevel"+QVariant(i).toString(),videoNivelComboBox[i],"currentText",SIGNAL(valueChanged(int)));

        audioBitrateLabel[i] = new QLabel(tr("Bitrate \nAudio [Kbps]:"));
        audioSlider[i] = new QSlider(Qt::Horizontal);
        audioSpinBox[i] = new QSpinBox;
        audioSpinBox[i]->setMaximumWidth(80);
        aSampleRateLabel[i] = new QLabel(tr("Frecuencia \nde Muestreo:"));
        aSampleRateComboBox[i] = new QComboBox;
        aChanelsLabel[i] = new QLabel(tr("Canales \nde Audio:"));
        aChanelsComboBox[i] = new QComboBox;
        aCodecLabel[i] = new QLabel(tr("Perfil \nde Audio:"));
        aCodecComboBox[i] =new QComboBox;

        registerField("AudioBitRate"+QVariant(i).toString(), audioSpinBox[i],"value","valueChanged");
        registerField("AudioChannels"+QVariant(i).toString(),aChanelsComboBox[i],"currentText",SIGNAL(valueChanged(int)));
        registerField("AudioPerfil"+QVariant(i).toString(),aCodecComboBox[i],"currentText",SIGNAL(valueChanged(int)));
        registerField("AudioSampleRate"+QVariant(i).toString(),aSampleRateComboBox[i],"currentText",SIGNAL(valueChanged(int)));

        GingaLabel[i] = new QLabel(tr("Archivo \nde Ginga:"));
        GingaRateLabel[i] = new QLabel(tr("BitRate \nde Ginga:"));

        GingaLineEdit[i] = new QLineEdit;
        registerField("GingaAppDir"+QVariant(i).toString(), GingaLineEdit[i]);
        GingaLabel[i]->setBuddy(GingaLineEdit[i]);
        GingaSlider[i] = new DoubleSlider;
        GingaSpinBox[i] = new QDoubleSpinBox;
        registerField("GingaBitRate"+QVariant(i).toString(), GingaSpinBox[i],"value","valueChanged");

        GingaButton[i] = new QPushButton(tr("Buscar"));

        Filelayout[i]->addWidget(videoLabel[i],0,0);
        Filelayout[i]->addWidget(videoLineEdit[i],0,1,1,6);
        Filelayout[i]->addWidget(videoButton[i],0,7);

        layoutTab[i]->addWidget(File[i],0,0,1,6);
        layoutTab[i]->addWidget(Video[i],1,0,1,5);
        layoutTab[i]->addWidget(Audio[i],2,0,1,4);
        layoutTab[i]->addWidget(GingaCheckBox[i],3,0);
        layoutTab[i]->addWidget(Ginga[i],4,0,1,6);
        layoutTab[i]->setSizeConstraint(QLayout::SetFixedSize);

        Videolayout[i]->addWidget(videoBitrateLabel[i],0,0);
        Videolayout[i]->addWidget(videoSlider[i],0,1);
        Videolayout[i]->addWidget(videoSpinBox[i],0,2);
        Videolayout[i]->addWidget(vResolutionLabel[i],0,3);
        Videolayout[i]->addWidget(vResolutionComboBox[i],0,4);
        Videolayout[i]->addWidget(videoFPSLabel[i],0,5);
        Videolayout[i]->addWidget(videoFPSComboBox[i],0,6);
        Videolayout[i]->addWidget(videoRALabel[i],1,0);
        Videolayout[i]->addWidget(videoRAComboBox[i],1,1);
        Videolayout[i]->addWidget(videoPerfilLabel[i],1,2);
        Videolayout[i]->addWidget(videoPerfilComboBox[i],1,3);
        Videolayout[i]->addWidget(videoNivelLabel[i],1,4);
        Videolayout[i]->addWidget(videoNivelComboBox[i],1,5);

        Audiolayout[i]->addWidget(audioBitrateLabel[i],0,0);
        Audiolayout[i]->addWidget(audioSlider[i],0,1);
        Audiolayout[i]->addWidget(audioSpinBox[i],0,2);
        Audiolayout[i]->addWidget(aSampleRateLabel[i],0,3);
        Audiolayout[i]->addWidget(aSampleRateComboBox[i],0,4);
        Audiolayout[i]->addWidget(aChanelsLabel[i],1,0);
        Audiolayout[i]->addWidget(aChanelsComboBox[i],1,1);
        Audiolayout[i]->addWidget(aCodecLabel[i],1,2);
        Audiolayout[i]->addWidget(aCodecComboBox[i],1,4);

        Gingalayout[i]->addWidget(GingaLabel[i],0,0);
        Gingalayout[i]->addWidget(GingaLineEdit[i],0,1,1,4);
        Gingalayout[i]->addWidget(GingaButton[i],0,5);
        Gingalayout[i]->addWidget(GingaRateLabel[i],1,0);
        Gingalayout[i]->addWidget(GingaSlider[i],1,1);
        Gingalayout[i]->addWidget(GingaSpinBox[i],1,2);

        connect(videoSlider[i],SIGNAL(valueChanged(int)),videoSlider[i],SLOT(notifyValueChanged(int)));
        connect(videoSlider[i],SIGNAL(doubleValueChanged(double)),videoSpinBox[i],SLOT(setValue(double)));

        connect(videoSpinBox[i],SIGNAL(valueChanged(double)),videoSlider[i],SLOT(notifydoubleChanged(double)));
        connect(videoSlider[i],SIGNAL(intValueChanged(int)),videoSlider[i],SLOT(setValue(int)));

        connect(GingaSlider[i],SIGNAL(valueChanged(int)),GingaSlider[i],SLOT(notifyValueChanged(int)));
        connect(GingaSlider[i],SIGNAL(doubleValueChanged(double)),GingaSpinBox[i],SLOT(setValue(double)));

        connect(GingaSpinBox[i],SIGNAL(valueChanged(double)),GingaSlider[i],SLOT(notifydoubleChanged(double)));
        connect(GingaSlider[i],SIGNAL(intValueChanged(int)),GingaSlider[i],SLOT(setValue(int)));

        connect(audioSlider[i],SIGNAL(valueChanged(int)),audioSpinBox[i],SLOT(setValue(int)));
        connect(audioSpinBox[i],SIGNAL(valueChanged(int)),audioSlider[i],SLOT(setValue(int)));

        connect(videoButton[i],SIGNAL(released()),this,SLOT(notifyFileLoad()));
        connect(GingaButton[i],SIGNAL(released()),this,SLOT(notifyFileLoad()));


        audioSlider[i]->setRange(96,256);
        audioSpinBox[i]->setRange(96,256);

        aSampleRateComboBox[i]->addItems(QStringList() <<"48000" << "44100");
        aChanelsComboBox[i]->addItems(QStringList() << "2"<< "6");
        aCodecComboBox[i]->addItems(QStringList() << "aac_low"<< "aac_he");

        connect(aSampleRateComboBox[i],SIGNAL(currentIndexChanged(int)),this,SLOT(notifyAudioChanges()));
        connect(aChanelsComboBox[i],SIGNAL(currentIndexChanged(int)),this,SLOT(notifyAudioChanges()));
        connect(aCodecComboBox[i],SIGNAL(currentIndexChanged(int)),this,SLOT(notifyAudioChanges()));
        connect(GingaCheckBox[i],SIGNAL(clicked(bool)),Ginga[i],SLOT(setEnabled(bool)));

        videoSpinBox[i]->setSingleStep(0.1);
        videoSlider[i]->setSingleStep(1);
        tabWidget[i]->setLayout(layoutTab[i]);
        //tabWidget[i]->setMaximumSize(1280,480);
        }
        setLayout(layout);

        //Introducimos los Parametros del Servicio One-seg dado que estos permanecen iguales en Todos los modelos
        aSampleRateComboBox[0]->addItems(QStringList() << "32000");
        aChanelsComboBox[0]->clear();
        aChanelsComboBox[0]->addItem("2");
        vResolutionComboBox[0]->addItems({"cif","qvga","qqvga"});
        videoFPSComboBox[0]->addItems({"5000/1001","10000/1001","12000/1001","15000/1001","24000/1001","30000/1001"});
        aCodecComboBox[0]->clear();
        aCodecComboBox[0]->addItem(tr("aac_he_v2"));
        videoBitrateLabel[0]->setText(tr("Bitrate \nVideo [Kbps]:"));
        videoSlider[0]->setRange(640,7680);
        videoSpinBox[0]->setRange(64.0,768.0);
        videoSpinBox[0]->setSingleStep(1.0);
        videoSlider[0]->setSingleStep(10);
        videoRAComboBox[0]->addItems({"16:9","4:3"});
        audioSpinBox[0]->setRange(24,32);
        videoNivelComboBox[0]->clear();
        videoNivelComboBox[0]->addItem(tr("1.3"));
        videoPerfilComboBox[0]->addItem(tr("baseline"));
        audioSpinBox[0]->setSingleStep(1);
        audioSlider[0]->setRange(24,32);
        audioSlider[0]->setSingleStep(10);

        CodeTab->setTabText(0,tr("Servicio One-Seg"));
}

void CodePage::initializePage()
{
    QStringList TabText[5], ResolutionText[5], PerfilText[3], FpsText[5], RA[5];
    QVector<int> VRange[5], PerfilIndex[5], FpsIndex[5],RAIndex[5];
    QVector<double> VRangeD[5];

    TabText[0]<<"Servicio One-Seg"<<"Servicio Full HD";
    TabText[1]<<"Servicio One-Seg"<<"Servicio Full HD"<<"Servicio HD";
    TabText[2]<<"Servicio One-Seg"<<"Servicio HD 1"<<"Servicio HD 2";
    TabText[3]<<"Servicio One-Seg"<<"Servicio HD"<<"Servicio SD 1"<<"Servicio SD 2";
    TabText[4]<<"Servicio One-Seg"<<"Servicio SD 1"<<"Servicio SD 2"<<"Servicio SD 3"<<"Servicio SD 4";

    ResolutionText[0]<<"1920:1080";
    ResolutionText[1]<<"1920:1080"<<"1280:720";
    ResolutionText[2]<<"1280:720"<<"1280:720";
    ResolutionText[3]<<"1280:720"<<"720:480"<<"720:480";
    ResolutionText[4]<<"720:480"<<"720:480"<<"720:480"<<"720:480";

    PerfilIndex[0]<<1;
    PerfilIndex[1]<<1<<1;
    PerfilIndex[2]<<1<<1;
    PerfilIndex[3]<<1<<2<<2;
    PerfilIndex[4]<<2<<2<<2<<2;

    PerfilText[0]<<"baseline";
    PerfilText[1]<<"high";
    PerfilText[2]<<"main"<<"high";

    VRange[0]<<150<<200;
    VRange[1]<<100<<120<<30<<45;
    VRange[2]<<60<<90<<60<<90;
    VRange[3]<<60<<90<<30<<45<<30<<45;
    VRange[4]<<30<<45<<30<<45<<30<<45<<30<<45;

    FpsText[0]<<"25"<<"50"<<"30000/1001"<<"60000/1001";
    FpsText[1]<<"30000/1001"<<"60000/1001";

    RA[0]<<"16:9"<<"4:3";
    RA[1]<<"16:9";

    FpsIndex[0]<<0;
    FpsIndex[1]<<1<<0;
    FpsIndex[2]<<0<<0;
    FpsIndex[3]<<0<<0<<0;
    FpsIndex[4]<<0<<0<<0<<0;

    RAIndex[0]<<0;
    RAIndex[1]<<1<<1;
    RAIndex[2]<<1<<1;
    RAIndex[3]<<1<<0<<0;
    RAIndex[4]<<0<<0<<0<<0;

    for(int it=1;it<5;it++)
    {
        vResolutionComboBox[it]->clear();
        videoPerfilComboBox[it]->clear();
        videoFPSComboBox[it]->clear();
        videoRAComboBox[it]->clear();
    }

    CodeTab->clear();

    int index=field("indexPlan").toInt();
    int aux=field("SevicesPlan").toInt();

    for(int i=1;i<aux;i++)
    {
        CodeTab->setTabText(i,TabText[index][i]);
        videoSlider[i]->setRange(VRange[index][2*(i-1)],VRange[index][2*i-1]);
        //Iteramos los valores almacenados en VRange
        videoSpinBox[i]->setRange(QVariant(VRange[index][2*(i-1)]).toDouble()/10.0,
                                    QVariant(VRange[index][2*i-1]).toDouble()/10.0);
        vResolutionComboBox[i]->addItem(ResolutionText[index][i-1]);
        videoPerfilComboBox[i]->addItems(PerfilText[PerfilIndex[index][i-1]]);
        videoFPSComboBox[i]->addItems(FpsText[FpsIndex[index][i-1]]);
        videoRAComboBox[i]->addItems(RA[RAIndex[index][i-1]]);
    }

    if(field("1seg").toBool())
    {
        CodeTab->addTab(tabWidget[0], TabText[index][0]);

    }
    for(int it=1;it<aux;it++)
    {
        CodeTab->addTab(tabWidget[it], TabText[index][it]);
    }
}

void CodePage::cleanupPage()

{
}

int CodePage::nextId() const
{
      return Tdtumsa::Page_Mux;
}


bool CodePage::validatePage()

{
    int aux = 0;
    bool validation=true;
    if(field("option0").toBool())
    {
        aux=2;
    }
    if(field("option1").toBool())
    {
        aux=3;
    }
    if(field("option2").toBool())
    {
        aux=3;
    }
    if(field("option3").toBool())
    {
        aux=4;
    }
    if(field("option4").toBool())
    {
        aux=5;
    }
    if(field("1seg").toBool())
    {
        validation&=!videoLineEdit[0]->text().isEmpty();
        validation&=!((!GingaLineEdit[0]->text().isEmpty())^(Ginga[0]->isEnabled()));
    }

    for(int it=1;it<aux;it++)
    {
        validation&=!videoLineEdit[it]->text().isEmpty();
        validation&=!((!GingaLineEdit[it]->text().isEmpty())^(Ginga[it]->isEnabled()));
    }
    if (!validation)
    {
        QMessageBox::information(this,"Error","Verificar que se haya cargado todos los archivos necesarios");
    }

    return validation;
}


/**
 * @brief
 *
 * @fn CodePage::notifyVideoLoad
 */
void CodePage::notifyFileLoad()
{
    int oneseg=field("1seg").toInt();

    if(this->sender()==videoButton[CodeTab->currentIndex()+1-oneseg]){
        QString fileName = QFileDialog::getOpenFileName(this,
               tr("Abrir un archivo de video"), "",
               tr("Video Files (*.mp4 *.mkv *.ogv *.avi);;All Files (*)"));
        videoLineEdit[CodeTab->currentIndex()+1-oneseg]->setText(fileName);
    }
    if(this->sender()==GingaButton[CodeTab->currentIndex()+1-oneseg]){
        QString Path = QFileDialog::getExistingDirectory(this,tr("Abrir Directorio"), "");
        GingaLineEdit[CodeTab->currentIndex()+1-oneseg]->setText(Path);
    }

}


void CodePage::notifyAudioChanges()
{

        int index=CodeTab->currentIndex()+1;
        QVector<int> AudioBitratemin[2][2], AudioBitratemax[2][2],
                Audio1sBitrate[2];

        AudioBitratemin[0][0]={96,288};
        AudioBitratemin[0][1]={48,160};
        AudioBitratemin[1][0]={86,259};
        AudioBitratemin[1][1]={43,144};

        AudioBitratemax[0][0]={256,384};
        AudioBitratemax[0][1]={128,256};
        AudioBitratemax[1][0]={230,346};
        AudioBitratemax[1][1]={115,230};

        Audio1sBitrate[0]={32,32,32};
        Audio1sBitrate[1]={64,56,48};

        if((this->sender()==aSampleRateComboBox[0])||((this->sender()==aChanelsComboBox[0])))
        {
            audioSlider[0]->setRange(Audio1sBitrate[0][aSampleRateComboBox[0]->currentIndex()],
                                    Audio1sBitrate[1][aSampleRateComboBox[0]->currentIndex()]);
            audioSpinBox[0]->setRange(Audio1sBitrate[0][aSampleRateComboBox[0]->currentIndex()],
                                    Audio1sBitrate[1][aSampleRateComboBox[0]->currentIndex()]);
        }

        else if((this->sender()!=aSampleRateComboBox[0])&&(this->sender()!=aCodecComboBox[0]))
        {
            audioSlider[index]->setRange(AudioBitratemin[aSampleRateComboBox[index]->currentIndex()][aCodecComboBox[index]->currentIndex()][aChanelsComboBox[index]->currentIndex()]
                                         ,AudioBitratemax[aSampleRateComboBox[index]->currentIndex()][aCodecComboBox[index]->currentIndex()][aChanelsComboBox[index]->currentIndex()]);
            audioSpinBox[index]->setRange(AudioBitratemin[aSampleRateComboBox[index]->currentIndex()][aCodecComboBox[index]->currentIndex()][aChanelsComboBox[index]->currentIndex()]
                                         ,AudioBitratemax[aSampleRateComboBox[index]->currentIndex()][aCodecComboBox[index]->currentIndex()][aChanelsComboBox[index]->currentIndex()]);
        }
    }

MuxPage::MuxPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Establesca los Parametros de Multiplexación"));
    setSubTitle(tr("Establesca todos lo parametros de las diferentes Tablas PSI/SI, "
                   "Tenga en cuenta que algunos valores están restringidos y/o se modificaran automaticamente"));

    QStringList TabText, PMTStreamLoopText[5];
    TabText << "PAT" << "NIT" << "SDT" << "TOT"
            << "PMT1"<<"EIT1"<<"AIT1"<<"PMT2"<<"EIT2"<<"AIT2"<<"PMT3"<<"EIT3"<<"AIT3"<<"PMT4"<<"EIT4"<<"AIT4"<<"PMT5"<<"EIT5"<<"AIT5";

    PMTStreamLoopText[0]<<"Stream Type Video"<<"PID Video";
    PMTStreamLoopText[1]<<"Stream Type Audio"<<"PID Audio";
    PMTStreamLoopText[2]<<"Stream Type AIT"<<"PID AIT";
    PMTStreamLoopText[3]<<"Stream Type DSMCC"<<"PID DSMCC";

    QStringList PMTAITait_identifier_infoText = {"application_type","ait_version"};
    QStringList application_signalling_descriptor = {"application_type","ait_version"};
    QStringList PMTDSMCCassociation_tag_descriptorText = {"association_tag","use","selector_lenght","transaction_id","timeout"};
    QStringList additional_ginga_j_infoItemText = {"transmission_format","document_resolution",
                                                   "organization_id","application_id","carousel_id"};
    QStringList SDTServiceLoopElementText = {"service ID","EIT_schedule_flag","EIT_present_following_flag","running_status","free_CA_mode"};

    QList<int> SDTServiceLoopElementValues = {1,0,0,4,0};

    QVBoxLayout *layout = new QVBoxLayout;
    MuxTab = new QTabWidget(this);
    layout->addWidget(MuxTab);
    MuxTab->setUsesScrollButtons(true);

    for(int i=0;i<TabText.size();i++){
        layoutTab[i]=new QVBoxLayout;
        layoutTab[i]->setSizeConstraint(QLayout::SetFixedSize);
        tabWidget[i]=new QWidget;
        scrollArea[i] = new QScrollArea;
        scrollArea[i]->setWidget(tabWidget[i]);
        scrollArea[i]->setBackgroundRole(QPalette::Light);
        scrollArea[i]->setVisible(false);
        MuxTab->addTab(scrollArea[i],TabText[i]);
        tabWidget[i]->setLayout(layoutTab[i]);
    }

    PATTSID=new LabelHexSpinBox(this,tr("Transport Stream ID"));
    registerField("Transport Stream ID",PATTSID,"value");
    layoutTab[0]->addWidget(PATTSID);

    PATProgramLoop = new SectionLoop(this,tr("Program Loop"));
    layoutTab[0]->addWidget(PATProgramLoop);

    NITNetworkID = new LabelHexSpinBox(this,tr("Network ID"));
    layoutTab[1]->addWidget(NITNetworkID);
    connect(NITNetworkID,SIGNAL(valueChanged(int)),this,SLOT(MuxChanges(int)));

    NITNetworkDescLoop = new SectionLoop(this,tr("network descriptor loop"));
    layoutTab[1]->addWidget(NITNetworkDescLoop);

    NITNetworkDesc = new SectionDescriptor(this,tr("network_descriptor"));
    NITNetworkDescLoop->layout()->addWidget(NITNetworkDesc);

    NITNetworkName = new LabelLineEdit(this,tr("Network Name"));
    registerField("Network Name",NITNetworkName,"text");
    NITNetworkName->setText(tr("UMSA NETWORK"));
    NITNetworkDesc->layout()->addWidget(NITNetworkName);

    NITSystemMngDesc = new SectionDescriptor(this,tr("system_management_descriptor"));
    NITNetworkDescLoop->layout()->addWidget(NITSystemMngDesc);

    NITSystemMngDesc_widgets= new QList<LabelHexSpinBox*>;
    foreach (const IntParam &item, NITSystemMngDesc_item) {
        NITSystemMngDesc_widgets->append(new LabelHexSpinBox(this,item.name));
        NITSystemMngDesc_widgets->last()->setRange(item.min,item.max);
        NITSystemMngDesc_widgets->last()->setValue(item.value);
        NITSystemMngDesc->layout()->addWidget(NITSystemMngDesc_widgets->last());
        registerField(item.name,NITSystemMngDesc_widgets->last(),"value");
    }

    NITTSLoop=new SectionLoop(this,tr("Transport Stream Loop"));
    layoutTab[1]->addWidget(NITTSLoop);

    NITTSLoopItem=new SectionLoop(this,tr("Transport Stream"));
    NITTSLoop->layout()->addWidget(NITTSLoopItem);

    NITTSItem = new ElementSectionDescriptor(this);
    NITTSLoopItem->layout()->addWidget(NITTSItem);

    NITTSID = new LabelHexSpinBox(this,tr("Transport Stream ID"));
    NITTSItem->layout()->addWidget(NITTSID);

    NITOriginNetworkID = new LabelHexSpinBox(this,tr("Original Network ID"));
    NITTSItem->layout()->addWidget(NITOriginNetworkID);

    NITTSTransportDescLoop = new SectionLoop(this,tr("transport descriptor loop"));
    NITTSLoopItem->layout()->addWidget(NITTSTransportDescLoop);

    NITServiceListDesc = new SectionLoop(this,tr("service_list_descriptor"));
    NITTSTransportDescLoop->layout()->addWidget(NITServiceListDesc);

    NITTerrestrialDeliverySystemDesc = new SectionDescriptor(this,tr("terrestrial delivery system descriptor"));
    NITTSTransportDescLoop->layout()->addWidget(NITTerrestrialDeliverySystemDesc);

    NITAreaCode =new LabelHexSpinBox(this,tr("Area Code"));
    NITTerrestrialDeliverySystemDesc->layout()->addWidget(NITAreaCode);

    transport_stream_information_descriptor = new SectionLoop(this,tr("Transport Stream Information Descriptor"));
    NITTSTransportDescLoop->layout()->addWidget(transport_stream_information_descriptor);

    transport_stream_information_descriptorItem = new ElementSectionDescriptor;
    transport_stream_information_descriptor->layout()->addWidget(transport_stream_information_descriptorItem);

    remote_control_key_id=new LabelHexSpinBox(this,tr("remote control key id"));
    remote_control_key_id->setRange(1,99);
    registerField("remote control key id",remote_control_key_id,"value");
    transport_stream_information_descriptorItem->layout()->addWidget(remote_control_key_id);

    ts_name = new LabelLineEdit(this,tr("ts name"));
    ts_name->setText(tr("UMSA TS"));
    registerField("tsname",ts_name ,"text");
    transport_stream_information_descriptorItem->layout()->addWidget(ts_name);

    SDTItem = new ElementSectionDescriptor(this);
    layoutTab[2]->addWidget(SDTItem);

    SDTTSID = new LabelHexSpinBox(this,tr("Transport Stream ID"));
    SDTItem->layout()->addWidget(SDTTSID);

    SDTNetworkID =new LabelHexSpinBox(this,tr("Network ID"));
    SDTItem->layout()->addWidget(SDTNetworkID);

    SDTServiceLoop=new SectionLoop(this,tr("Service Loop"));
    layoutTab[2]->addWidget(SDTServiceLoop);

    TOT_Layout = new QFormLayout;
    TOT_Label = new QList<QLabel*>;
    foreach(QString str, TOT_items){
        TOT_Label->append(new QLabel("<span style=\"color:#ff0000\"><strong>ESTE DATO SERA AGREGADO AUTOMATICAMENTE AL EJECUTAR DE ACUERDO AL SISTEMA</strong></span>"));
        TOT_Layout->addRow(str,TOT_Label->last());
        TOT_Label->last()->setTextFormat(Qt::RichText);
        TOT_Label->last()->setFrameStyle(QFrame::Panel | QFrame::Plain);
    }
    TOT_Widget = new QWidget;
    TOT_Widget->setLayout(TOT_Layout);
    layoutTab[3]->addWidget(TOT_Widget);

    TOT_descriptor_Loop = new SectionLoop(this,tr("descriptor_loop"));
    layoutTab[3]->addWidget(TOT_descriptor_Loop);
    TOT_Label->append(new QLabel("<span style=\"color:#ff0000\"><strong>NO DESCRIPTORES VALIDOS PARA BOLIVIA, AL NO TENER HORARIO DE INVIERNO</strong></span>"));
    TOT_descriptor_Loop->layout()->addWidget(TOT_Label->last());
    TOT_Label->last()->setTextFormat(Qt::RichText);
    TOT_Label->last()->setFrameStyle(QFrame::Panel | QFrame::Plain);

    connect(PATTSID,SIGNAL(valueChanged(int)),
                    NITTSID,SLOT(setValue(int)));
    connect(NITTSID,SIGNAL(valueChanged(int)),
                    SDTTSID,SLOT(setValue(int)));
    connect(SDTTSID,SIGNAL(valueChanged(int)),
                    PATTSID,SLOT(setValue(int)));

    connect(NITNetworkID,SIGNAL(valueChanged(int)),
                    NITOriginNetworkID,SLOT(setValue(int)));
    connect(NITOriginNetworkID,SIGNAL(valueChanged(int)),
                    SDTNetworkID,SLOT(setValue(int)));
    connect(SDTNetworkID,SIGNAL(valueChanged(int)),
                    NITNetworkID,SLOT(setValue(int)));


    for(int i=0;i<5;i++)
    {

        layoutTab[i]->setSizeConstraint(QLayout::SetFixedSize);
        PATService[i]=new QGroupBox(tr("Servicio ")+QString::number(i));

        PATprogram_loop_item[i] = new SectionDescriptor(this,tr("Servicio ")+QString::number(i));
        PATProgramLoop->layout()->addWidget(PATprogram_loop_item[i]);

        PATServiceID[i] = new LabelHexSpinBox(this,tr("Program_Number"));
        PATprogram_loop_item[i]->layout()->addWidget(PATServiceID[i]);

        PATServicePID[i] = new LabelHexSpinBox(this,tr("Program_MAP_PID"));
        PATprogram_loop_item[i]->layout()->addWidget(PATServicePID[i]);

        registerField("ServiceID"+QString("%1").arg(i),PATServiceID[i],"value");
        registerField("ServicePID"+QString("%1").arg(i),PATServicePID[i],"value");

        PATServicePID[i]->setRange(0x30,0x1FC7);

        NITService[i]=new SectionDescriptor(this,tr("Servicio ")+QString::number(i));
        NITServiceListDesc->layout()->addWidget(NITService[i]);

        NITServiceID[i]=new LabelHexSpinBox(this,tr("Service_ID"));
        NITService[i]->layout()->addWidget(NITServiceID[i]);

        NITServiceType[i]=new LabelHexSpinBox(this,tr("Service Type"));
        NITService[i]->layout()->addWidget(NITServiceType[i]);
        NITServiceType[i]->setRange(1,1);


        SDTServiceLoopItem[i]=new SectionLoop(this,tr("Servicio ")+QString::number(i));
        SDTServiceLoop->layout()->addWidget(SDTServiceLoopItem[i]);

        SDTServiceLoopElement[i]=new ElementSectionDescriptor;
        SDTServiceLoopItem[i]->layout()->addWidget(SDTServiceLoopElement[i]);


        for(int it=0;it<5;it++){
            SDTServiceLoopElementWidget[i][it]=new LabelHexSpinBox(this,SDTServiceLoopElementText[it]);
            SDTServiceLoopElementWidget[i][it]->setObjectName(SDTServiceLoopElementText[it]+QString("%1").arg(i));
            SDTServiceLoopElementWidget[i][it]->setRange(SDTServiceLoopElementValues[it],SDTServiceLoopElementValues[it]);
            SDTServiceLoopElement[i]->layout()->addWidget(SDTServiceLoopElementWidget[i][it]);
        }

        SDTServiceDescLoop[i] = new SectionLoop(this,tr("Service Descriptor Loop"));
        SDTServiceLoopItem[i]->layout()->addWidget(SDTServiceDescLoop[i]);

        SDTServiceDesc[i]=new SectionDescriptor(this,tr("Service Descriptor"));
        SDTServiceDescLoop[i]->layout()->addWidget(SDTServiceDesc[i]);

        SDTServiceType[i]=new LabelHexSpinBox(this,tr("Service Type"));
        SDTServiceType[i]->setRange(1,1);
        SDTServiceDesc[i]->layout()->addWidget(SDTServiceType[i]);

        SDTServiceProviderName[i]=new LabelLineEdit(this,tr("Service Provider Name"));
        SDTServiceProviderName[i]->setText("UMSA TV");
        registerField("Service Provider Name"+QVariant(i).toString(),SDTServiceProviderName[i],"text");
        SDTServiceDesc[i]->layout()->addWidget(SDTServiceProviderName[i]);

        SDTServiceName[i]=new LabelLineEdit(this,tr("Service Name"));
        SDTServiceName[i]->setText(QString("UMSA %1").arg(i));
        registerField("Service Name"+QVariant(i).toString(),SDTServiceName[i],"text");
        SDTServiceDesc[i]->layout()->addWidget(SDTServiceName[i]);

        PMTProgramNumber[i] = new LabelHexSpinBox(this,tr("Program Number"));
        PMTProgramNumber[i]->setRange(0x30,0x1FC7);
        registerField("PID PMT"+QVariant(i).toString(),PMTProgramNumber[i],"value");

        layoutTab[3*i+4]->addWidget(PMTProgramNumber[i]);

        PMTStreamLoop[i] = new SectionLoop(this,"Stream Loop");
        PMTVideo[i] = new SectionDescriptor(this,"Video");
        PMTAudio[i] = new SectionDescriptor(this,"Audio");
        PMTAIT[i] = new SectionLoop(this,"AIT Stream");
        PMTDSMCC[i] = new SectionLoop(this,"DSMCC Stream");

        layoutTab[3*i+4]->addWidget(PMTStreamLoop[i]);
        PMTStreamLoop[i]->layout()->addWidget(PMTVideo[i]);
        PMTStreamLoop[i]->layout()->addWidget(PMTAudio[i]);
        PMTStreamLoop[i]->layout()->addWidget(PMTAIT[i]);
        PMTStreamLoop[i]->layout()->addWidget(PMTDSMCC[i]);

        for(int it=0;it<2;it++){
            PMTVideoItem[i][it]= new LabelHexSpinBox(this,PMTStreamLoopText[0][it]);
            registerField(PMTStreamLoopText[0][it]+QVariant(i).toString(),PMTVideoItem[i][it],"value");
            PMTVideoItem[i][it]->setRange(0x30,0x1FC7);
            PMTVideo[i]->layout()->addWidget(PMTVideoItem[i][it]);

            PMTAudioItem[i][it]= new LabelHexSpinBox(this,PMTStreamLoopText[1][it]);
            registerField(PMTStreamLoopText[1][it]+QVariant(i).toString(),PMTAudioItem[i][it],"value");
            PMTAudioItem[i][it]->setRange(0x30,0x1FC7);
            PMTAudio[i]->layout()->addWidget(PMTAudioItem[i][it]);
        }

        PMTAudioItem[i][1]->setValue(0x50+i);
        PMTVideoItem[i][1]->setValue(0x40+i);

        PMTAITItem[i] = new ElementSectionDescriptor(this);
        for(int it=0;it<2;it++){
            PMTAITWidgetItem[i][it]=new LabelHexSpinBox(this,PMTStreamLoopText[2][it]);
            PMTAITItem[i]->layout()->addWidget(PMTAITWidgetItem[i][it]);
            registerField(PMTStreamLoopText[2][it]+QVariant(i).toString(),PMTAITWidgetItem[i][it],"value");
        }
        PMTAITWidgetItem[i][0]->setRange(0x05,0x05);
        PMTAITWidgetItem[i][1]->setRange(0x30,0x1FC7);
        PMTAITWidgetItem[i][1]->setValue(0x7D0+i);

        PMTAIT[i]->layout()->addWidget(PMTAITItem[i]);

        PMTAITelement_info_descriptor_loop[i] = new SectionLoop(this,"element_info_descriptor_loop");
        PMTAIT[i]->layout()->addWidget(PMTAITelement_info_descriptor_loop[i]);
        PMTAITdata_component_descriptor[i] =new SectionDescriptor(this,"data_component_descriptor");
        PMTAITelement_info_descriptor_loop[i]->layout()->addWidget(PMTAITdata_component_descriptor[i]);

        PMTAITdata_component_descriptorItem[i] = new LabelHexSpinBox(this,"data component id");
        PMTAITdata_component_descriptorItem[i]->setRange((i==0)?0xA4:0xA3,(i==0)?0xA4:0xA3);
        PMTAITdata_component_descriptor[i]->layout()->addWidget(PMTAITdata_component_descriptorItem[i]);

        registerField("data_component_id"+QVariant(i).toString(),
                                        PMTAITdata_component_descriptorItem[i]);

        PMTAITadditional_data_component_info[i] = new SectionDescriptor(this,"additional_data_component_info");
        PMTAITdata_component_descriptor[i]->layout()->addWidget(PMTAITadditional_data_component_info[i]);
        PMTAITait_identifier_info[i] = new SectionDescriptor(this,"ait_identifier_info");
        PMTAITadditional_data_component_info[i]->layout()->addWidget(PMTAITait_identifier_info[i]);
        for(int it=0;it<2;it++){
            PMTAITait_identifier_infoLabel[i][it] = new QLabel(PMTAITait_identifier_infoText[it]);
            PMTAITait_identifier_info[i]->layout()->addWidget(PMTAITait_identifier_infoLabel[i][it]);
            PMTAITait_identifier_infoHexSpinBox[i][it] = new HexSpinBox;
            PMTAITait_identifier_info[i]->layout()->addWidget(PMTAITait_identifier_infoHexSpinBox[i][it]);
        }

        PMTAITapplication_signalling_descriptor[i] = new SectionDescriptor(this,"application_signalling_descriptor");
        PMTAITelement_info_descriptor_loop[i]->layout()->addWidget(PMTAITapplication_signalling_descriptor[i]);
        for(int it=0;it<2;it++){
            PMTAITapplication_signalling_descriptorLabel[i][it] = new QLabel(PMTAITait_identifier_infoText[it]);
            PMTAITapplication_signalling_descriptor[i]->layout()->addWidget(PMTAITapplication_signalling_descriptorLabel[i][it]);
            PMTAITapplication_signalling_descriptorHexSpinBox[i][it] = new HexSpinBox;
            PMTAITapplication_signalling_descriptor[i]->layout()->addWidget(PMTAITapplication_signalling_descriptorHexSpinBox[i][it]);
        }

        PMTDSMCCItem[i] = new ElementSectionDescriptor(this);
        for(int it=0;it<2;it++){
            PMTDSMCCLabelItem[i][it]=new QLabel(PMTStreamLoopText[3][it]);
            PMTDSMCCItem[i]->layout()->addWidget(PMTDSMCCLabelItem[i][it]);
            PMTDSMCCHexspinBoxItem[i][it] = new HexSpinBox;
            PMTDSMCCItem[i]->layout()->addWidget(PMTDSMCCHexspinBoxItem[i][it]);
            registerField(PMTStreamLoopText[3][it]+QVariant(i).toString(),PMTDSMCCHexspinBoxItem[i][it]);
        }

        PMTDSMCC[i]->layout()->addWidget(PMTDSMCCItem[i]);

        PMTDSMCCelement_info_descriptor_loop[i] = new SectionLoop(this,"element_info_descriptor_loop");
        PMTDSMCC[i]->layout()->addWidget(PMTDSMCCelement_info_descriptor_loop[i]);

        PMTDSMCCassociation_tag_descriptor[i] =new SectionDescriptor(this,"association_tag_descriptor");
        PMTDSMCCelement_info_descriptor_loop[i]->layout()->addWidget(PMTDSMCCassociation_tag_descriptor[i]);

        for(int it=0;it<5;it++){
            PMTDSMCCassociation_tag_descriptorLabel[i][it] = new QLabel(PMTDSMCCassociation_tag_descriptorText[it]);
            PMTDSMCCassociation_tag_descriptor[i]->layout()->addWidget(PMTDSMCCassociation_tag_descriptorLabel[i][it]);
            PMTDSMCCassociation_tag_descriptorHexSpinBox[i][it] = new HexSpinBox;
            PMTDSMCCassociation_tag_descriptor[i]->layout()->addWidget(PMTDSMCCassociation_tag_descriptorHexSpinBox[i][it]);

        }

        PMTDSMCCdata_component_descriptor[i] = new SectionDescriptor(this,"data_component_descriptor");
        PMTDSMCCelement_info_descriptor_loop[i]->layout()->addWidget(PMTDSMCCdata_component_descriptor[i]);

        PMTDSMCCdata_component_id[i] = new LabelHexSpinBox(this,"data_component_id");
        PMTDSMCCdata_component_descriptor[i]->layout()->addWidget(PMTDSMCCdata_component_id[i]);
        PMTDSMCCdata_component_id[i]->setRange((i==0)?0xA1:0xA0,(i==0)?0xA1:0xA0);

        PMTDSMCCadditional_data_component_info[i]=new SectionDescriptor(this,"additional_data_component_info");
        PMTDSMCCdata_component_descriptor[i]->layout()->addWidget(PMTDSMCCadditional_data_component_info[i]);

        PMTDSMCCadditional_ginga_j_info[i]=new SectionDescriptor(this,"additional_ginga_j_info");
        PMTDSMCCadditional_data_component_info[i]->layout()->addWidget(PMTDSMCCadditional_ginga_j_info[i]);

        for(int it=0;it<5;it++){
            PMTDSMCCadditional_ginga_j_infoItem[i][it] = new LabelHexSpinBox(this,additional_ginga_j_infoItemText[it]);
            PMTDSMCCadditional_ginga_j_info[i]->layout()->addWidget(PMTDSMCCadditional_ginga_j_infoItem[i][it]);
        }

        layoutTab[3*i+5]->setSizeConstraint(QLayout::SetFixedSize);

        EIT_loop[i]=new SectionLoop(this,tr("EIT Actual"));
        layoutTab[3*i+5]->addWidget(EIT_loop[i]);

        EIT_loop_item[i] = new SectionDescriptor;
        EIT_loop[i]->layout()->addWidget(EIT_loop_item[i]);

        EITelements[i]= new QList<LabelHexSpinBox*>;
        foreach (const IntParam &item, EIT_items) {
            EITelements[i]->append(new LabelHexSpinBox(this,item.name));
            EIT_loop_item[i]->layout()->addWidget(EITelements[i]->last());
        }

        EIT_event_loop[i] = new SectionLoop(this,tr("Event Loop"));
        EIT_loop[i]->layout()->addWidget(EIT_event_loop[i]);

        EIT_event_loop_item[i]= new SectionDescriptor(this,tr("EIT Event Loop item"));
        EIT_event_loop[i]->layout()->addWidget(EIT_event_loop_item[i]);

        EIT_event_loop_widgets[i]= new QList<LabelHexSpinBox*>;
        foreach(IntParam item, EIT_event_loop_items){
            EIT_event_loop_widgets[i]->append(new LabelHexSpinBox(this,item.name,item.type));
            EIT_event_loop_widgets[i]->last()->setRange(item.min,item.max);
            EIT_event_loop_widgets[i]->last()->setValue(item.value);
            EIT_event_loop_item[i]->layout()->addWidget(EIT_event_loop_widgets[i]->last());
        }

        EIT_follow_loop[i]=new SectionLoop(this,tr("EIT Siguiente"));
        layoutTab[3*i+5]->addWidget(EIT_follow_loop[i]);

        EIT_follow_loop_item[i] = new ElementSectionDescriptor;
        EIT_follow_loop[i]->layout()->addWidget(EIT_follow_loop_item[i]);

        EIT_follow_elements[i]= new QList<LabelHexSpinBox*>;
        foreach (const IntParam &item, EIT_follow_items) {
            EIT_follow_elements[i]->append(new LabelHexSpinBox(this,item.name));
            EIT_follow_elements[i]->last()->setRange(item.min,item.max);
            EIT_follow_loop_item[i]->layout()->addWidget(EIT_follow_elements[i]->last());
        }

        EIT_follow_event_loop[i] = new SectionLoop(this,tr("Event Loop"));
        EIT_follow_loop[i]->layout()->addWidget(EIT_follow_event_loop[i]);

        EIT_follow_event_loop_item[i]= new SectionDescriptor(this,tr("EIT Event Loop item"));
        EIT_follow_event_loop[i]->layout()->addWidget(EIT_follow_event_loop_item[i]);

        EIT_follow_event_loop_widgets[i]= new QList<LabelHexSpinBox*>;
        foreach(IntParam item, EIT_follow_event_loop_items){
            EIT_follow_event_loop_widgets[i]->append(new LabelHexSpinBox(this,item.name,item.type));
            EIT_follow_event_loop_widgets[i]->last()->setRange(item.min,item.max);
            EIT_follow_event_loop_widgets[i]->last()->setValue(item.value);
            EIT_follow_event_loop_item[i]->layout()->addWidget(EIT_follow_event_loop_widgets[i]->last());
        }


        layoutTab[3*i+6]->setSizeConstraint(QLayout::SetFixedSize);

        AITApptype[i]=new LabelHexSpinBox(this,"App Type");
        layoutTab[3*i+6]->addWidget(AITApptype[i]);

        AITApploop[i]=new SectionLoop(this,tr("Application Loop"));
        layoutTab[3*i+6]->addWidget(AITApploop[i]);

        AITApp[i]=new SectionLoop(this,tr("Aplicación de Servicio ")+QString::number(i));
        AITApploop[i]->layout()->addWidget(AITApp[i]);

        AITAppElementSection[i]= new ElementSectionDescriptor(this);
        AITApp[i]->layout()->addWidget(AITAppElementSection[i]);

        AIT_app_item_widgets[i] = new QList<LabelHexSpinBox*>;
        foreach(IntParam item, AIT_app_items){
            AIT_app_item_widgets[i]->append(new LabelHexSpinBox(this,item.name,item.type));
            AIT_app_item_widgets[i]->last()->setRange(item.min,item.max);
            AIT_app_item_widgets[i]->last()->setValue(item.value);
            AITAppElementSection[i]->layout()->addWidget(AIT_app_item_widgets[i]->last());
        }


        AITApp_descriptors_loop[i]=new SectionLoop(this,tr("Application_desctiptor_loop"));

        AITApp[i]->layout()->addWidget(AITApp_descriptors_loop[i]);
        AITTransportProtocolControlDesc[i]= new SectionDescriptor(this,tr("Transport_Protocol_Control_Descriptor"));
        AITApp_descriptors_loop[i]->layout()->addWidget(AITTransportProtocolControlDesc[i]);

        AITTransportProtocolControlDesc_item_widgets[i] = new QList<LabelHexSpinBox*>;
        foreach(IntParam item, AITTransportProtocolControlDesc_items){
            AITTransportProtocolControlDesc_item_widgets[i]->append(new LabelHexSpinBox(this,item.name,item.type));
            AITTransportProtocolControlDesc_item_widgets[i]->last()->setRange(item.min,item.max);
            AITTransportProtocolControlDesc_item_widgets[i]->last()->setValue(item.value);
            AITTransportProtocolControlDesc[i]->layout()->addWidget(AITTransportProtocolControlDesc_item_widgets[i]->last());
        }

        AITAppDesc[i]= new SectionDescriptor(this,tr("Application_Descriptor"));
        AITApp_descriptors_loop[i]->layout()->addWidget(AITAppDesc[i]);

        AITapplication_profile[i]= new LabelHexSpinBox(this,tr("application_profile"));
        AITAppDesc[i]->layout()->addWidget(AITapplication_profile[i]);
        AITversion_major[i]= new LabelHexSpinBox(this,tr("version_major"));
        AITAppDesc[i]->layout()->addWidget(AITversion_major[i]);
        AITversion_minor[i]= new LabelHexSpinBox(this,tr("version_minor"));
        AITAppDesc[i]->layout()->addWidget(AITversion_minor[i]);
        AITversion_micro[i]= new LabelHexSpinBox(this,tr("version_micro"));
        AITAppDesc[i]->layout()->addWidget(AITversion_micro[i]);
        AITservice_bound_flagr[i]= new LabelHexSpinBox(this,tr("service_bound_flag"));
        AITAppDesc[i]->layout()->addWidget(AITservice_bound_flagr[i]);
        AITvisibility[i]= new LabelHexSpinBox(this,tr("visibility"));
        AITAppDesc[i]->layout()->addWidget(AITvisibility[i]);
        AITapplication_priority[i]= new LabelHexSpinBox(this,tr("application_priority"));
        AITAppDesc[i]->layout()->addWidget(AITapplication_priority[i]);
        AITtransport_protocol_labels[i]= new LabelHexSpinBox(this,tr("transport_protocol_labels"));
        AITAppDesc[i]->layout()->addWidget(AITtransport_protocol_labels[i]);

        AITApp_name_descriptor[i]= new SectionDescriptor(this,tr("Application_Name_Descriptor"));
        AITApp_descriptors_loop[i]->layout()->addWidget(AITApp_name_descriptor[i]);
        AITapplication_name[i]= new LabelLineEdit(this,tr("application_name"));
        AITApp_name_descriptor[i]->layout()->addWidget(AITapplication_name[i]);

        ginga_ncl_application_location_descriptor[i]= new SectionDescriptor(this,tr("ginga_ncl_application_location_descriptor"));
        AITApp_descriptors_loop[i]->layout()->addWidget(ginga_ncl_application_location_descriptor[i]);
        AITbase_directory[i]= new LabelLineEdit(this,tr("base_directory"));
        ginga_ncl_application_location_descriptor[i]->layout()->addWidget(AITbase_directory[i]);
        class_path_extension[i]= new LabelLineEdit(this,tr("class_path_extension"));
        ginga_ncl_application_location_descriptor[i]->layout()->addWidget(class_path_extension[i]);
        initial_class[i]= new LabelLineEdit(this,tr("initial_class"));
        ginga_ncl_application_location_descriptor[i]->layout()->addWidget(initial_class[i]);

        connect(PATServiceID[i],SIGNAL(valueChanged(int)),
                        NITServiceID[i],SLOT(setValue(int)));

        connect(NITServiceID[i],SIGNAL(valueChanged(int)),
                        SDTServiceLoopElementWidget[i][0],SLOT(setValue(int)));

        connect(SDTServiceLoopElementWidget[i][0],SIGNAL(valueChanged(int)),
                        EITelements[i]->at(1),SLOT(setValue(int)));

        connect(EITelements[i]->at(1),SIGNAL(valueChanged(int)),
                                PATServiceID[i],SLOT(setValue(int)));

        connect(PMTProgramNumber[i],SIGNAL(valueChanged(int)),
                        PATServicePID[i],SLOT(setValue(int)));
        connect(PATServicePID[i],SIGNAL(valueChanged(int)),
                        PMTProgramNumber[i],SLOT(setValue(int)));


        PATServicePID[i]->setValue(0x3E8+i);
        PATServiceID[i]->setValue(i-1);
    }

    connect(PATServiceID[0],SIGNAL(valueChanged(int)),this,SLOT(MuxChanges(int)));
    NITServiceType[0]->setRange(0xC0,0xC0);
    SDTServiceType[0]->setRange(0xC0,0xC0);
    PMTProgramNumber[0]->setRange(0x1FC8,0x1FCF);
    PATServicePID[0]->setRange(0x1FC8,0x1FCF);
    NITNetworkID->setValue(0x7880);

    setLayout(layout);

}


int MuxPage::nextId() const{
    return Tdtumsa::Page_Final;
}
void MuxPage::cleanupPage(){

}

void MuxPage::initializePage(){
    int index = 0, nservice = 0;
    QStringList TabText[5];
    TabText[0]<<"One-Seg"<<"Full HD";
    TabText[1]<<"One-Seg"<<"Full HD"<<"HD";
    TabText[2]<<"One-Seg"<<"HD 1"<<"HD 2";
    TabText[3]<<"One-Seg"<<"HD"<<"SD 1"<<"SD 2";
    TabText[4]<<"One-Seg"<<"SD 1"<<"SD 2"<<"SD 3"<<"SD 4";

    for(int it=0;it<5;it++)
    {
        if(field("option"+QVariant(it).toString()).toBool())
        {
            index=it;
        }
    }

    nservice = TabText[index].size();

    while(MuxTab->count()>4)
    {
        MuxTab->removeTab(MuxTab->count()-1);

    }

    for(int it=0;it<5;it++)
    {
        NITService[it]->hide();
        PATprogram_loop_item[it]->hide();
        SDTServiceLoopItem[it]->hide();
    }

    for(int it=0;it<nservice;it++)
    {
        MuxTab->addTab(scrollArea[3*it+4], {"PMT "+TabText[index][it]});
        MuxTab->addTab(scrollArea[3*it+5], {"EIT "+TabText[index][it]});
        MuxTab->addTab(scrollArea[3*it+6], {"AIT "+TabText[index][it]});
        NITService[it]->show();
        PATprogram_loop_item[it]->setTitle("Servicio "+TabText[index][it]);
        PATprogram_loop_item[it]->show();
        PMTAIT[it]->show();
        PMTDSMCC[it]->show();
        NITService[it]->setTitle("Servicio "+TabText[index][it]);
        SDTServiceLoopItem[it]->show();
        SDTServiceLoopItem[it]->setTitle("Servicio "+TabText[index][it]);
        SDTServiceName[it]->setText("UMSA "+TabText[index][it]);
    }

    for(int it=nservice-1;it>=0;it--)
    {      
        if(!field("GingaApp"+QVariant(it).toString()).toBool())
        {
            MuxTab->removeTab(3*it+6);
            PMTAIT[it]->hide();
            PMTDSMCC[it]->hide();
        }
    }

    if(!field("1seg").toBool())
    {
        MuxTab->removeTab(5);
        MuxTab->removeTab(4);
        NITService[0]->hide();
        PATprogram_loop_item[0]->hide();
        SDTServiceLoopItem[0]->hide();
        if(MuxTab->tabText(4).contains({"AIT "+TabText[index][0]}))
        {
            MuxTab->removeTab(4);
        }
    }
}

void MuxPage::MuxChanges(int value)
{
    if(this->sender()==NITNetworkID){
        int finalvalue, aux, min, max;
        finalvalue=(value&0x7FF)<<5;
        aux=(0x07&(PATServiceID[0]->Value()));
        min=(finalvalue|0x18);
        max=((finalvalue|0x18))|(0x7);

        PATServiceID[0]->setRange(min,max);
        NITServiceID[0]->setRange(min,max);
        SDTServiceLoopElementWidget[0][0]->setRange(min,max);
        PATServiceID[0]->setValue((finalvalue|0x18)|aux);

        min=(finalvalue)&(0xFFE7);
        max=((finalvalue)&(0xFFE7))|(0x7);
        for(int i=1;i<5;i++)
        {
            aux =(0x07&(PATServiceID[i]->Value()));
            PATServiceID[i]->setRange(min,max);
            NITServiceID[i]->setRange(min,max);
            EITelements[i]->at(1)->setRange(min,max);
            SDTServiceLoopElementWidget[i][0]->setRange(min,max);
            PATServiceID[i]->setValue(((finalvalue)&(0xFFE7))|aux);
        }
    }
    PATServicePID[0]->setRange((PATServiceID[0]->Value()&0x0007)+0x1FC8,(PATServiceID[0]->Value()&0x0007)+0x1FC8);

}


bool MuxPage::validatePage()
{
    QStringList PIDs;
    for(int it=0;it<5;it++)
    {
        PIDs.append(QString(PATServicePID[it]->Value()));
        PIDs.append(field("PID Audio"+QVariant(it).toString()).toString());
        PIDs.append(field("PID Video"+QVariant(it).toString()).toString());
    }

    return true;
}


FinalPage::FinalPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Finalización y Ejecución"));

    FinalTab = new QTabWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(FinalTab);
    setLayout(layout);
    QStringList tabnames={"script.sh","tables.py"};
    for(int i=0;i<2;i++)
    {
        tabWidget[i]=new QWidget;
        FinalTab->addTab(tabWidget[i],tabnames[i]);
        Text[i] = new QTextEdit;
        layoutTab[i]=new QGridLayout;
        layoutTab[i]->addWidget(Text[i],0,0);
        tabWidget[i]->setLayout(layoutTab[i]);
    }
    execButton = new QPushButton(tr("Ejecutar"));
    execButton->setMaximumWidth(100);
    connect(execButton,SIGNAL(clicked()),this,SLOT(execute()));
    layout->addWidget(execButton);
    layout->itemAt(1)->setAlignment(Qt::AlignHCenter);
}

void FinalPage::execute()
{
    QString uname = qgetenv("USER");
    QString path = field("WorkDirectory").toString();
    QDir dir;
    QFile file(path + "script.sh");
    QFile filepy(path + "tables.py");
    QFile nullts(path+"null.ts");

    if(!dir.exists(path))
    {
        dir.mkpath(path);
    }
    if ( file.open(QIODevice::WriteOnly) )
    {
        QTextStream out(&file);
        out<<Text[0]->toPlainText();
        file.close();
    }

    if ( filepy.open(QIODevice::WriteOnly) )
    {
        QTextStream outpy(&filepy);
        outpy<<Text[1]->toPlainText();
        filepy.close();
    }

    QFile(path + "script.sh").setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner | QFileDevice::ExeOwner);

    if ( nullts.open(QIODevice::WriteOnly) )
    {
        static const char mydata[] = {
           '\x47','\x1F','\xFF','\x10','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00',
           '\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00',
           '\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00',
           '\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00',
           '\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00',
           '\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00',
           '\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00',
           '\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00',
           '\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00',
           '\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00',
           '\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00'
        };
        QDataStream outnullts(&nullts);
        outnullts.writeRawData(mydata, sizeof(mydata));
        nullts.close();
    }

    QString program = "gnome-terminal";
    QStringList arguments;
    arguments <<"-e"<<path + "script.sh";
    QProcess *myProcess = new QProcess;
    myProcess->start(program,arguments);

}
void FinalPage::initializePage()
{
    QString strCodeMux,auxString1,auxString2;
    int nservice=field("SevicesPlan").toInt();
    int oneseg=field("1seg").toInt(),bitratetotal=0;;

    for(int it=0;it<(nservice+oneseg-1);it++){
        auxString1=QVariant(it).toString();
        auxString2=QVariant(it-oneseg+1).toString();
        if(oneseg==1&&it==0){
            bitratetotal+=field("VideoBitRate"+auxString2).toInt()*(1000);
        }else{
            bitratetotal+=field("VideoBitRate"+auxString2).toInt()*(1000000);
        }
        bitratetotal+=field("AudioBitRate"+auxString2).toInt()*(1000);

    }
    bitratetotal=bitratetotal*1.15;
    strCodeMux.append("cd "+field("WorkDirectory").toString());

    strCodeMux.append("\npython tables.py\n");
    QString PathVideo, LetterDisk;
    strCodeMux.append("ffmpeg -y ");
    for(int it=0;it<(nservice+oneseg-1);it++){

        PathVideo =field("File"+QVariant(it-oneseg+1).toString()).toString();
        strCodeMux.append("-i \""+PathVideo+"\" ");
    }
    for(int it=0;it<(nservice+oneseg-1);it++)
        strCodeMux.append("-map "+QVariant(it).toString()+" ");

    strCodeMux.append("-flags +global_header -c:v libx264 -tune zerolatency -c:a libfdk_aac -x264-params \"nal-hrd=cbr\" -pix_fmt yuv420p -strict 2 -movflags +faststart ");

    if(field("indexPlan").toInt()==1)
        strCodeMux.append(QString("-top:%1 1 -flags:%1 +ilme+ildct ").arg((oneseg==1)?1:0));

    for(int it=0;it<(nservice+oneseg-1);it++)
    {
        auxString1=QVariant(it).toString();
        auxString2=QVariant(it-oneseg+1).toString();
        strCodeMux.append("-streamid "+auxString1+":"+field("PID Video"+auxString2).toString()+" "
                          "-level:"+auxString1+" "+field("VideoLevel"+auxString2).toString()+" "
                          "-profile:v:"+auxString1+" "+field("VideoPerfil"+auxString2).toString()+" "
                          "-aspect:v:"+auxString1+" "+field("VideoRA"+auxString2).toString()+" "
                          "-r:v:"+auxString1+" "+field("VideoFPS"+auxString2).toString()+" ");
        if(oneseg==1&&it==0)
            strCodeMux.append("-b:v:"+auxString1+" "+QVariant(field("VideoBitRate"+auxString2).toInt()*(1000)).toString()+" "
                              "-maxrate:v:"+auxString1+" "+QVariant(field("VideoBitRate"+auxString2).toInt()*(1000)).toString()+" "
                              "-bufsize:v:"+auxString1+" "+QVariant(field("VideoBitRate"+auxString2).toInt()*(1000)/4).toString()+" ");
        else
            strCodeMux.append("-b:v:"+auxString1+" "+QVariant(field("VideoBitRate"+auxString2).toInt()*(1000000)).toString()+" "
                              "-maxrate:v:"+auxString1+" "+QVariant(field("VideoBitRate"+auxString2).toInt()*(1000000)).toString()+" "
                              "-bufsize:v:"+auxString1+" "+QVariant(field("VideoBitRate"+auxString2).toInt()*(1000000)/4).toString()+" ");
    }

    for(int it=0;it<(nservice+oneseg-1);it++)
    {
        auxString1=QVariant(it).toString();
        auxString2=QVariant(it-oneseg+1).toString();
        strCodeMux.append("-streamid "+QVariant(it+nservice+oneseg-1).toString()+":"+field("PID Audio"+auxString2).toString()+" "
                          "-profile:a:"+auxString1+" "+field("AudioPerfil"+auxString2).toString()+" "
                          "-ar:"+auxString1+" "+field("AudioSampleRate"+auxString2).toString()+" "
                          "-b:a:"+auxString1+" "+QVariant(field("AudioBitRate"+auxString2).toInt()*1000).toString()+" "
                          "-ac:a:"+auxString1+" "+field("AudioChannels"+auxString2).toString()+" ");
    }

    strCodeMux.append("-filter_complex \"[0:v]scale="+field("VideoResolution"+QVariant(-oneseg+1).toString()).toString()+"");
    for(int it=1;it<(nservice+oneseg-1);it++)
        strCodeMux.append(";["+QVariant(it).toString()+":v]scale="+field("VideoResolution"+QVariant(it-oneseg+1).toString()).toString()+"");
    strCodeMux.append("\" ");
    strCodeMux.append("-f mpegts -mpegts_flags latm -mpegts_service_type digital_tv -muxrate "+QString("%1").arg(bitratetotal)+" -y AVTS.ts\n");


    strCodeMux.append("tsmodder AVTS.ts +0 null.ts +17 null.ts +4096 null.ts > filterAVTS.ts\n");


    for(int it=0;it<(nservice+oneseg-1);it++){
        auxString1=QVariant(it).toString();
        auxString2=QVariant(it-oneseg+1).toString();
        if(field("GingaApp"+auxString2).toBool()){
            strCodeMux.append("cp -a \""+field(QString("GingaAppDir"+auxString2)).toString()+"/.\" app_ginga"+auxString1+"\n");
            strCodeMux.append("oc-update app_ginga"+auxString1+" 0x0C 1 "+field("PID DSMCC"+auxString2).toString()+" 2\n");
        }
    }

    strCodeMux.append("tscbrmuxer b:15040 pat.ts b:3008 sdt.ts b:3008 nit.ts b:1504 tot.ts b:3008 eit.ts ");
    bitratetotal=0;
    for(int it=0;it<(nservice+oneseg-1);it++){
        auxString1=QVariant(it).toString();
        auxString2=QVariant(it-oneseg+1).toString();
        if(oneseg==1&&it==0){
            strCodeMux.append("b:30080 pmt"+field("PID PMT"+auxString2).toString()+".ts ");
            bitratetotal+=field("VideoBitRate"+auxString2).toInt()*(1000);                

        }else{
            strCodeMux.append("b:15040 pmt"+field("PID PMT"+auxString2).toString()+".ts ");
            bitratetotal+=field("VideoBitRate"+auxString2).toInt()*(1000000);
        }
        if(field("GingaApp"+auxString2).toBool())
            strCodeMux.append("b:"+QString("%1").arg(field("GingaBitRate"+auxString2).toInt()*(1000))+" app_ginga"+auxString1+".ts "
                               "b:3008 ait"+auxString1+".ts ");

        bitratetotal+=field("AudioBitRate"+auxString2).toInt()*(1000);

    }
    bitratetotal=bitratetotal*1.15;
    strCodeMux.append(QString("c:%1 filterAVTS.ts o:29958294 null.ts > preout.ts\n").arg(bitratetotal));
    strCodeMux.append("tstdt preout.ts > preout_fixtime.ts\n");
    strCodeMux.append("tspcrstamp preout_fixtime.ts 29958294 > output.ts\n");




    Text[0]->setPlainText(strCodeMux);
    QString strTables;
    strTables.append("#!/usr/bin/env python\n\n"
                     "#coding: utf8\n\n"
                     "import os\n"
                     "import time\n"
                     "from dvbobjects.MHP.AIT import *\n"
                     "from dvbobjects.MHP.Descriptors import *\n"
                     "from dvbobjects.PSI.PAT import *\n"
                     "from dvbobjects.PSI.NIT import *\n"
                     "from dvbobjects.PSI.SDT import *\n"
                     "from dvbobjects.PSI.TOT import *\n"
                     "from dvbobjects.PSI.PMT import *\n"
                     "from dvbobjects.PSI.EIT import *\n"
                     "from dvbobjects.SBTVD.Descriptors import *\n");
    strTables.append("\nclass AAC_descriptor(Descriptor):\n    descriptor_tag = 0x7C\n\n    def bytes(self):\n        for property, value in vars(self).iteritems():\n            if not property in ['additional_info', 'AAC_type','profile_and_level']:\n                print \"WARN: unrecognized attribute \", property, \" in object \", self\n        stream = pack( \"!B\", self.profile_and_level)\n        if hasattr (self, 'AAC_type') | hasattr (self, 'additional_info'):\n            if hasattr (self, 'AAC_type'):\n                stream += pack(\"BB\", 0xFF, self.AAC_type)\n            else:\n                stream += pack(\"B\", 0x7F)\n            if hasattr (self, 'additional_info'):\n                stream += pack(\"%ds\" % len(self.additional_info), self.additional_info)\n        return stream\n");
    strTables.append("tvd_ts_id = "+field("Transport Stream ID").toString()+"\n"
                     "tvd_orig_network_id = "+field("Transport Stream ID").toString()+"\n"
                     "ts_freq = 497\n"
                     "ts_virtual_channel_key = "+field("remote control key id").toString()+"\n"
                     "tvd_network_name = \""+field("Network Name").toString()+"\"\n"
                     "tvd_ts_name = \"UMSA TS\"\n");

    for(int it=0;it<(nservice+oneseg-1);it++){
        auxString1=QVariant(it).toString();
        auxString2=QVariant(it-oneseg+1).toString();
        strTables.append("tvd_pmt"+auxString1+"_pid = "+field("PID PMT"+auxString2).toString()+"\n");
        strTables.append("tvd_service_id_"+auxString1+" = "+field("ServiceID"+auxString2).toString()+"\n");
        if(field("GingaApp"+QVariant(it-oneseg+1).toString()).toBool()){
            strTables.append("tvd_ait_pid_"+auxString1+" = "+field("PID AIT"+auxString2).toString()+"\n");

        }

    }

    strTables.append("pat = program_association_section(\n"
                     "	transport_stream_id = tvd_ts_id,\n"
                     "	program_loop = [ \n"
                     "		program_loop_item(\n"
                     "			program_number = 0,\n"
                     "			PID = 16,\n"
                     "		),\n");
    for(int it=0;it<(nservice+oneseg-1);it++)
    {
    strTables.append("		program_loop_item(\n"
                     "			program_number = tvd_service_id_"+QVariant(it).toString()+",\n"
                     "			PID = tvd_pmt"+QVariant(it).toString()+"_pid,\n"
                     "		), \n");
    }
    strTables.append("	],\n"
                     "	version_number = 0,\n"
                     "	section_number = 0,\n"
                     "	last_section_number = 0,\n"
                     ")\n\n");
    strTables.append("out = open(\"./pat.sec\", \"wb\")\n"
                     "out.write(pat.pack())\n"
                     "out.close\n"
                     "out = open(\"./pat.sec\", \"wb\")\n"
                     "out.close\n"
                     "os.system(\"sec2ts 0 < ./pat.sec > ./pat.ts\")\n\n");

    strTables.append("nit = network_information_section(\n"
                     "	network_id = tvd_orig_network_id,\n"
                     "	network_descriptor_loop = [\n"
                     "		network_descriptor(\n"
                     "              network_name = tvd_network_name,\n"
                     "      ),\n"
                     "		system_management_descriptor(\n"
                     "            broadcasting_flag = "+field("broadcasting_flag").toString()+",\n"
                     "            broadcasting_identifier = "+field("broadcasting_identifier").toString()+",\n"
                     "            additional_broadcasting_identification = "+field("additional_broadcasting_identification").toString()+",\n"
                     "            additional_identification_bytes = [],\n"
                     "      )\n"
                     "	],\n"
                     "	transport_stream_loop = [\n"
                     "		transport_stream_loop_item(\n"
                     "			transport_stream_id = tvd_ts_id,\n"
                     "			original_network_id = tvd_orig_network_id,\n"
                     "			transport_descriptor_loop = [\n"
                     "				service_list_descriptor(\n"
                     "					dvb_service_descriptor_loop = [\n");
    for(int it=0;it<(nservice+oneseg-1);it++)
    {
        auxString1=QVariant(it).toString();
        auxString2=QVariant(it-oneseg+1).toString();
        strTables.append("						service_descriptor_loop_item (\n"
                         "							service_ID = tvd_service_id_"+QVariant(it).toString()+",\n");
        if(oneseg==1&&it==0)
            strTables.append("							service_type = 0xC0,\n");
        else
            strTables.append("							service_type = 0x01,\n");
        strTables.append("						),\n");
    }
    strTables.append("					],\n"
                     "				),\n"
                     "                terrestrial_delivery_system_descriptor(\n"
                     "                    area_code = 1341,\n"
                     "                    guard_interval = 0x01,\n"
                     "                    transmission_mode = 0x02,\n"
                     "                    frequencies = [\n"
                     "                        tds_frequency_item(\n"
                     "                            freq=ts_freq\n"
                     "                        )\n"
                     "                    ],\n"
                     "                ),\n"
                     "                partial_reception_descriptor (\n");
    if(oneseg==1)
        strTables.append("                    service_ids = [tvd_service_id_0]\n");
    else
        strTables.append("                    service_ids = []\n");

    strTables.append("                ),\n"
                     "                transport_stream_information_descriptor (\n"
                     "                    remote_control_key_id = ts_virtual_channel_key,\n"
                     "                    ts_name = tvd_ts_name,\n"
                     "                    transmission_type_loop = [\n"
                     "                        transmission_type_loop_item(\n"
                     "                            transmission_type_info = 0xAF,\n");
    if(oneseg==1)
        strTables.append("                            service_id_loop = [\n"
                         "                                service_id_loop_item(\n"
                         "                                    service_id=tvd_service_id_0\n"
                         "                                ),\n"
                         "                            ]\n");
    else
        strTables.append("                            service_id_loop = [],\n");
    strTables.append("                        ),\n"
                     "                    ],\n"
                     "                )\n"
                     "            ],\n"
                     "        ),\n"
                     "     ],\n"
                     "version_number = 1,\n"
                     "section_number = 0,\n"
                     "last_section_number = 0,\n"
                     ")\n\n");
    strTables.append("out = open(\"./nit.sec\", \"wb\")\n"
                     "out.write(nit.pack())\n"
                     "out.close\n"
                     "out = open(\"./nit.sec\", \"wb\")\n"
                     "out.close\n"
                     "os.system(\"sec2ts 16 < ./nit.sec > ./nit.ts\")\n\n");

    strTables.append("sdt = service_description_section(\n"
                     "	transport_stream_id = tvd_ts_id,\n"
                     "	original_network_id = tvd_orig_network_id,\n"
                     "	service_loop = [\n");

    for(int it=0;it<(nservice+oneseg-1);it++)
    {
        auxString1=QVariant(it).toString();
        auxString2=QVariant(it-oneseg+1).toString();
        strTables.append("		service_loop_item(\n"
                         "			service_ID = tvd_service_id_"+QVariant(it).toString()+",\n"
                         "			EIT_schedule_flag= 0,\n"
                         "			EIT_present_following_flag = 0,\n"
                         "			running_status = 4,\n"
                         "			free_CA_mode = 0,\n"
                         "			service_descriptor_loop = [\n"
                         "				service_descriptor(\n");
        if(oneseg==1&&it==0)
            strTables.append("					service_type = 0xC0,\n");
        else
            strTables.append("					service_type = 0x01,\n");
        strTables.append("					service_provider_name = \""+field("Service Provider Name"+auxString2).toString()+"\",\n"
                         "					service_name = \""+field("Service Name"+auxString2).toString()+"\",\n"
                         "				),\n"
                         "			],\n"
                         "		),");
    }
    strTables.append("	],\n"
                     "	version_number = 0,\n"
                     "	section_number = 0,\n"
                     "	last_section_number = 0,\n"
                     ")\n\n");

    strTables.append("out = open(\"./sdt.sec\", \"wb\")\n"
                     "out.write(sdt.pack())\n"
                     "out.close\n"
                     "out = open(\"./sdt.sec\", \"wb\")\n"
                     "out.close\n"
                     "os.system(\"sec2ts 17 < ./sdt.sec > ./sdt.ts\")\n\n");
    strTables.append("current_time = time.gmtime()\n\n"
                     "tot = time_offset_section(\n"
                     "        year = current_time[0]-1900,\n"
                     "        month = current_time[1],\n"
                     "        day = current_time[2],\n"
                     "        hour = ((current_time[3] / 10) * 16) + (current_time[3] % 10), # it requires decimal time in hex... like 0x22 for 10 p.m.\n"
                     "        minute = ((current_time[4] / 10) * 16) + (current_time[4] % 10),\n"
                     "        second = ((current_time[5] / 10) * 16) + (current_time[5] % 10),\n"
                     "        descriptor_loop = [],\n"
                     ")\n\n"
                     "out = open(\"./tot.sec\", \"wb\")\n"
                     "out.write(tot.pack())\n"
                     "out.close\n"
                     "out = open(\"./tot.sec\", \"wb\") # python   flush bug\n"
                     "out.close\n"
                     "os.system('sec2ts 20 < ./tot.sec > ./tot.ts')\n\n");

    QStringList profile_and_level[2], AAC_type[3];
    profile_and_level[0]=QStringList({"0x29","0x2A"});
    profile_and_level[1]=QStringList({"0x2C","0x2E"});
    AAC_type[0]=QStringList({"0x53","0x59"});
    AAC_type[1]=QStringList({"0x03","0x09"});
    AAC_type[2]=QStringList({"0x44"});

    int indexAACp_a_l[2],indexAAC_type[2];

    for(int it=0;it<(nservice+oneseg-1);it++)
    {
        auxString1=QVariant(it).toString();
        auxString2=QVariant(it-oneseg+1).toString();
        if((field("AudioPerfil"+QVariant(it).toString()).toString()=="aac_low"))
            {indexAACp_a_l[0]=0;indexAAC_type[0]=0;}
        else if((field("AudioPerfil"+QVariant(it).toString()).toString()=="aac_he")){
                indexAACp_a_l[0]=1;indexAAC_type[0]=1;
                }
        else if((field("AudioPerfil"+QVariant(it).toString()).toString()=="aac_he_v2"))
              {  indexAACp_a_l[0]=1;indexAAC_type[0]=2;}

        if(field("AudioChannels"+QVariant(it).toString()).toString()=="2")
            {indexAACp_a_l[1]=0;indexAAC_type[1]=0;}
        else
            {indexAACp_a_l[1]=1;indexAAC_type[1]=1;}
        strTables.append("pmt"+auxString1+" = program_map_section(\n"
                         "	program_number = tvd_service_id_"+auxString1+",\n"
                         "	PCR_PID = "+field("PID Video"+auxString2).toString()+",\n"
                         "	program_info_descriptor_loop = [],\n"
                         "	stream_loop = [\n"
                         "		stream_loop_item(\n"
                         "			stream_type = 0x1B,\n"
                         "			elementary_PID = "+field("PID Video"+auxString2).toString()+",\n"
                         "			element_info_descriptor_loop = []\n"
                         "		),\n"
                         "		stream_loop_item(\n"
                         "			stream_type = 0x11,\n"
                         "			elementary_PID = "+field("PID Audio"+auxString2).toString()+",\n"
                         "			element_info_descriptor_loop = [\n"
                         "                                          AAC_descriptor(\n"
                         "                                          	profile_and_level = "+profile_and_level[indexAACp_a_l[0]].at(indexAACp_a_l[1])+",\n"
                         "                                          	AAC_type = "+AAC_type[indexAAC_type[0]].at(indexAAC_type[1])+",\n"
                         "                                                         ),\n"
                         "                                         ]\n"
                         "		),\n");

        if(field("GingaApp"+QVariant(it-oneseg+1).toString()).toBool()){
            strTables.append("		stream_loop_item(\n"
                             "			stream_type = 5,\n"
                             "			elementary_PID = tvd_ait_pid_"+auxString1+",\n"
                             "			element_info_descriptor_loop = [\n"
                             "				data_component_descriptor (\n");
            strTables.append("					data_component_id = 0xA3,\n");
            strTables.append("					additional_data_component_info = ait_identifier_info(\n"
                             "							application_type =0x0009,\n"
                             "							ait_version = 0\n"
                             "					).bytes(),\n"
                             "				),\n"
                             "					application_signalling_descriptor(\n"
                             "					application_type = 9,\n"
                             "					AIT_version = 1, # current ait version\n"
                             "				),\n"
                             "			]\n"
                             "		),\n"
                             "		stream_loop_item(\n"
                             "			stream_type = 0x0B,\n"
                             "			elementary_PID = "+field("PID DSMCC"+auxString2).toString()+",\n"
                             "			element_info_descriptor_loop = [\n"
                             "				association_tag_descriptor(\n"
                             "					association_tag = 0x0C,\n"
                             "					use = 0,\n"
                             "					selector_lenght = 0,\n"
                             "					transaction_id = 0x80000000,\n"
                             "					timeout = 0xFFFFFFFF,\n"
                             "					private_data = \"\",\n"
                             "				),\n"
                             "				stream_identifier_descriptor(\n"
                             "					component_tag = 0x0C,\n"
                             "				),\n"
                             "				carousel_identifier_descriptor(\n"
                             "					carousel_ID = 2,\n"
                             "					format_ID = 0,\n"
                             "					private_data = \"\",\n"
                             "				),\n"
                             "				data_component_descriptor (\n"
                             "					data_component_id = 0xA0,\n"
                             "					additional_data_component_info = additional_ginga_j_info(\n"
                             "					transmission_format = 0x2,\n"
                             "					document_resolution = 0x5,\n"
                             "					organization_id = 0x0000000A,\n"
                             "					application_id = 0x0064,\n"
                             "					carousel_id = 2,\n"
                             "				).bytes(),\n"
                             "				),\n"
                             "			]\n"
                             "		)\n");

        }
        strTables.append("	],\n"
                         "	version_number = 0,\n"
                         "	section_number = 0,\n"
                         "	last_section_number = 0,\n"
                         ")\n");



        strTables.append("out = open(\"./pmt\" + str(tvd_pmt"+auxString1+"_pid) + \".sec\", \"wb\") \n"
                         "out.write(pmt"+auxString1+".pack())\n"
                         "out.close\n"
                         "out = open(\"./pmt\" + str(tvd_pmt"+auxString1+"_pid) + \".sec\", \"wb\")\n"
                         "out.close\n"
                         "os.system(\"sec2ts \" + str(tvd_pmt"+auxString1+"_pid) + \"< ./pmt\" + str(tvd_pmt"+auxString1+"_pid) + \".sec > ./pmt\" + str(tvd_pmt"+auxString1+"_pid) + \".ts\")\n\n");
    }

    for(int it=0;it<(nservice+oneseg-1);it++)
    {
        auxString1=QVariant(it).toString();
        auxString2=QVariant(it-oneseg+1).toString();
        strTables.append("eit"+auxString1+" = event_information_section(\n"
                         "	table_id = EIT_ACTUAL_TS_PRESENT_FOLLOWING,\n"
                         "	service_id = tvd_service_id_"+auxString1+",\n"
                         "	transport_stream_id = tvd_ts_id,\n"
                         "	original_network_id = tvd_orig_network_id,\n"
                         "        event_loop = [\n"
                         "	    event_loop_item(\n"
                         "		event_id = 1,\n"
                         "		start_year = 108, # since 1900\n"
                         "		start_month = 6, \n"
                         "		start_day = 10, \n"
                         "		start_hours = 0x00, # use hex like decimals\n"
                         "		start_minutes = 0x00,\n"
                         "		start_seconds = 0x00,\n"
                         "		duration_hours = 0x23,\n"
                         "		duration_minutes = 0x00,\n"
                         "		duration_seconds = 0x00,\n"
                         "		running_status = 4, # 4 service is running, 1 not running, 2 starts in a few seconds, 3 pausing\n"
                         "		free_CA_mode = 0, # 0 means service is not scrambled, 1 means at least a stream is scrambled\n"
                         "		event_descriptor_loop = [\n"
                         "		    short_event_descriptor (\n"
                         "			ISO639_language_code = \"SPA\", \n"
                         "			event_name = \"epg event name\",\n"
                         "			text = \"this is an epg event text example\",\n"
                         "		    ),\n"
                         "		],\n"
                         "	    ),	    	\n"
                         "            ],\n"
                         "\n"
                         "        segment_last_section_number = 1,\n"
                         "        version_number = 1,\n"
                         "        section_number = 0,\n"
                         "        last_section_number = 1, # pay attention here, we have another section after this!\n"
                         "        )\n"
                         "\n"
                         "\n"
                         "eit_follow"+auxString1+" = event_information_section(\n"
                         "	table_id = EIT_ACTUAL_TS_PRESENT_FOLLOWING,\n"
                         "	service_id = tvd_service_id_"+QVariant(it).toString()+",\n"
                         "	transport_stream_id = tvd_ts_id,\n"
                         "	original_network_id = tvd_orig_network_id,\n"
                         "        event_loop = [\n"
                         "	    event_loop_item(\n"
                         "		event_id = 2, \n"
                         "		start_year = 108, # since 1900\n"
                         "		start_month = 06, \n"
                         "		start_day = 10,\n"
                         "		start_hours = 0x23,\n"
                         "		start_minutes = 0x30,\n"
                         "		start_seconds = 0x00, \n"
                         "		duration_hours = 0x12, \n"
                         "		duration_minutes = 0x00,\n"
                         "		duration_seconds = 0x00, \n"
                         "		running_status = 4, # 4 service is running, 1 not running, 2 starts in a few seconds, 3 pausing\n"
                         "		free_CA_mode = 0, # 0 means service is not scrambled, 1 means at least a stream is scrambled\n"
                         "		event_descriptor_loop = [\n"
                         "		    short_event_descriptor (\n"
                         "			ISO639_language_code = \"SPA\", \n"
                         "			event_name = \"epg event name 2\",\n"
                         "			text = \"this is the following text example\", \n"
                         "		    )    \n"
                         "		],\n"
                         "	    ),\n"
                         "            ],\n"
                         "        segment_last_section_number = 1,\n"
                         "        version_number = 1, \n"
                         "        section_number = 1, # this is the second section\n"
                         "        last_section_number = 1, \n"
                         "        )\n");

        strTables.append("out = open(\"./eit"+auxString1+".sec\", \"wb\")\n"
                         "out.write(eit"+auxString1+".pack())\n"
                         "out.close\n"
                         "out = open(\"./eit"+auxString1+".sec\", \"wb\") # python   flush bug\n"
                         "out.close\n"
                         "os.system('sec2ts 18 "+QString((it==0)?"-s":" ")+" < ./eit"+auxString1+".sec "+QString((it==0)?">":">>")+" ./eit.ts')\n"
                          "\n"
                         "out = open(\"./eit_follow"+auxString1+".sec\", \"wb\")\n"
                         "out.write(eit_follow"+auxString1+".pack())\n"
                         "out.close\n"
                         "out = open(\"./eit_follow"+auxString1+".sec\", \"wb\") # python   flush bug\n"
                         "out.close\n"
                         "os.system('sec2ts 18 < ./eit_follow"+auxString1+".sec >> ./eit.ts')\n");
    }


    for(int it=0;it<(nservice+oneseg-1);it++)
    {
        auxString1=QVariant(it).toString();
        auxString2=QVariant(it-oneseg+1).toString();
        if(field("GingaApp"+auxString2).toBool()){
            strTables.append("ait"+auxString1+" = application_information_section(\n"
                             "		application_type = 0x0009, # GINGA-NCL\n"
                             "		common_descriptor_loop = [],\n"
                             "		application_loop = [\n"
                             "			application_loop_item(\n"
                             "				organisation_id = 0x0000000A,\n"
                             "				application_id = 0x64,\n"
                             "				application_control_code = 0x01,\n"
                             "				application_descriptors_loop = [\n"
                             "					transport_protocol_descriptor(\n"
                             "						protocol_id = 0x0001,\n"
                             "						transport_protocol_label = 0,\n"
                             "						remote_connection = 0,\n"
                             "						component_tag = 0x0C, # association_tag\n"
                             "					),\n"
                             "					application_descriptor(\n"
                             "						application_profile = 0x0001,\n"
                             "						version_major = 1,\n"
                             "						version_minor = 0,\n"
                             "						version_micro = 0,\n"
                             "						service_bound_flag = 1,\n"
                             "						visibility = 3,\n"
                             "						application_priority = 1,\n"
                             "						transport_protocol_labels = [ 0 ],\n"
                             "					),\n"
                             "					application_name_descriptor(\n"
                             "						application_name = \"APP_GINGA\"\n"
                             "					),\n"
                             "					ginga_ncl_application_descriptor(\n"
                             "						parameters = [ ]\n"
                             "					),\n"
                             "					ginga_ncl_application_location_descriptor (\n"
                             "						base_directory = \"/\",\n"
                             "						class_path_extension = \"\",\n"
                             "						initial_class = \"main.ncl\",\n"
                             "					),\n"
                             "				]\n"
                             "			),\n"
                             "		],\n"
                             "version_number = 0,\n"
                             "section_number = 0,\n"
                             "last_section_number = 0,\n"
                             ")\n\n");
            strTables.append("out = open(\"./ait"+auxString1+".sec\", \"wb\")\n"
                             "out.write(ait"+auxString1+".pack())\n"
                             "out.close()\n"
                             "os.system(\"sec2ts \" + str(tvd_ait_pid_"+auxString1+") + \" < ./ait"+auxString1+".sec > ./ait"+auxString1+".ts\")\n");
         }
    }
    strTables.append("");
            strTables.append("");


    Text[1]->setPlainText(strTables);
    pythonHighlighter = new KickPythonSyntaxHighlighter(Text[1]->document());


}
