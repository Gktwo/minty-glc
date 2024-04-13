#include "Engine.h"
#include "EngineUtils.hpp"
#include "EngineFunc.hpp"


namespace cheat {
	static void EngineUpdate(app::UnityEngine_EventSystems_EventSystem_o* __this, app::MethodInfo* method);
	//find
	std::vector<app::GameObject*> foundobjs = {};
	char SeacherInputname[255];
	std::string Seachershowname = "Null";
	app::GameObject* SeacherGetobj = nullptr;
	//explorer
	//app::GameObject__Array* rootobjs = nullptr;
	//inspect
	app::Vector3 myPos;
	std::string InspectactivestatusText = "";
	app::GameObject* InspectObject = nullptr;//InspectObject
	app::Transform* InspectTransform = nullptr;//InspectTransform
	std::string InspectObjectname;
	app::Text* InspectText = nullptr;
	//pos
	app::Vector3 InspectTransformPos = { 0,0,0 };
	app::Vector3 InspectTargetpos = { 0,0,0 };
	//Rot
	app::Quaternion InspectTransformRot = { 0,0,0,0 };
	app::Quaternion InspectTargetRot = { 0,0,0,0 };
	//eulerAngles
	app::Vector3 InspectTransformeulerAngles = { 0,0,0 };
	app::Vector3 InspectTargeteulerAngles = { 0,0,0 };
	//scale
	app::Vector3 InspectTransformScale = { 0,0,0 };
	app::Vector3 InspectTargetScale = { 0,0,0 };
	app::Vector3 ibo = { 180.f, 180.f, 180.f };
	bool Inspectactivestatus = true;
	app::GameObject* newInspectptr = nullptr;
	app::Transform* newTransformparentptr = nullptr;
	//Text
	std::string InspectTexttext = "";
	std::string InspectTextMtext = "";
	int TextSetalignment = 0;
	int TextSize = 1;


	Engine::Engine() {
		HookManager::install(app::Global_Update, EngineUpdate);

		//main
		f_Enabled = config::getValue("functions:Engine", "enabled", false);
		f_Hotkey = Hotkey("functions:Engine:Engine");
		//sub
		f_EngineBar = config::getValue("functions:Engine:EngineBar", "enabled", false);
		f_Explorer = config::getValue("functions:Engine:Explorer", "enabled", false);
		f_Searcher = config::getValue("functions:Engine:Searcher", "enabled", false);
		f_Inspector = config::getValue("functions:Engine:Inspector", "enabled", false);
		f_Hooks = config::getValue("functions:Engine:Hooks", "enabled", false);
		f_Clipboard = config::getValue("functions:Engine:Clipboard", "enabled", false);
		//mover
		f_Mover = config::getValue("functions:Engine:Inspector:Mover", "enabled", false);
		f_moveSpeed = config::getValue("functions:Engine:Inspector:Mover:moveSpeed", "value", 1.0f);
		f_up = Hotkey("functions:Engine:Inspector:Mover:up", VK_UP);
		f_down = Hotkey("functions:Engine:Inspector:Mover:down", VK_DOWN);
		f_left = Hotkey("functions:Engine:Inspector:Mover:left", VK_LEFT);
		f_right = Hotkey("functions:Engine:Inspector:Mover:right", VK_RIGHT);
		f_forward = Hotkey("functions:Engine:Inspector:Mover:forward", VK_PRIOR);
		f_backward = Hotkey("functions:Engine:Inspector:Mover:backward", VK_NEXT);
		f_WorldPos = config::getValue("functions:Engine:Inspector:Mover:WorldPos", "enabled", false);
		f_LocalPos = config::getValue("functions:Engine:Inspector:Mover:LocalPos", "enabled", false);
		f_WorldRot = config::getValue("functions:Engine:Inspector:Mover:WorldRot", "enabled", false);
		f_LocalRot = config::getValue("functions:Engine:Inspector:Mover:LocalRot", "enabled", false);
		f_Rotator = config::getValue("functions:Engine:Inspector:Mover:Rotator", "enabled", false);
		f_WorldeulerAngles = config::getValue("functions:Engine:Inspector:Mover:WorldeulerAngles", "enabled", false);
		f_LocaleulerAngles = config::getValue("functions:Engine:Inspector:Mover:LocaleulerAngles", "enabled", false);
		f_euler = config::getValue("functions:Engine:Inspector:Mover:euler", "enabled", false);
		f_Scaler = config::getValue("functions:Engine:Inspector:Mover:Scaler", "enabled", false);
		f_Scale = config::getValue("functions:Engine:Inspector:Mover:LocalScale", "enabled", false);
		f_TextModifier = config::getValue("functions:Engine:Inspector:Mover:TextModifier", "enabled", false);

	}


