#include <vector>
#include <algorithm>
#include <windows.h>
#include <urlmon.h>
#pragma comment(lib, "urlmon.lib")
bool applied = false;
static bool sh_save_cfg = false;
static bool sh_load_cfg = false;
bool Remove = false;
bool create = false;
#include <chrono>
bool rus = false;


#include "discord/Discord.h"
#include <xstring>
float menuposx = 100;
float menuposy = 100;
typedef BOOL(APIENTRY* oSetCursorPos)(int, int);
oSetCursorPos pSetCursorPos = NULL;
long getMils() {
	auto duration = std::chrono::system_clock::now().time_since_epoch();

	return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}
ImVec2 menupos;
int y = 0;
#include <map>

bool tab(const char* icon, const char* label, bool selected)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(std::string(icon + std::string(label)).c_str());
	const ImVec2 label_size = ImGui::CalcTextSize(label);

	ImVec2 pos = window->DC.CursorPos;
	ImVec2 size = { 50 , 30 };

	const ImRect bb(pos, ImVec2(pos.x + 50, pos.y + 30));
	ImGui::ItemSize(size, 0);
	if (!ImGui::ItemAdd(bb, id))
		return false;

	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

	if (hovered || held)
		ImGui::SetMouseCursor(7);

	float t = selected ? 1.0f : 0.0f;
	float deltatime = 1.5f * ImGui::GetIO().DeltaTime;
	static std::map<ImGuiID, float> hover_animation;
	auto it_hover = hover_animation.find(id);
	if (it_hover == hover_animation.end())
	{
		hover_animation.insert({ id, 0.f });
		it_hover = hover_animation.find(id);
	}
	it_hover->second = ImClamp(it_hover->second + (0.2f * ImGui::GetIO().DeltaTime * (hovered || ImGui::IsItemActive() ? 1.f : -1.f)), 0.0f, 0.15f);
	it_hover->second *= min(255 * 1.2, 1.f);

	static std::map<ImGuiID, float> filled_animation;
	auto it_filled = filled_animation.find(id);
	if (it_filled == filled_animation.end())
	{
		filled_animation.insert({ id, 0.f });
		it_filled = filled_animation.find(id);
	}
	it_filled->second = ImClamp(it_filled->second + (2.55f * ImGui::GetIO().DeltaTime * (selected ? 1.f : -1.0f)), it_hover->second, 1.f);
	it_filled->second *= min(255 * 1.2, 1.f);

	static std::map<ImGuiID, float> fill_animation;
	auto it_fill = fill_animation.find(id);
	if (it_fill == fill_animation.end())
	{
		fill_animation.insert({ id, 0.f });
		it_fill = fill_animation.find(id);
	}
	static float line_pos = 0.f;
	it_fill->second = ImClamp(it_filled->second + (1.75f * ImGui::GetIO().DeltaTime * (selected ? 1.f : -1.0f)), it_hover->second, 1.f);
	it_fill->second *= min(255 * 1.2, 1.f);
	auto draw = ImGui::GetWindowDrawList();
	ImVec4 text = ImLerp(ImVec4{ 128 / 255.f, 128 / 255.f, 128 / 255.f, ImGui::GetStyle().Alpha }, ImVec4{ 255 / 255.f, 255 / 255.f, 255 / 255.f, ImGui::GetStyle().Alpha }, it_filled->second);
	ImVec4 text2 = ImLerp(ImVec4{ 120 / 255.f, 120 / 255.f, 120 / 255.f, ImGui::GetStyle().Alpha }, ImVec4{ 203 / 255.f, 207 / 255.f, 206 / 255.f, ImGui::GetStyle().Alpha }, it_filled->second);//203, 207, 206
	draw->AddRectFilled(ImVec2(bb.Min.x + 8, bb.Min.y), ImVec2(bb.Min.x + 42, bb.Min.y + 32), ImColor(35, 35, 35, int(255 * it_filled->second)), 5);
	draw->AddRectFilled(ImVec2(bb.Max.x - 3, bb.Min.y + 7.5), ImVec2(bb.Max.x, bb.Max.y - 7.5), ImColor(130, 20, 20, int(255 * it_filled->second)), 3, ImDrawFlags_RoundCornersLeft);
	/*line_pos = ImLerp(line_pos, selected ? bb.Min.y - window->Pos.y : line_pos, 0.04f);
	draw->AddRectFilled({ bb.Max.x - 2, window->Pos.y + line_pos }, { bb.Max.x, window->Pos.y + line_pos + size.y }, (209, 235, 103, int(255 * it_filled->second)), 2, ImDrawFlags_RoundCornersLeft);*/
	draw->AddText(ImVec2(bb.Min.x - (ImGui::CalcTextSize(icon).x / 2) + 26, bb.Min.y - (ImGui::CalcTextSize(icon).y / 2) + 16), ImColor(text2), icon);
	/*ImGui::PushFont(fonts::semibold);
	draw->AddText(ImVec2(bb.Min.x + (ImGui::CalcTextSize(icon).x / 2) + 17, bb.Min.y - (ImGui::CalcTextSize(label).y / 2) + 15), ImColor(text2), label);
	ImGui::PopFont();*/

	return pressed;
}
bool SUStab(const char* icon, const char* label, bool selected)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(std::string(icon + std::string(label)).c_str());
	const ImVec2 label_size = ImGui::CalcTextSize(icon);

	ImVec2 pos = window->DC.CursorPos;
	ImVec2 size = { label_size.x + 17, 34 };

	const ImRect bb(pos, ImVec2(pos.x + label_size.x, pos.y + 34));
	ImGui::ItemSize(size, 0);
	if (!ImGui::ItemAdd(bb, id))
		return false;

	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

	if (hovered || held)
		ImGui::SetMouseCursor(7);

	float t = selected ? 1.0f : 0.0f;
	float deltatime = 1.5f * ImGui::GetIO().DeltaTime;
	static std::map<ImGuiID, float> hover_animation;
	auto it_hover = hover_animation.find(id);
	if (it_hover == hover_animation.end())
	{
		hover_animation.insert({ id, 0.f });
		it_hover = hover_animation.find(id);
	}
	it_hover->second = ImClamp(it_hover->second + (0.2f * ImGui::GetIO().DeltaTime * (hovered || ImGui::IsItemActive() ? 1.f : -1.f)), 0.0f, 0.15f);
	it_hover->second *= min(ImGui::GetStyle().Alpha * 1.2, 1.f);

	static std::map<ImGuiID, float> filled_animation;
	auto it_filled = filled_animation.find(id);
	if (it_filled == filled_animation.end())
	{
		filled_animation.insert({ id, 0.f });
		it_filled = filled_animation.find(id);
	}
	it_filled->second = ImClamp(it_filled->second + (2.55f * ImGui::GetIO().DeltaTime * (selected ? 1.f : -1.0f)), it_hover->second, 1.f);
	it_filled->second *= min(ImGui::GetStyle().Alpha * 1.2, 1.f);

	static std::map<ImGuiID, float> fill_animation;
	auto it_fill = fill_animation.find(id);
	if (it_fill == fill_animation.end())
	{
		fill_animation.insert({ id, 0.f });
		it_fill = fill_animation.find(id);
	}
	it_fill->second = ImClamp(it_filled->second + (1.75f * ImGui::GetIO().DeltaTime * (selected ? 1.f : -1.0f)), it_hover->second, 1.f);
	it_fill->second *= min(ImGui::GetStyle().Alpha * 1.2, 1.f);
	auto draw = ImGui::GetWindowDrawList();
	ImVec4 text = ImLerp(ImVec4{ 128 / 255.f, 128 / 255.f, 128 / 255.f, ImGui::GetStyle().Alpha }, ImVec4{ 224 / 255.f, 152 / 255.f, 25 / 255.f, ImGui::GetStyle().Alpha }, it_filled->second);
	ImVec4 text2 = ImLerp(ImVec4{ 128 / 255.f, 128 / 255.f, 128 / 255.f, ImGui::GetStyle().Alpha }, ImVec4{ 203 / 255.f, 207 / 255.f, 206 / 255.f, ImGui::GetStyle().Alpha }, it_filled->second);//203, 207, 206
   /* draw->AddRectFilled(ImVec2(bb.Min.x , bb.Min.y ), ImVec2(bb.Max.x , bb.Max.y ), ImColor(26, 26, 26, int(255 * it_filled->second)));
	draw->AddRectFilled(ImVec2(bb.Min.x, bb.Min.y), ImVec2(bb.Min.x + 2, bb.Max.y), ImColor(192, 159, 201, int(255 * it_filled->second)));*/
	draw->AddText(ImVec2(bb.Min.x, bb.Min.y), ImColor(text2), icon);

	draw->AddText(ImVec2(bb.Min.x + 60, bb.Min.y), ImColor(text2), label);


	return pressed;
}
bool SubTabEx(const char* label, const bool active, const ImVec2& size_arg, ImGuiButtonFlags flags)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;
	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = Cuniaabyser1->CalcTextSizeA(15.f, FLT_MAX, 0.f, label);

	ImVec2 pos = window->DC.CursorPos;
	if ((flags & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset) // Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
		pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
	ImVec2 size = ImGui::CalcItemSize(size_arg, label_size.x + style.FramePadding.x, label_size.y + style.FramePadding.y);

	const ImRect bb(pos, pos + size);
	ImGui::ItemSize(size, style.FramePadding.y);
	if (!ImGui::ItemAdd(bb, id))
		return false;

	if (g.LastItemData.InFlags & ImGuiItemFlags_ButtonRepeat)
		flags |= ImGuiButtonFlags_Repeat;
	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, flags);
	if (pressed)
		ImGui::MarkItemEdited(id);
	ImGui::RenderNavHighlight(bb, id);
	struct TabAnimation {
		ImColor RectFilen;
		ImColor MultiRect;
		ImColor MultiRect2;

		ImColor Text;
		float CirclePos;
	};

	static std::map< ImGuiID, TabAnimation > TabMap;
	auto TabItemMap = TabMap.find(id);
	if (TabItemMap == TabMap.end()) {
		TabMap.insert({ id, TabAnimation() });
		TabItemMap = TabMap.find(id);
	}
	static std::map<ImGuiID, float> filled_animation;
	auto it_filled = filled_animation.find(id);
	ImColor one = ImColor(130, 20, 20, 255 * 0.2), two = ImColor(130, 20, 20, 0);
	TabItemMap->second.RectFilen = ImLerp(TabItemMap->second.RectFilen.Value, active ? ImColor(130, 20, 20) : ImColor(0, 0, 0, 0), g.IO.DeltaTime * 8.f * 0.8);
	TabItemMap->second.MultiRect = ImLerp(TabItemMap->second.MultiRect.Value, active ? ImColor(130, 20, 20, 255 * 0.2) : ImColor(0, 0, 0, 0), g.IO.DeltaTime * 8.f * 0.8);
	TabItemMap->second.MultiRect2 = ImLerp(TabItemMap->second.MultiRect2.Value, active ? ImColor(130, 20, 20, 0) : ImColor(0, 0, 0, 0), g.IO.DeltaTime * 8.f * 0.8);


	window->DrawList->AddRectFilled(ImVec2(bb.Min.x, bb.Min.y), ImVec2(bb.Max.x, bb.Min.y), TabItemMap->second.RectFilen, 4, ImDrawFlags_RoundCornersBottom);



	//window->DrawList->AddRectFilledMultiColor(ImVec2(bb.Min.x, bb.Max.y - 25), bb.Max, TabItemMap->second.MultiRect2, TabItemMap->second.MultiRect2, TabItemMap->second.MultiRect, TabItemMap->second.MultiRect);
	//}

	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(active ? ImColor(255, 255, 255) : hovered ? ImColor(200, 200, 200) : ImColor(110, 110, 110)));

	ImGui::PushFont(Cuniaabyser1);
	ImGui::RenderTextClipped(bb.Min, bb.Max, label, NULL, &label_size, ImVec2(0.5, 0.5), &bb);
	ImGui::PopFont();

	ImGui::PopStyleColor();

	IMGUI_TEST_ENGINE_ITEM_INFO(id, icon, window->DC.LastItemStatusFlags);
	return pressed;
}
bool SubTab(const char* label, const bool active, const ImVec2& size_arg)
{
	return SubTabEx(label, active, size_arg, 0);
}

