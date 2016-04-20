attribute vec3 a_position;
attribute vec2 a_texCoord;

varying vec2 uvVarying;

void main()
{
	gl_Position = CC_MVPMatrix * vec4(a_position, 1.0);
	uvVarying = a_texCoord;
}
