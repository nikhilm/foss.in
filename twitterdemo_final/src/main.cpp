#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>
#include <KLocale>

#include "twitterdemo.h"

int main( int argc, char *argv[] )
{
    KAboutData aboutData( "twitterdemo", 0,
            ki18n( "Tweet Fetcher" ), "1.0",
            ki18n( "A simple app to fetch tweets" ),
            KAboutData::License_GPL,
            ki18n( "Copyright (c) 2009 Nikhil Marathe" ) );

    aboutData.addAuthor( ki18n( "Nikhil Marathe" ), ki18n("Core Developer"), "nsm.nikhil@gmail.com" );

    KCmdLineArgs::init( argc, argv, &aboutData );

    KApplication app;

    TwitterDemo *window = new TwitterDemo;
    window->show();

    return app.exec();
}
