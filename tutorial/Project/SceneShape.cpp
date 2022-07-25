//
// Created by ditto on 28/06/2022.
//

#include "SceneShape.h"

Layer::Layer(bool isVisible, std::string layerName, std::vector<int> layerShapes) : isVisible(isVisible), layerName(layerName), layerShapes(layerShapes) {}

std::string Layer::getName()
{
    return this->layerName;
}

void Layer::setName(std::string name)
{
    this->layerName = name;
}

bool Layer::getIsVisible()
{
    return this->isVisible;
}

void Layer::setIsVisible(bool toSet)
{
    this->isVisible = toSet;
}
std::vector<int> Layer::getLayerShapes()
{
    return this->layerShapes;
}

void Layer::addShape(int shapeIndex)
{
    this->layerShapes.push_back(shapeIndex);
}

void Layer::removeShape(int shapeIndex)
{
    std::vector<int> layerShapes;
    for (int num : this->layerShapes)
    {
        if (num != shapeIndex)
            layerShapes.push_back(num);
    }
    this->layerShapes = layerShapes;
}

SceneShape::SceneShape(std::string shapeName, igl::opengl::glfw::Viewer::shapes shapeType,
                       Layer *layer, int index) : name(shapeName), type(shapeType),
                                                  layer(layer), index(index), NextPlaceIndex(0)
{
    //currentPosition(Eigen::Vector4f(0, 0, 0, 0))
}
Layer
    *
    SceneShape::getLayer()
{
    return layer;
}
void SceneShape::changeLayer(std::string layer_name)
{
    this->layer->setName(layer_name);
}
int SceneShape::getIndex()
{
    return index;
}

void SceneShape::addPlaces(const Eigen::Vector3f pos)
{
    const int tempNext = NextPlaceIndex;
    // this->movement.push_back(Eigen::Vector4f(pos, tempNext));
    this->NextPlaceIndex++;
}

SceneShape *SceneShape::getParent()
{
    return parent;
}

void SceneShape::removeParent()
{
    // currentPosition = getCurrentPositionAt(0);
    parent = nullptr;
}

void SceneShape::setParent(SceneShape *newParent)
{
    parent = newParent;
    currentPosition = currentPosition - newParent->getCurrentPosition();
    parent->addChild(this);
}

std::vector<SceneShape *> SceneShape::getChildren()
{
    return children;
}

// Eigen::Vector4f SceneShape::getCurrentPositionAt(float time)
// {
//     if (parent == nullptr)
//         return getPosition(time);
//     else
//         return (getPosition(time) + this->parent->getCurrentPositionAt(time));
// }

Eigen::Vector4f SceneShape::getCurrentPosition()
{
    return currentPosition;
}

void SceneShape::removePlace(int index)
{
    for (int i = 0; i < movement.size(); i++)
        if (index == movement[i].w())
            this->movement.erase(movement.begin() + i);
}

void SceneShape::addChild(SceneShape *child)
{
    children.push_back(child);
}

void SceneShape::removeChild(SceneShape *removedChild)
{
    std::vector<SceneShape *> newChildren;
    for (SceneShape *child : children)
    {
        if (child != removedChild)
            newChildren.push_back(child);
    }
    children = newChildren;
}
/// move object
int BinomialCoefficient(const int n, const int k)
{
    if (k == 0)
        return 1;
    std::vector<int> aSolutions(k);
    aSolutions[0] = n - k + 1;

    for (int i = 1; i < k; ++i)
    {
        aSolutions[i] = aSolutions[i - 1] * (n - k + 1 + i) / (i + 1);
    }

    return aSolutions[k - 1];
}
Eigen::Vector3f SceneShape::getPosition(float time)
{
    return Eigen::Vector3f(3,3,3);
//     float n = this->movement.size();
//     // Eigen::Vector3f pos = Eigen::Vector3f(0, 0, 0);
//     // for (std::size_t i = 0; i < n; i++)
//     // {
//     //     pos += BinomialCoefficient(n, i) * pow((1 - time), n - i) * pow(time, i) * movement[i];
//     // }
//     // return pos;
//     return Eigen::Vector3f(4);
}
