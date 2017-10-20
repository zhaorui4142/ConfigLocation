/*attribute highp vec4 qt_Vertex;
attribute highp vec4 qt_MultiTexCoord0;
uniform highp mat4 qt_ModelViewProjectionMatrix;
varying highp vec4 qt_TexCoord0;

void main(void)
{
    gl_Position = qt_ModelViewProjectionMatrix * qt_Vertex;
    qt_TexCoord0 = qt_MultiTexCoord0;
}*/

attribute highp vec4 vertexIn;
attribute highp vec2 textureIn;
attribute highp vec2 textureIn_fbo;
varying highp vec2 textureCoord;
varying highp vec2 textureCoord_fbo;
void main(void)
{
    gl_Position = vertexIn;
    textureCoord = textureIn;
    textureCoord_fbo = textureIn_fbo;
}
