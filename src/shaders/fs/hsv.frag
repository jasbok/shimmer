#version 130

varying vec2 fs_texcoord;
uniform sampler2D texture_unit;
uniform vec2 res_ratio;

vec4 shimmer_hsv(vec4 col);

void main()
{
vec2 voffset = vec2(mod(gl_FragCoord.x, res_ratio.x) / res_ratio.x ,mod(gl_FragCoord.y, res_ratio.y) / res_ratio.y)- vec2(0.5, 0.5);
    vec4 sample = textureOffset(texture_unit, fs_texcoord, ivec2(0,0));
    vec4 hsv = shimmer_hsv(sample);
    float delta_color = hsv.b - hsv.a * 0.5;
    vec4 color = vec4(delta_color, delta_color, delta_color, 1.0);

    if((hsv.r < 0.045 || hsv.r > 0.97) && hsv.g > 0.85){
        color = sample;
    }

   gl_FragColor = color;
}
