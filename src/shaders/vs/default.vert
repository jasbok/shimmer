#version 120

attribute vec3 position;
attribute vec2 texcoord;
varying vec2 fs_texcoord;
varying float scale;

void main(void)
{
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
    fs_texcoord = texcoord;
}
