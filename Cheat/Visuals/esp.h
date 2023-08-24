#pragma warning(disable : 4530)
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <dwmapi.h>
#include <d3d11.h>
#include <stdio.h>
#include <chrono>
#include <psapi.h>
#include <string>
#include <cstringt.h>
#include <atlstr.h>
#include <array>
#include <stdlib.h>
#include <math.h>
#include "winternl.h"
#include "time.h"
#include <map>
#include <cstdint>
#include <stdint.h>
#include <emmintrin.h>
#include <sstream>
#include <cstringt.h>
#include <atlstr.h>



Vector2 CosTanSinLineH(float flAngle, float range, int x, int y, int LineLength) {
	float oxunem = flAngle;
	oxunem += 45.f;

	float flYaw = (oxunem) * (PI / 180.0);

	float viewcosyawzzzzzzz = cos(flYaw);
	float viewsinyawzzzzzzz = sin(flYaw);

	float x2 = range * (-viewcosyawzzzzzzz) + range * viewsinyawzzzzzzz;
	float y2 = range * (-viewcosyawzzzzzzz) - range * viewsinyawzzzzzzz;

	int posonscreenX = x + int(x2 / range * (LineLength));
	int posonscreenY = y + int(y2 / range * (LineLength));

	return Vector2(posonscreenX, posonscreenY);
}
void CosTanSinLine(float flAngle, float range, int x, int y, int LineLength, const ImColor Clr, bool oof = false, bool outline = false) {
	float nigga = flAngle;
	nigga += 45.f;

	float flYaw = (nigga) * (PI / 180.0);

	float viewcosyawzzzzzzz = cos(flYaw);
	float viewsinyawzzzzzzz = sin(flYaw);

	float x2 = range * (-viewcosyawzzzzzzz) + range * viewsinyawzzzzzzz;
	float y2 = range * (-viewcosyawzzzzzzz) - range * viewsinyawzzzzzzz;

	int posonscreenX = x + int(x2 / range * (LineLength));
	int posonscreenY = y + int(y2 / range * (LineLength));
	Vector2 tp0 = CosTanSinLineH(flAngle, range, x, y, LineLength / 1.3);
	//Vector2 tp1 = CosTanSinLineH(angleYawRad, 5.f, vars::stuff::ScreenWidth / 2, vars::stuff::ScreenHeight / 2, 270.f);
	if (!oof) {
		g_Render->DrawLine(x, y, posonscreenX, posonscreenY, Clr, 1.5f, true);
		//Line(Vector2(x, y), Vector2(posonscreenX, posonscreenY), Clr);
	}
	else {
		g_Render->DrawLine(tp0.x, tp0.y, posonscreenX, posonscreenY, Clr, 1.5f, true);
		//Line(CosTanSinLineH(flAngle, range, x, y, LineLength / 1.3), Vector2(posonscreenX, posonscreenY), Clr, 1.5f);
		if (outline) {
			g_Render->DrawLine(tp0.x, tp0.y, posonscreenX, posonscreenY, Clr, 1.5f, true);
		//	Line(CosTanSinLineH(flAngle, range, x, y, LineLength / 1.3), Vector2(posonscreenX, posonscreenY), Clr, 1.5f, true);
		}
	}
	if (outline) {
		g_Render->CircleFilled(posonscreenX, posonscreenY, 5.35f, Clr, 0);
		//g_Render->AddCircleFilled({ posonscreenX, posonscreenY }, ImColor(0, 255, 0), 35ff);
	//	g_Render->FilledRect(posonscreenX - 10, posonscreenY - 10, posonscreenX + 10, posonscreenY +  10, Clr, 10, 0);
	//	g_Render->Rect(posonscreenX - 10, posonscreenY - 10, posonscreenX + 10, posonscreenY + 10, _color, 10, 0);
	//	FillCircle(Vector2(posonscreenX, posonscreenY), D2D1::ColorF::Black, 5.35f);
	}
	g_Render->CircleFilled(posonscreenX, posonscreenY, 4.f, Clr, 0);
//	FillCircle(Vector2(posonscreenX, posonscreenY), Clr, 4);//P.S this is the small dot at the end of each line!!!!!!!!!XD
}
#include <cstringt.h>
#include <atlstr.h>
namespace radar {
	void radar_bg() {
		float mid_x = vars::visuals::radar::x + vars::visuals::radar::size / 2;
		float mid_y = vars::visuals::radar::y + vars::visuals::radar::size / 2;
		POINT p;
		if (GetCursorPos(&p)) {
			if (p.x >= mid_x - vars::visuals::radar::size && p.x <= mid_x + vars::visuals::radar::size) {
				if (p.y >= mid_y - vars::visuals::radar::size && p.y <= mid_y + vars::visuals::radar::size) {
					if (GetAsyncKeyState(VK_LBUTTON) && show) {
						vars::visuals::radar::x = p.x - (vars::visuals::radar::size / 2);
						vars::visuals::radar::y = p.y - (vars::visuals::radar::size / 2);
					}
				}
			}
		}
		g_Render->CircleFilled(mid_x, mid_y, vars::visuals::radar::size, ImColor(50, 50, 50), 0);
	//	Renderer::FillCircle(Vector2(mid_x, mid_y), D2D1::ColorF(0.06f, 0.06f, 0.06f, 0.94f), vars::visuals::radar::size);
	//	Renderer::Circle(Vector2(mid_x, mid_y), D2D1::ColorF(0.43f, 0.43f, 0.50f, 0.50f), vars::visuals::radar::size);

		//Renderer::Circle(Vector2(mid_x, mid_y), D2D1::ColorF::Red, 2.5f);
		//Renderer::Triangle(Vector2(mid_x, mid_y), D2D1::ColorF::Red, 3.5f);
	}
	void radar_logic(DWORD64 ObjectClass, DWORD64 Object, char* buff) {
		float mid_x = vars::visuals::radar::x + vars::visuals::radar::size / 2;
		float mid_y = vars::visuals::radar::y + vars::visuals::radar::size / 2;
		if (LocalPlayer::Entity()) {
			Vector3 local = LocalPlayer::Entity()->GetBoneByID(head);
			if (strstr(buff, ("player.prefab")) || strstr(buff, ("scientist")) && !strstr(buff, ("prop")) && !strstr(buff, ("corpse"))) {
				BasePlayer* Player = (BasePlayer*)Object;
				//	if (!Player->isCached()) return;

				Vector3 ply = Player->GetBoneByID(head);
				float dist = Math::Distance_3D(local, ply);
				float y = local.x - ply.x;
				float x = local.z - ply.z;

				Vector3 eulerAngles = Math::EulerAngles(LocalPlayer::Entity()->eyes()->rotation()/*pViewMatrix->GetRotation()*/);
				float num = atan2(y, x) * 57.29578f - 270.f - eulerAngles.y;
				float PointPos_X = dist * cos(num * 0.0174532924f);
				float PointPos_Y = dist * sin(num * 0.0174532924f);
				PointPos_X = PointPos_X * (vars::visuals::radar::size / vars::visuals::radar::range) / 2.f;
				PointPos_Y = PointPos_Y * (vars::visuals::radar::size / vars::visuals::radar::range) / 2.f;

				Vector2 point = Vector2(vars::visuals::radar::x + vars::visuals::radar::size / 2.f + PointPos_X, vars::visuals::radar::y + vars::visuals::radar::size / 2.f + PointPos_Y);

				if (Math::Distance_2D(point, Vector2(mid_x, mid_y)) < vars::visuals::radar::size) {
					if (!Player->IsNpc()) {
						if (!Player->get_flag(PlayerFlags::Sleeping)) {
							if (LocalPlayer::Entity()->is_teammate(Player)) {
								g_Render->CircleFilled(point.x, point.y, 2.5f, ImColor(190, 0, 0), 0);
								//	Renderer::FillCircle(point, D2D1::ColorF::Lime, 2.5f);
							}
							else {
								if (Player->health() <= 0) {
									g_Render->CircleFilled(point.x, point.y, 2.5f, ImColor(190, 0, 0), 0);
									//	Renderer::FillCircle(point, D2D1::ColorF::Red, 2.5f);
								}
								else {
									g_Render->CircleFilled(point.x, point.y, 2.5f, ImColor(50, 50, 50), 0);
									//	Renderer::FillCircle(point, D2D1::ColorF::DarkGray, 2.5f);

								}
							}
						}
						//	else if (Player->HasFlags(PlayerFlags::Sleeping) && !vars::players::sleeperignore) {
						//		g_Render->CircleFilled(point.x, point.y, 2.5f, Clr, 0);
						//	//	Renderer::FillCircle(point, D2D1::ColorF::Orange, 2.5f);
						//	}
						//}
						//else if (Player->IsNpc() && (vars::npc::box || vars::npc::name || vars::npc::tracers || vars::npc::healthbar)) {
						//	g_Render->CircleFilled(point.x, point.y, 2.5f, Clr, 0);
						////	Renderer::FillCircle(point, D2D1::ColorF::Yellow, 2.5f);
						//}
					}
				}
			}
		}
	}
}
namespace otherEsp {
	void miscvis(DWORD64 ObjectClass, char* buff, bool boolean, bool showDistance, float drawDistance, const char* substring, const wchar_t* targettext, ImColor color) {
		if (boolean) {
			if (strstr(buff, substring)) {

				Vector2 screen_Pos;
				if (ObjectClass) {

				
					if (utils::w2s(reinterpret_cast<BaseEntity*>(ObjectClass)->transform()->position()/*utils::GetEntityPosition(gameObject)*/, screen_Pos)) {
						if ((int)Math::Distance_3D(LocalPlayer::Entity()->GetBoneByID(head), reinterpret_cast<BaseEntity*>(ObjectClass)->transform()->position()) <= drawDistance) {
							std::string string;
							char buf[256] = { 0 }; sprintf_s(buf, "%ls", targettext);
							string = buf;

							g_Render->DrawString(screen_Pos.x, screen_Pos.y, color, render2::outline | render2::centered_x, Cuniaabyser, 12, string.c_str());
							if (showDistance) {
								std::string string2;
								char buf2[256] = { 0 }; sprintf_s(buf2, "%.1fm", Math::Distance_3D(LocalPlayer::Entity()->GetBoneByID(head), reinterpret_cast<BaseEntity*>(ObjectClass)->transform()->position()));
								string2 = buf2;
								//	DrawList->AddText({ screen_Pos.x - (ImGui::CalcTextSize(string.c_str()).x / 2),screen_Pos.y + 15 }, color, string.c_str());
								g_Render->DrawString(screen_Pos.x, screen_Pos.y + 10, ImColor(128, 128, 128), render2::outline | render2::centered_x, Cuniaabyser, vars::misc::fotsize, string2.c_str());
							}
						
						}
					}
				}
			}
		}
	}
	void bradley(DWORD64 ObjectClass, DWORD64 Object, char* buff) {
		if (vars::visuals::bradley_apc) {
			if (strstr(buff, xorstr_("bradleyapc.prefab"))) {

				BaseCombatEntity* bradley = (BaseCombatEntity*)Object;
				if (bradley) {
					Vector3 pos = bradley->transform()->position();/*utils::GetEntityPosition(object);*/
					int distance = Math::Distance_3D(LocalPlayer::Entity()->GetBoneByID(head), pos);
					float health = bradley->health();
					Vector2 screen;
					if (utils::w2s(pos, screen)) {
						if (health > 0) {
							std::string string;
							char buf[256] = { 0 }; sprintf_s(buf, "Bradley APC [%dm]", (int)Math::Distance_3D(LocalPlayer::Entity()->GetBoneByID(head), pos));
							string = buf;
							g_Render->DrawString(screen.x, screen.y, ImColor(255, 0, 0, 255), render2::outline | render2::centered_x, Cuniaabyser, vars::misc::fotsize, string.c_str());

							g_Render->FilledRect(screen.x - 30, screen.y - 15, 60, 6, ImColor(0, 0, 0), 0, 0);
							g_Render->FilledRect(screen.x - 30, screen.y - 15, 60 * (health / 1000.f), 6, ImColor(0, 255, 0), 0, 0);
							g_Render->Rect(screen.x - 30, screen.y - 15, 60, 6, ImColor(0, 0, 0), 0, 0);
						}
					}
				}
			}
		}
	}
	void corpse(DWORD64 ObjectClass, DWORD64 Object, char* buff) {
		if (vars::visuals::other::corpse) {
			if (strstr(buff, xorstr_("player_corpse.prefab"))) {

				BaseEntity* corpse = (BaseEntity*)Object;
				if (corpse) {
					Vector3 pos = corpse->transform()->position();
					float distance = Math::Distance_3D(LocalPlayer::Entity()->GetBoneByID(head), pos);
					Vector2 screen;
					if (utils::w2s(pos, screen) && distance <= vars::visuals::other::draw_distance) {
						g_Render->DrawString(screen.x, screen.y, ImColor(255, 0, 0, 255), render2::outline | render2::centered_x, Cuniaabyser, vars::misc::fotsize, xorstr_("Corpse"));
						if (vars::visuals::other::show_distance) {
							std::string string2;
							char buf2[256] = { 0 }; sprintf_s(buf2, "%.1fm", distance);
							string2 = buf2;
							g_Render->DrawString(screen.x, screen.y + 10, ImColor(128, 128, 128), render2::outline | render2::centered_x, Cuniaabyser, vars::misc::fotsize, string2.c_str());

						}
					}
				}
			}
		}
	}
	void tc(DWORD64 ObjectClass, DWORD64 Object, char* buff) {
		if (vars::visuals::base::tc) {
			if (strstr(buff, xorstr_("cupboard.tool.deployed.prefab"))) {

				BaseEntity* cupboard = (BaseEntity*)Object;
				if (cupboard) {
					Vector3 pos = cupboard->transform()->position();
					float distance = Math::Distance_3D(LocalPlayer::Entity()->GetBoneByID(head), pos);
					Vector2 screen;
					if (utils::w2s(pos, screen) && distance <= vars::visuals::base::draw_distance) {
						int pos = 15;
						int upkeep = read(cupboard + 0x588, float); // private float cachedProtectedMinutes;
						std::string string;
						char buf[256] = { 0 }; sprintf_s(buf, "Tool Cupboard | %d hours", upkeep / 60);
						string = buf;
						g_Render->DrawString(screen.x, screen.y, ImColor(0, 255, 0, 255), render2::outline | render2::centered_x, Cuniaabyser, vars::misc::fotsize, string.c_str());

						if (vars::visuals::base::show_distance) {
							std::string string2;
							char buf2[256] = { 0 }; sprintf_s(buf2, "%.1fm", distance);
							string2 = buf2;

							g_Render->DrawString(screen.x, screen.y + 10, ImColor(128, 128, 128), render2::outline | render2::centered_x, Cuniaabyser, vars::misc::fotsize, string2.c_str());

							pos += 15;
						}
						//uintptr_t authedPly = read(cupboard + 0x598, uintptr_t); // public List<PlayerNameID> authorizedPlayers; || public class BuildingPrivlidge : StorageContainer
						//List<PlayerNameID*>* authedPly_list = read(authedPly + 0x10, List<PlayerNameID*>*);
						//authedPly_list->for_each([&](PlayerNameID* authorizedPlayer, int32_t idx) {
						//	if (authorizedPlayer) {
						//		auto user = authorizedPlayer->username();
						//		Renderer::Text(screen + Vector2(0, pos), D2D1::ColorF::YellowGreen, true, true, user);
						//		pos += 15;
						//	}
						//	});
					}
				}
			}
		}
	}
	void sleepingbag(DWORD64 ObjectClass, DWORD64 Object, char* buff) {
		if (vars::visuals::base::sleeping_bag) {
			if (strstr(buff, xorstr_("sleepingbag_leather_deployed.prefab"))) {

				BaseEntity* bag = (BaseEntity*)Object;
				if (bag) {
					Vector3 pos = bag->transform()->position();
					float distance = Math::Distance_3D(LocalPlayer::Entity()->GetBoneByID(head), pos);
					Vector2 screen;
					if (utils::w2s(pos, screen) && distance <= vars::visuals::base::draw_distance) {
						g_Render->DrawString(screen.x, screen.y, ImColor(128, 128, 0), render2::outline | render2::centered_x, Cuniaabyser, vars::misc::fotsize, xorstr_("Sleeping Bag"));
						if (vars::visuals::base::show_distance) {
							std::string string2;
							char buf2[256] = { 0 }; sprintf_s(buf2, "%.1fm", distance);
							string2 = buf2;
							g_Render->DrawString(screen.x, screen.y + 10, ImColor(128, 128, 128), render2::outline | render2::centered_x, Cuniaabyser, vars::misc::fotsize, string2.c_str());
						}
					}
				}
			}
		}
	}
	void bed(DWORD64 ObjectClass, DWORD64 Object, char* buff) {
		if (vars::visuals::base::bed) {
			if (strstr(buff, xorstr_("bed_deployed.prefab"))) {

				BaseEntity* bag = (BaseEntity*)Object;
				if (bag) {
					Vector3 pos = bag->transform()->position();
					float distance = Math::Distance_3D(LocalPlayer::Entity()->GetBoneByID(head), pos);
					Vector2 screen;
					if (utils::w2s(pos, screen) && distance <= vars::visuals::base::draw_distance) {
						g_Render->DrawString(screen.x, screen.y, ImColor(107, 142, 35), render2::outline | render2::centered_x, Cuniaabyser, vars::misc::fotsize, xorstr_("Bed"));
						if (vars::visuals::base::show_distance) {
							std::string string2;
							char buf2[256] = { 0 }; sprintf_s(buf2, "%.1fm", distance);
							string2 = buf2;
							g_Render->DrawString(screen.x, screen.y + 10, ImColor(128, 128, 128), render2::outline | render2::centered_x, Cuniaabyser, vars::misc::fotsize, string2.c_str());
						}
					}
				}
			}
		}
	}
	void stash(DWORD64 ObjectClass, DWORD64 Object, char* buff) {
		typedef bool(__stdcall* IsHidden)(BaseEntity*);
		if (vars::visuals::other::stash) {
			if (strstr(buff, xorstr_("small_stash_deployed.prefab"))) {

				BaseEntity* stash = (BaseEntity*)Object;
				if (stash) {
					Vector3 pos = stash->transform()->position();
					float distance = Math::Distance_3D(LocalPlayer::Entity()->GetBoneByID(head), pos);
					Vector2 screen;
					if (utils::w2s(pos, screen) && distance <= vars::visuals::other::draw_distance) {

						if (((IsHidden)(vars::stor::gBase + CO::IsHidden))(stash)) {
							g_Render->DrawString(screen.x, screen.y, ImColor(255, 0, 0), render2::outline | render2::centered_x, Cuniaabyser, vars::misc::fotsize, xorstr_("Stash [Hidden]"));

						}
						else {

							g_Render->DrawString(screen.x, screen.y, ImColor(255, 255, 0), render2::outline | render2::centered_x, Cuniaabyser, vars::misc::fotsize, xorstr_("Stash [Open]"));

						}
						if (vars::visuals::other::show_distance) {
							std::string string;
							char buf[256] = { 0 }; sprintf_s(buf, "%.1fm", distance);
							string = buf;
							g_Render->DrawString(screen.x, screen.y + 10, ImColor(128, 128, 128), render2::outline | render2::centered_x, Cuniaabyser, vars::misc::fotsize, string.c_str());
						}
					}
				}
			}
		}
	}
	void hackablecrate(DWORD64 ObjectClass, DWORD64 Object, char* buff) {
		typedef bool(__stdcall* IsBeingHacked)(BaseEntity*);
		typedef bool(__stdcall* IsFullyHacked)(BaseEntity*);
		if (vars::visuals::crates::chinook) {
			if (strstr(buff, xorstr_("codelockedhackablecrate.prefab"))) {

				BaseEntity* crate = (BaseEntity*)Object;
				if (crate) {
					Vector3 pos = crate->transform()->position();
					float distance = Math::Distance_3D(LocalPlayer::Entity()->GetBoneByID(head), pos);
					Vector2 screen;
					if (utils::w2s(pos, screen)) {
						uintptr_t timerText = read(crate + 0x470, uintptr_t); // public Text timerText; || public class HackableLockedCrate
						auto* m_Text = reinterpret_cast<pUncStr>(read(timerText + 0xD0, DWORD64));
						ImColor color;

						std::string _name((LPCSTR)CStringA(m_Text->str));
						if (!((IsFullyHacked)(vars::stor::gBase + CO::IsFullyHacked))(crate)) {
							if (((IsBeingHacked)(vars::stor::gBase + CO::IsBeingHacked))(crate)) {
								color = ImColor(250, 250, 210);
								std::string string;
								char buf[256] = { 0 }; sprintf_s(buf, "Chinook Crate | %ls", _name);
								string = buf;
								g_Render->DrawString(screen.x, screen.y, color, render2::outline | render2::centered_x, Cuniaabyser, vars::misc::fotsize, string.c_str());

							}
							else {
								color = ImColor(255, 69, 0);

								g_Render->DrawString(screen.x, screen.y, color, render2::outline | render2::centered_x, Cuniaabyser, vars::misc::fotsize, xorstr_("Chinook Crate"));

							}
						}
						else {
							color = ImColor(32, 178, 170);
							g_Render->DrawString(screen.x, screen.y, color, render2::outline | render2::centered_x, Cuniaabyser, vars::misc::fotsize, xorstr_("Chinook Crate [Open]"));

						}
						std::string string;
						char buf[256] = { 0 }; sprintf_s(buf, "%.1fm", distance);
						string = buf;
						g_Render->DrawString(screen.x, screen.y + 10, ImColor(128, 128, 128), render2::outline | render2::centered_x, Cuniaabyser, vars::misc::fotsize, string.c_str());
					}
				}
			}
		}
	}

