#version 430 core

in vec2 texCoords;

uniform sampler2D sampler0;
uniform vec4 color;
uniform bool use_color;

void main()
{  
	if (use_color)
		gl_FragColor = color;
	else
		gl_FragColor = texture(sampler0, texCoords);  
}