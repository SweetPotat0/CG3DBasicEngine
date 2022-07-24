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
	void Update(const Eigen::Matrix4f& Proj, const Eigen::Matrix4f& View, const Eigen::Matrix4f& Model, unsigned int  shaderIndx, unsigned int shapeIndx);
	void WhenRotate();
	void WhenTranslate();
	void Animate() override;
	void ScaleAllShapes(float amt, int viewportIndx);
    void SetRenderer(Renderer *renderer);
    void SetParent(int shape, int newParent);
    int GetParent(int shape);
    void SetMenu(igl::opengl::glfw::imgui::ImGuiMenu* menu);
    igl::opengl::glfw::imgui::ImGuiMenu* menu;
    std::vector<int> GetChildren(int shape);
    void Play();
    float time;
    float max_time;
	~Project(void);
private:
    std::vector<SceneShape> shapesGlobal;
    Renderer *renderer = nullptr;
    long globalTime;
    SceneShape AddGlobalShape(std::string name, shapes shapeType, std::shared_ptr<ObjectMover> mover,
                   std::shared_ptr<Layer> layer, int parent);
    bool animating;
};


