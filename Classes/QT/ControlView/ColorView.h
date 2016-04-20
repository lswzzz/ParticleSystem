#pragma once
#include "BaseDockWidget.h"
#include "QSlider"
#include "C3DShape.h"
#include "QLabel"

class ColorView : public BaseDockWidget
{
	Q_OBJECT
public:
	ColorView(char* title, QSize size);
	~ColorView();
	void setTarget(C3DShape* tar);

protected:
	void _connect();
	void setValueFromTarget();
private slots:
	void setAEditValue(int value);
	void setREditValue(int value);
	void setGEditValue(int value);
	void setBEditValue(int value);
private:
	QSlider* color_r;
	QSlider* color_g;
	QSlider* color_b;
	QSlider* color_a;
	QLabel* label_r;
	QLabel* label_g;
	QLabel* label_b;
	QLabel* label_a;
	C3DShape* target;
	bool isInsideOpera;
};

