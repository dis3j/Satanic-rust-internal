#include "defs.h"
Vector3 last_head_pos = Vector3::Zero();
Vector3 last_neck_pos = Vector3::Zero();
Vector3 last_spine4_pos = Vector3::Zero();
Vector3 last_spine3_pos = Vector3::Zero();
Vector3 last_spine2_pos = Vector3::Zero();
Vector3 last_spine1_pos = Vector3::Zero();
Vector3 last_l_upperarm_pos = Vector3::Zero();
Vector3 last_l_forearm_pos = Vector3::Zero();
Vector3 last_l_hand_pos = Vector3::Zero();
Vector3 last_r_upperarm_pos = Vector3::Zero();
Vector3 last_r_forearm_pos = Vector3::Zero();
Vector3 last_r_hand_pos = Vector3::Zero();
Vector3 last_pelvis_pos = Vector3::Zero();
Vector3 last_l_knee_pos = Vector3::Zero();
Vector3 last_l_foot_pos = Vector3::Zero();
Vector3 last_r_knee_pos = Vector3::Zero();
Vector3 last_r_foot_pos = Vector3::Zero();

bool magic_projectile_test = false;
float insta_travel_check_time = -1.f;
bool is_noclipping = false;
bool proj = false;
int flick = 0;
int yaw = 100;

bool targeted = false;
float target_time = 0.f;
float desync_time = 0;
Vector3 GetTrajectoryPoint(Vector3& startingPosition, Vector3 initialVelocity, float timestep, float gravity)
{
	float physicsTimestep = Time::fixedDeltaTime();
	Vector3 stepVelocity = initialVelocity * physicsTimestep;

	//Gravity is already in meters per second, so we need meters per second per second
	Vector3 stepGravity(0, physicsTimestep * physicsTimestep * gravity, 0);

	return startingPosition + (stepVelocity * timestep) + ((stepGravity * (timestep * timestep + timestep)) / 2.0f);;
}

using namespace hk_defs;

auto gameAssembly = GetModuleHandleA(xorstr_("GameAssembly.dll"));

#define ProcAddr(func) GetProcAddress(gameAssembly, func)

template<typename T, typename... Args>
inline T call(const char* func, Args... args) {
	return reinterpret_cast<T(__fastcall*)(Args...)>(ProcAddr(func))(args...);
}
namespace System {
	class Object_ {
	public:

	};
	template<typename T = void*>
	class Array {
	public:
		uint32_t size() {
			if (!this) return 0;
			return *reinterpret_cast<uint32_t*>(this + 0x18);
		}
		T get(int idx) {
			if (!this) return T{};
			return *reinterpret_cast<T*>(this + (0x20 + (idx * 0x8)));
		}
		void add(int idx, T value) {
			if (!this) return;
			*reinterpret_cast<T*>(this + (0x20 + (idx * 0x8))) = value;
		}
	};
	class String : public Object_ {
	public:
		char pad_0000[0x10];
		int len;
		wchar_t buffer[0];

		static String* New(const char* str) {
			return call<String*, const char*>(xorstr_("il2cpp_string_new"), str);
		}
	};
}
class MonoBehaviour {
public:
	static inline System::Object_* (*StartCoroutine_)(MonoBehaviour*, System::Object_*) = nullptr;
	System::Object_* StartCoroutine(System::Object_* routine) {
		return StartCoroutine_(this, routine);
	}
};
uintptr_t shader;


auto chams(BasePlayer* player, bool draw = true) -> void
{
	bool PlayerSleeping = player->get_flag(16);
	if (vars::players::sleeperignore && PlayerSleeping) return;
	if (draw) {
		Vector2 screen;
		if (utils::w2s(player->transform()->position(), screen))
		{
			if (vars::players::chams) {
				static float r = 1.00f, g = 0.00f, b = 1.00f;
				static int cases = 0;
				switch (cases) {
				case 0: { r -= 0.004f; if (r <= 0) cases += 1; break; }
				case 1: { g += 0.004f; b -= 0.004f; if (g >= 1) cases += 1; break; }
				case 2: { r += 0.004f; if (r >= 1) cases += 1; break; }
				case 3: { b += 0.004f; g -= 0.004f; if (b >= 1) cases = 0; break; }
				default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
				}
				/*auto _multiMesh = player->get_player_model2()->_multiMesh();*/
				auto _multiMesh = player->playerModel()->_multiMesh();
				if (_multiMesh) {
					auto render = _multiMesh->get_Renderers();
					for (int i = 0; i < render->get_size(); i++) {
						auto renderer = render->get_value(i);
						if (renderer) {
							Material* material = renderer->GetMaterial();
							if (material) {
								if (vars::players::chams_type == 0)
								{
									material->SetInt((char*)"_ZTest", 8);
									material->SetShader(chamsShader);
									material->SetColor(xorstr_(L"_Color"), col(vars::colors::chams.x, vars::colors::chams.y, vars::colors::chams.z, 1));
									material->SetColor(xorstr_(L"_ColorVisible"), col(vars::colors::chams.x, vars::colors::chams.y, vars::colors::chams.z, 1));
									material->SetColor(xorstr_(L"_ColorBehind"), col(vars::colors::chams.x, vars::colors::chams.y, vars::colors::chams.z, 1));
								}
			
								else if (vars::players::chams_type == 1)
								{
									material->SetInt((char*)"_ZTest", 8);
									material->SetShader(wireframe);
									material->SetColor(xorstr_(L"_WireColor"), col(vars::colors::chams.x, vars::colors::chams.y, vars::colors::chams.z, 1));
								}
								else if (vars::players::chams_type == 2)
								{
									material->SetShader(settrought);
								}
								else if (vars::players::chams_type == 3)
								{
									material->SetShader(list_shader);
									material->SetColor(xorstr_(L"_ColorVisible"), col(vars::colors::chamsvusuble.x, vars::colors::chamsvusuble.y, vars::colors::chamsvusuble.z, 1));
									material->SetColor(xorstr_(L"_ColorBehind"), col(vars::colors::chamsinvusuble.x, vars::colors::chamsinvusuble.y, vars::colors::chamsinvusuble.z, 1));
								}
								else if (vars::players::chams_type == 4)
								{
									material->SetShader(huy);
									material->SetColor(xorstr_(L"_ColorVisible"), col(vars::colors::chamsvusuble.x, vars::colors::chamsvusuble.y, vars::colors::chamsvusuble.z, 1));
									material->SetColor(xorstr_(L"_ColorBehind"), col(vars::colors::chamsinvusuble.x, vars::colors::chamsinvusuble.y, vars::colors::chamsinvusuble.z, 1));
								}
							}
						}
					}
				}
			}
		}
	}
}

auto chamslocal(BasePlayer* player, bool draw = true) -> void
{
	bool PlayerSleeping = player->get_flag(16);
	if (vars::players::sleeperignore && PlayerSleeping) return;
	if (draw) {
		Vector2 screen;
		if (utils::w2s(player->transform()->position(), screen))
		{
			if (vars::visuals::hand_chams && LocalPlayer::Entity()->is_local_player()) {
				static float r = 1.00f, g = 0.00f, b = 1.00f;
				static int cases = 0;
				switch (cases) {
				case 0: { r -= 0.004f; if (r <= 0) cases += 1; break; }
				case 1: { g += 0.004f; b -= 0.004f; if (g >= 1) cases += 1; break; }
				case 2: { r += 0.004f; if (r >= 1) cases += 1; break; }
				case 3: { b += 0.004f; g -= 0.004f; if (b >= 1) cases = 0; break; }
				default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
				}
				/*auto _multiMesh = player->get_player_model2()->_multiMesh();*/
				auto _multiMesh = player->playerModel()->_multiMesh();
				if (_multiMesh) {
					auto render = _multiMesh->get_Renderers();
					for (int i = 0; i < render->get_size(); i++) {
						auto renderer = render->get_value(i);
						if (renderer) {
							Material* material = renderer->GetMaterial();
							if (material) {
								if (vars::visuals::hand_chams_type == 0)
								{
									material->SetInt((char*)"_ZTest", 8);
									material->SetShader(chamsShader);
									material->SetColor(xorstr_(L"_Color"), col(vars::colors::hand_chams.x, vars::colors::hand_chams.y, vars::colors::hand_chams.z, 1));
									material->SetColor(xorstr_(L"_ColorVisible"), col(vars::colors::hand_chams.x, vars::colors::hand_chams.y, vars::colors::hand_chams.z, 1));
									material->SetColor(xorstr_(L"_ColorBehind"), col(vars::colors::hand_chams.x, vars::colors::hand_chams.y, vars::colors::hand_chams.z, 1));
								}
								else if (vars::visuals::hand_chams_type == 1)
								{
									material->SetInt((char*)"_ZTest", 8);
									renderer->set_material(GalaxyMaterial);
								}
								else if (vars::visuals::hand_chams_type == 2)
								{
									material->SetInt((char*)"_ZTest", 8);
									material->SetShader(wireframe);
									material->SetColor(xorstr_(L"_WireColor"), col(vars::colors::hand_chams.x, vars::colors::hand_chams.y, vars::colors::hand_chams.z, 1));
								}
								else if (vars::visuals::hand_chams_type == 3)
								{
									material->SetShader(settrought);
								}
								else if (vars::visuals::hand_chams_type == 4)
								{
									material->SetShader(list_shader);
									material->SetColor(xorstr_(L"_ColorVisible"), col(vars::colors::hand_chams.x, vars::colors::hand_chams.y, vars::colors::hand_chams.z, 1));
									material->SetColor(xorstr_(L"_ColorBehind"), col(vars::colors::hand_chams.x, vars::colors::hand_chams.y, vars::colors::hand_chams.z, 1));
								}
								else if (vars::visuals::hand_chams_type == 5)
								{
									material->SetShader(huy);
									material->SetColor(xorstr_(L"_ColorVisible"), col(vars::colors::hand_chams.x, vars::colors::hand_chams.y, vars::colors::hand_chams.z, 1));
									material->SetColor(xorstr_(L"_ColorBehind"), col(vars::colors::hand_chams.x, vars::colors::hand_chams.y, vars::colors::hand_chams.z, 1));
								}
							}
						}
					}
				}
			}
		}
	}
}
void HandChams() {
	if (!LocalPlayer::Entity()->is_alive() || LocalPlayer::Entity()->is_sleeping()) return;
	if (vars::visuals::hand_chams && LocalPlayer::Entity()->is_local_player()) {
		static float r = 1.00f, g = 0.00f, b = 1.00f;
		static int cases = 0;
		switch (cases) {
		case 0: { r -= 0.004f; if (r <= 0) cases += 1; break; }
		case 1: { g += 0.004f; b -= 0.004f; if (g >= 1) cases += 1; break; }
		case 2: { r += 0.004f; if (r >= 1) cases += 1; break; }
		case 3: { b += 0.004f; g -= 0.004f; if (b >= 1) cases = 0; break; }
		default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
		}
		auto model = get_activemodel();
		auto renderers = ((Networkable*)model)->GetComponentsInChildren(GetType(xorstr_("UnityEngine"), xorstr_("Renderer")));
		if (renderers)
		{
			auto sz = *reinterpret_cast<int*>(renderers + 0x18);
			for (int i = 0; i < sz; i++) {
				auto renderer = *reinterpret_cast<Renderer_**>(renderers + 0x20 + i * 0x8);
				if (!renderer) continue;
				Material* material = renderer->material();
				if (!material) continue;
				if (vars::visuals::hand_chams_type == 0)
				{
					material->SetShader(chamsShader);
					material->SetColor(xorstr_(L"_Color"), col(vars::colors::hand_chams.x, vars::colors::hand_chams.y, vars::colors::hand_chams.z, 1));
				}
				else if (vars::visuals::hand_chams_type == 1)
				{
					material->SetShader(wireframe);
					material->SetColor(xorstr_(L"_WireColor"), col(vars::colors::hand_chams.x, vars::colors::hand_chams.y, vars::colors::hand_chams.z, 1));
				}
				else if (vars::visuals::hand_chams_type == 2)
				{
					material->SetShader(settrought);
				}
				else if (vars::visuals::hand_chams_type == 3)
				{
					material->SetShader(list_shader);
					material->SetColor(xorstr_(L"_ColorVisible"), col(vars::colors::hand_chams.x, vars::colors::hand_chams.y, vars::colors::hand_chams.z, 1));
					material->SetColor(xorstr_(L"_ColorBehind"), col(vars::colors::hand_chams.x, vars::colors::hand_chams.y, vars::colors::hand_chams.z, 1));
				}
				else if (vars::visuals::hand_chams_type == 4)
				{
					material->SetShader(huy);
					material->SetColor(xorstr_(L"_ColorVisible"), col(vars::colors::hand_chams.x, vars::colors::hand_chams.y, vars::colors::hand_chams.z, 1));
					material->SetColor(xorstr_(L"_ColorBehind"), col(vars::colors::hand_chams.x, vars::colors::hand_chams.y, vars::colors::hand_chams.z, 1));
				}
			}
		}
	}
}
Projectile* projv;

