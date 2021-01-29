#version 400 core                     

uniform vec4 pickedColor;
uniform int colorMode;

in vec4 vCol;           

in TES_OUT
{
    vec4 color;
} frag_in;
                  
out vec4 color;                     
                  
const int PICKED_COLOR = 1;
const int COLOR_INTERPOLATED = 0;

void main()                       
{       	
	switch(colorMode)
	{
		case PICKED_COLOR:
			color = pickedColor;
			break;

		case COLOR_INTERPOLATED:
			color = frag_in.color;
			break;

		default :
			color = vCol;
			break;
	}

}