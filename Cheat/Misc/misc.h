constexpr auto set_asset = 0x2522020; //get_main Unity.Camera
constexpr auto Get_Camera_Main = 0x25227A0; //aspect Unity.Camera
constexpr auto set_collider = 0x256ECA0; //public void set_radius(float value) { }
bool meal = false;
void weapon_set( ) {
	Item* weapon = LocalPlayer::Entity( )->GetActiveWeapon( );
	if (weapon == nullptr) return;

	//-3 - hammer, -2 - bows, -1 - eoka, 0-nopatch, 1 - meele, 2 - semiautomatic, 3 - automatic
	Weapon target = weapon->Info( );
	if (!target.id) return;
	if (!target.category) return;

	if (target.category == -2) {
		weapon->NoSway( );
		weapon->FastBow( );	
		return;
	}
	if (target.category == 3) {
		weapon->NoSway( );
		weapon->RapidFire( );
		weapon->instakill_button();

		return;
	}
	if (target.category == 2) {
		weapon->NoSway( );
		
		weapon->instakill_button( );
		weapon->SetAutomatic( );
		
		return;
	}
	if (target.category == -1) {
		weapon->NoSway( );
	
		weapon->EokaTap( );
		
		return;
	}
}
float w_last_syringe = 0.f;
struct Camera
{
	static Camera* GetCameraMain()
	{
		return reinterpret_cast<Camera * (__fastcall*)()>(vars::stor::gBase + CO::Get_Camera_Main)();
	}
};
void set_aspect(Camera* cam, float aspect)//0x24B6B30
{
	return reinterpret_cast<void(__fastcall*)(Camera * cam, float aspect)>(vars::stor::gBase + CO::set_aspect)(cam, aspect);
}

void set_Radius(float rad)//0x24B6B30
{
	return reinterpret_cast<void(__fastcall*)( float rad)>(vars::stor::gBase + CO::set_collider)( rad);
}

void misc_set() {
	if (w_last_syringe == 0.f) {
		w_last_syringe = LocalPlayer::Entity( )->lastSentTickTime( );
	}
	Item* weapon = LocalPlayer::Entity( )->GetActiveWeapon( );
	if ((weapon->GetID( ) == 1079279582 || weapon->GetID( ) == -2072273936) && vars::misc::faster_healing && LocalPlayer::Entity()->health() < 99) {
		DWORD64 Held = weapon->entity( );
		bool deployed = read(Held + O::HeldEntity::isDeployed, bool); // protected bool isDeployed;
		float curtime = LocalPlayer::Entity( )->lastSentTickTime( );
		if (deployed && curtime > w_last_syringe + 0.7f) {
			reinterpret_cast<void(_stdcall*)(DWORD64, Str)>(vars::stor::gBase + CO::ServerRPC)(Held, Str(xorstr_(L"UseSelf")));
			w_last_syringe = curtime;
		}
	}
	auto klass = read(vars::stor::gBase + CO::ConvarGraphics, DWORD64);
	auto static_fields = read(klass + 0xB8, DWORD64);
	if (vars::visuals::zoom && GetAsyncKeyState(vars::keys::zoom)) {
		write(static_fields + 0x18, 10.f, float);
	}
	else {
		write(static_fields + 0x18, vars::misc::fov, float);
	}
	if (vars::misc::spiderman) {
		
		uintptr_t Movement = read(LocalPlayer::Entity( ) + O::BasePlayer::movement, uintptr_t);
		write(Movement + O::PlayerWalkMovement::groundAngle, 0.f, float);
		write(Movement + O::PlayerWalkMovement::groundAngleNew, 0.f, float);
	}

	if (vars::misc::aspectraratio)
	{
		auto camera = Camera::GetCameraMain();
		set_aspect(camera, vars::misc::aspectraratiofloat / 1000);
		
	}

	if (vars::misc::collider)
	{
		
		set_Radius(0.44);

	}

	if (vars::misc::fakeadmin)
	{
		LocalPlayer::Entity()->FakeAdmin();
	}
	if (vars::misc::unloadfakeadmin)
	{
		LocalPlayer::Entity()->UnloadFakeAdmin();
	}
		
	if (vars::misc::custom_time)
		LocalPlayer::Entity()->Admintime();
	if (vars::misc::long_neck && GetAsyncKeyState(vars::keys::longneck))
		LocalPlayer::Entity()->LongNeck();
}


