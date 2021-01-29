#version 330 core                                              
                              
layout (location = 0) in vec4 position;
out vec4 vCol;

uniform mat4 model;
uniform mat4 projection;

uniform vec4 pickedColor;
uniform int colorMode;

void main()                                                
{
    gl_Position = projection  * model * position;    //  view non fa funzionare il simple shader
    vCol = clamp(position, 0.0, 1.0);
}