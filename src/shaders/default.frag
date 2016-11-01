#version 120                                   
    
varying vec2 f_texcoord;
uniform sampler2D texture_unit;
uniform float scale;

void main()                                         
{                                                 
    gl_FragColor = texture2D(texture_unit, f_texcoord);
}                                                  
