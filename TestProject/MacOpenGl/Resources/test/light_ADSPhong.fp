// ADS Point lighting Shader
// Fragment Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 120

uniform vec4    ambientColor;
uniform vec4    diffuseColor;   
uniform vec4    specularColor;

varying vec3 vVaryingNormal;
varying vec3 vVaryingLightDir;


void main(void)
    { 
    // dot得到漫反射强度
    float diff = max(0.0, dot(normalize(vVaryingNormal), normalize(vVaryingLightDir)));

    // 强度乘以漫反射颜色
    gl_FragColor = diff * diffuseColor;
    gl_FragColor.a = 1.0;

    // 添加环境光
    gl_FragColor += ambientColor;


    // 镜面光
    vec3 vReflection = normalize(reflect(-normalize(vVaryingLightDir), normalize(vVaryingNormal)));
    float spec = max(0.0, dot(normalize(vVaryingNormal), vReflection));
    if(diff != 0) {
        float fSpec = pow(spec, 128.0);
        gl_FragColor.rgb += vec3(fSpec, fSpec, fSpec);
        }
    }
    