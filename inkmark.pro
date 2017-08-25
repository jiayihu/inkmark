######################################################################
# Automatically generated by qmake (3.0) ven ago 25 19:28:38 2017
######################################################################

TEMPLATE = app
TARGET = inkmark
OBJECTS_DIR=build
MOC_DIR=build

INCLUDEPATH += .
INCLUDEPATH += ./src
INCLUDEPATH += ./src/controllers
INCLUDEPATH += ./src/models
INCLUDEPATH += ./src/utilities
INCLUDEPATH += ./src/views
INCLUDEPATH += ./src/widgets

CONFIG += qt
CONFIG +=C++11
QT += widgets

RESOURCES = inkmark.qrc

# Input
HEADERS += src/inkmark.h \
           src/models/application_model.h \
           src/models/bookmark_model.h \
           src/models/user_model.h \
           src/utilities/utilities.h \
           src/controllers/application_controller/application_controller.h \
           src/controllers/auth_controller/auth_controller.h \
           src/views/application_view/application_view.h \
           src/views/auth_view/auth_view.h \
           src/widgets/button_widget/button_widget.h \
           src/widgets/link_widget/link_widget.h \
           src/widgets/text_area_widget/text_area_widget.h \
           src/widgets/text_input_widget/text_input_widget.h \
           src/controllers/admin/admin_application_controller/admin_application_controller.h \
           src/controllers/admin/users_list_controller/users_list_controller.h \
           src/controllers/users/add_bookmark_controller/add_bookmark_controller.h \
           src/controllers/users/bookmarks_list_controller/bookmarks_list_controller.h \
           src/controllers/users/search_bookmark_controller/search_bookmark_controller.h \
           src/controllers/users/user_application_controller/user_application_controller.h \
           src/views/admin/admin_application_view/admin_application_view.h \
           src/views/admin/edit_user_view/edit_user_view.h \
           src/views/admin/user_view/user_view.h \
           src/views/admin/users_list_view/users_list_view.h \
           src/views/users/bookmark_view/bookmark_view.h \
           src/views/users/bookmarks_list_view/bookmarks_list_view.h \
           src/views/users/edit_bookmark_view/edit_bookmark_view.h \
           src/views/users/search_bookmark_view/search_bookmark_view.h \
           src/views/users/user_application_view/user_application_view.h
SOURCES += main.cpp \
           src/inkmark.cpp \
           src/models/application_model.cpp \
           src/models/bookmark_model.cpp \
           src/models/user_model.cpp \
           src/utilities/utilities.cpp \
           src/controllers/application_controller/application_controller.cpp \
           src/controllers/auth_controller/auth_controller.cpp \
           src/views/application_view/application_view.cpp \
           src/views/auth_view/auth_view.cpp \
           src/widgets/button_widget/button_widget.cpp \
           src/widgets/link_widget/link_widget.cpp \
           src/widgets/text_area_widget/text_area_widget.cpp \
           src/widgets/text_input_widget/text_input_widget.cpp \
           src/controllers/admin/admin_application_controller/admin_application_controller.cpp \
           src/controllers/admin/users_list_controller/users_list_controller.cpp \
           src/controllers/users/add_bookmark_controller/add_bookmark_controller.cpp \
           src/controllers/users/bookmarks_list_controller/bookmarks_list_controller.cpp \
           src/controllers/users/search_bookmark_controller/search_bookmark_controller.cpp \
           src/controllers/users/user_application_controller/user_application_controller.cpp \
           src/views/admin/admin_application_view/admin_application_view.cpp \
           src/views/admin/edit_user_view/edit_user_view.cpp \
           src/views/admin/user_view/user_view.cpp \
           src/views/admin/users_list_view/users_list_view.cpp \
           src/views/users/bookmark_view/bookmark_view.cpp \
           src/views/users/bookmarks_list_view/bookmarks_list_view.cpp \
           src/views/users/edit_bookmark_view/edit_bookmark_view.cpp \
           src/views/users/search_bookmark_view/search_bookmark_view.cpp \
           src/views/users/user_application_view/user_application_view.cpp
