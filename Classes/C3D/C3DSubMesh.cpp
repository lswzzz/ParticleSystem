#include "C3DSubMesh.h"
#include <stdio.h>

C3DSubMesh::C3DSubMesh(void)
{
	this->FrameCount = 0;
}


C3DSubMesh::~C3DSubMesh(void)
{

}

void C3DSubMesh::loadFrameAtIndex(int index)
{
	stSubMeshHeader tHeader;
	frameData fd = frame.at(index);
	tHeader = *fd.tHeader;
	m_VertexCount = tHeader.m_VertexCount;
	m_IndexCount = tHeader.m_IndexCount;
	m_PrimitiveType = tHeader.m_PrimitiveType;
	m_IndexFormat = tHeader.m_IndexFormat;
	m_VertexArray = fd.tVeetices;
	m_IndiceArray = fd.tIndice;
	Mat4 tSubMatrix = *fd.tSubMatrix;
	tSubMatrix.decompose(&m_Scale_Self, &m_Rotate_Self, &m_Translate_Self);
}

bool C3DSubMesh::LoadMeshFromFile(FILE* pFile)
{
	Release();
	
	if(pFile){
		frame.clear();
		for(int i=0; i<this->FrameCount; i++)
		{
			stSubMeshHeader* tHeader = new stSubMeshHeader;
			fread(tHeader, sizeof(stSubMeshHeader), 1, pFile);
			//log("%s %s", tHeader->m_SubMeshName, tHeader->m_Texture);
			//frame.push_back(tHeader);
			stShapeVertices* tVeetices = new stShapeVertices[tHeader->m_VertexCount];
			fread(tVeetices, sizeof(stShapeVertices), tHeader->m_VertexCount, pFile);
			GLushort* tIndice = new GLushort[tHeader->m_IndexCount];
			fread(tIndice, sizeof(GLushort), tHeader->m_IndexCount, pFile);
			Mat4* tSubMatrix = new Mat4;
			fread(tSubMatrix, sizeof(Mat4), 1, pFile);
			frameData fd;
			fd.tHeader = tHeader;
			fd.tVeetices = tVeetices;
			fd.tIndice = tIndice;
			fd.tSubMatrix = tSubMatrix;
			frame.push_back(fd);
		}
		frameIndex = 0;
		frameData fd = frame.at(frameIndex);
		stSubMeshHeader tHeader = *fd.tHeader;
		SetName(tHeader.m_SubMeshName);
		//CreateSphere();
		log("frameCount:%d perframe:%d", FrameCount, PerFrame);
		log("%s %s", tHeader.m_SubMeshName, tHeader.m_Texture);
		SetTexture(tHeader.m_Texture);
		m_VertexCount = tHeader.m_VertexCount;
		m_IndexCount = tHeader.m_IndexCount;
		m_PrimitiveType = tHeader.m_PrimitiveType;
		m_IndexFormat = tHeader.m_IndexFormat;
		/*log("%s %s %d %d %d %d", tHeader.m_MeshName, tHeader.m_Texture,  tHeader.m_VertexCount, tHeader.m_IndexCount, tHeader.m_PrimitiveType, tHeader.m_IndexFormat);*/
		//�����������������鲢��ȡ����
		m_VertexArray = fd.tVeetices;
		//fread(m_VertexArray, sizeof(stShapeVertices), m_VertexCount, pFile);
		/*for(int i=0; i<m_VertexCount; i++){
			log("%.f %.f %.f", m_VertexArray[i].Position.x, m_VertexArray[i].Position.y, m_VertexArray[i].Position.z);
		}*/
		m_IndiceArray = fd.tIndice;//new GLushort[m_IndexCount];
		//fread(m_IndiceArray, sizeof(GLushort), m_IndexCount, pFile);
		

		//��ȡ��ͨ��ʽ������ģ��
		////����������ĵ��λ��ƫ��
		//fread(&m_Translate_Self, sizeof(Vec3), 1, pFile);
		////����������ĵ������
		//fread(&m_Scale_Self, sizeof(Vec3), 1, pFile);
		////�������ĵ����ת
		//fread(&m_Rotate_Self, sizeof(Quaternion), 1, pFile);
		////��Ը��ڵ��λ��ƫ��
		//fread(&m_Translate_Parent, sizeof(Vec3), 1, pFile);
		////��Ը��ڵ������
		//fread(&m_Scale_Parent, sizeof(Vec3), 1, pFile);
		////��Ը��ڵ����ת
		//fread(&m_Rotate_Parent, sizeof(Quaternion), 1, pFile);

		//��ȡ3dmax������ģ��
		Mat4 tSubMatrix = *fd.tSubMatrix;
		//fread(&tSubMatrix, sizeof(Mat4), 1, pFile);
		tSubMatrix.decompose(&m_Scale_Self, &m_Rotate_Self, &m_Translate_Self);
		//log("%f %f %f", m_Translate_Self.x, m_Translate_Self.y, m_Translate_Self.z);
		m_Translate_Parent = Vec3(0, 0, 0);
		m_Scale_Parent = Vec3(1, 1, 1);
		m_Rotate_Parent.identity();


		////����VB��IB
		glGenBuffers(1, &m_VertexBuffer);
		glGenBuffers(1, &m_IndexBuffer);

		glBindBuffer(GL_ARRAY_BUFFER_ARB, m_VertexBuffer);
		glBufferData(GL_ARRAY_BUFFER_ARB,
			m_VertexCount * sizeof(stShapeVertices),
			m_VertexArray,
			GL_STATIC_DRAW);

		//�����ݵ�IB�С�
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB, m_IndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER_ARB, m_IndexCount*sizeof(GLushort), m_IndiceArray, GL_STATIC_DRAW);

		BuildShader();
		struct timeval tv;
		gettimeofday(&tv, nullptr);
		preTime = tv.tv_sec * 1000 + tv.tv_usec / 1000;
        return true;

	}
	return false;
}

