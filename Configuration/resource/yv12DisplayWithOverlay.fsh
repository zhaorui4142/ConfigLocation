
varying highp vec2 textureCoord;
varying highp vec2 textureCoord_fbo;
uniform highp sampler2D tex_y;
uniform highp sampler2D tex_u;
uniform highp sampler2D tex_v;
uniform highp sampler2D tex_overlay;
void main(void)
{
    vec3 yuv;
    vec3 rgb;
    //×ª»»yuv->rgb
    yuv.x = texture2D(tex_y, textureCoord).r - 0.0625;
    yuv.y = texture2D(tex_u, textureCoord).r - 0.5;
    yuv.z = texture2D(tex_v, textureCoord).r - 0.5;
    rgb = mat3( 1.164383,     1.164383,    1.164383,
                0,           -0.391762,    2.017232,
                1.596027,    -0.812968,           0) * yuv;

    vec3 color = mix(rgb, texture2D(tex_overlay, textureCoord_fbo).rgb, texture2D(tex_overlay, textureCoord_fbo).a);
    gl_FragColor = vec4(color, 1);
}
