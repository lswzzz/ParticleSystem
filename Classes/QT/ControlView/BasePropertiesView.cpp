#include "BasePropertiesView.h"
#include "QLabel"
#include "FontChina.h"
#include "QPushButton"

BasePropertiesView::BasePropertiesView(char* title, QSize size)
	:BaseDockWidget(title, size, true)
{
	target = NULL;
	layout = new QGridLayout;
	createLayout();
	widget->setLayout(layout);
	isInsideOpera = false;
}

BasePropertiesView::~BasePropertiesView()
{
}

void BasePropertiesView::setTarget(C3DParticleSystem* tar)
{
	target = tar;
	isInsideOpera = true;
	setValueFromTarget();
	isInsideOpera = false;
}

void BasePropertiesView::setValueFromTarget()
{
	resetAccMinValue();
	resetAccMaxValue();
	resetSizeMinValue();
	resetSizeMaxValue();
	resetSizeVelocValue();
	resetVelocMinValue();
	resetVelocMaxValue();
	resetColorMinValue();
	resetColorMaxValue();
	resetColorVelocValue();
	resetLifeValue();
}

void BasePropertiesView::createLayout()
{
	createAccelerationMin();
	createAccelerationMax();
	createSizeMin();
	createSizeMax();
	createSizeVelocity();
	createVelocityMin();
	createVelocityMax();
	createColorMin();
	createColorMax();
	createColorVelocity();
	createLife();
}

//设定为每一行25 行头20
void BasePropertiesView::addToLayout(QVector<QDoubleSpinBox*> vec, QString name)
{
	static int count = 0;
	layout->addWidget(new QLabel(name), count / 4, count % 4, 1, 3);
	QPushButton* sub = new QPushButton;
	sub->setStyleSheet(" border: none; ");
	sub->setUserData(0, (QObjectUserData*)false);
	sub->setIcon(QIcon(":/icon/Resources/sub.ico"));
	layout->addWidget(sub, count / 4, count % 4 + 3, 1, 1);
	QVector<QLabel*> labelVec;
	count += 4;
	for (int i = 0; i < vec.size(); i++){
		QLabel* label = new QLabel(vec.at(i)->objectName());
		labelVec.push_back(label);
		layout->addWidget(label, count / 4, count % 4, 1, 1);
		count++;
		layout->addWidget(vec.at(i), count / 4, count % 4, 1, 1);
		count++;
	}
	count += 2;
	connect(sub, &QPushButton::clicked, [=]{
		bool state = (QObjectUserData*)sub->userData(0);
		if (!state){
			sub->setIcon(QIcon(":/icon/Resources/add2.ico"));
			sub->setUserData(0, (QObjectUserData*)true);
			for (int i = 0; i < labelVec.size(); i++){
				auto label = labelVec.at(i);
				label->setVisible(false);
			}
			for (int i = 0; i < vec.size(); i++){
				auto box = vec.at(i);
				box->setVisible(false);
			}
			size = QSize(size.width(), size.height() - 50);
			this->setMaximumSize(size);
			this->setMinimumSize(size);
		}
		else{
			sub->setIcon(QIcon(":/icon/Resources/sub.ico"));
			sub->setUserData(0, (QObjectUserData*)false);
			for (int i = 0; i < labelVec.size(); i++){
				auto label = labelVec.at(i);
				label->setVisible(true);
			}
			for (int i = 0; i < vec.size(); i++){
				auto box = vec.at(i);
				box->setVisible(true);
			}
			size = QSize(size.width(), size.height() + 50);
			this->setMaximumSize(size);
			this->setMinimumSize(size);
		}
	});
	
}

