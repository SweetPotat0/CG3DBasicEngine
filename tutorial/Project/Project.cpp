#include "Project.h"
#include <iostream>
#include <chrono>
#include "./igl/file_dialog_open.h"

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

IGL_INLINE void Project::my_open_dialog_load_mesh()
{
    std::string fname = igl::file_dialog_open();

    if (fname.length() == 0)
        return;

    Load_Shape_From_File(fname.c_str());
}

int indxFile = 0;

bool Project::Load_Shape_From_File(
    const std::string &mesh_file_name_string)
{
    std::vector<Eigen::Vector3f> points = {Eigen::Vector3f(4, 4, 0),
                                           Eigen::Vector3f(0, 20, 0),
                                           Eigen::Vector3f(-10, -10, -100),
                                           Eigen::Vector3f(4, 4, 0)};

    std::shared_ptr<ObjectMoverBezier> bez = std::make_shared<ObjectMoverBezier>(points, 0, 500, &max_time);
    SceneShape shape = AddGlobalShapeFromFile("file: " + indxFile++, mesh_file_name_string, bez, nullptr, -1);
    SetShapeShader(shape.getIndex(), 2);
    SetShapeMaterial(shape.getIndex(), 2);
    std::cout << "Load mesh from file: " << mesh_file_name_string << std::endl;
    return true;
}

long getCurrentUnixTime()
{
    const auto p1 = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(p1.time_since_epoch()).count();
}

Project::Project() {}

void Project::SetMenu(igl::opengl::glfw::imgui::ImGuiMenu *menu)
{
    this->menu = menu;
}

// Project::Project(float angle ,float relationWH, float near, float far) : Scene(angle,relationWH,near,far)
//{
// }

SceneShape Project::AddGlobalShapeFromFile(std::string name, std::string file_name,
                                           std::shared_ptr<ObjectMover> mover, std::shared_ptr<Layer> layer, int parent)
{
    int index = AddShapeFromFile(file_name, parent, TRIANGLES);
    SceneShape scnShape(name, MeshCopy, mover, layer, index);
    scnShape.setlastDrawnPosition(Eigen::Vector3f(0, 0, 0));
    shapesGlobal.push_back(scnShape);
    return scnShape;
}

SceneShape Project::AddGlobalShape(std::string name, igl::opengl::glfw::Viewer::shapes shapeType,
                                   std::shared_ptr<ObjectMover> mover, std::shared_ptr<Layer> layer, int parent, int viewPort = 0)
{

    int index = AddShape(shapeType, parent, TRIANGLES, viewPort);
    SceneShape scnShape(name, shapeType, mover, layer, index);
    scnShape.setlastDrawnPosition(Eigen::Vector3f(0, 0, 0));
    shapesGlobal.push_back(scnShape);
    return scnShape;
}