void C3DSubMesh::Render()
{
	struct timeval tv;
	gettimeofday(&tv, nullptr);
	currTime = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if(currTime - preTime >= PerFrame){
		preTime = currTime;
		if(frame.size() == 1){
			C3DShape::Render();
			return;
		}
		frameIndex++;
		if(frameIndex >= frame.size()){
			frameIndex = 0;
		}
		loadFrameAtIndex(frameIndex);
	}
	C3DShape::Render();
}

bool C3DSubMesh::WriteMeshToFile(FILE* pFile)
{
	if(pFile){
		stSubMeshHeader tHeader;
		strcpy(tHeader.m_SubMeshName, GetName());
		strcpy(tHeader.m_Texture, m_TextureFileName.c_str());
		log("%s", tHeader.m_Texture);
		tHeader.m_VertexCount = m_VertexCount;
		tHeader.m_IndexCount = m_IndexCount;
		tHeader.m_PrimitiveType = m_PrimitiveType;
		tHeader.m_IndexFormat = m_IndexFormat;
		fwrite(&tHeader, sizeof(stSubMeshHeader), 1, pFile);

		fwrite(m_VertexArray, sizeof(stShapeVertices), m_VertexCount, pFile);
		fwrite(m_IndiceArray, sizeof(GLushort), m_IndexCount, pFile);

		//����������ĵ��ƫ��
		fwrite(&m_Translate_Self, sizeof(Vec3), 1, pFile);
		//����������ĵ������
		fwrite(&m_Scale_Self, sizeof(Vec3), 1, pFile);
		//����������ĵ����ת
		fwrite(&m_Rotate_Self, sizeof(Quaternion), 1, pFile);
		//��Ը��ڵ��λ��ƫ��
		fwrite(&m_Translate_Parent, sizeof(Vec3), 1, pFile);
		//��Ը��ڵ������
		fwrite(&m_Scale_Parent, sizeof(Vec3), 1, pFile);
		//��Ը��ڵ����ת
		fwrite(&m_Rotate_Parent, sizeof(Quaternion), 1, pFile);


		return true;
	}
	return false;
}

void C3DSubMesh::Release()
{	
	std::vector<frameData>::iterator iter;
	for(iter = frame.begin(); iter != frame.end(); iter++){
		delete iter->tHeader;
		delete iter->tIndice;
		delete iter->tSubMatrix;
		delete iter->tVeetices;
	}
	frame.clear();
	if(m_VertexArray){
		m_VertexArray = NULL;
	}

	if(m_IndiceArray)
	{
		m_IndiceArray = NULL;
	}
	m_VertexCount = 0;
	m_IndexCount = 0;
	if(glIsBuffer(m_VertexBuffer)){
		glDeleteBuffers(1, &m_VertexBuffer);
		m_VertexBuffer = 0;
	}
	if(glIsBuffer(m_IndexBuffer)){
		glDeleteBuffers(1, &m_IndexBuffer);
		m_IndexBuffer = 0;
	}
}