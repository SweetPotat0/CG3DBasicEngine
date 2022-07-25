#pragma once

#include <Eigen/Core>
#include "igl/opengl/glfw/Viewer.h"
#include "ObjectMover.h"

class Layer {
public:
    Layer(bool isVisible, std::string layerName, std::vector<int> layerShapes);
    std::string getName();
    void setName(std::string name);
    bool getIsVisible();
    void setIsVisible(bool toSet);
    void addShape(int shapeIndex);
    void removeShape(int shapeIndex);
    std::vector<int> getLayerShapes();
private:
    bool isVisible;
    std::string layerName;
    std::vector<int> layerShapes;
};

class SceneShape {
public:
    SceneShape(std::string shapeName, igl::opengl::glfw::Viewer::shapes shapeType, Layer* layer, int index);
    Layer* getLayer();
    void changeLayer(std::string layer_name);
    int getIndex();
    void addPlaces(Eigen::Vector3f pos);
    bool isDrawn(float time);
    Eigen::Vector3f getPosition(float time);
    // void setlastDrawnPosition(Eigen::Vector3f pos);
    SceneShape* getParent();
    void removeParent();
    void removeChild();
    void setParent(SceneShape* newParent);
    void addChild(SceneShape* child);
    void removeChild(SceneShape* child);
    std::vector<SceneShape*> getChildren();
    // Eigen::Vector4f getCurrentPositionAt(float time);
    Eigen::Vector4f getCurrentPosition();
    void removePlace(int index);
    // from mover 
    Eigen::Vector3f getpoints(float time);
    bool isTransparent = false;


private:
    std::string name;
    igl::opengl::glfw::Viewer::shapes type;
    std::vector<Eigen::Vector4f> movement;
    Eigen::Vector4f currentPosition;
    Layer* layer;
    int index;
    SceneShape* parent;
    int NextPlaceIndex;
    std::vector<SceneShape*> children;
    float startTime;
    float endTime;
    





};