namespace hk {
	namespace exploit {
		void DoMovement(Projectile* projectile, float deltaTime) {
			auto held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();
			BaseProjectile* _held = held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();

			/*if (projectile->isAuthoritative() && vars::combat::always_heli_rotor) {
				f_object target = f_object::get_closest_object(projectile->currentPosition(), xorstr_("xdwadawfgaga"),
					Vector3::Zero(), Vector3::Zero(), Vector3::Zero(),
					true, xorstr_("BaseHelicopter"));

				if (target.valid) {
					Vector3 tar = reinterpret_cast<BaseEntity*>(target.entity)->transform()->position();
					if (utils::LineOfSight(tar, projectile->currentPosition()) && Math::Distance_3D(projectile->currentPosition(), tar) < 35.0f) {
						if (projectile->traveledDistance() > 35.0f) {
							Transform* transform = reinterpret_cast<BaseEntity*>(target.entity)->transform();

							HitTest* hitTest = projectile->hitTest();
							hitTest->DidHit() = true;
							hitTest->HitEntityt((BaseEntity*)target.entity);
							hitTest->HitTransform() = transform;
							hitTest->HitPoint() = transform->InverseTransformPoint(projectile->currentPosition());
							hitTest->HitNormal() = transform->InverseTransformDirection(projectile->currentPosition());
							hitTest->AttackRay() = Ray(projectile->currentPosition(), tar - projectile->currentPosition());
							projectile->DoHit(hitTest, hitTest->HitPointWorld(), hitTest->HitNormalWorld());
							return;
						}
					}
				}
			}*/
			if (projectile->owner()->userID() == LocalPlayer::Entity()->userID()
				&& vars::combat::followprojectile)
			{
				proj = true;
				projv = projectile;
			}
	


			return original_domovement(projectile, deltaTime);
		}
		bool Refract(Projectile* prj, uint32_t seed, Vector3 point, Vector3 normal, float resistancePower) {
			if (vars::combat::tree_reflect) {
				float gravity;
				if (reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer) != nullptr && reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->IsValid() && LocalPlayer::Entity()->get_flag(PlayerFlags::Connected)) {
					gravity = GetGravity(LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo());
					a::Prediction(prj->currentPosition(), reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->GetBoneByID(head), reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->newVelocity(), GetBulletSpeed(), gravity);
					prj->currentVelocity((reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->GetBoneByID(head) - prj->currentPosition()) * (GetBulletSpeed() / 75.f));
					prj->currentPosition(prj->currentPosition() + prj->currentVelocity().Normalized() * 0.001f);
				}
			}
			else {
				return original_refract(prj, seed, point, normal, resistancePower);
			}
		}
	}

	namespace misc {
		void ClientUpdate(BasePlayer* player) {
			lol::cachePlayer(player);

			return original_clientupdate(player);
		}
		void ClientUpdate_Sleeping(BasePlayer* player) {
			if (!vars::players::sleeperignore) {
				lol::cachePlayer(player);
			}

			return original_clientupdate_sleeping(player);
		}
		void VisUpdateUsingCulling(BasePlayer* pl, float dist, bool vis) {
			if (vars::players::chams) {
				return original_UnregisterFromVisibility(pl, 2.f, true);
			}
			else {
				return original_UnregisterFromVisibility(pl, dist, vis);
			}
		}
		float LastUpdate = 0.f;
		GameObject* CreateEffect(pUncStr strPrefab, Effect* effect) {
			auto effectName = strPrefab->str;
			auto position = read(effect + 0x64, Vector3);
			if (vars::visuals::raid_esp && effect && strPrefab->str && !position.empty()) {
				std::string string;
				char buf[256] = { 0 };
				switch (RUNTIME_CRC32_W(effectName)) {
				case STATIC_CRC32("assets/prefabs/tools/c4/effects/c4_explosion.prefab"):

					LogSystem::LogExplosion(C4, position);

					sprintf_s(buf, xorstr_("Explosion: %ls, Distsnce: %1.0fm"), wC4.c_str(), Math::Distance_3D(LocalPlayer::Entity()->GetBoneByID(head), position));
					string += buf;

					//g_Render->DrawString(100,100, ImColor(255, 255, 255), render2::outline | render2::centered_x, Cuniaabyser, 12, string.c_str());
				//	notify::add_log(("Hit for %.2f damage")/*, reinterpret_cast<BasePlayer*>(entity)->_displayName()*//*, utils::StringPool::Get(info->HitBone())->buffer*/, info->damageTypes()->Total(), ImColor(accent_color[0], accent_color[1], accent_color[2]), ImColor(255, 255, 255), 4700);
				//	LogSystem::Log(("Hit for %.2f damage")/*, reinterpret_cast<BasePlayer*>(entity)->_displayName()*//*, utils::StringPool::Get(info->HitBone())->buffer*/, info->damageTypes()->Total()), 5.f;
					//std::string _name(CStringA(reinterpret_cast<BasePlayer*>(entity)->_displayName()));
					//std::string string; 
					//char buf[256] = { 0 }; sprintf_s(buf, xorstr_("Hit %ls 's in the %ls for %d damage"), _name, utils::StringPool::Get(info->HitBone())->buffer, (int)info->damageTypes()->Total());
					///string += buf;
					notify::add_log("Raid", string.c_str(), ImColor(accent_color[0], accent_color[1], accent_color[2]), ImColor(255, 255, 255), 4700);
					//	LogSystem::Log(StringFormat::format(xorstr_(L"✚ Explosion: %ls, Distsnce: %1.0fm"), wC4.c_str( ), Math::Distance_3D(LocalPlayer::Entity( )->get_bone_pos(head), position)), 15.f);
					break;
				case STATIC_CRC32("assets/prefabs/weapons/satchelcharge/effects/satchel-charge-explosion.prefab"):
					LogSystem::LogExplosion(Satchel, position);
					sprintf_s(buf, xorstr_("Explosion: %ls, Distsnce: %1.0fm"), wSatchel.c_str(), Math::Distance_3D(LocalPlayer::Entity()->GetBoneByID(head), position));
					string += buf;

					//g_Render->DrawString(100,100, ImColor(255, 255, 255), render2::outline | render2::centered_x, Cuniaabyser, 12, string.c_str());
				//	notify::add_log(("Hit for %.2f damage")/*, reinterpret_cast<BasePlayer*>(entity)->_displayName()*//*, utils::StringPool::Get(info->HitBone())->buffer*/, info->damageTypes()->Total(), ImColor(accent_color[0], accent_color[1], accent_color[2]), ImColor(255, 255, 255), 4700);
				//	LogSystem::Log(("Hit for %.2f damage")/*, reinterpret_cast<BasePlayer*>(entity)->_displayName()*//*, utils::StringPool::Get(info->HitBone())->buffer*/, info->damageTypes()->Total()), 5.f;
					//std::string _name(CStringA(reinterpret_cast<BasePlayer*>(entity)->_displayName()));
					//std::string string; 
					//char buf[256] = { 0 }; sprintf_s(buf, xorstr_("Hit %ls 's in the %ls for %d damage"), _name, utils::StringPool::Get(info->HitBone())->buffer, (int)info->damageTypes()->Total());
					///string += buf;
					notify::add_log("Raid", string.c_str(), ImColor(accent_color[0], accent_color[1], accent_color[2]), ImColor(255, 255, 255), 4700);
					//		LogSystem::Log(StringFormat::format(xorstr_(L"✚ Explosion: %ls, Distsnce: %1.0fm"), wSatchel.c_str( ), Math::Distance_3D(LocalPlayer::Entity( )->get_bone_pos(head), position)), 15.f);
					break;
				case STATIC_CRC32("assets/prefabs/weapons/rocketlauncher/effects/rocket_explosion_incendiary.prefab"):
					LogSystem::LogExplosion(IncenRocket, position);
					sprintf_s(buf, xorstr_("Explosion: %ls, Distsnce: %1.0fm"), wIncenRocket.c_str(), Math::Distance_3D(LocalPlayer::Entity()->GetBoneByID(head), position));
					string += buf;

					//g_Render->DrawString(100,100, ImColor(255, 255, 255), render2::outline | render2::centered_x, Cuniaabyser, 12, string.c_str());
				//	notify::add_log(("Hit for %.2f damage")/*, reinterpret_cast<BasePlayer*>(entity)->_displayName()*//*, utils::StringPool::Get(info->HitBone())->buffer*/, info->damageTypes()->Total(), ImColor(accent_color[0], accent_color[1], accent_color[2]), ImColor(255, 255, 255), 4700);
				//	LogSystem::Log(("Hit for %.2f damage")/*, reinterpret_cast<BasePlayer*>(entity)->_displayName()*//*, utils::StringPool::Get(info->HitBone())->buffer*/, info->damageTypes()->Total()), 5.f;
					//std::string _name(CStringA(reinterpret_cast<BasePlayer*>(entity)->_displayName()));
					//std::string string; 
					//char buf[256] = { 0 }; sprintf_s(buf, xorstr_("Hit %ls 's in the %ls for %d damage"), _name, utils::StringPool::Get(info->HitBone())->buffer, (int)info->damageTypes()->Total());
					///string += buf;
					notify::add_log("Raid", string.c_str(), ImColor(accent_color[0], accent_color[1], accent_color[2]), ImColor(255, 255, 255), 4700);
					//LogSystem::Log(StringFormat::format(xorstr_(L"✚ Explosion: %ls, Distsnce: %1.0fm"), wIncenRocket.c_str( ), Math::Distance_3D(LocalPlayer::Entity( )->get_bone_pos(head), position)), 15.f);
					break;
				case STATIC_CRC32("assets/prefabs/weapons/rocketlauncher/effects/rocket_explosion.prefab"):
					LogSystem::LogExplosion(Rocket, position);
					sprintf_s(buf, xorstr_("Explosion: %ls, Distsnce: %1.0fm"), wRocket.c_str(), Math::Distance_3D(LocalPlayer::Entity()->GetBoneByID(head), position));
					string += buf;

					//g_Render->DrawString(100,100, ImColor(255, 255, 255), render2::outline | render2::centered_x, Cuniaabyser, 12, string.c_str());
				//	notify::add_log(("Hit for %.2f damage")/*, reinterpret_cast<BasePlayer*>(entity)->_displayName()*//*, utils::StringPool::Get(info->HitBone())->buffer*/, info->damageTypes()->Total(), ImColor(accent_color[0], accent_color[1], accent_color[2]), ImColor(255, 255, 255), 4700);
				//	LogSystem::Log(("Hit for %.2f damage")/*, reinterpret_cast<BasePlayer*>(entity)->_displayName()*//*, utils::StringPool::Get(info->HitBone())->buffer*/, info->damageTypes()->Total()), 5.f;
					//std::string _name(CStringA(reinterpret_cast<BasePlayer*>(entity)->_displayName()));
					//std::string string; 
					//char buf[256] = { 0 }; sprintf_s(buf, xorstr_("Hit %ls 's in the %ls for %d damage"), _name, utils::StringPool::Get(info->HitBone())->buffer, (int)info->damageTypes()->Total());
					///string += buf;
					notify::add_log("Raid", string.c_str(), ImColor(accent_color[0], accent_color[1], accent_color[2]), ImColor(255, 255, 255), 4700);
					//LogSystem::Log(StringFormat::format(xorstr_(L"✚ Explosion: %ls, Distsnce: %1.0fm"), wRocket.c_str( ), Math::Distance_3D(LocalPlayer::Entity( )->get_bone_pos(head), position)), 15.f);
					break;
				}
			}
			return original_createeffect(strPrefab, effect);
		}

		int yeet = 100;
		int flick = 0;
		int yaw = 100;
		void __fastcall SetFlying(ModelState* a1, bool a2) { }
		void SendClientTick(BasePlayer* baseplayer) {
			if (!baseplayer) return original_sendclienttick(baseplayer);
			if (vars::misc::anti_aim) {

				auto input = read(baseplayer + O::BasePlayer::input, uintptr_t);
				auto state = read(input + 0x20, uintptr_t);
				auto current = read(state + 0x10, uintptr_t); if (!current) { return original_sendclienttick(baseplayer); }
				if (!current)
					return original_sendclienttick(baseplayer);
				Vector3 real_angles = safe_read(current + 0x18, Vector3);
				Vector3 spin_angles = Vector3::Zero();
				//
				//spin_angles = Vector3((rand() % 999 + -999), (rand() % 999 + -999), (rand() % 999 + -999));
				//

				//if (spin_angles != Vector3::Zero())
				//	write(current + 0x18, spin_angles, Vector3);
				yeet += vars::misc::anti_aim_speed;
				if (yeet >= 999) { // reset number
					yeet = -999;
				}
				
				if (vars::misc::anti_aim_yaw == 0) {
					yaw = 100;
				}
				if (vars::misc::anti_aim_yaw == 1) {
					yaw = -100;
				}
				if (vars::misc::anti_aim_yaw == 2) {
					yaw = 0;
				}
				spin_angles = Vector3((yeet), (yaw), (yeet));
				if (spin_angles != Vector3::Zero())
					write(current + 0x18, spin_angles, Vector3);
			}
			if (vars::misc::local_bones)
			{
				last_head_pos = LocalPlayer::Entity()->GetBoneByID(head);// baseplayer->bones()->head->position;
				last_neck_pos = LocalPlayer::Entity()->GetBoneByID(neck);//baseplayer->bones()->neck->position;
				last_spine4_pos = LocalPlayer::Entity()->GetBoneByID(spine4);// baseplayer->bones()->spine4->position;
				last_spine1_pos = LocalPlayer::Entity()->GetBoneByID(spine1);//baseplayer->bones()->spine1->position;
				last_l_upperarm_pos = LocalPlayer::Entity()->GetBoneByID(l_upperarm); //baseplayer->bones()->l_upperarm->position;
				last_l_forearm_pos = LocalPlayer::Entity()->GetBoneByID(l_forearm);//baseplayer->bones()->l_forearm->position;
				last_l_hand_pos = LocalPlayer::Entity()->GetBoneByID(l_hand);//baseplayer->bones()->l_hand->position;
				last_r_upperarm_pos = LocalPlayer::Entity()->GetBoneByID(r_upperarm);//baseplayer->bones()->r_upperarm->position;
				last_r_forearm_pos = LocalPlayer::Entity()->GetBoneByID(r_forearm);//baseplayer->bones()->r_forearm->position;
				last_r_hand_pos = LocalPlayer::Entity()->GetBoneByID(r_hand);//baseplayer->bones()->r_hand->position;
				last_pelvis_pos = LocalPlayer::Entity()->GetBoneByID(pelvis);//baseplayer->bones()->pelvis->position;
				last_l_knee_pos = LocalPlayer::Entity()->GetBoneByID(l_knee); //baseplayer->bones()->l_knee->position;
				last_l_foot_pos = LocalPlayer::Entity()->GetBoneByID(l_foot);// baseplayer->bones()->l_foot->position;
				last_r_knee_pos = LocalPlayer::Entity()->GetBoneByID(r_knee);//baseplayer->bones()->r_knee->position;
				last_r_foot_pos = LocalPlayer::Entity()->GetBoneByID(r_foot);//baseplayer->bones()->r_foot->position;
			}
			//if (baseplayer->userID() == LocalPlayer::Entity()->userID()) {

			//
			//	Vector3 old = baseplayer->lastSentTick()->tick_position();
			//	Vector3 vector4 = (baseplayer->transform()->position() - baseplayer->lastSentTick()->tick_position());
			//	
			///*	bool dont_move = false;
			//	if (vars::misc::fly_auto_stopper) {
			//		Vector3 curr = baseplayer->transform()->position();
			//		Vector3 old = baseplayer->lastSentTick()->tick_position();
			//		Vector3 v4 = (curr - baseplayer->lastSentTick()->tick_position());
			//		Vector3 ov = Vector3(curr.x, curr.y , curr.z);

			//		if (VFlyhack >= 2.5f)
			//			ov = Vector3(ov.x, curr.y < old.y ? (curr.y - 0.3f) : old.y, ov.z);
			//		if (HFlyhack >= 6.f)
			//			ov = Vector3(old.x, ov.y, old.z);

			//		if (VFlyhack >= 2.5f
			//			|| HFlyhack >= 6.f) {
			//			if (ov != curr)
			//				baseplayer->movement()->TeleportTo(ov + Vector3(0, 0.5, 0));
			//			dont_move = true;
			//		}
			//	}*/
			//	//if (vars::misc::fly_auto_stopper && VFlyhack >= (VMaxFlyhack - 2.3f) && !GetAsyncKeyState(vars::keys::ignore_stopper)) {
			//	//	overrided = Vector3(overrided.x, current.y < old.y ? (current.y - 0.3f) : old.y, overrided.z);
			//	//}
			//	//if (vars::misc::fly_auto_stopper && HFlyhack >= (HMaxFlyhack - 2.3f) && !GetAsyncKeyState(vars::keys::ignore_stopper)) {
			//	//	overrided = Vector3(old.x, overrided.y, old.z);
			//	//}
			//	//if (vars::misc::fly_auto_stopper && !GetAsyncKeyState(vars::keys::ignore_stopper) && HFlyhack >= (HMaxFlyhack - 2.3f) || vars::misc::fly_auto_stopper && !GetAsyncKeyState(vars::keys::ignore_stopper) && VFlyhack >= (VMaxFlyhack - 2.3f)) {
			//	//	if (overrided != current);
			//	//	baseplayer->movement()->TeleportTo(back);
			//	//	/*baseplayer->movement()->TeleportTo(overrided);*/
			//	//}
			//	if (vars::misc::bhop && GetAsyncKeyState(vars::keys::bhop) || vars::misc::bhop && vars::keys::bhop == 0) {
			//		static float b = 4.0f;
			//		if (b >= 4.0f) {
			//			float radius = baseplayer->GetRadius();
			//			float height = baseplayer->GetHeight(false);
			//			Vector3 vector = (baseplayer->lastSentTick()->tick_position() + baseplayer->transform()->position()) * 0.5f;
			//			float flyhack_extrusion = 0.25f;
			//			Vector3 vector2 = vector + Vector3(0.0f, radius - flyhack_extrusion, 0.0f);
			//			Vector3 vector3 = vector + Vector3(0.0f, height - radius, 0.0f);
			//			float radius2 = radius - 0.05f;
			//			bool isgrounded = GamePhysics::CheckCapsule(vector2, vector3, radius2, 1503731969, GamePhysics::QueryTriggerInteraction::Ignore);
			//			if (isgrounded) {
			//				baseplayer->movement()->Jump(baseplayer->modelState());
			//				b = 0.0f;
			//			}
			//		}
			//		b++;
			//	}
			//	if (vars::misc::farmbot && vars::misc::jumpfarm) {
			//		static float b = 4.0f;
			//		if (b >= 4.0f) {
			//			float radius = baseplayer->GetRadius();
			//			float height = baseplayer->GetHeight(false);
			//			Vector3 vector = (baseplayer->lastSentTick()->tick_position() + baseplayer->transform()->position()) * 0.5f;
			//			float flyhack_extrusion = 0.25f;
			//			Vector3 vector2 = vector + Vector3(0.0f, radius - flyhack_extrusion, 0.0f);
			//			Vector3 vector3 = vector + Vector3(0.0f, height - radius, 0.0f);
			//			float radius2 = radius - 0.05f;
			//			bool isgrounded = GamePhysics::CheckCapsule(vector2, vector3, radius2, 1503731969, GamePhysics::QueryTriggerInteraction::Ignore);
			//			if (isgrounded) {
			//				baseplayer->movement()->Jump(baseplayer->modelState());
			//				b = 0.0f;
			//			}
			//		}
			//		b++;
			//	}
			//}
			return original_sendclienttick(baseplayer);
		}

		void DoFixedUpdate(PlayerWalkMovement* movement, ModelState* modelstate) {
			float speed = (read(movement + 0x143, bool) /*swimming*/ || read(movement + 0x50, float) /* ducked */ > 0.5f) ? 1.7f : (read(movement + 0x145, bool) /*jumping*/ ? 8.f : 5.5f);
			/*	if (vars::misc::farmbot) {
					if (vars::misc::farmbot_trees) {
						Vector3 vel = read(movement + 0x34, Vector3);
						f_object closest = f_object::get_closest_object(LocalPlayer::Entity()->GetBoneByID(head), xorstr_("tree"));
						if (closest.valid) {
							Vector3 direction = (closest.position - LocalPlayer::Entity()->GetBoneByID(head)).Normalized() * speed;
							write(movement + 0x34, Vector3(direction.x, vel.y, direction.z), Vector3);
						}
					}
					if (vars::misc::farmbot_ore) {
						Vector3 vel = read(movement + 0x34, Vector3);
						f_object closest = f_object::get_closest_object(LocalPlayer::Entity()->GetBoneByID(head), xorstr_("ore.prefab"));
						if (closest.valid) {
							Vector3 direction = (closest.position - LocalPlayer::Entity()->GetBoneByID(head)).Normalized() * speed;
							write(movement + 0x34, Vector3(direction.x, vel.y, direction.z), Vector3);
						}
					}
					if (vars::misc::farmbot_barrels) {
						Vector3 vel = read(movement + 0x34, Vector3);
						f_object closest = f_object::get_closest_object(LocalPlayer::Entity()->GetBoneByID(head), xorstr_("barrel"));
						if (closest.valid) {
							Vector3 direction = (closest.position - LocalPlayer::Entity()->GetBoneByID(head)).Normalized() * speed;
							write(movement + 0x34, Vector3(direction.x, vel.y, direction.z), Vector3);
						}
					}
				}*/


				//if (!movement->flying()) {
				//	Vector3 vel = movement->TargetMovement();
				//	if (vars::combat::manipulator && GetAsyncKeyState(vars::keys::manipulated_key)) {
				//		float max_speed = (movement->swimming() || movement->Ducking() > 0.5) ? 1.7f : 5.5f;
				//		if (vel.length() > 0.f) {
				//			movement->TargetMovement() = Vector3::Zero();
				//		}
				//	}
				//}

			original_dofixedupdate(movement, modelstate);
		}

		void ClientInput(BasePlayer* baseplayah, ModelState* ModelState) {
			vars::stuff::anti_aim_ = yeet;
			if (!baseplayah) return original_clientinput(baseplayah, ModelState);
			if (!baseplayah->IsValid()) return original_clientinput(baseplayah, ModelState);

			auto* TargetPlayer = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer);
			Vector3 startPos = LocalPlayer::Entity()->GetBoneByID(head);
			Vector3 endPos = ((BasePlayer*)TargetPlayer)->GetBoneByID(head);
			if (vars::visuals::hand_chams_type == 0 || vars::players::chams_type == 0) {
				static auto bundle = AssetBundle::LoadFromFile(xorstr_("C:\\Satanic\\circuit.bundle"));
				chamsShader = bundle->LoadAsset<Shader>(xorstr_("nebnel"), Type::GetType(xorstr_("UnityEngine.Shader, UnityEngine.CoreModule")));
			}

			static auto asset = AssetBundle::LoadFromFile(xorstr_("C:\\Satanic\\rust.assets"));
			if (vars::visuals::hand_chams_type == 1 || vars::players::chams_type == 1) {
				wireframe = asset->LoadAsset<Shader>(xorstr_("WireframeTransparent"), Type::GetType(xorstr_("UnityEngine.Shader, UnityEngine.CoreModule")));
			}
			if (vars::visuals::hand_chams_type == 2 || vars::players::chams_type == 2) {
				settrought = asset->LoadAsset<Shader>(xorstr_("SeethroughShader"), Type::GetType(xorstr_("UnityEngine.Shader, UnityEngine.CoreModule")));
			}
			if (vars::visuals::hand_chams_type == 3 || vars::players::chams_type == 3) {
				list_shader = asset->LoadAsset<Shader>(xorstr_("chamslit"), Type::GetType(xorstr_("UnityEngine.Shader, UnityEngine.CoreModule")));
			}
			if (vars::visuals::hand_chams_type == 4 || vars::players::chams_type == 4) {
				huy = asset->LoadAsset<Shader>(xorstr_("Chams"), Type::GetType(xorstr_("UnityEngine.Shader, UnityEngine.CoreModule")));
			}


			float desyncTime1 = (Time::realtimeSinceStartup() - baseplayah->lastSentTickTime()) - 0.03125 * 3;
			desync_time = desyncTime1;


			if (vars::combat::manipulator && GetAsyncKeyState(vars::keys::manipulated_key))
				baseplayah->clientTickInterval() = 0.99f;
			else {
				baseplayah->clientTickInterval() = 0.05f;
			}
			if (vars::combat::followprojectile
				&& proj
				&& !projv->isAlive())
				proj = false;
			if (vars::combat::manipulator && GetAsyncKeyState(vars::keys::manipulated_key)) {
				other::find_manipulate_angle();
			}
			else if (!other::m_manipulate.empty()) {
				other::m_manipulate = Vector3::Zero();
			}

			if (vars::misc::rayleigh_changer) {
				reinterpret_cast<void(__fastcall*)(float)>(vars::stor::gBase + CO::set_rayleigh)(vars::misc::rayleigh);
			}
			else {
				reinterpret_cast<void(__fastcall*)(float)>(vars::stor::gBase + CO::set_rayleigh)(vars::misc::rayleigh);
			}
			if (vars::misc::mie_changer) {
				reinterpret_cast<void(__fastcall*)(float)>(vars::stor::gBase + CO::set_mie)(vars::misc::mie);
			}
			else {
				reinterpret_cast<void(__fastcall*)(float)>(vars::stor::gBase + CO::set_mie)(vars::misc::mie);
			}
			if (vars::misc::Дождь) {
				reinterpret_cast<void(__fastcall*)(float)>(vars::stor::gBase + CO::Set_rain)(1); // weather set_rain
			}
			else {
				reinterpret_cast<void(__fastcall*)(float)>(vars::stor::gBase + CO::Set_rain)(0);
			}
			//if (vars::misc::шторм) {
			//	reinterpret_cast<void(__fastcall*)(float)>(vars::stor::gBase + CO::set_storm_chance)(1); // weather set_storm_chance
			//}
			//else {
			//	reinterpret_cast<void(__fastcall*)(float)>(vars::stor::gBase + CO::set_storm_chance)(0);
			//}
			//if (vars::misc::туман) {
			//	reinterpret_cast<void(__fastcall*)(float)>(vars::stor::gBase + CO::set_fog_chance)(1); // weather set_fog_chance
			//}
			//else {
			//	reinterpret_cast<void(__fastcall*)(float)>(vars::stor::gBase + CO::set_fog_chance)(0);
			//}
			if (vars::misc::brightness_changer) {
				reinterpret_cast<void(__fastcall*)(float)>(vars::stor::gBase + CO::set_brightness)(vars::misc::brightness);
			}
			else {
				reinterpret_cast<void(__fastcall*)(float)>(vars::stor::gBase + CO::set_brightness)(vars::misc::brightness);
			}

			typedef void(__stdcall* oxunem)(float);
			if (vars::misc::speedhack && GetAsyncKeyState(vars::keys::speedkey)) {
				oxunem Infinity = (oxunem)(vars::stor::gBase + CO::set_timeScale);
				Infinity(2);
			}
			else {
				oxunem Infinity = (oxunem)(vars::stor::gBase + CO::set_timeScale);
				Infinity(1);
			}

			if (vars::misc::mass_suicide) {
				LocalPlayer::Entity()->OnLand(-108.0001f);
			}
			//if (vars::misc::Sphera) {
			//	DDraw::Line(baseplayah->_playerModel()->position() , LocalPlayer::Entity()->lookingAtPoint(), Color(255, 255, 255, 255), 2.f, false, false);
			////	DDraw::Sphere(LocalPlayer::Entity()->lookingAtPoint(), 0.05f, Color(0, 136, 255, 1), 0.05f, 3);
			//}
			if (vars::misc::movement_line) {
				if (baseplayah->get_flag(PlayerFlags::Connected)) {
					DDraw::Line(baseplayah->_playerModel()->position() + Vector3(0, 0.15, 0), baseplayah->lastSentTick()->__position() + Vector3(0, 0.15, 0), Color(255, 255, 255, 255), 2.f, false, false);
					DDraw::Line(baseplayah->_playerModel()->position() + Vector3(0, 0.10, 0), baseplayah->lastSentTick()->__position() + Vector3(0, 0.10, 0), Color(0, 0, 255, 255), 2.f, false, false);
					DDraw::Line(baseplayah->_playerModel()->position() + Vector3(0, 0.05, 0), baseplayah->lastSentTick()->__position() + Vector3(0, 0.05, 0), Color(255, 0, 0, 255), 2.f, false, false);
				}
				else {}
			}

			if (vars::misc::flyhack_indicator) {
				CheckFlyhack();
			}

			auto held = baseplayah->GetHeldEntity<BaseProjectile>();
			BaseProjectile* _held = held = baseplayah->GetHeldEntity<BaseProjectile>();

			float lastShotTime = _held->lastShotTime() - GLOBAL_TIME;
			float reloadTime = _held->nextReloadTime() - GLOBAL_TIME;

			float desyncpercentage;
			float desyncTime = (Time::realtimeSinceStartup() - baseplayah->lastSentTickTime()) - 0.03125 * 3;
			desyncpercentage = ((desyncTime / 0.99f) * 100.0f) + 1.f;
			variables::manipulator::desync = (0.1f + (((desyncTime)+2.f / 60.f + 0.125f) * 1.5f) * baseplayah->GetMaxSpeed()) - 0.05f;

			if (_held && _held != nullptr && _held->class_name_hash() == STATIC_CRC32("BaseProjectile") ||
				_held && _held != nullptr && _held->class_name_hash() == STATIC_CRC32("BowWeapon") ||
				_held && _held != nullptr && _held->class_name_hash() == STATIC_CRC32("CrossBowWeapon")) {
				if (vars::combat::autoreload && _held)
				{
					BaseProjectile* ent = baseplayah->GetHeldEntity<BaseProjectile>();

					if (!did_reload)
						time_since_last_shot = (Time::fixedTime() - fixed_time_last_shot);

					if (just_shot && (time_since_last_shot > 0.2f))
					{
						ent->_ServerRPC(xorstr_("StartReload"));
						ent->SendSignalBroadcast(BaseEntity::Signal::Reload);
						just_shot = false;
					}
					if (time_since_last_shot > (_held->reloadTime() - (_held->reloadTime() / 10))
						&& !did_reload)
					{
						ent->_ServerRPC(xorstr_("Reload"));
						did_reload = true;
						time_since_last_shot = 0;
					}
				}
			}
			else {
				did_reload = false;
				just_shot = true;
				fixed_time_last_shot = Time::fixedTime();
			}

			if (baseplayah->userID() == LocalPlayer::Entity()->userID()) {
				if (LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1588298435 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -778367295 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -1367281941 ||
					LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -765183617 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -41440462 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 795371088 ||
					LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -75944661 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1965232394 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 884424049 ||
					LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1443579727 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1318558775 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1796682209 ||
					LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 649912614 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 818877484 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -852563019 ||
					LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1373971859 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -1758372725 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -1812555177 ||
					LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -904863145 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1545779598 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -1335497659 ||
					LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -2069578888 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -1214542497 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 28201841 ||
					LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1953903201 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 785728077) {
					if (vars::combat::desync_autoshoot_type == 0) {
						if (vars::combat::autoshoot) {
							if (vars::combat::autoshoot_type == 0) {
								if (!held->Empty()) {
									if (_held && reloadTime < 1.f) {
										if (lastShotTime < -0.1f) {
											if (reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer) != nullptr && !LocalPlayer::Entity()->is_teammate(reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)) && reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->IsValid() && baseplayah->get_flag(PlayerFlags::Connected)/* && !did_reload*/) {
												if (utils::LineOfSight(reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->GetBoneByID(head), baseplayah->eyes()->position())) {
													Item* weapon = LocalPlayer::Entity()->GetActiveWeapon();
													DWORD64 active = weapon->entity();
													//	reinterpret_cast<void(*)(uintptr_t, Signal, Str)>(vars::stor::gBase + CO::SendSignalBroadcast)(active, Signal::Attack, Str(xorstr_(L"")));
													_held->LaunchProjectile();
													_held->primaryMagazine()->contents()--;
													_held->UpdateAmmoDisplay();
													_held->ShotFired();
													_held->DidAttackClientside();
													_held->BeginCycle();
												}
											}
										}
									}
								}
							}
						}

						if (vars::combat::autoshoot) {
							if (vars::combat::autoshoot_type == 1) {
								if (!held->Empty() && held->class_name_hash() == STATIC_CRC32("BaseProjectile")) {
									if (reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer) != nullptr) {

										Vector3 target = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->GetBoneByID(head);

										if (utils::LineOfSight(target, baseplayah->eyes()->position()))
										{
											Item* weapon = LocalPlayer::Entity()->GetActiveWeapon();
											DWORD64 active = weapon->entity();
											//reinterpret_cast<void(*)(uintptr_t, Signal, Str)>(vars::stor::gBase + CO::SendSignalBroadcast)(active, Signal::Attack, Str(xorstr_(L"")));
											held->UpdateAmmoDisplay();
											held->DoAttack();
										}
									}
								}
							}
						}
					}

					if (vars::combat::desync_autoshoot_type == 1) {
						if (vars::combat::autoshoot && vars::combat::manipulator && GetAsyncKeyState(vars::keys::manipulated_key)) {
							if (vars::combat::autoshoot_type == 0) {
								if (!held->Empty()) {
									if (_held && reloadTime < 1.f) {
										if (lastShotTime < -0.1f) {
											if (reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer) != nullptr && !LocalPlayer::Entity()->is_teammate(reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)) && reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->IsValid() && baseplayah->get_flag(PlayerFlags::Connected)/* && !did_reload*/) {
												if (utils::LineOfSight(reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->GetBoneByID(head), baseplayah->eyes()->position())) {
													Item* weapon = LocalPlayer::Entity()->GetActiveWeapon();
													DWORD64 active = weapon->entity();
													//reinterpret_cast<void(*)(uintptr_t, Signal, Str)>(vars::stor::gBase + CO::SendSignalBroadcast)(active, Signal::Attack, Str(xorstr_(L"")));
													_held->LaunchProjectile();
													_held->primaryMagazine()->contents()--;
													_held->UpdateAmmoDisplay();
													_held->ShotFired();
													_held->DidAttackClientside();
													_held->BeginCycle();
												}
											}
										}
									}
								}
							}
						}


					}


					if (vars::combat::instakill && GetAsyncKeyState(vars::keys::instakill)) {
						if (vars::combat::instakill_type == 0) {
							if (!held->Empty()) {
								if (reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer) != nullptr && !LocalPlayer::Entity()->is_teammate(reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)) && reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->IsValid() && baseplayah->get_flag(PlayerFlags::Connected)/* && !did_reload*/) {
									if (utils::LineOfSight(reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->GetBoneByID(head), baseplayah->eyes()->position())) {
										baseplayah->clientTickInterval() = 0.99f;
										if (desyncTime > 0.80f) {
											Item* weapon = LocalPlayer::Entity()->GetActiveWeapon();
											DWORD64 active = weapon->entity();
											//	reinterpret_cast<void(*)(uintptr_t, Signal, Str)>(vars::stor::gBase + CO::SendSignalBroadcast)(active, Signal::Attack, Str(xorstr_(L"")));
											_held->LaunchProjectile();
											_held->primaryMagazine()->contents()--;
											_held->UpdateAmmoDisplay();
											_held->ShotFired();
											_held->DidAttackClientside();
											_held->BeginCycle();
										}
									}
								}
							}
						}
					}

					if (vars::combat::instakill && GetAsyncKeyState(vars::keys::instakill)) {
						if (vars::combat::instakill_type == 1) {
							if (!held->Empty() && held->class_name_hash() == STATIC_CRC32("BaseProjectile")) {
								if (reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer) != nullptr && !LocalPlayer::Entity()->is_teammate(reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)) && reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->IsValid() && baseplayah->get_flag(PlayerFlags::Connected)/* && !did_reload*/) {
									if (utils::LineOfSight(reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->GetBoneByID(head), baseplayah->eyes()->position())) {
										baseplayah->clientTickInterval() = 0.99f;
										if (desyncTime > 0.80f) {
											Item* weapon = LocalPlayer::Entity()->GetActiveWeapon();
											DWORD64 active = weapon->entity();
											//	reinterpret_cast<void(*)(uintptr_t, Signal, Str)>(vars::stor::gBase + CO::SendSignalBroadcast)(active, Signal::Attack, Str(xorstr_(L"")));
											held->DoAttack();
											held->UpdateAmmoDisplay();
										}
									}
								}
							}
						}
					}
				}
			
				if (vars::weapons::dobltap)
				{
					switch (vars::weapons::dobltapvalue)
					{
					case 0:
						break;
					case 1: //basic

						if (desyncTime1 > ((held->repeatDelay() * 0.9f) * 2.0f))
						{
							held->LaunchProjectile();
							if (held->primaryMagazine()->contents() > 0)
							{
								held->LaunchProjectile();
								held->primaryMagazine()->contents()--;
								held->UpdateAmmoDisplay();
								held->ShotFired();
								held->DidAttackClientside();
							}
							hk::misc::SendClientTick(LocalPlayer::Entity());
							return;
						}

						break;
					case 2: //smart
						float f = desyncTime1 / (held->repeatDelay() * 0.9f);
						int z = (int)f;


						for (size_t i = 0; i < (z > 9 ? 9 : (z < 0 ? 0 : z)); i++)
							if (held->primaryMagazine()->contents() > 0)
							{
								held->LaunchProjectile();
								held->primaryMagazine()->contents()--;
								held->UpdateAmmoDisplay();
								held->ShotFired();
								held->DidAttackClientside();
							}

						if (z <= 0)
							held->LaunchProjectile();

						hk::misc::SendClientTick(LocalPlayer::Entity());
						return;
					}
				}

				if (vars::misc::gesture_spam)
				{
					switch (vars::misc::gesture_spam) {
					case 0:
						break;
					case 1:
						reinterpret_cast<BaseProjectile*>(LocalPlayer::Entity())->SendSignalBroadcast(BaseEntity::Signal::Gesture, ("clap"));
						break;
					case 2:
						reinterpret_cast<BaseProjectile*>(LocalPlayer::Entity())->SendSignalBroadcast(BaseEntity::Signal::Gesture, ("friendly"));
						break;
					case 3:
						reinterpret_cast<BaseProjectile*>(LocalPlayer::Entity())->SendSignalBroadcast(BaseEntity::Signal::Gesture, ("thumbsdown"));
						break;
					case 4:
						reinterpret_cast<BaseProjectile*>(LocalPlayer::Entity())->SendSignalBroadcast(BaseEntity::Signal::Gesture, ("thumbsup"));
						break;
					case 5:
						reinterpret_cast<BaseProjectile*>(LocalPlayer::Entity())->SendSignalBroadcast(BaseEntity::Signal::Gesture, ("ok"));
						break;
					case 6:
						reinterpret_cast<BaseProjectile*>(LocalPlayer::Entity())->SendSignalBroadcast(BaseEntity::Signal::Gesture, ("point"));
						break;
					case 7:
						reinterpret_cast<BaseProjectile*>(LocalPlayer::Entity())->SendSignalBroadcast(BaseEntity::Signal::Gesture, ("shrug"));
						break;
					case 8:
						reinterpret_cast<BaseProjectile*>(LocalPlayer::Entity())->SendSignalBroadcast(BaseEntity::Signal::Gesture, ("victory"));
						break;
					case 9:
						reinterpret_cast<BaseProjectile*>(LocalPlayer::Entity())->SendSignalBroadcast(BaseEntity::Signal::Gesture, ("wave"));
						break;
					case 10:
						reinterpret_cast<BaseProjectile*>(LocalPlayer::Entity())->SendSignalBroadcast(BaseEntity::Signal::Gesture, ("dance.cabbagepatch"));
						break;
					case 11:
						reinterpret_cast<BaseProjectile*>(LocalPlayer::Entity())->SendSignalBroadcast(BaseEntity::Signal::Gesture, ("dance.twist"));
						break;
					}

				}
				if (vars::misc::local_bones)
				{
					//DDraw::Line(localPlayer->eyes( )->get_position( ), ret->hitPositionWorld( ), Color(1, 0, 0, 1), 0.05f, false, true);
					DDraw::Sphere(last_head_pos, 0.05f, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false); //head
					DDraw::Line(last_head_pos, last_neck_pos, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false, true);

					DDraw::Line(last_neck_pos, last_spine4_pos, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false, true);

					DDraw::Sphere(last_spine4_pos, 0.05f, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.05f, false); //
					DDraw::Line(last_spine4_pos, last_spine1_pos, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false, true);
					DDraw::Line(last_spine4_pos, last_l_upperarm_pos, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false, true);
					DDraw::Line(last_spine4_pos, last_r_upperarm_pos, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false, true);

					DDraw::Sphere(last_spine1_pos, 0.05f, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false); //
					DDraw::Line(last_spine1_pos, last_pelvis_pos, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false, true);
					DDraw::Line(last_spine1_pos, last_l_upperarm_pos, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false, true);
					DDraw::Line(last_spine1_pos, last_r_upperarm_pos, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false, true);

					DDraw::Sphere(last_l_upperarm_pos, 0.05f, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false); //
					DDraw::Line(last_l_upperarm_pos, last_l_forearm_pos, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false, true);

					DDraw::Sphere(last_l_forearm_pos, 0.05f, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false); //
					DDraw::Line(last_l_forearm_pos, last_l_hand_pos, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false, true);

					DDraw::Sphere(last_l_hand_pos, 0.05f, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false); //

					DDraw::Sphere(last_r_upperarm_pos, 0.05f, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false); //
					DDraw::Line(last_r_upperarm_pos, last_r_forearm_pos, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false, true);

					DDraw::Sphere(last_r_forearm_pos, 0.05f, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false); //
					DDraw::Line(last_r_forearm_pos, last_r_hand_pos, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false, true);

					DDraw::Sphere(last_r_hand_pos, 0.05f, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false); //

					DDraw::Sphere(last_pelvis_pos, 0.05f, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false); //
					DDraw::Line(last_pelvis_pos, last_l_knee_pos, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false, true);
					DDraw::Line(last_pelvis_pos, last_r_knee_pos, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false, true);

					DDraw::Sphere(last_l_knee_pos, 0.05f, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false); //
					DDraw::Line(last_l_knee_pos, last_l_foot_pos, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false, true);

					DDraw::Sphere(last_l_foot_pos, 0.05f, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false); //

					DDraw::Sphere(last_r_knee_pos, 0.05f, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false); //
					DDraw::Line(last_r_knee_pos, last_r_foot_pos, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false, true);

					DDraw::Sphere(last_r_foot_pos, 0.05f, Color(vars::colors::local_bones.x, vars::colors::local_bones.y, vars::colors::local_bones.z, 255), 0.02f, false); //
				}
				//if (vars::visuals::sphere) {
				//	RaycastHit hitInfo;
				//	Quaternion q;
				//	bool validCol = RaycastHit::RayCapsule(LocalPlayer::Entity()->eyes()->get_position(), LocalPlayer::Entity()->eyes()->BodyForward(), &hitInfo, 400.f, 256 || 2048 || 65536 || 8388608 || 16777216 || 33554432 || 67108864 || 1073741824);
				//	if (validCol) {
				//		DDraw::Capsule(hitInfo.point, q, 0.5f, 2 * 0.5f, Color(0.f, 1.f, 0.f, 255.f), 0.01f, false);
				//	}
				//}


				static bool alreadystartedReload = false;

				static bool alreadyReset = false;
				if (vars::combat::desync)
				{
					alreadyReset = false;
					static int updownleft = 0;
					static bool waspressed = false;
					if (vars::keys::PressedKeys[VK_DELETE])
					{
						waspressed = true;
					}

					if (!vars::keys::PressedKeys[VK_DELETE] && waspressed)
					{
						waspressed = false;
						updownleft += 1;
						if (updownleft > 3)
						{
							updownleft = 0;
						}
					}
				}
				if (vars::combat::desync && GetAsyncKeyState(vars::keys::desync)) {
					static int updownleft = 0;
					float desyncTime = (Time::realtimeSinceStartup() - baseplayah->lastSentTickTime()) - 0.03125 * 3;
					float max_eye_value = (0.1f + ((desyncTime + 2.f / 60.f + 0.125f) * 1.5f) * baseplayah->MaxVelocity()) - 0.05f;
					baseplayah->clientTickInterval() = 1.f;

					if (updownleft == 0)
					{
						baseplayah->eyes()->viewOffset().y = max_eye_value;
					}
				}

				if (vars::weapons::compound && held->class_name_hash() == STATIC_CRC32("CompoundBowWeapon")) {
					reinterpret_cast<CompoundBowWeapon*>(held)->currentHoldProgress() = 1.5f;
				}

				GLOBAL_TIME = Time::time();
			}

			Item* weapon = LocalPlayer::Entity()->GetActiveWeapon();
			DWORD64 active = weapon->entity();
			char* classname = weapon->ClassName();
			bool weaponmelee = weapon && classname && (strcmp(classname, xorstr_("BaseMelee")) || strcmp(classname, xorstr_("Jackhammer")));
			if (active && vars::misc::weapon_spam) {
				if (GetAsyncKeyState(vars::keys::weaponspam)) {
					reinterpret_cast<void(*)(uintptr_t, Signal, Str)>(vars::stor::gBase + CO::SendSignalBroadcast)(active, Signal::Attack, Str(xorstr_(L"")));
				}
			}
			if (vars::stor::meme_target != NULL) {
				if (!reinterpret_cast<BasePlayer*>(vars::stor::meme_target)->IsValid()) {
					vars::stor::meme_target = NULL;
				}
				if (LocalPlayer::Entity()->is_teammate(reinterpret_cast<BasePlayer*>(vars::stor::meme_target))) {
					vars::stor::meme_target = NULL;
				}
				if (reinterpret_cast<BasePlayer*>(vars::stor::meme_target)->health() <= 0.f) {
					vars::stor::meme_target = NULL;
				}
			}
			//if (vars::misc::auto_pickup) {
			//	f_object entity = f_object::get_closest_object(LocalPlayer::Entity()->GetBoneByID(head),
			//		xorstr_("/collectable/"),
			//		Vector3::Zero(),
			//		Vector3::Zero(),
			//		Vector3::Zero(),
			//		false
			//	);
			//	if (entity.valid) {
			//		Vector3 local = utils::ClosestPoint(LocalPlayer::Entity(), entity.position);
			//		if (Math::Distance_3D(local, entity.position) < 3.f) {
			//			if (reinterpret_cast<BaseEntity*>(entity.entity)->IsValid()) {
			//				utils::ServerRPC(entity.entity, Str(xorstr_(L"Pickup")));
			//			}
			//		}
			//	}
			//}
			//if (vars::misc::auto_grade) {
			//	f_object building_block = f_object::get_closest_object(LocalPlayer::Entity()->GetBoneByID(head),
			//		xorstr_(""),
			//		Vector3::Zero(),
			//		Vector3::Zero(),
			//		Vector3::Zero(),
			//		true,
			//		xorstr_("BuildingBlock"));
			//	if (building_block.valid) {
			//		Vector3 local = utils::ClosestPoint(LocalPlayer::Entity(), building_block.position);
			//		if (Math::Distance_3D(local, building_block.position) <= 2.f) {
			//			if (reinterpret_cast<BaseEntity*>(building_block.entity)->IsValid()) {
			//				lol::auto_grade(building_block.entity);
			//			}
			//		}
			//	}
			//}
		/*	if (vars::misc::auto_farm) {
				if (vars::misc::auto_farm_barrel || vars::misc::farmbot_barrels) {
					if (weaponmelee) {
						f_object ore_hot_spot = f_object::get_closest_object(LocalPlayer::Entity()->GetBoneByID(head),
							xorstr_("barrel"),
							Vector3::Zero(),
							Vector3::Zero(),
							Vector3::Zero(),
							false,
							xorstr_(""));
						if (ore_hot_spot.valid) {
							Vector3 local = utils::ClosestPoint(LocalPlayer::Entity(), ore_hot_spot.position);
							if (Math::Distance_3D(local, ore_hot_spot.position) <= 2.f) {
								if (reinterpret_cast<BaseEntity*>(ore_hot_spot.entity)->IsValid()) {
									lol::do_attack(ore_hot_spot, active, false);
								}
							}
						}
					}
				}
				if (vars::misc::auto_farm_ore || vars::misc::farmbot_ore) {
					if (weaponmelee) {
						f_object ore_hot_spot = f_object::get_closest_object(LocalPlayer::Entity()->GetBoneByID(head),
							xorstr_(""),
							Vector3::Zero(),
							Vector3::Zero(),
							Vector3::Zero(),
							true,
							xorstr_("OreHotSpot"));
						if (ore_hot_spot.valid) {
							Vector3 local = utils::ClosestPoint(LocalPlayer::Entity(), ore_hot_spot.position);
							if (Math::Distance_3D(local, ore_hot_spot.position) <= 2.f) {
								if (reinterpret_cast<BaseEntity*>(ore_hot_spot.entity)->IsValid()) {
									lol::do_attack(ore_hot_spot, active, false);
								}
							}
						}
					}
				}
				if (vars::misc::auto_farm_tree) {
					if (weaponmelee) {
						f_object tree_entity = f_object::get_closest_object(LocalPlayer::Entity()->GetBoneByID(head),
							xorstr_(""),
							Vector3::Zero(),
							Vector3::Zero(),
							Vector3::Zero(),
							true,
							xorstr_("TreeEntity"));
						if (tree_entity.valid) {
							tree_entity.position = Vector3::Zero();
							f_object tree_marker = f_object::get_closest_object(LocalPlayer::Entity()->GetBoneByID(head),
								xorstr_(""),
								Vector3::Zero(),
								Vector3::Zero(),
								Vector3::Zero(),
								true,
								xorstr_("TreeMarker"));
							if (tree_marker.valid) {
								Vector3 locala = utils::ClosestPoint(LocalPlayer::Entity(), tree_marker.position);
								if (Math::Distance_3D(locala, tree_marker.position) <= 2.f) {
									tree_entity.position = tree_marker.position;
									Vector3 local = utils::ClosestPoint(LocalPlayer::Entity(), tree_entity.position);
									if (Math::Distance_3D(local, tree_entity.position) <= 2.f) {
										if (reinterpret_cast<BaseEntity*>(tree_entity.entity)->IsValid()) {
											lol::do_attack(tree_entity, active, false);
										}
									}
								}
							}
						}
					}
				}
			}*/
			//lol::auto_farm_loop(weaponmelee, active);
		//	game_thread_loop();