void BasePropertiesView::createAccelerationMin()
{
	QDoubleSpinBox* x = new QDoubleSpinBox;
	QDoubleSpinBox* y = new QDoubleSpinBox;
	QDoubleSpinBox* z = new QDoubleSpinBox;
	x->setObjectName("accleMin_x");
	y->setObjectName("accletMin_y");
	z->setObjectName("accleMin_z");
	acclerationMin.push_back(x);
	acclerationMin.push_back(y);
	acclerationMin.push_back(z);
	addToLayout(acclerationMin, FontChina::G2U("最小加速度"));
	connect(x, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double d){
		if (isInsideOpera)return;
		Vec3 acc = target->getParticleAccelerationMin();
		target->resetParticleAccelerationMin(Vec3(d, acc.y, acc.z));
	});
	connect(y, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double d){
		if (isInsideOpera)return;
		Vec3 acc = target->getParticleAccelerationMin();
		target->resetParticleAccelerationMin(Vec3(acc.x, d, acc.z));
	});
	connect(z, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double d){
		if (isInsideOpera)return;
		Vec3 acc = target->getParticleAccelerationMin();
		target->resetParticleAccelerationMin(Vec3(acc.x, acc.y, d));
	});
}

void BasePropertiesView::createAccelerationMax()
{
	QDoubleSpinBox* x = new QDoubleSpinBox;
	QDoubleSpinBox* y = new QDoubleSpinBox;
	QDoubleSpinBox* z = new QDoubleSpinBox;
	x->setObjectName("accleMax_x");
	y->setObjectName("accleMax_y");
	z->setObjectName("accleMax_z");
	acclerationMax.push_back(x);
	acclerationMax.push_back(y);
	acclerationMax.push_back(z);
	addToLayout(acclerationMax, FontChina::G2U("最大加速度"));
	connect(x, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double d){
		if (isInsideOpera)return;
		Vec3 acc = target->getParticleAccelerationMax();
		target->resetParticleAccelerationMax(Vec3(d, acc.y, acc.z));
	});
	connect(y, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double d){
		if (isInsideOpera)return;
		Vec3 acc = target->getParticleAccelerationMax();
		target->resetParticleAccelerationMax(Vec3(acc.x, d, acc.z));
	});
	connect(z, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double d){
		if (isInsideOpera)return;
		Vec3 acc = target->getParticleAccelerationMax();
		target->resetParticleAccelerationMax(Vec3(acc.x, acc.y, d));
	});
}

void BasePropertiesView::createSizeMin()
{
	QDoubleSpinBox* x = new QDoubleSpinBox;
	QDoubleSpinBox* y = new QDoubleSpinBox;
	QDoubleSpinBox* z = new QDoubleSpinBox;
	x->setObjectName("sizeMin_x");
	y->setObjectName("sizeMin_y");
	z->setObjectName("sizeMin_z");
	sizeMin.push_back(x);
	sizeMin.push_back(y);
	sizeMin.push_back(z);
	addToLayout(sizeMin, FontChina::G2U("最小尺寸"));
	connect(x, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double d){
		if (isInsideOpera)return;
		Vec3 size = target->getParticleSizeMin();
		target->resetParticleSizeMin(Vec3(d, size.y, size.z));
	});
	connect(y, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double d){
		if (isInsideOpera)return;
		Vec3 size = target->getParticleSizeMin();
		target->resetParticleSizeMin(Vec3(size.x, d, size.z));
	});
	connect(z, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double d){
		if (isInsideOpera)return;
		Vec3 size = target->getParticleSizeMin();
		target->resetParticleSizeMin(Vec3(size.x, size.y, d));
	});
}

void BasePropertiesView::createSizeMax()
{
	QDoubleSpinBox* x = new QDoubleSpinBox;
	QDoubleSpinBox* y = new QDoubleSpinBox;
	QDoubleSpinBox* z = new QDoubleSpinBox;
	x->setObjectName("sizeMax_x");
	y->setObjectName("sizeMax_y");
	z->setObjectName("sizeMax_z");
	sizeMax.push_back(x);
	sizeMax.push_back(y);
	sizeMax.push_back(z);
	addToLayout(sizeMax, FontChina::G2U("最大尺寸"));
	connect(x, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double d){
		if (isInsideOpera)return;
		Vec3 size = target->getParticleSizeMax();
		target->resetParticleSizeMax(Vec3(d, size.y, size.z));
	});
	connect(y, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double d){
		if (isInsideOpera)return;
		Vec3 size = target->getParticleSizeMax();
		target->resetParticleSizeMax(Vec3(size.x, d, size.z));
	});
	connect(z, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double d){
		if (isInsideOpera)return;
		Vec3 size = target->getParticleSizeMax();
		target->resetParticleSizeMax(Vec3(size.x, size.y, d));
	});
}

