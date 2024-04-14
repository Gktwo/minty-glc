#pragma once

#include "../FunctionIncludes.h"

namespace cheat {
    class FreeCamera : public Function {
    public:
        ConfigField<bool> f_Enabled;
        ConfigField<bool> f_FreezeAnimation;
        ConfigField<bool> f_SetAvatarInvisible;
        ConfigField<bool> f_BlockInput;

        ConfigField<float> f_MoveSpeed;
        ConfigField<float> f_LookSens;
        ConfigField<float> f_RollSpeed;
        ConfigField<float> f_FOVSpeed;
        ConfigField<float> f_FOV;
        ConfigField<float> f_MovSmoothing;
        ConfigField<float> f_LookSmoothing;
        ConfigField<float> f_RollSmoothing;
        ConfigField<float> f_FovSmoothing;

        Hotkey f_Hotkey;
        Hotkey f_Forward;
        Hotkey f_Backward;
        Hotkey f_Left;
        Hotkey f_Right;
        Hotkey f_Up;
        Hotkey f_Down;
        Hotkey f_IncFOV;
        Hotkey f_DecFOV;
        Hotkey f_LeftRoll;
        Hotkey f_RightRoll;
        Hotkey f_ResetRoll;

        void GUI() override;
        void Outer() override;
        void Status() override;

        std::string getModule() override;

        static FreeCamera& getInstance();

        FreeCamera();
    };
}
