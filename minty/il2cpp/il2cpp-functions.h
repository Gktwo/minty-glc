#include "il2cpp-types.h"
#include "il2cpp-enum.h"


using namespace app;


//globalupdate
//UnityEngine.EventSystems.EventSystem$$Update
DO_APP_FUNC(0x024E4CF0,  void, EventSystem_Update, ( app::UnityEngine_EventSystems_EventSystem_o* __this, app::MethodInfo* method));









//UnityEngine.UI.Text$$
//DO_APP_FUNC(0x022dcc00, void, Text_set_text, (app::Text* __this, app::String* value));
//////UnityEngine.UI.Text$$set_text
//DO_APP_FUNC(0x024DD020, void, Text_set_alignment, (app::Text* __this, app::TextAnchor__Enum value));
//DO_APP_FUNC(0x024DD270, void, Text_set_horizontalOverflow, (app::Text* __this, app::HorizontalWrapMode__Enum value));
//DO_APP_FUNC(0x024DD5A0, void, Text_set_verticalOverflow, (app::Text* __this, app::VerticalWrapMode__Enum value));
//DO_APP_FUNC(0x024DD330, void, Text_set_resizeTextForBestFit, (app::Text* __this, bool value));
//DO_APP_FUNC(0x024DD090, void, Text_set_fontSize, (app::Text* __this, int32_t value));
//UnityEngine.UI.Slider
//DO_APP_FUNC(0x024DA1B0, void, Slider_set_minValue, (app::Slider_1* __this, float value));
//DO_APP_FUNC(0x024D9EA0, void, Slider_set_maxValue, (app::Slider_1* __this, float value));
//DO_APP_FUNC(0x024DA290, void, Slider_set_value, (app::Slider_1* __this, float value));



//System.Runtime.InteropServices.Marshal$$PtrToStringAnsi
DO_APP_FUNC(0x0183C260, app::String*, Marshal_PtrToStringAnsi, (void* ptr));




// Game Object, Transform, Object, Component Utility

//public sealed class GameObject :
//UnityEngine.GameObject$$CreatePrimitive
DO_APP_FUNC(0x0223A220, app::GameObject*, GameObject_CreatePrimitive, (app::PrimitiveType__Enum type));
//UnityEngine.GameObject$$get_active
DO_APP_FUNC(0x0223B110, bool, GameObject_get_active, (app::GameObject* __this));
//UnityEngine.GameObject$$SetActive
DO_APP_FUNC(0x0223B370 ,void, GameObject_SetActive, (app::GameObject* __this, bool value));
//UnityEngine.GameObject$$Find
DO_APP_FUNC(0x0223A2E0, app::GameObject*, GameObject_Find, (app::String* name));

DO_APP_FUNC(0x0223A320, app::Component*, GameObject_GetComponentByName, (app::GameObject* __this, app::String* className));
//UnityEngine.GameObject$$GetComponentByName
DO_APP_FUNC(0x02239FB0, app::Component*, GameObject_AddComponentInternal, (app::GameObject* __this, app::String* className));
//UnityEngine.GameObject$$AddComponentInternal

//UnityEngine.GameObject$$get_transform
DO_APP_FUNC(0x0223B330, app::Transform*, GameObject_get_transform, (app::GameObject* __this));



DO_APP_FUNC(0x022718B0, app::Transform*, Transform_GetChild, (app::Transform* __this, int32_t index));
//UnityEngine.Transform$$GetChild
// 
DO_APP_FUNC(0x02271870, int32_t, Transform_GetChildCount, (app::Transform* __this));
//UnityEngine.Transform$$GetChildCount

//UnityEngine.Transform$$FindChild
DO_APP_FUNC(0x02271770, app::Transform*, Transform_FindChild, (app::Transform* __this, app::String* name));

DO_APP_FUNC(0x02274CE0, void, Transform_set_localPosition, (app::Transform* __this, app::Vector3 value));
DO_APP_FUNC(0x02274400, app::Vector3, Transform_get_localPosition, (app::Transform* __this, app::MethodInfo* method));

DO_APP_FUNC(0x02274D80, void, Transform_set_localRotation, (app::Transform* __this, app::Quaternion value));
DO_APP_FUNC(0x022744A0, app::Quaternion, Transform_get_localRotation, (app::Transform* __this, app::MethodInfo* method));


