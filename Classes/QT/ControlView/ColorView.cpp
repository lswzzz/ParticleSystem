#include "ColorView.h"
#include "QLayout"
#include "FontChina.h"

ColorView::ColorView(char* title, QSize size)
	:BaseDockWidget(title, size, true)
{
	target = NULL;
	isInsideOpera = false;
	QGridLayout* layout = new QGridLayout;
	color_r = new QSlider(Qt::Horizontal);
	color_r->setMinimum(0);
	color_r->setMaximum(255);
	color_r->setValue(0);
	color_g = new QSlider(Qt::Horizontal);
	color_g->setMinimum(0);
	color_g->setMaximum(255);
	color_g->setValue(0);
	color_b = new QSlider(Qt::Horizontal);
	color_b->setMinimum(0);
	color_b->setMaximum(255);
	color_b->setValue(0);
	color_a = new QSlider(Qt::Horizontal);
	color_a->setMinimum(0);
	color_a->setMaximum(255);
	color_a->setValue(0);
	layout->addWidget(new QLabel(FontChina::G2U("red")), 0, 0, 1, 1);
	layout->addWidget(color_r, 0, 1, 1, 4);
	label_r = new QLabel("0");
	layout->addWidget(label_r, 0, 5, 1, 1);
	layout->addWidget(new QLabel(FontChina::G2U("green")), 0, 6, 1, 1);
	layout->addWidget(color_g, 0, 7, 1, 4);
	label_g = new QLabel("0");
	layout->addWidget(label_g, 0, 11, 1, 1);
	layout->addWidget(new QLabel(FontChina::G2U("blue")), 1, 0, 1, 1);
	layout->addWidget(color_b, 1, 1, 1, 4);
	label_b = new QLabel("0");
	layout->addWidget(label_b, 1, 5, 1, 1);
	layout->addWidget(new QLabel(FontChina::G2U("alpha")), 1, 6, 1, 1);
	layout->addWidget(color_a, 1, 7, 1, 4);
	label_a = new QLabel("0");
	layout->addWidget(label_a, 1, 11, 1, 1);
	widget->setLayout(layout);
	_connect();
}

ColorView::~ColorView()
{
}

void ColorView::_connect()
{
	connect(color_r, SIGNAL(valueChanged(int)), this, SLOT(setREditValue(int)));
	connect(color_g, SIGNAL(valueChanged(int)), this, SLOT(setGEditValue(int)));
	connect(color_b, SIGNAL(valueChanged(int)), this, SLOT(setBEditValue(int)));
	connect(color_a, SIGNAL(valueChanged(int)), this, SLOT(setAEditValue(int)));
}

void ColorView::setTarget(C3DShape* tar)
{
	target = tar;
	isInsideOpera = true;
	setValueFromTarget();
	isInsideOpera = false;
}

void ColorView::setValueFromTarget()
{
	GLfloat* color = target->getColor();
	int r = color[0] * 255.0;
	int g = color[1] * 255.0;
	int b = color[2] * 255.0;
	int a = color[3] * 255.0;
	color_r->setValue(r);
	label_r->setText(QString::number(r));
	color_g->setValue(g);
	label_g->setText(QString::number(g));
	color_b->setValue(b);
	label_b->setText(QString::number(b));
	color_a->setValue(a);
	label_a->setText(QString::number(a));
}

void ColorView::setAEditValue(int value)
{
	if (isInsideOpera)return;
	label_a->setText(QString::number(value));
	float v = value;
	target->setColorA(v / 255.0);
}

void ColorView::setREditValue(int value)
{
	if (isInsideOpera)return;
	label_r->setText(QString::number(value));
	float v = value;
	target->setColorR(v / 255.0);
}

void ColorView::setGEditValue(int value)
{
	if (isInsideOpera)return;
	label_g->setText(QString::number(value));
	float v = value;
	target->setColorG(v / 255.0);
}

void ColorView::setBEditValue(int value)
{
	if (isInsideOpera)return;
	label_b->setText(QString::number(value));
	float v = value;
	target->setColorB(v / 255.0);
}
