#version 120                                                   
                                                                 
attribute vec3 position;                            
attribute vec2 texcoord;
varying vec2 f_texcoord;
varying float scale;

void main(void)                                                        
{                                                                   
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
    f_texcoord = texcoord;
}  
