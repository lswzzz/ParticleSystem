#pragma once
#include "BaseDockWidget.h"
#include "QListWidget.h"
#include "QComboBox"
#include "C3DShape.h"

class ResourceView : public BaseDockWidget
{
	Q_OBJECT
public:
	ResourceView(char* title, QSize size);
	~ResourceView();
	void addRes(QString image);
	bool getModel();
	void setTarget(C3DShape* shape);
	QStringList getImageList();
	void clearResourceList();
private slots:
	void setResShowMode(int mode);
	void action_delete_Res();
	void action_setTexture();
protected:
	void contextMenuEvent(QContextMenuEvent *event);
private:
	QListWidget* listWidget;
	QString outputName;
	QString outputDir;
	QComboBox* showMode;
	C3DShape* target;
};