void Project::Init()
{
    globalTime = -1;
    unsigned int texIDs[4] = {0, 1, 2, 3};
    unsigned int slots[4] = {0, 1, 2, 3};
    int pickingShaderIndx = AddShader("shaders/pickingShader");
    int cubemapShaderIndx = AddShader("shaders/cubemapShader");
    basicShaderIndx = AddShader("shaders/basicShader");
    blurShaderIndx = AddShader("shaders/blurShader");

    unsigned int grassTexIndx = AddTexture("textures/grass.bmp", 2);
    unsigned int dayLightBoxTexIndx = AddTexture("textures/cubemaps/Daylight Box_", 3);
    unsigned int boxTexIndx = AddTexture("textures/box0.bmp", 2);
    unsigned int planeTexIndx = AddTexture("textures/plane.png", 2);

    int grass2DMatIndx = AddMaterial(&grassTexIndx, slots, 1);
    int dayLight3DMatIndx = AddMaterial(&dayLightBoxTexIndx, slots + 1, 1);

    int box2DMatIndx = AddMaterial(&boxTexIndx, slots + 2, 1);
    int plane2DMatIndx = AddMaterial(&planeTexIndx, slots + 3, 1);

    std::vector<Eigen::Vector3f> points = {Eigen::Vector3f(0, 0, 0),
                                           Eigen::Vector3f(0, 20, 0),
                                           Eigen::Vector3f(-10, -10, -100),
                                           Eigen::Vector3f(0, 0, 0)};

    std::vector<Eigen::Vector3f> pointsRev = {Eigen::Vector3f(0, 0, 0),
                                              Eigen::Vector3f(-10, -10, -100),
                                              Eigen::Vector3f(0, 20, 0),
                                              Eigen::Vector3f(0, 0, 0)};

    std::shared_ptr<ObjectMoverBezier> bez = std::make_shared<ObjectMoverBezier>(points, 0, 500, &max_time);

    // Cube map -->

    SceneShape cubeMap = AddGlobalShape("cubeMap", Cube, bez, nullptr, -2);
    SetShapeShader(cubeMap.getIndex(), cubemapShaderIndx);
    SetShapeMaterial(cubeMap.getIndex(), dayLight3DMatIndx);

    selected_data_index = cubeMap.getIndex();
    ShapeTransformation(scaleAll, 150, 0);
    SetShapeStatic(cubeMap.getIndex());

    cubeMapIndx = cubeMap.getIndex();

    // End cubeMap

    SceneShape shp = AddGlobalShape("test", Cube, bez, nullptr, -1);
    shapesGlobal[shp.getIndex()].addMover(std::make_shared<ObjectMoverConstant>(Eigen::Vector3f(0, 0, 0),
                                                                                500, 50));
    shapesGlobal[shp.getIndex()].addMover(std::make_shared<ObjectMoverBezier>(pointsRev, 550, 500, &max_time));

    SetShapeShader(shp.getIndex(), basicShaderIndx);
    SetShapeMaterial(shp.getIndex(), box2DMatIndx);

    SceneShape shp1 = AddGlobalShape("test 1", Cube, bez, nullptr, -1);
    SetShapeShader(shp1.getIndex(), basicShaderIndx);
    SetShapeMaterial(shp1.getIndex(), box2DMatIndx);

    SceneShape shp2 = AddGlobalShape("test 2", Cube, bez, nullptr, -1);
    SetShapeShader(shp2.getIndex(), basicShaderIndx);
    SetShapeMaterial(shp2.getIndex(), box2DMatIndx);

    // Picking plane -->

    SceneShape pickingPlane = AddGlobalShape("Picking plane", Plane, bez, nullptr, -2, 1);
    SetShapeShader(pickingPlane.getIndex(), pickingShaderIndx);
    SetShapeMaterial(pickingPlane.getIndex(), plane2DMatIndx);

    selected_data_index = pickingPlane.getIndex();
    ShapeTransformation(zTranslate, -1.1, 1);

    SetShapeStatic(pickingPlane.getIndex());

    // Picking plane End

    selected_data_index = shp1.getIndex();
    animating = true;

    // SetShapeViewport(6, 1);
    //	ReadPixel(); //uncomment when you are reading from the z-buffer
}

