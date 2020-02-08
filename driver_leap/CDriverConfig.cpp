#include "stdafx.h"
#include "CDriverConfig.h"
#include "Utils.h"

extern char g_modulePath[];

bool CDriverConfig::ms_enabled = true;
unsigned char CDriverConfig::ms_emulatedController = CDriverConfig::EC_Vive;
bool CDriverConfig::ms_leftHand = true;
bool CDriverConfig::ms_rightHand = true;
unsigned char CDriverConfig::ms_orientation = CDriverConfig::OM_HMD;
float CDriverConfig::ms_desktopRootX = 0.f;
float CDriverConfig::ms_desktopRootY = 0.f;
float CDriverConfig::ms_desktopRootZ = 0.f;
float CDriverConfig::ms_rotationOffsetX = 0.f;
float CDriverConfig::ms_rotationOffsetY = 0.f;
float CDriverConfig::ms_rotationOffsetZ = 0.f;
bool CDriverConfig::ms_skeleton = true;
unsigned char CDriverConfig::ms_trackingLevel = CDriverConfig::TL_Partial;
bool CDriverConfig::ms_input = true;
bool CDriverConfig::ms_menu = true;
bool CDriverConfig::ms_applicationMenu = true;
bool CDriverConfig::ms_trigger = true;
bool CDriverConfig::ms_grip = true;
bool CDriverConfig::ms_touchpad = true;
bool CDriverConfig::ms_touchpadTouch = true;
bool CDriverConfig::ms_touchpadPress = true;
bool CDriverConfig::ms_touchpadAxes = true;
bool CDriverConfig::ms_buttonA = true;
bool CDriverConfig::ms_buttonB = true;
bool CDriverConfig::ms_thumbstick = true;
bool CDriverConfig::ms_vrchatHandsReset = false;

const std::vector<std::string> g_configAttributes
{
    "enabled", "emulated_controller", "leftHand", "rightHand",
    "orientation", "desktopRoot", "rotationOffset",
    "skeleton", "trackingLevel",
    "input", "menu", "appMenu", "trigger", "grip",
    "touchpad", "touchpadTouch", "touchpadPress", "touchpadAxes",
    "buttonA", "buttonB", "thumbstick",
    "vrchat_handsReset"
};
enum ConfigParamIndex : size_t
{
    CPI_Enabled = 0U,
    CPI_EmulatedController,
    CPI_LeftHand,
    CPI_RightHand,
    CPI_Orientation,
    CPI_DesktopRoot,
    CPI_RotationOffset,
    CPI_Skeleton,
    CPI_TrackingLevel,
    CPI_Input,
    CPI_Menu,
    CPI_ApplicationMenu,
    CPI_Trigger,
    CPI_Grip,
    CPI_Touchpad,
    CPI_TouchpadTouch,
    CPI_TouchpadPress,
    CPI_TouchpadAxes,
    CPI_ButtonA,
    CPI_ButtonB,
    CPI_Thumbstick,
    CPI_VRChatHandsReset
};
const std::vector<std::string> g_orientationModes
{
    "hmd", "desktop"
};
const std::vector<std::string> g_emulatedControllers
{
    "vive", "index"
};
const std::vector<std::string> g_trackingLevels
{
    "partial", "full"
};