namespace lol {
	void do_attack(f_object target, uintptr_t Held, bool transform) {
	
		
		if (!(LocalPlayer::Entity()->GetActiveWeapon()->GetID() != 200773292 && LocalPlayer::Entity()->GetActiveWeapon()->GetID() != 1540934679 && LocalPlayer::Entity()->GetActiveWeapon()->GetID() != 1602646136 && LocalPlayer::Entity()->GetActiveWeapon()->GetID() != 1090916276 && LocalPlayer::Entity()->GetActiveWeapon()->GetID() != 1814288539 && LocalPlayer::Entity()->GetActiveWeapon()->GetID() != -363689972 && LocalPlayer::Entity()->GetActiveWeapon()->GetID() != -1789825282 && LocalPlayer::Entity()->GetActiveWeapon()->GetID() != -1137865085 && LocalPlayer::Entity()->GetActiveWeapon()->GetID() != 1711033574 && LocalPlayer::Entity()->GetActiveWeapon()->GetID() != -1966748496 && LocalPlayer::Entity()->GetActiveWeapon()->GetID() != -194509282 && LocalPlayer::Entity()->GetActiveWeapon()->GetID() != 1326180354 && LocalPlayer::Entity()->GetActiveWeapon()->GetID() != -1469578201 && LocalPlayer::Entity()->GetActiveWeapon()->GetID() != -1978999529 && LocalPlayer::Entity()->GetActiveWeapon()->GetID() != 1602646136 && LocalPlayer::Entity()->GetActiveWeapon()->GetID() != 2040726127 && LocalPlayer::Entity()->GetActiveWeapon()->GetID() != 963906841))
		{

		
		if (!target.valid || !Held) return;
	
		if (read(Held + O::AttackEntity::nextAttackTime, float) >= Time::time( )) { return; }
		if (read(Held + O::AttackEntity::timeSinceDeploy, float) < read(Held + O::AttackEntity::deployDelay, float)) { return; }

		uintptr_t staticHitTest = read(vars::stor::gBase + CO::HitTest, DWORD64); if (!staticHitTest) return;
		uintptr_t newHitTest = il2cpp::il2cpp_object_new(staticHitTest); if (!newHitTest) return;

		uintptr_t trans; Ray ray = Ray(LocalPlayer::Entity( )->GetBoneByID(neck), (target.position - LocalPlayer::Entity( )->GetBoneByID(neck)).Normalized( ));
		if (!target.entity) return;
		if (transform) {
			trans = reinterpret_cast<BasePlayer*>(target.entity)->mono_transform(head);
		}
		else {
			trans = (DWORD64)reinterpret_cast<Object*>(target.entity)->transform( );
		} if (!trans) {
		//	LogSystem::Log(xorstr_(L"Transform no found in Infinity product, go to update mono_transform pls. dm oxunem#1337 to get help."), 1.f);
			return;
		}
		
		write(newHitTest + O::HitTest::MaxDistance, 1000.f, float);
		write(newHitTest + O::HitTest::HitTransform, trans, uintptr_t);
		write(newHitTest + O::HitTest::AttackRay, ray, Ray);
		write(newHitTest + O::HitTest::DidHit, true, bool);
		write(newHitTest + O::HitTest::HitEntity, reinterpret_cast<BasePlayer*>(target.entity), BasePlayer*);
		write(newHitTest + O::HitTest::HitPoint, reinterpret_cast<Transform*>(trans)->InverseTransformPoint(target.position), Vector3);
		write(newHitTest + O::HitTest::HitNormal, reinterpret_cast<Transform*>(trans)->InverseTransformPoint(target.position), Vector3);
		write(newHitTest + O::HitTest::damageProperties, read(Held + O::BaseMelee::damageProperties, uintptr_t), uintptr_t);
		reinterpret_cast<void(*)(uintptr_t, float)>(vars::stor::gBase + CO::StartAttackCooldown)(Held, read(Held + O::AttackEntity::repeatDelay, float));
		return reinterpret_cast<void(*)(uintptr_t, uintptr_t)>(vars::stor::gBase + CO::ProcessAttack)(Held, newHitTest);
		
		}
	}
	// 0, -9.1 * gravityModifier, 0
	TraceResult traceProjectile(Vector3 position, Vector3 velocity, float drag, Vector3 gravity, Vector3 targetPoint) {
		constexpr float num = 0.03125f;
		Vector3 prevPosition = position;
		float prevDist = FLT_MAX;
		Line resultLine = Line(position, position);
		float travelTime = 0.f;
		TraceResult result;

		for (; travelTime < 8.f; ) {
			prevPosition = position;
			position += velocity * num;

			Line line = Line(prevPosition, position);
			Vector3 nearest = line.ClosestPoint(targetPoint);

			float dst = (nearest - targetPoint).Length( );

			if (dst > prevDist) {
				break;
			}
			prevDist = dst;
			resultLine = line;

			velocity += gravity * num;
			velocity -= velocity * drag * num;
			travelTime += num;
		}

		Vector3 hitPos = resultLine.ClosestPoint(targetPoint);

		result.hitDist = (hitPos - targetPoint).Length( );
		result.hitPosition = hitPos;
		result.outVelocity = velocity;
		result.hitTime = travelTime - num;
		return result;
	};
	//uintptr_t shader;
	//int property;
	//void chams(uintptr_t target, Color col, bool npc = false) {
	//	if (!vars::players::chams) return;
	//	if (target) {
	//		if (!property) {
	//			property = reinterpret_cast<int(*)(Str)>(vars::stor::gBase + CO::PropertyToId)(Str(xorstr_(L"_Color")));
	//		}
	//		auto mainRendList = reinterpret_cast<List<uintptr_t>*(*)(uintptr_t)>(vars::stor::gBase + CO::get_Renderers)(target);
	//		for (int idx = 0; idx < mainRendList->get_size(); idx++) {
	//			uintptr_t renderer = mainRendList->get_value(idx);
	//			if (renderer) {
	//				uintptr_t material = reinterpret_cast<uintptr_t(*)(uintptr_t)>(vars::stor::gBase + CO::get_material)(renderer);
	//				if (shader != reinterpret_cast<uintptr_t(*)(uintptr_t)>(vars::stor::gBase + CO::get_shader)(material)) {
	//					if (!shader)
	//						shader = utils::ShaderFind(Str(xorstr_(L"Hidden/Internal-Colored")));
	//					reinterpret_cast<void(*)(uintptr_t, uintptr_t)>(vars::stor::gBase + CO::set_shader)(material, shader);
	//					reinterpret_cast<void(*)(uintptr_t, int, Color)>(vars::stor::gBase + CO::SetColor)(material, property, col);
	//					if (!npc) {
	//						if (vars::players::chams_xqz) {
	//							reinterpret_cast<void(*)(uintptr_t, Str, int)>(vars::stor::gBase + CO::SetInt)(material, Str(xorstr_(L"_ZTest")), 8);
	//						}
	//					}
	//					else {
	//						if (vars::npc::chams_xqz) {
	//							reinterpret_cast<void(*)(uintptr_t, Str, int)>(vars::stor::gBase + CO::SetInt)(material, Str(xorstr_(L"_ZTest")), 8);
	//						}
	//					}
	//				}
	//			}
	//		}
	//	}
	//}
	float LastUpdate = 0.f;
	void update_chams() {
		if (Time::realtimeSinceStartup() > LastUpdate + vars::players::uptime) {
			reinterpret_cast<void(*)()>(vars::stor::gBase + CO::RebuildAll)();
			LastUpdate = Time::realtimeSinceStartup();
		}
	}
	float LastGrade = 0.f;
	void auto_grade(uintptr_t buildingblocc) {
		BuildingBlock* block = reinterpret_cast<BuildingBlock*>(buildingblocc);
		//LogSystem::Log(xorstr_(L"xd"), 5.f);
		if (LocalPlayer::Entity( )->lastSentTickTime( ) > LastGrade + 0.35f
			&& block->CanAffordUpgrade((BuildingGrade)vars::misc::grade_, LocalPlayer::Entity( ))
			&& block->CanChangeToGrade((BuildingGrade)vars::misc::grade_, LocalPlayer::Entity( ))
			&& !block->IsUpgradeBlocked( )) {
			block->UpgradeToGrade((BuildingGrade)vars::misc::grade_, LocalPlayer::Entity( ));
			LastGrade = LocalPlayer::Entity( )->lastSentTickTime( );
		}
	}
	float LastKnock = 0.f; float LastOpen = 0.f; float LastHatch = 0.f;
	void knocker(uintptr_t Door) {
		typedef void(__stdcall* DoorFunction)(uintptr_t, BasePlayer*);
		if (LocalPlayer::Entity( )->lastSentTickTime( ) > LastKnock + 0.5f) {
			((DoorFunction)(vars::stor::gBase + CO::KnockDoor))(Door, LocalPlayer::Entity( ));
			LastKnock = LocalPlayer::Entity( )->lastSentTickTime( );
		}
		if (LocalPlayer::Entity( )->lastSentTickTime( ) > LastOpen + 0.1f) {
			((DoorFunction)(vars::stor::gBase + CO::OpenDoor))(Door, LocalPlayer::Entity( ));
			LastOpen = LocalPlayer::Entity( )->lastSentTickTime( );
		}
		if (LocalPlayer::Entity( )->lastSentTickTime( ) > LastHatch + 0.1f) {
			((DoorFunction)(vars::stor::gBase + CO::OpenHatch))(Door, LocalPlayer::Entity( ));
			LastHatch = LocalPlayer::Entity( )->lastSentTickTime( );
		}
	}
	float LastPickup = 0.f;
	void pickup_player(BasePlayer* ent) {
		typedef void(__stdcall* AssistPlayer)(BasePlayer*, BasePlayer*);
		if (!LocalPlayer::Entity( )->is_teammate(ent)) return;
		if (LocalPlayer::Entity( )->lastSentTickTime( ) > LastPickup + 0.5f) {
			((AssistPlayer)(vars::stor::gBase + CO::AssistPlayer))(ent, LocalPlayer::Entity( ));
			LastPickup = LocalPlayer::Entity( )->lastSentTickTime( );
		}
	}
	void cachePlayer(BasePlayer* player) {
		
		
	}
	void auto_farm_loop(bool weaponmelee, uintptr_t active) {

	}
}
void TestFlying() {
	flyhackPauseTime = Mathf::Max(0.f, flyhackPauseTime - Time::deltaTime());
	bool inAir = false;
	float radius = LocalPlayer::Entity()->GetRadius();
	float height = LocalPlayer::Entity()->GetHeight(false);
	//Vector3 vector = (LocalPlayer::Entity()->lastSentTick()->position() + read(read<uintptr_t>(LocalPlayer::Entity() + 0x4c0) + 0x218)) * 0.5f; //internal Vector3 position; || public class PlayerModel : ListComponent<PlayerModel>, IOnParentDestroying 
	Vector3 vector = (LocalPlayer::Entity()->lastSentTick()->__position() + LocalPlayer::Entity()->transform()->position()) * 0.5f;
	Vector3 vector2 = vector + Vector3(0.f, radius - 1.85f, 0.f);
	Vector3 vector3 = vector + Vector3(0.f, height - radius, 0.f);
	float radius2 = radius - 0.05f;
	bool a = Physics::CheckCapsule(vector2, vector3, radius2, 1503731969, QueryTriggerInteraction::Ignore);
	inAir = !a;

	if (inAir) {
		bool flag = false;

		Vector3 vector4 = (LocalPlayer::Entity()->transform()->position() - LocalPlayer::Entity()->lastSentTick()->__position());
		float num3 = Mathf::Abs(vector4.y);
		float num4 = Misc::Magnitude2D(vector4);

		if (vector4.y >= 0.f) {
			flyhackDistanceVertical += vector4.y;
			flag = true;
		}
		if (num3 < num4) {
			flyhackDistanceHorizontal += num4;
			flag = true;
		}
		float flyhack_forgiveness_interia = 10.0f;
		float flyhack_forgiveness = 1.5f;
		float flyhack_extrusion = 1.85f;
		float num5 = Mathf::Max((flyhackPauseTime > 0.0f) ? flyhack_forgiveness_interia : flyhack_forgiveness, 0.0f);
		float num6 = ((LocalPlayer::Entity()->GetJumpHeight() + num5) * 3);

		VMaxFlyhack = num6;
		if (flyhackDistanceVertical <= (num6)) {
			VFlyhack = flyhackDistanceVertical;
		}
		if (VFlyhack >= VMaxFlyhack)
			VFlyhack = VMaxFlyhack;
		float num7 = Mathf::Max((flyhackPauseTime > 0.0f) ? flyhack_forgiveness_interia : flyhack_forgiveness, 0.0f);
		float num8 = ((5.f + num7) * 3);

		HMaxFlyhack = num8;
		if (flyhackDistanceHorizontal <= (num8)) {
			HFlyhack = flyhackDistanceHorizontal;
		}
		if (HFlyhack >= HMaxFlyhack)
			HFlyhack = HMaxFlyhack;
		if (flag) {
			float num5 = Mathf::Max((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
			float num6 = LocalPlayer::Entity()->GetJumpHeight() + num5;
			if (flyhackDistanceVertical > num6) {
				//return true;
			}
			float num7 = Mathf::Max((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
			float num8 = 5.f + num7;
			if (flyhackDistanceHorizontal > num8) {
				//return true;
			}
		}
	}
	else {
		flyhackDistanceHorizontal = 0.f;
		flyhackDistanceVertical = 0.f;
	}
}

void CheckFlyhack() {
	TestFlying();

	float num5 = Mathf::Max((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
	float num6 = LocalPlayer::Entity()->GetJumpHeight() + num5;
	vars::stuff::max_flyhack = num6;
	if (flyhackDistanceVertical <= num6) {
		vars::stuff::flyhack = flyhackDistanceVertical;
	}

	float num7 = Mathf::Max((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
	float num8 = 5.f + num7;
	vars::stuff::max_hor_flyhack = num8;
	if (flyhackDistanceHorizontal <= num8) {
		vars::stuff::hor_flyhack = flyhackDistanceHorizontal;
	}
}


auto* TargetPlayerA = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer);