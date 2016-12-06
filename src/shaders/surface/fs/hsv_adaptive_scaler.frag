#version 130
// #include /usr/local/libshimmer/shaders/common/colourspace.frag
// #include /usr/local/libshimmer/shaders/common/bilinear_filter.frag

varying vec2 fs_texcoord;
uniform sampler2D shimmer_application;

uniform float h_crange = 36.0f;
uniform float s_crange = 0.1f;
uniform float v_crange = 0.1f;

float fclamp(float p00, float p10, float p01, float p11, float sfilter, float fmix){

    float diff00 = abs(p00 - sfilter);
    float diff10 = abs(p10 - sfilter);
    float diff01 = abs(p01 - sfilter);
    float diff11 = abs(p11 - sfilter);

    float diff_min =   min(diff00,
                       min(diff01,
                       min(diff10, diff11)));

    if(diff_min == diff10) return mix(p10, sfilter, fmix);
    if(diff_min == diff01) return mix(p01, sfilter, fmix);
    if(diff_min == diff11) return mix(p11, sfilter, fmix);
    return mix(p00, sfilter, fmix);
}

void main()
{
    vec2 u = 1.0f / textureSize(shimmer_application, 0);
    vec2 d = fract(fs_texcoord * textureSize(shimmer_application, 0)) - vec2(0.5f, 0.5f);
    vec4 p00 = texture2D(shimmer_application, fs_texcoord);
    vec4 p10 = texture2D(shimmer_application, fs_texcoord + vec2(sign(d.x) * u.x, 0));
    vec4 p01 = texture2D(shimmer_application, fs_texcoord + vec2(0,               sign(d.y) * u.y));
    vec4 p11 = texture2D(shimmer_application, fs_texcoord + vec2(sign(d.x) * u.x, sign(d.y) * u.y));
    vec4 f00 = bilinear_preserve(shimmer_application, fs_texcoord);

    gl_FragColor =
        vec4(
            fclamp(p00.r, p10.r, p01.r, p11.r, f00.r, 0.1333333f),
            fclamp(p00.g, p10.g, p01.g, p11.g, f00.g, 0.1333333f),
            fclamp(p00.b, p10.b, p01.b, p11.b, f00.b, 0.1333333f),
            1.0);

//     hsv_t h00 = shimmer_hsv(p00);
//     hsv_t h10 = shimmer_hsv(p10);
//     hsv_t h01 = shimmer_hsv(p01);
//     hsv_t h11 = shimmer_hsv(p11);
//     hsv_t hf00 = shimmer_hsv(f00);
//
//     gl_FragColor = shimmer_rgb(hsv_t(
//             fclamp(h00.h, h10.h, h01.h, h11.h, hf00.h, 0.333f),
//             fclamp(h00.s, h10.s, h01.s, h11.s, hf00.s, 0.333f),
//             fclamp(h00.v, h10.v, h01.v, h11.v, hf00.v, 0.333f),
//             0.0
//     ));
}
