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
        for (size_t i = 0; i < scn->pShapes.size(); i++)
        {
            int shapeIndx = scn->pShapes[i];
            scn->shapesGlobal[shapeIndx].isTransparent = isTransparent;
        }
    }

    static void OnBlurToggled(bool isBlurred, Project *scn)
    {
        for (size_t i = 0; i < scn->pShapes.size(); i++)
        {
            int shapeIndx = scn->pShapes[i];
            if (isBlurred == true)
            {
                scn->SetShapeShader(shapeIndx, scn->blurShaderIndx);
            }
            else
            {
                scn->SetShapeShader(shapeIndx, scn->basicShaderIndx);
            }
        }
    }

    static void OnAddCamera(std::string camera_name, Project *scn)
    {
        std::cout << "added camera" << camera_name << std::endl;
    }

    static void OnAddLayer(std::string layer_name, bool is_shown, Project *scn)
    {
        std::vector<int> layerShapes;
        Layer *layer = new Layer(is_shown, layer_name, layerShapes);
        scn->layers.push_back(layer);
    }

    static void OnLayerChange(std::string layer_name, bool is_visible, Project *scn)
    {
        for (Layer *layer : scn->layers)
        {
            if (layer->getName() == layer_name)
            {
                layer->setIsVisible(is_visible);
                break;
            }
        }
    }

    static void OnSetLayer(std::string layer_name, Project *scn)
    {
        std::cout << "Set layer: " << layer_name << ", num of picked: " << scn->pShapes.size() << std::endl;
        Layer *changedLayer;
        for (size_t i = 0; i < scn->layers.size(); i++)
        {
            if(scn->layers[i]->getName() == layer_name){
                changedLayer = scn->layers[i];
                break;
            }
        }
        for (int shapeIndex : scn->pShapes)
        {
            scn->shapesGlobal[shapeIndex].getLayer()->removeShape(shapeIndex);
            scn->shapesGlobal[shapeIndex].changeLayer(changedLayer);
            scn->shapesGlobal[shapeIndex].getLayer()->addShape(shapeIndex);
        }
    }
    static void OnSelectMaterial(int material_inx, Project *scn)
    {
        for (size_t i = 0; i < scn->pShapes.size(); i++)
        {
            int shpIndex = scn->pShapes[i];
            scn->SetShapeMaterial(shpIndex, material_inx);
        }
    }

    static void OnPlayChanged(bool play, Project *scn)
    {
        scn->globalTime = 0;
    }
};