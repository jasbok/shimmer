#version 130
// #include /common/colourspace.frag

varying vec2 fs_texcoord;
uniform sampler2D shimmer_application;

void main()
{
    vec4 sample = textureOffset(shimmer_application, fs_texcoord, ivec2(0,0));
    hsv_t hsv = shimmer_hsv(sample);
    float delta_color = hsv.v - hsv.delta * 0.5;
    vec4 color = vec4(delta_color, delta_color, delta_color, 1.0);

    float prime_deg = mod(hsv.h, 60);
    if((prime_deg < 15.0 || prime_deg > 45.0) && hsv.s > 0.85){
        color = sample;
    }

   gl_FragColor = color;
}
