in vec3 vColour;		
in vec3 vPosition;	


uniform mat4 MVP;
uniform vec3 objectColour;
uniform int isWireframe;		

out vec3 color;		

void main()
{
    gl_Position = MVP * vec4( vPosition, 1.0f );
	color = objectColour;
}