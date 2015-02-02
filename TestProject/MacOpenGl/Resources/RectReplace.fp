// Rectangle Texture (replace) Shader
// Fragment Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 120

uniform sampler2DRect  rectangleImage;

varying vec2 vVaryingTexCoord;

void main(void)
    { 
    gl_FragColor = texture2DRect(rectangleImage, vVaryingTexCoord);
    }
    