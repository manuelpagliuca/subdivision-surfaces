#version 330 core                     

uniform vec4 pickedColor;
uniform int colorMode;

in vec4 vCol;           
out vec4 color;                     
                  
const int PICKED_COLOR = 1;

void main()                       
{       	
	switch(colorMode)
	{
		case PICKED_COLOR:
			color = pickedColor;
			break;

		default :
			color = vCol;
			break;
	}

}