void BasePropertiesView::createSizeVelocity()
{
	QDoubleSpinBox* x = new QDoubleSpinBox;
	QDoubleSpinBox* y = new QDoubleSpinBox;
	QDoubleSpinBox* z = new QDoubleSpinBox;
	x->setObjectName("sizeVeloc_x");
	y->setObjectName("sizeVeloc_y");
	z->setObjectName("sizeVeloc_z");
	sizeVelocity.push_back(x);
	sizeVelocity.push_back(y);
	sizeVelocity.push_back(z);
	addToLayout(sizeVelocity, FontChina::G2U("大小变化速度"));
	connect(x, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double d){
		if (isInsideOpera)return;
		Vec3 size = target->getParticleSizeVelocity();
		target->resetParticleSizeVelocity(Vec3(d, size.y, size.z));
	});
	connect(y, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double d){
		if (isInsideOpera)return;
		Vec3 size = target->getParticleSizeVelocity();
		target->resetParticleSizeVelocity(Vec3(size.x, d, size.z));
	});
	connect(z, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double d){
		if (isInsideOpera)return;
		Vec3 size = target->getParticleSizeVelocity();
		target->resetParticleSizeVelocity(Vec3(size.x, size.y, d));
	});
}

void BasePropertiesView::createVelocityMin()
{
	QDoubleSpinBox* x = new QDoubleSpinBox;
	QDoubleSpinBox* y = new QDoubleSpinBox;
	QDoubleSpinBox* z = new QDoubleSpinBox;
	x->setObjectName("velocMin_x");
	y->setObjectName("velocMin_y");
	z->setObjectName("velocMin_z");
	velocityMin.push_back(x);
	velocityMin.push_back(y);
	velocityMin.push_back(z);
	addToLayout(velocityMin, FontChina::G2U("最小速度变化"));
	connect(x, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double d){
		if (isInsideOpera)return;
		Vec3 size = target->getParticleVelocityMin();
		target->resetParticleVelocityMin(Vec3(d, size.y, size.z));
	});
	connect(y, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double d){
		if (isInsideOpera)return;
		Vec3 size = target->getParticleVelocityMin();
		target->resetParticleVelocityMin(Vec3(size.x, d, size.z));
	});
	connect(z, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double d){
		if (isInsideOpera)return;
		Vec3 size = target->getParticleVelocityMin();
		target->resetParticleVelocityMin(Vec3(size.x, size.y, d));
	});
}

void BasePropertiesView::createVelocityMax()
{
	QDoubleSpinBox* x = new QDoubleSpinBox;
	QDoubleSpinBox* y = new QDoubleSpinBox;
	QDoubleSpinBox* z = new QDoubleSpinBox;
	x->setObjectName("velocMax_x");
	y->setObjectName("velocMax_y");
	z->setObjectName("velocMax_z");
	velocityMax.push_back(x);
	velocityMax.push_back(y);
	velocityMax.push_back(z);
	addToLayout(velocityMax, FontChina::G2U("最大速度变化"));
	connect(x, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double d){
		if (isInsideOpera)return;
		Vec3 size = target->getParticleVelocityMax();
		target->resetParticleVelocityMax(Vec3(d, size.y, size.z));
	});
	connect(y, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double d){
		if (isInsideOpera)return;
		Vec3 size = target->getParticleVelocityMax();
		target->resetParticleVelocityMax(Vec3(size.x, d, size.z));
	});
	connect(z, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double d){
		if (isInsideOpera)return;
		Vec3 size = target->getParticleVelocityMax();
		target->resetParticleVelocityMax(Vec3(size.x, size.y, d));
	});
}

