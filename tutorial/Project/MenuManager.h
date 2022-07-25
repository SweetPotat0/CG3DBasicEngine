#include "Project.h"

class MenuManager
{
public:
    enum CameraSplitMode
    {
        no_split,
        split_x,
        split_y
    };

    static void OnCameraSplitChange(int splitMode, Project *scn)
    {
        switch (splitMode)
        {
        case CameraSplitMode::no_split:
            // implement
            break;
        case CameraSplitMode::split_x:
            // implement
            break;
        case CameraSplitMode::split_y:
            // implement
            break;
        default:
            // error
            break;
        }
    }

    static void OnTransparentToggled(bool isTransparent, Project *scn)
    {
    }

    static void OnAddCamera(std::string camera_name, Project *scn)
    {
        std::cout << "added camera" << camera_name << std::endl;
    }

    static void OnAddLayer(std::string layer_name, bool is_shown, Project *scn)
    {
        std::vector<int> layerShapes;
        Layer* layer = new Layer(is_shown, layer_name, layerShapes);
        scn->layers.push_back(layer);
    }

    static void OnLayerChange(std::string layer_name, bool is_shown, Project *scn)
    {
        for(Layer* layer : scn->layers){
            if(layer->getName() == layer_name){
                layer->setIsVisible(!is_shown);
                break;
            }
        }
    }

    static void OnSelectMaterial(int material_inx, Project *scn)
    {
    }

    static void OnPlayChanged(bool play, Project *scn)
    {
    }

    static void OnSetLayer(std::string layer_name, Project *scn)
    {
        std::cout << "Set layer: " << layer_name << ", num of picked: " << scn->pickedShapes.size() << std::endl;
        for(int shapeIndex : scn->pickedShapes){
            scn->shapesGlobal[shapeIndex]->getLayer()->removeShape(shapeIndex);
            scn->shapesGlobal[shapeIndex]->changeLayer(layer_name);
            scn->shapesGlobal[shapeIndex]->getLayer()->addShape(shapeIndex);
        }
    }
};