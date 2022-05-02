#include "./Assignment2.h"
#include "./sceneParser.h"
#include <iostream>

static void printMat(const Eigen::Matrix4d &mat)
{
    std::cout << " matrix:" << std::endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            std::cout << mat(j, i) << " ";
        std::cout << std::endl;
    }
}

Assignment2::Assignment2()
{
}

// Assignment2::Assignment2(float angle ,float relationWH, float near, float far) : Scene(angle,relationWH,near,far)
//{
// }

SceneData *sceneData;

void Assignment2::Init()
{
    sceneData = new SceneData();
    SceneParser::SceneParser("C:/Users/guyma/Desktop/scene.txt", sceneData);
    unsigned int texIDs[3] = {0, 1, 2};
    unsigned int slots[3] = {0, 1, 2};

    AddShader("shaders/pickingShader");
    AddShader("shaders/raytracingShader");

    AddTexture("textures/box0.bmp", 2);
    AddTexture("textures/grass.bmp", 2);

    AddMaterial(texIDs, slots, 2);
    AddMaterial(texIDs + 1, slots + 1, 1);

    AddShape(Plane, -1, TRIANGLES, 0);
    SetShapeShader(0, 1);
    SetShapeMaterial(0, 0);

    pickedShape = 0;
    SetShapeStatic(0);

    // SetShapeViewport(6, 1);
    //	ReadPixel(); //uncomment when you are reading from the z-buffer
}

Eigen::Matrix4f *generateMatFromVec(std::vector<Eigen::Vector4f> vecs, size_t size)
{
    Eigen::Matrix4f *objectsMat = new Eigen::Matrix4f();
    int index = 0;
    for (size_t i = 0; i < size; i++)
    {
        (*objectsMat).data()[index + 0] = vecs[i][0];
        (*objectsMat).data()[index + 1] = vecs[i][1];
        (*objectsMat).data()[index + 2] = vecs[i][2];
        (*objectsMat).data()[index + 3] = vecs[i][3];
        index += 4;
    }
    return objectsMat;
}

Eigen::Matrix4f *generateSpotMatFromVec(std::vector<Eigen::Vector4f> vecs, size_t max_size)
{
    Eigen::Matrix4f *objectsMat = new Eigen::Matrix4f();
    int index = 0;
    for (size_t i = 0; i < max_size; i++)
    {
        if (vecs[i][4] == 1)
        {
            (*objectsMat).data()[index + 0] = vecs[i][0];
            (*objectsMat).data()[index + 1] = vecs[i][1];
            (*objectsMat).data()[index + 2] = vecs[i][2];
            (*objectsMat).data()[index + 3] = vecs[i][3];
            index += 4;
        }
    }
    return objectsMat;
}

void Assignment2::Update(const Eigen::Matrix4f &Proj, const Eigen::Matrix4f &View, const Eigen::Matrix4f &Model, unsigned int shaderIndx, unsigned int shapeIndx)
{
    Shader *s = shaders[shaderIndx];
    int r = ((shapeIndx + 1) & 0x000000FF) >> 0;
    int g = ((shapeIndx + 1) & 0x0000FF00) >> 8;
    int b = ((shapeIndx + 1) & 0x00FF0000) >> 16;

    s->Bind();
    s->SetUniformMat4f("Proj", Proj);
    s->SetUniformMat4f("View", View);
    s->SetUniformMat4f("Model", Model);
    if (data_list[shapeIndx]->GetMaterial() >= 0 && !materials.empty())
    {
        //		materials[shapes[pickedShape]->GetMaterial()]->Bind(textures);
        BindMaterial(s, data_list[shapeIndx]->GetMaterial());
    }
    if (shaderIndx == 0)
        s->SetUniform4f("lightColor", r / 255.0f, g / 255.0f, b / 255.0f, 0.0f);
    else
    {
        s->SetUniform4f("lightColor", 4 / 100.0f, 60 / 100.0f, 99 / 100.0f, 0.5f);
        s->SetUniform4f("eye", sceneData->eye.data()[0], sceneData->eye.data()[1], sceneData->eye.data()[2], sceneData->eye.data()[3]);
        s->SetUniform4f("ambient", sceneData->ambient.data()[0], sceneData->ambient.data()[1], sceneData->ambient.data()[2], sceneData->ambient.data()[3]);
        s->SetUniform4f("ambient", sceneData->ambient.data()[0], sceneData->ambient.data()[1], sceneData->ambient.data()[2], sceneData->ambient.data()[3]);
        s->SetUniformMat4f("objects", *generateMatFromVec(sceneData->objects, sceneData->sizes[0]));
        s->SetUniformMat4f("objColors", *generateMatFromVec(sceneData->colors, sceneData->sizes[0]));
        s->SetUniformMat4f("lightsDirection", *generateMatFromVec(sceneData->directions, sceneData->sizes[1]));
        s->SetUniformMat4f("lightsIntensity", *generateMatFromVec(sceneData->intensities, sceneData->sizes[1]));
        s->SetUniformMat4f("lightsPosition", *generateSpotMatFromVec(sceneData->lights, sceneData->sizes[1]));
        s->SetUniform4i("sizes",sceneData->sizes.data()[0],sceneData->sizes.data()[1],sceneData->sizes.data()[2],sceneData->sizes.data()[3]);
    }
    // textures[0]->Bind(0);

    // s->SetUniform1i("sampler2", materials[shapes[pickedShape]->GetMaterial()]->GetSlot(1));
    // s->SetUniform4f("lightDirection", 0.0f , 0.0f, -1.0f, 0.0f);
    //	if(shaderIndx == 0)
    //		s->SetUniform4f("lightColor",r/255.0f, g/255.0f, b/255.0f,1.0f);
    //	else
    //		s->SetUniform4f("lightColor",0.7f,0.8f,0.1f,1.0f);
    s->Unbind();
}

void Assignment2::WhenRotate()
{
}

void Assignment2::WhenTranslate()
{
}

void Assignment2::Animate()
{
    if (isActive)
    {
    }
}

void Assignment2::ScaleAllShapes(float amt, int viewportIndx)
{
    for (int i = 1; i < data_list.size(); i++)
    {
        if (data_list[i]->Is2Render(viewportIndx))
        {
            data_list[i]->MyScale(Eigen::Vector3d(amt, amt, amt));
        }
    }
}

Assignment2::~Assignment2(void)
{
}