//if (vars::misc::auto_grade) {
//	f_object building_block = f_object::get_closest_object(LocalPlayer::Entity()->GetBoneByID(head),
//		xorstr_(""),
//		Vector3::Zero(),
//		Vector3::Zero(),
//		Vector3::Zero(),
//		true,
//		xorstr_("BuildingBlock"));
//	if (building_block.valid) {
//		Vector3 local = utils::ClosestPoint(LocalPlayer::Entity(), building_block.position);
//		if (Math::Distance_3D(local, building_block.position) <= 2.f) {
//			if (reinterpret_cast<BaseEntity*>(building_block.entity)->IsValid()) {
//				lol::auto_grade(building_block.entity);
//			}
//		}
//	}
//}
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
				DWORD64 ent = read(Object + 0x28, UINT64);
				if (!name) continue;
				char* buff = name->stub;
				BasePlayer* Player = (BasePlayer*)read(Object + 0x28, DWORD64);
				if (strstr(buff, xorstr_("Local"))) {
					BasePlayer* Player = (BasePlayer*)read(Object + 0x28, DWORD64);
					BasePlayer* Local = (BasePlayer*)read(Object + 0x28, DWORD64);
					if (!read(Player + O::BasePlayer::playerModel, DWORD64)) continue;

					/*lol::update_chams();
					chamslocal(Player);*/


					HandChams();
				}

			/*	if (strstr(buff, xorstr_("player.prefab")))
				{
					BasePlayer* Player = (BasePlayer*)read(Object + 0x28, DWORD64);
					BasePlayer* Local = (BasePlayer*)read(Object + 0x28, DWORD64);
					if (!read(Player + O::BasePlayer::playerModel, DWORD64)) continue;
					lol::update_chams();
					chams(Player);
				}*/
				if (!reinterpret_cast<BaseEntity*>(Entity)->IsValid()) { continue; }
				if (!reinterpret_cast<Component*>(Entity)->gameObject()) { continue; }
				if (strstr(buff, xorstr_("Local"))) { continue; }

				Item* weapon = LocalPlayer::Entity()->GetActiveWeapon();
				DWORD64 active = weapon->entity();
				char* classname = weapon->ClassName();

				bool weaponmelee = weapon && classname && (strcmp(classname, xorstr_("BaseMelee")) || strcmp(classname, xorstr_("Jackhammer")));
				if (reinterpret_cast<BaseCombatEntity*>(Entity)->IsPlayer()) {
					BasePlayer* lol = (BasePlayer*)Entity;

					if (!lol) continue;

			/*		if (vars::misc::auto_revive) {
						UINT64 gameObject = read(ObjectClass + 0x30, UINT64);
						Vector3 local = utils::ClosestPoint(LocalPlayer::Entity(), utils::GetEntityPosition(gameObject));
						if (vars::misc::auto_revive && (BasePlayer*)Entity && lol->get_flag(PlayerFlags::Wounded) && Math::Distance_3D(local, utils::GetEntityPosition(gameObject)) < 3.f && LocalPlayer::Entity()->GetKeyState(Button::USE)) {
							lol::pickup_player((BasePlayer*)Entity);
						}
					}*/
					if (vars::combat::silent_melee && weaponmelee && Math::Distance_3D(lol->GetBoneByID(head), LocalPlayer::Entity()->GetBoneByID(head)) <= vars::combat::reach) {
						f_object target = f_object::get_melee_target((BasePlayer*)Entity, active);
						lol::do_attack(target, active, true);
					}
				}



				if (vars::misc::auto_pickup && strstr(buff, xorstr_("/collectable/"))) {
					UINT64 gameObject = read(ObjectClass + 0x30, UINT64);
					Vector3 local = utils::ClosestPoint(LocalPlayer::Entity(), utils::GetEntityPosition(gameObject));
					if (Math::Distance_3D(local, utils::GetEntityPosition(gameObject)) < 3.f) {
						utils::ServerRPC(Entity, Str(xorstr_(L"Pickup")));
					}
				}
				if (vars::misc::annoyer && strstr((char*)read(read(Entity, DWORD64) + 0x10, DWORD64), xorstr_("Door"))) {
					UINT64 gameObject = read(ObjectClass + 0x30, UINT64);
					Vector3 local = utils::ClosestPoint(LocalPlayer::Entity(), utils::GetEntityPosition(gameObject));
					if (Entity && Math::Distance_3D(local, utils::GetEntityPosition(gameObject)) < 3.f) {
						lol::knocker(Entity);
					}
				}
			}
			if (vars::visuals::hand_chams) {
				auto oxunem = il2cpp::_init_class(xorstr_("Graphics"), xorstr_("ConVar"));
				auto static_fields = safe_read(oxunem + 0xb8, uintptr_t);
				safe_write(static_fields + 0x7D, false, bool);//public static bool viewModelCamera;
			}
		
			Physics::IgnoreLayerCollision((int)Layer::PlayerMovement, (int)Layer::Water, !vars::misc::walker);
			Physics::IgnoreLayerCollision((int)Layer::PlayerMovement, (int)Layer::Tree, vars::misc::walker);
			Physics::IgnoreLayerCollision((int)Layer::PlayerMovement, (int)Layer::AI, vars::misc::walker);

			weapon_set();
			misc_set();

			original_clientinput(baseplayah, ModelState);

			if (vars::misc::farmbot || vars::misc::egg_bot) {
				LocalPlayer::Entity()->add_modelstate_flag(ModelStateFlag::Sprinting);
			}

			if (vars::misc::modelstate == 0) {
			}
			if (vars::misc::modelstate == 1) {
				LocalPlayer::Entity()->add_modelstate_flag(ModelStateFlag::OnLadder);
			}
			if (vars::misc::modelstate == 2) {
				LocalPlayer::Entity()->add_modelstate_flag(ModelStateFlag::OnGround);
			}
			if (vars::misc::modelstate == 3) {
				LocalPlayer::Entity()->add_modelstate_flag(ModelStateFlag::Ducked);
			}
			if (vars::misc::modelstate == 4) {
				LocalPlayer::Entity()->add_modelstate_flag(ModelStateFlag::Sleeping);
			}
			if (vars::misc::modelstate == 5)
			{
				LocalPlayer::Entity()->add_modelstate_flag(ModelStateFlag::Sprinting);
			}
			if (vars::misc::modelstate == 6)
			{
				LocalPlayer::Entity()->add_modelstate_flag(ModelStateFlag::Flying);
			}
			if (vars::misc::modelstate == 6)
			{
				LocalPlayer::Entity()->add_modelstate_flag(ModelStateFlag::Aiming);
			}
			if (vars::misc::modelstate == 7)
			{
				LocalPlayer::Entity()->add_modelstate_flag(ModelStateFlag::Prone);
			}
			if (vars::misc::modelstate == 8)
			{
				LocalPlayer::Entity()->add_modelstate_flag(ModelStateFlag::Mounted);
			}
			if (vars::misc::modelstate == 9)
			{
				LocalPlayer::Entity()->add_modelstate_flag(ModelStateFlag::Relaxed);
			}
			if (vars::misc::modelstate == 10)
			{
				LocalPlayer::Entity()->add_modelstate_flag(ModelStateFlag::OnPhone);
			}

			if (vars::misc::omnidirectional_sprinting && !LocalPlayer::Entity()->get_flag(64)) {
				LocalPlayer::Entity()->add_modelstate_flag(ModelStateFlag::Sprinting);
			}

			if (vars::misc::interactive_debug && GetAsyncKeyState(vars::keys::debugging)) {
				BaseProjectile* ent = baseplayah->GetHeldEntity<BaseProjectile>();
				LocalPlayer::Entity()->add_modelstate_flag(ModelStateFlag::Mounted);
				ent->_ServerRPC(xorstr_("RPC_LootPlayer"));
			}
		}

		void UpdateAmbient(TOD_Sky* TOD_Sky) {
			uintptr_t cycle = read(TOD_Sky + 0x38, uintptr_t);
			uintptr_t ambient = read(TOD_Sky + 0x90, uintptr_t);
			if (vars::misc::night_stars) {
				uintptr_t stars = read(TOD_Sky + 0x70, uintptr_t);
				*(float*)(stars + 0x14) = vars::misc::stars;
			}
			if (vars::misc::облака) {
				uintptr_t stars = read(TOD_Sky + 0x78, uintptr_t);
				*(float*)(stars + 0x14) = vars::misc::облакафлоат / 1000;
			}
			
			if (!vars::misc::bright_ambient) {
				return original_updateambient(TOD_Sky);
			}
			RenderSettings::set_ambientMode(RenderSettings::AmbientMode::Flat);
			RenderSettings::set_ambientIntensity(6.f);
			RenderSettings::set_ambientLight(Color({ vars::colors::ambient_color.x, vars::colors::ambient_color.y, vars::colors::ambient_color.z, 1 }));
			//	RenderSettings::set_ambientSkyColor(Color({ vars::colors::sky_color.x, vars::colors::sky_color.y, vars::colors::sky_color.z, 1 }));
				//RenderSettings::set_ambientEquatorColor(Color({ vars::colors::equator_color.x, vars::colors::equator_color.y, vars::colors::equator_color.z, 1 }));
		}
		pUncStr Run(ConsoleOptions* options, pUncStr strCommand, DWORD64 args) {
			if (options->IsFromServer()) {
				std::wstring cmd = std::wstring(strCommand->str);
				if (cmd.find(xorstr_(L"noclip")) != std::wstring::npos || cmd.find(xorstr_(L"debugcamera")) != std::wstring::npos || cmd.find(xorstr_(L"camspeed")) != std::wstring::npos || cmd.find(xorstr_(L"admintime")) != std::wstring::npos) {
					strCommand = nullptr;
				}

			}
			return original_consolerun(options, strCommand, args);
		}
		void DoHitNotify(BaseCombatEntity* entity, HitInfo* info, Projectile* prj) {
			if (entity->IsPlayer()) {
				if (vars::misc::hit_logs) {
					std::stringstream ss;
					std::string string;
					BasePlayer* baseplayah;
					char buf[256] = { 0 }; sprintf_s(buf, xorstr_("[%ls's] in the %ls for %d damage"), reinterpret_cast<BasePlayer*>(entity)->_displayName(), utils::StringPool::Get(info->HitBone())->buffer, (int)info->damageTypes()->Total());
					string += buf;

					baseplayah->console_echo(stringe::wformat((L"[%ls's] in the %ls for %d damage"), reinterpret_cast<BasePlayer*>(entity)->_displayName(), utils::StringPool::Get(info->HitBone())->buffer, (int)info->damageTypes()->Total()));
					notify::add_log("Hit", string.c_str(), ImColor(130, 20, 20), ImColor(255, 255, 255), 4700);
				}

				if (vars::misc::custom_hitsound) {
					auto MiddleX = vars::stuff::ScreenWidth / 2;
					auto MiddleY = vars::stuff::ScreenHeight / 2;
					//	g_Render->DrawLine(10 + MiddleX, 10 + MiddleY, -10 + MiddleX, -10 + MiddleY, ImColor(255,255,255), 1.5f, true);
						//g_Render->DrawLine(-10 + MiddleX, 10  +  MiddleY, 10 + MiddleX, -10 + MiddleY, ImColor(255, 255, 255), 1.5f, true);
					if (vars::misc::hitsound_rejim == 0) {
						PlaySoundA((LPCSTR)head111, NULL, SND_MEMORY | SND_ASYNC);
					}
					if (vars::misc::hitsound_rejim == 1) {
						PlaySoundA((LPCSTR)MinecraftHit, NULL, SND_MEMORY | SND_ASYNC);
					}
					if (vars::misc::hitsound_rejim == 2) {
						PlaySoundA((LPCSTR)skeet, NULL, SND_MEMORY | SND_ASYNC);
					}
					if (vars::misc::hitsound_rejim == 3) {
						PlaySoundA((LPCSTR)Fatality, NULL, SND_MEMORY | SND_ASYNC);
					}
					if (vars::misc::hitsound_rejim == 4) {
						PlaySoundA((LPCSTR)crystal, NULL, SND_MEMORY | SND_ASYNC);
					}
					return;
				}

			}
			if (vars::misc::hitmaterial == 0) {
			}
			if (vars::misc::hitmaterial == 1) {
				uint32_t material = utils::StringPool::Get(xorstr_("glass"));
				info->HitMaterial() = material;
			}
			if (vars::misc::hitmaterial == 2) {
				uint32_t material = utils::StringPool::Get(xorstr_("water"));
				info->HitMaterial() = material;
			}
			if (vars::misc::hitmaterial == 3) {
				uint32_t material = utils::StringPool::Get(xorstr_("wood"));
				info->HitMaterial() = material;
			}
			if (vars::misc::hitmaterial == 4) {
				uint32_t material = utils::StringPool::Get(xorstr_("metal"));
				info->HitMaterial() = material;
			}
			if (vars::misc::hitmaterial == 5) {
				uint32_t material = utils::StringPool::Get(xorstr_("sand"));
				info->HitMaterial() = material;
			}
			if (vars::misc::hitmaterial == 6) {
				uint32_t material = utils::StringPool::Get(xorstr_("grass"));
				info->HitMaterial() = material;
			}
			if (vars::misc::hitmaterial == 7) {
				uint32_t material = utils::StringPool::Get(xorstr_("rock"));
				info->HitMaterial() = material;
			}
			if (vars::misc::hitmaterial == 8) {
				uint32_t material = utils::StringPool::Get(xorstr_("concrete"));
				info->HitMaterial() = material;
			}
			if (vars::misc::hitmaterial == 9) {
				uint32_t material = utils::StringPool::Get(xorstr_("forest"));
				info->HitMaterial() = material;
			}
			if (vars::misc::hitmaterial == 10) {
				uint32_t material = utils::StringPool::Get(xorstr_("cloth"));
				info->HitMaterial() = material;
			}
			if (vars::misc::hitmaterial == 11) {
				uint32_t material = utils::StringPool::Get(xorstr_("null"));
				info->HitMaterial() = material;
			}

			return original_dohitnotify(entity, info, prj);
		}
		bool get_isHeadshot(HitInfo* hitinfo) {
			if (vars::misc::custom_hitsound) {
				return false;
			}
			if (vars::combat::always_headshot) {
				return false;
			}
			return original_getisheadshot(hitinfo);
		}
		void Play(ViewModel* viewmodel, pUncStr name, int layer = 0) {
			if (vars::weapons::remove_attack_anim) {
				static auto ptr = METHOD("Assembly-CSharp::BaseProjectile::DoAttack(): Void");
				if (!CALLED_BY(0x6F40F0, 0x296) || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -75944661) {//ViewModel Play
					return original_viewmodelplay(viewmodel, name, layer);
				}
			}
			else {
				return original_viewmodelplay(viewmodel, name, layer);
			}
		}
	}
	namespace combat {
		float GetRandomVelocity(ItemModProjectile* mod) {
			return vars::weapons::fast_bullets ? original_getrandomvelocity(mod) * 1.699 : original_getrandomvelocity(mod); //1.499
		}
		void AddPunch(HeldEntity* a1, Vector3 a2, float duration) {
			if (vars::weapons::no_recoil) {
				a2 *= vars::weapons::recoil_control / 100.f;
			}
			return original_addpunch(a1, a2, duration);
		}
		Vector3 MoveTowards(Vector3 a1, Vector3 a2, float maxDelta) {
			static auto ptr = METHOD("Assembly-CSharp::BaseProjectile::SimulateAimcone(): Void");
			if (CALLED_BY(ptr, 0x800)) {
				if (vars::weapons::no_recoil) {
					a2 *= vars::weapons::recoil_control / 100.f;
					maxDelta *= vars::weapons::recoil_control / 100.f;
				}
			}
			return original_movetowards(a1, a2, maxDelta);
		}
		bool DoHit(Projectile* prj, HitTest* test, Vector3 point, Vector3 normal) {
			auto localPlayer = LocalPlayer::Entity();
			auto held = localPlayer->GetHeldEntity<BaseProjectile>();
			if (prj->isAuthoritative()) {
				if (vars::combat::ignore_team) {
					if (test->HitEntity() != null) {
						if (test->HitEntity()->IsValid()) {
							if (LocalPlayer::Entity()->is_teammate(reinterpret_cast<BasePlayer*>(test->HitEntity()))) {
								if (reinterpret_cast<BaseCombatEntity*>(test->HitEntity())->IsPlayer()) {
									return false;
								}
							}
						}
					}
				}

				//if (vars::misc::hitmarker) {
				//	if (test->HitEntity() != nullptr) {
				//		if (test->HitEntity()->IsValid()) {
				//			if (reinterpret_cast<BasePlayer*>(test->HitEntity())->IsPlayer()) {
				//				DDraw::Text(il2cpp::String::New("x"), prj->currentPosition(), Color(vars::colors::marker.x, vars::colors::marker.y, vars::colors::marker.z, 255), 1.5f);
				//			}
				//		}
				//	}
				//}
				if (vars::misc::bullet_tracers) {
					//	DDraw::Sphere(prj->previousPosition(), 0.05f, Color(1, 0, 0, 1), 1.5f, 10);
				//		DDraw::Sphere(prj->sentPosition(), 0.05f, Color(1, 0, 0, 1), 1.5f, 10);
					//DDraw::Line(localPlayer->eyes()->position(), prj->currentPosition(), Color(89, 227, 255, 89), 5.5f, false, true);
					DDraw::Line(localPlayer->eyes()->position(), prj->currentPosition(), Color(255, 255, 255, 255), 1.5f, true, false);
				}
				if (vars::combat::tree_reflect) {
					if (test->HitEntity() != null) {
						if (!reinterpret_cast<BaseCombatEntity*>(test->HitEntity())->IsPlayer()) {
							prj->penetrationPower(35.f);
						}
					}
				}
				if (vars::weapons::penetrate) {
					if (test->HitEntity() != null) {
						if (test->HitEntity()->IsValid()) {
							BaseCombatEntity* lol = reinterpret_cast<BaseCombatEntity*>(test->HitEntity());
							if (vars::stuff::testInt == 2) {
								printf(xorstr_("%s \n"), lol->ClassName());
							}
							if (lol->ClassNameHash() == STATIC_CRC32("CargoShip") || lol->ClassNameHash() == STATIC_CRC32("BaseOven")
								|| lol->ClassNameHash() == STATIC_CRC32("TreeEntity") || lol->ClassNameHash() == STATIC_CRC32("OreResourceEntity")
								|| lol->ClassNameHash() == STATIC_CRC32("CH47HelicopterAIController") || lol->ClassNameHash() == STATIC_CRC32("MiniCopter")
								|| lol->ClassNameHash() == STATIC_CRC32("BoxStorage") || lol->ClassNameHash() == STATIC_CRC32("Workbench")
								|| lol->ClassNameHash() == STATIC_CRC32("VendingMachine") || lol->ClassNameHash() == STATIC_CRC32("Barricade")
								|| lol->ClassNameHash() == STATIC_CRC32("BuildingPrivlidge") || lol->ClassNameHash() == STATIC_CRC32("LootContainer")
								|| lol->ClassNameHash() == STATIC_CRC32("HackableLockedCrate") || lol->ClassNameHash() == STATIC_CRC32("ResourceEntity")
								|| lol->ClassNameHash() == STATIC_CRC32("RidableHorse") || lol->ClassNameHash() == STATIC_CRC32("MotorRowboat")
								|| lol->ClassNameHash() == STATIC_CRC32("ScrapTransportHelicopter") || lol->ClassNameHash() == STATIC_CRC32("JunkPile")
								|| lol->ClassNameHash() == STATIC_CRC32("MiningQuarry") || lol->ClassNameHash() == STATIC_CRC32("WaterCatcher")) {
								return false;
							}
						}
					}
				}
			}
			return original_dohit(prj, test, point, normal);
		}
		void Launch(Projectile* prdoj) {
			if (vars::weapons::no_spread) {
				write(prdoj->mod() + 0x30, vars::weapons::no_spreadvalue / 100.f, float);
			}
			return original_launch(prdoj);
		}
		bool CanHoldItems(BaseMountable* a1) {
			if (vars::weapons::minicopter_aim) return true;
			return original_canholditems(a1);
		}
		void SendProjectileAttack(BasePlayer* a1, PlayerProjectileAttack* a2) {
			uintptr_t PlayerAttack = read(a2 + 0x18, uintptr_t); // PlayerAttack playerAttack;
			uintptr_t Attack = read(PlayerAttack + 0x18, uintptr_t); // public Attack attack;
			uint32_t hitID = read(Attack + 0x2C, uint32_t);
			if (vars::weapons::spoof_hitdistance) {
				write(a2 + 0x2C, vars::weapons::hitdistance, float);
			}
			return original_sendprojectileattack(a1, a2);
		}
		bool CanAttack(BasePlayer* a1) {
			if (vars::misc::can_attack)
				return true;
			return original_canattack(a1);
		}
		Projectile* CreateProjectile(BaseProjectile* BaseProjectileA, void* prefab_pathptr, Vector3 pos, Vector3 forward, Vector3 velocity) {
			Projectile* projectile = original_create_projectile(BaseProjectileA, prefab_pathptr, pos, forward, velocity);
			BasePlayer* TargetPlayer = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer);
			if (vars::weapons::local_scale) {
				projectile->transform()->set_scale({ vars::weapons::bullet_sizex, vars::weapons::bullet_sizey, vars::weapons::bullet_sizez });
			}
			if (vars::weapons::thick_bullet) {
				projectile->thickness(vars::weapons::thickness);
			}
			else {
				projectile->thickness(0.1f);
			}

			float desyncTime = (Time::realtimeSinceStartup() - LocalPlayer::Entity()->lastSentTickTime()) - 0.23125 * 3; //0.03125
			if (vars::combat::bullet_tp && !LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1443579727 || !LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 884424049 || !LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1965232394)
			{
				auto pos = MoveTowards(reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->GetBoneByID(head), BaseProjectileA->transform()->position(), 2.0f); //2
				auto d2t = LocalPlayer::Entity()->eyes()->get_position().distance(reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->GetBoneByID(head));

				projectile->initialDistance(d2t - 2.f); //1m then 2m? 3
				projectile->integrity(10.f);
				projectile->ricochetChance(1.f);

				magic_projectile_test = false;
			}
			else projectile->initialDistance(2.f); //1

			return projectile;
		}
		bool LineCircleIntersection1(Vector3 center,
			float radius,
			Vector3 rayStart,
			Vector3 rayEnd,
			float& offset)
		{
			Vector2 P(rayStart.x, rayStart.z);
			Vector2 Q(rayEnd.x, rayEnd.z);

			float a = Q.y - P.y;
			float b = P.x - Q.x;
			float c = (a * (P.x) + b * (P.y)) * -1.f;

			float x = center.x;
			float y = center.z;

			float c_x = (b * ((b * x) - (a * y)) - a * c) / (std::pow(a, 2) + std::pow(b, 2));
			float c_y = (a * ((-b * x) + (a * y)) - (b * c)) / (std::pow(a, 2) + std::pow(b, 2));

			Vector2 closestPoint(c_x, c_y);

			float distance = P.Distance(Q);

			if (P.Distance(closestPoint) > distance || Q.Distance(closestPoint) > distance)
			{
				return false;
			}

			if (radius > closestPoint.Distance(Vector2(center.x, center.z)))
			{
				Vector2 P(rayStart.x, rayStart.y);
				Vector2 Q(rayEnd.x, rayEnd.y);

				float a = Q.y - P.y;
				float b = P.x - Q.x;
				float c = (a * (P.x) + b * (P.y)) * -1.f;

				float x = center.x;
				float y = center.y;

				float c_x = (b * ((b * x) - (a * y)) - a * c) / (std::pow(a, 2) + std::pow(b, 2));
				float c_y = (a * ((-b * x) + (a * y)) - (b * c)) / (std::pow(a, 2) + std::pow(b, 2));

				Vector2 closestPoint(c_x, c_y);
				if (radius > closestPoint.Distance(Vector2(center.x, center.y)))
				{
					return true;
				}
				else
				{
					offset += std::fabs(center.y - closestPoint.y);
					return false;
				}
			}

			return false;
		};
		bool LineCircleIntersection(Vector3 center, float radius, Vector3 rayStart, Vector3 rayEnd, Vector3 direction, float& offset)
		{
			Vector2 P(rayStart.x, rayStart.z);
			Vector2 Q(rayEnd.x, rayEnd.z);

			float a = Q.y - P.y;
			float b = P.x - Q.x;
			float c = (a * (P.x) + b * (P.y)) * -1.f;

			float x = center.x;
			float y = center.z;

			float c_x = (b * ((b * x) - (a * y)) - a * c) / (std::pow(a, 2) + std::pow(b, 2));
			float c_y = (a * ((-b * x) + (a * y)) - (b * c)) / (std::pow(a, 2) + std::pow(b, 2));

			Vector2 closestPoint(c_x, c_y);

			float distance = P.distance(Q);

			if (P.distance(closestPoint) > distance || Q.distance(closestPoint) > distance)
			{
				return false;
			}

			if (radius > closestPoint.distance(Vector2(center.x, center.z)))
			{
				Vector2 P(rayStart.x, rayStart.y);
				Vector2 Q(rayEnd.x, rayEnd.y);

				float a = Q.y - P.y;
				float b = P.x - Q.x;
				float c = (a * (P.x) + b * (P.y)) * -1.f;

				float x = center.x;
				float y = center.y;

				float c_x = (b * ((b * x) - (a * y)) - a * c) / (std::pow(a, 2) + std::pow(b, 2));
				float c_y = (a * ((-b * x) + (a * y)) - (b * c)) / (std::pow(a, 2) + std::pow(b, 2));

				Vector2 closestPoint(c_x, c_y);
				if (radius > closestPoint.distance(Vector2(center.x, center.y)))
				{
					return true;
				}
				else
				{
					offset += std::fabs(center.y - closestPoint.y);
					return false;
				}
			}

			return false;
		};

		Vector3 SimulateProjectile(Vector3 position, Vector3 velocity, float& partialTime, float& travelTime, Vector3 gravity, float drag)
		{
			//float timestep = 0.03125f;
			//float timestep = 0.015625f;
			float timestep = 0.003f;
			Vector3 origin = position;
			if (partialTime > 0)
			{
				float num2 = timestep - partialTime;
				if (travelTime < num2)
				{
					origin = position;
					position += velocity * travelTime;
					partialTime += travelTime;
					return origin;
				}
				origin = position;
				position += velocity * num2;
				velocity += gravity * timestep;
				velocity -= velocity * drag * timestep;
				travelTime -= num2;
			}

			int num3 = (int)std::floor(travelTime / timestep);

			for (int i = 0; i < num3; i++)
			{
				origin = position;
				position += velocity * timestep;
				velocity += gravity * timestep;
				velocity -= velocity * drag * timestep;
				//DDraw::Sphere(position, 0.05f, Color::Color(180, 150, 210, 50), 1.0f, false); //head
			}
			partialTime = travelTime - timestep * (float)num3;
			if (partialTime > 0)
			{
				origin = position;
				position += velocity * partialTime;
			}


			return origin;
		}
