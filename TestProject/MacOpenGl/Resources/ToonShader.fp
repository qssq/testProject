// Cell lighting Shader
// Fragment Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 120

uniform sampler1D colorTable;

varying float textureCoordinate;


void main(void)
   { 
   gl_FragColor = texture1D(colorTable, textureCoordinate);
   }