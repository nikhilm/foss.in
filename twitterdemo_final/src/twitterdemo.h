#ifndef TWITTERDEMO_H
#define TWITTERDEMO_H

// Superclass
#include <KXmlGuiWindow>

#include <KConfig>
#include <KConfigGroup>

// forward declarations
namespace KIO
{
class Job;
}

class QDomNode;
class KJob;
class KListWidget;

class TwitterDemo : public KXmlGuiWindow
{
    Q_OBJECT
public:
    TwitterDemo( QWidget *parent=0 );

private:
    void setupActions();

private slots:
    void updateTweets();
    void response( KIO::Job *, const QByteArray & );
    void slotResult( KJob * );
    QString slotPreferences();

private:
    const QString formatTweet( const QDomNode & ) const;
    void loadTweets( const QDomDocument & );
    void saveLastTweetId( const QDomNode & );

    KListWidget *m_tweetsList;
    QByteArray m_responseData;

    KConfig *m_config;
    KConfigGroup *m_generalGroup;
    KConfigGroup *m_tweetsGroup;
    
};

#endif
