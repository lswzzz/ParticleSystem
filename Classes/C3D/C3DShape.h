#pragma once
#include "cocos2d.h"
#include "C3DNode.h"

USING_NS_CC;

//顶点类型
enum VertexChannelType{
	VERTEX_ATTRIB_POSITION,
	VERTEX_ATTRIB_COLOR,
	VERTEX_ATTRIB_TEX_COORD,
	VERTEX_ATTRIB_NORMAL,
	VERTEX_ATTRIB_MAX,
	VERTEX_ATTRIB_TEX_COORDS = VERTEX_ATTRIB_TEX_COORD,
};

//索引类型
enum IndexFormat
{
	INDEX8 = GL_UNSIGNED_BYTE,
	INDEX16 = GL_UNSIGNED_SHORT,

};

//图形绘制类型
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
	Vec3		Color;		//色彩
	Vec2        TexUV;
};

class C3DShape : public C3DNode
{
public:
	C3DShape(void);
	~C3DShape(void);
	public:
	//创建Shader
	virtual void	BuildShader();
	//渲染
	virtual void	Render();

	void CreateSphere();

	//创建点
	void	CreatePoints();
	//创建线
	void	CreateLines();
	//创建三角形
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
	//释放
	virtual void	Release();
protected:
	//图形渲染方式
	PrimitiveType		m_PrimitiveType;
	//索引格式
	IndexFormat			m_IndexFormat;
	//顶点数组
	stShapeVertices*	m_VertexArray;
	//索引数组
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
	//顶点数量
	int					m_VertexCount;
	//索引数量
	int					m_IndexCount;
	std::vector<Vec3>   vertexbuffer;
	std::vector<Vec2>   uvbuffer;
	//所用的Shader
	GLProgram*			m_ShaderProgram;
	Texture2D*			 m_Texture;
	std::string			m_TextureFileName;
	GLuint vao;
	bool				isTextureID;
	GLuint				TextureID;

	BlendFunc m_BlendFunc;
};

