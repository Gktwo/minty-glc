#include "../functions/about/About.h"
#include "../functions/settings/Settings.h"

//#include "../functions/player/godmode.h"
//#include "../functions/player/demagehack.h"
//#include "../functions/player/skillshack.h"
#include "../functions/world/SetTimeScale.h"

//#include "../functions/visuals/NoFog.h"
//#include "../functions/visuals/HideUI.h"
//#include "../functions/visuals/browser.h"

#include "../functions/visuals/UnlockFPS.h"
#include "../functions/visuals/freecamera.h"

#include "../functions/debug/Debug.h"


std::vector<std::string> ModuleOrder = {
	_("About"),
	_("Player"),
	_("World"),
	_("Visuals"),
	_("Settings"),
	_("Debug")

};

void Init() {
	//about
	INIT_FUNC(About);
	//player
	//INIT_FUNC(GodMode);

	
	//world
	INIT_FUNC(SetTimeScale);


	//settings
	INIT_FUNC(Settings);
	//debug
	INIT_FUNC(Debug);


	//Visuals
	//INIT_FUNC(HideUI);
	INIT_FUNC(UnlockFPS);
	//INIT_FUNC(Browser);
	//INIT_FUNC(NoFog);
	INIT_FUNC(FreeCamera);



}

void Outer() {
	for (auto& func : functions)
		func->Outer();
}

void Status() {
	auto& settings = cheat::Settings::getInstance();

	if (!settings.f_Status.getValue())
		return;

	ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoFocusOnAppearing;

	if (!settings.f_StatusMove.getValue())
		flags |= ImGuiWindowFlags_NoMove;

	ImGui::Begin(_("Status"), nullptr, flags);

	auto windowWidth = ImGui::GetWindowSize().x;
	auto& about = cheat::About::getInstance();
	std::string version = about.mVersion;

	ImGui::PushStyleColor(ImGuiCol_Text, { 0.17f, 0.63f, 0.45f, 1.00f });
	ImGui::Text("minty-glc");
	ImGui::PopStyleColor();
	ImGui::Separator();
	for (auto& feature : functions)
		feature->Status();
	ImGui::End();
}

void DrawSection(const std::string& moduleName) {
	for (auto& func : functions) {
		if (func->getModule() != moduleName)
			continue;

		func->GUI();
	}
}
