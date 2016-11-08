#version 130

varying vec2 fs_texcoord;
uniform sampler2D texture_unit;
uniform float scale;

void main()
{
    gl_FragColor = texture2D(texture_unit, fs_texcoord) * abs(mod(gl_FragCoord.y, 5) - 2) * 0.5;
}
