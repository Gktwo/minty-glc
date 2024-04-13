#include "GodMode.h"

namespace cheat {
    //static void VCHumanoidMove_NotifyLandVelocity_Hook(app::VCHumanoidMove* __this, app::Vector3 velocity,float reachMaxDownVelocityTime);


    GodMode::GodMode() {
        f_Enabled = config::getValue("functions:GodMode", "enabled", false);

        f_Hotkey = Hotkey("functions:GodMode");

      //  HookManager::install(app::Miscs_CheckTargetAttackable, Miscs_CheckTargetAttackable_Hook);

    }

    GodMode& GodMode::getInstance() {
        static GodMode instance;
        return instance;
    }

    void GodMode::GUI() {
        if (ConfigCheckbox(_("GODMODE_TITLE"), f_Enabled, _("GODMODE_DESCRIPTION"))) {
            ImGui::Indent();
            f_Hotkey.Draw();
            ImGui::Unindent();
        }
    }

    void GodMode::Outer() {
        if (f_Hotkey.IsPressed())
        {
            f_Enabled.setValue(!f_Enabled.getValue());
        }
    }

    void GodMode::Status() {
        if (f_Enabled)
            ImGui::Text(_("GODMODE_TITLE"));
    }

    std::string GodMode::getModule() {
        return _("MODULE_PLAYER");
    }

    //void VCHumanoidMove_NotifyLandVelocity_Hook(app::VCHumanoidMove* __this, app::Vector3 velocity,
    //    float reachMaxDownVelocityTime) {
    //    auto& godMode = GodMode::getInstance();

    //    if (godMode.f_Enabled && -velocity.y > 13) {
    //        float randAdd = (float)(std::rand() % 1000) / 1000;
    //        velocity.y = -8 - randAdd;
    //        reachMaxDownVelocityTime = 0;
    //    }
    //    CALL_ORIGIN(VCHumanoidMove_NotifyLandVelocity_Hook, __this, velocity, reachMaxDownVelocityTime);
    //}


}
