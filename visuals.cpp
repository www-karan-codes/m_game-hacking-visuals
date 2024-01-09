#include "visuals.hpp"

#include "../Aimbot/aimbot_visuals.hpp"
#include "../ESP/esp_visuals.hpp"
#include "../Radar/radar_visuals.hpp"

#include "../Aimbot/aimbot.hpp"

#include "../ImGui/imgui.h"
#include "../ImGui/backends/imgui_impl_dx9.h"

#include "../Math/math.hpp"
#include "../GameFunctions/game_functions.hpp"


using gamehacking::math::Vector3D;

Vector3D::operator ImVec2()
{
	ImVec2 vector;
	vector.x = x_;
	vector.y = y_;
	return vector;
}

Vector3D::Vector3D(ImVec2& v)
{
	x_ = v.x;
	y_ = v.y;
	z_ = 0;
}

Vector3D Vector3D::operator=(ImVec2& v)
{
	return Vector3D(v.x, v.y, 0);
}

namespace gamehacking::visuals
{
	/*
	bool initialised = false;

	void Setup(void)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.IniFilename = NULL;
		(void)io;

		ImGui_ImplWin32_Init(game_hwnd);
		ImGui_ImplDX9_Init(game_device);
	}
	*/

	bool show_imgui_menu = false;

	void Draw(void)
	{
		gamehacking::aimbot::visuals::Draw();

		gamehacking::esp::visuals::Draw();
		gamehacking::radar::visuals::Draw();

		ImGui::SetNextWindowPos({ 0, 0 });
		ImGui::SetNextWindowSize(gamehacking::game_functions::GetResolution());
		ImGui::Begin("crosshair", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBringToFrontOnFocus);

		auto imgui_draw_list = ImGui::GetWindowDrawList();

		gamehacking::math::Vector3D center = gamehacking::game_functions::GetResolution();
		center = center / 2;

		imgui_draw_list->AddCircle(center, 3, ImColor(255, 255, 255, 255));

		ImGui::End();

		if (gamehacking::visuals::show_imgui_menu)
		{
			ImGui::Begin("Settings");
			ImGui::Checkbox("Target everyone", &gamehacking::aimbot::settings::target_everyone);
			ImGui::Checkbox("Auto lock to new target", &gamehacking::aimbot::settings::auto_lock_to_new_target);
			ImGui::End();
		}
	}
}