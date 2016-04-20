#include "BlendFuncView.h"
#include "QLayout"
#include "FontChina.h"
#include "QLabel"

BlendFuncView::BlendFuncView(char* title, QSize size)
	:BaseDockWidget(title, size, true)
{
	target = NULL;
	isInsideOpera = false;
	QGridLayout* layout = new QGridLayout;
	DISABLE = new QPushButton(FontChina::G2U("DISABLE"));
	ALPHA_PREMULTIPLIED = new QPushButton(FontChina::G2U("ALPHA_PREMULTIPLIED"));
	ALPHA_NON_PREMULTIPLIED = new QPushButton(FontChina::G2U("ALPHA_NON_PREMULTIPLIED"));
	ADDITIVE = new QPushButton(FontChina::G2U("ADDITIVE"));
	src = new QComboBox;
	dst = new QComboBox;
	layout->addWidget(DISABLE, 0, 0, 1, 1);
	layout->addWidget(ALPHA_PREMULTIPLIED, 0, 1, 1, 1);
	layout->addWidget(ADDITIVE, 1, 0, 1, 1);
	layout->addWidget(ALPHA_NON_PREMULTIPLIED, 1, 1, 1, 1);
	layout->addWidget(new QLabel("Src"), 2, 0, 1, 1);
	layout->addWidget(src, 2, 1, 1, 1);
	layout->addWidget(new QLabel("Dst"), 3, 0, 1, 1);
	layout->addWidget(dst, 3, 1, 1, 1);
	layout->setColumnStretch(0, 1);
	layout->setColumnStretch(1, 2);
	widget->setLayout(layout);
	createSrcItem();
	createDstItem();
	_connect();
}


BlendFuncView::~BlendFuncView()
{
}

void BlendFuncView::setTarget(C3DShape* tar)
{
	target = tar;
	isInsideOpera = true;
	setValueFromTarget();
	isInsideOpera = false;
}

void BlendFuncView::setValueFromTarget()
{
	switch (target->getBlendFunc().src){
	case GL_ZERO:
		src->setCurrentIndex(_GL_ZERO);
		break;
	case GL_ONE:
		src->setCurrentIndex(_GL_ONE);
		break;
	case GL_SRC_COLOR:
		src->setCurrentIndex(_GL_SRC_COLOR);
		break;
	case GL_ONE_MINUS_SRC_COLOR:
		src->setCurrentIndex(_GL_ONE_MINUS_SRC_COLOR);
		break;
	case GL_SRC_ALPHA:
		src->setCurrentIndex(_GL_SRC_ALPHA);
		break;
	case GL_ONE_MINUS_SRC_ALPHA:
		src->setCurrentIndex(_GL_ONE_MINUS_SRC_ALPHA);
		break;
	case GL_DST_COLOR:
		src->setCurrentIndex(_GL_DST_COLOR);
		break;
	case GL_ONE_MINUS_DST_COLOR:
		src->setCurrentIndex(_GL_ONE_MINUS_DST_COLOR);
		break;
	case GL_DST_ALPHA:
		src->setCurrentIndex(_GL_DST_ALPHA);
		break;
	case GL_ONE_MINUS_DST_ALPHA:
		src->setCurrentIndex(_GL_ONE_MINUS_DST_ALPHA);
		break;
	case GL_SRC_ALPHA_SATURATE:
		src->setCurrentIndex(_GL_SRC_ALPHA_SATURATE);
		break;
	}
	switch (target->getBlendFunc().dst){
	case GL_ZERO:
		dst->setCurrentIndex(_GL_ZERO);
		break;
	case GL_ONE:
		dst->setCurrentIndex(_GL_ONE);
		break;
	case GL_SRC_COLOR:
		dst->setCurrentIndex(_GL_SRC_COLOR);
		break;
	case GL_ONE_MINUS_SRC_COLOR:
		dst->setCurrentIndex(_GL_ONE_MINUS_SRC_COLOR);
		break;
	case GL_SRC_ALPHA:
		dst->setCurrentIndex(_GL_SRC_ALPHA);
		break;
	case GL_ONE_MINUS_SRC_ALPHA:
		dst->setCurrentIndex(_GL_ONE_MINUS_SRC_ALPHA);
		break;
	case GL_DST_COLOR:
		dst->setCurrentIndex(_GL_DST_COLOR);
		break;
	case GL_ONE_MINUS_DST_COLOR:
		dst->setCurrentIndex(_GL_ONE_MINUS_DST_COLOR);
		break;
	case GL_DST_ALPHA:
		dst->setCurrentIndex(_GL_DST_ALPHA);
		break;
	case GL_ONE_MINUS_DST_ALPHA:
		dst->setCurrentIndex(_GL_ONE_MINUS_DST_ALPHA);
		break;
	case GL_SRC_ALPHA_SATURATE:
		dst->setCurrentIndex(_GL_SRC_ALPHA_SATURATE);
		break;
	}
}

