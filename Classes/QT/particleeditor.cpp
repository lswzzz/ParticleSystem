#include "ParticleEditor.h"
#include "Global.h"
#include "QFileDialog"
#include "FontChina.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <QTextStream>
#include "C3DLayer.h"
#include "C3DParticleSystem.h"

ParticleEditor::ParticleEditor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	g_editor = this;
	setDockWidget();
}

ParticleEditor::~ParticleEditor()
{

}

void ParticleEditor::closeEvent(QCloseEvent* e)
{
	cocos2d::Director::getInstance()->end();
	qApp->quit();
}

void ParticleEditor::setDockWidget()
{
	createResourceView();
	createControlView();
	createModelView();
}

void ParticleEditor::createResourceView()
{
	resourceView = new ResourceView("资源视图", QSize(350, 350));
	g_resourceView = resourceView;
	resourceView->setObjectName("resourceView");
	this->addDockWidget(Qt::LeftDockWidgetArea, resourceView);
}

void ParticleEditor::createControlView()
{
	controlView = new ControlView("属性视图", QSize(350, 650));
	g_controlView = controlView;
	controlView->setObjectName("controlView");
	this->addDockWidget(Qt::RightDockWidgetArea, controlView);
}

void ParticleEditor::createModelView()
{
	modelView = new ModelView("模型视图", QSize(350, 400));
	modelView->setObjectName("modelView");
	this->addDockWidget(Qt::LeftDockWidgetArea, modelView);
}

void ParticleEditor::on_actionAdd_Res_triggered()
{
	QStringList openFiles = QFileDialog::getOpenFileNames(this, FontChina::G2U("添加资源文件"), g_save_Dir, tr("Image Files (*.png *.jpg *.bmp)"));
	if (openFiles.size() > 0){
		g_save_Dir = openFiles.at(0).section("/", 0, -2);
		for (int i = 0; i < openFiles.size(); i++){
			resourceView->addRes(openFiles.at(i));
		}
	}
}

void ParticleEditor::on_actionOpenConfig_triggered()
{
	QString openFile = QFileDialog::getOpenFileName(this, FontChina::G2U("打开一个配置文件"), g_save_Dir, tr("Conf (*.conf)"));
	if (!openFile.isEmpty()){
		fileName = openFile;
		g_save_Dir = fileName.section("/", 0, -2);
		OpenConfigFile(fileName);
	}
}

void ParticleEditor::on_actionSaveConfig_triggered()
{
	if (fileName.isEmpty()){
		fileName = QFileDialog::getSaveFileName(this, FontChina::G2U("保存文件"), g_save_Dir, tr("Conf (*.conf)"));
	}
	if (fileName.isEmpty()){
		return;
	}
	g_save_Dir = fileName.section("/", 0, -2);
	QString file1 = fileName.section(".", -1);
	bool need = false;
	!QString::compare(file1, "Conf", Qt::CaseInsensitive) ? need = false : need = true;
	if (need){fileName += ".Conf";}
	SaveConfigFile(fileName);
}

void ParticleEditor::on_actionSave_as_triggered()
{
	fileName = QFileDialog::getSaveFileName(this, FontChina::G2U("另存为"), g_save_Dir, tr("Conf (*.conf)"));
	if (fileName.isEmpty())
		return;
	on_actionSaveConfig_triggered();
}

void ParticleEditor::on_actionOutput_triggered()
{
	
}

void ParticleEditor::OutputPlist(QString filename)
{

}

