// Skybox Shader
// Fragment Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 120

uniform samplerCube  cubeMap;

varying vec3 vVaryingTexCoord;

void main(void)
    { 
    gl_FragColor = textureCube(cubeMap, vVaryingTexCoord);
    }
    