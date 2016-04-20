#include "ResourceView.h"
#include "QLayout"
#include "FontChina.h"
#include "QLabel"
#include "QMenu"
#include "Global.h"

ResourceView::ResourceView(char* title, QSize size)
:BaseDockWidget(title, size)
{
	target = NULL;
	QGridLayout* glayout = new QGridLayout;
	glayout->addWidget(new QLabel(FontChina::G2U("显示模式")), 0, 0, 1, 1);
	showMode = new QComboBox();
	showMode->addItem(FontChina::G2U("文字模式"));
	showMode->addItem(FontChina::G2U("图标模式"));
	glayout->addWidget(showMode, 0, 1, 1, 1);
	glayout->addWidget(new QLabel, 0, 2, 1, 1);
	glayout->setColumnStretch(2, 10);
	listWidget = new QListWidget;
	glayout->addWidget(listWidget, 1, 0, 1, 3);
	widget->setLayout(glayout);
	this->setFeatures(QDockWidget::NoDockWidgetFeatures);
	connect(showMode, SIGNAL(currentIndexChanged(int)), this, SLOT(setResShowMode(int)));
}

ResourceView::~ResourceView()
{
}

void ResourceView::setResShowMode(int mode)
{
	switch (mode){
	case 0:
		listWidget->setViewMode(QListView::ListMode);
		listWidget->setIconSize(QSize(-1, -1));
		for (int i = 0; i < listWidget->count(); i++){
			auto item = listWidget->item(i);
			item->setText(item->data(Qt::UserRole).toString().section("/", -1));
		}
		break;
	case 1:
		listWidget->setViewMode(QListView::IconMode);
		listWidget->setIconSize(QSize(50, 50));
		for (int i = 0; i < listWidget->count(); i++){
			auto item = listWidget->item(i);
			item->setText("");
		}
		break;
	}
}

void ResourceView::contextMenuEvent(QContextMenuEvent *event)
{
	if (!listWidget->hasFocus())return;
	QMenu* ResMenu = new QMenu(this);
	QAction* setTexture = new QAction(FontChina::G2U("设置为粒子纹理"), this);
	QAction* deleteac = new QAction(FontChina::G2U("删除"), this);
	connect(setTexture, SIGNAL(triggered()), this, SLOT(action_setTexture()));
	connect(deleteac, SIGNAL(triggered()), this, SLOT(action_delete_Res()));
	ResMenu->addAction(deleteac);
	ResMenu->addAction(setTexture);
	ResMenu->exec(QCursor::pos());
}

void ResourceView::action_delete_Res()
{
	auto* item = listWidget->currentItem();
	QModelIndex index = listWidget->currentIndex();
	if (item){
		listWidget->takeItem(index.row());
		addConsoleInfo("删除成功");
	}
}

void ResourceView::action_setTexture()
{
	auto* item = listWidget->currentItem();
	QString str = item->data(Qt::UserRole).toString();
	target->SetTexture(str.toLocal8Bit().data());
}

void ResourceView::addRes(QString image)
{
	QListWidgetItem* item = new QListWidgetItem;
	item->setIcon(QIcon(image));
	item->setData(Qt::UserRole, image);
	if (getModel()){
		item->setText("");
	}
	else{
		item->setText(image.section("/", -1));
	}
	listWidget->addItem(item);
}

bool ResourceView::getModel()
{
	if (listWidget->iconSize() == QSize(50, 50)){
		return true;
	};
	return false;
}

void ResourceView::setTarget(C3DShape* shape)
{
	target = shape;
}

QStringList ResourceView::getImageList()
{
	QStringList list;
	for (int i = 0; i < listWidget->count(); i++){
		auto item = listWidget->item(i);
		list << item->data(Qt::UserRole).toString();
	}
	return list;
}

void ResourceView::clearResourceList()
{
	for (int i = 0; i < listWidget->count(); i++){
		auto item = listWidget->item(0);
		delete item;
	}
}