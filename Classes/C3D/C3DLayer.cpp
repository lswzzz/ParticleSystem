#include "C3DLayer.h"
#include "Global.h"
#include "ControlView.h"
#include "ResourceView.h"

C3DLayer::C3DLayer(void)
{
	m_pParticleSystem = NULL;
	shape = NULL;
	m_pCamera = NULL;
}


C3DLayer::~C3DLayer(void)
{
}

bool C3DLayer::init()
{
	addTouchEvent();
	m_pParticleSystem = new C3DParticleSystem();
	m_pParticleSystem->InitPS_FireWork(200);
	m_pParticleSystem->SetTexture("circle.png");
	/*shape = new C3DShape();
	shape->CreateSphere();
	shape->SetTexture("fire.png");
	shape->SetScale(0.5, 0.5, 0.5);*/
	//shape->AddChild(m_pParticleSystem);
	auto controlView = dynamic_cast<ControlView*>(g_controlView);
	controlView->setTarget(m_pParticleSystem);
	controlView->setParticleType(m_pParticleSystem->getParticleType());
	auto resourceView = dynamic_cast<ResourceView*>(g_resourceView);
	resourceView->setTarget(m_pParticleSystem);
	m_pCamera = new C3DCamera();
	kmVec3 tEyeResult = kmVec3(0, 0, 0);
	kmVec3 tLookAtResult = kmVec3(0, 0, 0);
	kmVec3 tUpResult = kmVec3(0, 1, 0);
	m_pCamera->SetEyePosition(tEyeResult);
	m_pCamera->SetLookAtTarget(m_pParticleSystem);
	m_pCamera->SetUpDir(tUpResult);
	m_pCamera->SetActive();
	m_pCamera->SetTranslate_Parent(0, 0, -200);
	m_pParticleSystem->AddChild(m_pCamera);

	m_fRotateYAngle = 0;
	Director::getInstance()->setDepthTest(true);
	return true;
}

bool C3DLayer::resetParticle(int totalSize, eParticleType _type, BlendFunc func)
{
	m_pParticleSystem->reset(totalSize, _type, func);
	return true;
}

void C3DLayer::draw(Renderer* renderer, const Mat4& transform, uint32_t flags)
{
	kmGLMatrixMode(KM_GL_PROJECTION);
	kmGLPushMatrix();
	kmGLMatrixMode(KM_GL_MODELVIEW);
	kmGLPushMatrix();

	UpdateViewProjMatrix();

	Render3DWorld();

	kmGLMatrixMode(KM_GL_PROJECTION);
	kmGLPopMatrix();
	kmGLMatrixMode(KM_GL_MODELVIEW);
	kmGLPopMatrix();
}

void C3DLayer::UpdateViewProjMatrix()
{
	Vec3 tEyeResult = Vec3(0,0,2);
	Vec3 tLookAtResult = Vec3(0, 0, 0);
	Vec3 tUpResult = Vec3(0, 1, 0);
	Mat4 tViewMatrix;
	kmMat4LookAt(&tViewMatrix, &tEyeResult, &tLookAtResult, &tUpResult);

	kmGLMatrixMode(KM_GL_MODELVIEW);
	kmGLLoadIdentity();
	//tViewMatrix.scale(0.01);
	//static float rotation = 0;
	//tViewMatrix.rotate(Vec3(0.5, 0.5, 0.5), CC_DEGREES_TO_RADIANS(rotation));
	/*rotation++;
	if (rotation >= 360){
		rotation = 0;
	}*/
	kmGLMultMatrix(&tViewMatrix);
	kmMat4 matrixPerspective;
	kmGLMatrixMode(KM_GL_PROJECTION);
	kmGLLoadIdentity();
	Size size = Director::getInstance()->getVisibleSize();
	kmMat4PerspectiveProjection(&matrixPerspective, 60, (GLfloat)size.width/size.height, 0.1f, 500.0f);
	kmGLMultMatrix(&matrixPerspective);

	if(m_pCamera)m_pCamera->UpdateViewMatrix();
}

void C3DLayer::Render3DWorld()
{
	if (m_pParticleSystem){
		m_pParticleSystem->Update();
		m_pParticleSystem->Render();
	}
	if (shape){
		shape->SetRotate(0, 1, 0, m_fRotateYAngle);
		shape->Render();
	}
	m_fRotateYAngle += 0.01;
}

void C3DLayer::addTouchEvent()
{
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(C3DLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(C3DLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(C3DLayer::onTouchEnded, this);
	dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool C3DLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point pos = touch->getLocation();
	pos.x = (pos.x - visibleSize.width / 2) / visibleSize.width / 2;
	pos.y = (pos.y - visibleSize.height / 2) / visibleSize.height / 2;
	if (m_pParticleSystem){
		Vec3 point = Vec3(pos.x*m_pCamera->GetTranslate_Parent().z*3, pos.y*-m_pCamera->GetTranslate_Parent().z*3, 0);
		m_pParticleSystem->resetParticleInitPos(point);
		m_pParticleSystem->addPS(0);
	}
	return true;
}

void C3DLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
}

void C3DLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
}