void ParticleEditor::SaveConfigFile(QString filename)
{
	FILE* sFile;
	sFile = fopen(filename.toLocal8Bit().data(), "wb");
	if (!sFile){
		addConsoleInfo("保存失败");
		return;
	}
	QVariantMap document;
	QVariantList resList;
	QVariantMap particleData;

	//导出资源
	QStringList imageList = resourceView->getImageList();
	for (int i = 0; i < imageList.size(); i++){
		QVariant res = imageList.at(i);
		resList.append(res);
	}

	//导出粒子
	auto layer = dynamic_cast<C3DLayer*>(g_Layer);
	auto particleSystem = layer->getParticleSystem();
	particleData.insert("texture", particleSystem->getTextureFileName().c_str());
	particleData.insert("count", particleSystem->getParticleCount());
	particleData.insert("particle_type", particleSystem->getParticleType());
	particleData.insert("blendfunc_src", particleSystem->getBlendFunc().src);
	particleData.insert("blendfunc_dst", particleSystem->getBlendFunc().dst);
	auto data = particleSystem->getParticleData();
	particleData.insert("velocity_min_x", data.m_Velocity_Min.x);
	particleData.insert("velocity_min_y", data.m_Velocity_Min.y);
	particleData.insert("velocity_min_z", data.m_Velocity_Min.z);
	particleData.insert("velocity_max_x", data.m_Velocity_Max.x);
	particleData.insert("velocity_max_y", data.m_Velocity_Max.y);
	particleData.insert("velocity_max_z", data.m_Velocity_Max.z);
	particleData.insert("accleration_min_x", data.m_Acceleration_Min.x);
	particleData.insert("accleration_min_y", data.m_Acceleration_Min.y);
	particleData.insert("accleration_min_z", data.m_Acceleration_Min.z);
	particleData.insert("accleration_max_x", data.m_Acceleration_Max.x);
	particleData.insert("accleration_max_y", data.m_Acceleration_Max.y);
	particleData.insert("accleration_max_z", data.m_Acceleration_Max.z);
	particleData.insert("size_min_x", data.m_Size_Min.x);
	particleData.insert("size_min_y", data.m_Size_Min.y);
	particleData.insert("size_min_z", data.m_Size_Min.z);
	particleData.insert("size_max_x", data.m_Size_Max.x);
	particleData.insert("size_max_y", data.m_Size_Max.y);
	particleData.insert("size_max_z", data.m_Size_Max.z);
	particleData.insert("size_velocity_x", data.m_Size_Velocity.x);
	particleData.insert("size_velocity_y", data.m_Size_Velocity.y);
	particleData.insert("size_velocity_z", data.m_Size_Velocity.z);
	particleData.insert("color_min_x", data.m_Color_Min.x);
	particleData.insert("color_min_y", data.m_Color_Min.y);
	particleData.insert("color_min_z", data.m_Color_Min.z);
	particleData.insert("color_max_x", data.m_Color_Max.x);
	particleData.insert("color_max_y", data.m_Color_Max.y);
	particleData.insert("color_max_z", data.m_Color_Max.z);
	particleData.insert("color_velocity_x", data.m_Color_Velocity.x);
	particleData.insert("color_velocity_y", data.m_Color_Velocity.y);
	particleData.insert("color_velocity_z", data.m_Color_Velocity.z);
	particleData.insert("life_min", data.m_Life_Min);
	particleData.insert("life_max", data.m_Life_Max);
	particleData.insert("life_velocity", data.m_Life_Velocity);
	particleData.insert("m_color_r", particleSystem->getColor()[0]);
	particleData.insert("m_color_g", particleSystem->getColor()[1]);
	particleData.insert("m_color_b", particleSystem->getColor()[2]);
	particleData.insert("m_color_a", particleSystem->getColor()[3]);
	document.insert("resList", resList);
	document.insert("particleData", particleData);
	QJsonDocument jsonDocument = QJsonDocument::fromVariant(document);
	QByteArray array = jsonDocument.toJson(QJsonDocument::Compact);
	unsigned int count = array.size();
	const char* data__ = (const char*)array.data();
	fwrite(data__, count, 1, sFile);
	fclose(sFile);
}

