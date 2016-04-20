#include "C3DMesh.h"


C3DMesh::C3DMesh(void)
{
}


C3DMesh::~C3DMesh(void)
{
	DeleteAllSubMesh();
}

void C3DMesh::AddSubMesh(C3DSubMesh* pSubMesh)
{
	m_SubMeshVec.push_back(pSubMesh);
	AddChild(pSubMesh);
}

//删除所有子模型
void C3DMesh::DeleteAllSubMesh()
{
	std::vector<C3DSubMesh*>::iterator tIter;
	for(tIter=m_SubMeshVec.begin(); tIter!=m_SubMeshVec.end();tIter++){
		delete (*tIter);
		DelNode(*tIter);
	}
	m_SubMeshVec.clear();
}

//取得子模型数量
int C3DMesh::GetSubMeshCount()
{
	return m_SubMeshVec.size();
}

//取得指定的子模型
C3DSubMesh* C3DMesh::GetSubMesh(int vIndex)
{
	return m_SubMeshVec[vIndex];
}

C3DSubMesh* C3DMesh::GetSubMesh(const char* szSubMesh)
{
	std::vector<C3DSubMesh*>::iterator tIter;
	for(tIter=m_SubMeshVec.begin();tIter!=m_SubMeshVec.end();tIter++){
		if(0 == strcmp((*tIter)->GetName(), szSubMesh)){
			return (*tIter);
		}
	}
	return NULL;
}

//从文件中读取并创建模型
bool C3DMesh::LoadMeshFromFile(const char* szFileName)
{
	DeleteAllSubMesh();
	FILE* pFile = fopen(szFileName, "rb");
	if(pFile){
		BaseInfo info;
		//int count = 0;
		fread(&info, sizeof(BaseInfo), 1, pFile);
		//fread(&count, sizeof(int), 1, pFile);
		for(int j=0; j<info.MeshCount; j++){
			stMeshHeader tHeader;
			fread(&tHeader, sizeof(stMeshHeader), 1, pFile);
			log("%s", tHeader.m_MeshName);
			//log("model count%d", tHeader.m_SubMeshCount);
			for(int i=0; i<tHeader.m_SubMeshCount; i++){
				C3DSubMesh* pSubMesh = new C3DSubMesh();
				pSubMesh->FrameCount = info.frameCount;
				pSubMesh->PerFrame = info.perFrame;
				if(false == pSubMesh->LoadMeshFromFile(pFile)){
					return false;
				}
				AddSubMesh(pSubMesh);
			}
		}
		fclose(pFile);
		return true;
	}
	return false;
}

bool C3DMesh::WriteMeshToFile(const char* szFileName)
{
	FILE* pFile = fopen(szFileName, "wb");
	if(pFile){
		stMeshHeader tHeader;
		strcpy(tHeader.m_MeshName, GetName());

		tHeader.m_SubMeshCount = m_SubMeshVec.size();
		fwrite(&tHeader, sizeof(stMeshHeader), 1, pFile);

		std::vector<C3DSubMesh*>::iterator tIter;
		for(tIter=m_SubMeshVec.begin();tIter!=m_SubMeshVec.end();tIter++){
			(*tIter)->WriteMeshToFile(pFile);
		}
		fclose(pFile);
		return true;
	}
	return false;
}