void CDriverConfig::LoadConfig()
{
    std::string l_path(g_modulePath);
    l_path.erase(l_path.begin() + l_path.rfind('\\'), l_path.end());
    l_path.append("\\..\\..\\resources\\settings.xml");

    pugi::xml_document *l_config = new pugi::xml_document();
    if(l_config->load_file(l_path.c_str()))
    {
        pugi::xml_node l_root = l_config->child("settings");
        if(l_root)
        {
            for(pugi::xml_node l_node = l_root.child("setting"); l_node; l_node = l_node.next_sibling("setting"))
            {
                pugi::xml_attribute l_attribName = l_node.attribute("name");
                pugi::xml_attribute l_attribValue = l_node.attribute("value");
                if(l_attribName && l_attribValue)
                {
                    switch(ReadEnumVector(l_attribName.as_string(), g_configAttributes))
                    {
                        case ConfigParamIndex::CPI_Enabled:
                            ms_enabled = l_attribValue.as_bool(true);
                            break;
                        case ConfigParamIndex::CPI_EmulatedController:
                        {
                            size_t l_tableIndex = ReadEnumVector(l_attribValue.as_string(), g_emulatedControllers);
                            if(l_tableIndex != std::numeric_limits<size_t>::max()) ms_emulatedController = static_cast<unsigned char>(l_tableIndex);
                        } break;
                        case ConfigParamIndex::CPI_LeftHand:
                            ms_leftHand = l_attribValue.as_bool(true);
                            break;
                        case ConfigParamIndex::CPI_RightHand:
                            ms_rightHand = l_attribValue.as_bool(true);
                            break;
                        case ConfigParamIndex::CPI_Orientation:
                        {
                            size_t l_tableIndex = ReadEnumVector(l_attribValue.as_string(), g_orientationModes);
                            if(l_tableIndex != std::numeric_limits<size_t>::max()) ms_orientation = static_cast<unsigned char>(l_tableIndex);
                        } break;
                        case ConfigParamIndex::CPI_DesktopRoot:
                        {
                            std::stringstream l_desktopRoot(l_attribValue.as_string());
                            l_desktopRoot >> ms_desktopRootX >> ms_desktopRootY >> ms_desktopRootZ;
                        } break;
                        case ConfigParamIndex::CPI_RotationOffset:
                        {
                            std::stringstream l_offset(l_attribValue.as_string());
                            l_offset >> ms_rotationOffsetX >> ms_rotationOffsetY >> ms_rotationOffsetZ;
                        } break;
                        case ConfigParamIndex::CPI_Skeleton:
                            ms_skeleton = l_attribValue.as_bool(true);
                            break;
                        case ConfigParamIndex::CPI_TrackingLevel:
                        {
                            size_t l_tableIndex = ReadEnumVector(l_attribValue.as_string(), g_trackingLevels);
                            if(l_tableIndex != std::numeric_limits<size_t>::max()) ms_trackingLevel = static_cast<unsigned char>(l_tableIndex);
                        } break;
                        case ConfigParamIndex::CPI_Input:
                            ms_input = l_attribValue.as_bool(true);
                            break;
                        case ConfigParamIndex::CPI_Menu:
                            ms_menu = l_attribValue.as_bool(true);
                            break;
                        case ConfigParamIndex::CPI_ApplicationMenu:
                            ms_applicationMenu = l_attribValue.as_bool(true);
                            break;
                        case ConfigParamIndex::CPI_Trigger:
                            ms_trigger = l_attribValue.as_bool(true);
                            break;
                        case ConfigParamIndex::CPI_Grip:
                            ms_grip = l_attribValue.as_bool(true);
                            break;
                        case ConfigParamIndex::CPI_Touchpad:
                            ms_touchpad = l_attribValue.as_bool(true);
                            break;
                        case ConfigParamIndex::CPI_TouchpadTouch:
                            ms_touchpadTouch = l_attribValue.as_bool(true);
                            break;
                        case ConfigParamIndex::CPI_TouchpadPress:
                            ms_touchpadPress = l_attribValue.as_bool(true);
                            break;
                        case ConfigParamIndex::CPI_TouchpadAxes:
                            ms_touchpadAxes = l_attribValue.as_bool(true);
                            break;
                        case ConfigParamIndex::CPI_ButtonA:
                            ms_buttonA = l_attribValue.as_bool(true);
                            break;
                        case ConfigParamIndex::CPI_ButtonB:
                            ms_buttonB = l_attribValue.as_bool(true);
                            break;
                        case ConfigParamIndex::CPI_Thumbstick:
                            ms_thumbstick = l_attribValue.as_bool(true);
                            break;
                        case ConfigParamIndex::CPI_VRChatHandsReset:
                            ms_vrchatHandsReset = l_attribValue.as_bool(false);
                            break;
                    }
                }
            }
        }
    }
    delete l_config;
}
