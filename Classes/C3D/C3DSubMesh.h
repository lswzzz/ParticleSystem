#pragma once
#include "cocos2d.h"
#include "C3DShape.h"
#include "C3DShape.h"

USING_NS_CC;

struct stSubMeshHeader
{
	//ģ������
	char m_SubMeshName[32];
	//��ͼ�ļ�
	char m_Texture[32];
	//��������
	unsigned int m_VertexCount;
	//��������
	unsigned int m_IndexCount;
	//ͼ����Ⱦ��ʽ
	PrimitiveType m_PrimitiveType;
	IndexFormat m_IndexFormat;
};

struct frameData
{
	stSubMeshHeader* tHeader;
	stShapeVertices* tVeetices;
	GLushort* tIndice;
	Mat4* tSubMatrix;
};

class C3DSubMesh : public C3DShape
{
public:
	C3DSubMesh(void);
	~C3DSubMesh(void);

public:
	//���ļ��ж�ȡ������ģ��
	bool LoadMeshFromFile(FILE* pFile);
	//��ģ�ͱ��浽�ļ���
	bool WriteMeshToFile(FILE* pFile);
	void loadFrameAtIndex(int index);
	virtual void	Render();
	virtual void	Release();
	int FrameCount;
	int PerFrame;
	long preTime;
	long currTime;
	int frameIndex;
	std::vector<frameData> frame;
};

