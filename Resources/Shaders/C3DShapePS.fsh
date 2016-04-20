varying vec2 uvVarying;

uniform sampler2D myTextureSampler;
uniform vec4 u_color;

void main()
{
    gl_FragColor = texture2D(myTextureSampler, uvVarying)*u_color;//vec4(uvVarying.x, uvVarying.y, 1, 1);
}