void BasePropertiesView::createColorMin()
{
	QDoubleSpinBox* x = new QDoubleSpinBox;
	QDoubleSpinBox* y = new QDoubleSpinBox;
	QDoubleSpinBox* z = new QDoubleSpinBox;
	x->setObjectName("colorMin_x");
	y->setObjectName("colorMin_y");
	z->setObjectName("colorMin_z");
	colorMin.push_back(x);
	colorMin.push_back(y);
	colorMin.push_back(z);
	addToLayout(colorMin, FontChina::G2U("最小颜色变化"));
	connect(x, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double d){
		if (isInsideOpera)return;
		Vec3 size = target->getParticleColorMin();
		target->resetParticleColorMin(Vec3(d, size.y, size.z));
	});
	connect(y, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double d){
		if (isInsideOpera)return;
		Vec3 size = target->getParticleColorMin();
		target->resetParticleColorMin(Vec3(size.x, d, size.z));
	});
	connect(z, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double d){
		if (isInsideOpera)return;
		Vec3 size = target->getParticleColorMin();
		target->resetParticleColorMin(Vec3(size.x, size.y, d));
	});
}

void BasePropertiesView::createColorMax()
{
	QDoubleSpinBox* x = new QDoubleSpinBox;
	QDoubleSpinBox* y = new QDoubleSpinBox;
	QDoubleSpinBox* z = new QDoubleSpinBox;
	x->setObjectName("colorMax_x");
	y->setObjectName("colorMax_y");
	z->setObjectName("colorMax_z");
	colorMax.push_back(x);
	colorMax.push_back(y);
	colorMax.push_back(z);
	addToLayout(colorMax, FontChina::G2U("最大颜色变化"));
	connect(x, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double d){
		if (isInsideOpera)return;
		Vec3 size = target->getParticleColorMax();
		target->resetParticleColorMax(Vec3(d, size.y, size.z));
	});
	connect(y, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double d){
		if (isInsideOpera)return;
		Vec3 size = target->getParticleColorMax();
		target->resetParticleColorMax(Vec3(size.x, d, size.z));
	});
	connect(z, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double d){
		if (isInsideOpera)return;
		Vec3 size = target->getParticleColorMax();
		target->resetParticleColorMax(Vec3(size.x, size.y, d));
	});
}

void BasePropertiesView::createColorVelocity()
{
	QDoubleSpinBox* x = new QDoubleSpinBox;
	QDoubleSpinBox* y = new QDoubleSpinBox;
	QDoubleSpinBox* z = new QDoubleSpinBox;
	x->setObjectName("coloVeloc_x");
	y->setObjectName("coloVeloc_y");
	z->setObjectName("coloVeloc_z");
	colorVelocity.push_back(x);
	colorVelocity.push_back(y);
	colorVelocity.push_back(z);
	addToLayout(colorVelocity, FontChina::G2U("颜色变化速度"));
	connect(x, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double d){
		if (isInsideOpera)return;
		Vec3 size = target->getParticleColorVelocity();
		target->resetParticleColorVelocity(Vec3(d, size.y, size.z));
	});
	connect(y, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double d){
		if (isInsideOpera)return;
		Vec3 size = target->getParticleColorVelocity();
		target->resetParticleColorVelocity(Vec3(size.x, d, size.z));
	});
	connect(z, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double d){
		if (isInsideOpera)return;
		Vec3 size = target->getParticleColorVelocity();
		target->resetParticleColorVelocity(Vec3(size.x, size.y, d));
	});
}

void BasePropertiesView::createLife()
{
	QDoubleSpinBox* lifeMin = new QDoubleSpinBox;
	QDoubleSpinBox* lifeMax = new QDoubleSpinBox;
	QDoubleSpinBox* lifeVelocity = new QDoubleSpinBox;
	lifeMin->setObjectName("lifeMin");
	lifeMax->setObjectName("lifeMax");
	lifeVelocity->setObjectName("lifeVeloc");
	life.push_back(lifeMin);
	life.push_back(lifeMax);
	life.push_back(lifeVelocity);
	addToLayout(life, FontChina::G2U("存活属性"));
	connect(lifeMin, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double d){
		if (isInsideOpera)return;
		target->resetParticleLifeMin(d);
	});
	connect(lifeMax, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double d){
		if (isInsideOpera)return;
		target->resetParticleLifeMax(d);
	});
	connect(lifeVelocity, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double d){
		if (isInsideOpera)return;
		target->resetParticleLife_Velocity(d);
	});
}

