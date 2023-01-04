#include "MainWindow.h"

#include "EnterMenu.h"
#include "SettingsWidget.h"
#include "TyperWidget.h"

#include "auth/RegistrationWidget.h"
#include "auth/AuthentificationWidget.h"

#include <QApplication>
#include <QPushButton>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QJsonDocument>


typer::gui::MainWindow::MainWindow(QWidget *parent)
    : QMainWindow( parent )
{
    setEnterMenu();
}

void typer::gui::MainWindow::setEnterMenu()
{
    EnterMenu * enterMenu = new EnterMenu;
    setCentralWidget(  enterMenu );

    connect( enterMenu, &EnterMenu::start, this, [this](){
        TyperWidget * typerWidget = new TyperWidget;
        setCentralWidget( typerWidget );
        connect( typerWidget, &TyperWidget::exit,
                 this, &MainWindow::setEnterMenu);
    });

    connect( enterMenu, &EnterMenu::settings, this, [this](){
        SettingsWidget * settingsWidget = new SettingsWidget;
        setCentralWidget( settingsWidget );
        connect( settingsWidget, &SettingsWidget::exit,
                 this, &MainWindow::setEnterMenu);
    });

    connect( enterMenu, &EnterMenu::auth, this, [this](){
        AuthentificationWidget * authWidget = new AuthentificationWidget;
        setCentralWidget( authWidget );
        connect( authWidget, &AuthentificationWidget::accepted,
                 this, [this](const typer::common::AuthentificationInfo & info) {
            // @todo encript pass
            QString urlString = QString("http://127.0.0.1:8080/auth?user_name='%1'&user_password='%2'")
                    .arg(info.userName)
                    .arg(info.password);

            qDebug() << "url string is" << urlString;

            QNetworkRequest textRequest( urlString );
            bool requestFinished = false;
            QNetworkAccessManager * manager = new QNetworkAccessManager;
            connect(manager, &QNetworkAccessManager::finished, this, [&requestFinished](QNetworkReply * reply) {
                if ( reply->error() == QNetworkReply::NoError )
                {
                    QString text = QString(reply->readAll());
                    QJsonDocument d = QJsonDocument::fromJson( reply->readAll() );
                    qDebug() << "recieve" << text;
                }
                else
                {
                    qDebug() << "!!! request error";
                }
                requestFinished = true;
            });
            manager->get(textRequest);
            while ( !requestFinished ) qApp->processEvents();
        });
        connect( authWidget, &AuthentificationWidget::canceled,
                 this, &MainWindow::setEnterMenu);
    });

    connect( enterMenu, &EnterMenu::registration, this, [this](){
        RegistrationWidget * registrationWidget = new RegistrationWidget;
        setCentralWidget( registrationWidget );
        connect( registrationWidget, &RegistrationWidget::accepted,
                 [this](const typer::common::RegistrationInfo & info)
        {
            // @todo encript pass
            QString urlString = QString("http://127.0.0.1:8080/register?user_name='%1'&user_password='%2'")
                    .arg(info.userName)
                    .arg(info.password);

            qDebug() << "url string is" << urlString;

            QNetworkRequest textRequest( urlString );
            bool requestFinished = false;
            QNetworkAccessManager * manager = new QNetworkAccessManager;
            connect(manager, &QNetworkAccessManager::finished, this, [&requestFinished](QNetworkReply * reply) {
                if ( reply->error() == QNetworkReply::NoError )
                {
                    QString text = QString(reply->readAll());
                    QJsonDocument d = QJsonDocument::fromJson( reply->readAll() );
                    qDebug() << "recieve" << text;
                }
                else
                {
                    qDebug() << "!!! request error";
                }
                requestFinished = true;
            });
            manager->get(textRequest);
            while ( !requestFinished ) qApp->processEvents();
        });
        connect( registrationWidget, &RegistrationWidget::canceled,
                 this, &MainWindow::setEnterMenu);
    });
}
