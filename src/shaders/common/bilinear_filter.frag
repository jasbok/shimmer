#version 130

vec4 bilinear(sampler2D sampler, vec2 coord){
    vec2 d = fract(coord * textureSize(sampler, 0));
    vec2 s = 1.0 / textureSize(sampler, 0);

    vec4 t00 = texture2D(sampler, coord );
    vec4 t10 = texture2D(sampler, coord + vec2(s.x, 0) );
    vec4 t01 = texture2D(sampler, coord + vec2(0, s.y) );
    vec4 t11 = texture2D(sampler, coord + vec2(s.x, s.y) );
    vec2 interp = abs(d);
    vec4 bx = mix(t00, t10, interp.x);
    vec4 by = mix(t01, t11, interp.x);
    return mix(bx, by, interp.y);
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

    vec4 nSum = vec4( 0.0, 0.0, 0.0, 0.0 );
    vec4 nDenom = vec4( 0.0, 0.0, 0.0, 0.0 );
    for( int m = -1; m <=2; m++ )
    {
        for( int n =-1; n<= 2; n++)
        {
            vec4 vecData = texture2D(sampler, coord + vec2(s.x * float( m ), s.y * float( n )));
            float f  = triangular( float( m ) - d.x );
            vec4 vecCooef1 = vec4( f,f,f,f );
            float f1 = triangular ( -( float( n ) - d.y ) );
            vec4 vecCoeef2 = vec4( f1, f1, f1, f1 );
            nSum = nSum + ( vecData * vecCoeef2 * vecCooef1  );
            nDenom = nDenom + (( vecCoeef2 * vecCooef1 ));
        }
    }
    return nSum / nDenom;
}
