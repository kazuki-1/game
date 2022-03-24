#pragma once
#include <d3d11.h>
#include <memory>
#include <DirectXMath.h>
#include "../../External/ImGui/imgui.h"
#include "../../External/ImGui/imgui_impl_dx11.h"
#include "../../External/ImGui/imgui_impl_win32.h"
#include "../../External/ImGui/imfilebrowser.h"
#include "Singleton.h"
#include "DROPMANAGER.h"
#include "DirectX11.h"
using namespace DirectX;

class IMGUI : public SINGLETON<IMGUI>
{
    ImGuiContext* imContext;
    ImVec4 default_colour;
    ImVec4 highlighted_colour;
    ImVec4 colour;
public:
    HRESULT Initialize(HWND hwnd)
    {
        imContext = { ImGui::CreateContext() };
        ImGui::SetCurrentContext(imContext);
        ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        default_colour = ImGui::GetStyleColorVec4(ImGuiCol_FrameBg);
        highlighted_colour = { default_colour.x * 1.1f, default_colour.w * 1.1f , default_colour.x * 1.1f , default_colour.w };
        colour = default_colour;
        return ImGui_ImplWin32_Init(hwnd) ? S_OK : E_FAIL;
        //return s ? S_OK : E_FAIL;
    }
    HRESULT Initialize(DirectX11* dx)
    {
        return ImGui_ImplDX11_Init(dx->Device(), dx->DeviceContext()) ? S_OK : E_FAIL;
    }


    void UpdatePlatformWindows()
    {
    }
    void SetWindowSize(XMFLOAT2 size)
    {
        ImGui::SetWindowSize({ size.x, size.y });
    }
    void SetWindowPos(XMFLOAT2 pos)
    {
        ImGui::SetWindowPos({ pos.x, pos.y });
    }
    void Execute()
    {
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
    }
    void Render()
    {
        //Execute();
        ImGui::Render();

        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        if (!(ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable))
            return;
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
    void End()
    {
        ImGui_ImplWin32_Shutdown();
        ImGui_ImplDX11_Shutdown();
        ImGui::DestroyContext(imContext);
        //delete imContext;
    };

    void CreatePopup(std::string error_string, bool* status)
    {
        if (!*status )
            return;
        ImGui::OpenPopup("Error");

        if (ImGui::BeginPopupModal("Error")) {
            ImGui::Text(error_string.c_str());
            if (ImGui::Button("Ok")) {
                ImGui::CloseCurrentPopup();

                *status = false;
            }
            ImGui::EndPopup();
        }

    }
    void InputText(std::string label, std::string* str)
    {
        ImGui::PushStyleColor(ImGuiCol_FrameBg, default_colour);
        ImGui::InputText(label.c_str(), (char*)str->c_str(), 256);
        if (ImGui::IsItemHovered())
        {
            //colour = highlighted_colour;
            ImVec2 min, max;
            min = ImGui::GetItemRectMin();
            max = ImGui::GetItemRectMax();
            ImGui::GetWindowDrawList()->AddRectFilled(min, max, IM_COL32(0, 255, 255, 100));
            if (DROPMANAGER::Instance()->Loaded())
                *str = DROPMANAGER::Instance()->Path();
        }
        else
            colour = default_colour;
        ImGui::PopStyleColor();
    }
    void InputText(std::string label, std::wstring* str)
    {
        ImGui::PushStyleColor(ImGuiCol_FrameBg, default_colour);
        ImGui::InputText(label.c_str(), (char*)str->c_str(), 256);
        if (ImGui::IsItemHovered())
        {
            //colour = highlighted_colour;
            ImVec2 min, max;
            min = ImGui::GetItemRectMin();
            max = ImGui::GetItemRectMax();
            ImGui::GetWindowDrawList()->AddRectFilled(min, max, IM_COL32(0, 255, 255, 100));
            if (DROPMANAGER::Instance()->Loaded())
                *str = DROPMANAGER::Instance()->WPath();
        }
        else
            colour = default_colour;
        ImGui::PopStyleColor();
    }
};