/*                     CHEATNAME GUI                     */
bool TabEx(const char* icon, const char* label, const bool active, const ImVec2& size_arg, ImGuiButtonFlags flags)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;
	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(icon);
	const ImVec2 icon_size = fIcons->CalcTextSizeA(20, FLT_MAX, 0, icon, NULL);
	const ImVec2 label_size = fMain->CalcTextSizeA(15, FLT_MAX, 0, label, NULL);

	ImVec2 pos = window->DC.CursorPos;
	if ((flags & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset) // Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
		pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
	ImVec2 size = ImGui::CalcItemSize(size_arg, label_size.x + style.FramePadding.x, label_size.y + style.FramePadding.y);

	const ImRect bb(pos, pos + size);
	ImGui::ItemSize(size, style.FramePadding.y);
	if (!ImGui::ItemAdd(bb, id))
		return false;

	if (g.LastItemData.InFlags & ImGuiItemFlags_ButtonRepeat)
		flags |= ImGuiButtonFlags_Repeat;
	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, flags);
	if (pressed)
		ImGui::MarkItemEdited(id);
	ImGui::RenderNavHighlight(bb, id);
	struct TabAnimation {
		ImColor RectFilen;
		ImColor MultiRect;
		ImColor MultiRect2;
		ImColor Text;
		float CirclePos;
	};

	static std::map< ImGuiID, TabAnimation > TabMap;
	auto TabItemMap = TabMap.find(id);
	if (TabItemMap == TabMap.end()) {
		TabMap.insert({ id, TabAnimation() });
		TabItemMap = TabMap.find(id);
	}
	ImColor one = ImColor(130, 20, 20, 255 * 0.2), two = ImColor(130, 20, 20, 0);
	TabItemMap->second.RectFilen = ImLerp(TabItemMap->second.RectFilen.Value, active ? ImColor(130, 20, 20) : ImColor(0, 0, 0, 0), g.IO.DeltaTime * 8.f * 0.8);
	TabItemMap->second.MultiRect = ImLerp(TabItemMap->second.MultiRect.Value, active ? ImColor(130, 20, 20, 255 * 0.2) : ImColor(0, 0, 0, 0), g.IO.DeltaTime * 8.f * 0.8);
	TabItemMap->second.MultiRect2 = ImLerp(TabItemMap->second.MultiRect2.Value, active ? ImColor(130, 20, 20, 0) : ImColor(0, 0, 0, 0), g.IO.DeltaTime * 8.f * 0.8);
	/*  if (active)
	  {*/
	window->DrawList->AddRectFilled(bb.Min, ImVec2(bb.Min.x + 4, bb.Max.y), TabItemMap->second.RectFilen, 4, ImDrawFlags_RoundCornersRight);

	window->DrawList->AddRectFilledMultiColor(bb.Min, ImVec2(bb.Min.x + 100, bb.Max.y), TabItemMap->second.MultiRect, TabItemMap->second.MultiRect2, TabItemMap->second.MultiRect2, TabItemMap->second.MultiRect);
	//}

	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(active ? ImColor(255, 255, 255) : hovered ? ImColor(200, 200, 200) : ImColor(100, 100, 100)));

	ImGui::RenderTextClipped(bb.Min + ImVec2(30, 0), bb.Max - style.FramePadding, icon, NULL, &icon_size, ImVec2(0.f, 0.5f), &bb);

	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(active ? ImColor(255, 255, 255) : hovered ? ImColor(200, 200, 200) : ImColor(100, 100, 100)));

	ImGui::PushFont(fMain);
	ImGui::RenderTextClipped(bb.Min + ImVec2(55, 0), bb.Max - style.FramePadding, label, NULL, &label_size, ImVec2(0.f, 0.5f), &bb);
	ImGui::PopFont();

	ImGui::PopStyleColor(2);


	IMGUI_TEST_ENGINE_ITEM_INFO(id, icon, window->DC.LastItemStatusFlags);
	return pressed;
}
bool Tab(const char* icon, const char* label, const bool active, const ImVec2& size_arg)
{
	return TabEx(icon, label, active, size_arg, 0);
}

bool MenuChildEx(const char* name, ImGuiID id, const ImVec2& size_arg, bool border, ImGuiWindowFlags flags)
{
	ImGuiContext& g = *GImGui;
	ImGuiWindow* parent_window = g.CurrentWindow;

	flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_ChildWindow | ImGuiWindowFlags_NoMove;
	//flags |= (parent_window->Flags & ImGuiWindowFlags_NoMove);  // Inherit the NoMove flag

	// Size
	const ImVec2 content_avail = ImGui::GetContentRegionAvail();
	ImVec2 size = ImFloor(size_arg);
	const int auto_fit_axises = ((size.x == 0.0f) ? (1 << ImGuiAxis_X) : 0x00) | ((size.y == 0.0f) ? (1 << ImGuiAxis_Y) : 0x00);
	if (size.x <= 0.0f)
		size.x = ImMax(content_avail.x + size.x, 4.0f); // Arbitrary minimum child size (0.0f causing too much issues)
	if (size.y <= 0.0f)
		size.y = ImMax(content_avail.y + size.y, 4.0f);
	ImGui::SetNextWindowSize(size);

	// Build up name. If you need to append to a same child from multiple location in the ID stack, use BeginChild(ImGuiID id) with a stable value.
	char title[256];

	const char* temp_window_name;
	if (name)
		ImFormatStringToTempBuffer(&temp_window_name, NULL, "%s/%s_%08X", parent_window->Name, name, id);
	else
		ImFormatStringToTempBuffer(&temp_window_name, NULL, "%s/%08X", parent_window->Name, id);

	const float backup_border_size = g.Style.ChildBorderSize;
	if (!border)
		g.Style.ChildBorderSize = 0.0f;
	bool ret = ImGui::Begin(temp_window_name, NULL, flags);
	g.Style.ChildBorderSize = backup_border_size;
	ImGuiWindow* child_window = g.CurrentWindow;
	child_window->ChildId = id;
	child_window->AutoFitChildAxises = (ImS8)auto_fit_axises;

	// Set the cursor to handle case where the user called SetNextWindowPos()+BeginChild() manually.
	// While this is not really documented/defined, it seems that the expected thing to do.
	if (child_window->BeginCount == 1)
		parent_window->DC.CursorPos = child_window->Pos;

	auto p = parent_window->DC.CursorPos;
	//parent_window->DrawList->AddRect(p, p + size, ImColor(30, 30, 30), 4, 15, 2);
	if (!(flags & ImGuiWindowFlags_NoTitleBar))
	{
		auto size_text = fMain->CalcTextSizeA(15, FLT_MAX, 0, name);
		parent_window->DrawList->AddText(fMain, 15, ImVec2(p.x + (size.x - size_text.x) / 2, p.y + 10), ImColor(255, 255, 255), name);
		//	parent_window->DrawList->AddRectFilled(ImVec2(p.x + 10, p.y + 30), ImVec2(p.x + size.x - 10, p.y + 34), ImColor(130, 20, 20));
	}

	// Process navigation-in immediately so NavInit can run on first frame
	if (g.NavActivateId == id && !(flags & ImGuiWindowFlags_NavFlattened) && (child_window->DC.NavLayersActiveMask != 0 || child_window->DC.NavHasScroll))
	{
		ImGui::FocusWindow(child_window);
		ImGui::NavInitWindow(child_window, false);
		ImGui::SetActiveID(id + 1, child_window); // Steal ActiveId with a dummy id so that key-press won't activate child item
		g.ActiveIdSource = ImGuiInputSource_Nav;
	}
	if (!(flags & ImGuiWindowFlags_NoTitleBar))
		ImGui::SetCursorPosY(40);
	return ret;
}
bool MenuChild(const char* str_id, const ImVec2& size_arg, bool border, ImGuiWindowFlags extra_flags)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	return MenuChildEx(str_id, window->GetID(str_id), size_arg, false, extra_flags);
}

bool Checkbox_(const char* label, bool* v)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

	const float square_sz = ImGui::GetFrameHeight();
	const ImVec2 pos = window->DC.CursorPos;
	const ImRect total_bb(pos, pos + ImVec2(square_sz + (label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f), label_size.y + style.FramePadding.y * 2.0f));
	ImGui::ItemSize(total_bb, style.FramePadding.y);
	if (!ImGui::ItemAdd(total_bb, id))
		return false;

	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(total_bb, id, &hovered, &held);
	if (pressed)
	{
		*v = !(*v);
		ImGui::MarkItemEdited(id);
	}

	const ImRect check_bb(pos, pos + ImVec2(square_sz, square_sz));
	ImGui::RenderNavHighlight(total_bb, id);
	struct TabAnimation {
		ImColor CheckboxFrame;
		ImColor CircleFrame;
		ImColor Text;
		float CirclePos;
	};

	static std::map< ImGuiID, TabAnimation > TabMap;
	auto TabItemMap = TabMap.find(id);
	if (TabItemMap == TabMap.end()) {
		TabMap.insert({ id, TabAnimation() });
		TabItemMap = TabMap.find(id);
	}
	TabItemMap->second.CheckboxFrame = ImLerp(TabItemMap->second.CheckboxFrame.Value, *v ? ImColor(130, 20, 20) : ImColor(130, 20, 20, 170), g.IO.DeltaTime * 8.f * 0.8);
	TabItemMap->second.CircleFrame = ImLerp(TabItemMap->second.CircleFrame.Value, *v ? ImColor(130, 20, 20) : ImColor(0, 0, 0, 0), g.IO.DeltaTime * 8.f * 0.8);
	window->DrawList->AddRect(check_bb.Min, check_bb.Max, TabItemMap->second.CheckboxFrame, 4);

	window->DrawList->AddRectFilled(check_bb.Min + ImVec2(3, 3), check_bb.Max - ImVec2(3, 3), TabItemMap->second.CircleFrame, 4);

	if (g.LogEnabled)
		ImGui::LogRenderedText(&total_bb.Min, *v ? "[x]" : "[ ]");
	if (label_size.x > 0.0f)
		ImGui::RenderText(ImVec2(check_bb.Max.x + style.ItemInnerSpacing.x, check_bb.Min.y + style.FramePadding.y), label);

	IMGUI_TEST_ENGINE_ITEM_INFO(id, label, window->DC.ItemFlags | ImGuiItemStatusFlags_Checkable | (*v ? ImGuiItemStatusFlags_Checked : 0));
	return pressed;
}


struct checkbox_element {
	float selected_rect;
};

bool Checkbox__(const char* label, bool* v)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

	const float square_sz = ImGui::GetFrameHeight();
	const ImVec2 pos = window->DC.CursorPos;
	const ImRect total_bb(pos, ImVec2(pos.x + 100, pos.y + 20));
	ImGui::ItemSize(total_bb, style.FramePadding.y);
	if (!ImGui::ItemAdd(total_bb, id))
		return false;

	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(total_bb, id, &hovered, &held);
	float t = *v ? 1.0f : 0.0f;
	float deltatime = 1.5f * ImGui::GetIO().DeltaTime;
	static std::map<ImGuiID, float> hover_animation;
	auto it_hover = hover_animation.find(id);
	if (it_hover == hover_animation.end())
	{
		hover_animation.insert({ id, 0.f });
		it_hover = hover_animation.find(id);
	}
	it_hover->second = ImClamp(it_hover->second + (0.2f * ImGui::GetIO().DeltaTime * (hovered || ImGui::IsItemActive() ? 1.f : -1.f)), 0.0f, 0.15f);
	it_hover->second *= (ImGui::GetStyle().Alpha * 1.2, 1.f);

	static std::map<ImGuiID, float> filled_animation;
	auto it_filled = filled_animation.find(id);
	if (it_filled == filled_animation.end())
	{
		filled_animation.insert({ id, 0.f });
		it_filled = filled_animation.find(id);
	}
	it_filled->second = ImClamp(it_filled->second + (2.55f * ImGui::GetIO().DeltaTime * (*v ? 1.f : -1.0f)), it_hover->second, 1.f);
	it_filled->second *= (ImGui::GetStyle().Alpha * 1.2, 1.f);

	static std::map<ImGuiID, float> fill_animation;
	auto it_fill = fill_animation.find(id);
	if (it_fill == fill_animation.end())
	{
		fill_animation.insert({ id, 0.f });
		it_fill = fill_animation.find(id);
	}
	it_fill->second = ImClamp(it_filled->second + (1.75f * ImGui::GetIO().DeltaTime * (*v ? 1.f : -1.0f)), it_hover->second, 1.f);
	it_fill->second *= (ImGui::GetStyle().Alpha * 1.2, 1.f);
	ImVec4 text2 = ImLerp(ImVec4{ 128 / 255.f, 128 / 255.f, 128 / 255.f, ImGui::GetStyle().Alpha }, ImVec4{ 232 / 255.f, 232 / 255.f, 232 / 255.f, ImGui::GetStyle().Alpha }, it_filled->second);//124, 43, 186
	ImVec4 text = ImLerp(ImVec4{ 16 / 255.f, 16 / 255.f, 16 / 255.f, ImGui::GetStyle().Alpha }, ImVec4{ 110 / 255.f, 10 / 255.f, 10 / 255.f, ImGui::GetStyle().Alpha }, it_filled->second);//130, 20, 20
	ImVec4 text23 = ImLerp(ImVec4{ 25 / 255.f, 25 / 255.f, 25 / 255.f, 0 }, ImVec4{ 255 / 255.f, 255 / 255.f, 255 / 255.f, ImGui::GetStyle().Alpha }, it_filled->second);//124, 43, 186


	ImColor lol = *v ? ImColor(128, 128, 128) : ImColor(203, 207, 206);
	if (pressed)
	{
		*v = !(*v);

	}

	{

		window->DrawList->AddRect(ImVec2(total_bb.Min.x, total_bb.Min.y ), ImVec2(total_bb.Min.x + 14, total_bb.Min.y + 14), ImColor(23, 23, 23), 1);
		window->DrawList->AddRectFilled(ImVec2(total_bb.Min.x, total_bb.Min.y ), ImVec2(total_bb.Min.x + 14, total_bb.Min.y + 14), ImColor(text), 1);
		//window->DrawList->AddCircleFilled((window->DrawList, ImVec2(total_bb.Min.x + 5, total_bb.Min.y + 15)), 3.0f, ImColor(198 / 255.f, 198 / 255.f, 198 / 255.f), 30);//124, 43, 186
		ImGui::RenderCheckMark(window->DrawList, ImVec2({ total_bb.Min + ImVec2(3, 3) }), ImColor(text23), 8);

		if (label_size.x > 0.0f)
			window->DrawList->AddText(ImVec2(total_bb.Min.x + 20, total_bb.Min.y + 6 - ImGui::CalcTextSize(label).y / 2), ImColor(text2), label);
	}

	return pressed;

}


namespace Anime {
	bool reverse = false;
	//bool done = false;
	int offset = 0;
	bool show_popup = false;

