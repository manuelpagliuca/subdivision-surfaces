#version 400 core                                                            

layout (vertices = 3) out;

in VS_OUT 
{
    vec4 color;
} tcs_in[];

out TCS_OUT
{
    vec4 color;
} tcs_out[];

uniform float triangInnerLevel;
uniform float triangOuterLevel1;    
uniform float triangOuterLevel2;    
uniform float triangOuterLevel3;    

void main(void)                                                              
{                                                                            
    if (gl_InvocationID == 0)                                                
    {                                                                        
        gl_TessLevelInner[0] = triangInnerLevel;                                          
        gl_TessLevelOuter[0] = triangOuterLevel1;                                          
        gl_TessLevelOuter[1] = triangOuterLevel2;                                          
        gl_TessLevelOuter[2] = triangOuterLevel3;                                          
    }
 
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    tcs_out[gl_InvocationID].color = tcs_in[gl_InvocationID].color;
}                                                                             