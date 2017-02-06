#version 130
// #include /usr/local/libshimmer/shaders/common/colourspace.frag
// #include /usr/local/libshimmer/shaders/common/bilinear_filter.frag

varying vec2 fs_texcoord;
uniform sampler2D shimmer_application;

float fclamp(   float p00, float p10, float p01, float p11, float sfilter, float fmix){
    float diff00 = abs(p00 - sfilter);
    float diff10 = abs(p10 - sfilter);
    float diff01 = abs(p01 - sfilter);
    float diff11 = abs(p11 - sfilter);

    float diff_min =   min(diff00,
                       min(diff10, 
                       min(diff01,
                       diff11)));

    if(diff_min == diff10) return mix(p10, sfilter, fmix);
    if(diff_min == diff01) return mix(p01, sfilter, fmix);
    //if(diff_min == diff11) return mix(p11, sfilter, fmix);
    return mix(p00, sfilter, fmix);
}

vec3 vclamp(   vec3 p00, vec3 p10, vec3 p01, vec3 p11, vec3 sfilter, float fmix){
    float diff00 = distance(p00,sfilter);
    float diff10 = distance(p10,sfilter);
    float diff01 = distance(p01,sfilter);
    float diff11 = distance(p11,sfilter);

    float diff_min =   min(diff00,
                       min(diff10, 
                       min(diff01,
                       diff11)));

    if(diff_min == diff10) return mix(p10, sfilter, fmix);
    if(diff_min == diff01) return mix(p01, sfilter, fmix);
    if(diff_min == diff11) return mix(p11, sfilter, fmix);
    return mix(p00, sfilter, fmix);
}

void main()
{
    vec2 u = 1.0f / textureSize(shimmer_application, 0);
    vec2 d = fract(fs_texcoord * textureSize(shimmer_application, 0)) - vec2(0.5f, 0.5f);

    vec4 p[16];
    for(int j = -1; j < 3; j++){
        int dj = 4 * (j+1);
        for(int i = -1; i < 3; i++){
            p[dj + i + 1] = texture2D(shimmer_application, fs_texcoord + vec2(sign(d.x) * u.x * i, sign(d.y) * u.y * j), 0);
        }
    }
    vec4 a00 = vec4(0,0,0,0); vec4 a10 = vec4(0,0,0,0); vec4 a01 = vec4(0,0,0,0); vec4 a11 = vec4(0,0,0,0);
    for(int j = -1; j < 2; j++){
        int dj = 4 * (j);
        for(int i = -1; i < 2; i++){
            if(i != 0 || j != 0){
                a00 += p[5 + dj + i];
                a10 += p[6 + dj + i];
                a01 += p[9 + dj + i];
                a11 += p[10 + dj + i];
            }
        }
    }
    a00 = (p[5] - a00 * 0.125) + 1.0f;
    a10 = (p[6] - a10 * 0.125) + 1.0f;
    a01 = (p[9] - a01 * 0.125) + 1.0f;
    a11 = (p[10] - a11 * 0.125) + 1.0f;

    vec4 f00 = bilinear(p[5], p[6], p[9], p[10], d);
    vec4 d00 = bilinear(a00, a10, a01, a11, d);
    gl_FragColor =
        vec4(
            fclamp(p[5].r, p[6].r, p[9].r, p[10].r, f00.r * d00.r, 0.0f),
            fclamp(p[5].g, p[6].g, p[9].g, p[10].g, f00.g * d00.g, 0.0f),
            fclamp(p[5].b, p[6].b, p[9].b, p[10].b, f00.b * d00.b, 0.0f),
            1.0);
    //gl_FragColor = d00;
//     gl_FragColor =
//         vec4(
//             vclamp(p[5].rgb, p[6].rgb, p[9].rgb, p[10].rgb, f00.rgb * d00.rgb, 0.0025f),
//             1.0);
}
