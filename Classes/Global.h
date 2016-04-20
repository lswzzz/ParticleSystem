#pragma once 
#include <qplaintextedit.h>
#include "cocos2d.h"
#include <QtCore\qobject.h>
#include "AppDelegate.h"

using namespace cocos2d;


extern QWidget* glWidget;
extern Layer* g_scene;
extern QObject* g_editor;
extern AppDelegate* g_app;
extern QPlainTextEdit* logText;
extern QString g_save_Dir;
extern QWidget* g_controlView;
extern Layer* g_Layer;
extern QWidget* g_resourceView;
extern HWND g_cocos_HWND;



void addConsoleInfo(std::string str);

void clearConsoleInfo();

