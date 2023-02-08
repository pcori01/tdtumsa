#include "tdtumsa.h"
#include <QApplication>
#include <QTranslator>
//#include <QLocale>
//#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    //Q_INIT_RESOURCE(tdtumsa);
    QApplication app(argc, argv);

    #ifndef QT_NO_TRANSLATION
        QString translatorFileName = QLatin1String("qt_");
        translatorFileName += QLocale::system().name();
        QTranslator *translator = new QTranslator(&app);
        if (translator->load(translatorFileName, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
            app.installTranslator(translator);
    #endif
    app.setWindowIcon(QIcon(":/images/logo.svg"));

    Tdtumsa wizard;
    wizard.show();

    QFont font("Arial");
    font.setStyleHint(QFont::Monospace);
    font.setPointSize(11);
    wizard.setFont(font);


    return app.exec();
}
