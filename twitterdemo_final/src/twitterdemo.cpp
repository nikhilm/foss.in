#include "twitterdemo.h"

#include <QtXml>
#include <QInputDialog>

#include <kio/jobclasses.h>
#include <kio/job.h>
#include <KUrl>
#include <KListWidget>
#include <KStatusBar>
#include <KMessageBox>
#include <KLocale>
#include <KAction>
#include <KStandardAction>
#include <KActionCollection>

#include <kdebug.h>

TwitterDemo::TwitterDemo( QWidget *parent )
    : KXmlGuiWindow( parent )
{
    m_tweetsList = new KListWidget( this );
    m_tweetsList->setSpacing( 5 );
    m_tweetsList->setAlternatingRowColors( true );

    m_config = new KConfig;
    m_generalGroup = new KConfigGroup( m_config, "General" );
    m_tweetsGroup = new KConfigGroup( m_config, "tweets" );

    setCentralWidget( m_tweetsList );
    setupActions();

    QDomDocument existing( "tweets" );
    bool result = existing.setContent( m_tweetsGroup->readEntry( "saved_tweets", QString() ) );

    loadTweets( existing );
}

void TwitterDemo::setupActions()
{
    KAction *refreshAction = new KAction( actionCollection() );
    refreshAction->setText( i18n( "Refresh" ) );
    refreshAction->setIcon( KIcon( "view-refresh" ) );
    refreshAction->setShortcut( Qt::CTRL + Qt::Key_R );
    actionCollection()->addAction( "refresh", refreshAction );
    connect( refreshAction, SIGNAL( triggered( bool ) ), this, SLOT( updateTweets() ) );

    KStandardAction::preferences( this, // <- slot owner
                                  SLOT( slotPreferences() ), // <- slot name
                                  actionCollection() ); // <- parent

    KStandardAction::quit( this, SLOT( close() ), actionCollection() );

    setupGUI();
}

void TwitterDemo::updateTweets()
{
    statusBar()->showMessage( i18n( "Downloading..." ) );

    // See http://apiwiki.twitter.com/Twitter-REST-API-Method:-statuses-user_timeline
    QString endpoint( "http://twitter.com/statuses/user_timeline/%2.xml?since_id=%1" );

    QString last_tweet = m_generalGroup->readEntry( "last_tweet", QString( "1" ) );
    endpoint = endpoint.arg( last_tweet );
    
    QString user = m_generalGroup->readEntry( "user", QString() );
    if( user.isEmpty() )
        user = slotPreferences();

    if( user.isEmpty() )
    {
        statusBar()->showMessage( "Please set user" );
        return;
    }
    
    m_responseData.clear();
    KIO::TransferJob *job = KIO::get( KUrl( endpoint.arg( user ) ) );
    connect( job, SIGNAL( data( KIO::Job *, const QByteArray & ) ), this, SLOT( response( KIO::Job *, const QByteArray & ) ) );
    connect( job, SIGNAL( result( KJob * ) ), this, SLOT( slotResult( KJob * ) ) );
}

void TwitterDemo::response( KIO::Job *job, const QByteArray &data )
{
    m_responseData.append( data );
}

void TwitterDemo::slotResult( KJob *job )
{
    if( job->error() )
    {
        KMessageBox::error( this, "Error: " + job->errorString(), "Error" );
        return;
    }

    statusBar()->showMessage( "Downloaded tweets" );

    QDomDocument dom( "tweets" );
    dom.setContent( m_responseData );
    loadTweets( dom );

    QDomNodeList statuses = dom.elementsByTagName( "status" );

    if( statuses.size() > 0 )
        saveLastTweetId( statuses.at( 0 ) );

    QDomDocument save( "save" );
    save.setContent( m_responseData );

    QDomDocument old( "old" );
    old.setContent( m_tweetsGroup->readEntry( "saved_tweets", QString() ) );
   

    QDomNodeList oldstats = old.elementsByTagName( "status" );
    for( int i = 0; i < oldstats.length(); i++ )
    {
        save.firstChildElement().appendChild( oldstats.at(i).cloneNode() );
    }

    m_tweetsGroup->writeEntry( "saved_tweets", save.toString() );
    m_tweetsGroup->sync();
}

void TwitterDemo::loadTweets( const QDomDocument & dom )
{

    QDomNodeList statuses = dom.elementsByTagName( "status" );

    for( int i = statuses.length() - 1; i >= 0; i-- )
    {
        QDomNode status = statuses.item( i );
        QListWidgetItem *item = new QListWidgetItem( formatTweet( status ) );
        m_tweetsList->insertItem( 0, item );
    }
}

const QString TwitterDemo::formatTweet( const QDomNode &status ) const
{
    QString fmt( "%1: %2" );

    QDomNode user = status.firstChildElement( "user" );

    fmt = fmt.arg( user.firstChildElement( "name" ).text() );

    fmt = fmt.arg( status.firstChildElement( "text" ).text() );

    return fmt;
}

void TwitterDemo::saveLastTweetId( const QDomNode &status )
{
    m_generalGroup->writeEntry( "last_tweet", status.firstChildElement( "id" ).text() );
    m_generalGroup->sync();
}

QString TwitterDemo::slotPreferences()
{
    bool ok = true;

    QString user = m_generalGroup->readEntry( "user", QString() );
    user = QInputDialog::getText(
            this // parent
            , i18n( "Fetch tweets for" ) // title
            , i18n( "Twitter username to fetch tweets for" ) // label
            , QLineEdit::Normal // input type ( password? )
            , user // default value
            , &ok // errors
            );

    if( ok && !user.isEmpty() )
    {
        m_generalGroup->writeEntry( "user", user );
        m_generalGroup->sync();
    }

    return user;
}
