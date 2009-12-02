#ifndef TWITTERDEMO_H
#define TWITTERDEMO_H

// Superclass
#include <KXmlGuiWindow>

class KListWidget;

class TwitterDemo : public KXmlGuiWindow
{
    // allows us to use Qt's Signals and Slots system
    Q_OBJECT

public:
    TwitterDemo( QWidget *parent=0 );

private:
    void setupActions();

private slots:
    void slotPreferences();

private:
    KListWidget *m_tweetsList;
    
};

#endif
