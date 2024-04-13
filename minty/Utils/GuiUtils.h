#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS
#include <Windows.h>

#include "Logger.h"

#include "../hotkeys/Hotkey.h"
#include "../config/ConfigManager.h"
#include "../gui/GuiDefinitions.h"
#include "../api/imgui/ImGui/imgui.h"
#include "../api/imgui/ImGui/imgui_internal.h"
#include "../api/imgui/ImGui/imgui_stdlib.h"

void HelpMarker(const char* description);

bool BeginGroupPanel(const char* label, bool node = false, const ImVec2& size = ImVec2(-1.0f, 0.0f));
void EndGroupPanel();

bool BeginSelectableGroupPanel(const char* label, bool& value, bool& changed, bool node = false,
    const ImVec2& size = ImVec2(-1.0f, 0.0f), const char* selectLabel = _("SELECT_TITLE"));
void EndSelectableGroupPanel();

void NextGroupPanelHeaderItem(const ImVec2& size, bool rightAlign = false);

#define START_WIDGET()\
	T& value = field.getValue();

#define END_WIDGET()\
    if (description != nullptr) {\
        ImGui::SameLine();\
        HelpMarker(description);\
    }\

template <typename T>
bool ConfigCheckbox(const char* name, ConfigField<T>& field, const char* description = nullptr) {
    START_WIDGET()

        if (ImGui::Checkbox(name, &value)) {
            field.setValue(value);
            config::setValue(field, value);
        }

    END_WIDGET()
        return value;
}

template <typename T>
void ConfigInputText(const char* name, ConfigField<T>& field, const char* description = nullptr) {
    START_WIDGET()

        if (ImGui::InputText(name, &value)) {
            field.setValue(value);
            config::setValue(field, value);
        }

    END_WIDGET()
}

template <typename T>
void ConfigInputInt(const char* name, ConfigField<T>& field, const char* description = nullptr) {
    START_WIDGET()

        if (ImGui::InputInt(name, &value)) {
            field.setValue(value);
            config::setValue(field, value);
        }

    END_WIDGET()
}

template <typename T>
void ConfigInputInt(const char* name, ConfigField<T>& field, int minValue, int maxValue,
    const char* description = nullptr) {
    START_WIDGET()

        if (ImGui::InputInt(name, &value)) {
            if (value < minValue)
                value = minValue;
            else if (value > maxValue)
                value = maxValue;

            field.setValue(value);
            config::setValue(field, value);
        }

    END_WIDGET()
}

template <typename T>
void ConfigInputFloat(const char* name, ConfigField<T>& field, const char* description = nullptr) {
    START_WIDGET()

        if (ImGui::InputFloat(name, &value)) {
            field.setValue(value);
            config::setValue(field, value);
        }

    END_WIDGET()
}

template <typename T>
void ConfigInputFloat(const char* name, ConfigField<T>& field, float minValue, float maxValue,
    const char* description = nullptr) {
    START_WIDGET()

        if (ImGui::InputFloat(name, &value)) {
            if (value < minValue)
                value = minValue;
            else if (value > maxValue)
                value = maxValue;

            field.setValue(value);
            config::setValue(field, value);
        }

    END_WIDGET()
}

template <typename T>
void ConfigSliderInt(const char* name, ConfigField<T>& field, const int min, const int max,
    const char* description = nullptr) {
    START_WIDGET()

        if (ImGui::SliderInt(name, &value, min, max)) {
            field.setValue(value);
            config::setValue(field, value);
        }

    END_WIDGET()
}

template <typename T>
void ConfigDragInt(const char* name, ConfigField<T>& field, const int step, const int min, const int max,
    const char* description = nullptr) {
    START_WIDGET()

        if (ImGui::DragInt(name, &value, static_cast<float>(step), min, max, nullptr,
            ImGuiSliderFlags_AlwaysClamp)) {
            field.setValue(value);
            config::setValue(field, value);
        }

    END_WIDGET()
}

template <typename T>
void ConfigDragFloat(const char* name, ConfigField<T>& field, const float step, const float min, const float max,
    const char* description = nullptr) {
    START_WIDGET()

        if (ImGui::DragFloat(name, &value, step, min, max, nullptr,
            ImGuiSliderFlags_AlwaysClamp)) {
            field.setValue(value);
            config::setValue(field, value);
        }

    END_WIDGET()
}


template <typename T>
void ConfigSliderFloat(const char* name, ConfigField<T>& field, const float min, const float max,
    const char* description = nullptr) {
    START_WIDGET()

        if (ImGui::SliderFloat(name, &value, min, max)) {
            field.setValue(value);
            config::setValue(field, value);
        }

    END_WIDGET()
}

template <typename T>
void ColorToggleButton(const char* label, ConfigField<T>& field, ImVec4 col = ImVec4(0.0f, 0.0f, 0.0f, 0.0f),
    const char* description = nullptr) {
    START_WIDGET()

        if (value)
            if (col.x == 0.0f && col.y == 0.0f && col.z == 0.0f && col.w == 0.0f)
                ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyle().Colors[ImGuiCol_ButtonActive]);
            else
                ImGui::PushStyleColor(ImGuiCol_Button, col);
        else
            ImGui::PushStyleColor(ImGuiCol_Button, ImGuiCol_Button);

    if (ImGui::Button(label)) {
        value = !value;
        field.setValue(value);
        config::setValue(field, value);
    }

    ImGui::PopStyleColor();
    END_WIDGET()
}

template <typename T>
void ConfigCombo(const char* name, ConfigField<T>& field, int* current_item, const char* const items[], int items_count,
    int height_in_items, const char* description = nullptr) {
    START_WIDGET()

        if (ImGui::Combo(name, &value, items, items_count, height_in_items)) {
            field.setValue(value);
            config::setValue(field, value);
        }

    END_WIDGET()
}

void ConfigComboLanguage(ConfigField<int>& f_Language);

void AddUnderLine(ImColor color);
void TextURL(const char* name, const char* url, bool sameLineBefore, bool sameLineAfter);
