#include "FreeCamera.h"

namespace cheat {
    static void onGameUpdateFreeCamera(app::EventSystem* __this, app::MethodInfo* method);

    app::GameObject* freeCam = nullptr;
    app::GameObject* mainCam = nullptr;
    app::Object_1* freeCamObj = nullptr;
    //app::Object_1* mainCamObj = nullptr;

    app::Transform* freeCam_Transform;
    app::Component_1* freeCam_Camera;
    app::Component_1* mainCam_Camera;
    app::Vector3 targetPosition;
    app::Vector3 smoothPosition;
    float smoothFOV = 0;
    double focalLength = 0;
    bool FCamisEnabled = false;

    FreeCamera::FreeCamera() {
        f_Enabled = config::getValue("functions:FreeCamera", "enabled", false);
        //f_FreezeAnimation = config::getValue("functions:FreeCamera", "freezeAnimation", false);
        // f_SetAvatarInvisible = config::getValue("functions:FreeCamera", "setAvatarInvisible", false);
        // f_BlockInput = config::getValue("functions:FreeCamera", "blockInput", false);
        f_MoveSpeed = config::getValue("functions:FreeCamera", "moveSpeed", 1.0f);
        f_LookSens = config::getValue("functions:FreeCamera", "lookSens", 1.0f);
        f_RollSpeed = config::getValue("functions:FreeCamera", "rollSpeed", 1.0f);
        f_FOVSpeed = config::getValue("functions:FreeCamera", "fovSpeed", 0.1f);
        f_FOV = config::getValue("functions:FreeCamera", "fov", 45.0f);
        f_MovSmoothing = config::getValue("functions:FreeCamera", "movSmoothing", 1.0f);
        f_LookSmoothing = config::getValue("functions:FreeCamera", "lookSmoothing", 1.0f);
        f_RollSmoothing = config::getValue("functions:FreeCamera", "rollSmoothing", 1.0f);
        f_FovSmoothing = config::getValue("functions:FreeCamera", "fovSmoothing", 1.0f);

        f_Forward = Hotkey("functions:FreeCamera:Inspector:Mover:up", 'W');
        f_Backward = Hotkey("functions:FreeCamera:Inspector:Mover:down", 'S');
        f_Left = Hotkey("functions:FreeCamera:Inspector:Mover:left", 'A');
        f_Right = Hotkey("functions:FreeCamera:Inspector:Mover:right", 'D');
        f_Up = Hotkey("functions:FreeCamera:Inspector:Mover:up", VK_SPACE);
        f_Down = Hotkey("functions:FreeCamera:Inspector:Mover:down", VK_LCONTROL);
        f_IncFOV = Hotkey("functions:FreeCamera:Inspector:Mover:up", VK_ADD);
        f_DecFOV = Hotkey("functions:FreeCamera:Inspector:Mover:down", VK_SUBTRACT);
        f_LeftRoll = Hotkey("functions:FreeCamera:Inspector:Mover:left", VK_LEFT);
        f_RightRoll = Hotkey("functions:FreeCamera:Inspector:Mover:right", VK_RIGHT);
        f_ResetRoll = Hotkey("functions:FreeCamera:Inspector:Mover:down", VK_NUMPAD0);

        f_Hotkey = Hotkey("functions:FreeCamera");

        HookManager::install(app::EventSystem_Update, onGameUpdateFreeCamera);
    }

    FreeCamera& FreeCamera::getInstance() {
        static FreeCamera instance;
        return instance;
    }

    void FreeCamera::GUI() {
        if (ConfigCheckbox(_("freecamera"), f_Enabled, _("freecamera"))) {
            ImGui::SameLine();
            f_Hotkey.Draw();
            ImGui::Indent();
            //ConfigCheckbox(_("FreezeAnimation"), f_FreezeAnimation, _("FreezeAnimation"));
            //ConfigCheckbox(_("Make Character invisible"), f_SetAvatarInvisible, _("Make Character invisible"));
            // ConfigCheckbox(_("Block User Input"), f_BlockInput, _("If enabled, any input will be blocked"));
            ConfigSliderFloat(_("MoveSpeed"), f_MoveSpeed, 0.1f, 30.0f, "PosMover Speed");
            ConfigSliderFloat(_("LookSens"), f_LookSens, 0.1f, 100.0f, "Look Sensitivity");
            ConfigSliderFloat(_("RollSpeed"), f_RollSpeed, 0.1f, 100.0f, "Roll Speed");
            ConfigSliderFloat(_("FOVSpeed"), f_FOVSpeed, 0.1f, 100.0f, "FOV Speed");
            ConfigInputFloat(_("FOV"), f_FOV, 0.1f, 200.0f, "Field of View");

            if (BeginGroupPanel("Hotkeys", true)) {
                f_Forward.Draw(_("forward"));
                ImGui::SameLine();
                f_Backward.Draw(_("backward"));
                f_Left.Draw(_("left"));
                ImGui::SameLine();
                f_Right.Draw(_("right"));
                f_Up.Draw(_("up"));
                ImGui::SameLine();
                f_Down.Draw(_("down"));
                f_IncFOV.Draw(_("IncreaseFOV"));
                ImGui::SameLine();
                f_DecFOV.Draw(_("DecreaseFOV"));
                f_LeftRoll.Draw(_("leftRoll"));
                ImGui::SameLine();
                f_RightRoll.Draw(_("rightRoll"));
                f_ResetRoll.Draw(_("resetRoll"));
            }
            EndGroupPanel();

            ImGui::Unindent();
        }
    }

