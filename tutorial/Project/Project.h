#pragma once
#include "igl/opengl/glfw/Viewer.h"
#include "SceneShape.h"
#include "igl/opengl/glfw/renderer.h"

class Project : public igl::opengl::glfw::Viewer
{

public:
    Project();
    //	Project(float angle,float relationWH,float near, float far);
    void Init(int DISPLAY_WIDTH, int DISPLAY_HEIGHT);
    void Update(const Eigen::Matrix4f &Proj, const Eigen::Matrix4f &View, const Eigen::Matrix4f &Model, unsigned int shaderIndx, unsigned int shapeIndx);
    void WhenRotate();
    void WhenTranslate();
    void Animate() override;
    void ScaleAllShapes(float amt, int viewportIndx);
    void SetRenderer(Renderer *renderer);
    void SetParent(int shape, int newParent);
    int GetParent(int shape);
    void SetMenu(igl::opengl::glfw::imgui::ImGuiMenu *menu);
    igl::opengl::glfw::imgui::ImGuiMenu *menu;
    std::vector<int> GetChildren(int shape);
    bool Load_Shape_From_File(const std::string &mesh_file_name_string);
    IGL_INLINE void my_open_dialog_load_mesh();
    void Play();
    float time = 0;
    std::vector<SceneShape> shapesGlobal;
    int cubeMapIndx = -1;
    int pickingPlaneIndx = -1;
    int blurShaderIndx = -1;
    int basicShaderIndx = -1;
    float max_time = 1;
    ~Project(void);
    void ChangeCubeMap(std::string file_name);
    void NextCubeMap();
    long globalTime;
    std::vector<Layer *> layers;
    Renderer *GetRenderer() { return renderer; }
    int DISPLAY_WIDTH;
    int DISPLAY_HEIGHT;

    float bizPoint[3] = {0,0,0};
    std::vector<Eigen::Vector3f> bizPoints;
    float start_end_time[2] = { 0, max_time };
    std::vector<int> farShapes;
    void updateFarShapes();
    float calculateCameraDistance(SceneShape shp);
    float farCoeff = 20;
    void ModeChange();

private:
    Renderer *renderer = nullptr;
    int AddGlobalShapeFromFile(std::string name, std::string file_name, int parent, Viewer *viewer, int viewPort);
    int AddGlobalShape(std::string name, igl::opengl::glfw::Viewer::shapes shapeType, Viewer *viewer, int parent, int viewPort);

    bool animating;
};
