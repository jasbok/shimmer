#version 130

attribute vec3 position;
attribute vec2 texcoord;
varying vec2 fs_texcoord;

uniform mat4 projection;

void main(void)
{
    gl_Position = projection * vec4(position.x, position.y, position.z, 1.0);
    fs_texcoord = texcoord;
}
