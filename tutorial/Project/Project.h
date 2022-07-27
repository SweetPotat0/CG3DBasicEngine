#pragma once
#include "igl/opengl/glfw/Viewer.h"
#include "SceneShape.h"
#include "igl/opengl/glfw/renderer.h"

class Project : public igl::opengl::glfw::Viewer
{

public:
    Project();
    //	Project(float angle,float relationWH,float near, float far);
    void Init();
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
    int blurShaderIndx = -1;
    int basicShaderIndx = -1;
    float max_time = 1;
    ~Project(void);
    void ChangeCubeMap(std::string file_name);
    void NextCubeMap();
    long globalTime;

private:
    Renderer *renderer = nullptr;
    SceneShape AddGlobalShapeFromFile(std::string name, std::string file_name,
                                       std::shared_ptr<Layer> layer, int parent, Viewer* viewer);
    SceneShape AddGlobalShape(std::string name, igl::opengl::glfw::Viewer::shapes shapeType,
                               std::shared_ptr<Layer> layer,Viewer* viewer, int parent, int viewPort );

    bool animating;
};