void ParticleEditor::OpenConfigFile(QString filename)
{
	QFile sFile(fileName);
	if (sFile.open(QIODevice::ReadOnly | QIODevice::Text)){
		QTextStream in(&sFile);
		QString content = in.readAll();
		QJsonParseError jsonError;
		QJsonDocument document = QJsonDocument::fromJson(content.toLatin1(), &jsonError);
		if (jsonError.error == QJsonParseError::NoError && document.isObject()){
			QJsonObject obj = document.object();
			QJsonArray resList = obj["resList"].toArray();
			QJsonObject particleData = obj["particleData"].toObject();

			resourceView->clearResourceList();
			for (int i = 0; i < resList.size(); i++){
				resourceView->addRes(resList.at(i).toString());
			}

			auto layer = dynamic_cast<C3DLayer*>(g_Layer);
			auto particleSystem = layer->getParticleSystem();
			auto acclerationMin = Vec3(particleData["accleration_min_x"].toDouble(), particleData["accleration_min_y"].toDouble(), particleData["accleration_min_z"].toDouble());
			auto acclerationMax = Vec3(particleData["accleration_max_x"].toDouble(), particleData["accleration_max_y"].toDouble(), particleData["accleration_max_z"].toDouble());
			auto sizeMin = Vec3(particleData["size_min_x"].toDouble(), particleData["size_min_y"].toDouble(), particleData["size_min_z"].toDouble());
			auto sizeMax = Vec3(particleData["size_max_x"].toDouble(), particleData["size_max_y"].toDouble(), particleData["size_max_z"].toDouble());
			auto sizeVelocity = Vec3(particleData["size_velocity_x"].toDouble(), particleData["size_velocity_z"].toDouble(), particleData["size_velocity_z"].toDouble());
			auto velocityMin = Vec3(particleData["velocity_min_x"].toDouble(), particleData["velocity_min_y"].toDouble(), particleData["velocity_min_z"].toDouble());
			auto velocityMax = Vec3(particleData["velocity_max_x"].toDouble(), particleData["velocity_max_y"].toDouble(), particleData["velocity_max_z"].toDouble());
			auto colorMin = Vec3(particleData["color_min_x"].toDouble(), particleData["color_min_y"].toDouble(), particleData["color_min_z"].toDouble());
			auto colorMax = Vec3(particleData["color_max_x"].toDouble(), particleData["color_max_y"].toDouble(), particleData["color_max_z"].toDouble());
			auto colorVelocity = Vec3(particleData["color_velocity_x"].toDouble(), particleData["color_velocity_y"].toDouble(), particleData["color_velocity_z"].toDouble());
			auto life = Vec3(particleData["life_min"].toDouble(), particleData["life_max"].toDouble(), particleData["life_velocity"].toDouble());
			particleSystem->resetParticleAccelerationMin(acclerationMin);
			particleSystem->resetParticleAccelerationMax(acclerationMax);
			particleSystem->resetParticleSizeMin(sizeMin);
			particleSystem->resetParticleSizeMax(sizeMax);
			particleSystem->resetParticleSizeVelocity(sizeVelocity);
			particleSystem->resetParticleVelocityMin(velocityMin); 
			particleSystem->resetParticleVelocityMax(velocityMax);
			particleSystem->resetParticleColorMin(colorMin);
			particleSystem->resetParticleColorMax(colorMax);
			particleSystem->resetParticleColorVelocity(colorVelocity);
			particleSystem->resetParticleLifeMin(life.x);
			particleSystem->resetParticleLifeMax(life.y); 
			particleSystem->resetParticleLife_Velocity(life.z);
			particleSystem->SetTexture(particleData["texture"].toString().toLocal8Bit().data());
			particleSystem->setColor(particleData["m_color_r"].toDouble(), particleData["m_color_g"].toDouble(), particleData["m_color_b"].toDouble(), particleData["m_color_a"].toDouble());
			eParticleType _type;
			switch (particleData["particle_type"].toInt()){
			case 0:
				_type = eParticleType::PT_FIRE;
				break;
			case 1:
				_type = eParticleType::PT_FIREWORK;
				break;
			case 2:
				_type = eParticleType::PT_FOUNTAIN;
				break;
			case 3:
				_type = eParticleType::PT_MAX;
				break;
			}
			layer->resetParticle(particleData["count"].toInt(), _type, { particleData["blendfunc_src"].toInt(), particleData["blendfunc_dst"].toInt() });
			controlView->setTarget(particleSystem);
			controlView->setParticleType(_type);
		}
		else{
			addConsoleInfo("文件错误");
		}
	}
	else{
		addConsoleInfo("读取文件错误");
	}
}

void ParticleEditor::setDockWidgetVisible(QDockWidget* widget, QString objName)
{
	if (widget->isVisible()){
		widget->setVisible(false);
		QList<QAction*> list = ui.menuView->actions();
		for (int i = 0; i < list.size(); i++){
			auto action = list.at(i);
			if (action->objectName() == objName){
				action->setIcon(QIcon(":/icon/Resources/hide.ico"));
			}
		}
	}
	else{
		widget->setVisible(true);
		QList<QAction*> list = ui.menuView->actions();
		for (int i = 0; i < list.size(); i++){
			auto action = list.at(i);
			if (action->objectName() == objName){
				action->setIcon(QIcon(":/icon/Resources/show.ico"));
			}
		}
	}
}

void ParticleEditor::on_actionControlView_triggered()
{
	setDockWidgetVisible(controlView, "controlView");
}

void ParticleEditor::on_actionResView_triggered()
{
	setDockWidgetVisible(resourceView, "resourceView");
}

void ParticleEditor::on_actionModelView_triggered()
{
	setDockWidgetVisible(modelView, "modelView");
}