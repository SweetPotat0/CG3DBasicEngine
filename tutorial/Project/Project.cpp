#include "Project.h"
#include <iostream>
#include <chrono>
#include "./igl/file_dialog_open.h"

Layer* defaultLayer = new Layer(true, "default", std::vector<int>());

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

    int index = AddGlobalShapeFromFile("file: " + indxFile++, mesh_file_name_string, -1, this);
    SetShapeShader(index, 2);
    SetShapeMaterial(index, 2);
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

int Project::AddGlobalShapeFromFile(std::string name, std::string file_name, int parent, Viewer* viewer)
{
    int index = AddShapeFromFile(file_name, parent, TRIANGLES);
    SceneShape scnShape(name, MeshCopy, defaultLayer, index, viewer);
    scnShape.setlastDrawnPosition(Eigen::Vector3f(0, 0, 0));
    shapesGlobal.push_back(scnShape);
    return index;
}

int Project::AddGlobalShape(std::string name, igl::opengl::glfw::Viewer::shapes shapeType, 
    Viewer* viewer, int parent, int viewPort = 0)
{
    int index = AddShape(shapeType, parent, TRIANGLES, viewPort);
    SceneShape scnShape(name, shapeType, defaultLayer, index, viewer);
    scnShape.setlastDrawnPosition(Eigen::Vector3f(0, 0, 0));
    shapesGlobal.push_back(scnShape);
    return index;
}

void Project::Init()
{
    layers.push_back(defaultLayer);
    globalTime = 0;
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
    std::vector<Eigen::Vector3f> point = {Eigen::Vector3f(0, 2, 0)};


    // Cube map -->

    cubeMapIndx = AddGlobalShape("cubeMap", Cube, this , -2 );
    SetShapeShader(cubeMapIndx, cubemapShaderIndx);
    SetShapeMaterial(cubeMapIndx, dayLight3DMatIndx);

//    selected_data_index = cubeMap.getIndex();
    ShapeTransformation(scaleAll, 150, 0);
    SetShapeStatic(cubeMapIndx);


    // End cubeMap
    // Picking plane -->


    pickingPlaneIndx = AddGlobalShape("Picking plane", Plane, this, -2, 1);
    SetShapeShader(pickingPlaneIndx, pickingShaderIndx);
    SetShapeMaterial(pickingPlaneIndx, plane2DMatIndx);

    //    selected_data_index = pickingPlane.getIndex();
    ShapeTransformation(zTranslate, -1.1, 1);

    SetShapeStatic(pickingPlaneIndx);

    // Picking plane End
    int index;
    index = AddGlobalShape("test", Cube, this, -1);
    SetShapeShader(index, basicShaderIndx);
    SetShapeMaterial(index, box2DMatIndx);
    shapesGlobal[index].addBiz(BizMovment(points, 0, 500), &max_time);
    shapesGlobal[index].addBiz(BizMovment(point, 500, 1000), &max_time);
    shapesGlobal[index].addBiz(BizMovment(pointsRev, 1000, 1500), &max_time);
    shapesGlobal[index].move(2, y);


    index = AddGlobalShape("test 1", Cube, this, -1);
    SetShapeShader(index, basicShaderIndx);
    SetShapeMaterial(index, box2DMatIndx);
    shapesGlobal[index].move(2, x);


    index = AddGlobalShape("test 2", Cube, this,-1);
    SetShapeShader(index, basicShaderIndx);
    SetShapeMaterial(index, box2DMatIndx);

    
    shapesGlobal[selected_data_index].move(-1,y);




    /*selected_data_index = shp1.getIndex();
    animating = true;*/

    // SetShapeViewport(6, 1);
    //	ReadPixel(); //uncomment when you are reading from the z-buffer
}

void Project::Update(const Eigen::Matrix4f &Proj, const Eigen::Matrix4f &View, const Eigen::Matrix4f &Model, unsigned int shaderIndx, unsigned int shapeIndx)
{
    Shader *s = shaders[shaderIndx];
    long ctime;
    if (isActive) {
        ++globalTime;
        ctime = globalTime;
    }
    else
        ctime = time;
    
    if (shapeIndx != cubeMapIndx && shapeIndx != pickingPlaneIndx) {
        SceneShape scnShape = shapesGlobal[shapeIndx];
        Eigen::Vector3f pos = scnShape.getlastDrawnPosition();
        Eigen::Vector3f newPos = scnShape.getPosition((float)ctime);
        if (newPos != pos) {
        
            Eigen::Vector3f delta = newPos - pos;
            selected_data_index = shapeIndx;
            ShapeTransformation(xTranslate, delta(x), 0);
            ShapeTransformation(yTranslate, delta(y), 0);
            ShapeTransformation(zTranslate, delta(z), 0);
            shapesGlobal[shapeIndx].setlastDrawnPosition(newPos);
        }
    }
    

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
    s->Unbind();
}

void Project::WhenRotate()
{
}

void Project::WhenTranslate()
{
}

const int numOfCubeMaps = 3;

std::string cubeMaps[numOfCubeMaps] = { "Daylight Box_", "grass_cubemap_",
                                       "desert_cubemap_" };

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

void Project::SetRenderer(Renderer* renderer)
{
    if (this->renderer != nullptr)
        throw std::invalid_argument("renderer cannot be set twice");
    this->renderer = renderer;
}

void Project::SetParent(int shape, int newParent)
{
    //    shapesGlobal[shapesGlobal[shape].getParent()].removeChild(shape);
    //    shapesGlobal[shape].setParent(newParent);
    //    shapesGlobal[newParent].addChild(shape);
}

int Project::GetParent(int shape)
{
    //    return shapesGlobal[shape].getParent();
    return 1;
}

std::vector<int> Project::GetChildren(int shape)
{
    //    return shapesGlobal[shape].getChildren();
    return std::vector<int>();
}

void Project::Play()
{
    animating = !animating;
    globalTime = -1;
}