#define powFFFFFFFFFFFFFFFFFFFFFF(n) (n)*(n)
#define maxSimulateSeconds 5
#define stepRate 0.01666666666
		struct weapon_stats_t {
			float initial_velocity;
			float gravity_modifier;
			float drag;
			float initial_distance;
		};

		enum ammo_types : int32_t {
			shotgun = -1685290200,
			shotgun_slug = -727717969,
			shotgun_fire = -1036635990,
			shotgun_handmade = 588596902,

			rifle_556 = -1211166256,
			rifle_556_hv = 1712070256,
			rifle_556_fire = 605467368,
			rifle_556_explosive = -1321651331,

			pistol = 785728077,
			pistol_hv = -1691396643,
			pistol_fire = 51984655,

			arrow_wooden = -1234735557,
			arrow_hv = -1023065463,
			arrow_fire = 14241751,
			arrow_bone = 215754713,

			nailgun_nails = -2097376851
		};

		enum weapon_types : int32_t {
			spear_stone = 1602646136,
			spear_wooden = 1540934679
		};

		double get_bullet_drop(double height, double aaaa, float speed, float gravity) {
			double pitch = std::atan2(height, aaaa);
			double vel_double = speed * std::cos(pitch);
			double t = aaaa / vel_double;
			double y = (0.4905f * gravity * t * t);
			return y * 10;
		}

		Vector3 GetModifiedAimConeDirection(float aimCone, Vector3 inputVec, bool anywhereInside = true) {
			BasePlayer* TargetPlayer = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer);
			Vector3 Local = LocalPlayer::Entity()->eyes()->get_position();

			Item* weapon = LocalPlayer::Entity()->GetActiveWeapon();
			DWORD64 active = weapon->entity();
			char* classname = weapon->ClassName();
			float velonity;
			if (TargetPlayer->has_modelstate_flag(ModelStateFlag::Mounted) || vars::stor::closestHeli != 0)
			{
				velonity = 0.9f;
			}
			else
			{
				velonity = 0.8;//0.8
			}
			Vector3 heli_target = reinterpret_cast<BaseEntity*>(vars::stor::closestHeli)->transform()->position() + Vector3(0, 1.9, 0);
			if (vars::combat::psilent &&( TargetPlayer || vars::stor::closestHeli != 0)&& LocalPlayer::Entity()->GetActiveWeapon()->GetID() != 1540934679 && LocalPlayer::Entity()->GetActiveWeapon()->GetID() != 1602646136 && LocalPlayer::Entity()->GetActiveWeapon()->GetID() != 1090916276 && LocalPlayer::Entity()->GetActiveWeapon()->GetID() != 1814288539 && LocalPlayer::Entity()->GetActiveWeapon()->GetID() != -363689972 && LocalPlayer::Entity()->GetActiveWeapon()->GetID() != -1789825282 && LocalPlayer::Entity()->GetActiveWeapon()->GetID() != -1137865085 && LocalPlayer::Entity()->GetActiveWeapon()->GetID() != 1711033574 && LocalPlayer::Entity()->GetActiveWeapon()->GetID() != -1966748496 && LocalPlayer::Entity()->GetActiveWeapon()->GetID() != -194509282 && LocalPlayer::Entity()->GetActiveWeapon()->GetID() != 1326180354 && LocalPlayer::Entity()->GetActiveWeapon()->GetID() != -1469578201 && LocalPlayer::Entity()->GetActiveWeapon()->GetID() != -1978999529 && LocalPlayer::Entity()->GetActiveWeapon()->GetID() != 1602646136 && LocalPlayer::Entity()->GetActiveWeapon()->GetID() != 2040726127 && LocalPlayer::Entity()->GetActiveWeapon()->GetID() != 963906841)
			{


				if (vars::combat::psilentbone == 0)
				{
					float xs = vars::stuff::ScreenWidth / 2, ys = vars::stuff::ScreenHeight / 2;
					Vector3 target;


					target = TargetPlayer->GetBoneByID(head);

					float gravity;
					if (LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1540934679 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1602646136) {
						gravity = 2.1;
					}
					else {
						gravity = GetGravity(LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo());
					}
					a::PredictionWeapon(Local, heli_target, reinterpret_cast<BaseEntity*>(vars::stor::closestHeli)->GetWorldVelocity(), velonity);
					a::PredictionWeapon(Local, target, TargetPlayer->newVelocity(), velonity);
					Vector3 heliDir = (heli_target - Local).Normalized();
					Vector3 playerDir = (target - Local).Normalized();
					if (vars::combat::psilent) {
						if (!vars::combat::psilentonkey) {
							if (vars::combat::psilent && vars::stor::closestPlayer != NULL) {
								inputVec = playerDir;
							}
							if (vars::combat::psilentheli && vars::stor::closestHeli != NULL) {
								inputVec = heliDir;
							}
						}
						else {
							if (GetAsyncKeyState(vars::keys::psilent)) {
								if (vars::combat::psilent && vars::stor::closestPlayer != NULL) {
									inputVec = playerDir;
								}
								if (vars::combat::psilentheli && vars::stor::closestHeli != NULL) {
									inputVec = heliDir;
								}
							}
						}
					}
				}
				if (vars::combat::psilentbone == 1)
				{
					Vector3 target;
					int yeet11 = rand() % 100;
					if (yeet11 > 50) {
						target = TargetPlayer->GetBoneByID(spine4);
					}
					else {
						target = TargetPlayer->GetBoneByID(spine1);
					}
					float gravity;
					if (LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1540934679 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1602646136) {
						gravity = 2.1;
					}
					else {
						gravity = GetGravity(LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo());
					}
					a::PredictionWeapon(Local, heli_target, reinterpret_cast<BaseEntity*>(vars::stor::closestHeli)->GetWorldVelocity(), velonity);
					a::PredictionWeapon(Local, target, TargetPlayer->newVelocity(), velonity);
					Vector3 heliDir = (heli_target - Local).Normalized();
					Vector3 playerDir = (target - Local).Normalized();
					if (vars::combat::psilent) {
						if (!vars::combat::psilentonkey) {
							if (vars::combat::psilent && vars::stor::closestPlayer != NULL) {
								inputVec = playerDir;
							}
							if (vars::combat::psilentheli && vars::stor::closestHeli != NULL) {
								inputVec = heliDir;
							}
						}
						else {
							if (GetAsyncKeyState(vars::keys::psilent)) {
								if (vars::combat::psilent && vars::stor::closestPlayer != NULL) {
									inputVec = playerDir;
								}
								if (vars::combat::psilentheli && vars::stor::closestHeli != NULL) {
									inputVec = heliDir;
								}
							}
						}
					}
				}
				if (vars::combat::psilentbone == 2)
				{
					Vector3 target;
					int num = rand() % 100;
					if (num > 90)
					{
						target = TargetPlayer->GetBoneByID(head);
					}
					else if (num < 90 && num > 80)
					{
						target = TargetPlayer->GetBoneByID(neck);
					}
					else if (num < 80 && num > 70)
					{
						target = TargetPlayer->GetBoneByID(r_hip);
					}
					else if (num < 70 && num > 60)
					{
						target = TargetPlayer->GetBoneByID(pelvis);
					}
					else if (num < 60 && num > 50)
					{
						target = TargetPlayer->GetBoneByID(l_clavicle);
					}
					else if (num < 50 && num > 40)
					{
						target = TargetPlayer->GetBoneByID(l_upperarm);
					}
					else if (num < 40 && num > 30)
					{
						target = TargetPlayer->GetBoneByID(l_foot);
					}
					else if (num < 30 && num > 20)
					{
						target = TargetPlayer->GetBoneByID(r_foot);
					}
					else if (num < 20 && num > 10)
					{
						target = TargetPlayer->GetBoneByID(l_hand);
					}
					else if (num < 10)
					{
						target = TargetPlayer->GetBoneByID(r_hand);
					}
					else
					{
						target = TargetPlayer->GetBoneByID(spine1);
					}
					float gravity;
					if (LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1540934679 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1602646136) {
						gravity = 2.1;
					}
					else {
						gravity = GetGravity(LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo());
					}
					a::PredictionWeapon(Local, heli_target, reinterpret_cast<BaseEntity*>(vars::stor::closestHeli)->GetWorldVelocity(), velonity);
					a::PredictionWeapon(Local, target, TargetPlayer->newVelocity(), velonity);
					Vector3 heliDir = (heli_target - Local).Normalized();
					Vector3 playerDir = (target - Local).Normalized();
					if (vars::combat::psilent) {
						if (!vars::combat::psilentonkey) {
							if (vars::combat::psilent && vars::stor::closestPlayer != NULL) {
								inputVec = playerDir;
							}
							if (vars::combat::psilentheli && vars::stor::closestHeli != NULL) {
								inputVec = heliDir;
							}
						}
						else {
							if (GetAsyncKeyState(vars::keys::psilent)) {
								if (vars::combat::psilent && vars::stor::closestPlayer != NULL) {
									inputVec = playerDir;
								}
								if (vars::combat::psilentheli && vars::stor::closestHeli != NULL) {
									inputVec = heliDir;
								}
							}
						}
					}
				}
				if (vars::combat::psilentbone == 3)
				{
					Vector3 target;
					int yeet1 = rand() % 100;
					if (yeet1 > 50) {
						target = TargetPlayer->GetBoneByID(head);
					}
					else {
						target = TargetPlayer->GetBoneByID(spine1);
					}
					float gravity;
					if (LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1540934679 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1602646136) {
						gravity = 2.1;
					}
					else {
						gravity = GetGravity(LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo());
					}
					a::PredictionWeapon(Local, heli_target, reinterpret_cast<BaseEntity*>(vars::stor::closestHeli)->GetWorldVelocity(), velonity);
					a::PredictionWeapon(Local, target, TargetPlayer->newVelocity(), velonity);
					Vector3 heliDir = (heli_target - Local).Normalized();
					Vector3 playerDir = (target - Local).Normalized();
					if (vars::combat::psilent) {
						if (!vars::combat::psilentonkey) {
							if (vars::combat::psilent && vars::stor::closestPlayer != NULL) {
								inputVec = playerDir;
							}
							if (vars::combat::psilentheli && vars::stor::closestHeli != NULL) {
								inputVec = heliDir;
							}
						}
						else {
							if (GetAsyncKeyState(vars::keys::psilent)) {
								if (vars::combat::psilent && vars::stor::closestPlayer != NULL) {
									inputVec = playerDir;
								}
								if (vars::combat::psilentheli && vars::stor::closestHeli != NULL) {
									inputVec = heliDir;
								}
							}
						}
					}
				}
			}
			else  if (vars::combat::psilent && (TargetPlayer || vars::stor::closestHeli != 0))
			{
			if (vars::combat::psilentbone == 0)
			{
				float xs = vars::stuff::ScreenWidth / 2, ys = vars::stuff::ScreenHeight / 2;
				Vector3 target;


				target = TargetPlayer->GetBoneByID(head);

				float gravity;
				if (LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1540934679 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1602646136) {
					gravity = 2.1;
				}
				else {
					gravity = GetGravity(LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo());
				}
				a::Prediction(Local, heli_target, reinterpret_cast<BaseEntity*>(vars::stor::closestHeli)->GetWorldVelocity(), GetBulletSpeed(), gravity);
				a::Prediction(Local, target, TargetPlayer->newVelocity(), GetBulletSpeed(), gravity);
				Vector3 heliDir = (heli_target - Local).Normalized();
				Vector3 playerDir = (target - Local).Normalized();
				if (vars::combat::psilent) {
					if (!vars::combat::psilentonkey) {
						if (vars::combat::psilent && vars::stor::closestPlayer != NULL) {
							inputVec = playerDir;
						}
						if (vars::combat::psilentheli && vars::stor::closestHeli != NULL) {
							inputVec = heliDir;
						}
					}
					else {
						if (GetAsyncKeyState(vars::keys::psilent)) {
							if (vars::combat::psilent && vars::stor::closestPlayer != NULL) {
								inputVec = playerDir;
							}
							if (vars::combat::psilentheli && vars::stor::closestHeli != NULL) {
								inputVec = heliDir;
							}
						}
					}
				}
			}
			if (vars::combat::psilentbone == 1)
			{
				Vector3 target;
				int yeet11 = rand() % 100;
				if (yeet11 > 50) {
					target = TargetPlayer->GetBoneByID(spine4);
				}
				else {
					target = TargetPlayer->GetBoneByID(spine1);
				}
				float gravity;
				if (LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1540934679 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1602646136) {
					gravity = 2.1;
				}
				else {
					gravity = GetGravity(LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo());
				}
				a::Prediction(Local, heli_target, reinterpret_cast<BaseEntity*>(vars::stor::closestHeli)->GetWorldVelocity(), GetBulletSpeed(), gravity);
				a::Prediction(Local, target, TargetPlayer->newVelocity(), GetBulletSpeed(), gravity);
				Vector3 heliDir = (heli_target - Local).Normalized();
				Vector3 playerDir = (target - Local).Normalized();
				if (vars::combat::psilent) {
					if (!vars::combat::psilentonkey) {
						if (vars::combat::psilent && vars::stor::closestPlayer != NULL) {
							inputVec = playerDir;
						}
						if (vars::combat::psilentheli && vars::stor::closestHeli != NULL) {
							inputVec = heliDir;
						}
					}
					else {
						if (GetAsyncKeyState(vars::keys::psilent)) {
							if (vars::combat::psilent && vars::stor::closestPlayer != NULL) {
								inputVec = playerDir;
							}
							if (vars::combat::psilentheli && vars::stor::closestHeli != NULL) {
								inputVec = heliDir;
							}
						}
					}
				}
			}
			if (vars::combat::psilentbone == 2)
			{
				Vector3 target;
				int num = rand() % 100;
				if (num > 90)
				{
					target = TargetPlayer->GetBoneByID(head);
				}
				else if (num < 90 && num > 80)
				{
					target = TargetPlayer->GetBoneByID(neck);
				}
				else if (num < 80 && num > 70)
				{
					target = TargetPlayer->GetBoneByID(r_hip);
				}
				else if (num < 70 && num > 60)
				{
					target = TargetPlayer->GetBoneByID(pelvis);
				}
				else if (num < 60 && num > 50)
				{
					target = TargetPlayer->GetBoneByID(l_clavicle);
				}
				else if (num < 50 && num > 40)
				{
					target = TargetPlayer->GetBoneByID(l_upperarm);
				}
				else if (num < 40 && num > 30)
				{
					target = TargetPlayer->GetBoneByID(l_foot);
				}
				else if (num < 30 && num > 20)
				{
					target = TargetPlayer->GetBoneByID(r_foot);
				}
				else if (num < 20 && num > 10)
				{
					target = TargetPlayer->GetBoneByID(l_hand);
				}
				else if (num < 10)
				{
					target = TargetPlayer->GetBoneByID(r_hand);
				}
				else
				{
					target = TargetPlayer->GetBoneByID(spine1);
				}
				float gravity;
				if (LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1540934679 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1602646136) {
					gravity = 2.1;
				}
				else {
					gravity = GetGravity(LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo());
				}
				a::Prediction(Local, heli_target, reinterpret_cast<BaseEntity*>(vars::stor::closestHeli)->GetWorldVelocity(), GetBulletSpeed(), gravity);
				a::Prediction(Local, target, TargetPlayer->newVelocity(), GetBulletSpeed(), gravity);
				Vector3 heliDir = (heli_target - Local).Normalized();
				Vector3 playerDir = (target - Local).Normalized();
				if (vars::combat::psilent) {
					if (!vars::combat::psilentonkey) {
						if (vars::combat::psilent && vars::stor::closestPlayer != NULL) {
							inputVec = playerDir;
						}
						if (vars::combat::psilentheli && vars::stor::closestHeli != NULL) {
							inputVec = heliDir;
						}
					}
					else {
						if (GetAsyncKeyState(vars::keys::psilent)) {
							if (vars::combat::psilent && vars::stor::closestPlayer != NULL) {
								inputVec = playerDir;
							}
							if (vars::combat::psilentheli && vars::stor::closestHeli != NULL) {
								inputVec = heliDir;
							}
						}
					}
				}
			}
			if (vars::combat::psilentbone == 3)
			{
				Vector3 target;
				int yeet1 = rand() % 100;
				if (yeet1 > 50) {
					target = TargetPlayer->GetBoneByID(head);
				}
				else {
					target = TargetPlayer->GetBoneByID(spine1);
				}
				float gravity;
				if (LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1540934679 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1602646136) {
					gravity = 2.1;
				}
				else {
					gravity = GetGravity(LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo());
				}
				a::Prediction(Local, heli_target, reinterpret_cast<BaseEntity*>(vars::stor::closestHeli)->GetWorldVelocity(), GetBulletSpeed(), gravity);
				a::Prediction(Local, target, TargetPlayer->newVelocity(), GetBulletSpeed(), gravity);
				Vector3 heliDir = (heli_target - Local).Normalized();
				Vector3 playerDir = (target - Local).Normalized();
				if (vars::combat::psilent) {
					if (!vars::combat::psilentonkey) {
						if (vars::combat::psilent && vars::stor::closestPlayer != NULL) {
							inputVec = playerDir;
						}
						if (vars::combat::psilentheli && vars::stor::closestHeli != NULL) {
							inputVec = heliDir;
						}
					}
					else {
						if (GetAsyncKeyState(vars::keys::psilent)) {
							if (vars::combat::psilent && vars::stor::closestPlayer != NULL) {
								inputVec = playerDir;
							}
							if (vars::combat::psilentheli && vars::stor::closestHeli != NULL) {
								inputVec = heliDir;
							}
						}
					}
				}
			}
 }
			if (vars::weapons::no_spread) {
				aimCone = vars::weapons::no_spreadvalue / 100.f;
			}
			did_reload = false;
			just_shot = true;
			fixed_time_last_shot = Time::fixedTime();
			auto held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();
			return original_aimconedirection(aimCone, inputVec, anywhereInside);
		}

		Vector3 hk_BodyLeanOffset(PlayerEyes* a1) {
			if (vars::combat::manipulator && !other::m_manipulate.empty()) {
				return other::m_manipulate;
			}
			return Original_BodyLeanOffset(a1);
		}
		Vector3 hk_EyePositionForPlayer(BaseMountable* arg1, BasePlayer* arg2, Quaternion* arg3) {
			BasePlayer* player = arg2;
			if (player->userID()) {
				if (vars::combat::manipulator && GetAsyncKeyState(vars::keys::manipulated_key)) {
					return Original_EyePositionForPlayer(arg1, arg2, arg3) + other::m_manipulate;
				}
			}
			return Original_EyePositionForPlayer(arg1, arg2, arg3);
		}
		void hk_DoFirstPersonCamera(PlayerEyes* a1, Component* cam) {
			if (!a1 || !cam) return;
			Original_DoFirstPersonCamera_hk(a1, cam);
			if (vars::combat::followprojectile
				&& GetAsyncKeyState(vars::keys::followprojectile)
				&& proj)
			{
				Vector3 p = projv->currentPosition();
				cam->transform()->set_position(Vector3(p.x, p.y + 0.1f, p.z));
				//return;
			}

			if (vars::combat::manipulator && !GetAsyncKeyState(vars::keys::followprojectile)) {
				Vector3 re_p = LocalPlayer::Entity()->transform()->position() + LocalPlayer::Entity()->transform()->up() * (PlayerEyes::EyeOffset().y + LocalPlayer::Entity()->eyes()->viewOffset().y);
				cam->transform()->set_position(re_p);
			}
		}
	}
	System::Object_* StartCoroutine_hk(MonoBehaviour* a1, System::Object_* un2) {
		if (vars::misc::fast_loot) {
			if (CALLED_BY(vars::stor::gBase + 0x971010, 0x656)) {
				*reinterpret_cast<float*>(un2 + 0x28) = -0.2f;
			}
		}
		return a1->StartCoroutine(un2);
	}
}

