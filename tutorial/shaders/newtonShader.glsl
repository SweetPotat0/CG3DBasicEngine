#version 330

in vec2 texCoord0;
in vec3 normal0;
in vec3 color0;
in vec3 position0;

uniform vec4 lightColor;
uniform sampler2D sampler1;
uniform vec4 lightDirection;
uniform float time;
uniform float x;
uniform float y;

uniform int iterNum;
uniform vec4 coeffsReal;
uniform vec4 coeffsImag;
uniform float fxStart;
uniform float fxEnd;
uniform float fyStart;
uniform float fyEnd;
uniform float scrnXWidth;
uniform float scrnXHeight;
uniform vec2 root1;
uniform vec3 color1;
uniform vec2 root2;
uniform vec3 color2;
uniform vec2 root3;
uniform vec3 color3;
uniform float threashold;


out vec4 Color;

vec2 cMul(vec2 num1,vec2 num2){
    vec2 res = vec2(0,0);
    res.x = num1.x * num2.x - num1.y * num2.y;
    res.y = num1.x * num2.y + num1.y * num2.x;
    return res;
}

vec2 tzamud(vec2 num){
    return vec2(num.x,-num.y);
}

vec2 cSubD(vec2 num1,vec2 num2){
    return vec2(cMul(num1,tzamud(num2)))/cMul(num2,tzamud(num2)).x;
}

vec2 cPow(vec2 num,float pow){
    vec2 res = vec2(1,0);
    for(int i=0;i<pow;i++){
        res = cMul(res,num);
    }
    return res;
}

vec2 f(vec2 z) {
    vec2 a = vec2(coeffsReal[0], coeffsImag[0]);
    vec2 b = vec2(coeffsReal[1], coeffsImag[1]);
    vec2 c = vec2(coeffsReal[2], coeffsImag[2]);
    vec2 d = vec2(coeffsReal[3], coeffsImag[3]);
    return cMul(a,cPow(z,3)) + cMul(b,cPow(z,2)) + cMul(c,z)+d;
}

vec2 df(vec2 z){
    vec2 a = vec2(coeffsReal[0], coeffsImag[0]);
    vec2 b = vec2(coeffsReal[1], coeffsImag[1]);
    vec2 c = vec2(coeffsReal[2], coeffsImag[2]);
    return 3*cMul(a,cPow(z,2)) + 2*cMul(b,z)+c;
}

float currIter = iterNum;

vec2 findIterPos() {
    vec2 z = vec2(texCoord0.s,texCoord0.t);
    //Rescale pixel according to current x,y coordinates
    z = vec2(fxEnd-z.x*(fxEnd-fxStart),fyEnd-z.y*(fyEnd-fyStart));
    for(int i=0;i < iterNum;i++) {
        vec2 fz = f(z);
        vec2 dfz = df(z);
        z = z - cSubD(fz,dfz);
        if(distance(z,root1)<threashold||distance(z,root2)<threashold||distance(z,root3)<threashold) {
            currIter = i;
            break;
        }
    }
    return z;
}

void main()
{
    vec2 finalZ = findIterPos();
    float dist1 = distance(finalZ,root1);
    float dist2 = distance(finalZ,root2);
    float dist3 = distance(finalZ,root3);
    float sub = 1-float(currIter/iterNum)*0.5;
    if(dist1<=dist2 && dist1<=dist3){
        //1 is minimal
        // Color = vec4(color1.r*0.5,color1.g*0.1,color1.b*0.1,1);
        Color = vec4(color1*sub,1);
    }else if(dist2<=dist1 && dist2<=dist3){
        //2 is minimal
        // Color = vec4(color2.r*0.1,color2.g*0.1,color2.b*0.1,1);
        Color = vec4(color2*sub,1);
    }else if(dist3<=dist1 && dist3<=dist2){
        //3 is minimal
        // Color = vec4(color3.r*0.1,color3.g*0.1,color3.b*0.1,1);
        Color = vec4(color3*sub,1);
    }
    // Color = vec4(clamp(Color.r,0,255),clamp(Color.g,0,255),clamp(Color.b,0,255),1);
}
