#version 330
 
layout(location = 0) out vec4 OutColor;
 
in vec4 DrawColor;
 
void main( void )
{
  OutColor = DrawColor;
  OutColor = vec4(1, 0, 1, 1);
}