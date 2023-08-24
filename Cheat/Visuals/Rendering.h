
struct m_indicator
{
	std::string m_text;
	ImColor m_color;
	m_indicator(const char* text, ImColor color) :
		m_text(text), m_color(color)
	{

	}
	m_indicator(std::string text, ImColor color) :
		m_text(text), m_color(color)
	{

	}
};
std::vector<m_indicator> m_indicators;
void AddIndicators() {
	float width = vars::stuff::ScreenWidth, height = vars::stuff::ScreenHeight;
	int h = 0;
	for (auto& indicator : m_indicators) {
		auto size_text = indShandow->CalcTextSizeA(30.f, FLT_MAX, NULL, indicator.m_text.c_str());
		g_Render->FilledRectGradient(14, height - 340 - h - 3, size_text.x / 2, 33, ImColor(0, 0, 0, 0), ImColor(0, 0, 0, 165), ImColor(0, 0, 0, 165), ImColor(0, 0, 0, 0));
		g_Render->FilledRectGradient(14 + size_text.x / 2, height - 340 - h - 3, size_text.x / 2, 33, ImColor(0, 0, 0, 165), ImColor(0, 0, 0, 0), ImColor(0, 0, 0, 0), ImColor(0, 0, 0, 165));
		//	g_Render->DrawString(21 + 1, height - 340 - h + 1, ImColor(0, 0, 0, 200), 0, indShandow, 30.f, indicator.m_text.c_str());
		g_Render->DrawString(21, height - 340 - h, indicator.m_color, render2::outline, indShandow, 30.f, indicator.m_text.c_str());
		h += 36;
	}
	m_indicators.clear();
}
struct m_keybind
{
	ImDrawList* drawList;
	ImVec2 position;
	const char* m_text;
	int bind_key;
	//Color m_color;
	m_keybind(ImDrawList* drawList, ImVec2 position, const char* text, int bind) : drawList(drawList), position(position), m_text(text), bind_key(bind) {
	}
};
std::vector<m_keybind> m_keybinds;
void Addbind() {
	auto offset = 2;
	for (auto& indicator : m_keybinds) {
		if (GetAsyncKeyState(indicator.bind_key)) {
			indicator.drawList->AddText(flogs, 13.f, ImVec2(indicator.position.x + 7, indicator.position.y + 25 + 4 + offset), ImColor(203, 207, 206), indicator.m_text);
			indicator.drawList->AddText(flogs, 13.f, ImVec2(indicator.position.x + 107, indicator.position.y + 25 + 4 + offset), ImColor(203, 207, 206), xorstr_("(hold on)"));
			offset += 15.f;
		}
	}
	m_keybinds.clear();
}
void keybind() {
	ImVec2 position;
	ImDrawList* drawList_test;
	auto count = 0;
	if (vars::combat::manipulator && GetAsyncKeyState(vars::keys::manipulated_key))  count++;
	if (vars::combat::instakill && GetAsyncKeyState(vars::keys::instakill)) count++;
	if (vars::misc::long_neck && GetAsyncKeyState(vars::keys::longneck)) count++;
	if (vars::combat::desync && GetAsyncKeyState(vars::keys::desync)) count++;
	if (vars::visuals::zoom && GetAsyncKeyState(vars::keys::zoom)) count++;
	if (vars::misc::interactive_debug && GetAsyncKeyState(vars::keys::debugging)) count++;
	if (vars::misc::speedhack && GetAsyncKeyState(vars::keys::speedkey)) count++;
	if (vars::misc::weapon_spam && GetAsyncKeyState(vars::keys::weaponspam)) count++;
	if (vars::misc::modelstate && GetAsyncKeyState(vars::keys::ModelState)) count++;
	ImGui::SetNextWindowSize(ImVec2(160, 25 * count + 25));
	ImGui::Begin(xorstr_("keybinds"), nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize); {
		auto offset = 2;
		ImDrawList* drawList = ImGui::GetWindowDrawList();
		drawList_test = drawList;
		const ImVec2 origin(ImGui::GetCursorScreenPos());
		position = ImGui::GetWindowPos();
		//drawList->AddRectFilled(ImVec2(position.x, position.y + 23), ImVec2(position.x + 160, position.y + 26), ImColor(130, 20, 20));//167
		drawList->AddRectFilled(position, ImVec2(position.x + 160, position.y + 25), ImColor(26, 26, 26), 7, ImDrawFlags_RoundCornersTop);//167
		drawList->AddRectFilled(ImVec2(position.x, position.y + 24 ), ImVec2(position.x + 160, position.y + 25 + 25 * count), ImColor(107, 107, 107, 60));//167
	
		//drawList->AddRect(position, ImVec2(position.x + 160, position.y + 25), ImColor(21, 18, 13), ImDrawFlags_RoundCornersTop);//167
	//	drawList->AddRectFilled(ImVec2(position.x, position.y + 24), ImVec2(position.x + 160, position.y + 25), ImColor(130, 20, 20));//167
		auto size_text = flogs->CalcTextSizeA(13.f, FLT_MAX, NULL, xorstr_("keybinds"));
		drawList->AddText(flogs, 13.f, ImVec2(position.x + 10 /*+ 160 / 2 - size_text.x / 2*/, position.y + 25 / 2 - size_text.y / 2), ImColor(255, 255, 255), xorstr_("Keybinds"));
		m_keybinds.push_back(m_keybind(drawList, position, "Manipulator", vars::keys::manipulated_key));
		m_keybinds.push_back(m_keybind(drawList, position, "Timeshot", vars::keys::instakill));
		m_keybinds.push_back(m_keybind(drawList, position, "Long Neck", vars::keys::longneck));
		m_keybinds.push_back(m_keybind(drawList, position, "Desync", vars::keys::desync));
		m_keybinds.push_back(m_keybind(drawList, position, "Zoom", vars::keys::zoom));
		m_keybinds.push_back(m_keybind(drawList, position, "Debug", vars::keys::debugging));
		m_keybinds.push_back(m_keybind(drawList, position, "Time Scale", vars::keys::speedkey));
		m_keybinds.push_back(m_keybind(drawList, position, "Fake Shoots", vars::keys::weaponspam));
		m_keybinds.push_back(m_keybind(drawList, position, "ModelState", vars::keys::ModelState));
	}
	ImGui::End();
}
//void Watermarck() {
//	ImVec2 position;
//	ImDrawList* drawList_test;
//	auto count = 0;
//	char name[UNLEN + 1];
//	DWORD username_len = UNLEN + 1;
//	GetUserNameA(name, &username_len);
//	std::string winname = name;
//	std::time_t result = std::time(nullptr);
//	std::string wintime = std::asctime(std::localtime(&result));
//	time_t lt;
//	struct tm* t_m;
//	lt = time(NULL);
//	t_m = localtime(&lt);
//
//	int time_h = t_m->tm_hour;
//	int time_m = t_m->tm_min;
//	int time_s = t_m->tm_sec;
//
//	std::string time;
//
//	if (time_h < 10)
//		time += "0";
//
//	time += std::to_string(time_h) + ":";
//
//	if (time_m < 10)
//		time += "0";
//
//	time += std::to_string(time_m) + ":";
//
//	if (time_s < 10)
//		time += "0";
//
//	time += std::to_string(time_s);
//	float sWidth = vars::stuff::ScreenWidth;
//	ImGuiStyle* style = &ImGui::GetStyle();
//
//
//
//	const char* _text = (u8" Satanic   Last Update: " __DATE__ " | User: ");
//	std::string _text1 = (winname.c_str());
//	const char* _text2(" | ");
//	float damage = Time::time();
//	std::string string;
//	char buf[256] = { 0 }; sprintf_s(buf, xorstr_(" | Plays For %.f Seconds"), damage);
//	string += buf;
//
//	const char* _text3(wintime.c_str());
//	std::string waterka = _text + _text1 + string;
//	auto size_text = flogs->CalcTextSizeA(13.f, FLT_MAX, NULL, waterka.c_str());
//	std::string waterka1 = "E";
//	auto size_text1 = worldico->CalcTextSizeA(26.f, FLT_MAX, NULL, waterka1.c_str());
//	ImGui::SetNextWindowPos(ImVec2(vars::stuff::ScreenWidth - 480, 15));
//	ImGui::SetNextWindowSize(ImVec2(20 + size_text.x + size_text1.x,  60));
//	ImGui::Begin(xorstr_("Watermark"), nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize); {
//
//
//		auto offset = 2;
//		ImDrawList* drawList = ImGui::GetWindowDrawList();
//		drawList_test = drawList;
//		const ImVec2 origin(ImGui::GetCursorScreenPos());
//		position = ImGui::GetWindowPos();
//		
//		drawList->AddRectFilled(position, ImVec2(position.x + 20 + size_text.x + size_text1.x, position.y + 25), ImColor(31, 30, 30),7);//167
//		drawList->AddRectFilled(position, ImVec2(position.x + size_text1.x + flogs->CalcTextSizeA(13.f, FLT_MAX, NULL, "Satanic    |").x, position.y + 25), ImColor(130, 20, 20), 7 , ImDrawFlags_RoundCornersLeft);//167
//		drawList->AddRect(position, ImVec2(position.x + 20 + size_text.x + size_text1.x, position.y + 25), ImColor(37, 37, 36, 100), 7);
//	//	drawList->AddRect(position, ImVec2(position.x + 20 + size_text.x, position.y + 25), ImColor(21, 18, 13), 10.f);//167
//		//drawList->AddRectFilled(ImVec2(position.x, position.y + 23), ImVec2(position.x + 19 + size_text.x, position.y + 25), ImColor(130, 20, 20));//
//		drawList->AddText(worldico,30.f, ImVec2(position.x + 5 , position.y  /*- size_text1.y / 2*/), ImColor(255, 255, 255), "E" );
//		drawList->AddText(flogs, 13.f, ImVec2(position.x + 10 + size_text1.x, position.y + 13 - size_text.y / 2), ImColor(255, 255, 255), waterka.c_str());
//	
//	}
//	ImGui::End();
//}
void pre_draw() {
	//static std::map< ImGuiID, TabAnimation > TabMap;
	ImGuiContext& g = *GImGui;
	if (vars::crosshair::swastika) {
		float xs = vars::stuff::ScreenWidth / 2, ys = vars::stuff::ScreenHeight / 2;
		static float rotation_degree = 0.f;
		if (rotation_degree > 89.f)
			rotation_degree = 0.f;
		rotation_degree += vars::crosshair::speed; // скорость вращения свастона
		int length = (int)(vars::stuff::ScreenWidth / vars::crosshair::razmer / 15); // размер свастона
		float gamma = atan(length / length);
		int i = 0;
		while (i < 4)
		{
			std::vector <int> p
			{
				int(length * sin(Math::GRD_TO_BOG(rotation_degree + (i * 90)))),
				int(length * cos(Math::GRD_TO_BOG(rotation_degree + (i * 90)))),
				int((length / cos(gamma)) * sin(Math::GRD_TO_BOG(rotation_degree + (i * 90) + RAD2DEG(gamma)))),
				int((length / cos(gamma)) * cos(Math::GRD_TO_BOG(rotation_degree + (i * 90) + RAD2DEG(gamma))))
			};
			g_Render->DrawLine(xs, ys, xs + p[0], ys - p[1], ImColor(vars::colors::swaston_color), 1.f);
			g_Render->DrawLine(xs + p[0], ys - p[1], xs + p[2], ys - p[3], ImColor(vars::colors::swaston_color), 1.f);
			i++;
		}
	}
	auto* TargetPlayerA = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer);
	if (vars::visuals::GameSense) {
		if (GetAsyncKeyState(vars::keys::manipulated_key)) m_indicators.push_back({ "MP", ImColor(0, 255, 0,255) });
		if (GetAsyncKeyState(vars::keys::instakill)) m_indicators.push_back({ "TM", ImColor(255, 255, 255,255) });
		if (GetAsyncKeyState(vars::keys::longneck)) m_indicators.push_back({ "LN", ImColor(255, 255, 255,255) });
		if (GetAsyncKeyState(vars::keys::desync)) m_indicators.push_back({ "Desync", ImColor(255, 255, 255,255) });
		if (GetAsyncKeyState(vars::keys::zoom)) m_indicators.push_back({ "Zoom", ImColor(255, 255, 255,255) });
		if (GetAsyncKeyState(vars::keys::debugging)) m_indicators.push_back({ "Debug", ImColor(255, 255, 255,255) });
		if (GetAsyncKeyState(vars::keys::speedkey)) m_indicators.push_back({ "TM", ImColor(255, 255, 255,255) });
		if (GetAsyncKeyState(vars::keys::weaponspam)) m_indicators.push_back({ "FS", ImColor(255, 255, 255,255) });
	}
	if (vars::visuals::keybinds) keybind();
	AddIndicators();
	Addbind();

	//if (vars::visuals::waterka) Watermarck();
	float xs = vars::stuff::ScreenWidth / 2, ys = vars::stuff::ScreenHeight / 2;
	if (vars::misc::flyhack_indicator) {
		if (vars::stuff::flyhack / vars::stuff::max_flyhack >= 3.f) {
			g_Render->Progbar({ xs - 400, ys - 400 }, { 800, 5 }, vars::stuff::flyhack / vars::stuff::max_flyhack, vars::stuff::flyhack / vars::stuff::max_flyhack);
		}
		else {
			g_Render->Progbar({ xs - 400, ys - 410 }, { 800, 5 }, vars::stuff::flyhack / vars::stuff::max_flyhack, 1.f);
		}

		if (vars::stuff::hor_flyhack / vars::stuff::max_hor_flyhack >= 6.5f) {
			g_Render->Progbar({ xs - 400, ys - 400 }, { 800, 5 }, vars::stuff::hor_flyhack / vars::stuff::max_hor_flyhack, vars::stuff::hor_flyhack / vars::stuff::max_hor_flyhack);
		}
		else {
			g_Render->Progbar({ xs - 400, ys - 400 }, { 800, 5 }, vars::stuff::hor_flyhack / vars::stuff::max_hor_flyhack, 1.f);
		}
	}

	if (vars::crosshair::default) {
		g_Render->DrawLine(xs, ys, xs + 4, ys + 4, ImColor(255, 255, 255, 255), 0.7f);
		g_Render->DrawLine(xs, ys, xs + 4, ys - 4, ImColor(255, 255, 255, 255), 0.7f);
		g_Render->DrawLine(xs, ys, xs - 4, ys - 4, ImColor(255, 255, 255, 255), 0.7f);
		g_Render->DrawLine(xs, ys, xs - 4, ys + 4, ImColor(255, 255, 255, 255), 0.7f);

		g_Render->DrawLine(xs + 4, ys + 4, xs + 4 + 4, ys + 4 + 4, ImColor(vars::colors::default_color), 0.7f);
		g_Render->DrawLine(xs + 4, ys - 4, xs + 4 + 4, ys - 4 - 4, ImColor(vars::colors::default_color), 0.7f);
		g_Render->DrawLine(xs - 4, ys - 4, xs - 4 - 4, ys - 4 - 4, ImColor(vars::colors::default_color), 0.7f);
		g_Render->DrawLine(xs - 4, ys + 4, xs - 4 - 4, ys + 4 + 4, ImColor(vars::colors::default_color), 0.7f);
	}
	if (vars::crosshair::custom) {
		g_Render->FilledRectGradient(xs + vars::crosshair::gap, ys, vars::crosshair::length, 1, ImColor(vars::colors::custom_color), ImColor(vars::colors::custom_color[0], vars::colors::custom_color[1], vars::colors::custom_color[2], 0.0f), ImColor(vars::colors::custom_color[0], vars::colors::custom_color[1], vars::colors::custom_color[2], 0.0f), ImColor(vars::colors::custom_color));
		g_Render->FilledRectGradient(xs - vars::crosshair::gap + 2, ys, -vars::crosshair::length, 1, ImColor(vars::colors::custom_color), ImColor(vars::colors::custom_color[0], vars::colors::custom_color[1], vars::colors::custom_color[2], 0.0f), ImColor(vars::colors::custom_color[0], vars::colors::custom_color[1], vars::colors::custom_color[2], 0.0f), ImColor(vars::colors::custom_color));
		g_Render->FilledRectGradient(xs, ys - vars::crosshair::gap + 2, 1, -vars::crosshair::length, ImColor(vars::colors::custom_color), ImColor(vars::colors::custom_color), ImColor(vars::colors::custom_color[0], vars::colors::custom_color[1], vars::colors::custom_color[2], 0.0f), ImColor(vars::colors::custom_color[0], vars::colors::custom_color[1], vars::colors::custom_color[2], 0.0f));
		g_Render->FilledRectGradient(xs, ys + vars::crosshair::gap, 1, vars::crosshair::length, ImColor(vars::colors::custom_color), ImColor(vars::colors::custom_color), ImColor(vars::colors::custom_color[0], vars::colors::custom_color[1], vars::colors::custom_color[2], 0.0f), ImColor(vars::colors::custom_color[0], vars::colors::custom_color[1], vars::colors::custom_color[2], 0.0f));
	}
	if (vars::crosshair::dot) {
		g_Render->CircleFilled(xs, ys + 1.f, 1.8, ImColor(vars::colors::dot_color), 0);
	}
	if (vars::crosshair::cadicall) {
		g_Render->FilledRect(xs + 8.f, ys, 8.f, 3, ImColor(vars::colors::cadicall_color), 0, 0);
		g_Render->FilledRect(xs - 8.f, ys, -8.f, 3, ImColor(vars::colors::cadicall_color), 0, 0);
		g_Render->CircleFilled(xs, ys + 1.f, 1.8, ImColor(vars::colors::cadicall_color), 0);
	}
	if (vars::combat::visualize_fov) {
		if (vars::players::fovstyle == 0) {
			g_Render->Rect(xs - vars::combat::fov, ys - vars::combat::fov , vars::combat::fov * 2, vars::combat::fov * 2, ImColor(vars::colors::fov_color), 2, 0);
		}
		if (vars::players::fovstyle == 1) {
			g_Render->DrawCircle(xs, ys, vars::combat::fov, 1.2f, ImColor(vars::colors::fov_color));
		}
		/*g_Render->Rect(xs, ys, vars::combat::fov, 1.2f, ImColor(vars::colors::fov_color), 20, 0);

		g_Render->DrawCircle(xs, ys, vars::combat::fov, 1.2f, ImColor(vars::colors::fov_color));*/
		//	g_Render->AddRadialGradient(ImVec2(xs, ys), 10.f, ImColor(vars::colors::fov_color), ImColor(0, 0, 0, 0));
	}
	float FOV = vars::combat::fov, CurFOV;
	if (vars::stor::closestPlayer != NULL) {
		if (FOV < (CurFOV = GetFov(TargetPlayerA, BoneList(0.5))) ) {
			vars::stor::closestPlayer = NULL;
		}
	}
	if (vars::stor::closestHeli != NULL) {
		Vector3 pos = reinterpret_cast<BaseEntity*>(vars::stor::closestHeli)->transform()->position();
		if (FOV < (CurFOV = GetFovHeli(pos))) {
			vars::stor::closestHeli = NULL;
		}
	}

	if (reinterpret_cast<BaseEntity*>(vars::stor::closestPlayer)->IsDestroyed()) {
		vars::stor::closestPlayer = NULL;
	}
	if (reinterpret_cast<BaseEntity*>(vars::stor::closestHeli)->IsDestroyed()) {
		vars::stor::closestHeli = NULL;
	}

	if (vars::combat::manipulator && !other::m_manipulate.empty() && vars::stor::closestPlayer != NULL) {
		//OxyRender::Text(Vector2{ xs, ys - 50 }, D2D1::ColorF::Red, true, true, xorstr_(L"%s manipulated"), TargetPlayerA->_displayName());
		std::string string;
		char buf[256] = { 0 }; sprintf_s(buf, xorstr_(u8"%ls manipulated"), TargetPlayerA->_displayName());
		string += buf;
		g_Render->DrawString(xs, ys - 50, ImColor(255, 0, 0), render2::outline | render2::centered_x, Cuniaabyser, vars::misc::fotsize, string.c_str());
	}



	
	if (vars::visuals::wrn) {
		float bpfov = 20.f;
		float xs = vars::stuff::ScreenWidth / 2, ys = vars::stuff::ScreenHeight / 2;
		if (utils::LineOfSight(reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->GetBoneByID(head), LocalPlayer::Entity()->GetBoneByID(head))) {
			std::string string;
			char buf[256] = { 0 }; sprintf_s(buf, xorstr_(u8"%ls check u"), TargetPlayerA->_displayName());
			string += buf;
			g_Render->DrawString(xs, ys + 15, ImColor(vars::colors::target_name_color), render2::outline | render2::centered_x, Cuniaabyser, vars::misc::fotsize, string.c_str());

		}
	}
	if (vars::visuals::target_name) {
		if (vars::stor::closestPlayer != NULL) {
			std::string string;
			std::string _name(CStringA(TargetPlayerA->_displayName()));
			char buf[256] = { 0 }; sprintf_s(buf, xorstr_(u8"target: ") + (CStringA(TargetPlayerA->_displayName())));
			string += buf;
			g_Render->DrawString(xs, ys + 15, ImColor(vars::colors::target_name_color), render2::outline | render2::centered_x, Cuniaabyser, vars::misc::fotsize, string.c_str());
		}
		else {
			std::string string;
			char buf[256] = { 0 }; sprintf_s(buf, xorstr_(u8"target: no found"));
			string += buf;
			g_Render->DrawString(xs, ys + 15, ImColor(vars::colors::target_name_color), render2::outline | render2::centered_x, Cuniaabyser, vars::misc::fotsize, string.c_str());
		}
	}
	/*if (vars::ores::closest_ore) {
		static float screenX = vars::stuff::ScreenWidth;
		static float screenY = vars::stuff::ScreenHeight;
		Vector2 startPos = Vector2(screenX / 2.f, screenY);

		f_object tr1 = f_object::get_closest_object(LocalPlayer::Entity()->GetBoneByID(head), xorstr_("ore.prefab"));
		Vector2 screen;
		if (utils::w2s(tr1.position, screen) && tr1.valid) {
			g_Render->DrawLine(startPos.x, startPos.y, screen.x, screen.y, ImColor(255, 255, 255), 1.f);

			f_object tr2 = f_object::get_closest_object(tr1.position, xorstr_("ore.prefab"), tr1.position);
			Vector2 screen2;
			if (utils::w2s(tr2.position, screen2) && tr2.valid) {
				g_Render->DrawLine(screen.x, screen.y, screen2.x, screen2.y, ImColor(255, 255, 255), 1.f);

				f_object tr3 = f_object::get_closest_object(tr2.position, xorstr_("ore.prefab"), tr1.position, tr2.position);
				Vector2 screen3;
				if (utils::w2s(tr3.position, screen3) && tr3.valid) {
					g_Render->DrawLine(screen2.x, screen2.y, screen3.x, screen3.y, ImColor(255, 255, 255), 1.f);

					f_object tr4 = f_object::get_closest_object(tr3.position, xorstr_("ore.prefab"), tr1.position, tr2.position, tr3.position);
					Vector2 screen4;
					if (utils::w2s(tr4.position, screen4) && tr4.valid) {
						g_Render->DrawLine(screen3.x, screen3.y, screen4.x, screen4.y, ImColor(255, 255, 255), 1.f);
					}
				}
			}
		}
	}*/
	if (vars::players::targetline) {
		if (vars::stor::closestPlayer != NULL && TargetPlayerA->IsValid()) {
			static float screenX = vars::stuff::ScreenWidth;
			static float screenY = vars::stuff::ScreenHeight;
			static Vector2 startPos;
			if (vars::players::targetline_pos == 0) {
				startPos = Vector2(screenX / 2.f, screenY);
			}
			if (vars::players::targetline_pos == 1) {
				startPos = Vector2(screenX / 2, screenY / 2);
			}
			Vector2 ScreenPos;
			if (!(TargetPlayerA->GetBoneByID(spine1).x == 0 && TargetPlayerA->GetBoneByID(spine1).y == 0 && TargetPlayerA->GetBoneByID(spine1).z == 0)) {
				if (utils::w2s(TargetPlayerA->GetBoneByID(head), ScreenPos)) {
					g_Render->DrawLine(startPos.x, startPos.y, ScreenPos.x, ScreenPos.y, ImColor(255, 0, 0), 1.f);
				}
			}
		}
	}
	if (vars::combat::visualize_prediction && TargetPlayerA->IsValid()) {
		Vector2 t;
		if (!(TargetPlayerA->GetBoneByID(spine1).x == 0 && TargetPlayerA->GetBoneByID(spine1).y == 0 && TargetPlayerA->GetBoneByID(spine1).z == 0)) {
			if (utils::w2s(a::get_aim_point(GetBulletSpeed(), GetGravity(LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo())), t)) {
			
				
					g_Render->DrawString(t.x, t.y, ImColor(vars::colors::prediction_color), render2::outline | render2::centered_x, Cuniaabyser, vars::misc::fotsize, xorstr_("X"));
				
			
			}
		}
	}
	if (vars::stor::closestHeli != NULL && vars::visuals::patrol_heli) {
		static float screenX = vars::stuff::ScreenWidth;
		static float screenY = vars::stuff::ScreenHeight;
		static Vector2 startPos = Vector2(screenX / 2.f, screenY - 200.f);
		Vector2 ScreenPos;
		if ((int)ceil(read(vars::stor::closestHeli + 0x20C, float)) > 0) {
			if (utils::w2s(reinterpret_cast<BaseEntity*>(vars::stor::closestHeli)->transform()->position(), ScreenPos));
			//Renderer::Line(startPos, ScreenPos, D2D1::ColorF(0.3f, 0.34f, 1.f), 1.f);
		}

	}
	if (vars::combat::smooth_factor <= 0) { vars::combat::smooth_factor = 1; }
	if (vars::misc::grade_ > 4) { vars::misc::grade_ = 4; }
	if (vars::weapons::hitdistance < 300) { vars::weapons::hitdistance = 300; }
	if (vars::misc::anti_aim && vars::misc::anti_aim_indicator) {
		int radius = 80;
		float range = 5;
		int LineLength = 50;
		POINT p;
		if (GetCursorPos(&p)) {
			if (p.x >= indicator_x - radius && p.x <= indicator_x + radius) {
				if (p.y >= indicator_y - radius && p.y <= indicator_y + radius) {
					if (GetAsyncKeyState(VK_LBUTTON) && show) {
						indicator_x = p.x;
						indicator_y = p.y;
					}
				}
			}
		}
		g_Render->FilledRect(indicator_x - radius, indicator_y - radius, radius + 80, radius + 80, ImColor(31, 31, 31, 130), 10, 0);
	//	Renderer::FillCircle(Vector2(indicator_x, indicator_y), D2D1::ColorF(0.13, 0.13, 0.13, 0.6), radius);//this draws that grey circle u see :]
		float origyaw = vars::stuff::anti_aim_;
	//	g_Render->DrawLine(radius / 2, radius / 2, radius  / 2+ origyaw, ImColor(140, 0, 0), 1.5f, true);
		CosTanSinLine(origyaw, range, indicator_x, indicator_y, LineLength, ImColor(140, 0, 0));//this the function from b4 btw
	}
	if (TargetPlayerA) {
		if (vars::stor::closestPlayer != NULL && !TargetPlayerA->IsNpc() && vars::players::belt && TargetPlayerA->IsValid()) {
			const float Height = 180.f;
			const float Width = 200.f;
			POINT p;
			if (GetCursorPos(&p)) {
				if (p.x >= vars::players::beltx && p.x <= vars::players::beltx + Width) {
					if (p.y >= vars::players::belty && p.y <= vars::players::belty + Height) {
						if (GetAsyncKeyState(VK_LBUTTON) && show) {
							vars::players::beltx = p.x - (Width / 2);
							vars::players::belty = p.y - (Height / 2);
						}
					}
				}
			}
			g_Render->FilledRect(vars::players::beltx, vars::players::belty, Width, Height, ImColor(31, 31, 31), 10, 0);
			

		//	Renderer::FillRoundedRectangle({ vars::players::beltx, vars::players::belty }, { 200, 20 }, D2D1::ColorF(0.14f, 0.14f, 0.14f), 18);
	//		Renderer::FillRectangle({ vars::players::beltx, vars::players::belty + 10 }, { 200, 20 }, D2D1::ColorF(0.14f, 0.14f, 0.14f));
			//Renderer::FillRoundedRectangle({ vars::players::beltx, vars::players::belty }, { Width, Height }, D2D1::ColorF(0.14f, 0.14f, 0.14f), 18);
			std::string string;	char buf[256] = { 0 };
		
			std::string _name(CStringA(TargetPlayerA->_displayName()));
			sprintf_s(buf, xorstr_("Belt ") + (CStringA(TargetPlayerA->_displayName())));
			string += buf;
			g_Render->DrawString(vars::players::beltx + (Width / 2), vars::players::belty + 3, ImColor(255,255,255), render2::outline | render2::centered_x, Cuniaabyser, 12,  string.c_str());
			g_Render->Rect(vars::players::beltx, vars::players::belty + 15, Width, 2, ImColor(130, 20, 20), 10, 0);
			float Pos = 0;
			if (TargetPlayerA->item_list_b()) {
				for (int i = 0; i < TargetPlayerA->item_list_b()->get_size(); i++) { // belt
					Item* ActWeapon = TargetPlayerA->item_list_b()->get_value(i);
					if (ActWeapon) {
						if (ActWeapon == TargetPlayerA->GetActiveWeapon()) {
							wchar_t* ActiveItem = ActWeapon->get_name();
							std::string string;	char buf[256] = { 0 };
							sprintf_s(buf, xorstr_("%ls"), ActiveItem);
							string += buf;
							if (ActiveItem) {
								g_Render->DrawString(vars::players::beltx + (Width / 2), vars::players::belty + 40 + Pos, ImColor(255, 255, 255), render2::outline | render2::centered_x, Cuniaabyser, 12, string.c_str());
							//	Renderer::Text({ vars::players::beltx + (Width / 2), vars::players::belty + 40 + Pos }, D2D1::ColorF::Red, true, true, xorstr_(L"%s"), ActiveItem);
							}
						}
						else {
							wchar_t* ActiveItem = ActWeapon->get_name();
							std::string string;	char buf[256] = { 0 };
							sprintf_s(buf, xorstr_("%ls"), ActiveItem);
							string += buf;
							if (ActiveItem) {
								g_Render->DrawString(vars::players::beltx + (Width / 2), vars::players::belty + 40 + Pos, ImColor(203, 207, 206), render2::outline | render2::centered_x, Cuniaabyser, 12, string.c_str());
							//	Renderer::Text({ vars::players::beltx + (Width / 2), vars::players::belty + 40 + Pos }, D2D1::ColorF::White, true, true, xorstr_(L"%s"), ActiveItem);
							}
						}
					}
					Pos += 15;
				}
			}
		}
	}
	if (TargetPlayerA) {
		if (vars::stor::closestPlayer != NULL && !TargetPlayerA->IsNpc() && vars::players::clothes && TargetPlayerA->IsValid()) {
			const float Height = 180.f;
			const float Width = 200.f;
			POINT p;
			if (GetCursorPos(&p)) {
				if (p.x >= vars::players::clothesx && p.x <= vars::players::clothesx + Width) {
					if (p.y >= vars::players::clothesy && p.y <= vars::players::clothesy + Height) {
						if (GetAsyncKeyState(VK_LBUTTON) && show) {
							vars::players::clothesx = p.x - (Width / 2);
							vars::players::clothesy = p.y - (Height / 2);
						}
					}
				}
			}
			std::string string;	char buf[256] = { 0 };
			std::string _name(CStringA(TargetPlayerA->_displayName()));
			sprintf_s(buf, xorstr_("Clothes ") + (CStringA(TargetPlayerA->_displayName())));
			string += buf;
			g_Render->FilledRect(vars::players::clothesx, vars::players::clothesy, Width, Height, ImColor(31, 31, 31), 10, 0);
			
			g_Render->DrawString(vars::players::clothesx + (Width / 2), vars::players::clothesy + 3, ImColor(255, 255, 255), render2::outline | render2::centered_x, Cuniaabyser, 12, string.c_str());
			g_Render->Rect(vars::players::clothesx, vars::players::clothesy + 15, Width, 2, ImColor(130, 20, 20), 10, 0);
			float Pos = 0;
			if (TargetPlayerA->item_list_w()) {
				for (int i = 0; i < TargetPlayerA->item_list_w()->get_size(); i++) { // clothes
					Item* ActWeapon = TargetPlayerA->GetClothesInfo(i);
					if (ActWeapon) {
						wchar_t* ActiveItem = ActWeapon->get_name();
						std::string string;	char buf[256] = { 0 };
						sprintf_s(buf, xorstr_("%ls"), ActiveItem);
						string += buf;
						if (ActiveItem) {
							g_Render->DrawString(vars::players::clothesx + (Width / 2), vars::players::clothesy + 40 + Pos, ImColor(203, 207, 206), render2::outline | render2::centered_x, Cuniaabyser, 12,  string.c_str());
						}
					}
					Pos += 15;
				}
			}
		}
	}

	if (vars::players::belt  && !reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)) {
		const float Height = 180.f;
		const float Width = 200.f;
		POINT p;
		if (GetCursorPos(&p)) {
			if (p.x >= vars::players::beltx && p.x <= vars::players::beltx + Width) {
				if (p.y >= vars::players::belty && p.y <= vars::players::belty + Height) {
					if (GetAsyncKeyState(VK_LBUTTON) && show) {
						vars::players::beltx = p.x - (Width / 2);
						vars::players::belty = p.y - (Height / 2);
					}
				}
			}
		}

		g_Render->FilledRect(vars::players::beltx, vars::players::belty, Width, Height, ImColor(31, 31, 31), 10, 10);	
		g_Render->DrawString(vars::players::beltx + (Width / 2), vars::players::belty + 3, ImColor(255, 255, 255), render2::outline | render2::centered_x, Cuniaabyser, 12, "Belt");
		g_Render->Rect(vars::players::beltx, vars::players::belty + 15, Width, 2, ImColor(130, 20, 20), 10, 0);
	}
	if (vars::players::clothes  && !reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)) {
		const float Height = 180.f;
		const float Width = 200.f;
		POINT p;
		if (GetCursorPos(&p)) {
			if (p.x >= vars::players::clothesx && p.x <= vars::players::clothesx + Width) {
				if (p.y >= vars::players::clothesy && p.y <= vars::players::clothesy + Height) {
					if (GetAsyncKeyState(VK_LBUTTON) && show) {
						vars::players::clothesx = p.x - (Width / 2);
						vars::players::clothesy = p.y - (Height / 2);
					}
				}
			}
		}

		g_Render->FilledRect(vars::players::clothesx, vars::players::clothesy, Width, Height, ImColor(31, 31, 31), 10, 0);
		g_Render->DrawString(vars::players::clothesx + (Width / 2), vars::players::clothesy + 3, ImColor(255, 255, 255), render2::outline | render2::centered_x, Cuniaabyser, 12, "Сlothes");
		g_Render->Rect(vars::players::clothesx, vars::players::clothesy + 15, Width, 2, ImColor(130, 20, 20), 10, 0);

	}
	if (vars::visuals::radar_) {
		radar::radar_bg();
	}
	LogSystem::Render();
	if (vars::visuals::raid_esp) {
		LogSystem::RenderExplosions();
	}
	ent_loop();
}