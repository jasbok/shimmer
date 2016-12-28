#version 130

varying vec2 fs_texcoord;
uniform sampler2D shimmer_application;

void main()
{
    gl_FragColor = vec4(texture2D(shimmer_application, fs_texcoord).rgb * abs(mod(gl_FragCoord.y, 3) - 2) * 0.75f,1.0f);
}
