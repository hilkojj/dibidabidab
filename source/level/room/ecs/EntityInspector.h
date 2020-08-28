
#ifndef GAME_ENTITYINSPECTOR_H
#define GAME_ENTITYINSPECTOR_H


#include <graphics/camera.h>
#include <graphics/3d/debug_line_renderer.h>
#include "../../../../external/entt/src/entt/entity/registry.hpp"
#include "../../../macro_magic/component.h"

struct InspectPathState
{
    bool multiline = false;
    std::string newKey;
};

COMPONENT(Inspecting, HASH(0),
    FIELD_DEF_VAL(bool, show, true),

    FIELD(json, addingComponentJson)
)
    std::map<const char *, bool> freezeComponent;
    std::map<const char *, json> frozenComponentContents;

    std::string addingComponentTypeName;

    std::vector<std::string> currentPath;
    std::map<std::string, InspectPathState> state;

    InspectPathState &getState()
    {
        std::string pathKey;
        for (auto &s : currentPath) pathKey += "--->" + s;
        return state[pathKey];
    }

END_COMPONENT(Inspecting)

class EntityInspector
{
    entt::registry &reg;

  public:

    bool
        pickEntity = false,
        moveEntity = false;

    entt::entity movingEntity = entt::null;

    std::vector<std::string> entityTemplates;
    std::string templateToCreate = "", templateToEdit = "";

    EntityInspector(entt::registry &reg);

    void drawGUI(const Camera *cam, DebugLineRenderer &lineRenderer);

  private:
    void pickEntityGUI(const Camera *cam, DebugLineRenderer &lineRenderer);

    void moveEntityGUI(const Camera *cam, DebugLineRenderer &lineRenderer);

    void drawEntityInspectorGUI(entt::entity e, Inspecting &ins);

    void drawComponentFieldsTree(entt::entity e, Inspecting &ins, const char *componentName, const ComponentUtils *componentUtils);

    void drawAddComponent(entt::entity e, Inspecting &ins, const char *popupName);
};


#endif