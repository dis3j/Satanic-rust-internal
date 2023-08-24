class f_object {
public:


	bool valid;
	DWORD64 entity;
	BasePlayer* entityFarm;
	Vector3 position;
	float dist = 10000.f;
	float realdist = 0.f;
	float fov = 10000.f;
	bool visible = false;

	bool operator<(const f_object& b) { return this->dist < b.dist; }
	bool operator>(const f_object& b) { return this->dist > b.dist; }
	bool operator<=(const f_object& b) { return this->dist <= b.dist; }
	bool operator>=(const f_object& b) { return this->dist >= b.dist; }
	f_object() {
		this->valid = false;
	}
	f_object(Vector3 target) {
		this->valid = false;
		this->position = target;
	}

	static f_object get_closest_object(Vector3 from, const char* namee, Vector3 ignore = Vector3::Zero(), Vector3 ignore2 = Vector3::Zero(), Vector3 ignore3 = Vector3::Zero(), bool classname = false, const char* classnamee = xorstr_(""), float get_dist = 99999.f, bool vis = false, bool y = false) {
		f_object lowest = f_object();

		DWORD64 BaseNetworkable;
		BaseNetworkable = read(vars::stor::gBase + CO::BaseNetworkable, DWORD64); //BaseNetworkable_c 
		DWORD64 EntityRealm = read(BaseNetworkable + 0xB8, DWORD64);
		DWORD64 ClientEntities = read(EntityRealm, DWORD64);
		DWORD64 ClientEntities_list = read(ClientEntities + 0x10, DWORD64);
		DWORD64 ClientEntities_values = read(ClientEntities_list + 0x28, DWORD64);
		
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
				f_object res = f_object();
				if (classname) {
					if (strstr((char*)read(read(read(Object + 0x28, DWORD64), DWORD64) + 0x10, DWORD64), classnamee)) {
						uintptr_t a = read(ObjectClass + 0x30, UINT64);
						float dist = Math::Distance_3D(utils::GetEntityPosition(a), from);
						if (utils::GetEntityPosition(a) != ignore && utils::GetEntityPosition(a) != ignore2 && utils::GetEntityPosition(a) != ignore3) {
							res.valid = dist <= get_dist;
							res.dist = dist;
							res.entity = Entity;
							res.position = utils::GetEntityPosition(a);
							if (res < lowest) lowest = res;
						}
					}
				}
				else {
					if (strstr(buff, namee)) {
						uintptr_t a = read(ObjectClass + 0x30, UINT64);
						float dist = Math::Distance_3D(utils::GetEntityPosition(a), from);
						if (utils::GetEntityPosition(a) != ignore && utils::GetEntityPosition(a) != ignore2 && utils::GetEntityPosition(a) != ignore3) {
							if (vis ? utils::LineOfSight(utils::GetEntityPosition(a), from) : true) {
								if (y) {
									if (utils::GetEntityPosition(a).y > 0) {
										res.valid = dist <= get_dist;
										res.dist = dist;
										res.entity = Entity;
										res.position = utils::GetEntityPosition(a);
										if (res < lowest) lowest = res;
									}
								}
								else {
									res.valid = dist <= get_dist;
									res.dist = dist;
									res.entity = Entity;
									res.position = utils::GetEntityPosition(a);
									if (res < lowest) lowest = res;
								}
							}
						}
					}
				}
			}
			return lowest;
		
	}
	static float MaxMeleeDist(DWORD64 melee, bool localplayer) {
		float pad = 0.1f;
		typedef float(__stdcall* RetF)();
		float time = Time::time();

		float desyncTime = max(time - LocalPlayer::Entity()->lastSentTickTime() - 0.0325f, 0.f);
		float res = pad + desyncTime * 5.5f;
		if (localplayer) {
			res += (1.5f * read(melee + O::BaseMelee::maxDistance, float)); // public float maxDistance;
		}
		return max(res, 0.05f);
	}

	static f_object get_melee_target(BasePlayer* Player, DWORD64 melee) {
		f_object res = f_object();

		if (Player->health() <= 0) return res;
		if (vars::combat::ignore_npc && Player->IsNpc()) return res;
		if (vars::combat::ignore_sleepers && Player->get_flag(PlayerFlags::Sleeping)) return res;
		if (vars::combat::ignore_team && LocalPlayer::Entity()->is_teammate(Player)) return res;
		Vector3 prepos = Player->GetBoneByID(head);
		Vector3 closest_entity = utils::ClosestPoint(LocalPlayer::Entity(), prepos);
		Vector3 closest_local = utils::ClosestPoint(Player, closest_entity);
		float disttoentity = MaxMeleeDist(melee, false);
		float distfromlocal = MaxMeleeDist(melee, true);

		float maxdist = distfromlocal + disttoentity;

		float realdist = (closest_local - closest_entity).Length();

		if (realdist > maxdist) return res;

		Vector3 target;
		if (realdist <= disttoentity) {
			target = closest_entity;
		}
		else {
			Vector3 dir = (closest_entity - closest_local).Normalized();
			target = closest_local + dir * disttoentity;
		}
		res.valid = utils::LineOfSight(closest_local, target);
		if (!res.valid) return res;

		Vector3 lppos = LocalPlayer::Entity()->GetBoneByID(neck);
		res.valid = utils::LineOfSight(lppos, target);
		if (!res.valid) return res;

		res.dist = realdist;
		res.entity = (DWORD64)Player;
		res.position = target;
		return res;
	}
};