	void Popup(const char* text, int onScreenMils, bool* done) {
		if (!done)
			show_popup = true;

		ImGuiIO& io = ImGui::GetIO();
		int Wd = io.DisplaySize.x;

		static long oldTime = -1;

		ImGui::SetNextWindowPos(ImVec2(Wd - offset, 7));
		ImGui::Begin("PopUp Window", &show_popup, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar);
		ImGui::BeginChild(("##linerender"), ImVec2(110, 1)); ImGui::EndChild();
		long currentTime_ms = getMils();

		ImVec2 txtSz = ImGui::CalcTextSize(text);
		ImGui::SetCursorPosY(ImGui::GetWindowHeight() / 2 - txtSz.y / 2);
		ImGui::Text(text);

		if (!reverse)
		{
			if (offset < ImGui::GetWindowWidth())
				offset += (ImGui::GetWindowWidth() + 5) * ((1000.0f / ImGui::GetIO().Framerate) / 100);

			if (offset >= ImGui::GetWindowWidth() && oldTime == -1)
			{

				oldTime = currentTime_ms;
			}
		}


		if (currentTime_ms - oldTime >= onScreenMils && oldTime != -1) // close after x mils
			reverse = true;

		if (reverse)
		{
			if (offset > 0)
				offset -= (ImGui::GetWindowWidth() + 5) * ((1000.0f / ImGui::GetIO().Framerate) / 100);
			if (offset <= 0)
			{
				offset = 0;
				reverse = false;
				*done = true;
				oldTime = -1;
				show_popup = false;

			}
		}

		ImGui::End();
	}
}
class dot
{
public:
	dot(Vector3 p, Vector3 v) {
		m_vel = v;
		m_pos = p;
	}

	void update();
	void draw();

	Vector3 m_pos, m_vel;
};

std::vector<dot*> dots = { };

void dot::update() {
	auto opacity = 100 / 255.0f;

	m_pos += m_vel * (opacity);
}

void dot::draw() {
	int opacity = 55.0f * (240 / 255.0f);
	auto draw = ImGui::GetWindowDrawList();


	ImGui::GetWindowDrawList()->AddRectFilled({ m_pos.x - 2, m_pos.y - 4 }, { m_pos.x , m_pos.y + 4 }, ImColor(130, 20, 20));
	ImGui::GetWindowDrawList()->AddRectFilled({ m_pos.x + 2, m_pos.y - 4 }, { m_pos.x + 4, m_pos.y + 4 }, ImColor(130, 20, 20));
	ImGui::GetWindowDrawList()->AddRectFilled({ m_pos.x , m_pos.y - 1 }, { m_pos.x + 4, m_pos.y + 1 }, ImColor(130, 20, 20));



}
void dot_draw() {
	struct screen_size {
		int x, y;
	}; screen_size sc;

	sc.x = 1920, sc.y = 1080;
	auto pos = ImGui::GetWindowPos();

	int s = rand() % 39;
	float elda = sc.x / 2;// 864, 610
	if (s == 0) {
		dots.push_back(new dot(Vector3(menupos.x - 4, 16 + menupos.y - 10, 0), Vector3(-(rand() % 3 + 1), -(rand() % 3 + 1), 0)));
		dots.push_back(new dot(Vector3(menupos.x + 860, 16 + menupos.y - 10, 0), Vector3((rand() % 3 + 1), -(rand() % 3 + 1), 0)));
		dots.push_back(new dot(Vector3(menupos.x - 4, 16 + menupos.y + 606, 0), Vector3(-(rand() % 3 + 1), (rand() % 3 + 1), 0)));
		dots.push_back(new dot(Vector3(menupos.x + 860, 16 + menupos.y + 606, 0), Vector3((rand() % 3 + 1), (rand() % 3 + 1), 0)));

	}



	auto alph = 135.0f * (240 / 255.0f);
	auto a_int = (int)(alph);

	ImGui::GetWindowDrawList()->AddRectFilled({ 0, 0 }, { (float)sc.x, (float)sc.y }, ImColor(a_int, 0, 0, 0));

	for (auto i = dots.begin(); i < dots.end();) {
		if ((*i)->m_pos.y < -20 || (*i)->m_pos.y > sc.y + 20 || (*i)->m_pos.x < -20 || (*i)->m_pos.x > sc.x + 20) {
			delete (*i);
			i = dots.erase(i);
		}
		else {
			(*i)->update();
			i++;
		}
	}

	for (auto i = dots.begin(); i < dots.end(); i++) {
		(*i)->draw();
	}
}
ImFont* initx;
void Init()
{
	// Setup
	auto front = ImGui::GetForegroundDrawList(); // also you can use GetWindowDrawList() or GetBackgroundDrawList()
	ImVec2 center = ImGui::GetIO().DisplaySize / 2.f;
	static ImColor fore_color(130, 20, 20);
	static ImColor back_color(0, 0, 0, 25);
	static float arc_size = 0.45f; // 0.f < x < 2.f
	static float radius = 30.f;
	static float thickness = 3.f;
	ImColor  Alpha = ImColor(0,0,0, Alpha);
	int screenWidthX = GetSystemMetrics(SM_CXSCREEN);
	int screenHeightY = GetSystemMetrics(SM_CYSCREEN);
	auto back = ImGui::GetBackgroundDrawList();

	////if (Alpha[3] < 65)
	////	Alpha.z += 0.5;
	//back->AddRectFilled(ImVec2(0, 0), ImVec2(screenWidthX, screenHeightY), ImColor(130, 20, 20, 65));


	//// Animation
	//static float position = 0.f;
	//position = ImLerp(position, IM_PI * 2.f, ImGui::GetIO().DeltaTime * 2.3f);

	//// Background
	//front->PathClear();
	//front->PathArcTo(center, radius, 0.f, 2.f * IM_PI, 35.f);
	//front->PathStroke(ImGui::GetColorU32(back_color.Value), 0, thickness);

	//// Foreground
	//front->PathClear();
	//front->PathArcTo(center, radius, IM_PI * 1.5f + position, IM_PI * (1.5f + arc_size) + position, 35.f);
	//front->PathStroke(ImGui::GetColorU32(fore_color.Value), 0, thickness);

	//auto MiddleX = vars::stuff::ScreenWidth / 2;
	//auto MiddleY = vars::stuff::ScreenHeight / 2;
	//ImVec2 inject = ImGui::CalcTextSize((u8"Satanic"));
	//ImVec2 discord = ImGui::CalcTextSize((u8"Poves#2455"));
	//g_Render->DrawString(MiddleX, MiddleY + 35, ImColor(255, 255, 255), render2::centered_x, Cuniaabyser12, 16, "Satanic Created By poves_Satanic");
	//g_Render->DrawString(MiddleX, MiddleY + 50, ImColor(255, 255, 255), render2::centered_x, Cuniaabyser12, 16, "discord.gg/Z7PncQSNN2");




	// Reset animation
	//if (position >= IM_PI * 1.90f)
	//	position = 0.f;
}
const char* const KeyNames[] = {
	"None",
	"Mouse1",
	"Mouse2",
	"Esc",
	"Mouse3",
	"Mouse4",
	"Mouse5",
	"None",
	"Back",
	"Tab",
	"None",
	"None",
	"Backspace",
	"Enter",
	"None",
	"None",
	"Shift",
	"Ctrl",
	"Alt",
	"Pause Break",
	"CapsLock",
	"VK_KANA",
	"Unknown",
	"VK_JUNJA",
	"VK_FINAL",
	"VK_KANJI",
	"Unknown",
	"Esc",
	"VK_CONVERT",
	"VK_NONCONVERT",
	"VK_ACCEPT",
	"VK_MODECHANGE",
	"Space",
	"Page Up",
	"Page Down",
	"End",
	"Home",
	"Left",
	"Up",
	"Right",
	"Down",
	"VK_SELECT",
	"VK_PRINT",
	"VK_EXECUTE",
	"Print Screen",
	"Ins",
	"Del",
	"VK_HELP",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"Left Windows",
	"Right Windows",
	"VK_APPS",
	"Unknown",
	"VK_SLEEP",
	"NUMPAD0",
	"NUMPAD1",
	"NUMPAD2",
	"NUMPAD3",
	"NUMPAD4",
	"NUMPAD5",
	"NUMPAD6",
	"NUMPAD7",
	"NUMPAD8",
	"NUMPAD9",
	"Multiply",
	"+",
	"Separator",
	"Subtract",
	"-",
	"/",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
	"F13",
	"F14",
	"F15",
	"F16",
	"F17",
	"F18",
	"F19",
	"F20",
	"F21",
	"F22",
	"F23",
	"F24",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Num Lock",
	"Scroll lock",
	"VK_OEM_NEC_EQUAL",
	"VK_OEM_FJ_MASSHOU",
	"VK_OEM_FJ_TOUROKU",
	"VK_OEM_FJ_LOYA",
	"VK_OEM_FJ_ROYA",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Left Shift",
	"Right Shift",
	"Left Ctrl",
	"Right Ctrl",
	"Left Alt",
	"Right Alt"
};


static bool _IsKeyPressedMap(ImGuiKey key, bool repeat = true)
{
	const int key_index = GImGui->IO.KeyMap[key];
	return (key_index >= 0) ? ImGui::IsKeyPressed((ImGuiKey)key_index, repeat) : false;
}
inline bool     FocusableItemRegister(ImGuiWindow* window, ImGuiID id) { IM_ASSERT(0); IM_UNUSED(window); IM_UNUSED(id); return false; }
bool KeyBind(const char* label, int& k, const ImVec2& size_arg = ImVec2(0, 0))
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	ImGuiIO& io = g.IO;
	const ImGuiStyle& style = g.Style;

	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
	ImVec2 size = ImGui::CalcItemSize(size_arg, ImGui::CalcItemWidth(), label_size.y + style.FramePadding.y * 1.0f);
	const ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + size);
	const ImRect total_bb(window->DC.CursorPos, frame_bb.Max);

	ImGui::ItemSize(total_bb, style.FramePadding.y);
	if (!ImGui::ItemAdd(total_bb, id))
		return false;

	const bool focus_requested = FocusableItemRegister(window, g.ActiveId == id);
	//const bool focus_requested_by_code = focus_requested && (window->FocusIdxAllCounter == window->FocusIdxAllRequestCurrent);
	//const bool focus_requested_by_tab = focus_requested && !focus_requested_by_code;

	const bool hovered = ImGui::ItemHoverable(frame_bb, id);

	if (hovered) {
		ImGui::SetHoveredID(id);
		g.MouseCursor = ImGuiMouseCursor_TextInput;
	}

	const bool user_clicked = hovered && io.MouseClicked[0];

	if (focus_requested || user_clicked) {
		if (g.ActiveId != id) {
			// Start edition
			memset(io.MouseDown, 0, sizeof(io.MouseDown));
			memset(io.KeysDown, 0, sizeof(io.KeysDown));
			k = 0;
		}
		ImGui::SetActiveID(id, window);
		ImGui::FocusWindow(window);
	}
	else if (io.MouseClicked[0]) {
		// Release focus when we click outside
		if (g.ActiveId == id)
			ImGui::ClearActiveID();
	}

	bool value_changed = false;
	int key = k;

	if (g.ActiveId == id) {
		for (auto i = 0; i < 5; i++) {
			if (io.MouseDown[i]) {
				switch (i) {
				case 0:
					key = VK_LBUTTON;
					break;
				case 1:
					key = VK_RBUTTON;
					break;
				case 2:
					key = VK_MBUTTON;
					break;
				case 3:
					key = VK_XBUTTON1;
					break;
				case 4:
					key = VK_XBUTTON2;
					break;
				}
				value_changed = true;
				ImGui::ClearActiveID();
			}
		}
		if (!value_changed) {
			for (auto i = VK_BACK; i <= VK_RMENU; i++) {
				if (io.KeysDown[i]) {
					key = i;
					value_changed = true;
					ImGui::ClearActiveID();
				}
			}
		}

		if (_IsKeyPressedMap(ImGuiKey_Escape)) {
			k = 0;
			ImGui::ClearActiveID();
		}
		else {
			k = key;
		}
	}

	// Render
	// Select which buffer we are going to display. When ImGuiInputTextFlags_NoLiveEdit is Set 'buf' might still be the old value. We Set buf to NULL to prevent accidental usage from now on.

	char buf_display[64] = "None";

	ImGui::RenderFrame(frame_bb.Min, frame_bb.Max, (ImColor(16, 16, 16)), true, 6.f);
	window->DrawList->AddRect(frame_bb.Min, frame_bb.Max, ImColor(37, 37, 36), 3);
	if (k != 0 && g.ActiveId != id) {
		strcpy_s(buf_display, KeyNames[k]);
	}
	else if (g.ActiveId == id) {
		strcpy_s(buf_display, "...");
	}

	const ImRect clip_rect(frame_bb.Min.x, frame_bb.Min.y, frame_bb.Min.x + size.x, frame_bb.Min.y + size.y); // Not using frame_bb.Max because we have adjusted size
	ImVec2 render_pos = frame_bb.Min + style.FramePadding;
	ImGui::RenderTextClipped(frame_bb.Min + style.FramePadding * 0.8, frame_bb.Max - style.FramePadding, buf_display, NULL, NULL, style.ButtonTextAlign, &clip_rect);

	if (label_size.x > 0)
		ImGui::RenderText(ImVec2(total_bb.Max.x + style.FramePadding.x, frame_bb.Min.y + style.FramePadding.y), label);

	return value_changed;
}
namespace EFFECT
{
#define min(x,y) ((x)<(y)?x:y)
#define wh(a) ImColor(1.f,1.f,1.f,a)
	void FX(ImDrawList* d, ImVec2 a, ImVec2 b, ImVec2 sz, ImVec2, float t)
	{
		static float fl;
		if ((rand() % 500) == 0) fl = t;


		for (int i = 0; i < 2000; ++i) {
			unsigned h = ImGui::GetID(d + i + int(t / 4));
			auto f = fmodf(t + fmodf(h / 777.f, 99), 99);
			auto tx = h % (int)sz.x;
			auto ty = h % (int)sz.y;
			if (f < 1) {
				auto py = ty - 300 * (1 - f);
				d->AddRectFilled({ a.x + tx, a.y + py }, { a.x + tx + 1.5f, a.y + py + 4.2f }, wh(1 - (f - 1) * 5.f));
			//	d->AddCircleFilled({ a.x + tx, a.y + py }, (6), wh(1 - (f - 1) * 5.f));

			}
			else if (f < 1.2f)
				d->AddCircle({ a.x + tx, a.y + ty }, (f - 1) * 10 + h % 5, wh(1 - (f - 1) * 5.f));
		}
	}
	void дождик()
	{
		ImGui::SetWindowSize({ 1920, 1080 });
		ImGui::SetCursorPos(ImVec2(0, 0));

		ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0,0,0,0 });
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
		ImVec2 size(1920, 1080);
		ImGui::Begin("##menu2", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoMove);
		{
			if (dotdraw) {

				auto pos_model = menupos + ImVec2{ 825, 0 };


			//	draw_list->PopClipRect();
				dot_draw();
			}
		}
		ImGui::End();

	}
}
void invis(bool background, bool dotdraw)
{
	if (background) {
		static float Alpha = 0.0f;
		int screenWidthX = GetSystemMetrics(SM_CXSCREEN);
		int screenHeightY = GetSystemMetrics(SM_CYSCREEN);
		auto back = ImGui::GetBackgroundDrawList();

		if (Alpha < 0.65f)
			Alpha += 0.005f;
		back->AddRectFilled(ImVec2(0, 0), ImVec2(screenWidthX , screenHeightY ), ImColor(0, 0, 0, 60));

		ImGuiIO& io = ImGui::GetIO();
		auto MiddleX = vars::stuff::ScreenWidth;
		auto MiddleY = vars::stuff::ScreenHeight;
		ImVec2 size(MiddleX, MiddleY);

		ImVec2 p0 = ImGui::GetItemRectMin();
		ImVec2 p1 = ImGui::GetItemRectMax();
	//	ImDrawList* draw_list = ImGui::GetWindowDrawList();


		ImVec2 mouse_data;
		mouse_data.x = (io.MousePos.x - p0.x) / size.x;
		mouse_data.y = (io.MousePos.y - p0.y) / size.y;


		EFFECT::FX(back, p0, p1, size, mouse_data, (float)ImGui::GetTime());
	}
}


