#version 400 core                                          
               
layout (triangles, fractional_even_spacing, cw) in;

in TCS_OUT
{
    vec4 color;
} tes_in[];

out TES_OUT
{
    vec4 color;
} tes_out;

uniform mat4 projection;
uniform vec4 pickedColor;
uniform int tessCoord_x_color;
uniform int tessCoord_y_color;
uniform int tessCoord_z_color;

vec4 tessCoordinateColors()
{
    if(tessCoord_x_color == 0)
    {
        if(tessCoord_y_color == 1 && tessCoord_z_color == 2)
            return vec4(gl_TessCoord.x, gl_TessCoord.y, gl_TessCoord.z, 1.0);
        if(tessCoord_y_color == 2 && tessCoord_z_color == 1)
            return vec4(gl_TessCoord.x, gl_TessCoord.z, gl_TessCoord.y, 1.0);
    }
    else if (tessCoord_x_color == 1)
    {
        if(tessCoord_y_color == 0 && tessCoord_z_color == 2)
            return vec4(gl_TessCoord.y, gl_TessCoord.x, gl_TessCoord.z, 1.0);
        if(tessCoord_y_color == 2 && tessCoord_z_color == 0)
            return vec4(gl_TessCoord.z, gl_TessCoord.x, gl_TessCoord.y, 1.0);
    }
    else if (tessCoord_x_color == 2)
    {
        if(tessCoord_y_color == 0 && tessCoord_z_color == 1)
            return vec4(gl_TessCoord.y, gl_TessCoord.z, gl_TessCoord.x, 1.0);
        if(tessCoord_y_color == 1 && tessCoord_z_color == 0)
            return vec4(gl_TessCoord.z, gl_TessCoord.y, gl_TessCoord.x, 1.0);
    }
}

void main()                                            
{               
    tes_out.color = tessCoordinateColors();
    
    gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position) +
                  (gl_TessCoord.y * gl_in[1].gl_Position) +
                  (gl_TessCoord.z * gl_in[2].gl_Position);
}                                                          