void BlendFuncView::_connect()
{
	connect(DISABLE, SIGNAL(clicked()), this, SLOT(on_disable_clicked()));
	connect(ALPHA_PREMULTIPLIED, SIGNAL(clicked()), this, SLOT(on_fremultiplied_clicked()));
	connect(ALPHA_NON_PREMULTIPLIED, SIGNAL(clicked()), this, SLOT(on_nonfremultiplied_clicked()));
	connect(ADDITIVE, SIGNAL(clicked()), this, SLOT(on_additive_clicked()));
	connect(src, SIGNAL(currentIndexChanged(int)), this, SLOT(src_change(int)));
	connect(dst, SIGNAL(currentIndexChanged(int)), this, SLOT(dst_change(int)));
}

void BlendFuncView::on_disable_clicked()
{
	target->setBlendFunc(BlendFunc::DISABLE);
	isInsideOpera = true;
	src_change(_GL_ONE);
	dst_change(_GL_ZERO);
	isInsideOpera = false;
}

void BlendFuncView::on_fremultiplied_clicked()
{
	target->setBlendFunc(BlendFunc::ALPHA_PREMULTIPLIED);
	isInsideOpera = true;
	src_change(_GL_ONE);
	dst_change(_GL_ONE_MINUS_SRC_ALPHA);
	isInsideOpera = false;
}

void BlendFuncView::on_nonfremultiplied_clicked()
{
	target->setBlendFunc(BlendFunc::ALPHA_NON_PREMULTIPLIED);
	isInsideOpera = true;
	src_change(_GL_SRC_ALPHA);
	dst_change(_GL_ONE_MINUS_SRC_ALPHA);
	isInsideOpera = false;
}

void BlendFuncView::on_additive_clicked()
{
	target->setBlendFunc(BlendFunc::ADDITIVE);
	isInsideOpera = true;
	src_change(_GL_SRC_ALPHA);
	dst_change(_GL_ONE);
	isInsideOpera = false;
}

void BlendFuncView::src_change(int index)
{
	if (isInsideOpera)return;
	switch (index){
	case _GL_ZERO:
		target->setBlendFunc({ GL_ZERO, target->getBlendFunc().dst });
		break;
	case _GL_ONE:
		target->setBlendFunc({ GL_ONE, target->getBlendFunc().dst });
		break;
	case _GL_SRC_COLOR:
		target->setBlendFunc({ GL_SRC_COLOR, target->getBlendFunc().dst });
		break;
	case _GL_ONE_MINUS_SRC_COLOR:
		target->setBlendFunc({ GL_ONE_MINUS_SRC_COLOR, target->getBlendFunc().dst });
		break;
	case _GL_SRC_ALPHA:
		target->setBlendFunc({ GL_SRC_ALPHA, target->getBlendFunc().dst });
		break;
	case _GL_ONE_MINUS_SRC_ALPHA:
		target->setBlendFunc({ GL_ONE_MINUS_SRC_ALPHA, target->getBlendFunc().dst });
		break;
	case _GL_DST_COLOR:
		target->setBlendFunc({ GL_DST_COLOR, target->getBlendFunc().dst });
		break;
	case _GL_ONE_MINUS_DST_COLOR:
		target->setBlendFunc({ GL_ONE_MINUS_DST_COLOR, target->getBlendFunc().dst });
		break;
	case _GL_DST_ALPHA:
		target->setBlendFunc({ GL_DST_ALPHA, target->getBlendFunc().dst });
		break;
	case _GL_ONE_MINUS_DST_ALPHA:
		target->setBlendFunc({ GL_ONE_MINUS_DST_ALPHA, target->getBlendFunc().dst });
		break;
	case _GL_SRC_ALPHA_SATURATE:
		target->setBlendFunc({ GL_SRC_ALPHA_SATURATE, target->getBlendFunc().dst });
		break;
	}
}

