#version 400 core                                          
               
layout (quads, fractional_even_spacing, cw) in;    
uniform mat4 projection;

in TCS_OUT
{
    vec4 color;
} tes_in[];

out TES_OUT
{
    vec4 color;
} tes_out;

void main(void)                                            
{                      
    vec4 p1 = mix(gl_in[0].gl_Position, gl_in[1].gl_Position, gl_TessCoord.x);
    vec4 p2 = mix(gl_in[2].gl_Position, gl_in[3].gl_Position, gl_TessCoord.x);
    
    gl_Position = mix(p1, p2, gl_TessCoord.y);
   
    tes_out.color = vec4(gl_TessCoord.x, gl_TessCoord.y , gl_TessCoord.z, 1.0);
}