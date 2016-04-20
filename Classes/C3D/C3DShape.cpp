#include "C3DShape.h"
#include "comman/texture.h"

static GLfloat*	m_color = new GLfloat[4];

C3DShape::C3DShape(void):m_VertexBuffer(0)
	,m_IndexBuffer(0)
	,m_VertexArray(0)
	,m_IndiceArray(0)
	,m_VertexCount(0)
	,m_IndexCount(0)
	,m_ShaderProgram(NULL),
	m_Texture(NULL)
	,type(0)
{
	m_BlendFunc = BlendFunc::ALPHA_NON_PREMULTIPLIED;
	m_color[0] = 1.0f;
	m_color[1] = 1.0f;
	m_color[2] = 1.0f;
	m_color[3] = 1.0f;
}

void C3DShape::CreatePoints()
{
	Release();
	type = 1;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	auto size = Director::getInstance()->getVisibleSize();
	glGenBuffers(1, &m_VertexBuffer);
	//创建数组并填充数据
	m_VertexArray = new stShapeVertices[100];
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			float x, y;
			x = sin(i * 18 - 90);
			y = cos(j * 18 - 180);
			//m_VertexArray[i*10+j].Position = Vec3((i*size.width/20+50)/(size.width), (j*size.height/20+50)/(size.width), 0);
			m_VertexArray[i * 10 + j].Position = Vec3(x, y, 0);
		}
	}
	m_VertexCount = 100;
	m_IndexCount = 0;
	m_PrimitiveType = PT_POINTS;

	glBindBuffer(GL_ARRAY_BUFFER_ARB, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER_ARB, m_VertexCount * sizeof(stShapeVertices),
		m_VertexArray, GL_STATIC_DRAW);
	BuildShader();
}

void C3DShape::CreateLines()
{
	Release();
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	type = 2;
	glGenBuffers(1, &m_VertexBuffer);
	glGenBuffers(1, &m_IndexBuffer);
	//创建顶点数组
	m_VertexArray = new stShapeVertices[23];
	m_VertexArray[0].Position = kmVec3(-1, -1, 0);
	m_VertexArray[1].Position = kmVec3(-1, 1, 0);
	m_VertexArray[2].Position = kmVec3(0.5, 1, 0);
	m_VertexArray[3].Position = kmVec3(0.7, 1, 0);
	m_VertexArray[4].Position = kmVec3(1, 1, 0);
	m_VertexArray[5].Position = kmVec3(1, -1, 0);
	m_VertexArray[6].Position = kmVec3(0.8, -0.7, 0);
	m_VertexArray[7].Position = kmVec3(-0.5, -0.7, 0);
	m_VertexArray[8].Position = kmVec3(-0.5, 0, 0);
	m_VertexArray[9].Position = kmVec3(-0.6, 0.7, 0);
	m_VertexArray[10].Position = kmVec3(0, 0.7, 0);
	m_VertexArray[11].Position = kmVec3(0, 0, 0);
	m_VertexArray[12].Position = kmVec3(0.8, -0.5, 0);
	m_VertexArray[13].Position = kmVec3(0.8, 0, 0);
	m_VertexArray[14].Position = kmVec3(0.6, 0, 0);
	m_VertexArray[15].Position = kmVec3(0.6, 0.7, 0);
	m_VertexArray[16].Position = kmVec3(-0.8, -1, 0);
	m_VertexArray[17].Position = kmVec3(-0.6, 0.4, 0);
	m_VertexArray[18].Position = kmVec3(-0.2, 0.4, 0);
	m_VertexArray[19].Position = kmVec3(-0.2, -0.4, 0);
	m_VertexArray[20].Position = kmVec3(-0.6, 0.2, 0);
	m_VertexArray[21].Position = kmVec3(-0.4, 0.2, 0);
	m_VertexArray[22].Position = kmVec3(-0.4, -0.4, 0);
	//创建索引数组
	float indices[32] = {
		0, 1, 1, 2, 3, 4, 4, 5, 5, 16,
		6, 7, 7, 8, 9, 10, 10, 11,
		12, 13, 13, 14, 14, 15,
		17, 18, 18, 19, 20, 21, 21, 22
	};
	m_IndiceArray = new GLushort[24];
	for (int i = 0; i < 32; i++){
		m_IndiceArray[i] = indices[i];
	}

	m_VertexCount = 23;
	m_IndexCount = 32;
	m_PrimitiveType = PT_LINES;
	m_IndexFormat = INDEX16;
	//绑定数据到VB中
	glBindBuffer(GL_ARRAY_BUFFER_ARB, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER_ARB, m_VertexCount * sizeof(stShapeVertices),
		m_VertexArray, GL_STATIC_DRAW);

	//绑定下标到IB
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB, m_IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER_ARB, m_IndexCount * sizeof(GLushort),
		m_IndiceArray, GL_STATIC_DRAW);
	BuildShader();
	//出现OpenGL error 0x0500 in ..\renderer\CCTextureAtlas.cpp cocos2d::TextureAtlas::mapBuffers 312错误
}

