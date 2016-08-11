#version 400

in vec3 TexCoord;

out vec4 FragColor;

uniform vec4 InnerColor;
uniform vec4 OuterColor;
uniform float RadiusInner;
uniform float RadiusOuter;
uniform float Offset;

void main()
{
	float dx = TexCoord.x - Offset;
	float dy = TexCoord.y - Offset;
	float dist = sqrt(dx * dx + dy * dy);
	FragColor = mix(InnerColor, OuterColor, smoothstep(RadiusInner, RadiusOuter, dist));
}