#version 130

varying vec2 fs_texcoord;
uniform sampler2D texunit;
uniform vec4 colour;

void main(void){
    gl_FragColor = colour * vec4(1.0, 1.0, 1.0, texture(texunit, vec2(fs_texcoord.x, 1 - fs_texcoord.y)).r);
}
