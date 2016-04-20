#pragma once
#include "BaseDockWidget.h"
#include "QComboBox"
#include "QPushButton"
#include "C3DShape.h"

class BlendFuncView : public BaseDockWidget
{
	Q_OBJECT
public:
	BlendFuncView(char* title, QSize size);
	~BlendFuncView();
	void setTarget(C3DShape* tar);
private slots:
	void on_disable_clicked();
	void on_fremultiplied_clicked();
	void on_nonfremultiplied_clicked();
	void on_additive_clicked();
	void src_change(int index);
	void dst_change(int index);
protected:
	void _connect();
	void createSrcItem();
	void createDstItem();
	void setValueFromTarget();
private:
	QComboBox* src;
	QComboBox* dst;
	QPushButton* DISABLE;
	QPushButton* ALPHA_PREMULTIPLIED;
	QPushButton* ALPHA_NON_PREMULTIPLIED;
	QPushButton* ADDITIVE;
	C3DShape* target;
	bool isInsideOpera;
	enum Blend_Type{
		_GL_ZERO,
		_GL_ONE,
		_GL_SRC_COLOR,
		_GL_ONE_MINUS_SRC_COLOR,
		_GL_SRC_ALPHA,
		_GL_ONE_MINUS_SRC_ALPHA,
		_GL_DST_COLOR,
		_GL_ONE_MINUS_DST_COLOR,
		_GL_DST_ALPHA,
		_GL_ONE_MINUS_DST_ALPHA,
		_GL_SRC_ALPHA_SATURATE,
	};
};

