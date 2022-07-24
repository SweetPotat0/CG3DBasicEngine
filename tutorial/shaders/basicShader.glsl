#version 330

in vec2 texCoord0;
in vec3 normal0;
in vec3 color0;
in vec3 position0;
in float shapeIndx;

uniform vec4 lightColor;
uniform sampler2D sampler1;
uniform vec4 lightDirection;

out vec4 Color;
void main()
{
    // Color =  vec4(color0,1.0); //you must have gl_FragColor
    vec3 colr = vec3(0,0,0);
    if(shapeIndx==0) {
        colr = vec3(0.5,1,1);
    }
    else if(shapeIndx==1) {
        colr = vec3(1,0.5,1);
    }
    else if(shapeIndx==2) {
        colr = vec3(1,1,0.5);
    }
    else if(shapeIndx==3) {
        colr = vec3(1,1,0);
    }
	Color = texture2D(sampler1, texCoord0) * vec4(colr, 0.4); //you must have gl_FragColor
}
