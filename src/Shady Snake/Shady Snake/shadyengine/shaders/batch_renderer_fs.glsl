#version 400

//outs
layout(location = 0) out vec4 finalColor;

//ins
in vec2 texCoords;

//uniforms
uniform bool useColor;
uniform sampler2D sampler0;
uniform vec4 color;


void main()
{
	if (useColor)
		finalColor = color;
	else
		finalColor = texture(sampler0,texCoords);	
}