void BlendFuncView::dst_change(int index)
{
	if (isInsideOpera)return;
	switch (index){
	case _GL_ZERO:
		target->setBlendFunc({ target->getBlendFunc().src, GL_ZERO});
		break;
	case _GL_ONE:
		target->setBlendFunc({ target->getBlendFunc().src, GL_ONE });
		break;
	case _GL_SRC_COLOR:
		target->setBlendFunc({ target->getBlendFunc().src, GL_SRC_COLOR });
		break;
	case _GL_ONE_MINUS_SRC_COLOR:
		target->setBlendFunc({ target->getBlendFunc().src, GL_ONE_MINUS_SRC_COLOR });
		break;
	case _GL_SRC_ALPHA:
		target->setBlendFunc({ target->getBlendFunc().src, GL_SRC_ALPHA });
		break;
	case _GL_ONE_MINUS_SRC_ALPHA:
		target->setBlendFunc({ target->getBlendFunc().src, GL_ONE_MINUS_SRC_ALPHA });
		break;
	case _GL_DST_COLOR:
		target->setBlendFunc({ target->getBlendFunc().src, GL_DST_COLOR });
		break;
	case _GL_ONE_MINUS_DST_COLOR:
		target->setBlendFunc({ target->getBlendFunc().src, GL_ONE_MINUS_DST_COLOR });
		break;
	case _GL_DST_ALPHA:
		target->setBlendFunc({ target->getBlendFunc().src, GL_DST_ALPHA });
		break;
	case _GL_ONE_MINUS_DST_ALPHA:
		target->setBlendFunc({ target->getBlendFunc().src, GL_ONE_MINUS_DST_ALPHA });
		break;
	case _GL_SRC_ALPHA_SATURATE:
		target->setBlendFunc({ target->getBlendFunc().src, GL_SRC_ALPHA_SATURATE });
		break;
	}
}

void BlendFuncView::createSrcItem()
{
	src->addItem("GL_ZERO");
	src->addItem("GL_ONE");
	src->addItem("GL_SRC_COLOR");
	src->addItem("GL_ONE_MINUS_SRC_COLOR");
	src->addItem("GL_SRC_ALPHA");
	src->addItem("GL_ONE_MINUS_SRC_ALPHA");
	src->addItem("GL_DST_COLOR");
	src->addItem("GL_ONE_MINUS_DST_COLOR");
	src->addItem("GL_DST_ALPHA");
	src->addItem("GL_ONE_MINUS_DST_ALPHA");
	src->addItem("GL_SRC_ALPHA_SATURATE");
}

void BlendFuncView::createDstItem()
{
	dst->addItem("GL_ZERO");
	dst->addItem("GL_ONE");
	dst->addItem("GL_SRC_COLOR");
	dst->addItem("GL_ONE_MINUS_SRC_COLOR");
	dst->addItem("GL_SRC_ALPHA");
	dst->addItem("GL_ONE_MINUS_SRC_ALPHA");
	dst->addItem("GL_DST_COLOR");
	dst->addItem("GL_ONE_MINUS_DST_COLOR");
	dst->addItem("GL_DST_ALPHA");
	dst->addItem("GL_ONE_MINUS_DST_ALPHA");
	dst->addItem("GL_SRC_ALPHA_SATURATE");
}