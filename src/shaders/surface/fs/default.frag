#version 130

varying vec2 fs_texcoord;
uniform sampler2D shimmer_application;

void main()
{
    gl_FragColor = texture2D(shimmer_application, fs_texcoord);
}
