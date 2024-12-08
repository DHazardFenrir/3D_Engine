#version 430
 out vec4 color;
 in vec2 uv0;
  uniform sampler2D mytexture;
 void main()
 {
     color = texture(mytexture, uv0); 
}