void UpdateVelocity_hk(PlayerWalkMovement* self) {
	if (!self->flying()) {
		Vector3 vel = self->TargetMovement();
		if (vars::misc::omnidirectional_sprinting && !LocalPlayer::Entity()->get_flag(64)) {
			float max_speed = (self->swimming() || self->Ducking() > 0.5) ? 1.7f : 5.5f;
			if (vel.length() > 0.f) {

				Vector3 target_vel = Vector3(vel.x / vel.length() * max_speed, vel.y, vel.z / vel.length() * max_speed);
				self->TargetMovement() = target_vel;
			}
		}
	}

	return original_updatevelos(self);
}

void HandleJumping_hk(PlayerWalkMovement* a1, ModelState* state, bool wantsJump, bool jumpInDirection = false) {
	if (vars::misc::spiderman)
	{
		a1->SetPinosScale(0.44);
	}

	if (vars::misc::inf_jump) {
		if (!wantsJump)
			return;

		a1->grounded() = (a1->climbing() = (a1->sliding() = false));
		state->set_ducked(false);
		a1->jumping() = true;
		state->set_jumped(true);
		a1->jumpTime() = Time::time();
		a1->ladder() = nullptr;

		Vector3 curVel = a1->body()->velocity();
		a1->body()->set_velocity({ curVel.x, 10, curVel.z });
		return;
	}

	return original_jumpup(a1, state, wantsJump, jumpInDirection);
}