void Project::Update(const Eigen::Matrix4f &Proj, const Eigen::Matrix4f &View, const Eigen::Matrix4f &Model, unsigned int shaderIndx, unsigned int shapeIndx)
{
    ++globalTime;
    Shader *s = shaders[shaderIndx];
    long ctime;
    if (isActive)
        ctime = globalTime;
    else
        ctime = time;
    //std::cout << time << std::endl;
    int r = ((shapeIndx + 1) & 0x000000FF) >> 0;
    int g = ((shapeIndx + 1) & 0x0000FF00) >> 8;
    int b = ((shapeIndx + 1) & 0x00FF0000) >> 16;

    selected_data_index = shapeIndx;

    SceneShape scnShape = shapesGlobal[shapeIndx];
    Eigen::Vector3f pos = scnShape.getlastDrawnPosition();

    Eigen::Vector3f newPos = scnShape.getPosition((float)ctime);
    Eigen::Vector3f delta = newPos - pos;

    // pickedShapes = {scnShape.getIndex()};
    ShapeTransformation(xTranslate, delta[0], 0);
    ShapeTransformation(yTranslate, delta[1], 0);
    ShapeTransformation(zTranslate, delta[2], 0);
    shapesGlobal[shapeIndx].setlastDrawnPosition(newPos);
    // pickedShapes.clear();

    s->Bind();
    s->SetUniformMat4f("Proj", Proj);
    s->SetUniformMat4f("View", View);
    s->SetUniformMat4f("Model", Model);
    if (shapesGlobal[shapeIndx].isTransparent)
    {
        s->SetUniform2f("isTransparent", 1, 0);
    }
    else
    {
        s->SetUniform2f("isTransparent", 0, 0);
    }
    if (data_list[shapeIndx]->GetMaterial() >= 0 && !materials.empty())
    {
        //		materials[shapes[pickedShape]->GetMaterial()]->Bind(textures);
        BindMaterial(s, data_list[shapeIndx]->GetMaterial());
    }
    if (shaderIndx == 0)
        s->SetUniform4f("lightColor", r / 255.0f, g / 255.0f, b / 255.0f, 0.0f);
    else
        s->SetUniform4f("lightColor", 4 / 100.0f, 60 / 100.0f, 99 / 100.0f, 0.5f);
    // textures[0]->Bind(0);

    // s->SetUniform1i("sampler2", materials[shapes[pickedShape]->GetMaterial()]->GetSlot(1));
    // s->SetUniform4f("lightDirection", 0.0f , 0.0f, -1.0f, 0.0f);
    //	if(shaderIndx == 0)
    //		s->SetUniform4f("lightColor",r/255.0f, g/255.0f, b/255.0f,1.0f);
    //	else
    //		s->SetUniform4f("lightColor",0.7f,0.8f,0.1f,1.0f);
    s->Unbind();
}

void Project::WhenRotate()
{
}

void Project::WhenTranslate()
{
}

const int numOfCubeMaps = 3;

std::string cubeMaps[numOfCubeMaps] = {"Daylight Box_", "grass_cubemap_",
                                       "desert_cubemap_"};

int cubeMapCurrTextIndx = 0;

void Project::NextCubeMap()
{
    cubeMapCurrTextIndx = (cubeMapCurrTextIndx + 1) % numOfCubeMaps;
    ChangeCubeMap(cubeMaps[cubeMapCurrTextIndx]);
}

void Project::ChangeCubeMap(std::string file_name)
{
    unsigned int tex = AddTexture("textures/cubemaps/" + file_name, 3);
    unsigned int numOfMats = materials.size();
    int cubeMat = AddMaterial(&tex, &numOfMats, 1);
    SetShapeMaterial(cubeMapIndx, cubeMat);
}

void Project::Animate()
{
    animating = !animating;
}

void Project::ScaleAllShapes(float amt, int viewportIndx)
{
    for (int i = 1; i < data_list.size(); i++)
    {
        if (data_list[i]->Is2Render(viewportIndx))
        {
            data_list[i]->MyScale(Eigen::Vector3d(amt, amt, amt));
        }
    }
}

Project::~Project(void)
{
}

void Project::SetRenderer(Renderer *renderer)
{
    if (this->renderer != nullptr)
        throw std::invalid_argument("renderer cannot be set twice");
    this->renderer = renderer;
}

void Project::SetParent(int shape, int newParent)
{
    shapesGlobal[shapesGlobal[shape].getParent()].removeChild(shape);
    shapesGlobal[shape].setParent(newParent);
    shapesGlobal[newParent].addChild(shape);
}

int Project::GetParent(int shape)
{
    return shapesGlobal[shape].getParent();
}

std::vector<int> Project::GetChildren(int shape)
{
    return shapesGlobal[shape].getChildren();
}

void Project::Play()
{
    animating = !animating;
    globalTime = -1;
}
