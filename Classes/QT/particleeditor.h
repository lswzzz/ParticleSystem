#ifndef QTEDITOR_H
#define QTEDITOR_H

#include <QtWidgets/QMainWindow>
#include "ui_particleeditor.h"
#include "ResourceView.h"
#include "ControlView.h"
#include "ModelView.h"

namespace Ui{
	class ParticleEditor;
}

class ParticleEditor : public QMainWindow
{
	Q_OBJECT

public:
	explicit ParticleEditor(QWidget *parent = 0);
	~ParticleEditor();
	Ui::ParticleEditorClass getUI(){ return ui; }
protected:
	void closeEvent(QCloseEvent* e);
	void setDockWidget();
	void createResourceView();
	void createControlView();
	void createModelView();
	void OutputPlist(QString filename);
	void SaveConfigFile(QString filename);
	void OpenConfigFile(QString filename);
	void setDockWidgetVisible(QDockWidget* widget, QString objName);
private slots:
	void on_actionAdd_Res_triggered();
	void on_actionOpenConfig_triggered();
	void on_actionSaveConfig_triggered();
	void on_actionSave_as_triggered();
	void on_actionOutput_triggered();

	void on_actionControlView_triggered();
	void on_actionResView_triggered();
	void on_actionModelView_triggered();

private:
	Ui::ParticleEditorClass ui;
	ResourceView* resourceView;
	ControlView* controlView;
	ModelView* modelView;
	QString fileName;
};

#endif // QTEDITOR_H
