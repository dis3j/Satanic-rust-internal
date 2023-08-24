#include <random>
#pragma comment(lib, "Urlmon.lib")
namespace keybinds_ {
	Vector2 pos = Vector2(300, 300);
	bool should_drag = false;
	bool should_move = false;

	POINT cursor;
	POINT cursor_corrected;
	void belt_tab_mov(Vector2 size) {
		GetCursorPos(&cursor);

		if (GetAsyncKeyState(VK_LBUTTON) && (cursor.x > pos.x && cursor.y > pos.y && cursor.x < pos.x + size.x && cursor.y < pos.y + size.y)) {
			should_drag = true;
			if (!should_move) {
				cursor_corrected.x = cursor.x - pos.x;
				cursor_corrected.y = cursor.y - pos.y;
				should_move = true;
			}
		}

		if (should_drag) {
			pos.x = cursor.x - cursor_corrected.x;
			pos.y = cursor.y - cursor_corrected.y;
		}

		if (GetAsyncKeyState(VK_LBUTTON) == 0) {
			should_drag = false;
			should_move = false;
		}
	}
}	
DWORD64 Entity1;
int EntityCount1;
DWORD64 Object1;

DWORD64 ObjectClass1 ;

pUncStr name1 ;

using namespace otherEsp;
bool inited = false;
void ent_loop() {
	DrawList = ImGui::GetBackgroundDrawList();
	static float r = 1.00f, g = 0.00f, b = 1.00f;
	static int cases = 0;
	switch (cases)
	{
	case 0: { r -= 0.005f; if (r <= 0) cases += 1; break; }
	case 1: { g += 0.005f; b -= 0.005f; if (g >= 1) cases += 1; break; }
	case 2: { r += 0.005f; if (r >= 1) cases += 1; break; }
	case 3: { b += 0.005f; g -= 0.005f; if (b >= 1) cases = 0; break; }
	default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
	}
	uintptr_t bn = read(vars::stor::gBase + CO::BaseNetworkable, uintptr_t);
	if (!bn) {
		std::string string;
		char buf[256] = { 0 }; sprintf_s(buf, xorstr_(u8"Wrong game version! dm poves_Satanic"));
		string += buf;
		float xs = vars::stuff::ScreenWidth / 2, ys = vars::stuff::ScreenHeight / 2;
		g_Render->DrawString(155, 10, ImColor(255, 0, 0), render2::outline | render2::centered_x, Cuniaabyser, 11, string.c_str());
		return;
	}
	if (!inited) {
		//rename("C:\\Rawetrip\\", "C:\\Satanic\\");//Satanic
		/*Sleep(100);
		CreateDirectoryA(xorstr_("C:\\Satanic"), NULL);*/
		bool result = false;
		char name[UNLEN + 1];
		DWORD username_len = UNLEN + 1;
		GetUserNameA(name, &username_len);
		CreateDirectoryA(xorstr_("C:\\Satanic"), NULL);
		std::string winname = name;
		config.Initialize();
		inited = true;
		

		

	//	PlaySoundA((LPCSTR)audio_2023, NULL, SND_MEMORY | SND_ASYNC);
		//PlaySoundA((LPCSTR)Loading, NULL, SND_MEMORY | SND_ASYNC);
			Beep(10,10);
			//PlaySoundA((LPCSTR)cowbellhit, NULL, SND_MEMORY | SND_ASYNC);
				//PlaySoundA((LPCSTR)done, NULL, SND_MEMORY | SND_ASYNC);

	}
	if (!LocalPlayer::Entity()) return;
	static float faken_rot = 0.0f;
	static int gamerjuice = 0;
	float a = screen_center.y / 30.0f;
	float gamma = atan(a / a);
	if (vars::combat::instakill_indicator) {
		float xs = vars::stuff::ScreenWidth / 2, ys = vars::stuff::ScreenHeight / 2;
		float size = 200;
		g_Render->Rect(xs - (size / 2), ys + 30.f, size, 3.f, ImColor(0.f, 0.f, 0.f, 1.f), 20, 0);
		if (vars::combat::instakill_indicator) {
			auto desynctime = (Time::realtimeSinceStartup() - LocalPlayer::Entity()->lastSentTickTime()) - 0.03125 * 3;
			auto desyncpercentage = (((desynctime / 0.85f) * 100.0f) + 1.f) / 100;
			float red, green, blue;
			float Num = desyncpercentage;
			if (desyncpercentage < 0.05) Num = 0;
			if (vars::combat::instakill_indicator && Num != 0) {
				if (Num < 0.5) {
					red = Num * 2.f * 255.f;
					green = 255.f;
					blue = 0.f;
				}
				else {
					red = 255.f;
					green = (2.f - 2.f * Num) * 255.f;
					blue = 0.f;
				}

				if (Num > 1.f)
					Num = 1.f;

				ImVec2 center(vars::stuff::ScreenWidth / 2, vars::stuff::ScreenHeight / 2);
				float size = 200;
				float x = (desynctime * size);
				if (x > (size) * 2)
					x = (size) * 2; //s
				if (GetAsyncKeyState(vars::keys::manipulated_key) || GetAsyncKeyState(vars::keys::instakill))
				{
					g_Render->FilledRect(xs - (size / 2) + 1, ys + 30.f, x - 2, 3.f, ImColor((int)(red), (int)(green), (int)(blue)), 20, 0);
				}
			}
		}
		g_Render->Rect(xs - (size / 2), ys + 30.f, size, 3.f, ImColor(0.f, 0.f, 0.f, 1.f), 20, 0);
	}
	if (vars::misc::reload_coldown) {
		float xs = vars::stuff::ScreenWidth / 2, ys = vars::stuff::ScreenHeight / 2;
		auto held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();
		float size = 200;
		g_Render->Rect(xs - (size / 2), ys + 40.f - 4, size, 3.f, ImColor(0.f, 0.f, 0.f, 1.f), 26, 0);
		if (held) {
			if (did_reload == false && time_since_last_shot <= (held->reloadTime() - (held->reloadTime() / 10)) && time_since_last_shot > 0) {
				float reloadDurationTotal = (held->reloadTime() - (held->reloadTime() / 10));
				float reloadDuration = time_since_last_shot;
				auto percentage = (((reloadDuration / reloadDurationTotal) * 100.0f) + 1.f) / 100;
				float red, green, blue;
				float Num = percentage;
				if (vars::misc::reload_coldown && Num != 0) {
					if (Num < 0.5) {
						red = Num * 2.f * 255.f;
						green = 255.f;
						blue = 0.f;
					}
					else {
						red = 255.f;
						green = (2.f - 2.f * Num) * 255.f;
						blue = 0.f;
					}
					if (Num > 1.f) Num = 1.f;
					ImVec2 center(vars::stuff::ScreenWidth / 2, vars::stuff::ScreenHeight / 2);
					float size = 200;
					float x = (percentage * size);
					if (x > (size) * 2)
						x = (size) * 2; //s
					g_Render->FilledRect(xs - (size / 2) + 1, ys + 40.f - 4, x - 2, 3.f, ImColor((int)(red), (int)(green), (int)(blue)), 26, 0);
				}
			}
			else {
				if (held->HasReloadCooldown()) {
					float SamReloadDuration = held->nextReloadTime() - GLOBAL_TIME;
					float SamReloadDurationTotal = held->CalculateCooldownTime(held->nextReloadTime(), held->reloadTime()) - GLOBAL_TIME;
					auto SamPercentage = (((SamReloadDuration / SamReloadDurationTotal) * 100.0f) + 1.f) / 100;
					float red, green, blue;
					float Num = SamPercentage;
					if (vars::misc::reload_coldown && Num != 0) {
						if (Num < 0.5) {
							red = Num * 2.f * 255.f;
							green = 255.f;
							blue = 0.f;
						}
						else {
							red = 255.f;
							green = (2.f - 2.f * Num) * 255.f;
							blue = 0.f;
						}

						if (Num > 1.f)
							Num = 1.f;

						ImVec2 center(vars::stuff::ScreenWidth / 2, vars::stuff::ScreenHeight / 2);
						float size = 200;
						float x = (SamPercentage * size);
						if (x > (size) * 2)
							x = (size) * 2; //s
						g_Render->FilledRect(xs - (size / 2) + 1, ys + 40.f - 4, x - 2, 3.f, ImColor((int)(red), (int)(green), (int)(blue)), 26, 0);
					}
				}
			}

		}
		g_Render->Rect(xs - (size / 2), ys + 40.f - 4, size, 3.f, ImColor(0.f, 0.f, 0.f, 1.f), 26, 0);

	}

	float FOV = vars::combat::fov, CurFOV;
	//auto entityList = BaseNetworkable::clientEntities()->entityList();
//	if (entityList) {
	//	for (int i = 0; i < entityList->vals->size; i++) {
			DWORD64 BaseNetworkable;
			BaseNetworkable = read(vars::stor::gBase + CO::BaseNetworkable, DWORD64); //BaseNetworkable_c 
			DWORD64 EntityRealm = read(BaseNetworkable + 0xB8, DWORD64);
			DWORD64 ClientEntities = read(EntityRealm, DWORD64);
			DWORD64 ClientEntities_list = read(ClientEntities + 0x10, DWORD64);
			DWORD64 ClientEntities_values = read(ClientEntities_list + 0x28, DWORD64);
			if (!ClientEntities_values) return;
			int EntityCount = read(ClientEntities_values + 0x10, int);
			DWORD64 EntityBuffer = read(ClientEntities_values + 0x18, DWORD64);
			for (int i = 0; i <= EntityCount; i++)
			{
				
				DWORD64 Entity = read(EntityBuffer + 0x20 + (i * 0x8), DWORD64);
				if (Entity <= 100000) continue;
				DWORD64 Object = read(Entity + 0x10, DWORD64);
				if (Object <= 100000) continue;
				DWORD64 ObjectClass = read(Object + 0x30, DWORD64);
				if (ObjectClass <= 100000) continue;
				pUncStr name = read(ObjectClass + 0x60, pUncStr);
				if (!name) continue;
				char* buff = name->stub;
				BasePlayer* Player = (BasePlayer*)read(Object + 0x28, DWORD64);
			
			/*uintptr_t Entity = *reinterpret_cast<uintptr_t*>(std::uint64_t(entityList->vals->buffer) + (0x20 + (sizeof(void*) * i)));
			if (!Entity) continue;

			auto entity = *reinterpret_cast<BaseEntity**>(std::uint64_t(entityList->vals->buffer) + (0x20 + (sizeof(void*) * i)));
			if (!entity) continue;
			uintptr_t Object = *reinterpret_cast<uint64_t*>(Entity + 0x10);
			if (!Object) continue;

			uintptr_t ObjectClass = *reinterpret_cast<uint64_t*>(Object + 0x30);
			if (!ObjectClass) continue;
			

			pUncStr name = read(ObjectClass + 0x60, pUncStr); 
			if (!name) continue;
			char* buff = name->stub;*/

			if (!reinterpret_cast<BaseEntity*>(Entity)->IsValid()) { continue; }
			if (!reinterpret_cast<Component*>(Entity)->gameObject()) { continue; }
			if (strstr(buff, xorstr_("Local"))) { continue; }

		

				if (vars::visuals::radar_) {
					radar::radar_logic(ObjectClass, Entity, buff);
				}
				BasePlayer* Player1 = (BasePlayer*)read(Object + 0x28, DWORD64);
				
			if (reinterpret_cast<BaseCombatEntity*>(Entity)->IsPlayer() && (int)Math::Distance_3D(LocalPlayer::Entity()->GetBoneByID(head), Player1->GetBoneByID(head)) < 300) {
				BasePlayer* Player = (BasePlayer*)Entity;
				Vector2 screen;

			//	if (!vars::visuals::NpcEspEnable && Player->IsNpc()) continue;
				bool Playerwounded = Player->get_flag(64);
				bool PlayerDead = !Player->is_alive();
				if (!utils::OOF(Player))
				{

					if (vars::players::skeleton && !Player->IsNpc()) {
						if (!Player->get_flag(PlayerFlags::Sleeping)) {
							if (Playerwounded)
							{
								Skeleton(Player, ImColor(vars::colors::wounded_color));
							}
							else if (LocalPlayer::Entity()->is_teammate(Player)) {
								Skeleton(Player, ImColor(0, 255, 0));
							}

							else {

								//	if (Player->IsVisible()) {
								 //       	Skeleton(Player, ImColor(vars::visible::skeleton_color));//vars::visible::skeleton_color
								//	}
									//else {
								Skeleton(Player, ImColor(vars::invisible::skeleton_color));

								//}
							}
						}
						else if (Player->get_flag(PlayerFlags::Sleeping) && !vars::players::sleeperignore) {
							Skeleton(Player, ImColor(vars::colors::sleep_color));
						}
					}
					else if (vars::npc::skeleton && vars::visuals::NpcEspEnable &&Player->IsNpc()) {
						Skeleton(Player, ImColor(255, 255, 0));
					}


	
					ImColor color = ImColor(0.f, 0.f, 0.f, 1.f);
					if (!Player->IsNpc()) {
						if (!Player->get_flag(PlayerFlags::Sleeping)) {
							if (Playerwounded)
							{
								color = ImColor(vars::colors::wounded_color);
							}
							else if (PlayerDead) {
								color = ImColor(1.f, 0.f, 0.f, 1.f);
							}
							else if (LocalPlayer::Entity()->is_teammate(Player)) {
								color = ImColor(vars::colors::team_color);
							}

							else {
								/*if (Player->IsVisible()) {

									color = ImColor(vars::visible::box_color);
									}
									else {*/
								color = ImColor(vars::invisible::box_color);//vars::visible::box_color
							//	}
							}
						}


						else {
							color = ImColor(vars::colors::sleep_color);
						}

						if (vars::visuals::playerEspEnable)
						{
							ESP(Player, color);
						}



					}

					else if (Player->IsNpc()) {
						color = ImColor(255, 255, 0);
						if (Player->health() > 0) {
							if (vars::visuals::NpcEspEnable)
							{
								NPCESP(Player, ImColor(255, 255, 0));
							}

						}
					}
					else {
						color = ImColor(255, 255, 0);
					}

				}


				else
				{
					ImColor _color = ImColor(0.f, 0.f, 0.f, 1.f);
					if (!Player->IsNpc()) {
						if (!Player->get_flag(PlayerFlags::Sleeping)) {
							if (Playerwounded)
							{
								_color = ImColor(vars::colors::wounded_color);
							}
							else if (LocalPlayer::Entity()->is_teammate(Player)) {
								_color = ImColor(vars::colors::team_color);
							}
							else {
								if (PlayerDead) {
									_color = ImColor(1.f, 0.f, 0.f, 1.f);
								}
								else {
									//	BasePlayer* TargetPlayer = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer);
									//if (Player->IsVisible()) {
									//	_color = ImColor(vars::invisible::box_color);
									//	}
									//else {
									_color = ImColor(vars::invisible::box_color);//vars::visible::box_color
									//	}
								}
							}
						}
						else {
							_color = ImColor(vars::colors::sleep_color);
						}
					}


					OOF(Player, _color);
				}
				if (vars::combat::ignore_sleepers && Player->get_flag(PlayerFlags::Sleeping)) continue;

				if (!vars::visuals::NpcEspEnable && Player->IsNpc()) continue;
				if (vars::combat::ignore_team && LocalPlayer::Entity()->is_teammate(Player)) continue;
				//if (vars::combat::ignore_invisible && !Player->is_visible()) continue;
			/*	if (Player->GetBoneByID(head).x == 0 || Player->GetBoneByID(head).y == 0 || Player->GetBoneByID(head).z == 0) continue;*/
				if (vars::combat::ignore_players) continue;
				if (Math::Distance_3D(LocalPlayer::Entity()->GetBoneByID(head), Player->GetBoneByID(head)) > 300.f) continue;
				if (FOV > (CurFOV = GetFov(Player, BoneList(0.5))) && Player->is_alive() && !vars::combat::lock_target) {
					FOV = CurFOV; vars::stor::closestPlayer = (uintptr_t)Player;
				}
		
			}
			if (reinterpret_cast<BaseCombatEntity*>(Entity)->ClassNameHash() == STATIC_CRC32("BaseHelicopter")) {
				BaseEntity* helicopter = (BaseEntity*)Entity;
				if (helicopter) {
					float health = reinterpret_cast<BaseCombatEntity*>(Entity)->health();
					float maxhealth = 10000.f;
					Vector3 pos = helicopter->transform()->position();
					Vector2 screenPos;
					if (utils::w2s(pos, screenPos)) {
						if (vars::visuals::patrol_heli) {
							std::string string;
							char buf[256] = { 0 }; sprintf_s(buf, xorstr_("Helicopter[%1.0fm]"), Math::Distance_3D(LocalPlayer::Entity()->GetBoneByID(head), pos));
							string += buf;
							std::string string2;
							char buf2[256] = { 0 }; sprintf_s(buf, xorstr_("[%dHP]"), (int)health);
							string2 += buf2;
				
							
								g_Render->DrawString(screenPos.x, screenPos.y, ImColor(0, 0, 255), render2::outline | render2::centered_x, Cuniaabyser, 11, string.c_str());
								g_Render->DrawString(screenPos.x, screenPos.y + 15, ImColor(128, 128, 128), render2::outline | render2::centered_x, Cuniaabyser, 11, string2.c_str());
							
							
							//	g_Render->DrawString(screenPos.x, screenPos.y, ImColor(0, 0, 255), render2::outline | render2::centered_x, Cuniaabyser, 11, string.c_str());
							//	g_Render->DrawString(screenPos.x, screenPos.y + 15, ImColor(128, 128, 128), render2::outline | render2::centered_x, Cuniaabyser, 11, string2.c_str());


							g_Render->FilledRect(screenPos.x - 30, screenPos.y + 20, 60, 6, ImColor(0, 0, 0), 0, 0);
							g_Render->FilledRect(screenPos.x - 30, screenPos.y + 20, 60 * (health / maxhealth), 6, ImColor(0, 255, 0), 0, 0);
							g_Render->Rect(screenPos.x - 30, screenPos.y + 20, 60, 6, ImColor(0, 0, 0), 0, 0);
						}
						if (health > 0 && !vars::combat::ignore_heli) {
							if ((FOV > (CurFOV = GetFovHeli(pos)))) {
								FOV = CurFOV; vars::stor::closestHeli = (uintptr_t)helicopter;
							}
						}
					}
				}
			}
			otherEsp::bradley(ObjectClass, Entity, buff);
			otherEsp::corpse(ObjectClass, Entity, buff);
			otherEsp::tc(ObjectClass, Entity, buff);
			otherEsp::sleepingbag(ObjectClass, Entity, buff);
			otherEsp::bed(ObjectClass, Entity, buff);
			otherEsp::stash(ObjectClass, Entity, buff);
			otherEsp::hackablecrate(ObjectClass, Entity, buff);
			//otherEsp::world(ObjectClass, Entity, buff);
			if (vars::ores::show_collectables) {
				miscvis(Entity, buff, vars::ores::stone, vars::ores::show_distance, vars::ores::draw_distance, xorstr_("stone-collectable.prefab"), xorstr_(L"Stone Collectable"), ImColor(128, 128, 128));
				miscvis(Entity, buff, vars::ores::sulfur, vars::ores::show_distance, vars::ores::draw_distance, xorstr_("sulfur-collectable.prefab"), xorstr_(L"Sulfur Collectable"), ImColor(255, 215, 0));
				miscvis(Entity, buff, vars::ores::metal, vars::ores::show_distance, vars::ores::draw_distance, xorstr_("metal-collectable.prefab"), xorstr_(L"Metal Collectable"), ImColor(139, 69, 19));
			}
			// ---------------------------------------------------------
			miscvis(Entity, buff, vars::ores::stone, vars::ores::show_distance, vars::ores::draw_distance, xorstr_("stone-ore.prefab"), xorstr_(L"Stone Ore"), ImColor(128, 128, 128));
			miscvis(Entity, buff, vars::ores::sulfur, vars::ores::show_distance, vars::ores::draw_distance, xorstr_("sulfur-ore.prefab"), xorstr_(L"Sulfur Ore"), ImColor(255, 215, 0));
			miscvis(Entity, buff, vars::ores::metal, vars::ores::show_distance, vars::ores::draw_distance, xorstr_("metal-ore.prefab"), xorstr_(L"Metal Ore"), ImColor(139, 69, 19));
			// ---------------------------------------------------------
			miscvis(Entity, buff, vars::visuals::crates::elite, vars::visuals::crates::show_distance, vars::visuals::crates::draw_distance, xorstr_("crate_elite.prefab"), xorstr_(L"Elite Crate"), ImColor(46, 139, 87));
			miscvis(Entity, buff, vars::visuals::crates::military, vars::visuals::crates::show_distance, vars::visuals::crates::draw_distance, xorstr_("crate_normal.prefab"), xorstr_(L"Military Crate"), ImColor(1, 68, 33));
			miscvis(Entity, buff, vars::visuals::crates::supply, vars::visuals::crates::show_distance, vars::visuals::crates::draw_distance, xorstr_("supply_drop.prefab"), xorstr_(L"Airdrop"), ImColor(0, 139, 139));
			miscvis(Entity, buff, vars::visuals::crates::heli, vars::visuals::crates::show_distance, vars::visuals::crates::draw_distance, xorstr_("heli_crate.prefab"), xorstr_(L"Heli Crate"), ImColor(1, 50, 32));
			miscvis(Entity, buff, vars::visuals::crates::bradley, vars::visuals::crates::show_distance, vars::visuals::crates::draw_distance, xorstr_("bradley_crate.prefab"), xorstr_(L"Bradley Crate"), ImColor(173, 255, 47));
			// ---------------------------------------------------------
			miscvis(Entity, buff, vars::visuals::vehicles::minicopter, vars::visuals::vehicles::show_distance, vars::visuals::vehicles::draw_distance, xorstr_("minicopter.entity.prefab"), xorstr_(L"Minicopter"), ImColor(0, 0, 255));
			miscvis(Entity, buff, vars::visuals::vehicles::scrapheli, vars::visuals::vehicles::show_distance, vars::visuals::vehicles::draw_distance, xorstr_("scraptransporthelicopter.prefab"), xorstr_(L"Scrap Heli"), ImColor(0, 0, 139));
			miscvis(Entity, buff, vars::visuals::vehicles::boat, vars::visuals::vehicles::show_distance, vars::visuals::vehicles::draw_distance, xorstr_("rowboat.prefab"), xorstr_(L"Boat"), ImColor(173, 216, 230));
			miscvis(Entity, buff, vars::visuals::vehicles::rhib, vars::visuals::vehicles::show_distance, vars::visuals::vehicles::draw_distance, xorstr_("rhib.prefab"), xorstr_(L"RHIB"), ImColor(224, 255, 255));
			// ---------------------------------------------------------
			miscvis(Entity, buff, vars::visuals::turrets::auto_turret, vars::visuals::turrets::show_distance, vars::visuals::turrets::draw_distance, xorstr_("autoturret_deployed.prefab"), xorstr_(L"Auto Turret"), ImColor(255, 165, 0));
			miscvis(Entity, buff, vars::visuals::turrets::flame_turret, vars::visuals::turrets::show_distance, vars::visuals::turrets::draw_distance, xorstr_("flameturret.deployed.prefab"), xorstr_(L"Flame Turret"), ImColor(255, 140, 0));
			miscvis(Entity, buff, vars::visuals::turrets::shotgun_turret, vars::visuals::turrets::show_distance, vars::visuals::turrets::draw_distance, xorstr_("guntrap.deployed.prefab"), xorstr_(L"Shotgun Trap"), ImColor(105, 105, 105));
			miscvis(Entity, buff, vars::visuals::turrets::landmine, vars::visuals::turrets::show_distance, vars::visuals::turrets::draw_distance, xorstr_("landmine.prefab"), xorstr_(L"Landmine"), ImColor(138, 43, 226));
			miscvis(Entity, buff, vars::visuals::turrets::sam_site, vars::visuals::turrets::show_distance, vars::visuals::turrets::draw_distance, xorstr_("sam_site_turret_deployed.prefab"), xorstr_(L"SAM Site"), ImColor(176, 224, 230));
			miscvis(Entity, buff, vars::visuals::turrets::bear_trap, vars::visuals::turrets::show_distance, vars::visuals::turrets::draw_distance, xorstr_("beartrap.prefab"), xorstr_(L"Beartrap"), ImColor(255, 248, 220));
			// ---------------------------------------------------------
			miscvis(Entity, buff, vars::visuals::other::hemp, vars::visuals::other::show_distance, vars::visuals::other::draw_distance, xorstr_("hemp-collectable.prefab"), xorstr_(L"Hemp"), ImColor(50, 205, 50));
			miscvis(Entity, buff, vars::visuals::other::dropped_items, vars::visuals::other::show_distance, vars::visuals::other::draw_distance, "rifle.ak", L"AK-47 Rifle", ImColor(255, 165, 0));
			miscvis(Entity, buff, vars::visuals::other::dropped_items, vars::visuals::other::show_distance, vars::visuals::other::draw_distance, "rifle.lr300", L"LR300 Rifle", ImColor(255, 165, 0));
			miscvis(Entity, buff, vars::visuals::other::dropped_items, vars::visuals::other::show_distance, vars::visuals::other::draw_distance, "rifle.l96", L"L96 Sniper", ImColor(255, 165, 0));
			miscvis(Entity, buff, vars::visuals::other::dropped_items, vars::visuals::other::show_distance, vars::visuals::other::draw_distance, "rifle.m39", L"M39 Rifle", ImColor(255, 165, 0));
			miscvis(Entity, buff, vars::visuals::other::dropped_items, vars::visuals::other::show_distance, vars::visuals::other::draw_distance, "pistol.prototype17", L"Prototype 17", ImColor(255, 165, 0));
			miscvis(Entity, buff, vars::visuals::other::dropped_items, vars::visuals::other::show_distance, vars::visuals::other::draw_distance, "bow.compound	", L"Bow Compound", ImColor(255, 165, 0));
			miscvis(Entity, buff, vars::visuals::other::dropped_items, vars::visuals::other::show_distance, vars::visuals::other::draw_distance, "rifle.semiauto", L"Semi Auto Rifle", ImColor(255, 165, 0));
			miscvis(Entity, buff, vars::visuals::other::dropped_items, vars::visuals::other::show_distance, vars::visuals::other::draw_distance, "smg.mp5", L"MP5 SMG", ImColor(255, 165, 0));
			miscvis(Entity, buff, vars::visuals::other::dropped_items, vars::visuals::other::show_distance, vars::visuals::other::draw_distance, "smg.2", L"SMG Auto", ImColor(255, 165, 0));
			miscvis(Entity, buff, vars::visuals::other::dropped_items, vars::visuals::other::show_distance, vars::visuals::other::draw_distance, "smg.thompson", L"Smg Thompson", ImColor(255, 165, 0));
			miscvis(Entity, buff, vars::visuals::other::dropped_items, vars::visuals::other::show_distance, vars::visuals::other::draw_distance, "pistol.nailgun", L"Nailgun Pistol", ImColor(255, 165, 0));
			miscvis(Entity, buff, vars::visuals::other::dropped_items, vars::visuals::other::show_distance, vars::visuals::other::draw_distance, "pistol.eoka", L"EOKA Pistol", ImColor(255, 165, 0));
			miscvis(Entity, buff, vars::visuals::other::dropped_items, vars::visuals::other::show_distance, vars::visuals::other::draw_distance, "pistol.m92", L"M92 Pistol", ImColor(255, 165, 0));
			miscvis(Entity, buff, vars::visuals::other::dropped_items, vars::visuals::other::show_distance, vars::visuals::other::draw_distance, "pistol.python", L"Python Pistol", ImColor(255, 165, 0));
			miscvis(Entity, buff, vars::visuals::other::dropped_items, vars::visuals::other::show_distance, vars::visuals::other::draw_distance, "pistol.revolver", L"Revolver Pistol", ImColor(255, 165, 0));
			miscvis(Entity, buff, vars::visuals::other::dropped_items, vars::visuals::other::show_distance, vars::visuals::other::draw_distance, "pistol.semiauto", L"Semi Auto Pistol", ImColor(255, 165, 0));
			miscvis(Entity, buff, vars::visuals::other::dropped_items, vars::visuals::other::show_distance, vars::visuals::other::draw_distance, "shotgun.pump", L"Shotgun Pump", ImColor(255, 165, 0));
			miscvis(Entity, buff, vars::visuals::other::dropped_items, vars::visuals::other::show_distance, vars::visuals::other::draw_distance, "shotgun.double", L"Double Shotgun", ImColor(255, 165, 0));
			miscvis(Entity, buff, vars::visuals::other::dropped_items, vars::visuals::other::show_distance, vars::visuals::other::draw_distance, "grenade.f1", L"F1 Grenade", ImColor(255, 165, 0));
			miscvis(Entity, buff, vars::visuals::other::dropped_items, vars::visuals::other::show_distance, vars::visuals::other::draw_distance, "multiplegrenadelauncher", L"Multiple Grenade Launcher", ImColor(255, 165, 0));
			miscvis(Entity, buff, vars::visuals::other::dropped_items, vars::visuals::other::show_distance, vars::visuals::other::draw_distance, "bow.compound", L"Compound Bow", ImColor(255, 165, 0));
			miscvis(Entity, buff, vars::visuals::other::dropped_items, vars::visuals::other::show_distance, vars::visuals::other::draw_distance, "crossbow", L"Crossbow", ImColor(255, 165, 0));
			miscvis(Entity, buff, vars::visuals::other::dropped_items, vars::visuals::other::show_distance, vars::visuals::other::draw_distance, "bow.hunting", L"Bow", ImColor(255, 165, 0));
			miscvis(Entity, buff, vars::visuals::other::dropped_items, vars::visuals::other::show_distance, vars::visuals::other::draw_distance, "hmlmg", L"HMLMG", ImColor(255, 165, 0));
			miscvis(Entity, buff, vars::visuals::other::dropped_items, vars::visuals::other::show_distance, vars::visuals::other::draw_distance, "spear.stone", L"Spear Stone", ImColor(255, 165, 0));
			miscvis(Entity, buff, vars::visuals::other::dropped_items, vars::visuals::other::show_distance, vars::visuals::other::draw_distance, "spear.wooden", L"Spear Wooden", ImColor(255, 165, 0));
			miscvis(Entity, buff, vars::visuals::other::dropped_items, vars::visuals::other::show_distance, vars::visuals::other::draw_distance, "shotgun.double", L"Double Shotgun", ImColor(255, 165, 0));
			miscvis(Entity, buff, vars::visuals::other::dropped_items, vars::visuals::other::show_distance, vars::visuals::other::draw_distance, "ammo.nailgun.nails", L"Nailgun Nails", ImColor(255, 165, 0));
			miscvis(Entity, buff, vars::visuals::other::dropped_items, vars::visuals::other::show_distance, vars::visuals::other::draw_distance, "arrow.hv", L"Arrow Hv", ImColor(255, 165, 0));
			miscvis(Entity, buff, vars::visuals::other::dropped_items, vars::visuals::other::show_distance, vars::visuals::other::draw_distance, "arrow.bone", L"Arrow Bone", ImColor(255, 165, 0));
			miscvis(Entity, buff, vars::visuals::other::dropped_items, vars::visuals::other::show_distance, vars::visuals::other::draw_distance, "arrow.fire", L"Arrow Fire", ImColor(255, 165, 0));
			miscvis(Entity, buff, vars::visuals::other::dropped_items, vars::visuals::other::show_distance, vars::visuals::other::draw_distance, "arrow.wooden", L"Arrow wooden", ImColor(255, 165, 0));
			miscvis(Entity, buff, vars::visuals::other::bodybag, vars::visuals::other::show_distance, vars::visuals::other::draw_distance, xorstr_("item_drop_backpack.prefab"), xorstr_(L"Bodybag"), ImColor(139, 0, 139));
			// ---------------------------------------------------------
			miscvis(Entity, buff, vars::visuals::base::boxes, vars::visuals::base::show_distance, vars::visuals::base::draw_distance, xorstr_("box.wooden.large.prefab"), xorstr_(L"Box"), ImColor(188, 143, 143));
			// ---------------------------------------------------------
			miscvis(Entity, buff, vars::visuals::animals::bear, vars::visuals::animals::show_distance, vars::visuals::animals::draw_distance, xorstr_("bear.prefab"), xorstr_(L"Bear"), ImColor(139, 69, 19));
			miscvis(Entity, buff, vars::visuals::animals::wolf, vars::visuals::animals::show_distance, vars::visuals::animals::draw_distance, xorstr_("wolf.prefab"), xorstr_(L"Wolf"), ImColor(119, 136, 153));
			miscvis(Entity, buff, vars::visuals::animals::pig, vars::visuals::animals::show_distance, vars::visuals::animals::draw_distance, xorstr_("boar.prefab"), xorstr_(L"Pig"), ImColor(255, 136, 77));
			miscvis(Entity, buff, vars::visuals::animals::chicken, vars::visuals::animals::show_distance, vars::visuals::animals::draw_distance, xorstr_("chicken.prefab"), xorstr_(L"Chicken"), ImColor(173, 255, 47));
			miscvis(Entity, buff, vars::visuals::animals::deer, vars::visuals::animals::show_distance, vars::visuals::animals::draw_distance, xorstr_("horse.prefab"), xorstr_(L"Horse"), ImColor(244, 164, 96));
		}
		BasePlayer* TargetPlayer = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer);

		/*targeting shit*/
		if (TargetPlayer) {
		/*	if (TargetPlayer->GetBoneByID(head).x == 0 || TargetPlayer->GetBoneByID(head).y == 0 || TargetPlayer->GetBoneByID(head).z == 0) {
				vars::stor::closestPlayer = NULL;
			}*/
			if (TargetPlayer->IsNpc() && !vars::visuals::NpcEspEnable) {
				vars::stor::closestPlayer = NULL;
			}
			if (TargetPlayer->get_flag(PlayerFlags::Sleeping) && vars::combat::ignore_sleepers) {
				vars::stor::closestPlayer = NULL;
			}
			if (LocalPlayer::Entity()->is_teammate(TargetPlayer) && vars::combat::ignore_team) {
				vars::stor::closestPlayer = NULL;
			}
			if (TargetPlayer->health() <= 0) {
				vars::combat::lock_target = false;
				vars::stor::closestPlayer = NULL;
			}
			//if (vars::combat::ignore_invisible && !TargetPlayer->is_visible()) {
			//	vars::stor::closestPlayer = NULL;
			//}
		}
		if (vars::stor::closestPlayer == NULL) {
			vars::combat::lock_target = false;
		}
		if (vars::stor::closestHeli != NULL) {
			if (reinterpret_cast<BaseEntity*>(vars::stor::closestHeli)->IsDestroyed()) {
				vars::stor::closestHeli = NULL;
			}
			if (!reinterpret_cast<Component*>(vars::stor::closestHeli)->gameObject()) {
				vars::stor::closestHeli = NULL;
			}
		}
		if (vars::combat::ignore_players) {
			vars::stor::closestPlayer = NULL;
		}
		if (vars::combat::ignore_heli) {
			vars::stor::closestHeli = NULL;
		}
		Item* ActWeapon = LocalPlayer::Entity()->GetActiveWeapon();
		if (LocalPlayer::Entity() != nullptr && ActWeapon) {
			if (vars::combat::aimbot && !LocalPlayer::Entity()->is_teammate(reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer))) {
				if (vars::stor::closestPlayer) {
					if (GetAsyncKeyState(vars::keys::aimkey)) {
						do_aimbot(reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer));
					}
				}
			
		}
	}
}