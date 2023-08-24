#include <map>
#include <vector>
#pragma once

#include <map>
#include <vector>
#pragma once
static Vector3 get_gravity() {
	return reinterpret_cast<Vector3(*)()>(il2cpp::il2cpp_resolve_icall(xorstr_("UnityEngine.Physics::get_gravity")))();
}
static float get_deltaTime() {
	return reinterpret_cast<float(*)()>(il2cpp::il2cpp_resolve_icall(xorstr_("UnityEngine.Time::get_deltaTime")))();
}
static float get_timeScale() {
	return reinterpret_cast<float(*)()>(il2cpp::il2cpp_resolve_icall(xorstr_("UnityEngine.Time::get_timeScale")))();
}
float GetGravity(int ammoid) {
	switch (ammoid) {
	case 14241751:
		return 1.f;
	case -1234735557:
		return 0.75;
	case 215754713:
		return 0.75;
	case -1023065463:
		return 0.5f;
	case -2097376851:
		return 0.75;
	case -1321651331:
		return 1.25f;
	default:
		return 1.f;
	}
}

float GetBulletSpeed() {
	Item* active = LocalPlayer::Entity()->GetActiveWeapon();
	Weapon tar = active->Info();
	int ammo = active->LoadedAmmo();
	if (ammo == 0) return vars::weapons::fast_bullets ? tar.ammo[0].speed * 1.699 + vars::stuff::testFloat : tar.ammo[0].speed + vars::stuff::testFloat;
	for (Ammo am : tar.ammo) {
		for (int id : am.id) {
			if (id == ammo) {
				return vars::weapons::fast_bullets ? am.speed * 1.699 + vars::stuff::testFloat : am.speed + vars::stuff::testFloat;
			}
		}
		if (am.id[0] == 0) return vars::weapons::fast_bullets ? am.speed * 1.699 + vars::stuff::testFloat : am.speed + vars::stuff::testFloat;
	}
	return vars::weapons::fast_bullets ? 250.f * 1.699 + vars::stuff::testFloat : 250.f + vars::stuff::testFloat;
}
//double CalcBulletDrop(double height, double DepthPlayerTarget, float velocity, float gravity) {
//
//	auto* TargetPlayer = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer);
//	auto transform = TargetPlayer->GetBoneByID(head);
//
//	auto distance = (int)Math::Distance_3D(LocalPlayer::Entity()->GetBoneByID(head), TargetPlayer->GetBoneByID(head));
//
//	double pitch = (atan2(height, DepthPlayerTarget));
//	double BulletVelocityXY = velocity * cos(pitch);
//	double Time = DepthPlayerTarget / BulletVelocityXY;
//
//
//	if (LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo() == 1545779598) //ak 47
//	{
//		double TotalVerticalDrop = 1.000000 * 0.600000;
//
//		if (distance > 400.f) {
//			double TotalVerticalDrop = (0.751 * gravity * Time * Time);
//			return TotalVerticalDrop * 10;
//		}
//		if (distance > 350.f) {
//			double TotalVerticalDrop = (0.745 * gravity * Time * Time);
//			return TotalVerticalDrop * 10;
//		}
//		if (distance > 340.f) {
//			double TotalVerticalDrop = (0.7355 * gravity * Time * Time);
//			return TotalVerticalDrop * 10;
//		}
//		if (distance > 330.f) {
//			double TotalVerticalDrop = (0.731 * gravity * Time * Time);
//			return TotalVerticalDrop * 10;
//		}
//		if (distance > 300.f) {
//			double TotalVerticalDrop = (0.716 * gravity * Time * Time);
//			return TotalVerticalDrop * 10;
//		}
//		if (distance > 250.f) {
//			double TotalVerticalDrop = (0.622 * gravity * Time * Time);
//			return TotalVerticalDrop * 10;
//		}
//		if (distance > 200.f) {
//			double TotalVerticalDrop = (0.5941 * gravity * Time * Time);
//			return TotalVerticalDrop * 10;
//		}
//		if (distance > 150.f) {
//			double TotalVerticalDrop = (0.5727 * gravity * Time * Time);
//			return TotalVerticalDrop * 10;
//		}
//		if (distance > 100.f) {
//			double TotalVerticalDrop = (0.567 * gravity * Time * Time);
//			return TotalVerticalDrop * 10;
//		}
//		if (distance < 100.f) {
//			double TotalVerticalDrop = (0.569 * gravity * Time * Time);
//			return TotalVerticalDrop * 10;
//		}
//
//	}
//
//	else if (LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo() == 1318558775) //MP5A4
//	{
//		double TotalVerticalDrop = 1.000000 * 0.700000;
//
//	}
//	else if (LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo() == -1812555177) //LR-300
//	{
//		double TotalVerticalDrop = 1.000000 * 0.600000;
//
//	}
//	else if (LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo() == -904863145) //Полуавтоматическая винтовка
//	{
//		double TotalVerticalDrop = 1.000000 * 0.600000;
//
//	}
//	else if (LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo() == 1796682209) //Самодельный пистолет-пулемет
//	{
//		double TotalVerticalDrop = 1.000000 * 0.700000;
//	}
//	else if (LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo() == 1373971859) //Револьвер Питон
//	{
//		double TotalVerticalDrop = 1.000000 * 0.700000;
//
//	}
//	else if (LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo() == 818877484) //Полуавтоматический пистолет
//	{
//		double TotalVerticalDrop = 1.000000 * 0.700000;
//
//	}
//	else if (LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo() == -1123473824) //Многозарядный гранатомет
//	{
//		if (distance < 100.f) {
//			double TotalVerticalDrop = (0.58 * gravity * Time * Time);
//			return TotalVerticalDrop * 10;
//		}
//
//	}
//	else if (LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo() == 28201841) //Винтовка M39
//	{
//		double TotalVerticalDrop = 1.000000 * 0.600000;
//	}
//	else if (LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo() == 884424049) //Блочный лук
//	{
//		double TotalVerticalDrop = 0.750000 * 0.004500;
//	}
//	else if (LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo() == 649912614) //Револьвер
//	{
//		double TotalVerticalDrop = 1.000000 * 0.700000;
//
//	}
//	else if (LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo() == -765183617) //Двуствольный дробовик
//	{
//		double TotalVerticalDrop = 1.000000 * 1.000000;
//	}
//	else if (LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo() == -75944661) //eoka
//	{
//		double TotalVerticalDrop = -2;
//
//	}
//	else if (LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo() == 1953903201) //Гвоздомет
//	{
//		if (distance < 55.f) {
//			double TotalVerticalDrop = (0.5465 * gravity * Time * Time);
//			//return TotalVerticalDrop * 10;
//		}
//		else if (distance > 56.f) {
//			double TotalVerticalDrop = (0.5465 * gravity * Time * Time);
//			//return TotalVerticalDrop * 10;
//		}
//		else if (distance > 78.f) {
//			double TotalVerticalDrop = (0.56 * gravity * Time * Time);
//			//return TotalVerticalDrop * 10;
//		}
//
//	}
//	else if (LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo() == -778367295) //Винтовка L96
//	{
//		double TotalVerticalDrop = 1.000000 * 0.600000;
//
//	}
//	else if (LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo() == 1965232394) //Арбалет
//	{
//
//		double TotalVerticalDrop = 0.750000 * 0.005000;
//
//	}
//	else if (LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo() == 1588298435) //Винтовка = болт
//	{
//		double TotalVerticalDrop = 1.000000 * 0.600000;
//
//	}
//
//	else if (LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo() == -852563019) //М92 Беретта
//	{
//
//		double TotalVerticalDrop = 1.000000 * 0.700000;
//
//	}
//	else if (LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo() == 1103488722) //Снежкомет
//	{
//		if (distance < 100.f) {
//			double TotalVerticalDrop = (0.58 * gravity * Time * Time);
//			return TotalVerticalDrop * 10;
//		}
//
//	}
//
//	else if (LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo() == -1758372725) //Пистолет-пулемет Томпсона
//	{
//		double TotalVerticalDrop = 1.000000 * 0.700000;
//
//	}
//	else if (LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo() == -2069578888) //Пулемет М249
//	{
//		double TotalVerticalDrop = 1.000000 * 0.600000;
//	}
//
//	if (distance < 50.f)
//	{
//		double TotalVerticalDrop = (0.451f * gravity * Time * Time);
//		return TotalVerticalDrop * 10;
//	}
//
//	if (distance < 100.f)
//	{
//		double TotalVerticalDrop = (0.460f * gravity * Time * Time);
//		return TotalVerticalDrop * 10;
//	}
//	if (distance >= 100.f)
//	{
//		double TotalVerticalDrop = (0.510f * gravity * Time * Time);
//		return TotalVerticalDrop * 10;
//	}
//
//
//	if (distance >= 150.f)
//	{
//		double TotalVerticalDrop = (0.620f * gravity * Time);
//		return TotalVerticalDrop * 10;
//	}
//
//	if (distance >= 200.f)
//	{
//		double TotalVerticalDrop = (0.672f * gravity * Time);
//		return TotalVerticalDrop * 10;
//	}
//	else
//
//		return 0;
//
//
//
//}
//


