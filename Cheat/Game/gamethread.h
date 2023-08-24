//void game_thread_loop() {
//	
//	if (!LocalPlayer::Entity()) return;
//
//	DWORD64 BaseNetworkable;
//	BaseNetworkable = read(vars::stor::gBase + CO::BaseNetworkable, DWORD64); //BaseNetworkable_c 
//	DWORD64 EntityRealm = read(BaseNetworkable + 0xB8, DWORD64);
//	DWORD64 ClientEntities = read(EntityRealm, DWORD64);
//	DWORD64 ClientEntities_list = read(ClientEntities + 0x10, DWORD64);
//	DWORD64 ClientEntities_values = read(ClientEntities_list + 0x28, DWORD64);
//	if (!ClientEntities_values) return;
//	int EntityCount = read(ClientEntities_values + 0x10, int);
//	DWORD64 EntityBuffer = read(ClientEntities_values + 0x18, DWORD64);
//	for (int i = 0; i <= EntityCount; i++)
//	{
//
//		DWORD64 Entity = read(EntityBuffer + 0x20 + (i * 0x8), DWORD64);
//		if (Entity <= 100000) continue;
//		DWORD64 Object = read(Entity + 0x10, DWORD64);
//		if (Object <= 100000) continue;
//		DWORD64 ObjectClass = read(Object + 0x30, DWORD64);
//		if (ObjectClass <= 100000) continue;
//		pUncStr name = read(ObjectClass + 0x60, pUncStr);
//		if (!name) continue;
//		char* buff = name->stub;
//		BasePlayer* Player = (BasePlayer*)read(Object + 0x28, DWORD64);
//		if (strstr(buff, xorstr_("Local"))) {
//			BasePlayer* Player = (BasePlayer*)read(Object + 0x28, DWORD64);
//			BasePlayer* Local = (BasePlayer*)read(Object + 0x28, DWORD64);
//			if (!read(Player + O::BasePlayer::playerModel, DWORD64)) continue;
//
//			/*lol::update_chams();
//			chamslocal(Player);*/
//
//
//			HandChams();
//		}
//
//		if (strstr(buff, xorstr_("player.prefab")))
//		{
//			BasePlayer* Player = (BasePlayer*)read(Object + 0x28, DWORD64);
//			BasePlayer* Local = (BasePlayer*)read(Object + 0x28, DWORD64);
//			if (!read(Player + O::BasePlayer::playerModel, DWORD64)) continue;
//			lol::update_chams();
//			chams(Player);
//		}
//			if (!reinterpret_cast<BaseEntity*>(Entity)->IsValid( )) { continue; }
//			if (!reinterpret_cast<Component*>(Entity)->gameObject( )) { continue; }
//			if (strstr(buff, xorstr_("Local"))) { continue; }
//
//			Item* weapon = LocalPlayer::Entity()->GetActiveWeapon();
//			DWORD64 active = weapon->entity( );
//			char* classname = weapon->ClassName();
//
//			bool weaponmelee = weapon && classname && (strcmp(classname, xorstr_("BaseMelee")) || strcmp(classname, xorstr_("Jackhammer")));
//			if (reinterpret_cast<BaseCombatEntity*>(Entity)->IsPlayer()) {
//				BasePlayer* lol = (BasePlayer*)Entity;
//
//				if (!lol) continue;
//
//				if (vars::misc::auto_revive) {
//					UINT64 gameObject = read(ObjectClass + 0x30, UINT64);
//					Vector3 local = utils::ClosestPoint(LocalPlayer::Entity(), utils::GetEntityPosition(gameObject));
//					if (vars::misc::auto_revive && (BasePlayer*)Entity && lol->get_flag(PlayerFlags::Wounded) && Math::Distance_3D(local, utils::GetEntityPosition(gameObject)) < 3.f && LocalPlayer::Entity()->GetKeyState(Button::USE)) {
//						lol::pickup_player((BasePlayer*)Entity);
//					}
//				}
//				if (vars::combat::silent_melee && weaponmelee && Math::Distance_3D(lol->GetBoneByID(head), LocalPlayer::Entity()->GetBoneByID(head)) <= vars::combat::reach) {
//					f_object target = f_object::get_melee_target((BasePlayer*)Entity, active);
//					lol::do_attack(target, active, true);
//				}
//			}
//			if (vars::misc::auto_pickup && strstr(buff, xorstr_("/collectable/"))) {
//				UINT64 gameObject = read(ObjectClass + 0x30, UINT64);
//				Vector3 local = utils::ClosestPoint(LocalPlayer::Entity(), utils::GetEntityPosition(gameObject));
//				if (Math::Distance_3D(local, utils::GetEntityPosition(gameObject)) < 3.f) {
//					utils::ServerRPC(Entity, Str(xorstr_(L"Pickup")));
//				}
//			}
//			if (vars::misc::annoyer && strstr((char*)read(read(Entity, DWORD64) + 0x10, DWORD64), xorstr_("Door"))) {
//				UINT64 gameObject = read(ObjectClass + 0x30, UINT64);
//				Vector3 local = utils::ClosestPoint(LocalPlayer::Entity(), utils::GetEntityPosition(gameObject));
//				if (Entity && Math::Distance_3D(local, utils::GetEntityPosition(gameObject)) < 3.f) {
//					lol::knocker(Entity);
//				}
//			}
//		}
//	}
