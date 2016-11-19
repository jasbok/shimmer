#version 130
// #include /common/fs/colourspace.frag

varying vec2 fs_texcoord;
uniform sampler2D shimmer_application;
uniform vec2 res_ratio;

void main()
{
vec2 voffset = vec2(mod(gl_FragCoord.x, res_ratio.x) / res_ratio.x ,mod(gl_FragCoord.y, res_ratio.y) / res_ratio.y)- vec2(0.5, 0.5);
    vec4 sample = textureOffset(shimmer_application, fs_texcoord, ivec2(0,0));
    hsv_t hsv = shimmer_hsv(sample);
    float delta_color = hsv.v - hsv.delta * 0.5;
    vec4 color = vec4(delta_color, delta_color, delta_color, 1.0);

    if((hsv.h < 15.0 || hsv.h > 345.0) && hsv.s > 0.85){
        color = sample;
    }

   gl_FragColor = color;
}