void C3DShape::CreateTriangles()
{
	Release();
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	type = 3;
	glGenBuffers(1, &m_VertexBuffer);
	glGenBuffers(1, &m_IndexBuffer);
	///建顶点数组
	//m_VertexArray =/* new stShapeVertices[4*6];*/
	m_VertexArray = new stShapeVertices[8];
	m_VertexArray[0].Position = Vec3(-1, -1, 0);
	m_VertexArray[1].Position = Vec3(-1, 1, 0);
	m_VertexArray[2].Position = Vec3(1, 1, 0);
	m_VertexArray[3].Position = Vec3(1, -1, 0);
	m_VertexArray[4].Position = Vec3(-1, -1, 2);
	m_VertexArray[5].Position = Vec3(-1, 1, 2);
	m_VertexArray[6].Position = Vec3(1, 1, 2);
	m_VertexArray[7].Position = Vec3(1, -1, 2);
	//创建索引数组
	float indices[12 * 3] = { 0, 1, 2,
		0, 2, 3,
		2, 6, 7,
		2, 3, 7,
		5, 6, 7,
		5, 4, 7,
		5, 1, 0,
		0, 4, 5,
		0, 3, 7,
		0, 4, 7,
		1, 2, 6,
		1, 5, 6
	};
	m_IndiceArray = new GLushort[12 * 3];
	for (int i = 0; i < 12 * 3; i++){
		m_IndiceArray[i] = indices[i];
	}
	m_VertexCount = 8;
	m_IndexCount = 12 * 3;
	m_PrimitiveType = PT_TRIANGLES;

	//绑定数据到VB
	glBindBuffer(GL_ARRAY_BUFFER_ARB, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER_ARB, m_VertexCount * sizeof(stShapeVertices),
		m_VertexArray, GL_STATIC_DRAW);

	//绑定数据到IB中
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB, m_IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER_ARB, m_IndexCount * sizeof(GLushort),
		m_IndiceArray, GL_STATIC_DRAW);
	BuildShader();
}

C3DShape::~C3DShape(void)
{
}

