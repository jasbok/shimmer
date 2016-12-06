#version 130

// Source: https://www.codeproject.com/Articles/236394/Bi-Cubic-and-Bi-Linear-Interpolation-with-GLSL#GLSLLinear

vec4 bilinear(sampler2D sampler, vec2 coord){
    vec4 t00 = texture2D(sampler, coord);
    vec4 t10 = textureOffset(sampler, coord, ivec2(1, 0));
    vec4 t01 = textureOffset(sampler, coord, ivec2(0, 1));
    vec4 t11 = textureOffset(sampler, coord, ivec2(1, 1));
    vec2 d = fract(coord * textureSize(sampler, 0));
    vec4 bx = mix(t00, t10, d.x);
    vec4 by = mix(t01, t11, d.x);
    return mix(bx, by, d.y);
}

vec4 bilinear_preserve(sampler2D sampler, vec2 coord){
    vec2 u = 1.0f / textureSize(sampler, 0);
    vec2 d = fract(coord * textureSize(sampler, 0)) - vec2(0.5f, 0.5f);
    vec4 t00 = texture2D(sampler, coord);
    vec4 t10 = texture2D(sampler, coord + vec2(sign(d.x) * u.x, 0));
    vec4 t01 = texture2D(sampler, coord + vec2(0,               sign(d.y) * u.y));
    vec4 t11 = texture2D(sampler, coord + vec2(sign(d.x) * u.x, sign(d.y) * u.y));

    d = abs(d);
    vec4 bx = mix(t00, t10, d.x);
    vec4 by = mix(t01, t11, d.x);
    return mix(bx, by, d.y);
}

float triangular( float f )
{
    f = f / 2.0;
    if( f < 0.0 )
    {
        return ( f + 1.0 );
    }
    return ( 1.0 - f );
}

vec4 bicubic( sampler2D sampler, vec2 coord )
{
    vec2 d = fract(coord * textureSize(sampler, 0));
    vec2 s = 1.0 / textureSize(sampler, 0);
    vec4 sum = vec4( 0.0, 0.0, 0.0, 0.0 );
    vec4 denominator = vec4( 0.0, 0.0, 0.0, 0.0 );

    for( float j = -1; j <=2; j++ )
    {
        float f1 = triangular( j - d.x );
        vec4 coef1 = vec4( f1,f1,f1,f1 );
        for( float i =-1; i<= 2; i++)
        {
            float f2 = triangular ( d.y - i );
            vec4 coef2 = vec4( f2, f2, f2, f2 );
            sum += coef2 * coef1 * texture2D(sampler, coord + vec2(s.x * j, s.y * i));
            denominator += coef2 * coef1;
        }
    }
    return sum / denominator;
}
