#pragma once
#include "cocos2d.h"
#include "C3DNode.h"

USING_NS_CC;

//��������
enum VertexChannelType{
	VERTEX_ATTRIB_POSITION,
	VERTEX_ATTRIB_COLOR,
	VERTEX_ATTRIB_TEX_COORD,
	VERTEX_ATTRIB_NORMAL,
	VERTEX_ATTRIB_MAX,
	VERTEX_ATTRIB_TEX_COORDS = VERTEX_ATTRIB_TEX_COORD,
};

//��������
enum IndexFormat
{
	INDEX8 = GL_UNSIGNED_BYTE,
	INDEX16 = GL_UNSIGNED_SHORT,

};

//ͼ�λ�������
enum PrimitiveType
{
	PT_POINTS = GL_POINTS,
	PT_TRIANGLES = GL_TRIANGLES,
	PT_TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
	PT_LINES = GL_LINES,
	PT_LINE_STRIP = GL_LINE_STRIP,
};

struct stShapeVertices
{
	Vec3 Position;
	Vec3 Normal;
	Vec3		Color;		//ɫ��
	Vec2        TexUV;
};

class C3DShape : public C3DNode
{
public:
	C3DShape(void);
	~C3DShape(void);
	public:
	//����Shader
	virtual void	BuildShader();
	//��Ⱦ
	virtual void	Render();

	void CreateSphere();

	//������
	void	CreatePoints();
	//������
	void	CreateLines();
	//����������
	void	CreateTriangles();

	int type;

	void SetTexture(const char* texture);

	const BlendFunc& getBlendFunc();
	void setBlendFunc(const BlendFunc& func);
	std::string getTextureFileName(){ return m_TextureFileName; };
	void setColor(float r, float g, float b, float a);
	void setColorR(float r);
	void setColorG(float g);
	void setColorB(float b);
	void setColorA(float a);
	GLfloat* getColor();
protected:
	//�ͷ�
	virtual void	Release();
protected:
	//ͼ����Ⱦ��ʽ
	PrimitiveType		m_PrimitiveType;
	//������ʽ
	IndexFormat			m_IndexFormat;
	//��������
	stShapeVertices*	m_VertexArray;
	//��������
	GLushort*			m_IndiceArray;
	//VB
	GLuint				m_VertexBuffer;
	GLuint				m_UvBuffer;

	//TextureID
	GLuint				m_TextureId;

	//u_color
	GLuint				m_colorId;

	//IB
	GLuint				m_IndexBuffer;
	//��������
	int					m_VertexCount;
	//��������
	int					m_IndexCount;
	std::vector<Vec3>   vertexbuffer;
	std::vector<Vec2>   uvbuffer;
	//���õ�Shader
	GLProgram*			m_ShaderProgram;
	Texture2D*			 m_Texture;
	std::string			m_TextureFileName;
	GLuint vao;
	bool				isTextureID;
	GLuint				TextureID;

	BlendFunc m_BlendFunc;
};

