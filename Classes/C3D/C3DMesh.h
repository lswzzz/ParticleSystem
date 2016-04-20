#pragma once
#include "cocos2d.h"
#include "C3DNode.h"
#include "C3DSubMesh.h"

using namespace cocos2d;

struct stMeshHeader
{
	//ģ������
	char m_MeshName[32];
	//��ģ������
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
	//������ģ��
	void AddSubMesh(C3DSubMesh* pSubMesh);
	//ɾ��������ģ��
	void DeleteAllSubMesh();
	//ȡ����ģ������
	int GetSubMeshCount();
	//ȡ��ָ������ģ��
	C3DSubMesh* GetSubMesh(int vIndex);
	C3DSubMesh* GetSubMesh(const char* szSubMesh);
	//���ļ��ж�ȡ������ģ��
	bool LoadMeshFromFile(const char* szFileName);
	bool WriteMeshToFile(const char* szFileName);

private:
	std::vector<C3DSubMesh*> m_SubMeshVec;
};