	////void world(DWORD64 ObjectClass, DWORD64 Object, char* buff) {
	////	typedef uintptr_t(__stdcall* GetItem)(uintptr_t);
	////	if (vars::visuals::other::dropped_items) {
	////		if (strstr(buff, xorstr_("world"))) {

	////			BaseEntity* item = (BaseEntity*)Object;
	////			if (item) {
	////				Vector3 pos = item->transform()->position();
	////				float distance = Math::Distance_3D(LocalPlayer::Entity()->GetBoneByID(head), pos);
	////				Vector2 screen;
	////				if (utils::w2s(pos, screen) && distance <= vars::visuals::other::draw_distance) {
	////					uintptr_t Item = read(item + 0x170, uintptr_t); // public Item item; || public class WorldItem : BaseEntity
	////					uintptr_t itemDefinition = read(Item + 0x20, uintptr_t);
	////					uintptr_t displayName = read(itemDefinition + 0x28, uintptr_t);
	////					auto* english = reinterpret_cast<pUncStr>(read(displayName + 0x0, DWORD64)); // public static readonly DisplayNameAttribute Default; || private string _displayName;
	////					int amount = read(Item + 0x30, int);

	////					std::wstring eng = std::wstring(english->str);
	////					if (!(eng.find(xorstr_(L"Arrow")) != std::wstring::npos) && !(eng.find(xorstr_(L"Nails")) != std::wstring::npos)) {
	////						std::string string;
	////						char buf[256] = { 0 }; sprintf_s(buf, "%ls", english->str);
	////						string = buf;
	////						g_Render->DrawString(screen.x, screen.y, ImColor(255, 255, 255, 255), render2::outline | render2::centered_x, Cuniaabyser, 12, string.c_str());
	////						if (vars::visuals::other::show_distance) {
	////							std::string string2;
	////							char buf[256] = { 0 }; sprintf_s(buf, "%.1fm", distance);
	////							string2 = buf;

