#version 130
// #include /common/fs/colourspace.frag

varying vec2 fs_texcoord;
uniform sampler2D shimmer_application;
uniform vec2 res_ratio;

uniform float h_segment = 7.5f;
uniform float h_clamp_range = 0.90f;

uniform float s_segment = 0.1f;
uniform float s_clamp_range = 0.90f;

uniform float v_segment = 0.05f;
uniform float v_clamp_range = 0.90f;

float clamp(float value, float segment, float clamp_range){
    float seg = mod(value, segment);
    float seg_clamp = seg * 0.5f * clamp_range;

    if(seg >= seg_clamp && seg <= segment * 0.5f){
        return value - (seg - seg_clamp);
    }
    else if(seg >= segment * 0.5f &&  seg <= (segment - seg_clamp)){
        return value + (segment - seg_clamp - seg);
    }
    return value;
}

void main()
{
vec2 voffset = vec2(mod(gl_FragCoord.x, res_ratio.x) / res_ratio.x ,mod(gl_FragCoord.y, res_ratio.y) / res_ratio.y)- vec2(0.5, 0.5);
    vec4 sample = textureOffset(shimmer_application, fs_texcoord, ivec2(0,0));
    hsv_t hsv = shimmer_hsv(sample);

    hsv.h = clamp(hsv.h, h_segment, h_clamp_range);
    hsv.s = clamp(hsv.s, s_segment, s_clamp_range);
    hsv.v = clamp(hsv.v, v_segment, v_clamp_range);

    gl_FragColor = shimmer_rgb(hsv);
}