    void FreeCamera::Outer() {
        if (f_Hotkey.IsDown())
            f_Enabled.setValue(!f_Enabled.getValue());
    }

    void FreeCamera::Status() {
        if (f_Enabled)
            ImGui::Text(_("FreeCamera"));
    }

    std::string FreeCamera::getModule() {
        return _("MODULE_VISUALS");
    }

    class CameraRotation {
    public:
        float pitch, yaw, roll;

        void InitializeFromTransform(app::Transform* t) {
            auto t_eulerAngles = app::Transform_get_eulerAngles(t, nullptr);
            pitch = t_eulerAngles.x;
            yaw = t_eulerAngles.y;
            roll = t_eulerAngles.z;
        }

        void LerpTowards(CameraRotation target, float lookRotationLerpPct, float rollRotationLerpPct) {
            yaw = app::Mathf_Lerp(yaw, target.yaw, lookRotationLerpPct,nullptr);
            pitch = app::Mathf_Lerp(pitch, target.pitch, lookRotationLerpPct, nullptr);
            roll = app::Mathf_Lerp(roll, target.roll, rollRotationLerpPct, nullptr);
        }

        void UpdateTransform(app::Transform* t) {
            app::Transform_set_eulerAngles(t, app::Vector3{pitch, yaw, roll}, nullptr);
        }
    };
    auto targetRotation = CameraRotation();
    auto currentRotation = CameraRotation();

    void EnableFreeCam() {
        auto& FreeCamera = FreeCamera::getInstance();

        freeCam = reinterpret_cast<app::GameObject*>(freeCamObj);

        freeCam_Transform = app::GameObject_get_transform(freeCam);
        auto freeCam_Transform_position = app::Transform_get_position(freeCam_Transform);

        freeCam_Camera = app::GameObject_GetComponentByName(freeCam, string_to_il2cppi("Camera"));
        mainCam_Camera = app::GameObject_GetComponentByName(mainCam, string_to_il2cppi("Camera"));

        if (!FCamisEnabled) {
            targetRotation.InitializeFromTransform(freeCam_Transform);
            currentRotation.InitializeFromTransform(freeCam_Transform);
            app::Camera_CopyFrom(reinterpret_cast<app::Camera*>(freeCam_Camera),
                                 reinterpret_cast<app::Camera*>(mainCam_Camera), nullptr);

            targetPosition = freeCam_Transform_position;
            FCamisEnabled = true;
        }

        app::GameObject_SetActive(mainCam, false);
        app::GameObject_SetActive(freeCam, true);

        if (FreeCamera.f_Forward.IsDown())
            targetPosition = targetPosition + app::Transform_get_forward(freeCam_Transform) * FreeCamera.f_MoveSpeed.
                getValue();
        
        if (FreeCamera.f_Backward.IsDown())
            targetPosition = targetPosition - app::Transform_get_forward(freeCam_Transform) * FreeCamera.f_MoveSpeed.
                getValue();
        
        if (FreeCamera.f_Left.IsDown())
            targetPosition = targetPosition - app::Transform_get_right(freeCam_Transform) * FreeCamera.f_MoveSpeed.
                getValue();
        
        if (FreeCamera.f_Right.IsDown())
            targetPosition = targetPosition + app::Transform_get_right(freeCam_Transform) * FreeCamera.f_MoveSpeed.
                getValue();
        
        if (FreeCamera.f_Up.IsDown())
            targetPosition = targetPosition + app::Transform_get_up(freeCam_Transform) * FreeCamera.f_MoveSpeed.
                getValue();
        
        if (FreeCamera.f_Down.IsDown())
            targetPosition = targetPosition - app::Transform_get_up(freeCam_Transform) *
                FreeCamera.f_MoveSpeed.getValue();

        if (FreeCamera.f_LeftRoll.IsDown())
            targetRotation.roll += FreeCamera.f_RollSpeed.getValue();

        if (FreeCamera.f_RightRoll.IsDown())
            targetRotation.roll -= FreeCamera.f_RollSpeed.getValue();

        if (FreeCamera.f_ResetRoll.IsDown())
            targetRotation.roll = 0.f;

        if (FreeCamera.f_IncFOV.IsDown())
            smoothFOV += FreeCamera.f_FOVSpeed.getValue();
        if (FreeCamera.f_DecFOV.IsDown())
            smoothFOV -= FreeCamera.f_FOVSpeed.getValue();

        auto mouseX = app::Input_GetAxis(string_to_il2cppi("Mouse X"), nullptr);
        auto mouseY = app::Input_GetAxis(string_to_il2cppi("Mouse Y"), nullptr);
        auto mouseInput = app::Vector2{mouseX, mouseY * -1.0f};
        targetRotation.yaw += mouseInput.x * FreeCamera.f_LookSens.getValue();
        targetRotation.pitch += mouseInput.y * FreeCamera.f_LookSens.getValue();

        currentRotation.UpdateTransform(freeCam_Transform);

        smoothPosition =
            app::Vector3_Lerp(freeCam_Transform_position, targetPosition, FreeCamera.f_MovSmoothing.getValue());
        app::Transform_set_position(freeCam_Transform, smoothPosition);
        smoothFOV =
            app::Mathf_Lerp(app::Camera_get_fieldOfView(reinterpret_cast<app::Camera*>(freeCam_Camera), nullptr),
                            FreeCamera.f_FOV.getValue(), FreeCamera.f_FovSmoothing.getValue(), nullptr);
        app::Camera_set_fieldOfView(reinterpret_cast<app::Camera*>(freeCam_Camera), smoothFOV, nullptr);
        currentRotation.LerpTowards(targetRotation, FreeCamera.f_LookSmoothing.getValue(),
                                    FreeCamera.f_RollSmoothing.getValue());
    }