namespace a {
	double CalcBulletDrop(double height, double DepthPlayerTarget, float velocity, float gravity) {
		double pitch = (Vector3::my_atan2(height, DepthPlayerTarget));
	
		
		double BulletVelocityXY = velocity * Vector3::my_cos(pitch);
		double Time = DepthPlayerTarget / BulletVelocityXY;
		double TotalVerticalDrop = (0.4905f * gravity * Time * Time);
		return TotalVerticalDrop * 10;
	}

	void Prediction(Vector3 local, Vector3& target, Vector3 targetvel, float bulletspeed, float gravity) {

		//float Dist = Math::Distance_3D(target, local);
		float distance = target.distance(local);
		float BulletTime = distance / bulletspeed;
		BaseProjectile* BaseProjectileA;
		
		Vector3 vel = Vector3(targetvel.x, 0, targetvel.z) * 0.75f;// 0.8
		Vector3 PredictVel = vel * BulletTime;
		target += PredictVel;

	
		double height = target.y - local.y;
		Vector3 dir = target - local;
		float astronaut = sqrt((dir.x * dir.x) + (dir.z * dir.z));
		float drop = CalcBulletDrop(height, astronaut, bulletspeed, gravity);
		target.y += drop;
	}

	void PredictionWeapon(Vector3 local, Vector3& target, Vector3 targetvel, float velonity) {
		BasePlayer* TargetPlayer = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer);
		auto base_projectile = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();
		if (base_projectile == nullptr)
			return;
		float distance_to_travel;
		static Type* type = Type::GetType(xorstr_("ItemModProjectile, Assembly-CSharp"));
		if (type == nullptr)
			return;

