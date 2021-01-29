#version 400 core                                                            

uniform float quadInnerLevel1;
uniform float quadInnerLevel2;

uniform float quadOuterLevel1;
uniform float quadOuterLevel2;
uniform float quadOuterLevel3;
uniform float quadOuterLevel4;    

in VS_OUT 
{
    vec4 color;
} tcs_in[];

out TCS_OUT
{
    vec4 color;
} tcs_out_quad[];

layout (vertices = 4) out;

void main(void)                                                              
{                     
    if (gl_InvocationID == 0)                                                
    {                                                                        
        gl_TessLevelInner[0] = quadInnerLevel1;                                    
        gl_TessLevelInner[1] = quadInnerLevel2;           
                               
        gl_TessLevelOuter[0] = quadOuterLevel1;                                
        gl_TessLevelOuter[1] = quadOuterLevel2;                                
        gl_TessLevelOuter[2] = quadOuterLevel3;                                
        gl_TessLevelOuter[3] = quadOuterLevel4;                                    
    }                                                                        
    
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    
    tcs_out_quad[gl_InvocationID].color = tcs_in[gl_InvocationID].color;
}