	Engine& Engine::getInstance() {
		static Engine instance;
		return instance;
	}

	void Engine::GUI() {
		//ImGui::SeparatorText(_("Unity Explorer"));
		ConfigCheckbox(_("Unity Explorer"), f_Enabled, _("Unity Explorer(Control the engine, but mostly only locally)"));

		if (f_Enabled.getValue()) {
			ImGui::Indent();
			ConfigCheckbox(_("EngineBar"), f_EngineBar, _("EngineBar"));
			//ConfigCheckbox(_("Explorer"), f_Explorer, _("Explorer"));
			ConfigCheckbox(_("Searcher"), f_Searcher, _("Searcher"));
			ConfigCheckbox(_("Inspector"), f_Inspector, _("Inspector"));
			if (!f_EngineBar.getValue())
			{
				if (f_Explorer.getValue())
					DrawExplorer();

				if (f_Searcher.getValue())
					DrawSearcher();

				if (f_Inspector.getValue())
					DrawInspector();
			}
			//ConfigCheckbox(_("Hooks"), f_Hooks, _("Hooks"));
			//ConfigCheckbox(_("Clipboard"), f_Clipboard, _("Clipboard"));
			ImGui::Unindent();
		}
	}


	//Control
	void Engine::Outer() {

		auto& Engine = cheat::Engine::getInstance();
		if (!Engine.f_Enabled.getValue())
			return;

		if (Engine.f_Enabled.getValue())
		{
			if (f_EngineBar.getValue())
			{
				EngineBar();
				if (f_Explorer.getValue())
					Explorer();
				if (f_Searcher.getValue())
					Searcher();
				if (f_Inspector.getValue())
					Inspector();
			}

		}

	}


	void Engine::Status() {
		if (f_Enabled.getValue())
			ImGui::Text(_("Unity Explorer"));

	}

	std::string Engine::getModule() {
		return _("Debug");
	}

	static app::Quaternion E2Q(app::Vector3 euler)
	{
		auto roll = euler.x;
		auto pitch = euler.y;
		auto yaw = euler.z;

		float cr = cos(roll * .5f);
		float sr = sin(roll * .5f);
		float cp = cos(pitch * .5f);
		float sp = sin(pitch * .5f);
		float cy = cos(yaw * .5f);
		float sy = sin(yaw * .5f);
		auto a = sr * cp * cy - cr * sp * sy;
		auto b = cr * sp * cy + sr * cp * sy;
		auto c = cr * cp * sy - sr * sp * cy;
		auto d = cr * cp * cy + sr * sp * sy;

		app::Quaternion q = { a, b, c,d };

		return q;
	}
	//static app::Vector3 Q2E(app::Quaternion q)
	//{
	//	float roll, pitch, yaw;

	//	// roll (x-axis rotation)
	//	float sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
	//	float cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
	//	roll = atan2(sinr_cosp, cosr_cosp);

	//	// pitch (y-axis rotation)
	//	float sinp = 2 * (q.w * q.y - q.z * q.x);
	//	if (abs(sinp) >= 1)
	//		pitch = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
	//	else
	//		pitch = asin(sinp);

	//	// yaw (z-axis rotation)
	//	float siny_cosp = 2 * (q.w * q.z + q.x * q.y);
	//	float cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
	//	yaw = atan2(siny_cosp, cosy_cosp);

	//	app::Vector3 euler = { roll, pitch, yaw };
	//	return euler;
	//}