void C3DShape::CreateSphere()
{
	Release();
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &m_VertexBuffer);
	glGenBuffers(1, &m_IndexBuffer);
	type = 4;
	int nRings = 40;
	int nSegments = 40;
	//每个环的角度
	float deltaRing = M_PI/(nRings);
	float deltaSegment = 2.0f*M_PI/nSegments;
	m_VertexCount = (nRings + 1) * (nSegments + 1);
	m_VertexArray = new stShapeVertices[m_VertexCount];
	stShapeVertices* pCurrVertex = m_VertexArray;
	m_IndexCount = nRings * (nSegments + 1) * 2;
	m_IndiceArray = new GLushort[m_IndexCount];
	GLushort* pCurrIndex = m_IndiceArray;
	GLushort vIndex = 0;
	m_PrimitiveType = PT_TRIANGLE_STRIP;
	m_IndexFormat = INDEX16;

	//创建球的算法
	for(int j=0; j<nRings+1; j++){
		float radius = sinf(j*deltaRing);
		float y0 = cosf(j*deltaRing);

		for(int i=0; i<nSegments+1; i++){
			float x0 = radius * sinf(i * deltaSegment);
			float z0 = radius * cosf(i * deltaSegment);
			pCurrVertex->Position.x = x0;
			pCurrVertex->Position.y = y0;
			pCurrVertex->Position.z = z0;
			pCurrVertex->TexUV.x = float(i)/nSegments;
			pCurrVertex->TexUV.y = float(j)/nRings;
			//log("%f %f", pCurrVertex->TexUV.x, pCurrVertex->TexUV.y);
			pCurrVertex++;

			//除了第一点和最后一点只有一次，其他点都有两次索引
			if(j != nRings){
				*pCurrIndex = vIndex;
				pCurrIndex++;

				*pCurrIndex = vIndex + (GLushort)(nSegments + 1);
				pCurrIndex++;
				vIndex++;
			}
		}
	}

	log("%d",m_VertexCount * sizeof(stShapeVertices ));
	//绑定数据到VB中
	glBindBuffer(GL_ARRAY_BUFFER_ARB, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER_ARB, m_VertexCount * sizeof(stShapeVertices),
					m_VertexArray, GL_STATIC_DRAW);

	//IB
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB, m_IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER_ARB, m_IndexCount * sizeof(GLushort),
				m_IndiceArray, GL_STATIC_DRAW);
	BuildShader();
}

void C3DShape::SetTexture(const char* texture)
{
	std::string strEx = "png";
	std::string str = texture;
	std::string::size_type pos = str.find_last_of(".");
	if(pos != std::string::npos){
		strEx = str.substr(pos+1);
	}else{
		return;
	}
	log("Ex:%s  image:%s",strEx.c_str(), texture);
	if(strEx == "dds"){
		TextureID = loadDDS(FileUtils::getInstance()->fullPathForFilename(texture).c_str());
		isTextureID = true;
		m_TextureFileName = texture;
		return;
	}
	Image *image = new Image;
	std::string imagePath = texture;
	imagePath = FileUtils::getInstance()->fullPathForFilename(texture);
	image->initWithImageFile(imagePath);
	if(!m_Texture)m_Texture = new Texture2D();
	m_Texture->initWithImage(image);
	/*Texture2D::TexParams tRepeatParams;
	tRepeatParams.magFilter = GL_LINEAR;
	tRepeatParams.minFilter = GL_LINEAR;
	tRepeatParams.wrapS = GL_REPEAT;
	tRepeatParams.wrapT = GL_REPEAT;
	m_Texture->setTexParameters(&tRepeatParams);
	m_Texture->setAntiAliasTexParameters();*/
	m_TextureFileName = texture;
	isTextureID = false;
	CC_SAFE_DELETE(image);
}

const BlendFunc& C3DShape::getBlendFunc()
{
	return m_BlendFunc;
}

void C3DShape::setBlendFunc(const BlendFunc& func)
{
	m_BlendFunc = func;
}

void C3DShape::setColor(float r, float g, float b, float a)
{
	m_color[0] = r;
	m_color[1] = g;
	m_color[2] = b;
	m_color[3] = a;
}

void C3DShape::setColorR(float r)
{
	m_color[0] = r;
}

void C3DShape::setColorG(float g)
{
	m_color[1] = g;
}

void C3DShape::setColorB(float b)
{
	m_color[2] = b;
}

void C3DShape::setColorA(float a)
{
	m_color[3] = a;
}

GLfloat* C3DShape::getColor()
{
	return m_color;
}