DO_APP_FUNC(0x02274540, app::Vector3, Transform_get_localScale, (app::Transform* __this));
DO_APP_FUNC(0x02274E20, void, Transform_set_localScale, (app::Transform* __this, app::Vector3 value));

DO_APP_FUNC(0x02274780, app::Vector3, Transform_get_right, (app::Transform* __this));
DO_APP_FUNC(0x022748F0, app::Vector3, Transform_get_up, (app::Transform* __this));
DO_APP_FUNC(0x02274150, app::Vector3, Transform_get_forward, (app::Transform* __this));

DO_APP_FUNC(0x02274730, app::Vector3, Transform_get_position, (app::Transform* __this));
DO_APP_FUNC(0x02274F80, void, Transform_set_position, (app::Transform* __this, app::Vector3 value));

DO_APP_FUNC(0x022748A0, app::Quaternion, Transform_get_rotation, (app::Transform* __this));
DO_APP_FUNC(0x022750D0, void, Transform_set_rotation, (app::Transform* __this, app::Quaternion value));

DO_APP_FUNC(0x02271A80, app::Transform*, Transform_get_parent, (app::Transform* __this));
DO_APP_FUNC(0x02274E70, void, Transform_set_parent, (app::Transform* __this, app::Transform* value));

DO_APP_FUNC(0x02273D60, void, Transform_Translate, (app::Transform* __this, app::Vector3 translation));
////UnityEngine.Object$$get_name
DO_APP_FUNC(0x02240280, app::String*, Object_get_name, (app::Object* __this));
////UnityEngine.Object$$DestroyImmediate
DO_APP_FUNC(0x0223E170, void, Object_1_DestroyImmediate_1, (app::Object* obj));
////UnityEngine.Component$$get_gameObject
DO_APP_FUNC(0x02236900, app::GameObject*, Component_get_gameObject, (app::Component* __this));


// UnityEngine.RenderSettings$$set_fog
DO_APP_FUNC(0x02211810, void, RenderSettings_set_fog, (bool value));
//public static void set_fog(bool value) { }

//public class Time
DO_APP_FUNC(0x02249080,  float, Time_get_deltaTime, ());
//public static float get_deltaTime() { }
DO_APP_FUNC(0x02249380, float, Time_get_timeScale, ());
//public static float get_timeScale() { }
DO_APP_FUNC(0x02249630, void*, Time_set_timeScale, (float time));


DO_APP_FUNC(0x021CBBF0, bool, Application_get_isFocused, ());
//public static bool get_isFocused() { }
DO_APP_FUNC(0x021CC910, void, Application_set_targetFrameRate, (int32_t value));
//	public static void set_targetFrameRate(int value) { }
DO_APP_FUNC(0x022108B0,  void, QualitySettings_set_vSyncCount, (int32_t value));

//UnityEngine.Vector3$$Distance
DO_APP_FUNC(0x02232EE0,  float, Vector3_Distance, (app::Vector3 pos1, app::Vector3 pos2));

DO_APP_FUNC(0x02233280, app::Vector3, Vector3_Lerp, (app::Vector3 start, app::Vector3 end, float time));


//public class Cursor
DO_APP_FUNC(0x02222F80, void, Cursor_set_visible, (bool value));
DO_APP_FUNC(0x02222F10, bool, Cursor_get_visible, ());
//public static void set_visible(bool value) { }
DO_APP_FUNC(0x02222EE0, app::CursorLockMode__Enum, Cursor_get_lockState, ());
//public static CursorLockMode get_lockState() { }
DO_APP_FUNC(0x02222F40, void, Cursor_set_lockState, (app::CursorLockMode__Enum value));
//public static void set_lockState(CursorLockMode value) { }

//public sealed class Screen
DO_APP_FUNC(0x021F3860,  int32_t, Screen_get_width, (app::MethodInfo* method));
//	 public static int get_width() { }
DO_APP_FUNC(0x021F36C0, int32_t, Screen_get_height, (app::MethodInfo* method));
//public static int get_height() { }
DO_APP_FUNC(0x021F3360,  void, Screen_SetResolution, (int32_t width, int32_t height, bool fullscreen));








// Protection bypass