bool lang(const char* label)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

	ImVec2 pos = window->DC.CursorPos;
	ImVec2 size = ImGui::CalcItemSize(label_size, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

	const ImRect bb(pos, pos + size);
	ImGui::ItemSize(size, style.FramePadding.y);
	if (!ImGui::ItemAdd(bb, id))
		return false;

	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

	if (hovered || held)
		ImGui::SetMouseCursor(0);
	window->DrawList->AddRectFilled(bb.Min - ImVec2(7, 7), bb.Min + ImVec2(20, 20), ImColor(26, 26, 26), 3);
	window->DrawList->AddRect(bb.Min - ImVec2(7, 7), bb.Min + ImVec2(20, 20), ImColor(37, 37, 36), 3);
	ImGui::PushFont(Cuniaabyser);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(129 / 255.f, 129 / 255.f, 129 / 255.f, 255 / 255.f));
	ImGui::RenderText(ImVec2(bb.Min.x, bb.Min.y), label);
	ImGui::PopStyleColor();
	ImGui::PopFont();

	return pressed;
}

namespace menu {
	struct TabInfo {
		ImRect bb;
		unsigned int index;
	};
	ImVec2 cursor_pos = { 0,0 };
	ImFont* title_font = nullptr, * tabs_font = nullptr, * menu_font = nullptr;
	static int tab_index = 0;
	static float border_bang = 1.0f;
	static int old_tab_index = 0;
	std::vector<TabInfo> tabs_info;

	void apply_fonts() {
		ImGuiIO& io = ImGui::GetIO();
		title_font = io.Fonts->AddFontFromFileTTF("", 24);
		tabs_font = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 16);
		menu_font = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 13);
	}
	void HelpMarker(const char* desc) {
		ImGui::TextDisabled(("[?]"));
		if (ImGui::IsItemHovered()) {
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextUnformatted(desc);
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}

	void HelpCheckbox(const char* desc, bool* v, const char* helptext) { Checkbox__(desc, v); ImGui::SameLine(); HelpMarker(helptext); }
	void style(ImGuiStyle* dst) {

		ImGuiStyle* style = dst ? dst : &ImGui::GetStyle();
		ImVec4* colors = style->Colors;

		colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
		colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 1.f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.29f, 0.48f, 0.54f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.29f, 0.48f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
		colors[ImGuiCol_Tab] = ImLerp(colors[ImGuiCol_Header], colors[ImGuiCol_TitleBgActive], 0.80f);
		colors[ImGuiCol_TabHovered] = colors[ImGuiCol_HeaderHovered];
		colors[ImGuiCol_TabActive] = ImLerp(colors[ImGuiCol_HeaderActive], colors[ImGuiCol_TitleBgActive], 0.60f);
		colors[ImGuiCol_TabUnfocused] = ImLerp(colors[ImGuiCol_Tab], colors[ImGuiCol_TitleBg], 0.80f);
		colors[ImGuiCol_TabUnfocusedActive] = ImLerp(colors[ImGuiCol_TabActive], colors[ImGuiCol_TitleBg], 0.40f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	}

	bool tab_info_already_exist(std::vector<TabInfo> infos, unsigned int index) {
		for (int i = 0; i < infos.size(); i++)
			if (infos[i].index == index) return true;

		return false;
	}
	void TabBorderAnim(unsigned int current_tab, unsigned int old_tab) {
		if (tabs_info.size() > 0) {
			ImGuiWindow* window = ImGui::GetCurrentWindow();
			if (window->SkipItems)
				return;
			auto& style = ImGui::GetStyle();
			auto old_tab_rect = tabs_info[old_tab].bb;
			auto tab_rect = tabs_info[current_tab].bb;
			auto tab_min = old_tab_rect.Min + (tab_rect.Min - old_tab_rect.Min) * border_bang;
			auto tab_max = old_tab_rect.Max + (tab_rect.Max - old_tab_rect.Max) * border_bang;
			window->DrawList->AddRectFilled(tab_min, tab_max, ImColor(110, 110, 110, 255), style.FrameRounding, ImDrawFlags_RoundCornersAll);
		}

	}
	IMGUI_API bool TabButton(const char* label, const ImVec2& size_arg, unsigned int index, ImGuiButtonFlags flags = 0) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);
		const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

		ImVec2 pos = window->DC.CursorPos;
		if ((flags & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset)
			pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
		ImVec2 size = ImGui::CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

		const ImRect bb(pos, pos + size);
		ImGui::ItemSize(bb, style.FramePadding.y);
		if (!ImGui::ItemAdd(bb, id))
			return false;

		if (g.LastItemData.InFlags & ImGuiItemFlags_ButtonRepeat)
			flags |= ImGuiButtonFlags_Repeat;
		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, flags);

		// Render
		const ImU32 col = ImGui::GetColorU32((hovered && held) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
		const ImU32 border_col = ImGui::GetColorU32((hovered && held) ? ImGui::GetColorU32(ImVec4(1, 1, 1, 0.7)) : hovered ? ImColor(110, 110, 110, 115) : ImGui::GetColorU32(ImVec4(1, 1, 1, 0.0)));
		window->DrawList->AddRectFilled(bb.Min, bb.Max, border_col, style.FrameRounding, ImDrawFlags_RoundCornersAll);
		ImGui::RenderTextClipped(bb.Min + style.FramePadding, bb.Max - style.FramePadding, label, NULL, &label_size, style.ButtonTextAlign, &bb);
		if (!tab_info_already_exist(tabs_info, index)) {
			TabInfo tab_info;
			tab_info.bb = bb;
			tab_info.index = index;
			tabs_info.push_back(tab_info);
		}

		return pressed;
	}
	IMGUI_API bool Tab(unsigned int index, const char* label, int* selected, float width = 0) {
		if (TabButton(label, ImVec2(width, 30), index)) {
			border_bang = 0.0f;
			old_tab_index = *selected;
			*selected = index;
		}
		return *selected == index;
	}
}
namespace menu
{
	static const char* bullettrace_type[]{
"Green",
"Cyan",
"purple",
"white",
"red",
	};

	static const char* healthbar_color_style[]{
	rus ? u8"Обычный" : "Defualt",
	rus ? u8"Переливающийся" : "Gradient",
	};
	static const char* healthbar_style[]{
	   rus ? u8"Слево" : "Left",
	  rus ? u8"Снизу" : "Bottom",
	};
	static const char* healthbar_color[]{
		  rus ? u8"Обычный" : "Defualt",
		rus ? u8"Кастомный" : "Custom",
	};
	static const char* npc_healthbar_color_style[]{
	 rus ? u8"Обычный" : "Defualt",
	 rus ? u8"Переливающийся" : "Gradient",
	};
	static const char* chams_type[]{
"Glow",
"Wire Frame",
"Set Trought",
"Lit Chams",
"Standart",
	};
	static const char* fov_style[]{
rus ? u8"Квадратный" : "Square",
rus ? u8"Круглый" : "Circular",
	};
	static const char* npc_healthbar_color[]{
	 rus ? u8"Обычный" : "Defualt",
		rus ? u8"Кастомный" : "Custom",
	};
	static const char* npc_healthbar_style[]{
		"None",
		"Left Side",
		"Bottom",
	};
	static const char* building_grade[]{
	"Twig",
	"Wood",
	"Stone",
	"Metal",
	"HQM",
	};
	static const char* psilent_bone[]{
	rus ? u8"Голова" : "Head",
  rus ? u8"Тело" : "Body",
	 rus ? u8"Рандом(Всё)" : "Random (All)",
	  rus ? u8"Рандом(Основное)" : "Random (Main)",
	};
	static const char* npc_box_style[]{
		rus ? u8"Пусто" : "None",
		 rus ? "Обычный" : "Default",
		 rus ? "Угловитый" : "Cornered",
	};
	static const char* box_style[]{
		rus ? u8"Пусто" : "None",
	  rus ? u8"Обычный" : "Default",
		 rus ? u8"Угловитый" : "Cornered",
		 rus ? u8"3д" : "3D Box",
	};
	static const char* anti_aim_yaw[]{
		rus ? u8"Вверх" : "Up",
		rus ? u8"Вниз" : "Down",
		rus ? u8"Обычный" : "Ophthalmic",
	};
	static const char* Doble_tap_type[]{
	"None",
	rus ? u8"Обычный" : "Basic",
	rus ? u8"Двойной" : "Smart",
	};
	static const char* fake_lag_type[]{
		"None",
		rus ? u8"Обычный" : "Basic",
		rus ? u8"Двойной" : "Double Tap",
	};
	static const char* target_tracer_pos[]{
		rus ? u8"Дефолтный" : "Default",
		rus ? u8"Середина" : "Middle",
	};
	static const char* name_pos[]{
	  rus ? u8"Внизу" : "Bottom",
	rus ? u8"Вверх" : "Top",
	};
	static const char* font_style[]{
"VerdanaBolt",
"Cunia",
"Arial"
	};
	static const char* tracer_pos[]{
		rus ? u8"Дефолтный" : "Default",
		rus ? u8"Середина" : "Middle",
	};
	static const char* modelstate_pos[]{
		"Default",
		"On Ladder",
		"On Ground",
		"Ducked",
		"Sleeping",

	};
	static const char* autoshoot_type[]{
		"Silent",
		"Default",
	};
	static const char* desync_autoshoot_type[]{
		"Always",
		"Desync",
	};
	static const char* timeshoot_type[]{
		"Silent",
		"Default",
	};
	static const char* Out_style[]{
	 "Triangle Filled",
	"Triangle NoFilled",
	"Circle",
	"Circle small",
	};
	static const char* ignore[]{
		"Ignore NPC",
		"Ignore Teammate",
		"Ignore Sleeping",
	};
	static const char* hitmaterial[]{
	"Default",
	"Glass",
	"Water",
	"Wood",
	"Metal",
	"Sand",
	"Grass",
	"Rock",
	"Concrete",
	"Forest",
	"Cloth",
	"Generic",
	"Null",
	};
	static const char* emotions[]{
						("None"),
						("Clap"),
						("Friendly"),
						("Thumbsdown"),
						("Thumbsup"),
						("Ok"),
						("Point"),
						("Shrug"),
						("Victory"),
						("Wave"),
	};
	static const char* hitsound_type[]{
			"Headshot Rust",
			"Minecraft",
			"Skeet",
			"Fatality",
			"Crystal",
	};
	static bool selected[3];
	static std::string previewValue1 = "";
	static int pTabs = 0;
	int pSubTabs = 0;
	int pSubTabs2 = 0;
	int pSubTabs3 = 0;
	int pSubTabs4 = 0;
	static int pSubTabs1 = 0;
	static int pWeapons = 0;
	static bool toggled;