//创建Shader
void C3DShape::BuildShader()
{
	m_ShaderProgram = GLProgram::createWithFilenames("Shaders/C3DShapeVS.vsh", "Shaders/C3DShapePS.fsh");
	if(m_ShaderProgram){
		m_ShaderProgram->addAttribute("a_position", GLProgram::VERTEX_ATTRIB_POSITION);
		m_ShaderProgram->addAttribute("a_texCoord", GLProgram::VERTEX_ATTRIB_TEX_COORD);
		m_ShaderProgram->retain();
	}else{
		
	}
}

void C3DShape::Render()
{
	if(m_ShaderProgram && m_VertexCount > 0){

		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_ShaderProgram->use();
		//更新shader
		m_ShaderProgram->setUniformsForBuiltins();
		
		Mat4 matrixP;
		Mat4 matrixMV;
		Mat4 matrixMVP;
		Mat4 matrixWorld;
		Mat4 matrixMVPW;

		kmGLGetMatrix(KM_GL_PROJECTION, &matrixP);
		kmGLGetMatrix(KM_GL_MODELVIEW, &matrixMV);
		kmMat4Multiply(&matrixMVP, &matrixP, &matrixMV);
		GLuint matrixId = glGetUniformLocation(m_ShaderProgram->getProgram(), "CC_MVPMatrix");
		matrixWorld = GetWorldMatrix();
		kmMat4Multiply(&matrixMVPW, &matrixMVP, &matrixWorld);
		m_ShaderProgram->setUniformLocationWithMatrix4fv(matrixId, (GLfloat*)&matrixMVPW.m, 1);
		//matrixId = glGetUniformLocation(m_ShaderProgram->getProgram(), "matNormal");
		//m_ShaderProgram->setUniformLocationWithMatrix4fv(matrixId, (GLfloat*)matrixWorld.m, 1);
		m_TextureId = glGetUniformLocation(m_ShaderProgram->getProgram(), "myTextureSampler");
		m_ShaderProgram->setUniformLocationWith1i(m_TextureId, 0);
		m_colorId = glGetUniformLocation(m_ShaderProgram->getProgram(), "u_color");
		m_ShaderProgram->setUniformLocationWith4f(m_colorId, m_color[0], m_color[1], m_color[2], m_color[3]);
		if(isTextureID == true){
			GL::bindTexture2DN(0, TextureID);
			ccGLBindTexture2D(TextureID);
			ccGLBlendFunc(m_BlendFunc.src, m_BlendFunc.dst);
		}else{
			GL::bindTexture2DN(0, this->m_Texture->getName());
			ccGLBindTexture2D(m_Texture->getName());
			ccGLBlendFunc(m_BlendFunc.src, m_BlendFunc.dst);
		}
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	/*	glEnable(GL_ARRAY_BUFFER);*/
		glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
		glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION,3, GL_FLOAT, GL_FALSE,
			sizeof(stShapeVertices), (GLvoid*) offsetof( stShapeVertices, Position));
		glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORD);
		glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD,2, GL_FLOAT, GL_FALSE,
			sizeof(stShapeVertices), (GLvoid*) offsetof( stShapeVertices, TexUV));
		

		//如果有索引缓冲
		if(m_IndexCount > 0 && m_IndiceArray){
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
			glEnable(GL_ELEMENT_ARRAY_BUFFER);
			glDrawElements(m_PrimitiveType, (GLsizei)m_IndexCount, m_IndexFormat, 0);
		}else{
			glDrawArrays(m_PrimitiveType, 0, m_VertexCount);
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		CC_INCREMENT_GL_DRAWS(1);

		
	}
	C3DNode::Render();
}

void C3DShape::Release()
{
	if(m_VertexArray){
		delete[] m_VertexArray;
		m_VertexArray = NULL;
	}

	if(m_IndiceArray)
	{
		delete[] m_IndiceArray;
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