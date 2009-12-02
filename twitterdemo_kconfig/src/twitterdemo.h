#ifndef TWITTERDEMO_H
#define TWITTERDEMO_H

// Superclass
#include <KXmlGuiWindow>

// NEW
class KConfig;
class KConfigGroup;

class KListWidget;

class TwitterDemo : public KXmlGuiWindow
{
    Q_OBJECT
public:
    TwitterDemo( QWidget *parent=0 );

private:
    void setupActions();
    void displayConfig();

private slots:
    void saveConfig();

private:
    KListWidget *m_list;

    KConfig *m_config;
    KConfigGroup *m_generalGroup;
    
};

#endif