		auto mag = base_projectile->primaryMagazine();
		if (mag == nullptr)
			return;

		auto ammo = mag->ammoType();
		if (ammo == nullptr)
			return;

		auto itemModProjectile = ammo->GetComponent<ItemModProjectile>(type); // 0x3189118 for getting Projectile* ref
		if (itemModProjectile == nullptr)
			return;

		Projectile* projectile = itemModProjectile->projectileObject()->Get()->GetComponent<Projectile>(Type::Projectile());

		if (projectile == nullptr)
			return;
	
		

		float m_flBulletSpeed = (itemModProjectile->projectileVelocity() * (base_projectile->projectileVelocityScale() * (vars::weapons::fast_bullets ? 2.499f : 1.0f)));
		float distance = target.distance(LocalPlayer::Entity()->eyes()->position());
		float bullet_time = distance / m_flBulletSpeed;
		//const float m_flTimeStep = 0.005f;
		const float m_flTimeStep = 0.001f;
		float m_flYTravelled{}, m_flYSpeed{}, m_flBulletTime{}, m_flDivider{};

		//float m_flDistanceTo = fVrom.distance(aimpoint);

		for (distance_to_travel = 0.f; distance_to_travel < distance;)
		{
			//float speed_modifier = (aidsware::ui::get_bool(xorstr_("fast bullets")) ? 1.48f : 1.0f) - m_flTimeStep * projectile->drag();
			float speed_modifier = 1.0f - m_flTimeStep * projectile->drag();
			m_flBulletSpeed *= speed_modifier;

			if (m_flBulletSpeed <= 0.f || m_flBulletSpeed >= 10000.f || m_flYTravelled >= 10000.f || m_flYTravelled < 0.f)
				break;

			if (m_flBulletTime > 10.f)
				break;

			m_flYSpeed += (9.8f * projectile->gravityModifier()) * m_flTimeStep;
			m_flYSpeed *= speed_modifier;

			distance_to_travel += m_flBulletSpeed * m_flTimeStep;
			m_flYTravelled += m_flYSpeed * m_flTimeStep;
			m_flBulletTime += m_flTimeStep;
		}
		//float Dist = Math::Distance_3D(target, local);
	


