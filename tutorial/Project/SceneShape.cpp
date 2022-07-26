#include "SceneShape.h"

SceneShape::SceneShape(std::string shapeName, igl::opengl::glfw::Viewer::shapes shapeType,
                       std::shared_ptr<ObjectMover> mover, std::shared_ptr<Layer> layer, int index, igl::opengl::glfw::Viewer* parentViewer) :
                       name(shapeName), type(shapeType), mover(ObjectMoverSplit(mover)),
                       layer(layer), index(index), parentViewer(parentViewer) {}

std::shared_ptr<Layer> SceneShape::getLayer() {
    return layer;
}
void SceneShape::changeLayer(std::shared_ptr<Layer> layer) {
    this->layer = layer;
}
int SceneShape::getIndex() {
    return index;
}


bool SceneShape::isDrawn(float time) {
    return mover.isDrawnAt(time);
}

Eigen::Vector3f SceneShape::getPosition(float time) {
    return mover.getPosition(time);
}

Eigen::Vector3f SceneShape::getlastDrawnPosition() {
    return lastDrawnPosition;
}

void SceneShape::setlastDrawnPosition(Eigen::Vector3f pos) {
    lastDrawnPosition = pos;
}

void SceneShape::addMover(std::shared_ptr<ObjectMover> mover) {
    this->mover.addMover(mover);

}

int SceneShape::getParent() {
    return parent;
}

void SceneShape::setParent(int newParent) {
    parent = newParent;
}

std::vector<int> SceneShape::getChildren() {
    return children;
}

void SceneShape::addChild(int child) {
    children.push_back(child);
}

void SceneShape::removeChild(int removedChild) {
    std::vector<int> newChildren;
    for(int child : children) {
        if(child != removedChild)
            newChildren.push_back(child);
    }
    children = newChildren;
}

void SceneShape::moveShape(Eigen::Vector3d moveTo) {
    std::cout<<"____________________________________________"<< index<<std::endl;
    parentViewer->data(0)->MyTranslate(moveTo,true);
}