	////							g_Render->DrawString(screen.x, screen.y + 10, ImColor(128, 128, 128), render2::outline | render2::centered_x, Cuniaabyser, 12, string2.c_str());
	////						}
	////					}
	////				}
	////			}
	////		}
	////	}
	////}
}
void Skeleton(BasePlayer* player, ImColor color) {

	auto head_pos = player->GetBoneByID(head);
	auto spine4_pos = player->GetBoneByID(spine4);
	auto l_clavicle_pos = player->GetBoneByID(l_clavicle);
	auto l_upperarm_pos = player->GetBoneByID(l_upperarm);
	auto l_forearm_pos = player->GetBoneByID(l_forearm);
	auto l_hand_pos = player->GetBoneByID(l_hand);
	auto r_clavicle_pos = player->GetBoneByID(r_clavicle);
	auto r_upperarm_pos = player->GetBoneByID(r_upperarm);
	auto r_forearm_pos = player->GetBoneByID(r_forearm);
	auto r_hand_pos = player->GetBoneByID(r_hand);
	auto pelvis_pos = player->GetBoneByID(pelvis);
	auto l_hip_pos = player->GetBoneByID(l_hip);
	auto l_knee_pos = player->GetBoneByID(l_knee);
	auto l_ankle_scale_pos = player->GetBoneByID(l_ankle_scale);
	auto l_foot_pos = player->GetBoneByID(l_foot);
	auto r_hip_pos = player->GetBoneByID(r_hip);
	auto r_knee_pos = player->GetBoneByID(r_knee);
	auto r_ankle_scale_pos = player->GetBoneByID(r_ankle_scale);
	auto r_foot_pos = player->GetBoneByID(r_foot);
	

	Vector2 head, spine, l_clavicle, l_upperarm, l_forearm, l_hand, r_clavicle, r_upperarm, r_forearm, r_hand, pelvis, l_hip, l_knee, l_ankle_scale, l_foot, r_hip, r_knee, r_ankle_scale, r_foot;
	if (utils::w2s(head_pos, head) &&
		utils::w2s(spine4_pos, spine) &&
		utils::w2s(l_clavicle_pos, l_clavicle) &&
		utils::w2s(l_upperarm_pos, l_upperarm) &&
		utils::w2s(l_forearm_pos, l_forearm) &&
		utils::w2s(l_hand_pos, l_hand) &&
		utils::w2s(r_clavicle_pos, r_clavicle) &&
		utils::w2s(r_upperarm_pos, r_upperarm) &&
		utils::w2s(r_forearm_pos, r_forearm) &&
		utils::w2s(r_hand_pos, r_hand) &&
		utils::w2s(pelvis_pos, pelvis) &&
		utils::w2s(l_hip_pos, l_hip) &&
		utils::w2s(l_knee_pos, l_knee) &&
		utils::w2s(l_ankle_scale_pos, l_ankle_scale) &&
		utils::w2s(l_foot_pos, l_foot) &&
		utils::w2s(r_hip_pos, r_hip) &&
		utils::w2s(r_knee_pos, r_knee) &&
		utils::w2s(r_ankle_scale_pos, r_ankle_scale) &&
		utils::w2s(r_foot_pos, r_foot)) {


		

		g_Render->DrawLine(head.x, head.y, spine.x, spine.y, color, 1.5f, true);
		g_Render->DrawLine(spine.x, spine.y, l_upperarm.x, l_upperarm.y, color, 1.5f, true);
		g_Render->DrawLine(l_upperarm.x, l_upperarm.y, l_forearm.x, l_forearm.y, color, 1.5f, true);
		g_Render->DrawLine(l_forearm.x, l_forearm.y, l_hand.x, l_hand.y, color, 1.5f, true);
		g_Render->DrawLine(spine.x, spine.y, r_upperarm.x, r_upperarm.y, color, 1.5f, true);
		g_Render->DrawLine(r_upperarm.x, r_upperarm.y, r_forearm.x, r_forearm.y, color, 1.5f, true);
		g_Render->DrawLine(r_forearm.x, r_forearm.y, r_hand.x, r_hand.y, color, 1.5f, true);
		g_Render->DrawLine(spine.x, spine.y, pelvis.x, pelvis.y, color, 1.5f, true);
		g_Render->DrawLine(pelvis.x, pelvis.y, l_hip.x, l_hip.y, color, 1.5f, true);
		g_Render->DrawLine(l_hip.x, l_hip.y, l_knee.x, l_knee.y, color, 1.5f, true);
		g_Render->DrawLine(l_knee.x, l_knee.y, l_foot.x, l_foot.y, color, 1.5f, true);
		g_Render->DrawLine(pelvis.x, pelvis.y, r_hip.x, r_hip.y, color, 1.5f, true);
		g_Render->DrawLine(r_hip.x, r_hip.y, r_knee.x, r_knee.y, color, 1.5f, true);
		g_Render->DrawLine(r_knee.x, r_knee.y, r_foot.x, r_foot.y, color, 1.5f, true);
	}

}
void CornerBox(float Entity_x, float Entity_y, float Entity_w, float Entity_h, ImColor color) {
	g_Render->DrawLine(Entity_x, Entity_y, Entity_x + Entity_w / 3.5f, Entity_y, color, 1.f, true);
	g_Render->DrawLine(Entity_x, Entity_y, Entity_x, Entity_y + Entity_h / 3.5f, color, 1.f, true);

	g_Render->DrawLine(Entity_x + Entity_w, Entity_y, (Entity_x + Entity_w) - Entity_w / 3.5f, Entity_y, color, 1.f, true);
	g_Render->DrawLine(Entity_x + Entity_w, Entity_y, Entity_x + Entity_w, Entity_y + Entity_h / 3.5f, color, 1.f, true);

	g_Render->DrawLine(Entity_x + Entity_w, Entity_y + Entity_h, (Entity_x + Entity_w) - Entity_w / 3.5f, Entity_y + Entity_h, color, 1.f, true);
	g_Render->DrawLine(Entity_x + Entity_w, Entity_y + Entity_h, Entity_x + Entity_w, (Entity_y + Entity_h) - Entity_h / 3.5f, color, 1.f, true);

	g_Render->DrawLine(Entity_x, Entity_y + Entity_h, Entity_x + Entity_w / 3.5f, Entity_y + Entity_h, color, 1.f, true);

	g_Render->DrawLine(Entity_x, Entity_y + Entity_h, Entity_x, (Entity_y + Entity_h) - Entity_h / 3.5f, color, 1.f, true);
}
void rotate_triangle(std::array<Vector2, 3>& points, float rotation)
{
	const auto pointsCenter = (points.at(0) + points.at(1) + points.at(2)) / 3;
	for (auto& point : points)
	{
		point -= pointsCenter;

		const auto tempX = point.x;
		const auto tempY = point.y;

		const auto theta = DEG2RAD(rotation);
		const auto c = cos(theta);
		const auto s = sin(theta);

		point.x = tempX * c - tempY * s;
		point.y = tempX * s + tempY * c;

		point += pointsCenter;
	}
}
void OOF(BasePlayer* ply, ImColor _color) {
	if (vars::players::sleeperignore && ply->get_flag(PlayerFlags::Sleeping)) return;
	if (!vars::npc::oof_arrows && ply->IsNpc()) return;
	if (!ply) return;
	//	if (!LocalPlayer::Entity()->isCached()) return;

	if (vars::players::oof_arrows) {
		if (utils::OOF(ply)) {
			Vector3 local = LocalPlayer::Entity()->GetBoneByID(head);
			Vector3 cordi = ply->GetBoneByID(head);
			float y = local.x - cordi.x;
			float x = local.z - cordi.z;
			Vector3 eulerAngles = Math::EulerAngles(LocalPlayer::Entity()->eyes()->rotation());
			float angleYawRad = atan2(y, x) * 57.29578f - 180.f - eulerAngles.y;
			Item* ActWeapon = ply->GetActiveWeapon();
			std::string _name(CStringA(ply->_displayName()));
			std::string string;	char buf[256] = { 0 };
			sprintf_s(buf, xorstr_("%ls"), ActWeapon->get_name());
			string += buf;
			std::string string1; char buf1[256] = { 0 };
			sprintf_s(buf1, xorstr_("[ %dm ]"), (int)Math::Distance_3D(LocalPlayer::Entity()->GetBoneByID(head), ply->GetBoneByID(head)));
			string1 += buf1;
			Vector2 tp0 = CosTanSinLineH(angleYawRad, 5.f, vars::stuff::ScreenWidth / 2, vars::stuff::ScreenHeight / 2, 270.f);
			Vector2 tp1 = CosTanSinLineH(angleYawRad + 2.f, 5.f, vars::stuff::ScreenWidth / 2, vars::stuff::ScreenHeight / 2, 260.f);
			Vector2 tp2 = CosTanSinLineH(angleYawRad - 2.f, 5.f, vars::stuff::ScreenWidth / 2, vars::stuff::ScreenHeight / 2, 260.f);
			if (vars::players::Outstyle == 0) {
				g_Render->TriangleFilled(tp0.x, tp0.y, tp1.x, tp1.y, tp2.x, tp2.y, _color);

			}
			if (vars::players::Outstyle == 1) {
				ImGui::GetBackgroundDrawList()->AddTriangle({ tp0.x,tp0.y }, { tp1.x,tp1.y }, { tp2.x,tp2.y }, _color);
	
			}
			if (vars::players::Outstyle == 2) {
				g_Render->FilledRect(tp1.x, tp1.y, 19, 19, _color, 60, 0);//_color
				g_Render->Rect(tp1.x, tp1.y, 20, 20, ImColor(17, 17, 17), 60, 0);
			
			}
			if (vars::players::Outstyle == 3) {

				g_Render->FilledRect(tp1.x, tp1.y, 10, 10, ImColor(17, 17, 17), 10, 0);
				g_Render->Rect(tp1.x, tp1.y, 11, 11, _color, 10, 0);
				g_Render->DrawString(tp1.x + 5, tp1.y - 20.f, _color, render2::centered_x | render2::outline, Verdanabyser, vars::misc::fotsize, _name.c_str());
				g_Render->DrawString(tp1.x + 7, tp1.y + 30.f, _color, render2::centered_x | render2::outline, Verdanabyser, vars::misc::fotsize, string1.c_str());
				if(ActWeapon)
				{ 
				g_Render->DrawString(tp1.x + 7, tp1.y + 20.f, _color, render2::centered_x | render2::outline, Verdanabyser, vars::misc::fotsize, string.c_str());
				}
				else
				{
					g_Render->DrawString(tp1.x + 7, tp1.y + 20.f, _color, render2::centered_x | render2::outline, Verdanabyser, vars::misc::fotsize, "Empty");
				}
				}
	
		}
	}
}
typedef bool(__stdcall* IsDucked)(BasePlayer*);
void Box3D(BasePlayer* player, ImColor color) {
	CBounds bounds = CBounds();
	IsDucked ducked = (IsDucked)(vars::stor::gBase + CO::IsDucked);
	if (ducked(player)) {
		bounds.center = player->GetBoneByID(l_foot).midPoint(player->GetBoneByID(r_foot)) + Vector3(0.0f, 0.55f, 0.0f);
		bounds.extents = Vector3(0.4f, 0.65f, 0.4f);
	}
	else {
		if (player->get_flag(PlayerFlags::Wounded) || player->get_flag(PlayerFlags::Sleeping)) {
			bounds.center = player->GetBoneByID(pelvis);
			bounds.extents = Vector3(0.9f, 0.2f, 0.4f);
		}
		 else {
			bounds.center = player->GetBoneByID(l_foot).midPoint(player->GetBoneByID(r_foot)) + Vector3(0.0f, 0.85f, 0.0f);
			bounds.extents = Vector3(0.4f, 0.9f, 0.4f);
		}
	}
	float y = Math::EulerAngles(player->eyes()->rotation()).y;
	Vector3 center = bounds.center;
	Vector3 extents = bounds.extents;
	Vector3 frontTopLeft = Math::RotatePoint(center, Vector3(center.x - extents.x, center.y + extents.y, center.z - extents.z), y);
	Vector3 frontTopRight = Math::RotatePoint(center, Vector3(center.x + extents.x, center.y + extents.y, center.z - extents.z), y);
	Vector3 frontBottomLeft = Math::RotatePoint(center, Vector3(center.x - extents.x, center.y - extents.y, center.z - extents.z), y);
	Vector3 frontBottomRight = Math::RotatePoint(center, Vector3(center.x + extents.x, center.y - extents.y, center.z - extents.z), y);
	Vector3 backTopLeft = Math::RotatePoint(center, Vector3(center.x - extents.x, center.y + extents.y, center.z + extents.z), y);
	Vector3 backTopRight = Math::RotatePoint(center, Vector3(center.x + extents.x, center.y + extents.y, center.z + extents.z), y);
	Vector3 backBottomLeft = Math::RotatePoint(center, Vector3(center.x - extents.x, center.y - extents.y, center.z + extents.z), y);
	Vector3 backBottomRight = Math::RotatePoint(center, Vector3(center.x + extents.x, center.y - extents.y, center.z + extents.z), y);
	Vector2 frontTopLeft_2d, frontTopRight_2d, frontBottomLeft_2d, frontBottomRight_2d, backTopLeft_2d, backTopRight_2d, backBottomLeft_2d, backBottomRight_2d;
	if (utils::w2s(frontTopLeft, frontTopLeft_2d) &&
		utils::w2s(frontTopRight, frontTopRight_2d) &&
		utils::w2s(frontBottomLeft, frontBottomLeft_2d) &&
		utils::w2s(frontBottomRight, frontBottomRight_2d) &&
		utils::w2s(backTopLeft, backTopLeft_2d) &&
		utils::w2s(backTopRight, backTopRight_2d) &&
		utils::w2s(backBottomLeft, backBottomLeft_2d) &&
		utils::w2s(backBottomRight, backBottomRight_2d)) {
		g_Render->DrawLine(frontTopLeft_2d.x, frontTopLeft_2d.y, frontTopRight_2d.x, frontTopRight_2d.y, color, 1.5f, true);
		g_Render->DrawLine(frontTopRight_2d.x, frontTopRight_2d.y, frontBottomRight_2d.x, frontBottomRight_2d.y, color, 1.5f, true);
		g_Render->DrawLine(frontBottomRight_2d.x, frontBottomRight_2d.y, frontBottomLeft_2d.x, frontBottomLeft_2d.y, color, 1.5f, true);
		g_Render->DrawLine(frontBottomLeft_2d.x, frontBottomLeft_2d.y, frontTopLeft_2d.x, frontTopLeft_2d.y, color, 1.5f, true);
		g_Render->DrawLine(backTopLeft_2d.x, backTopLeft_2d.y, backTopRight_2d.x, backTopRight_2d.y, color, 1.5f, true);
		g_Render->DrawLine(backTopRight_2d.x, backTopRight_2d.y, backBottomRight_2d.x, backBottomRight_2d.y, color, 1.5f, true);
		g_Render->DrawLine(backBottomRight_2d.x, backBottomRight_2d.y, backBottomLeft_2d.x, backBottomLeft_2d.y, color, 1.5f, true);
		g_Render->DrawLine(backBottomLeft_2d.x, backBottomLeft_2d.y, backTopLeft_2d.x, backTopLeft_2d.y, color, 1.5f, true);
		g_Render->DrawLine(frontTopLeft_2d.x, frontTopLeft_2d.y, backTopLeft_2d.x, backTopLeft_2d.y, color, 1.5f, true);
		g_Render->DrawLine(frontTopRight_2d.x, frontTopRight_2d.y, backTopRight_2d.x, backTopRight_2d.y, color, 1.5f, true);
		g_Render->DrawLine(frontBottomRight_2d.x, frontBottomRight_2d.y, backBottomRight_2d.x, backBottomRight_2d.y, color, 1.5f, true);
		g_Render->DrawLine(frontBottomLeft_2d.x, frontBottomLeft_2d.y, backBottomLeft_2d.x, backBottomLeft_2d.y, color, 1.5f, true);
	}
}

