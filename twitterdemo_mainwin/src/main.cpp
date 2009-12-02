#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>
#include <KLocale>

#include "twitterdemo.h"

int main( int argc, char *argv[] )
{
    KAboutData aboutData( "twitterdemo", 0, // this 0 is catalog name for translations
            ki18n( "Tweet Fetcher" ), "1.0",
            ki18n( "A simple app to fetch tweets" ),
            KAboutData::License_GPL,
            ki18n( "Copyright (c) 2009 Your name " ) );

    aboutData.addAuthor( ki18n( "Your Name" ), ki18n( "Core Developer" ), "rockstar@example.com" );
    aboutData.addAuthor( ki18n( "Creative Mind" ), ki18n( "Designer" ), "3columns@example.com" );

    KCmdLineArgs::init( argc, argv, &aboutData );

    KApplication app;

    TwitterDemo *window = new TwitterDemo;
    window->show();

    return app.exec();
}
