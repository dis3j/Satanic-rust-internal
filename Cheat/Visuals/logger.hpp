#pragma once
#include <string>
#include <deque>
struct notify_t
{
	float life_ime_local;
	float life_ime;
	std::string type;
	std::string message;
	ImColor c_type;
	ImColor c_message;
	float x;
	float y = -15;
	float max_x;
};

std::deque<notify_t> notifications;

notify_t find_notify(std::string pre_text, std::string body)
{
	for (size_t i = 0; i < notifications.size(); i++)
		if (notifications[i].type == pre_text && notifications[i].message == body)
			return notifications[i];
	return notify_t();
}
int epoch_time()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}
template <typename t>
static t lerp(const t& t1, const t& t2, float progress)
{
	return t1 + (t2 - t1) * progress;
}
namespace notify {
	void render()
	{
		if (notifications.empty())
			return;

		float last_y = 0;
		float x = vars::stuff::ScreenWidth, y = vars::stuff::ScreenHeight;
		for (size_t i = 0; i < notifications.size(); i++)
		{
			auto& notify = notifications.at(i) ;

			const auto pre = notify.type.c_str();
			const auto text = notify.message.c_str();
			ImVec2 textSize = flogs->CalcTextSizeA(14.f, FLT_MAX, 0.0f, notify.type.c_str());

			std::string all_text;
			all_text += pre;
			all_text += "";
			all_text += text;

			ImVec2 all_textSize = flogs->CalcTextSizeA(14.f, FLT_MAX, 0.0f, all_text.c_str());

			notify.y = lerp(notify.y, (i * 17.f), 0.05f);

			if (notify.y > y + 17) {
				continue;
			}

			if (epoch_time() - notify.life_ime_local > notify.life_ime)
			{
				if ((notify.x + all_textSize.x / 2 + 16) < 0) {
					notifications.erase(notifications.begin() + i);
					continue;
				}

				notify.max_x = all_textSize.x / 2 + 16;

				notify.x = lerp(notify.x, (notify.max_x  * -1) - 10, 0.05f);

				int procent_x = (100 * (notify.max_x  + notify.x )) / notify.max_x;

				auto opacity = int((255 / 100) * procent_x);

				if (procent_x >= 0 && procent_x <= 100)
				{
					notify.c_message = ImColor(notify.c_message);
					notify.c_type = ImColor(notify.c_type);
				}
				else
				{
					notify.c_message = ImColor(notify.c_message);
					notify.c_type = ImColor(notify.c_type);
				}
			}

			float box_w = (float)fabs(0 - (all_textSize.x + 16));
			float xs = vars::stuff::ScreenWidth / 2, ys = vars::stuff::ScreenHeight / 2;
			g_Render->DrawString(notify.x + 3, last_y + notify.y, notify.c_type, render2::none, Cuniaabyser, 11, pre);
			g_Render->DrawString(notify.x + 13 + textSize.x, last_y + notify.y, notify.c_message, render2::none, Cuniaabyser, 11, text);
			//DrawList->AddRectFilled(ImVec2(0.f, last_y + notify.y - 1), ImVec2(notify.x + all_textSize.x + 16, last_y + notify.y + all_textSize.y + 2), ImColor(0, 0, 0));//  x, y, z, w;
			//DrawList->AddRectFilled(ImVec2(notify.x + all_textSize.x + 16, last_y + notify.y - 1), ImVec2(notify.x + all_textSize.x + 18, last_y + notify.y + all_textSize.y + 2),ImColor(notify.c_type.Value.x, notify.c_type.Value.y, notify.c_type.Value.z, 150.f));
			/*DrawList->AddText(flogs, 13, ImVec2(notify.x + 3, last_y + notify.y), notify.c_type, pre);
			DrawList->AddText(flogs, 13, ImVec2(notify.x + 13 + textSize.x, last_y + notify.y), notify.c_message, text);*/

		}
	}
	namespace console {
		void clear() {
			//m_engine()->ExecuteClientCmd("clear");
		}

		void notify(std::string pre, std::string msg, ImColor clr_pre) {
			///	m_cvar()->ConsoleColorPrintf(Color(255, 0, 0), "[Overline] ");
			///	m_cvar()->ConsoleColorPrintf(clr_pre, "[%s]", pre.data());
			//	m_cvar()->ConsolePrintf(" %s\n", msg.data());
		}
	}

	namespace screen
	{
		void notify(std::string pre, std::string text, ImColor color_pre, ImColor color_text, int life_time) {
			std::string type_buf;
			type_buf += "[";
			type_buf += pre;
			type_buf += "]";

			notifications.push_front(notify_t{ static_cast<float>(epoch_time()), (float)life_time, type_buf, text, color_pre, color_text });
		}
	}
	void add_log(std::string pre, std::string text, ImColor color_pre, ImColor color_text, int life_time)
	{
		screen::notify(pre, text, color_pre, color_text, life_time);
		console::notify(pre, text, color_pre);
	}
}