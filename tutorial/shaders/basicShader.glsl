#version 330

in vec2 texCoord0;
in vec3 normal0;
in vec3 color0;
in vec3 position0;
<<<<<<< Updated upstream
=======
in float shapeIndx;
in float isTransparentFS;
>>>>>>> Stashed changes

uniform vec4 lightColor;
uniform sampler2D sampler1;
uniform vec4 lightDirection;

out vec4 Color;
void main()
{
<<<<<<< Updated upstream
	Color = texture2D(sampler1, texCoord0)* vec4(color0,1.0); //you must have gl_FragColor
=======
    if(isTransparentFS == 1) {
        Color = texture2D(sampler1, texCoord0) * vec4(color0, 0.4);
    } else {
        Color = texture2D(sampler1, texCoord0) * vec4(color0, 1);
    }
	 //you must have gl_FragColor
>>>>>>> Stashed changes
}
