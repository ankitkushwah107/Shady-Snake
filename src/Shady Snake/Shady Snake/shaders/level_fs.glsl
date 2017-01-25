#version 400

//outs
layout(location = 0) out vec4 finalColor;

//ins
in vec2 tex_coords;

//uniforms
uniform sampler2D sprite_sheet;


void main()
{
		finalColor = texture(sprite_sheet,tex_coords);	
}