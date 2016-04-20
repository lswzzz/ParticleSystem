#include "Global.h"
#include "FontChina.h"
#include <cstdarg>
#include <qtextcursor.h>
#include <atlstr.h>
#include <QTextStream>
#include <QJsonDocument>

QWidget* glWidget = NULL;
Layer* g_scene = NULL;
QObject* g_editor = NULL;
AppDelegate* g_app = NULL;
HWND g_cocos_HWND = NULL;
QString g_save_Dir = "../Resources";
QWidget* g_controlView = NULL;
Layer* g_Layer = NULL;
QWidget* g_resourceView = NULL;
QPlainTextEdit* logText = NULL;

void addConsoleInfo(std::string str)
{
	QTextCursor cursor = logText->textCursor();
	cursor.movePosition(QTextCursor::End);
	logText->setTextCursor(cursor);
	logText->insertPlainText(FontChina::G2U((str + "\n").c_str()));
	cursor.movePosition(QTextCursor::End);
	logText->setTextCursor(cursor);
	logText->ensureCursorVisible();
}

void clearConsoleInfo()
{
	logText->clear();
}

