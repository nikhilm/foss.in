#include "twitterdemo.h"

#include <KListWidget>
#include <KStatusBar>
#include <KLocale>
#include <KAction>
#include <KStandardAction>
#include <KActionCollection>

#include <kdebug.h>

TwitterDemo::TwitterDemo( QWidget *parent )
    : KXmlGuiWindow( parent )
{
    // standard procedure
    // 1. create your main widget
    m_tweetsList = new KListWidget( this );

    // 2. set it as the central widget of the window
    setCentralWidget( m_tweetsList );

    // 3. Add the actions you need
    setupActions();

    // example of using the status bar
    statusBar()->showMessage( i18n( "Ready to go" ) );
}

void TwitterDemo::setupActions()
{
    KAction *refreshAction = new KAction( actionCollection() );
    refreshAction->setText( i18n( "Refresh" ) );
    refreshAction->setIcon( KIcon( "view-refresh" ) );
    refreshAction->setShortcut( Qt::CTRL + Qt::Key_R );
    actionCollection()->addAction( "refresh", refreshAction );

    // lets use a standard action for settings and to quit the application
    KStandardAction::preferences( this, // <- slot owner
                                  SLOT( slotPreferences() ), // <- slot name
                                  actionCollection() ); // <- parent

    KStandardAction::quit( this, SLOT( close() ), actionCollection() );

    setupGUI();
}

void TwitterDemo::slotPreferences()
{
}