void ESP(BasePlayer* BP, const ImColor color) {
	if (vars::players::sleeperignore && BP->get_flag(PlayerFlags::Sleeping)) return;
	if (!BP) return;
	Vector2 tempFeetR, tempFeetL;
	if (utils::w2s(BP->GetBoneByID(r_foot), tempFeetR) && utils::w2s(BP->GetBoneByID(l_foot), tempFeetL)) {
		if (tempFeetR.x == 0 && tempFeetR.y == 0) return;
		Vector2 tempHead;
		if (utils::w2s(BP->GetBoneByID(head) + Vector3(0, 0.2f, 0), tempHead)) {
			Vector2 tempFeet = (tempFeetR + tempFeetL) / 2.f;
			float Entity_h = tempHead.y - tempFeet.y;
			float w = Entity_h / 4;
			float Entity_x = tempFeet.x - w;
			float Entity_y = tempFeet.y;
			float Entity_w = Entity_h / 2;
			Vector3 middlePointWorld = BP->GetBoneByID(l_foot).midPoint(BP->GetBoneByID(r_foot));//cachedBones[BP->userID()]->l_foot->position.midPoint(cachedBones[BP->userID()]->r_foot->position
			Vector3 middlePointWorld_ = BP->GetBoneByID(head).midPoint(BP->GetBoneByID(head));//cachedBones[BP->userID()]->head->position.midPoint(cachedBones[BP->userID()]->head->position
			int CurPos = 0;
			int CurPos2 = 0;
			Vector2 middlePointPlayerTop;
			Vector2 middlePointPlayerFeet;
					if (utils::w2s(middlePointWorld_, middlePointPlayerTop) && utils::w2s(middlePointWorld, middlePointPlayerFeet)) {
						
						if (vars::players::fillbox) {
							if ((int)BP->health() > 0) {
								g_Render->FilledRect(Entity_x, Entity_y, Entity_w, Entity_h, ImColor(0, 0, 0, 175), 0, 0);
							}
						}
						if (vars::players::boxstyle == 0) {}
						if (vars::players::boxstyle == 1) {
							DrawList->AddRect({ Entity_x, Entity_y }, { Entity_x + Entity_w, Entity_y + Entity_h }, ImColor(0, 0, 0, 255), 0.f, 0.f, 1.2f);
							DrawList->AddRect({ Entity_x, Entity_y }, { Entity_x + Entity_w,Entity_y + Entity_h }, color, 0.f, 0.f);
						}
						if (vars::players::boxstyle == 2) {
							CornerBox(Entity_x, Entity_y, Entity_w, Entity_h, color);
						}
						if (vars::players::boxstyle == 3) {
							Box3D(BP, color);
						}
						if (vars::players::name) {
							if (vars::players::namePos == 0)
							{
								std::string _name(CStringA(BP->_displayName()));
								g_Render->DrawString(middlePointPlayerFeet.x, middlePointPlayerFeet.y + CurPos + 8.f, color, render2::centered_x | render2::outline, Verdanabyser, vars::misc::fotsize, _name.c_str());
							}

							if (vars::players::namePos == 1)
							{
								std::string _name(CStringA(BP->_displayName()));
								g_Render->DrawString(middlePointPlayerFeet.x, middlePointPlayerTop.y - 15.f, color, render2::centered_x | render2::outline, Verdanabyser, vars::misc::fotsize, _name.c_str());
							}

						}

						Item* ActWeapon = BP->GetActiveWeapon();

						if (vars::players::weapon && ActWeapon) {
							std::string string;	char buf[256] = { 0 };
							sprintf_s(buf, xorstr_("%ls"), ActWeapon->get_name());
							string += buf;
							if (vars::players::weaponPos == 0 && vars::players::weaponPos != vars::players::namePos)
							{
								g_Render->DrawString(middlePointPlayerFeet.x, middlePointPlayerFeet.y + CurPos + 8.f, color, render2::centered_x | render2::outline, Verdanabyser, vars::misc::fotsize, string.c_str());
							}
							if (vars::players::weaponPos == 0 && vars::players::weaponPos == vars::players::namePos)
							{
								g_Render->DrawString(middlePointPlayerFeet.x, middlePointPlayerFeet.y + CurPos + 18.f, color, render2::centered_x | render2::outline, Verdanabyser, vars::misc::fotsize, string.c_str());
							}
							if (vars::players::weaponPos == 1 && vars::players::weaponPos != vars::players::namePos)
							{
								g_Render->DrawString(middlePointPlayerFeet.x, middlePointPlayerTop.y - 15.f, color, render2::centered_x | render2::outline, Verdanabyser, vars::misc::fotsize, string.c_str());
							}
							if (vars::players::weaponPos == 1 && vars::players::weaponPos == vars::players::namePos)
							{
								g_Render->DrawString(middlePointPlayerFeet.x, middlePointPlayerTop.y - 25.f, color, render2::centered_x | render2::outline, Verdanabyser, vars::misc::fotsize, string.c_str());
							}

							CurPos += 12.f;
						}
						else if (vars::players::weapon)
						{
							std::string string;	char buf[256] = { 0 };

							string += buf;
							if (vars::players::weaponPos == 0 && vars::players::weaponPos != vars::players::namePos)
							{
								g_Render->DrawString(middlePointPlayerFeet.x, middlePointPlayerFeet.y + CurPos + 8.f, color, render2::centered_x | render2::outline, Verdanabyser, vars::misc::fotsize, "Empty");
							}
							if (vars::players::weaponPos == 0 && vars::players::weaponPos == vars::players::namePos)
							{
								g_Render->DrawString(middlePointPlayerFeet.x, middlePointPlayerFeet.y + CurPos + 18.f, color, render2::centered_x | render2::outline, Verdanabyser, vars::misc::fotsize, "Empty");
							}
							if (vars::players::weaponPos == 1 && vars::players::weaponPos != vars::players::namePos)
							{
								g_Render->DrawString(middlePointPlayerFeet.x, middlePointPlayerTop.y - 15.f, color, render2::centered_x | render2::outline, Verdanabyser, vars::misc::fotsize, "Empty");
							}
							if (vars::players::weaponPos == 1 && vars::players::weaponPos == vars::players::namePos)
							{
								g_Render->DrawString(middlePointPlayerFeet.x, middlePointPlayerTop.y - 25.f, color, render2::centered_x | render2::outline, Verdanabyser, vars::misc::fotsize, "Empty");
							}

							CurPos += 12.f;
						}
						if (vars::misc::eyeline) {


							//DDraw::Line(baseplayah->_playerModel()->position() , baseplayah->lastSentTick()->tick_position() , Color(0, 52, 255, 255), 2.f, true, true);

						}
						if (vars::players::distance) {
							std::string string; char buf[256] = { 0 };
							sprintf_s(buf, xorstr_("[ %dm ]"), (int)Math::Distance_3D(LocalPlayer::Entity()->GetBoneByID(head), BP->GetBoneByID(head)));
							string += buf;
							if (vars::players::weaponPos == 0 && vars::players::weaponPos != vars::players::namePos)
							{
								g_Render->DrawString(middlePointPlayerFeet.x, middlePointPlayerFeet.y + CurPos + 8.f, color, render2::centered_x | render2::outline, Verdanabyser, vars::misc::fotsize, string.c_str());
							}
							if (vars::players::weaponPos == 0 && vars::players::weaponPos == vars::players::namePos)
							{
								g_Render->DrawString(middlePointPlayerFeet.x, middlePointPlayerFeet.y + CurPos + 26.f, color, render2::centered_x | render2::outline, Verdanabyser, vars::misc::fotsize, string.c_str());
							}
							if (vars::players::weaponPos == 1 && vars::players::weaponPos != vars::players::namePos)
							{
								g_Render->DrawString(middlePointPlayerFeet.x, middlePointPlayerTop.y - 25.f, color, render2::centered_x | render2::outline, Verdanabyser, vars::misc::fotsize, string.c_str());
							}
							if (vars::players::weaponPos == 1 && vars::players::weaponPos == vars::players::namePos)
							{
								g_Render->DrawString(middlePointPlayerFeet.x, middlePointPlayerTop.y - 35.f, color, render2::centered_x | render2::outline, Verdanabyser, vars::misc::fotsize, string.c_str());
							}

							CurPos += 8;
						}
						if (vars::visuals::lookingDirection)
						{
							Vector2 forwardd;
							auto head_pos = BP->GetBoneByID(head);
							utils::w2s(BP->GetBoneByID(head) + (BP->eyes()->BodyForward() * 2), forwardd);
							Vector2 head;
							
						
							utils::w2s(head_pos, head);
							
							
							g_Render->DrawLine(head.x, head.y, forwardd.x, forwardd.y, color, 1.5f, true);
						}
						
						int health = (int)BP->health();
						int n = 5;
						int b = 0;
						float maxheal = 100.f;
						float CurOff = (health / maxheal);
						if (vars::players::healthbar) {
							g_Render->FilledRect(Entity_x + Entity_w - 8.f, Entity_y, 5, Entity_h, ImColor(0, 0, 0), 0, 0);
							ImColor color_health = ImColor(0.f, 255.f, 0.f, 0.8f);
							ImColor color_grad1 = ImColor(vars::colors::gradient_1[0], vars::colors::gradient_1[1], vars::colors::gradient_1[2]);
							ImColor color_grad2 = ImColor(vars::colors::gradient_2[0], vars::colors::gradient_2[1], vars::colors::gradient_2[2]);
							if (vars::players::healthbarscolor == 0) {
								if ((int)BP->health() <= 33) {
									color_health = ImColor(255.f, 0.f, 0.f, 0.8f);
								}
								if ((int)BP->health() >= 34 && (int)BP->health() <= 66) {
									color_health = ImColor(255.f, 202.f, 0.f, 0.8f);
								}
								if ((int)BP->health() >= 67) {
									color_health = ImColor(0.f, 255.f, 0.f, 0.8f);
								}
							}
							else if (vars::players::healthbarscolor == 1) {
								color_health = ImColor(vars::colors::Player_custom_healthColor[0], vars::colors::Player_custom_healthColor[1], vars::colors::Player_custom_healthColor[2]);
							}
							
							if (vars::players::healthbarscolortyle == 0 )
								g_Render->FilledRect(Entity_x + Entity_w - 8.f, Entity_y, 5, Entity_h * (health / maxheal), color_health, 0, 0);
							else if (vars::players::healthbarscolortyle == 1 )
								g_Render->DrawLineGradient(Entity_x + Entity_w - 8.f, Entity_y, 5, Entity_h * (health / maxheal), color_grad1, color_grad2, 1, true);
							g_Render->Rect(Entity_x + Entity_w - 8.f, Entity_y, 5, Entity_h, ImColor(0, 0, 0), 0, 0);
							if ((int)BP->health() <= 99 ) {
								std::string string;
								char buf[256] = { 0 }; sprintf_s(buf, xorstr_("%d"), (int)BP->health());
								string += buf;
								g_Render->DrawString(Entity_x + Entity_w - 6.f, Entity_y + (Entity_h * CurOff) - 4, color, render2::centered_x | render2::outline, Verdanabyser, vars::misc::fotsize, string.c_str());
							}
						}
						
					}//verdana//Verdanabyser
				
			

			
		}
	}
}
void NPCESP(BasePlayer* BP, ImColor color) {
	Vector2 tempFeetR, tempFeetL;
	if (utils::w2s(BP->GetBoneByID(r_foot), tempFeetR) && utils::w2s(BP->GetBoneByID(l_foot), tempFeetL)) {
		if (tempFeetR.x == 0 && tempFeetR.y == 0) return;
		Vector2 tempHead;
		if (utils::w2s(BP->GetBoneByID(jaw) + Vector3(0.f, 0.16f, 0.f), tempHead)) {
			Vector2 tempFeet = (tempFeetR + tempFeetL) / 2.f;
			float Entity_h = tempHead.y - tempFeet.y;
			float w = Entity_h / 4;
			float Entity_x = tempFeet.x - w;
			float Entity_y = tempFeet.y;
			float Entity_w = Entity_h / 2;
			Vector3 middlePointWorld = BP->GetBoneByID(l_foot).midPoint(BP->GetBoneByID(r_foot));
			Vector3 middlePointWorld_ = BP->GetBoneByID(head).midPoint(BP->GetBoneByID(head));
			int CurPos = 0;
			int CurPos2 = 0;
			Vector2 middlePointPlayerTop;
			Vector2 middlePointPlayerFeet;
	

			{
		
					if (utils::w2s(middlePointWorld_, middlePointPlayerTop) && utils::w2s(middlePointWorld, middlePointPlayerFeet)) {
						if (vars::npc::fillbox) {
							g_Render->FilledRect(Entity_x, Entity_y, Entity_w, Entity_h, ImColor(0, 0, 0, 175), 0, 0);
						}
						if (vars::npc::boxstyle == 0) {}
						if (vars::npc::boxstyle == 1) {
							DrawList->AddRect({ Entity_x, Entity_y }, { Entity_x + Entity_w, Entity_y + Entity_h }, ImColor(0, 0, 0, 255), 0.f, 0.f, 1.2f);
							DrawList->AddRect({ Entity_x, Entity_y }, { Entity_x + Entity_w,Entity_y + Entity_h }, color, 0.f, 0.f);
						}
						if (vars::npc::boxstyle == 2) {
							CornerBox(Entity_x, Entity_y, Entity_w, Entity_h, ImColor(vars::colors::npc_box_color));
						}
						if (vars::npc::name) {
							g_Render->DrawString(middlePointPlayerTop.x, middlePointPlayerTop.y - 15.f, ImColor(vars::colors::npc_name_color), render2::centered_x | render2::outline, Verdanaboltbyser, vars::misc::fotsize, xorstr_("NPC"));
						}
						Item* ActWeapon = BP->GetActiveWeapon();
						if (vars::npc::weapon && ActWeapon) {
							std::string string; char buf[256] = { 0 };
							sprintf_s(buf, xorstr_("%ls"), ActWeapon->get_name());
							string += buf;
							g_Render->DrawString(middlePointPlayerFeet.x, middlePointPlayerFeet.y + CurPos2 + 5.f, ImColor(vars::colors::npc_name_color), render2::centered_x | render2::outline, Verdanaboltbyser, vars::misc::fotsize, string.c_str());
							CurPos2 += 10;
						}

						if (vars::npc::distance) {
							std::string string;
							char buf[256] = { 0 }; sprintf_s(buf, xorstr_("%dm"), (int)Math::Distance_3D(LocalPlayer::Entity()->GetBoneByID(head), BP->GetBoneByID(head)));
							string += buf;
							g_Render->DrawString(middlePointPlayerFeet.x, middlePointPlayerFeet.y + CurPos2 + 5.f, ImColor(vars::colors::npc_name_color), render2::centered_x | render2::outline, Verdanaboltbyser, vars::misc::fotsize, string.c_str());
							CurPos2 += 10;
						}
						int health = (int)BP->health();
						float maxheal = 150.f;
						float CurOff = (health / maxheal);
						int n = 5;
						int b = 0;
						if (vars::npc::healthbar) {
							g_Render->FilledRect(Entity_x + Entity_w - 8.f, Entity_y, 5, Entity_h, ImColor(0, 0, 0), 0, 0);
							ImColor color_health = ImColor(0.f, 255.f, 0.f, 0.8f);
							ImColor color_grad1 = ImColor(vars::colors::gradient_1[0], vars::colors::gradient_1[1], vars::colors::gradient_1[2]);
							ImColor color_grad2 = ImColor(vars::colors::gradient_2[0], vars::colors::gradient_2[1], vars::colors::gradient_2[2]);
							if (vars::npc::healthbarscolor == 0) {
								if ((int)BP->health() <= 33) {
									color_health = ImColor(255.f, 0.f, 0.f, 0.8f);
								}
								if ((int)BP->health() >= 34 && (int)BP->health() <= 66) {
									color_health = ImColor(255.f, 202.f, 0.f, 0.8f);
								}
								if ((int)BP->health() >= 67) {
									color_health = ImColor(0.f, 255.f, 0.f, 0.8f);
								}
							}
							else if (vars::npc::healthbarscolor == 1) {
								color_health = ImColor(vars::colors::npc_custom_healthColor[0], vars::colors::npc_custom_healthColor[1], vars::colors::npc_custom_healthColor[2]);
							}
							if (vars::npc::healthbarscolortyle == 0)
								g_Render->FilledRect(Entity_x + Entity_w - 8.f, Entity_y, 5, Entity_h * (health / maxheal), color_health, 0, 0);
							else if (vars::npc::healthbarscolortyle == 1)
								g_Render->DrawLineGradient(Entity_x + Entity_w - 8.f, Entity_y, 5, Entity_h * (health / maxheal), color_grad1, color_grad2, 1, true);
							g_Render->Rect(Entity_x + Entity_w - 8.f, Entity_y, 5, Entity_h, ImColor(0, 0, 0), 0, 0);
							if ((int)BP->health() <= 99) {
								std::string string;
								char buf[256] = { 0 }; sprintf_s(buf, xorstr_("%d"), (int)BP->health());
								string += buf;
								g_Render->DrawString(Entity_x + Entity_w - 6.f, Entity_y + (Entity_h * CurOff) - 4, color, render2::centered_x | render2::outline, Verdanaboltbyser, vars::misc::fotsize, string.c_str());

							}
						}
					}
				}
			}
		}
	
}