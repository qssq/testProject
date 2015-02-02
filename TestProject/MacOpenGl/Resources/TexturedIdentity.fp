// The TexturedIdentity Shader
// Fragment Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 120


uniform sampler2D colorMap;

varying vec2 vVaryingTexCoords;


void main(void)
   { 
   gl_FragColor = texture2D(colorMap, vVaryingTexCoords.st);
   }