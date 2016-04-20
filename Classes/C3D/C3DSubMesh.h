#pragma once
#include "cocos2d.h"
#include "C3DShape.h"
#include "C3DShape.h"

USING_NS_CC;

struct stSubMeshHeader
{
	//模型名称
	char m_SubMeshName[32];
	//贴图文件
	char m_Texture[32];
	//顶点数量
	unsigned int m_VertexCount;
	//索引数量
	unsigned int m_IndexCount;
	//图形渲染方式
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
	//从文件中读取并创建模型
	bool LoadMeshFromFile(FILE* pFile);
	//将模型保存到文件中
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