void BasePropertiesView::resetAccMinValue()
{
	auto x = acclerationMin.at(0);
	auto y = acclerationMin.at(1);
	auto z = acclerationMin.at(2);
	x->setValue(target->getParticleAccelerationMin().x);
	y->setValue(target->getParticleAccelerationMin().y);
	z->setValue(target->getParticleAccelerationMin().z);
}

void BasePropertiesView::resetAccMaxValue()
{
	auto x = acclerationMax.at(0);
	auto y = acclerationMax.at(1);
	auto z = acclerationMax.at(2);
	x->setValue(target->getParticleAccelerationMax().x);
	y->setValue(target->getParticleAccelerationMax().y);
	z->setValue(target->getParticleAccelerationMax().z);
}

void BasePropertiesView::resetSizeMinValue()
{
	auto x = sizeMin.at(0);
	auto y = sizeMin.at(1);
	auto z = sizeMin.at(2);
	x->setValue(target->getParticleSizeMin().x);
	y->setValue(target->getParticleSizeMin().y);
	z->setValue(target->getParticleSizeMin().z);
}

void BasePropertiesView::resetSizeMaxValue()
{
	auto x = sizeMax.at(0);
	auto y = sizeMax.at(1);
	auto z = sizeMax.at(2);
	x->setValue(target->getParticleSizeMax().x);
	y->setValue(target->getParticleSizeMax().y);
	z->setValue(target->getParticleSizeMax().z);
}

void BasePropertiesView::resetSizeVelocValue()
{
	auto x = sizeVelocity.at(0);
	auto y = sizeVelocity.at(1);
	auto z = sizeVelocity.at(2);
	x->setValue(target->getParticleSizeVelocity().x);
	y->setValue(target->getParticleSizeVelocity().y);
	z->setValue(target->getParticleSizeVelocity().z);
}

void BasePropertiesView::resetVelocMinValue()
{
	auto x = velocityMin.at(0);
	auto y = velocityMin.at(1);
	auto z = velocityMin.at(2);
	x->setValue(target->getParticleVelocityMin().x);
	y->setValue(target->getParticleVelocityMin().y);
	z->setValue(target->getParticleVelocityMin().z);
}

void BasePropertiesView::resetVelocMaxValue()
{
	auto x = velocityMax.at(0);
	auto y = velocityMax.at(1);
	auto z = velocityMax.at(2);
	x->setValue(target->getParticleVelocityMax().x);
	y->setValue(target->getParticleVelocityMax().y);
	z->setValue(target->getParticleVelocityMax().z);
}

void BasePropertiesView::resetColorMinValue()
{
	auto x = colorMin.at(0);
	auto y = colorMin.at(1);
	auto z = colorMin.at(2);
	x->setValue(target->getParticleColorMin().x);
	y->setValue(target->getParticleColorMin().y);
	z->setValue(target->getParticleColorMin().z);
}

void BasePropertiesView::resetColorMaxValue()
{
	auto x = colorMax.at(0);
	auto y = colorMax.at(1);
	auto z = colorMax.at(2);
	x->setValue(target->getParticleColorMax().x);
	y->setValue(target->getParticleColorMax().y);
	z->setValue(target->getParticleColorMax().z);
}

void BasePropertiesView::resetColorVelocValue()
{
	auto x = colorVelocity.at(0);
	auto y = colorVelocity.at(1);
	auto z = colorVelocity.at(2);
	x->setValue(target->getParticleColorVelocity().x);
	y->setValue(target->getParticleColorVelocity().y);
	z->setValue(target->getParticleColorVelocity().z);
}

void BasePropertiesView::resetLifeValue()
{
	auto lifeMin = life.at(0);
	auto lifeMax = life.at(1);
	auto lifeVel = life.at(2);
	float min = target->getParticleLifeMin();
	float max = target->getParticleLifeMax();
	float velocity = target->getParticleLife_Velocity();
	lifeMin->setValue(min);
	lifeMax->setValue(max);
	lifeVel->setValue(velocity);
}