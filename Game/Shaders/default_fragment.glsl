#version 430
 out vec4 color;
 in vec2 uv0;
  uniform sampler2D diffuse;
 void main()
 {
     color = texture(diffuse, uv0); 
}