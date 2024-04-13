#pragma once

#include "../FunctionIncludes.h"


namespace cheat {

	class Engine : public Function {
	public:
		ConfigField<bool> f_Enabled;
		ConfigField<bool> f_Explorer;
		ConfigField<bool> f_Searcher;
		ConfigField<bool> f_EngineBar;
		ConfigField<bool>f_Inspector;
		ConfigField<bool>f_Hooks;
		ConfigField<bool>f_Clipboard;
		ConfigField<bool> f_Mover;
		ConfigField<bool> f_LocalPos;//Position
		ConfigField<bool> f_WorldPos;
		ConfigField<bool> f_LocalRot;//Rotation
		ConfigField<bool> f_WorldRot;
		ConfigField<bool> f_Rotator;
		ConfigField<bool> f_LocaleulerAngles;//eulerAngles
		ConfigField<bool> f_WorldeulerAngles;
		ConfigField<bool> f_euler;
		ConfigField<bool> f_Scale;//Scale
		ConfigField<bool> f_Scaler;
		ConfigField<bool> f_TextModifier;



		Hotkey f_Hotkey;
		Hotkey f_up;
		Hotkey f_down;
		Hotkey f_left;
		Hotkey f_right;
		Hotkey f_forward;
		Hotkey f_backward;
		ConfigField<float>f_moveSpeed;


		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string getModule() override;

		void Explorer();
		static void EngineBar();
		void Searcher();
		void Inspector();
		void DrawInspector();
		void DrawExplorer();
		void DrawSearcher();
		static Engine& getInstance();
		//app::GameObject* FindGameObject(std::string objname);
		Engine();

	private:



		/* data */
	};
}
