project ( twitterdemo )

find_package ( KDE4 REQUIRED )
include_directories ( ${KDE4_INCLUDES} )

set ( twitterdemo_SRCS
    src/main.cpp
    src/twitterdemo.cpp
)

kde4_add_executable ( twitterdemo ${twitterdemo_SRCS} )
target_link_libraries ( twitterdemo ${KDE4_KDEUI_LIBS} ${KDE4_KPARTS_LIBS} )

install ( TARGETS twitterdemo DESTINATION ${BIN_INSTALL_DIR} )
install ( FILES src/twitterdemoui.rc DESTINATION ${DATA_INSTALL_DIR}/twitterdemo )