inline float __fastcall Fake_GetSpeed(float* a1, float* a2)
{
	if (vars::misc::speedhack && GetAsyncKeyState(vars::keys::speedkey));
	return true;
	return  Orig_GetSpeed(a1, a2);
}

void OnLand_hk(BasePlayer* ply, float vel) {
	if (!LocalPlayer::Entity()->get_flag(PlayerFlags::Connected)) return ply->OnLand(vel);
	if (!vars::misc::no_fall)
		ply->OnLand(vel);
}

bool IsDown_hk(InputState* self, Button btn) {
	if (!LocalPlayer::Entity()->get_flag(PlayerFlags::Connected)) return original_isdown(self, btn);
	if (LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1588298435 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -778367295 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -1367281941 ||
		LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -765183617 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -41440462 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 795371088 ||
		LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -75944661 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1965232394 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 884424049 ||
		LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1443579727 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1318558775 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1796682209 ||
		LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 649912614 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 818877484 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -852563019 ||
		LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1373971859 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -1758372725 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -1812555177 ||
		LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -904863145 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1545779598 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -1335497659 ||
		LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -2069578888 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -1214542497 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 28201841 ||
		LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1953903201) {
		if (vars::combat::autoshoot) {
			if (vars::combat::desync_autoshoot_type == 0) {
				if (vars::combat::autoshoot_type == 1) {
					if (btn == Button::FIRE_PRIMARY) {
						auto held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();
						if (held && !held->Empty() && held->class_name_hash() == STATIC_CRC32("BaseProjectile")) {
							if (reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer) != nullptr) {

								Vector3 target = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->GetBoneByID(head);
								if (utils::LineOfSight(target, LocalPlayer::Entity()->eyes()->position()) && vars::combat::autoshoot)
									return true;
							}
						}
					}
				}
			}
		}
		if (vars::combat::desync_autoshoot_type == 1) {
			if (vars::combat::autoshoot && vars::combat::manipulator && GetAsyncKeyState(vars::keys::manipulated_key)) {
				if (vars::combat::autoshoot_type == 1) {
					if (btn == Button::FIRE_PRIMARY) {
						auto held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();
						if (held && !held->Empty() && held->class_name_hash() == STATIC_CRC32("BaseProjectile")) {
							if (reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer) != nullptr) {

								Vector3 target = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->GetBoneByID(head);

								if (utils::LineOfSight(target, LocalPlayer::Entity()->eyes()->position()) && vars::combat::autoshoot)
									return true;
							}
						}
					}
				}
			}
		}
		float desyncpercentage;
		float desyncTime = (Time::realtimeSinceStartup() - LocalPlayer::Entity()->lastSentTickTime()) - 0.03125 * 3;
		desyncpercentage = ((desyncTime / 0.99f) * 100.0f) + 1.f;
		if (!LocalPlayer::Entity()->get_flag(PlayerFlags::Connected)) return original_isdown(self, btn);
		if (vars::combat::instakill && GetAsyncKeyState(vars::keys::instakill)) {
			if (vars::combat::instakill_type == 1) {
				if (btn == Button::FIRE_PRIMARY) {
					auto held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();
					if (held && !held->Empty() && held->class_name_hash() == STATIC_CRC32("BaseProjectile")) {
						if (reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer) != nullptr && !LocalPlayer::Entity()->is_teammate(reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)) && reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->IsValid() && LocalPlayer::Entity()->get_flag(PlayerFlags::Connected)/* && !did_reload*/) {
							if (utils::LineOfSight(reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->GetBoneByID(head), LocalPlayer::Entity()->eyes()->position())) {
								LocalPlayer::Entity()->clientTickInterval() = 0.99f;
								if (desyncTime > 0.80f) {
									return true;
								}
							}
						}
					}
				}
			}
		}
	}

	return original_isdown(self, btn);
}

