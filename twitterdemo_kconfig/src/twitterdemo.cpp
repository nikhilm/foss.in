#include "twitterdemo.h"

#include <QtXml>
#include <QInputDialog>
#include <QDateTime>
#include <QRect>

#include <KApplication>
#include <KListWidget>
#include <KStatusBar>
#include <KLocale>
#include <KAction>
#include <KStandardAction>
#include <KActionCollection>

#include <KConfig>
#include <KConfigGroup>

#include <kdebug.h>

TwitterDemo::TwitterDemo( QWidget *parent )
    : KXmlGuiWindow( parent )
{
    m_list = new KListWidget( this );

    // global config
    // will create a file called twitterdemorc ( usually in .kde4/share/config )
    m_config = new KConfig;

    // represents a section in the file
    // [General]
    m_generalGroup = new KConfigGroup( m_config, "General" );

    setCentralWidget( m_list );
    setupActions();

    displayConfig();
}

void TwitterDemo::setupActions()
{
    KAction *refreshAction = new KAction( actionCollection() );
    refreshAction->setText( i18n( "Refresh" ) );
    refreshAction->setIcon( KIcon( "view-refresh" ) );
    refreshAction->setShortcut( Qt::CTRL + Qt::Key_R );
    actionCollection()->addAction( "refresh", refreshAction );

    KStandardAction::preferences( this, // <- slot owner
                                  SLOT( saveConfig() ), // <- slot name
                                  actionCollection() ); // <- parent

    KStandardAction::quit( this, SLOT( close() ), actionCollection() );

    setupGUI();
}

void TwitterDemo::displayConfig()
{
    QString fact = m_generalGroup->readEntry( "fact", QString( "default" ) );
    int answer = m_generalGroup->readEntry( "answer", 0 );
    QDateTime now = m_generalGroup->readEntry( "now", QDateTime( QDate( 2012, 12, 21 ) ) );
    QRect geom = m_generalGroup->readEntry( "window", QRect( 0, 0, 0, 0 ) );

    m_list->clear();
    m_list->addItem( fact );
    m_list->addItem( QString::number( answer ) );
    m_list->addItem( now.toString() );
    m_list->addItem( i18n( "Window left coordinate %1" ).arg( geom.x() ) );
}

void TwitterDemo::saveConfig()
{
    // the usual types
    m_generalGroup->writeEntry( "fact", "etaoin shrdlu" );
    m_generalGroup->writeEntry( "answer", 42 );

    // not so usual
    m_generalGroup->writeEntry( "now", QDateTime::currentDateTime() );
    m_generalGroup->writeEntry( "window", geometry() );

    // VERY IMPORTANT
    m_generalGroup->sync();

    statusBar()->showMessage( "Wrote configuration" );

    displayConfig();
}
