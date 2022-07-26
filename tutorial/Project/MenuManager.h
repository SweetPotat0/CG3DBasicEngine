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
        for (size_t i = 0; i < scn->pickedShapes.size(); i++)
        {
            int shapeIndx = scn->pickedShapes[i];
            scn->shapesGlobal[shapeIndx].isTransparent = isTransparent;
        }
    }

    static void OnBlurToggled(bool isBlurred, Project *scn)
    {
        for (size_t i = 0; i < scn->pickedShapes.size(); i++)
        {
            int shapeIndx = scn->pickedShapes[i];
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
    }

    static void OnLayerChange(std::string layer_name, bool is_shown, Project *scn)
    {
    }

    static void OnSelectMaterial(int material_inx, Project *scn)
    {
        for (size_t i = 0; i < scn->pickedShapes.size(); i++)
        {
            int shpIndex = scn->pickedShapes[i];
            scn->SetShapeMaterial(shpIndex, material_inx);
        }
    }

    static void OnPlayChanged(bool play, Project *scn)
    {
    }

    static void OnSetLayer(std::string layer_name, Project *scn)
    {
        std::cout << "Set layer: " << layer_name << ", num of picked: " << scn->pickedShapes.size() << std::endl;
    }
};