void hk_(void* Function, void** Original, void* Detour) {
	if (MH_Initialize() != MH_OK && MH_Initialize() != MH_ERROR_ALREADY_INITIALIZED) {
		MessageBox(0, xorstr_(L"Initialization hook error in product, go to 2iq fix pls. dm  to get help."), 0, 0);
		return;
	}
	MH_CreateHook(Function, Detour, Original);
	MH_EnableHook(Function);
}

void hk__() {

	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::set_flying), (void**)&original_setflying, hk::misc::SetFlying);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::SendProjectileAttack), (void**)&original_sendprojectileattack, hk::combat::SendProjectileAttack);
//	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::CanAttack), (void**)&original_canattack, hk::combat::CanAttack);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::SendClientTick), (void**)&original_sendclienttick, hk::misc::SendClientTick);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::GetModifiedAimConeDirection), (void**)&original_aimconedirection, hk::combat::GetModifiedAimConeDirection);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::CanHoldItems), (void**)&original_canholditems, hk::combat::CanHoldItems);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::Run), (void**)&original_consolerun, hk::misc::Run);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::CreateProjectile), (void**)&original_create_projectile, hk::combat::CreateProjectile);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::CreateEffect), (void**)&original_createeffect, hk::misc::CreateEffect);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::Play), (void**)&original_viewmodelplay, hk::misc::Play);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::VisUpdateUsingCulling), (void**)&original_UnregisterFromVisibility, hk::misc::VisUpdateUsingCulling);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::GetRandomVelocity), (void**)&original_getrandomvelocity, hk::combat::GetRandomVelocity);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::AddPunch), (void**)&original_addpunch, hk::combat::AddPunch);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::MoveTowards), (void**)&original_movetowards, hk::combat::MoveTowards);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::Refract), (void**)&original_refract, hk::exploit::Refract);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::DoMovement), (void**)&original_domovement, hk::exploit::DoMovement);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::Launch), (void**)&original_launch, hk::combat::Launch);
	//hk_((void*)(uintptr_t)(vars::stor::gBase + CO::DoFixedUpdate), (void**)&original_dofixedupdate, hk::misc::DoFixedUpdate);
	//hk_((void*)(uintptr_t)(vars::stor::gBase + CO::ClientUpdate), (void**)&original_clientupdate, hk::misc::ClientUpdate);
	//hk_((void*)(uintptr_t)(vars::stor::gBase + CO::ClientUpdate_Sleeping), (void**)&original_clientupdate_sleeping, hk::misc::ClientUpdate_Sleeping);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::DoHit), (void**)&original_dohit, hk::combat::DoHit);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::UpdateAmbient), (void**)&original_updateambient, hk::misc::UpdateAmbient);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::ClientInput), (void**)&original_clientinput, hk::misc::ClientInput);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::DoHitNotify), (void**)&original_dohitnotify, hk::misc::DoHitNotify);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::get_isHeadshot), (void**)&original_getisheadshot, hk::misc::get_isHeadshot);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::StartCoroutine), (void**)&MonoBehaviour::StartCoroutine_, hk::StartCoroutine_hk);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::UpdateVelocity), (void**)&original_updatevelos, UpdateVelocity_hk);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::HandleJumping), (void**)&original_jumpup, HandleJumping_hk);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::OnLand), (void**)&BasePlayer::OnLand_, OnLand_hk);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::IsDown), (void**)&original_isdown, IsDown_hk);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::get_BodyLeanOffset), (void**)&Original_BodyLeanOffset, hk::combat::hk_BodyLeanOffset);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::EyePositionForPlayer), (void**)&Original_EyePositionForPlayer, hk::combat::hk_EyePositionForPlayer);
	hk_((void*)(uintptr_t)(vars::stor::gBase + CO::DoFirstPersonCamera), (void**)&Original_DoFirstPersonCamera_hk, hk::combat::hk_DoFirstPersonCamera);
}