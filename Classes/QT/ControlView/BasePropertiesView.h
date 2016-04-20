#pragma once
#include "BaseDockWidget.h"
#include "C3DParticleSystem.h"
#include "QDoubleSpinBox"
#include  "QLayout"

class BasePropertiesView : public BaseDockWidget
{
	Q_OBJECT
public:
	BasePropertiesView(char* title, QSize size);
	~BasePropertiesView();
	void setTarget(C3DParticleSystem* tar);
protected:
	void createLayout();
	void addToLayout(QVector<QDoubleSpinBox*> vec, QString name);
	void createAccelerationMin();
	void createAccelerationMax();
	void createSizeMin();
	void createSizeMax();
	void createSizeVelocity();
	void createVelocityMin();
	void createVelocityMax();
	void createColorMin();
	void createColorMax();
	void createColorVelocity();
	void createLife();
	void setValueFromTarget();

	void resetAccMinValue();
	void resetAccMaxValue();
	void resetSizeMinValue();
	void resetSizeMaxValue();
	void resetSizeVelocValue();
	void resetVelocMinValue();
	void resetVelocMaxValue();
	void resetColorMinValue();
	void resetColorMaxValue();
	void resetColorVelocValue();
	void resetLifeValue();
private slots:

private:
	QVector<QDoubleSpinBox*> acclerationMin;
	QVector<QDoubleSpinBox*> acclerationMax;
	QVector<QDoubleSpinBox*> sizeMin;
	QVector<QDoubleSpinBox*> sizeMax;
	QVector<QDoubleSpinBox*> sizeVelocity;
	QVector<QDoubleSpinBox*> velocityMin;
	QVector<QDoubleSpinBox*> velocityMax;
	QVector<QDoubleSpinBox*> colorMin;
	QVector<QDoubleSpinBox*> colorMax;
	QVector<QDoubleSpinBox*> colorVelocity;
	QVector<QDoubleSpinBox*> life;
	QGridLayout* layout;
	C3DParticleSystem * target;
	bool isInsideOpera;
};