		//Vector3 vel = Vector3(targetvel.x, 0, targetvel.z) * velonity;// 0.8
		Vector3 velocity = targetvel * velonity;
		if (velocity.y > 0.f)
			velocity.y /= 3.25f;
		Vector3 PredictVel = velocity * m_flBulletTime;
	

		target += PredictVel;
		target.y += m_flYTravelled;

	}
	Vector3 get_aim_point(float speed, float gravity) {
		Vector3 ret = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->GetBoneByID(head);
		Prediction(LocalPlayer::Entity()->GetBoneByID(head), ret, reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->newVelocity(), speed, gravity);
		return ret;
	}
}

float GetFov(BasePlayer* Entity, BoneList Bone) {
	Vector2 ScreenPos;
	if (!utils::w2s(Entity->GetBoneByID(Bone), ScreenPos)) return 1000.f;
	return Math::Distance_2D(Vector2(vars::stuff::ScreenWidth / 2, vars::stuff::ScreenHeight / 2), ScreenPos);
}
float GetFovHeli(Vector3 pos) {
	Vector2 ScreenPos;
	if (!utils::w2s(pos, ScreenPos)) return 1000.f;
	return Math::Distance_2D(Vector2(vars::stuff::ScreenWidth / 2, vars::stuff::ScreenHeight / 2), ScreenPos);
}
void StepConstant(Vector2& angles) {
	bool smooth = vars::combat::smooth;
	Vector2 angles_step = angles - LocalPlayer::Entity()->viewangles();
	Math::Normalize(angles_step.x, angles_step.y);

	if (smooth) {
		float factor_pitch = (vars::combat::smooth_factor / 10.f);
		if (angles_step.x < 0.f) {
			if (factor_pitch > std::abs(angles_step.x)) {
				factor_pitch = std::abs(angles_step.x);
			}
			angles.x = LocalPlayer::Entity()->viewangles().x - factor_pitch;
		}
		else {
			if (factor_pitch > angles_step.x) {
				factor_pitch = angles_step.x;
			}
			angles.x = LocalPlayer::Entity()->viewangles().x + factor_pitch;
		}
	}
	if (smooth) {
		float factor_yaw = (vars::combat::smooth_factor / 10.f);
		if (angles_step.y < 0.f) {
			if (factor_yaw > std::abs(angles_step.y)) {
				factor_yaw = std::abs(angles_step.y);
			}
			angles.y = LocalPlayer::Entity()->viewangles().y - factor_yaw;
		}
		else {
			if (factor_yaw > angles_step.y) {
				factor_yaw = angles_step.y;
			}
			angles.y = LocalPlayer::Entity()->viewangles().y + factor_yaw;
		}
	}
}
void do_aimbot(BasePlayer* player) {
	if (vars::combat::psilentbone == 0)
	{
		Vector3 target = player->GetBoneByID(head);
		bool long_neck = vars::misc::long_neck && GetAsyncKeyState(vars::keys::longneck);
		Vector3 local = long_neck ? LocalPlayer::Entity()->GetBoneByID(head) + Vector3(0, 1.15, 0) : LocalPlayer::Entity()->GetBoneByID(head);
		a::Prediction(local, target, player->newVelocity(), GetBulletSpeed(), GetGravity(LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo()));
		Vector2 Offset = Math::CalcAngle(local, target) - LocalPlayer::Entity()->viewangles();
		Math::Normalize(Offset.y, Offset.x);
		Vector2 AngleToAim = LocalPlayer::Entity()->viewangles() + Offset;
		if (vars::combat::smooth) {
			StepConstant(AngleToAim);
		}
		Math::Normalize(AngleToAim.y, AngleToAim.x);
		LocalPlayer::Entity()->set_viewangles(AngleToAim);
	}
	if (vars::combat::psilentbone == 1)
	{
		Vector3 target;
		int yeet11 = rand() % 100;
		if (yeet11 > 10) {
			target = player->GetBoneByID(spine4);
		}
		else {
			target = player->GetBoneByID(spine1);
		}
		bool long_neck = vars::misc::long_neck && GetAsyncKeyState(vars::keys::longneck);
		Vector3 local = long_neck ? LocalPlayer::Entity()->GetBoneByID(head) + Vector3(0, 1.15, 0) : LocalPlayer::Entity()->GetBoneByID(head);
		a::Prediction(local, target, player->newVelocity(), GetBulletSpeed(), GetGravity(LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo()));
		Vector2 Offset = Math::CalcAngle(local, target) - LocalPlayer::Entity()->viewangles();
		Math::Normalize(Offset.y, Offset.x);
		Vector2 AngleToAim = LocalPlayer::Entity()->viewangles() + Offset;
		if (vars::combat::smooth) {
			StepConstant(AngleToAim);
		}
		Math::Normalize(AngleToAim.y, AngleToAim.x);
		LocalPlayer::Entity()->set_viewangles(AngleToAim);
	}
	if (vars::combat::psilentbone == 2)
	{
		Vector3 target;
		int num = rand() % 400;
		if (num > 90)
		{
			target = player->GetBoneByID(head);
		}
		else if (num < 90 && num > 80)
		{
			target = player->GetBoneByID(neck);
		}
		else if (num < 80 && num > 70)
		{
			target = player->GetBoneByID(r_hip);
		}
		else if (num < 70 && num > 60)
		{
			target = player->GetBoneByID(pelvis);
		}
		else if (num < 60 && num > 50)
		{
			target = player->GetBoneByID(l_clavicle);
		}
		else if (num < 50 && num > 40)
		{
			target = player->GetBoneByID(l_upperarm);
		}
		else if (num < 40 && num > 30)
		{
			target = player->GetBoneByID(l_foot);
		}
		else if (num < 30 && num > 20)
		{
			target = player->GetBoneByID(r_foot);
		}
		else if (num < 20 && num > 10)
		{
			target = player->GetBoneByID(l_hand);
		}
		else if (num < 10)
		{
			target = player->GetBoneByID(r_hand);
		}
		else
		{
			target = player->GetBoneByID(spine1);
		}
		bool long_neck = vars::misc::long_neck && GetAsyncKeyState(vars::keys::longneck);
		Vector3 local = long_neck ? LocalPlayer::Entity()->GetBoneByID(head) + Vector3(0, 1.15, 0) : LocalPlayer::Entity()->GetBoneByID(head);
		a::Prediction(local, target, player->newVelocity(), GetBulletSpeed(), GetGravity(LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo()));
		Vector2 Offset = Math::CalcAngle(local, target) - LocalPlayer::Entity()->viewangles();
		Math::Normalize(Offset.y, Offset.x);
		Vector2 AngleToAim = LocalPlayer::Entity()->viewangles() + Offset;
		if (vars::combat::smooth) {
			StepConstant(AngleToAim);
		}
		Math::Normalize(AngleToAim.y, AngleToAim.x);
		LocalPlayer::Entity()->set_viewangles(AngleToAim);
	}
	if (vars::combat::psilentbone == 3)
	{
		Vector3 target;
		int yeet1 = rand() % 400;
		if (yeet1 > 50) {
			target = player->GetBoneByID(head);
		}
		else {
			target = player->GetBoneByID(spine1);
		}
		if (!LocalPlayer::Entity() || !player) { return; }
		if (!LocalPlayer::Entity()->GetActiveWeapon() || player->IsDestroyed()) { return; }
		bool long_neck = vars::misc::long_neck && GetAsyncKeyState(vars::keys::longneck);
		Vector3 local = long_neck ? LocalPlayer::Entity()->GetBoneByID(head) + Vector3(0, 1.15, 0) : LocalPlayer::Entity()->GetBoneByID(head);
		a::Prediction(local, target, player->newVelocity(), GetBulletSpeed(), GetGravity(LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo()));
		Vector2 Offset = Math::CalcAngle(local, target) - LocalPlayer::Entity()->viewangles();
		Math::Normalize(Offset.y, Offset.x);
		Vector2 AngleToAim = LocalPlayer::Entity()->viewangles() + Offset;
		if (vars::combat::smooth) {
			StepConstant(AngleToAim);
		}
		Math::Normalize(AngleToAim.y, AngleToAim.x);
		LocalPlayer::Entity()->set_viewangles(AngleToAim);
	}

}






