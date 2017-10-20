
varying vec2 textureCoord;
uniform sampler2D tex_y;

void main(void)
{
    gl_FragColor = vec4(texture2D(tex_y, textureCoord).rrr, 1);
}