	void Decoration()
	{
		
		ImGuiStyle style = ImGui::GetStyle();
		auto draw = ImGui::GetWindowDrawList(); auto pos = ImGui::GetWindowPos();

		menupos = pos;
		draw->AddRectFilled(pos, pos + ImVec2(690, 500), ImColor(16, 16, 16), 3);
		draw->AddRectFilled(pos + ImVec2(0, 40), pos + ImVec2(50, 500), ImColor(30, 28, 29), 3, ImDrawFlags_RoundCornersLeft);
		draw->AddRectFilled(pos + ImVec2(50, 40), pos + ImVec2(51, 500), ImColor(37, 37, 36));
		draw->AddRectFilled(pos, pos + ImVec2(690, 40), ImColor(21, 19, 20), 3, ImDrawFlags_RoundCornersTop);
		draw->AddRectFilled(pos + ImVec2(0, 40), pos + ImVec2(690, 42), ImColor(130, 20, 20));

		draw->AddRect(pos, pos + ImVec2(690, 500), ImColor(37, 37, 36), 3);
		draw->AddRectFilled(pos + ImVec2(125, 125), pos + ImVec2(370, 445), ImColor(20, 20, 20), 3);

		draw->AddRectFilled(pos + ImVec2(380, 125), pos + ImVec2(620, 445), ImColor(20, 20, 20), 3);
		draw->AddRectFilled(pos + ImVec2(125, 65), pos + ImVec2(620, 110), ImColor(20, 20, 20), 3);
		draw->AddRect(pos + ImVec2(380, 125), pos + ImVec2(620, 445), ImColor(37, 37, 36), 3);
		draw->AddRect(pos + ImVec2(125, 125), pos + ImVec2(370, 445), ImColor(37, 37, 36), 3);
		draw->AddRect(pos + ImVec2(125, 65), pos + ImVec2(620, 110), ImColor(37, 37, 36), 3);
		draw->AddRectFilled(pos + ImVec2(126, 155), pos + ImVec2(369, 156), ImColor(50, 50, 50));
		draw->AddRectFilled(pos + ImVec2(126, 125), pos + ImVec2(369, 155), ImColor(26, 26, 26), 3, ImDrawFlags_RoundCornersTop);
		draw->AddRectFilled(pos + ImVec2(381, 155), pos + ImVec2(619, 156), ImColor(50, 50, 50));
		draw->AddRectFilled(pos + ImVec2(381, 125), pos + ImVec2(619, 155), ImColor(26, 26, 26), 3, ImDrawFlags_RoundCornersTop);
		auto size1 = fMain->CalcTextSizeA(48.f, FLT_MAX, NULL, ("E"));
		//draw->AddText(worldico, 36.f, ImVec2(pos.x + 355 - size1.x / 2 , pos.y + 25 - size1.y / 2), ImColor(130, 20, 20), "E");
		draw->AddText(fMain, 18.f, ImVec2(pos.x + 355 - size1.x / 2, pos.y + 37 - size1.y / 2), ImColor(190, 40, 40), "Satanic");
		//ImGui::SetCursorPos(ImVec2(665 - Cuniaabyser->CalcTextSizeA(12.0f, FLT_MAX, NULL, "RU").x / 2, 25 - Cuniaabyser->CalcTextSizeA(12.0f, FLT_MAX, NULL, "RU").y));
		//if (lang(rus ? "Ru" : "Eu")) rus = !rus;
		//char name[UNLEN + 1];
		//DWORD username_len = UNLEN + 1;
		//GetUserNameA(name, &username_len);
		//std::string winname = name;
		
	}

	void Tabs()
	{
		ImGui::SetCursorPos({ 0 , 60 });

		ImGui::PushFont(Iconsis_Font);
		if (tab("A", rus ? u8"Наводка" : "AimBot", pTabs == 0)) pTabs = 0;

		ImGui::PopFont();
		

		ImGui::PushFont(Iconsis_Font);
		if (tab("D", rus ? u8"Визуалы" : "Visuals", pTabs == 1)) pTabs = 1;
		ImGui::PopFont();
		ImGui::PushFont(Iconsis_Font_2);
		
		if (tab("F", rus ? u8"Мир" : "World", pTabs == 2)) pTabs = 2;
		ImGui::PopFont();
		
		ImGui::PushFont(Iconsis_Font_2);
		if (tab("I", rus ? u8"Разное" : "Misc", pTabs == 3)) pTabs = 3;
		ImGui::PopFont();
		
		ImGui::PushFont(Iconsis_Font);
		if (tab("L", rus ? u8"Конфиг" : "Config", pTabs == 4)) pTabs = 4;
		ImGui::PopFont();

	}


	void combat()
	{
		if (pTabs == 0) {
			ImGui::SetCursorPos({ 145 , 81 });
			if (SUStab(rus ? u8"Основное" : "General", "", pSubTabs == 0)) pSubTabs = 0;
			ImGui::SameLine();
			if (SUStab(rus ? u8"Оружие" : "Weapon", "", pSubTabs == 1)) pSubTabs = 1;
			if (pSubTabs == 0) {
				auto draw = ImGui::GetWindowDrawList();
				auto pos = ImGui::GetWindowPos();
				draw->AddText(ImVec2(pos.x + 135, pos.y + 135), ImColor(199, 199, 199), rus ? u8"Аимбот" : "AimBot");
				draw->AddText(ImVec2(pos.x + 387, pos.y + 135), ImColor(199, 199, 199), rus ? u8"Основное" : "Other");

				ImGui::SetCursorPos({ 132 , 163 });
				MenuChild(("Aimbot"), ImVec2(230, 275), true, 0);
				{
					Checkbox__((rus ? u8"Вектор" : "Vector Aimbot"), &vars::combat::aimbot); ImGui::SameLine(); KeyBind(("##Aiming Key"), vars::keys::aimkey, ImVec2(70, 18));
					if (vars::combat::aimbot) {
						Checkbox__((rus ? u8"Плавность" : "Smooth"), &vars::combat::smooth);
					}
					Checkbox__(((rus ? u8"Псалент" : "Perfect Silent")), &vars::combat::psilent);
					if (vars::combat::psilent)
					{
						ImGui::Combo(((rus ? u8"Приоретет Аимбота" : "AimBot Priority")), &vars::combat::psilentbone, psilent_bone, IM_ARRAYSIZE(psilent_bone));
					}
					ImGui::Spacing();
					ImGui::SliderFloat(((rus ? u8"Размер фова" : "Fov Value")), &vars::combat::fov, 20.f, 2000.f, ("%.0f"));
					Checkbox__(((rus ? u8"Показ фова" : "Draw Fov")), &vars::combat::visualize_fov); ImGui::SameLine(); ImGui::ColorEdit4((" ##Color"), vars::colors::fov_color, ImGuiColorEditFlags_NoInputs);
					if (vars::combat::visualize_fov) {
						ImGui::Combo(((rus ? u8"Стиль фова" : "Draw Fov style")), &vars::players::fovstyle, fov_style, IM_ARRAYSIZE(fov_style));
					}




					Checkbox__(((rus ? u8"Увеличение пули(визуально)" : "Visual Projectile")), &vars::weapons::local_scale);
					if (vars::weapons::local_scale) {
						ImGui::Spacing();
						ImGui::SliderFloat(("X"), &vars::weapons::bullet_sizex, 0.f, 100.f, ("%.0f"));
						ImGui::SliderFloat(("Y"), &vars::weapons::bullet_sizey, 0.f, 100.f, ("%.0f"));
						ImGui::SliderFloat(("Z"), &vars::weapons::bullet_sizez, 0.f, 100.f, ("%.0f"));
					}

				}
				ImGui::EndChild();
				ImGui::SetCursorPos({ 385 , 163 });
				MenuChild(("Weapon  "), ImVec2(230, 275), true, 0);
				{
					Checkbox__((rus ? u8"Псалент вертолёт" : "Heli Aim"), &vars::combat::psilentheli);
					Checkbox__((rus ? u8"Манипулятор" : "Manipulator"), &vars::combat::manipulator); ImGui::SameLine(); KeyBind(("##Manipulator Key"), vars::keys::manipulated_key, ImVec2(70, 18));
					if (vars::combat::manipulator)
					{
						Checkbox__((rus ? u8"Сферы англов" : "Angles Sphere"), &vars::combat::manipulate_angle);
					}
					Checkbox__((rus ? u8"Авто Выстрел" : "Auto Fire"), &vars::combat::autoshoot);
					if (vars::combat::autoshoot) {
						ImGui::Combo((rus ? u8"Авто выстрел режим" : "Auto Fire Mode"), &vars::combat::autoshoot_type, autoshoot_type, IM_ARRAYSIZE(autoshoot_type));
						ImGui::Combo((rus ? u8"Тип авто выстрела" : "Fire Type"), &vars::combat::desync_autoshoot_type, desync_autoshoot_type, IM_ARRAYSIZE(desync_autoshoot_type));
					}
					Checkbox__((rus ? u8"Инста килл" : "Insta Kill"), &vars::combat::instakill); ImGui::SameLine(); KeyBind(("##Time Shot Key"), vars::keys::instakill, ImVec2(70, 18));
					if (vars::combat::instakill) {
						ImGui::Combo((rus ? u8"Тип выстрела" : "Shot Type"), &vars::combat::instakill_type, timeshoot_type, IM_ARRAYSIZE(timeshoot_type));
					}
					Checkbox__((rus ? u8"Игнорирование тимейтов" : "Ignore Teammates"), &vars::combat::ignore_team);
					Checkbox__((rus ? u8"Игнорирование спящих" : "Ignore Sleeping"), &vars::combat::ignore_sleepers);
				}
				ImGui::EndChild();
	
			}
			else
			{
				auto draw = ImGui::GetWindowDrawList();
				auto pos = ImGui::GetWindowPos();
				draw->AddText(ImVec2(pos.x + 135, pos.y + 135), ImColor(199, 199, 199), rus ? u8"Аимбот" : "AimBot");
				draw->AddText(ImVec2(pos.x + 387, pos.y + 135), ImColor(199, 199, 199), rus ? u8"Основное" : "Other");
				ImGui::SetCursorPos({ 132 , 163 });
				MenuChild(("Weapon"), ImVec2(230, 275), true, 0);
				{
					Checkbox__((rus ? u8"Без отдачи" : "Recoil Control"), &vars::weapons::no_recoil);
					if (vars::weapons::no_recoil) {
						ImGui::SliderFloat((rus ? u8"Отдача" : "Recoil"), &vars::weapons::recoil_control, 0.f, 100.f, ("%.0f"));
					}
					Checkbox__((rus ? u8"Без Сприда" : "Anti Spread"), &vars::weapons::no_spread);
					if (vars::weapons::no_spread) {
						ImGui::SliderFloat((rus ? u8"Сприд" : "Spread"), &vars::weapons::no_spreadvalue, 0.f, 100.f, ("%.0f"));
					}
					Checkbox__((rus ? u8"Быстрая еока" : "Instant Eoka"), &vars::weapons::eokatap);
					Checkbox__((rus ? u8"Быстрый лук" : "Fast Bow"), &vars::weapons::fastbow);
					Checkbox__((rus ? u8"Быстрая стрельба" : "Rapid Fire"), &vars::weapons::rapid_fire);
					Checkbox__((rus ? u8"Двойной выстрел" : "Double Tap"), &vars::weapons::dobltap);
					if (vars::weapons::dobltap)
					{
						ImGui::Combo((rus ? u8"Двойной выстрел стиль" : "Double Tap Style"), &vars::weapons::dobltapvalue, Doble_tap_type, IM_ARRAYSIZE(Doble_tap_type));
					}
					
					Checkbox__((rus ? u8"Быстрая пуля" : "Fast Bullets"), &vars::weapons::fast_bullets);
					Checkbox__((rus ? u8"Толстая пуля" : "Thick Bullets"), &vars::weapons::thick_bullet);
					if (vars::weapons::thick_bullet) {
						ImGui::SliderFloat((rus ? u8"Размер" : "Thick"), &vars::weapons::thickness, 0.1f, 3.f);// 1.5f
					}

				}
				ImGui::EndChild();
				ImGui::SetCursorPos({ 385 , 163 });
				MenuChild(("Weapon  "), ImVec2(230, 275), true, 0);
				{
					Checkbox__((rus ? u8"Авто перезарядка" : "Auto Reload"), &vars::combat::autoreload);
					Checkbox__((rus ? u8"Без анимаций" : "No Attack Animation"), &vars::weapons::remove_attack_anim);
					Checkbox__((rus ? u8"Быстрая тетива на луке" : "Insta Charge Compound"), &vars::weapons::compound);
					Checkbox__((rus ? u8"Без качаний" : "Remove Sway"), &vars::weapons::no_sway);
					Checkbox__((rus ? u8"Автоматик" : "Automatic"), &vars::weapons::automatic);
					Checkbox__((rus ? u8"Держать оружие на коптере" : "Can Hold Items"), &vars::weapons::minicopter_aim);
					Checkbox__((rus ? u8"Выстрел в прыжке" : "Jump Shoot"), &vars::misc::can_attack);
					Checkbox__((rus ? u8"Телепорт пули" : "Bullet Teleport"), &vars::combat::bullet_tp);
					Checkbox__((rus ? u8"Длинная шея" : "Long Neck"), &vars::misc::long_neck); ImGui::SameLine(); KeyBind(("##Long Neck Key"), vars::keys::longneck, ImVec2(70, 18));
					Checkbox__((rus ? u8"Десинк" : "Desync"), &vars::combat::desync); ImGui::SameLine(); KeyBind(("##Desync Key"), vars::keys::desync, ImVec2(70, 18));

					Checkbox__((rus ? u8"Простел сквозь обьекты" : "Pierce Materials"), &vars::weapons::penetrate);
				}
				ImGui::EndChild();
			}

		}
	}

