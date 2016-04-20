#pragma once
#include "BaseDockWidget.h"
#include <QScrollArea>
#include "BlendFuncView.h"
#include "C3DParticleSystem.h"
#include "ColorView.h"
#include "BasePropertiesView.h"
#include "QComboBox"

class ControlView : public BaseDockWidget
{
	Q_OBJECT
public:
	ControlView(char* title, QSize size);
	~ControlView();
	bool addDockWidget(QDockWidget* widget);
	QScrollArea* getScrollArea();
	void addDock();
	void addBlendFuncView();
	void addColorView();
	void addBasePropertiesView();
	void setTarget(C3DParticleSystem* tar);
	void setParticleType(int index);
private slots:
	void particleTypeIndexChanged(int index);
private:
	QScrollArea* scrollArea;
	std::vector<QDockWidget*> vec;
	BlendFuncView* blendFuncView;
	ColorView* colorView;
	BasePropertiesView* basePropertiesView;
	QComboBox* m_particleType;
	C3DParticleSystem* target;
	bool isInsideOperat;
};

