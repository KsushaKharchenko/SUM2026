#version 460 

layout(location = 0) out vec4 OutColor;

in vec4 DrawColor;
in vec3 DrawNormal;
in vec3 DrawPos;
in vec3 DrawPosOrg;
in vec2 DrawTexCoord;

uniform vec3 CamLoc;
uniform float Time, GlobalTime;
uniform vec3 Ka, Kd, Ks;
uniform float Ph;

uniform bool IsTexture0;
layout(binding = 0) uniform sampler2D Tex;

void main( void )
{
  OutColor = vec4(color, 1);
}