	void esp() {

		if (pTabs == 1) {
			auto draw = ImGui::GetWindowDrawList();

			auto pos = ImGui::GetWindowPos();
			ImGui::SetCursorPos({ 145 , 81 });
			if (SUStab(rus ? u8"Игроки" : "Player", "", pSubTabs2 == 0)) pSubTabs2 = 0;
			ImGui::SameLine();
			if (SUStab(rus ? u8"Боты" : "Npc", "", pSubTabs2 == 1)) pSubTabs2 = 1;
			if (pSubTabs2 == 0) {
				auto pos = ImGui::GetWindowPos();
				draw->AddText(ImVec2(pos.x + 135, pos.y + 135), ImColor(199, 199, 199), rus ? u8"Есп" : "Esp");
				draw->AddText(ImVec2(pos.x + 387, pos.y + 135), ImColor(199, 199, 199), rus ? u8"Цвета" : "Colors");
				ImGui::SetCursorPos({ 132 , 163 });
				MenuChild("Players", ImVec2(230, 275), true, 0);
				{
					Checkbox__((rus ? u8"Включить игроков" : "Enable Player"), &vars::visuals::playerEspEnable);
					if (vars::visuals::playerEspEnable)
					{

						//(vars::misc::eyeline
						ImGui::Combo((rus ? u8"Коробка стиль" : "Box Style"), &vars::players::boxstyle, box_style, IM_ARRAYSIZE(box_style));
						ImGui::Combo((rus ? u8"Жизни бар стиль" : "Healthbar Style"), &vars::players::healthbarscolortyle, healthbar_color_style, IM_ARRAYSIZE(healthbar_color_style));

						ImGui::Combo((rus ? u8"Жизни бар цвет" : "Healthbar Style Color"), &vars::players::healthbarscolor, healthbar_color, IM_ARRAYSIZE(healthbar_color));
						Checkbox__((rus ? u8"Имя" : "Name"), &vars::players::name);
						if (vars::players::name)
						{
							ImGui::Combo((rus ? u8"Имя позиция" : "Name Position"), &vars::players::namePos, name_pos, IM_ARRAYSIZE(name_pos));
						}
						Checkbox__((rus ? u8"Дистанция" : "Distance"), &vars::players::distance);
						Checkbox__((rus ? u8"Показывать куда смотрит игрок" : "LookingDirection"), &vars::visuals::lookingDirection);

						Checkbox__((rus ? u8"Полная коробка" : "Fill Box"), &vars::players::fillbox);
						Checkbox__((rus ? u8"Жизни бар" : "Health Bar"), &vars::players::healthbar);
						Checkbox__((rus ? u8"Оружие" : "Weapon"), &vars::players::weapon);
						if (vars::players::weapon)
						{
							ImGui::Combo((rus ? u8"Оружие позиция" : "Weapon Position"), &vars::players::weaponPos, name_pos, IM_ARRAYSIZE(name_pos));
						}
						Checkbox__((rus ? u8"Скелет" : "Skeleton"), &vars::players::skeleton);
						Checkbox__((rus ? u8"Подсветка" : "Chams"), &vars::players::chams);
						if (vars::players::chams)
							ImGui::Combo((rus ? u8"Подсветка стиль" : "Chams Style"), &vars::players::chams_type, chams_type, IM_ARRAYSIZE(chams_type));
						Checkbox__((rus ? u8"Таргет линия" : "Target Tracers"), &vars::players::targetline);
						if (vars::players::targetline) {
							ImGui::Combo((rus ? u8"Таргет линия позиция" : "Target Tracer Position "), &vars::players::targetline_pos, target_tracer_pos, IM_ARRAYSIZE(target_tracer_pos));
						}
						Checkbox__((rus ? u8"Показ пояса таргета" : "Target Player Belt"), &vars::players::belt);
						Checkbox__((rus ? u8"Показ одежды таргета" : "Target Player Clothes"), &vars::players::clothes);
						Checkbox__((rus ? u8"Показ игроков за экраном" : "Out Of Arrows"), &vars::players::oof_arrows);
						if (vars::players::oof_arrows) {
							ImGui::Combo((rus ? u8"Показ игроков за экраном стиль" : "Out Of Arrows style"), &vars::players::Outstyle, Out_style, IM_ARRAYSIZE(Out_style));
						}

						Checkbox__((rus ? u8"Игнорирование спящих" : "Sleepers Ignore"), &vars::players::sleeperignore);

					}
				}

				ImGui::EndChild();

				ImGui::SetCursorPos({ 385 , 163 });
				MenuChild("Colors", ImVec2(230, 275), true, 0);
				{
					if (vars::visuals::playerEspEnable)
					{
						if (vars::players::chams_type == 0) {
							ImGui::ColorEdit4(("Chams##Color"), (float*)&vars::colors::chams, ImGuiColorEditFlags_NoInputs);
						}
						if (vars::players::chams_type == 1) {
							ImGui::ColorEdit4(("Chams##Color"), (float*)&vars::colors::chams, ImGuiColorEditFlags_NoInputs);
						}
						if (vars::players::chams_type == 2) {
							ImGui::ColorEdit4(("Chams##Color"), (float*)&vars::colors::chams, ImGuiColorEditFlags_NoInputs);
						}
						if (vars::players::chams_type == 3) {
							ImGui::ColorEdit4(("ChamsInVisible##Color"), (float*)&vars::colors::chamsinvusuble, ImGuiColorEditFlags_NoInputs);
							ImGui::ColorEdit4(("ChamsVisible##Color"), (float*)&vars::colors::chamsvusuble, ImGuiColorEditFlags_NoInputs);
						}
						if (vars::players::chams_type == 4) {
							ImGui::ColorEdit4(("ChamsInVisible##Color"), (float*)&vars::colors::chamsinvusuble, ImGuiColorEditFlags_NoInputs);
							ImGui::ColorEdit4(("ChamsVisible##Color"), (float*)&vars::colors::chamsvusuble, ImGuiColorEditFlags_NoInputs);
						}
						ImGui::ColorEdit4((rus ? u8"Скелет цвет" : "Skeleton   Color##Color"), vars::invisible::skeleton_color, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4(("Esp Visible Color##Color"), vars::invisible::box_color, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4((rus ? u8"Игроки цвет" : "Esp Color##Color"), vars::invisible::box_color, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4((rus ? u8"Нокнутый цвет" : "Wounded Color##Color"), vars::colors::wounded_color, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4((rus ? u8"Тимейт цвет" : "Teammate Color##Color"), vars::colors::team_color, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4((rus ? u8"Спящий цвет" : "Sleepers##Color"), vars::colors::sleep_color, ImGuiColorEditFlags_NoInputs);
						if (vars::players::healthbarscolor == 1)
							ImGui::ColorEdit4((rus ? u8"Цвет на жизни бар" : "Custom Health Color##Color"), vars::colors::Player_custom_healthColor, ImGuiColorEditFlags_NoInputs);
						if (vars::players::healthbarscolortyle == 1) {
							ImGui::ColorEdit4((rus ? u8"Градиент два" : "Gradient Two##Color"), vars::colors::gradient_2, ImGuiColorEditFlags_NoInputs);
							ImGui::ColorEdit4((rus ? u8"Градиент один" : "Gradient One##Color"), vars::colors::gradient_1, ImGuiColorEditFlags_NoInputs);
						}


					}
				}
				ImGui::EndChild();

			}
			else
			{
				auto pos = ImGui::GetWindowPos();
				draw->AddText(ImVec2(pos.x + 135, pos.y + 135), ImColor(199, 199, 199), rus ? u8"Есп" : "Esp");
				draw->AddText(ImVec2(pos.x + 387, pos.y + 135), ImColor(199, 199, 199), rus ? u8"Цвета" : "Colors");
				ImGui::SetCursorPos({ 132 , 163 });
				MenuChild("NPC", ImVec2(230, 275), true, 0);
				{
					Checkbox__((rus ? u8"Включить ботов" : "Enable Npc"), &vars::visuals::NpcEspEnable);
					if (vars::visuals::NpcEspEnable)
					{
						ImGui::Combo((rus ? u8"Коробка стиль" : "Box Style "), &vars::npc::boxstyle, npc_box_style, IM_ARRAYSIZE(npc_box_style));
						ImGui::Combo((rus ? u8"Жизни стиль" : "Healthbar Style"), &vars::npc::healthbarscolortyle, npc_healthbar_color_style, IM_ARRAYSIZE(npc_healthbar_color_style));
						ImGui::Combo((rus ? u8"Жизни стиль цвет" : "Healthbar Style Color"), &vars::npc::healthbarscolor, npc_healthbar_color, IM_ARRAYSIZE(npc_healthbar_color));
						Checkbox__((rus ? u8"Имя" : "Name"), &vars::npc::name);
						Checkbox__((rus ? u8"Жизни бар" : "Health Bar"), &vars::npc::healthbar);
						Checkbox__((rus ? u8"Дистанция" : "Distance"), &vars::npc::distance);
						Checkbox__((rus ? u8"Полная коробка" : "Fill Box "), &vars::npc::fillbox);
						Checkbox__((rus ? u8"Скелет" : "Skeleton "), &vars::npc::skeleton);
						Checkbox__((rus ? u8"Оружие" : "Weapon "), &vars::npc::weapon);
					}
				}
				ImGui::EndChild();
				ImGui::SetCursorPos({ 385 , 163 });
				MenuChild("Colors", ImVec2(230, 275), true, 0);
				{

					if (vars::visuals::NpcEspEnable)
					{
						ImGui::ColorEdit4((rus ? u8"Боты Коробка цвет" : " Npc Box##Color"), vars::colors::npc_box_color, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4((rus ? u8"Боты Имя цвет" : "Npc Name##Color"), vars::colors::npc_name_color, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4((rus ? u8"Боты Скелет цвет" : "Npc Skeleton##Color"), vars::colors::npc_skeleton_color, ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4((rus ? u8"Боты Оружие цвет" : "Npc Weapon##Color"), vars::colors::npc_weapons_color, ImGuiColorEditFlags_NoInputs);
						if (vars::npc::healthbarscolor == 1)
							ImGui::ColorEdit4((rus ? u8"Боты Цвет на жизни бар" : "Npc Custom Health Color##Color"), vars::colors::npc_custom_healthColor, ImGuiColorEditFlags_NoInputs);
						if (vars::npc::healthbarscolortyle == 1) {
							ImGui::ColorEdit4(rus ? u8"Боты Градиент два" : "Npc Gradient Two##Color", vars::colors::gradient_2, ImGuiColorEditFlags_NoInputs);
							ImGui::ColorEdit4(rus ? u8"Боты Градиент один" : "Npc Gradient One##Color", vars::colors::gradient_1, ImGuiColorEditFlags_NoInputs);
						}
					}
				}
				ImGui::EndChild();

			}
		}

	}

	void visuals() {
		if (pTabs == 2) {
			auto pos = ImGui::GetWindowPos();
			auto draw = ImGui::GetWindowDrawList();
			/*draw->AddText(Cuniaabyser, 12.0f, ImVec2(pos.x + 20 + 13, pos.y + 83), ImColor(229, 226, 229), rus ? u8"Локальные" : "Local");
			draw->AddText(Cuniaabyser, 12.0f, ImVec2(pos.x + 300 + 13, pos.y + 83), ImColor(229, 226, 229), rus ? u8"На экране" : "Screen");
			draw->AddText(Cuniaabyser, 12.0f, ImVec2(pos.x + 580 + 13, pos.y + 83), ImColor(229, 226, 229), rus ? u8"Мир" : "World");*/
			

			ImGui::SetCursorPos({ 145 , 81 });
			if (SUStab(rus ?  u8"Основное"  : "General", "", pSubTabs3 == 0)) pSubTabs3 = 0;
			ImGui::SameLine();
			if (SUStab(rus ? u8"Мир" : "World", "", pSubTabs3 == 1)) pSubTabs3 = 1;
			if (pSubTabs3 == 0) {
				draw->AddText(ImVec2(pos.x + 135, pos.y + 135), ImColor(199, 199, 199), rus ? u8"Основное" : "General");
				draw->AddText(ImVec2(pos.x + 387, pos.y + 135), ImColor(199, 199, 199), rus ? u8"Экран" : "Screen");
				ImGui::SetCursorPos({ 132 , 163 });
				MenuChild(("Main"), ImVec2(230, 275), true, 0);
				{
					ImGui::SliderFloat(rus ? u8"Визуальный фов" : "Player Fov", &vars::misc::fov, 30.f, 130.f, "%.0f");
					Checkbox__((rus ? u8"Растягивание экрана" : "AspectRatio"), &vars::misc::aspectraratio);
					if (vars::misc::aspectraratio)
					{
						ImGui::SliderFloat(rus ? u8"Растягивание экрана выбор" : "AspectRatio float", &vars::misc::aspectraratiofloat, 1000.f, 4000.f, "%.0f");
					}
					Checkbox__((rus ? u8"Сфера" : "Sphere"), &vars::visuals::sphere);// ImGui::SameLine(); ImGui::ColorEdit4(("                  "), (float*)&vars::colors::sphere_color, ImGuiColorEditFlags_NoInputs);

					Checkbox__((rus ? u8"Приблежение" : "Zoom"), &vars::visuals::zoom); ImGui::SameLine(); KeyBind("##Zoom Key", vars::keys::zoom, ImVec2(70, 18));

					ImGui::Combo((rus ? u8"Эмоции" : "Emotions spam"), &vars::misc::gesture_spam, emotions, IM_ARRAYSIZE(emotions));


					ImGui::Combo((rus ? u8"Эффекты при попадании" : "Hit Effect"), &vars::misc::hitmaterial, hitmaterial, IM_ARRAYSIZE(hitmaterial));
					Checkbox__((rus ? u8"Линия куда попала пуля" : "Bullet Tracers"), &vars::misc::bullet_tracers);



					Checkbox__((rus ? u8"Мувмент линия" : "Movement Line"), &vars::misc::movement_line);

					Checkbox__((rus ? u8"Виз. предикт" : "Vis. Predict"), &vars::combat::visualize_prediction);  ImGui::SameLine(); ImGui::ColorEdit4(("                 ##Color"), vars::colors::prediction_color, ImGuiColorEditFlags_NoInputs);
					Checkbox__((rus ? u8"Найтмод" : "Nightmode (Ambient)"), &vars::misc::bright_ambient); ImGui::SameLine(); ImGui::ColorEdit4(("                  ##Color"), (float*)&vars::colors::ambient_color, ImGuiColorEditFlags_NoInputs);


					Checkbox__((rus ? u8"Локальные кости" : "Local Bones"), &vars::misc::local_bones); ImGui::SameLine(); ImGui::ColorEdit4(("                   ##Color"), (float*)&vars::colors::local_bones, ImGuiColorEditFlags_NoInputs);
					Checkbox__((rus ? u8"Кастомное время" : "Custom Time"), &vars::misc::custom_time);
					if (vars::misc::custom_time) {
						ImGui::SliderFloat((rus ? u8"Время" : "Time"), &vars::misc::time, 0.f, 12.f, "%.0f");
					}
					Checkbox__((rus ? u8"Подсветка рук" : "Hand Chams"), &vars::visuals::hand_chams);
					ImGui::SameLine();
					ImGui::ColorEdit4((""), (float*)&vars::colors::hand_chams, ImGuiColorEditFlags_NoInputs);
					if (vars::visuals::hand_chams)
						ImGui::Combo((rus ? u8"Подцветка стиль" : "Chams Style"), &vars::visuals::hand_chams_type, chams_type, IM_ARRAYSIZE(chams_type));

				}
				ImGui::EndChild();
				ImGui::SetCursorPos({ 385 , 163 });
				MenuChild(("Main##1"), ImVec2(230, 275), true, 0);
				{

					Checkbox__((rus ? u8"Ноуклип бар" : "Noclip Bar"), &vars::misc::flyhack_indicator); /*ImGui::SameLine(); ImGui::ColorEdit4(("##Color"), vars::colors::flyhack_color);*/
					Checkbox__((rus ? u8"Индикатор перезарядки" : "Reload Coldown"), &vars::misc::reload_coldown);
					Checkbox__((rus ? u8"Индикатор манипулятора" : "Desync Indicator"), &vars::combat::instakill_indicator);
					Checkbox__((rus ? u8"Показывать имя таргета" : "Show Target Name"), &vars::visuals::target_name); ImGui::SameLine(); ImGui::ColorEdit4(("            ##Color"), (float*)vars::colors::target_name_color, ImGuiColorEditFlags_NoInputs);
					Checkbox__((rus ? u8"Хит лог" : "Hit Logs"), &vars::misc::hit_logs);
					Checkbox__((rus ? u8"Кеибинды" : "Keybinds"), &vars::visuals::keybinds);
					Checkbox__(("Cadicall Cross"), &vars::crosshair::cadicall); ImGui::SameLine(); ImGui::ColorEdit4(("    ##Color"), vars::colors::cadicall_color, ImGuiColorEditFlags_NoInputs);
					Checkbox__(("Evil Cross"), &vars::crosshair::default); ImGui::SameLine(); ImGui::ColorEdit4((" ##Color"), vars::colors::default_color, ImGuiColorEditFlags_NoInputs);
					Checkbox__(("Dot Cross"), &vars::crosshair::dot); ImGui::SameLine(); ImGui::ColorEdit4(("##Color"), vars::colors::dot_color, ImGuiColorEditFlags_NoInputs);
					Checkbox__(("Swastika Cross"), &vars::crosshair::swastika); ImGui::SameLine(); ImGui::ColorEdit4(("  ##Color"), vars::colors::swaston_color, ImGuiColorEditFlags_NoInputs);
					if (vars::crosshair::swastika) {
						ImGui::SliderFloat("Size ", &vars::crosshair::razmer, 1.f, 10.f, "%.0f");
						ImGui::SliderFloat("Speed", &vars::crosshair::speed, 0.f, 5.f, "%.0f");
					}
					Checkbox__(("Custom Cross"), &vars::crosshair::custom); ImGui::SameLine(); ImGui::ColorEdit4(("   ##Color"), vars::colors::custom_color, ImGuiColorEditFlags_NoInputs);
					if (vars::crosshair::custom) {
						ImGui::SliderFloat(("Gap"), &vars::crosshair::gap, 0.f, 50.f, "%.0f");
						ImGui::SliderFloat(("Length"), &vars::crosshair::length, 0.f, 150.f, "%.0f");
					}
					Checkbox__((rus ? u8"Звёзды" : "Night Stars"), &vars::misc::night_stars);
					if (vars::misc::night_stars) {
						ImGui::SliderFloat((rus ? u8"Изменение звёзд" : "Stars Amount"), &vars::misc::stars, 0.f, 40000.f, "%.0f");
					}
					Checkbox__((rus ? u8"Солнце" : "Mie Changer"), &vars::misc::mie_changer);
					if (vars::misc::mie_changer) {
						ImGui::SliderFloat((rus ? u8"Изменение солнца" : "Mie Amount"), &vars::misc::mie, 1.f, 100.f, "%.0f");
					}
					Checkbox__((rus ? u8"Небо разноцвет" : "Rayleigh Changer"), &vars::misc::rayleigh_changer);
					if (vars::misc::rayleigh_changer) {
						ImGui::SliderFloat((rus ? u8"Изменение небо разноцвет" : "Rayleigh Amount"), &vars::misc::rayleigh, 1.f, 100.f, "%.0f");
					}
					Checkbox__((rus ? u8"Небо" : "Brightness Changer"), &vars::misc::brightness_changer);
					if (vars::misc::brightness_changer) {
						ImGui::SliderFloat((rus ? u8"Изменение небо" : "Brightness Amount"), &vars::misc::brightness, 1.f, 50.f, "%.0f");
					}


					Checkbox__((rus ? u8"Облака" : "Clouds"), &vars::misc::облака);
					if (vars::misc::облака)
					{
						ImGui::SliderFloat(rus ? u8"Облака количество" : "Clouds value", &vars::misc::облакафлоат, 0.f, 2000.f, "%.0f");
					}
					Checkbox__((rus ? u8"Дождь или Снегопад" : "Rain & Snowfall"), &vars::misc::Дождь);

				}
				ImGui::EndChild();

			}
			else
			{
				draw->AddText(ImVec2(pos.x + 135, pos.y + 135), ImColor(199, 199, 199), rus ? u8"Мир" : "World");
				draw->AddText(ImVec2(pos.x + 387, pos.y + 135), ImColor(199, 199, 199), rus ? u8"Мир" : "World");
				ImGui::SetCursorPos({ 132 , 163 });
				MenuChild(("World##1"), ImVec2(230, 275), true, 0);
				{



					if (ImGui::CollapsingHeader(("Important"))) {
						Checkbox__(("Raid Esp"), &vars::visuals::raid_esp);
						Checkbox__(("Dropped Items"), &vars::visuals::other::dropped_items);
						Checkbox__(("Hemp"), &vars::visuals::other::hemp);
						Checkbox__(("Corpses"), &vars::visuals::other::corpse);
						Checkbox__(("Bodybags"), &vars::visuals::other::bodybag);
						Checkbox__(("Stashes"), &vars::visuals::other::stash);
						if (vars::visuals::other::corpse || vars::visuals::other::stash || vars::visuals::other::hemp || vars::visuals::other::dropped_items) {
							ImGui::SliderFloat(("Important ESP Distance"), &vars::visuals::other::draw_distance, 5.f, 400.f, "%.0f");
							Checkbox__(("Show Distance    "), &vars::visuals::other::show_distance);
						}
					}
					if (ImGui::CollapsingHeader(("Ores"))) {
						Checkbox__(("Ore Path"), &vars::ores::closest_ore);
						Checkbox__(("Stone"), &vars::ores::stone);
						Checkbox__(("Sulfur"), &vars::ores::sulfur);
						Checkbox__(("Metal"), &vars::ores::metal);
						if (vars::ores::sulfur || vars::ores::stone || vars::ores::metal) {
							ImGui::SliderFloat(("Ores ESP Distance"), &vars::ores::draw_distance, 5.f, 400.f, "%.0f");
							Checkbox__(("Show Collectables"), &vars::ores::show_collectables);
							Checkbox__(("Show Distance"), &vars::ores::show_distance);
						}
					}
					if (ImGui::CollapsingHeader(("Crates"))) {
						Checkbox__(("Chinook Crates"), &vars::visuals::crates::chinook);
						Checkbox__(("Airdrops"), &vars::visuals::crates::supply);
						Checkbox__(("Heli Box"), &vars::visuals::crates::heli);
						Checkbox__(("Bradley Box"), &vars::visuals::crates::bradley);
						Checkbox__(("Military Box"), &vars::visuals::crates::military);
						Checkbox__(("Elite Box"), &vars::visuals::crates::elite);
						if (vars::visuals::crates::supply || vars::visuals::crates::bradley || vars::visuals::crates::heli || vars::visuals::crates::military || vars::visuals::crates::elite) {
							ImGui::SliderFloat(("Crates ESP Distance"), &vars::visuals::crates::draw_distance, 5.f, 3000.f, "%.0f");
							Checkbox__(("Show Distance "), &vars::visuals::crates::show_distance);
						}
					}


				}
				ImGui::EndChild();
				ImGui::SetCursorPos({ 385 , 163 });
				MenuChild(("World##2"), ImVec2(230, 275), true, 0);
				{


				/*	Checkbox__(("Radar "), &vars::visuals::radar_);
					if (vars::visuals::radar_) {
						ImGui::SliderFloat(("Size"), &vars::visuals::radar::size, 5.f, 400.f);
						ImGui::SliderFloat(("Range"), &vars::visuals::radar::range, 5.f, 400.f);
					}*/
					if (ImGui::CollapsingHeader(("Animals"))) {
						Checkbox__(("Bears"), &vars::visuals::animals::bear);
						Checkbox__(("Boars"), &vars::visuals::animals::pig);
						Checkbox__(("Wolfs"), &vars::visuals::animals::wolf);
						Checkbox__(("Horses"), &vars::visuals::animals::deer);
						Checkbox__(("Chickens"), &vars::visuals::animals::chicken);
						if (vars::visuals::animals::bear || vars::visuals::animals::pig || vars::visuals::animals::wolf || vars::visuals::animals::deer || vars::visuals::animals::chicken) {
							ImGui::SliderFloat("Animals ESP Distance", &vars::visuals::animals::draw_distance, 5.f, 400.f, "%.0f");
							Checkbox__(("Show Distance      "), &vars::visuals::animals::show_distance);
						}
					}
					if (ImGui::CollapsingHeader(("Vehicles"))) {
						Checkbox__(("Patrol Heli"), &vars::visuals::patrol_heli);
						Checkbox__(("Bradley APC"), &vars::visuals::bradley_apc);
						Checkbox__(("Minicopters"), &vars::visuals::vehicles::minicopter);
						Checkbox__(("Scrap Helis"), &vars::visuals::vehicles::scrapheli);
						Checkbox__(("Boats"), &vars::visuals::vehicles::boat);
						Checkbox__(("RHIB's"), &vars::visuals::vehicles::rhib);
						if (vars::visuals::vehicles::minicopter || vars::visuals::vehicles::scrapheli || vars::visuals::vehicles::boat || vars::visuals::vehicles::rhib) {
							ImGui::SliderFloat(("Vehicles ESP Distance"), &vars::visuals::vehicles::draw_distance, 5.f, 3000.f, "%.0f");
							Checkbox__(("Show Distance  "), &vars::visuals::vehicles::show_distance);
						}
					}
					if (ImGui::CollapsingHeader(("Traps"))) {
						Checkbox__(("Auto Turrets"), &vars::visuals::turrets::auto_turret);
						Checkbox__(("Flame Turrets"), &vars::visuals::turrets::flame_turret);
						Checkbox__(("Shotgun Traps"), &vars::visuals::turrets::shotgun_turret);
						Checkbox__(("SAM Sites"), &vars::visuals::turrets::sam_site);
						Checkbox__(("Landmines"), &vars::visuals::turrets::landmine);
						Checkbox__(("Beartraps"), &vars::visuals::turrets::bear_trap);
						if (vars::visuals::turrets::auto_turret || vars::visuals::turrets::flame_turret || vars::visuals::turrets::shotgun_turret || vars::visuals::turrets::landmine || vars::visuals::turrets::bear_trap) {
							ImGui::SliderFloat(("Traps ESP Distance"), &vars::visuals::turrets::draw_distance, 5.f, 400.f, "%.0f");
							Checkbox__(("Show Distance   "), &vars::visuals::turrets::show_distance);
						}
					}
					if (ImGui::CollapsingHeader(("Base"))) {
						Checkbox__(("Tool Cupboards"), &vars::visuals::base::tc);
						Checkbox__(("Sleeping Bags"), &vars::visuals::base::sleeping_bag);
						Checkbox__(("Beds"), &vars::visuals::base::bed);
						Checkbox__(("Boxes"), &vars::visuals::base::boxes);
						if (vars::visuals::base::tc || vars::visuals::base::sleeping_bag || vars::visuals::base::bed || vars::visuals::base::boxes) {
							ImGui::SliderFloat(("Base ESP Distance"), &vars::visuals::base::draw_distance, 5.f, 400.f, "%.0f");
							Checkbox__(("Show Distance     "), &vars::visuals::base::show_distance);
						}


					}


					}
				ImGui::EndChild();
				
			

			}

		}
	}

	void misc() {
		if (pTabs == 3) {
			ImGui::SetCursorPos({ 145 , 81 });
			if (SUStab(rus ? u8"Основное" : "General", "", pSubTabs4 == 0)) pSubTabs4 = 0;
			ImGui::SameLine();
			if (SUStab(rus ? u8"Остальное" : "Other", "", pSubTabs4 == 1)) pSubTabs4 = 1;
			if (pSubTabs4 == 0) {
				auto pos = ImGui::GetWindowPos();
				auto draw = ImGui::GetWindowDrawList();
				draw->AddText(ImVec2(pos.x + 135, pos.y + 135), ImColor(199, 199, 199), rus ? u8"Основное" : "Misc");
				draw->AddText(ImVec2(pos.x + 387, pos.y + 135), ImColor(199, 199, 199), rus ? u8"Основное" : "Misc");
				ImGui::SetCursorPos({ 132 , 163 });
				MenuChild("Main", ImVec2(230, 275), true, 0);
				{
					Checkbox__((rus ? u8"Фейк админ" : "Fake Admin"), &vars::misc::fakeadmin);

					Checkbox__((rus ? u8"Лететь за пулей" : "Follow Projectile"), &vars::combat::followprojectile); ImGui::SameLine(); KeyBind(("##Projectile Key"), vars::keys::followprojectile, ImVec2(70, 18));
					Checkbox__((rus ? u8"Быстро лутать" : "Fast Loot"), &vars::misc::fast_loot);
					Checkbox__((rus ? u8"Без колизии" : "No Collision"), &vars::misc::walker);
					ImGui::Combo((rus ? u8"Модель" : "Model State"), &vars::misc::modelstate, modelstate_pos, IM_ARRAYSIZE(modelstate_pos)); ; KeyBind(("##Model State Key"), vars::keys::ModelState, ImVec2(70, 18));
					Checkbox__((rus ? u8"Быстрый бег" : "Omni-Sprint"), &vars::misc::omnidirectional_sprinting);
					Checkbox__((rus ? u8"Интерактив дебаг" : "Interactive Debug"), &vars::misc::interactive_debug); ImGui::SameLine(); KeyBind(("##Debug Key"), vars::keys::debugging, ImVec2(70, 18));
					Checkbox__((rus ? u8"Звук при попадании" : "Hitsound"), &vars::misc::custom_hitsound);

					if (vars::misc::custom_hitsound)
						ImGui::Combo((rus ? u8"Звук" : "Sound"), &vars::misc::hitsound_rejim, hitsound_type, IM_ARRAYSIZE(hitsound_type));



				}
				ImGui::EndChild();

				ImGui::SetCursorPos({ 385 , 163 });
				MenuChild("Main##4", ImVec2(230, 275), true, 0);
				{
					Checkbox__((rus ? u8"Фейклаги" : "Fake-Lag"), &vars::misc::fake_lag);
					if (vars::misc::fake_lag)
						ImGui::Combo((rus ? u8"Стиль" : "Fake-Lag "), &vars::misc::fake_lag_type, fake_lag_type, IM_ARRAYSIZE(fake_lag_type));
					Checkbox__((rus ? u8"Килл" : "Suicide"), &vars::misc::mass_suicide);
					//Checkbox__((rus ? u8"Паучок" : "Spiderman"), &vars::misc::spiderman);
		/*			Checkbox__(("Auto Farm"), &vars::misc::auto_farm);
					if (vars::misc::auto_farm) {
						Checkbox__(("Auto Farm Trees"), &vars::misc::auto_farm_tree);
						Checkbox__(("Auto Farm Ores"), &vars::misc::auto_farm_ore);
						Checkbox__(("Auto Farm Barrels"), &vars::misc::auto_farm_barrel);
					}*/
					Checkbox__((rus ? u8"Без дамага при падении" : "No Fall Damage"), &vars::misc::no_fall);
					Checkbox__((rus ? u8"Бесконечный прыжок" : "Infinity Jump"), &vars::misc::inf_jump);
					Checkbox__((rus ? u8"Фейк выстрел" : "Fake Shots"), &vars::misc::weapon_spam); ImGui::SameLine(); KeyBind(("##Shots Key"), vars::keys::weaponspam, ImVec2(70, 18));
					Checkbox__(("Door Spammer"), &vars::misc::annoyer);
				}
				ImGui::EndChild();

				//}
			}
			else if (pSubTabs4 == 1)
			{
				auto draw = ImGui::GetWindowDrawList();
				auto pos = ImGui::GetWindowPos();
				draw->AddText(ImVec2(pos.x + 135, pos.y + 135), ImColor(199, 199, 199), rus ? u8"Основное" : "Misc");
				draw->AddText(ImVec2(pos.x + 387, pos.y + 135), ImColor(199, 199, 199), rus ? u8"Основное" : "Misc");
				ImGui::SetCursorPos({ 132 , 163 });
				MenuChild("Main##4", ImVec2(230, 275), true, 0);
				{
					Checkbox__((rus ? u8"Ускорение игрока" : "Speed Hack"), &vars::misc::speedhack); ImGui::SameLine(); KeyBind(("##Speed Hack Key"), vars::keys::speedkey, ImVec2(70, 18));
					Checkbox__((rus ? u8"АнтиАимы" : "Anti-Aim"), &vars::misc::anti_aim);
					if (vars::misc::anti_aim) {
						ImGui::SliderFloat((rus ? u8"Скорость" : "Speed"), &vars::misc::anti_aim_speed, 1, 150);
						ImGui::Combo((rus ? u8"Отклонение" : "Yaw"), &vars::misc::anti_aim_yaw, anti_aim_yaw, IM_ARRAYSIZE(anti_aim_yaw));
						Checkbox__((rus ? u8"АнтиАим Индикатор" : "Anti-Aim Indicator"), &vars::misc::anti_aim_indicator);
						

					}
				}
				ImGui::EndChild();
				ImGui::SetCursorPos({ 385 , 163 });
				MenuChild("Main##2", ImVec2(230, 275), true, 0);
				{

					//Checkbox__((rus ? u8"Авто удары" : "Silent Melee"), &vars::combat::silent_melee);
					Checkbox__((rus ? u8"Авто поднятие игрока" : "Insta Revive"), &vars::misc::auto_revive);

					//Checkbox__((rus ? u8"Авто поднятие" : "Auto Pick Up"), &vars::misc::auto_pickup);

					Checkbox__((rus ? u8"Авто хилл" : "Auto Healing"), &vars::misc::faster_healing);




				}
				ImGui::EndChild();
			}
		}
	}

	std::string get_random_string(size_t length)
	{
		std::string str(("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890"));
		std::random_device rd;
		std::mt19937 generator(rd());
		std::shuffle(str.begin(), str.end(), generator);
		return str.substr(0, length);
	}

	static bool menu_added = false;

	struct Configs
	{
		std::string name;
		std::string fullname;
		bool loaded;
	};
	std::vector<Configs> configs;
	std::vector<Configs> luas;

	void settings()
	{
		if (pTabs == 4) {
			auto draw = ImGui::GetWindowDrawList();
			auto pos = ImGui::GetWindowPos();
			/*draw->AddText(Cuniaabyser, 12.0f, ImVec2(pos.x + 20 + 13, pos.y + 83), ImColor(229, 226, 229), rus ? u8"Конфиг лист" : "ConfigList");
			draw->AddText(Cuniaabyser, 12.0f, ImVec2(pos.x + 300 + 13, pos.y + 83), ImColor(229, 226, 229), rus ? u8"Загрузка и Сохранение" : "Load and Save");
			draw->AddText(Cuniaabyser, 12.0f, ImVec2(pos.x + 580 + 13, pos.y + 83), ImColor(229, 226, 229), rus ? u8"Остальное" : "Other");*/
			draw->AddText(ImVec2(pos.x + 135, pos.y + 135), ImColor(199, 199, 199), rus ? u8"Конфиг" : "Config");
			draw->AddText(ImVec2(pos.x + 387, pos.y + 135), ImColor(199, 199, 199), rus ? u8"Основное" : "Other");
			draw->AddRectFilled(pos + ImVec2(128, 158), pos + ImVec2(368, 443), ImColor(16, 16, 16), 3);
			draw->AddRect(pos + ImVec2(128, 158), pos + ImVec2(368, 443), ImColor(37, 37, 36), 3);
			ImGui::SetCursorPos({ 145 , 81 });
			if (SUStab(rus ? u8"Конфиг" : "Config", "", pSubTabs1 == 0)) pSubTabs1 = 0;
			if (pSubTabs1 == 0)
			{
				ImGui::SetCursorPos({ 132 , 163 });
				MenuChild("Config List", ImVec2(230, 275), true, 0);
				{
					std::vector<std::string> files;
					config_manager::read_directory(("C:/Satanic/"), files);
					for (auto cfg : config.GetConfigList())
						if (ImGui::Selectable(cfg.c_str(), cfg == vars::stuff::selected_cfg))
							vars::stuff::selected_cfg = cfg;





					ImGui::EndChild();

				}
				ImGui::SetCursorPos({ 385 , 163 });
				MenuChild("Config List##1", ImVec2(230, 275), true, 0);
				{

					if (!sh_save_cfg) {
						if (ImGui::Button((rus ? u8"Сохранить" : "Save"), ImVec2(0, 0))) {
	
							sh_save_cfg = true;
						}
					}
					else
					{
						if (ImGui::Button((rus ? u8"Применить" : "Apply"), ImVec2(0, 0))) {
							SaveCFG((vars::stuff::selected_cfg));

							notify::add_log("Config", "Saved", ImColor(130, 20, 20), ImColor(255, 255, 255), 4700);
							sh_save_cfg =false ;
						}
					}
					ImGui::SameLine();
					if (!sh_load_cfg) {
						if (ImGui::Button((rus ? u8"Загрузить" : "Load"), ImVec2(0, 0))) {
							
							sh_load_cfg = true;
						}
					}
					else
					{
						if (ImGui::Button((rus ? u8"Применить" : "Apply"), ImVec2(0, 0))) {
							LoadCFG((vars::stuff::selected_cfg));
							notify::add_log("Config", "Loaded", ImColor(130, 20, 20), ImColor(255, 255, 255), 4700);


							sh_load_cfg = false;
						}
					}
				
				
					
					ImGui::SameLine();
	               if (!Remove) {
		               if (ImGui::Button((rus ? u8"Удалить" : "Remove"), ImVec2(0, 0))) {
			
			             Remove = true;
	        	}
					}
					else
					{
						if (ImGui::Button((rus ? u8"Применить" : "Apply"), ImVec2(0, 0))) {
							config.Remove(vars::stuff::selected_cfg.c_str());
							notify::add_log("Config", "Removed", ImColor(130, 20, 20), ImColor(255, 255, 255), 4700);

							
							Remove =false ;
						}
					}
				
				
				   ImGui::SameLine();
					if (ImGui::Button((rus ? u8"Создать" : "Create"), ImVec2(0, 0))) {
						create = true;
					}
					if (create)
					{
						ImGui::InputText("", vars::stuff::ConfigName, 0x100);
						if (ImGui::ButtonEx((rus ? u8"Подтвердить" : "Accept"), ImVec2(0, 0))) {
							CREATY(vars::stuff::ConfigName);

							notify::add_log("Config", "Created", ImColor(130, 20, 20), ImColor(255, 255, 255), 4700);
							create = false;
						}
					}
					if (ImGui::Button((rus ? u8"Открыть папку" : "Open Folder"), ImVec2(0, 0))) {
						system(("start C:\Satanic"));
					}
					//if (ImGui::Button((rus ? u8"Скачать дефолт кфг" : "Download Defaut cfg"), ImVec2(0, 0))) {
					//	URLDownloadToFileA(NULL, "https://cdn.discordapp.com/attachments/1115586281162936412/1124713438380294225/Defaut.ini", "C:\\Satanic\\Defaut.ini", 0, NULL);
					//}
					//Checkbox__((rus ? u8"Ватермарка" : "Watermark"), &vars::visuals::waterka);

					Discord* g_Discord1;
					if (ImGui::Button((rus ? u8"Выгрузить" : "Unload Cheat"), ImVec2(0, 0))) {
						vars::misc::Дождь = false;
						vars::misc::fakeadmin = false;
						vars::misc::rayleigh_changer = false;
						vars::misc::облакафлоат = 1;
						vars::misc::rayleigh = 0;
						vars::misc::brightness = 1;
						vars::misc::unloadfakeadmin = true;
						vars::misc::fov = false;
						vars::misc::omnidirectional_sprinting = false;
						Sleep(3000);
						//g_Discord1->Shutdown();
						vars::stuff::Panic = true;
					}
 
					ImGui::EndChild();

				}
	
			}
		}
	}

	void Components()
	{
		ImGui::SetCursorPos(ImVec2(165, 95));
		ImGui::BeginGroup();
		{
			switch (pTabs)
			{
			case 0: combat();  break;
				//	case 7: legit();  break;
			case 1: esp();  break;
			case 2: visuals(); break;
			case 3: misc();  break;
			case 4: settings(); break;
			}
		}
		ImGui::EndGroup();
	}

	void DrawMenu()
	{
		auto& s = ImGui::GetStyle();
		s.FrameRounding = 0.f;
		s.FramePadding = ImVec2(2.5f, 1.5f);
		s.WindowBorderSize = 0;
		s.ScrollbarSize = 6.f;
		auto c = s.Colors;
		c[ImGuiCol_ScrollbarGrab] = ImColor(33, 33, 33);
		c[ImGuiCol_ScrollbarGrabHovered] = ImColor(130, 20, 20);
		c[ImGuiCol_ScrollbarGrabActive] = ImColor(130, 20, 20);
		ImGui::SetNextWindowSize(menu_size);
		ImVec2 menu_pos;
		ImDrawList* drawList_test;
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		invis(true, true);
		ImGui::Begin(("Menu"), nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoSavedSettings);
		{

			auto p = ImGui::GetWindowPos();
			ImDrawList* drawList = ImGui::GetWindowDrawList();
			drawList_test = drawList;
			const ImVec2 origin(ImGui::GetCursorScreenPos());
			menu_pos = ImGui::GetWindowPos();
			auto draw = ImGui::GetWindowDrawList();

		//	EFFECT::дождик();
			Decoration();
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 5));
			ImGui::PushFont(Cuniaabyser1);
			Tabs();


			Components();
			ImGui::PopFont();
			ImGui::PopStyleVar();
		}
		ImGui::End();

		ImGui::PopStyleVar();

	}
}


