// Flat Shader
// Fragment Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 120

// Make geometry solid
uniform vec4 vColorValue;

// Output fragment color

void main(void)
   { 
   gl_FragColor = vColorValue;
   }