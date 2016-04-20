#pragma once
#include "cocos2d.h"
#include "C3DNode.h"
#include "C3DSubMesh.h"

using namespace cocos2d;

struct stMeshHeader
{
	//模型名称
	char m_MeshName[32];
	//自模型数量
	int m_SubMeshCount;
};

struct BaseInfo{
	int MeshCount;
	int frameCount;
	int perFrame;
};

class C3DMesh : public C3DNode
{
public:
	C3DMesh(void);
	~C3DMesh(void);

public:
	//增加子模型
	void AddSubMesh(C3DSubMesh* pSubMesh);
	//删除所有子模型
	void DeleteAllSubMesh();
	//取得子模型数量
	int GetSubMeshCount();
	//取得指定的子模型
	C3DSubMesh* GetSubMesh(int vIndex);
	C3DSubMesh* GetSubMesh(const char* szSubMesh);
	//从文件中读取并创建模型
	bool LoadMeshFromFile(const char* szFileName);
	bool WriteMeshToFile(const char* szFileName);

private:
	std::vector<C3DSubMesh*> m_SubMeshVec;
};

