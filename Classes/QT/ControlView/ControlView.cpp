#include "ControlView.h"
#include "QLayout"
#include "QLabel"

ControlView::ControlView(char* title, QSize size)
	:BaseDockWidget(title, size)
{
	target = NULL;
	isInsideOperat = false;
	scrollArea = new QScrollArea();
	scrollArea->setWidgetResizable(true);
	scrollArea->setAlignment(Qt::AlignTop);
	scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	scrollArea->setStyleSheet("background-color: rgb(191, 191, 191);");
	addDock();
	this->setWidget(scrollArea);
	this->setFeatures(QDockWidget::NoDockWidgetFeatures);
	connect(m_particleType, SIGNAL(currentIndexChanged(int)), this, SLOT(particleTypeIndexChanged(int)));
}

ControlView::~ControlView()
{
}

bool ControlView::addDockWidget(QDockWidget* widget)
{
	vec.push_back(widget);
	QGridLayout* gridLayout = new QGridLayout;
	gridLayout->addWidget(new QLabel("particle_Type:"), 0, 0, 1, 1);
	gridLayout->addWidget(m_particleType, 0, 1, 1, 1);
	for (int i = 0; i < vec.size(); i++){
		QDockWidget* dockWidget = vec.at(i);
		gridLayout->addWidget(dockWidget, i+1, 0, 1, 2);
		gridLayout->setRowStretch(i, 1);
	}
	gridLayout->addWidget(new QLabel(), vec.size()+1, 0, 1, 1);
	gridLayout->setRowStretch(vec.size()+1, 100);
	QWidget* widget__ = new QWidget();
	widget__->setLayout(gridLayout);
	scrollArea->setWidget(widget__);
	this->setFeatures(QDockWidget::NoDockWidgetFeatures);
	return true;
}

QScrollArea* ControlView::getScrollArea()
{
	return scrollArea;
}

void ControlView::addDock()
{
	m_particleType = new QComboBox;
	m_particleType->addItem("PT_FIRE");
	m_particleType->addItem("PT_FIREWORK");
	m_particleType->addItem("PT_FOUNTAIN");
	m_particleType->addItem("PT_MAX");
	addBasePropertiesView();
	addBlendFuncView();
	addColorView();
}

void ControlView::addBlendFuncView()
{
	blendFuncView = new BlendFuncView("Blend Func", QSize(320, 150));
	this->addDockWidget(blendFuncView);
}

void ControlView::addColorView()
{
	colorView = new ColorView("Color", QSize(320, 80));
	this->addDockWidget(colorView);
}

void ControlView::addBasePropertiesView()
{
	basePropertiesView = new BasePropertiesView("Base View", QSize(320, 845));
	this->addDockWidget(basePropertiesView);
}

void ControlView::setTarget(C3DParticleSystem* tar)
{
	target = tar;
	blendFuncView->setTarget(target);
	colorView->setTarget(target);
	basePropertiesView->setTarget(target);
}

void ControlView::setParticleType(int index)
{
	isInsideOperat = true;
	m_particleType->setCurrentIndex(index);
	isInsideOperat = false;
}

void ControlView::particleTypeIndexChanged(int index)
{
	if (isInsideOperat)return;
	switch (index){
	case 0:
		target->setParticleType(eParticleType::PT_FIRE);
		break;
	case 1:
		target->setParticleType(eParticleType::PT_FIREWORK);
		break;
	case 2:
		target->setParticleType(eParticleType::PT_FOUNTAIN);
		break;
	case 3:
		target->setParticleType(eParticleType::PT_MAX);
		break;
	}
	setTarget(target);
}