	//DrawBar&&Window
	void Engine::EngineBar() {
		auto& Engine = cheat::Engine::getInstance();
		if (!Engine.f_Enabled.getValue())
			return;
		ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize |
			ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoFocusOnAppearing;
		ImGui::SetNextWindowPos({ 50, 1 }, ImGuiCond_FirstUseEver);
		ImGui::Begin("##EngineBar", NULL, flags);
		ImGui::BeginGroup();
		ImGui::PushStyleColor(ImGuiCol_Text, { 0.17f, 0.63f, 0.45f, 1.00f });
		ImGui::Text("UnityExplorer");
		ImGui::SameLine();
		ImGui::Dummy(ImVec2(10.0f, 0.f));
		ImGui::SameLine();
		ImGui::PopStyleColor();
		//ColorToggleButton("Explorer", Engine.f_Explorer);
		//ImGui::SameLine();
		ColorToggleButton("Searcher", Engine.f_Searcher, { 0.17f, 0.63f, 0.45f, 1.00f });
		ImGui::SameLine();
		ColorToggleButton("Inspector", Engine.f_Inspector, { 0.17f, 0.63f, 0.45f, 1.00f });
		ImGui::SameLine();
		//ColorToggleButton("Hooks", Engine.f_Hooks);
		//ImGui::SameLine();
		//ColorToggleButton("Clipboard", Engine.f_Clipboard);
		//ImGui::SameLine();
		ImGui::Dummy(ImVec2(10.0f, 0.f));
		ImGui::SameLine();
		ColorToggleButton("Exit", Engine.f_EngineBar, { 0.83f, 0.37f, 0.55f, 1.00f });
		ImGui::EndGroup();
		ImGui::End();
	}
	void Engine::Explorer() {
		auto& Engine = cheat::Engine::getInstance();
		if (!Engine.f_Enabled.getValue())
			return;
		//Obj list
		ImGui::PushStyleColor(ImGuiCol_Text, { 0.17f, 0.63f, 0.45f, 1.00f });
		ImGui::SetNextWindowSize({ 300, 500 }, ImGuiCond_FirstUseEver);
		ImGui::Begin("Explorer", NULL, 0);
		ImGui::PopStyleColor();
		ImGui::BeginGroup();
		if (Engine.f_EngineBar.getValue() && Engine.f_Explorer.getValue())
			DrawExplorer();
		ImGui::EndGroup();
		ImGui::End();
	}
	void Engine::Searcher() {
		auto& Engine = cheat::Engine::getInstance();
		if (!Engine.f_Enabled.getValue())
			return;
		//Searcher
		ImGui::PushStyleColor(ImGuiCol_Text, { 0.17f, 0.63f, 0.45f, 1.00f });
		ImGui::SetNextWindowSize({ 300, 500 }, ImGuiCond_FirstUseEver);
		ImGui::Begin("Searcher", NULL, 0);
		ImGui::PopStyleColor();
		ImGui::BeginGroup();
		if (Engine.f_EngineBar.getValue() && Engine.f_Searcher.getValue())
			DrawSearcher();
		ImGui::EndGroup();
		ImGui::End();
	}
	void Engine::Inspector() {
		auto& Engine = cheat::Engine::getInstance();
		if (!Engine.f_Enabled.getValue())
			return;
		ImGui::PushStyleColor(ImGuiCol_Text, { 0.17f, 0.63f, 0.45f, 1.00f });
		ImGui::SetNextWindowSize({ 300, 500 }, ImGuiCond_FirstUseEver);
		ImGui::Begin("Inspector", NULL, 0);
		ImGui::PopStyleColor();
		ImGui::BeginGroup();
		if (Engine.f_EngineBar.getValue() && Engine.f_Inspector.getValue())
			DrawInspector();
		ImGui::EndGroup();
		ImGui::End();
	}
	//DrawFunc
	const char* const Textalignment[] = {
"UpperLeft",//0
"UpperCenter",
"UpperRight",
"MiddleLeft",
"MiddleCenter",
"MiddleRight",
"LowerLeft",
"LowerCenter",
"LowerRight"//8
	};
	void Engine::DrawInspector()
	{
		if (BeginGroupPanel("Inspector", true, ImGui::GetContentRegionAvail()))
		{
			ImGui::Text("New ptr: 0x"); ImGui::SameLine();
			ImGui::InputScalar("##newGameObject*: ptr", ImGuiDataType_U64, &newInspectptr, NULL, NULL, "%016llX");
			ImGui::SameLine();
			if (ImGui::Button("Inspect")) {
				LOG_DEBUG("newInspectptr: %p", newInspectptr);
				InspectObject = (app::GameObject*)newInspectptr;
				InspectTransform = EngineUtils::GetTransform(InspectObject);
				InspectText = EngineUtils::GetText(InspectObject);
				LOG_DEBUG("Engine::Inspect:Load %s.GameObject:%p ", EngineUtils::GetName(InspectObject), InspectObject);
				LOG_DEBUG("Engine::Inspect:Get %s.Transform:%p ", EngineUtils::GetName(InspectObject), InspectTransform);
				if(InspectText!=nullptr)
				LOG_DEBUG("Engine::Inspect:Get %s.Text:%p ", EngineUtils::GetName(InspectObject), InspectText);
			}ImGui::SameLine(); HelpMarker("Inspect from ptr");
			//information
			ImGui::Text("Name: %s Active: %s ptr: %p", InspectObjectname, InspectactivestatusText, InspectObject);//ImGui::SameLine();
			//if (ImGui::Button("Copy"))
			//	EngineUtils::CopyToClipboard(InspectObject);ImGui::SameLine(); HelpMarker("Copy this  GameObject* to Clipboard");		 
			if (Inspectactivestatus)
			{
				if (ImGui::Button("Disable"))
				{
					app::GameObject_SetActive(InspectObject, false);
					Inspectactivestatus = false;
					InspectactivestatusText = "False";
				}
				ImGui::SameLine(); HelpMarker("Disable GameObject");
			}
			else
			{
				if (ImGui::Button("Enable"))
				{
					app::GameObject_SetActive(InspectObject, true);
					Inspectactivestatus = true;
					InspectactivestatusText = "True";
				}
				ImGui::SameLine(); HelpMarker("Enable GameObject");
			}
			ImGui::SameLine();
			if (ImGui::Button("Destroy"))
			{
				app::Object_1_DestroyImmediate_1(reinterpret_cast<app::Object_1*>(InspectObject));
				InspectObject = nullptr;
				InspectTransform = nullptr;
				InspectTransformPos = { 0,0,0 };
				InspectTargetpos = { 0,0,0 };
				InspectObjectname = "Null";
				f_Inspector.setValue(false);
			}
			ImGui::SameLine(); HelpMarker("Destroy GameObject"); ImGui::SameLine();
			if (ImGui::Button("Instantiate")) {
				auto obj = EngineUtils::Instantiate1(reinterpret_cast<app::Object_1*>(InspectObject), { myPos.x,myPos.y + 5.0f,myPos.z }, EngineUtils::GetRotation(InspectTransform));
				LOG_DEBUG("Engine::Instantiate: %s:%p pos:(%f,%f,%f)", EngineUtils::GetName(obj), obj, myPos.x, myPos.y + 5.0f, myPos.z);
			}
			ImGui::SameLine(); HelpMarker("Clone  a GameObject above the avatar's head");
			ImGui::Text("AvatarPos: %2f,%2f,%2f", myPos.x, myPos.y, myPos.z);
			//Transform  
			ImGui::Text("%s.Transform: %p", InspectObjectname, InspectTransform);
			if (BeginGroupPanel("Transform", true)) {
				/*
			if (ImGui::Button("Copy"))
				EngineUtils::CopyToClipboard(InspectTransform); ImGui::SameLine(); HelpMarker("Copy this  Transform* to Clipboard");
				ImGui::SameLine();*/
				if (ImGui::Button("SetParent")) {
					auto newTransform = (app::Transform*)newTransformparentptr;
					EngineUtils::Transform_set_parent(InspectTransform, newTransform);
				}ImGui::SameLine();
				ImGui::InputScalar(": ptr new_parent", ImGuiDataType_U64, &newTransformparentptr, NULL, NULL, "%016llX");
				if (BeginGroupPanel("Position", true)) {//pos			 
					//ImGui::Text("Position");
					ConfigCheckbox(_("WorldPos"), f_WorldPos, _("Position in the world")); ImGui::SameLine();
					ConfigCheckbox(_("LocalPos"), f_LocalPos, _("Position for Parent object"));
					if (f_Mover.getValue())
					{
						ImGui::InputFloat(" :X", &(InspectTargetpos.x));
						ImGui::InputFloat(" :Y", &(InspectTargetpos.y));
						ImGui::InputFloat(" :Z", &(InspectTargetpos.z));
					}
					else
					{
						ImGui::InputFloat(" :X", &(InspectTransformPos.x));
						ImGui::InputFloat(" :Y", &(InspectTransformPos.y));
						ImGui::InputFloat(" :Z", &(InspectTransformPos.z));
					}
					ConfigCheckbox(_("PosMover"), f_Mover, _("Mover"));
					if (f_Mover.getValue()) {
						ImGui::Indent();
						ImGui::BeginGroup();
						ConfigSliderFloat(_("MoveSpeed"), f_moveSpeed, 0.1f, 100.0f, "PosMover Speed");
						f_up.Draw(_("forward")); ImGui::SameLine();
						f_down.Draw(_("backward"));
						f_left.Draw(_("left")); ImGui::SameLine();
						f_right.Draw(_("right"));
						f_forward.Draw(_("up")); ImGui::SameLine();
						f_backward.Draw(_("down"));
						ImGui::EndGroup();
					}
				}EndGroupPanel();

				if (BeginGroupPanel("EulerAngles", true)) {//eulerAngles}
					//ImGui::Text("EulerAngles");
					ConfigCheckbox(_("WorldEulerAngles"), f_WorldeulerAngles, _("eulerAngles for the world")); ImGui::SameLine();
					ConfigCheckbox(_("LocalEulerAngles"), f_LocaleulerAngles, _("eulerAngles for Parent object"));
					ConfigCheckbox(_("Euler"), f_euler, _("euler2Angles "));
					if (f_euler.getValue())
					{
						ImGui::SliderFloat(" :X", &(InspectTargeteulerAngles.x), -180.f, 180.0f);
						ImGui::SliderFloat(" :Y", &(InspectTargeteulerAngles.y), -180.f, 180.0f);
						ImGui::SliderFloat(" :Z", &(InspectTargeteulerAngles.z), -180.f, 180.0f);
					}
					else
					{
						ImGui::SliderFloat(" :X", &(InspectTransformeulerAngles.x), -180.f, 180.0f);
						ImGui::SliderFloat(" :Y", &(InspectTransformeulerAngles.y), -180.f, 180.0f);
						ImGui::SliderFloat(" :Z", &(InspectTransformeulerAngles.z), -180.f, 180.0f);
					}
				}EndGroupPanel();
				if (BeginGroupPanel("Scale", true)) {//scale
					//ImGui::Text("Scale");
					ConfigCheckbox(_("GetScale"), f_Scale, _("Scale Size "));
					ConfigCheckbox(_("Scaler"), f_Scaler, _("Modify Size"));
					if (f_Scaler.getValue())
					{
						ImGui::InputFloat(":X", &(InspectTargetScale.x));
						ImGui::InputFloat(":Y", &(InspectTargetScale.y));
						ImGui::InputFloat(":Z", &(InspectTargetScale.z));
					}
					else
					{
						ImGui::InputFloat(":X", &(InspectTransformScale.x));
						ImGui::InputFloat(":Y", &(InspectTransformScale.y));
						ImGui::InputFloat(":Z", &(InspectTransformScale.z));
					}
				}EndGroupPanel();
				if (BeginGroupPanel("Rotation", true)) {//
					ConfigCheckbox(_("WorldRot"), f_WorldRot, _(" WRotation ")); ImGui::SameLine();
					ConfigCheckbox(_("LocalRot"), f_LocalRot, _("L Rotation "));
					ConfigCheckbox(_("Rotation"), f_Rotator, _("Modify Rotation"));
					if (f_Rotator.getValue())
					{
						ImGui::InputFloat(":X", &(InspectTargetRot.x));
						ImGui::InputFloat(":Y", &(InspectTargetRot.y));
						ImGui::InputFloat(":Z", &(InspectTargetRot.z));
						ImGui::InputFloat(":W", &(InspectTargetRot.w));
					}
					else
					{
						ImGui::InputFloat(":X", &(InspectTransformRot.x));
						ImGui::InputFloat(":Y", &(InspectTransformRot.y));
						ImGui::InputFloat(":Z", &(InspectTransformRot.z));
						ImGui::InputFloat(":W", &(InspectTransformRot.w));
					}
				}EndGroupPanel();

			}EndGroupPanel();

			if (InspectText != nullptr)
			{
				//Text
				if (BeginGroupPanel("UI.Text", true, ImGui::GetContentRegionAvail()))
				{

					ImGui::Text("UI.Text: %p", InspectText);
					//if (ImGui::Button("Copy"))
						//EngineUtils::CopyToClipboard(InspectText);
					//ImGui::SameLine(); HelpMarker("Copy this  Text* to Clipboard");
					ConfigCheckbox("Modifier", f_TextModifier, "TextModifier");
					if (!f_TextModifier.getValue())
					{
						ImGui::InputText("text:", &InspectTexttext); ImGui::SameLine();
					}
					else
					{
						ImGui::InputText("text:", &InspectTextMtext); 
						ImGui::Combo("Alignment", &TextSetalignment, Textalignment, 9, 4);
						ImGui::InputInt("FontSize", &TextSize);
					}
				}EndGroupPanel();
			}


		}EndGroupPanel();


	}
	void Engine::DrawExplorer() {
		auto& Engine = cheat::Engine::getInstance();
		if (BeginGroupPanel("Obj List", true, ImGui::GetContentRegionAvail()))
		{
			if (ImGui::Button("Get"))
			{
				//auto scene = app::SceneManager_GetActiveScene(nullptr);
				//LOG_DEBUG("scene:%p",scene);
				//auto gobjs=EngineUtils::GetRootGObjs(scene);
				//auto gobjs = il2cppi_to_string(app::GetNameInternal(scene->fields.m_Handle));
				//LOG_DEBUG("GObjs:%s", gobjs.c_str());


			}
			ImGui::SameLine(); HelpMarker("Get GameObject List");

		}EndGroupPanel();
	}
	void Engine::DrawSearcher()
	{

		auto& Engine = cheat::Engine::getInstance();
		int objcount = 0;
		//Obj finder
		if (BeginGroupPanel("Obj finder", true, ImGui::GetContentRegionAvail()))
		{
			ImGui::InputText("Objname", SeacherInputname, sizeof(SeacherInputname));
			if (ImGui::Button("Search"))
			{
				foundobjs = {};
				Seachershowname = "Null";
				SeacherGetobj = nullptr;
				SeacherGetobj = EngineUtils::FindGameObject(SeacherInputname);

				if (SeacherGetobj != nullptr) {

					Seachershowname = EngineUtils::GetName(SeacherGetobj);
					LOG_DEBUG("Engine::Searcher found %s:%p ", Seachershowname, SeacherGetobj);
					foundobjs.push_back(SeacherGetobj);
				}
				else {
					Seachershowname = "Null";
					LOG_ERROR("Engine::Searcher found Null ");
				}
			}
			ImGui::SameLine(); HelpMarker("Find a GameObject ");
			if (ImGui::Button("Inspect")) {
				Engine::f_Inspector.setValue(true);
				InspectObject = SeacherGetobj;
				InspectTransform = EngineUtils::GetTransform(InspectObject);
				InspectText = EngineUtils::GetText(InspectObject);
				auto name = EngineUtils::GetName(InspectObject);
				//LOG_DEBUG("Engine::Inspect:%s.Transform:%p ", name, InspectTransform);
				//LOG_DEBUG("Engine::Inspect:%s.Text:%p ", name, InspectText);
			}ImGui::SameLine(); HelpMarker("Inspect "); /*ImGui::SameLine();
			ImGui::Button("Copy"))
				EngineUtils::CopyToClipboard(SeacherGetobj); ImGui::SameLine(); HelpMarker("Copy this  GameObject* to Clipboard");*/
			ImGui::Text("found %d %s : %p", foundobjs.size(), Seachershowname, SeacherGetobj);
		}EndGroupPanel();
	}
	//Main Hook
	void EngineUpdate(app::GameManager* __this, app::MethodInfo* method)
	{
		auto& Engine = Engine::getInstance();
		//if (!Engine.f_Searcher.getValue())
		//{
		//	foundobjs = {};
		//	SeacherInputname = "";
		//	Seachershowname = "Null";
		//	SeacherGetobj = nullptr;
		//}
		if (Engine.f_Enabled.getValue())
		{
			if (Engine.f_Inspector.getValue())
			{
				if (InspectObject != nullptr) {
					myPos = EngineUtils::GetmyPos();
					if (InspectObjectname == "Null")
						InspectObjectname = EngineUtils::GetName(InspectObject);
					//LOG_DEBUG("Engine::Inspect: %s Active: %s ptr: %p", InspectObjectname, InspectactivestatusText, InspectObject);
				}
				if (InspectTransform != nullptr) {//Inspector				
					if (!Engine.f_WorldPos.getValue() && !Engine.f_LocalPos.getValue() && !EngineFunc::Vector3_Equal0(InspectTransformPos))
						InspectTransformPos = { 0,0,0 };//Clear Pos
					if (!Engine.f_WorldeulerAngles.getValue() && !Engine.f_LocaleulerAngles.getValue() && !EngineFunc::Vector3_Equal0(InspectTransformeulerAngles))
						InspectTransformeulerAngles = { 0,0,0 };//=Clear eulerAngles
					if (!Engine.f_Scale.getValue() && !EngineFunc::Vector3_Equal0(InspectTransformScale))
						InspectTransformScale = { 0,0,0 };//Clear Scale
					if (!Engine.f_WorldRot.getValue() && !Engine.f_LocalRot.getValue() && !EngineFunc::Quaternion_Equal0(InspectTransformRot))
						InspectTransformRot = { 0,0,0,0 };//Clear Rot

					if (Engine.f_WorldPos.getValue() && !Engine.f_LocalPos.getValue())
						InspectTransformPos = EngineUtils::GetPosition(InspectTransform);//WorldPos
					if (Engine.f_LocalPos.getValue() && !Engine.f_WorldPos.getValue())
						InspectTransformPos = EngineUtils::GetLocalPosition(InspectTransform);//LocalPos
					if (Engine.f_WorldeulerAngles.getValue() && !Engine.f_LocaleulerAngles.getValue())
						InspectTransformeulerAngles = EngineUtils::GeteulerAngles(InspectTransform) - ibo;//WorldeulerAngles
					if (Engine.f_LocaleulerAngles.getValue() && !Engine.f_WorldeulerAngles.getValue())
						InspectTransformeulerAngles = EngineUtils::GetLocaleulerAngles(InspectTransform) - ibo;//LocaleulerAngles
					if (Engine.f_WorldRot.getValue() && !Engine.f_LocalRot.getValue())
						InspectTransformRot = EngineUtils::GetRotation(InspectTransform);//WorldRot
					if (Engine.f_LocalRot.getValue() && !Engine.f_WorldRot.getValue())
						InspectTransformRot = EngineUtils::GetLocalRotation(InspectTransform);//LocalRot
					if (Engine.f_Scale.getValue())
						InspectTransformScale = EngineUtils::GetLocalScale(InspectTransform);//Scale
					//Enabled Mover
					if (Engine.f_Mover.getValue()) {
						if (EngineFunc::Vector3_Equal0(InspectTargetpos))
							InspectTargetpos = InspectTransformPos;

						InspectTargetpos = EngineFunc::SetTargetPosition(InspectTargetpos, InspectTransform);//SetTargetPosition

						if (!EngineFunc::Vector3_Compare(InspectTargetpos, InspectTransformPos))//If Target!=Current
						{
							if (Engine.f_WorldPos.getValue() && !Engine.f_LocalPos.getValue())
								EngineUtils::SetPositon(InspectTransform, InspectTargetpos);//SetWorldPos
							if (Engine.f_LocalPos.getValue() && !Engine.f_WorldPos.getValue())
								EngineUtils::SetLocalPositon(InspectTransform, InspectTargetpos);//SetLocalPos
						}
					}
					else if (!EngineFunc::Vector3_Equal0(InspectTargetpos))//Clear Targetpos
						InspectTargetpos = { 0,0,0 };

					//Enabled euler
					if (Engine.f_euler.getValue()) {
						if (EngineFunc::Vector3_Equal0(InspectTargeteulerAngles))
							InspectTargeteulerAngles = InspectTransformeulerAngles;

						if (!EngineFunc::Vector3_Compare(InspectTargeteulerAngles, InspectTransformeulerAngles))
						{
							auto targeteuler = (InspectTargeteulerAngles + ibo);
							if (Engine.f_WorldeulerAngles.getValue() && !Engine.f_LocaleulerAngles.getValue())
							{
								//EngineUtils::SeteulerAngles(InspectTransform, targeteuler);//SetWorldeulerAngles
								EngineUtils::SetRotation(InspectTransform, E2Q(targeteuler));//SetWorldRotation

							}
							if (Engine.f_LocaleulerAngles.getValue() && !Engine.f_WorldeulerAngles.getValue())
							{
								//EngineUtils::SetLocaleulerAngles(InspectTransform, targeteuler);//SetLocaleulerAngles
								EngineUtils::SetLocalRotation(InspectTransform, E2Q(targeteuler));//SetLocalRotation

							}
						}
					}
					else if (!EngineFunc::Vector3_Equal0(InspectTargeteulerAngles))//Clear TargeteulerAngles
						InspectTargeteulerAngles = { 0,0,0 };
					//Enabled Scaler
					if (Engine.f_Scaler.getValue())
					{
						if (EngineFunc::Vector3_Equal0(InspectTargetScale))
							InspectTargetScale = InspectTransformScale;
						if (!EngineFunc::Vector3_Compare(InspectTargetScale, InspectTransformScale))//If Target!=Current
							EngineUtils::SetScale(InspectTransform, InspectTargetScale);//SetLocalScale						
					}
					else if (!EngineFunc::Vector3_Equal0(InspectTargetScale))//Clear TargetScale
						InspectTargetScale = { 0,0,0 };
					//Enabled Rotator
					if (Engine.f_Rotator.getValue())
					{
						if (EngineFunc::Quaternion_Equal0(InspectTargetRot))
							InspectTargetRot = InspectTransformRot;
						if (!EngineFunc::Quaternion_Compare(InspectTargetRot, InspectTransformRot))//If Target!=Current
							EngineUtils::SetRotation(InspectTransform, InspectTargetRot);//SetRotation						
					}
					else if (!EngineFunc::Quaternion_Equal0(InspectTargetRot))//Clear TargetRot
						InspectTargetRot = { 0,0,0,0 };
				}
				if (InspectText != nullptr)
				{
					InspectTexttext = EngineUtils::GetTextString(InspectText);
					if (InspectTextMtext == "")
						InspectTextMtext = InspectTexttext;
					if (!Engine.f_TextModifier.getValue())
						InspectTexttext = EngineUtils::GetTextString(InspectText);
					else
					{
						if(InspectTextMtext != InspectTexttext )
						    EngineUtils::SetTextString(InspectText, InspectTextMtext);
						EngineUtils::SetTextAlignment(InspectText, static_cast<app::TextAnchor__Enum>(TextSetalignment));
						EngineUtils::SetFontSize(InspectText, TextSize);
					}



				}
			}
			else if (InspectObject != nullptr )//Clear Inspector
			{
				InspectObject = nullptr;
				InspectTransform = nullptr;
				InspectObjectname = "Null";
				InspectText = nullptr;

			}
		}

		CALL_ORIGIN(EngineUpdate, __this, method);
	}
}// namespace cheat