    void DisableFreeCam() {
        if (!FCamisEnabled)
            return;

        if (mainCam != nullptr) {
            app::GameObject_SetActive(mainCam, true);
            LOG_DEBUG("MainCam Active");
            mainCam = nullptr;
        }
        if (freeCamObj != nullptr) {
            app::Object_1_DestroyImmediate_1(freeCamObj);
            LOG_DEBUG("FreeCam Destroyed");
            freeCamObj = nullptr;
        }
        FCamisEnabled = false;
    }

    void onGameUpdateFreeCamera(app::EventSystem* __this, app::MethodInfo* method) {
        auto& FreeCamera = FreeCamera::getInstance();
        //static bool isBlock = false;
        if (FreeCamera.f_Enabled.getValue()) {
            if (mainCam == nullptr)
            {
                mainCam = app::GameObject_Find(string_to_il2cppi("Main Camera"));
                //auto mainCamobj = app::Camera_get_main(nullptr);
            }
            if (freeCamObj == nullptr && mainCam) {
                auto mainCamTransform = app::GameObject_get_transform(mainCam);
                auto mainCamPos = app::Transform_get_position(mainCamTransform);
                LOG_DEBUG("MainCamPos: %f %f %f", mainCamPos.x, mainCamPos.y, mainCamPos.z);
                auto mainCamRot = app::Transform_get_rotation(mainCamTransform);
                LOG_DEBUG("MainCamRot: %f %f %f %f", mainCamRot.x, mainCamRot.y, mainCamRot.z, mainCamRot.w);
                freeCamObj = app::Object_1_Instantiate(reinterpret_cast<app::Object_1*>(mainCam), mainCamPos,
                                                         mainCamRot,nullptr);
                LOG_DEBUG("FreeCamObj: %p", freeCamObj);

                //auto CinemachineBrain = app::GameObject_GetComponentByName(
                //    reinterpret_cast<app::GameObject*>(freeCamObj), string_to_il2cppi("CinemachineBrain"));
                //auto CinemachineExternalCamera =
                //    app::GameObject_GetComponentByName(reinterpret_cast<app::GameObject*>(freeCamObj),
                //                                       string_to_il2cppi("CinemachineExternalCamera"));
                //app::Object_1_DestroyImmediate_1(reinterpret_cast<app::Object_1*>(CinemachineBrain));
                //app::Object_1_DestroyImmediate_1(reinterpret_cast<app::Object_1*>(CinemachineExternalCamera));

                //app::GameObject_SetActive(mainCam, false);
                //app::GameObject_SetActive(mainCam, true);
                app::GameObject_SetActive(reinterpret_cast<app::GameObject*>(freeCamObj), false);
            }
            if (freeCamObj != nullptr)
                EnableFreeCam();
        } else {
            DisableFreeCam();
        }

        CALL_ORIGIN(onGameUpdateFreeCamera, __this, method);
    }
}
