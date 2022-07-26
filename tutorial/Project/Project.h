#pragma once
#include "igl/opengl/glfw/Viewer.h"

class Project : public igl::opengl::glfw::Viewer
{
	
public:
<<<<<<< Updated upstream
	
	Project();
//	Project(float angle,float relationWH,float near, float far);
	void Init();
	void Update(const Eigen::Matrix4f& Proj, const Eigen::Matrix4f& View, const Eigen::Matrix4f& Model, unsigned int  shaderIndx, unsigned int shapeIndx);
	void WhenRotate();
	void WhenTranslate();
	void Animate() override;
	void ScaleAllShapes(float amt, int viewportIndx);
	
	~Project(void);
=======
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
    float time;
    std::vector<SceneShape> shapesGlobal;
    std::vector<int> pickedShapes;
    int cubeMapIndx = -1;
    float max_time;
    ~Project(void);
    void ChangeCubeMap(std::string file_name);
    void Project::NextCubeMap();
    bool zoomInMode = false;

private:
    Renderer *renderer = nullptr;
    long globalTime;
    SceneShape AddGlobalShape(std::string name, shapes shapeType, std::shared_ptr<ObjectMover> mover,
                              std::shared_ptr<Layer> layer, int parent, int viewPort);
    SceneShape Project::AddGlobalShapeFromFile(std::string name, std::string file_name,
                                               std::shared_ptr<ObjectMover> mover, std::shared_ptr<Layer> layer, int parent);
    bool animating;
>>>>>>> Stashed changes
};


