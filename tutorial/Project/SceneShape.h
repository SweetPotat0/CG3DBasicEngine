
#ifndef ASSIGNMENT1_CPP_SCENESHAPE_H
#define ASSIGNMENT1_CPP_SCENESHAPE_H

#include <Eigen/Core>
#include "igl/opengl/glfw/Viewer.h"

enum directions{
    x,y,z
};

class Layer {
public:
    bool isVisible;
};

class SceneShape {
public:
    SceneShape(std::string shapeName, igl::opengl::glfw::Viewer::shapes shapeType,
               std::shared_ptr<Layer> layer, int index, igl::opengl::glfw::Viewer* viewer);
    std::shared_ptr<Layer> getLayer();
    void changeLayer(std::shared_ptr<Layer> layer);
    int getIndex();
    void addPlaces(Eigen::Vector3f pos);
    bool isDrawn(float time);
    Eigen::Vector3f getPosition(float time);
    Eigen::Vector3f getlastDrawnPosition();
    void setlastDrawnPosition(Eigen::Vector3f pos);
    SceneShape* getParent();
    void removeParent();
    void removeChild();
    void setParent(SceneShape* newParent);
    void addChild(SceneShape* child);
    void removeChild(SceneShape* child);
    std::vector<SceneShape*> getChildren();
    Eigen::Vector3f getCurrentPositionAt(float time);
    Eigen::Vector3f getCurrentPosition();
    void removePlace(int index);
    // from mover
    Eigen::Vector3f getpoints(float time);

    //edit mode movment:
    void move(double shiftSize,directions d);


private:
    std::string name;
    igl::opengl::glfw::Viewer::shapes type;
    std::vector<Eigen::Vector4f> movement;
    Eigen::Vector3f currentPosition;
    igl::opengl::glfw::Viewer* viewer;
    //ObjectMoverSplit mover;
    std::shared_ptr<Layer> layer;
    int index;
     Eigen::Vector3f lastDrawnPosition;
    SceneShape* parent;
    int NextPlaceIndex;
    std::vector<SceneShape*> children;
    float startTime;
    float endTime;




};
#endif //ASSIGNMENT1_CPP_SCENESHAPE_H