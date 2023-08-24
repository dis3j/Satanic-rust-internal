
#pragma once
#include <direct.h>

CSimpleIniA cfg; //инициализируем объект

#pragma region Config Color

void SaveColorValue(const char* pSection, std::string name, float a_Value[4])
{
    int R, G, B, A;
    R = a_Value[0] * 1000;
    G = a_Value[1] * 1000;
    B = a_Value[2] * 1000;
    A = a_Value[3] * 1000;
    cfg.SetLongValue(pSection, (name + "_R").c_str(), R);
    cfg.SetLongValue(pSection, (name + "_G").c_str(), G);
    cfg.SetLongValue(pSection, (name + "_B").c_str(), B);
    cfg.SetLongValue(pSection, (name + "_A").c_str(), A);
}


void LoadColorValue(const char* pSection, std::string name, float a_Value[4])
{
    float R, G, B, A;
    R = cfg.GetLongValue(pSection, (name + "_R").c_str(), a_Value[0]);
    G = cfg.GetLongValue(pSection, (name + "_G").c_str(), a_Value[1]);
    B = cfg.GetLongValue(pSection, (name + "_B").c_str(), a_Value[2]);
    A = cfg.GetLongValue(pSection, (name + "_A").c_str(), a_Value[3]);
    a_Value[0] = R / 1000; a_Value[1] = G / 1000; a_Value[2] = B / 1000; a_Value[3] = A / 1000;
}

#pragma endregion 

inline bool folder_exists(const char* foldername)
{
    struct stat st;
    stat(foldername, &st);
    return st.st_mode & S_IFDIR;
}
void SaveCFG(std::string FileName)
{
    DWORD SerialNumber;

    GetVolumeInformation(L"C:\\Satanic", 0, 0, &SerialNumber, 0, 0, 0, 0);

    char Path[0x100];
    sprintf(Path, ("C:\\Satanic\\"));

    if (!folder_exists(Path))
        _mkdir(Path);
    cfg.SetUnicode();
    char result[0x100];
    sprintf(result, ("C:\\Satanic\\%s.ini"), FileName);

    cfg.SetBoolValue("AimBot", "Perfect Silent", vars::combat::psilent);
    cfg.SetBoolValue("AimBot", "Simple Aimbot", vars::combat::aimbot);
    cfg.SetLongValue("AimBot", "AimBone", vars::combat::psilentbone);
    cfg.SetLongValue("AimBot", "Fov Value", vars::combat::fov);
    cfg.SetLongValue("AimBot", "Draw Fov style", vars::players::fovstyle);
    cfg.SetBoolValue("AimBot", "Draw fov", vars::combat::visualize_fov);
    SaveColorValue("Visuals",  "Fov  Color", vars::colors::fov_color);
    cfg.SetBoolValue("AimBot", "Heli Aim", vars::combat::psilentheli);
    cfg.SetBoolValue("AimBot", "Manipulator", vars::combat::manipulator);
    cfg.SetLongValue("AimBot", "Manipulator Key", vars::keys::manipulated_key);
    cfg.SetBoolValue("AimBot", "Auto Fire", vars::combat::autoshoot);
    cfg.SetLongValue("AimBot", "Auto Fire type", vars::combat::desync_autoshoot_type);
    cfg.SetBoolValue("AimBot", "Time Shot", vars::combat::instakill);
    cfg.SetLongValue("AimBot", "Time Shot Key", vars::keys::instakill);
    cfg.SetBoolValue("AimBot", "Visual Projectile", vars::weapons::local_scale);
    cfg.SetLongValue("AimBot", "Bullet Size x", vars::weapons::bullet_sizex);
    cfg.SetLongValue("AimBot", "Bullet Size y", vars::weapons::bullet_sizey);
    cfg.SetLongValue("AimBot", "Bullet Size z", vars::weapons::bullet_sizez);
    cfg.SetBoolValue("AimBot", "Ignore NPC", vars::combat::ignore_npc);
    cfg.SetBoolValue("AimBot", "Ignore Teammates", vars::combat::ignore_team);
    cfg.SetBoolValue("AimBot", "Ignore Sleeping", vars::combat::ignore_sleepers);
    cfg.SetBoolValue("AimBot", "Recoil Control", vars::weapons::no_recoil);
    cfg.SetLongValue("AimBot", "Recoil", vars::weapons::recoil_control);
    cfg.SetBoolValue("AimBot", "Anti Spread", vars::weapons::no_spread);
    cfg.SetLongValue("AimBot", "Anti Spread value", vars::weapons::no_spreadvalue);
    cfg.SetBoolValue("AimBot", "Remove Sway", vars::weapons::no_sway);
   cfg.SetBoolValue("AimBot", "Fast Bullets", vars::weapons::fast_bullets);
    cfg.SetBoolValue("AimBot", "Thick Bullets", vars::weapons::thick_bullet);
    //cfg.SetLongValue("AimBot", "Thick", vars::weapons::thickness);
    cfg.SetBoolValue("AimBot", "Instant Eoka", vars::weapons::eokatap);
    cfg.SetBoolValue("AimBot", "Fast Bow", vars::weapons::fastbow);
    cfg.SetBoolValue("AimBot", "Rapid Fire", vars::weapons::rapid_fire);
    cfg.SetBoolValue("AimBot", "Auto Reload", vars::combat::autoreload);
    cfg.SetBoolValue("AimBot", "No Attack Animation", vars::weapons::remove_attack_anim);
    cfg.SetBoolValue("AimBot", "Insta Charge Compound", vars::weapons::compound);
    cfg.SetBoolValue("AimBot", "Automatic", vars::weapons::automatic);
    cfg.SetBoolValue("AimBot", "Can Hold Items", vars::weapons::minicopter_aim);
    cfg.SetBoolValue("AimBot", "Jump Shoot", vars::misc::can_attack);
    cfg.SetBoolValue("AimBot", "Fake Distance", vars::weapons::spoof_hitdistance);
    cfg.SetLongValue("AimBot", "Distance Value", vars::weapons::hitdistance);
    cfg.SetBoolValue("AimBot", "Bullet Teleport", vars::combat::bullet_tp);
    cfg.SetBoolValue("AimBot", "Magic Heli", vars::combat::always_heli_rotor);
    cfg.SetBoolValue("AimBot", "Long Neck", vars::misc::long_neck);
    cfg.SetLongValue("AimBot", "Long Neck Key", vars::keys::longneck);
    cfg.SetBoolValue("AimBot", "Desync", vars::combat::desync);
    cfg.SetLongValue("AimBot", "Desync Key", vars::keys::desync);
    cfg.SetBoolValue("AimBot", "Pierce Materials", vars::weapons::penetrate);
    cfg.SetBoolValue("Visuals", "Enable Player", vars::visuals::playerEspEnable);
    cfg.SetLongValue("Visuals", "Box Style", vars::players::boxstyle);
    cfg.SetLongValue("Visuals", "Healthbar Style", vars::players::healthbarscolortyle);
    cfg.SetLongValue("Visuals", "Healthbar Style Color", vars::players::healthbarscolor);
    cfg.SetBoolValue("Visuals", "Name", vars::players::name);
    cfg.SetLongValue("Visuals", "Name Position", vars::players::namePos);
    cfg.SetBoolValue("Visuals", "Distance", vars::players::distance);
    cfg.SetBoolValue("Visuals", "Fill Box", vars::players::fillbox);
    cfg.SetBoolValue("Visuals", "Health Bar", vars::players::healthbar);
    cfg.SetBoolValue("Visuals", "Weapon", vars::players::weapon);
    cfg.SetLongValue("Visuals", "Weapon Position", vars::players::weaponPos);
    cfg.SetBoolValue("Visuals", "Skeleton", vars::players::skeleton);
    //cfg.SetBoolValue("Visuals", "Chams", vars::players::chams);
    //cfg.SetLongValue("Visuals", "Chams Style", vars::players::chams_type);
    cfg.SetBoolValue("Visuals", "Target Tracers", vars::players::targetline);
    cfg.SetLongValue("Visuals", "Target Tracer Position", vars::players::targetline_pos);
    cfg.SetBoolValue("Visuals", "Target Player Belt", vars::players::belt);
    cfg.SetBoolValue("Visuals", "Out Of Arrows", vars::players::oof_arrows);
    cfg.SetLongValue("Visuals", "Out Of Arrows style", vars::players::Outstyle);
    cfg.SetBoolValue("Visuals", "lookingDirection", vars::visuals::lookingDirection);
    cfg.SetLongValue("Visuals", "Max dist", vars::players::maxdisctanse);
   // cfg.SetLongValue("Visuals", "Font Size", vars::misc::fotsize);
    cfg.SetBoolValue("Visuals", "Ignore Sleepers", vars::players::sleeperignore);
    SaveColorValue("Visuals", "Skeleton  Color", vars::visible::skeleton_color);
    SaveColorValue("Visuals", "Esp Color", vars::invisible::box_color);
    SaveColorValue("Visuals", "Teammate Color", vars::colors::team_color);
    SaveColorValue("Visuals", "Sleepers Color", vars::colors::sleep_color);
    cfg.SetBoolValue("Npc", "Enable Npc", vars::visuals::NpcEspEnable);
    SaveColorValue("Npc", "Custom Health Color", vars::colors::Player_custom_healthColor);
    SaveColorValue("Npc", "Gradient Two", vars::colors::gradient_2);
    SaveColorValue("Npc", "Gradient One", vars::colors::gradient_1);
    cfg.SetLongValue("Npc", "Box Style", vars::npc::boxstyle);
    cfg.SetLongValue("Npc", "Healthbar Style", vars::npc::healthbarscolortyle);
    cfg.SetLongValue("Npc", "Healthbar Style Color", vars::npc::healthbarscolor);
    cfg.SetBoolValue("Npc", "Name", vars::npc::name);
    cfg.SetBoolValue("Npc", "Health Bar", vars::npc::healthbar);
    cfg.SetBoolValue("Npc", "Distance", vars::npc::distance);
    cfg.SetBoolValue("Npc", "Fill Box", vars::npc::fillbox);
    cfg.SetBoolValue("Npc", "Skeleton", vars::npc::skeleton);
    cfg.SetBoolValue("Npc", "Weapon", vars::npc::weapon);
    SaveColorValue("Npc", "Box  Color", vars::colors::npc_box_color);
    SaveColorValue("Npc", "Name Color", vars::colors::npc_name_color);
    SaveColorValue("Npc", "Skeleton Color", vars::colors::npc_skeleton_color);
    SaveColorValue("Npc", "Weapon Color", vars::colors::npc_weapons_color);
    SaveColorValue("Npc", "Custom Health Color", vars::colors::npc_custom_healthColor);
    SaveColorValue("Npc", "Gradient Two", vars::colors::gradient_2);
    SaveColorValue("Npc", "Gradient One", vars::colors::gradient_1);

    cfg.SetBoolValue("Visuals", "cadicall", vars::crosshair::cadicall);
    SaveColorValue("Visuals", "cadicall color", vars::colors::cadicall_color);
    cfg.SetBoolValue("Visuals", "default", vars::crosshair::default);
    SaveColorValue("Visuals", "default color", vars::colors::default_color);
    cfg.SetBoolValue("Visuals", "dot", vars::crosshair::dot);
    SaveColorValue("Visuals", "dot color", vars::colors::dot_color);
    cfg.SetBoolValue("Visuals", "Swastika", vars::crosshair::swastika);
    SaveColorValue("Visuals", "Swastika color", vars::colors::swaston_color);
    cfg.SetLongValue("Visuals", "Size1", vars::crosshair::razmer);
    cfg.SetLongValue("Visuals", "Speed2", vars::crosshair::speed);
    cfg.SetBoolValue("Visuals", "Custom Cross", vars::crosshair::custom);
    SaveColorValue("Visuals", "Custom Cross color", vars::colors::custom_color);
    cfg.SetLongValue("Visuals", "Gap", vars::crosshair::gap);
    cfg.SetLongValue("Visuals", "Length", vars::crosshair::length);

    cfg.SetLongValue("Misc", "Player Fov", vars::misc::fov);
    cfg.SetBoolValue("Misc", "AspectRatio", vars::misc::aspectraratio);
    cfg.SetLongValue("Misc", "AspectRatio float", vars::misc::aspectraratiofloat);
    cfg.SetBoolValue("Misc", "Zoom", vars::visuals::zoom); 
    cfg.SetLongValue("Misc", "Zoom key", vars::keys::zoom);
    cfg.SetBoolValue("Misc", "Sphere", vars::visuals::sphere);
    cfg.SetBoolValue("Misc", "Noclip Bar", vars::misc::flyhack_indicator);
    cfg.SetBoolValue("Misc", "Reload Coldown", vars::misc::reload_coldown);
    cfg.SetBoolValue("Misc", "Desync Indicator", vars::combat::instakill_indicator);
    cfg.SetBoolValue("Misc", "Show Target Name", vars::visuals::target_name);
    cfg.SetBoolValue("Misc", "Hit Logs", vars::misc::hit_logs);
    cfg.SetBoolValue("Misc", "Gesture spam", vars::misc::gesture_spam);
    
    cfg.SetBoolValue("Misc", "Keybinds", vars::visuals::keybinds);
    cfg.SetBoolValue("Misc", "Side Indicator", vars::visuals::GameSense);
    cfg.SetLongValue("Misc", "Hit Effect", vars::misc::hitmaterial);
    cfg.SetBoolValue("Misc", "Bullet Tracers", vars::misc::bullet_tracers);
   // cfg.SetBoolValue("Misc", "Hitmarker", vars::misc::hitmarker);
    cfg.SetBoolValue("Misc", "Movement Line", vars::misc::movement_line );
    cfg.SetBoolValue("Misc", "Vis. Predict", vars::combat::visualize_prediction);
    cfg.SetBoolValue("Misc", "Nightmode (Ambient)", vars::misc::bright_ambient);
    cfg.SetBoolValue("Misc", "Local Bones", vars::misc::local_bones);
    cfg.SetBoolValue("Misc", "Custom Time", vars::misc::custom_time);
    cfg.SetLongValue("Misc", "Time", vars::misc::time);
    cfg.SetBoolValue("Misc", "Hand Chams", vars::visuals::hand_chams);
    cfg.SetLongValue("Misc", "Chams Style", vars::visuals::hand_chams_type);
    cfg.SetBoolValue("Misc", "Night Stars", vars::misc::night_stars);
    cfg.SetLongValue("Misc", "Stars Amount", vars::misc::stars);
    cfg.SetBoolValue("Misc", "Rayleigh Changer", vars::misc::rayleigh_changer);
    cfg.SetLongValue("Misc", "Rayleigh Amount", vars::misc::rayleigh);
    cfg.SetBoolValue("Misc", "Mie Changer", vars::misc::mie_changer);
    cfg.SetLongValue("Misc", "Mie Amount", vars::misc::mie);
    cfg.SetBoolValue("Misc", "Brightness Changer", vars::misc::brightness_changer);
    cfg.SetLongValue("Misc", "Brightness Amount", vars::misc::brightness);
    cfg.SetBoolValue("Misc", "Clouds", vars::misc::облака);
    cfg.SetLongValue("Misc", "Clouds Amount", vars::misc::облакафлоат);
    cfg.SetBoolValue("Misc", "Rain", vars::misc::Дождь);
    cfg.SetBoolValue("Misc", "Fog", vars::misc::туман);
    cfg.SetBoolValue("Misc", "Storm", vars::misc::шторм);
    cfg.SetBoolValue("Misc", "Rayleigh Changer", vars::misc::rayleigh_changer);
    cfg.SetBoolValue("Misc", "Fake Admin", vars::misc::fakeadmin);
    cfg.SetBoolValue("Misc", "Follow Projectile", vars::combat::followprojectile);
    cfg.SetLongValue("Misc", "Projectile Key", vars::keys::followprojectile);
    cfg.SetBoolValue("Misc", "Fast Loot", vars::misc::fast_loot);
    cfg.SetBoolValue("Misc", "No Collision", vars::misc::walker);
    cfg.SetLongValue("Misc", "Model State", vars::misc::modelstate);
    cfg.SetLongValue("Misc", "Model State Key", vars::keys::ModelState);
    cfg.SetBoolValue("Misc", "Omni-Sprint", vars::misc::omnidirectional_sprinting);
    cfg.SetBoolValue("Misc", "Interactive Debug", vars::misc::interactive_debug);
    cfg.SetLongValue("Misc", "Debug Key", vars::keys::debugging);
    cfg.SetBoolValue("Misc", "Hitsound", vars::misc::custom_hitsound);
    cfg.SetLongValue("Misc", "Sound", vars::misc::hitsound_rejim);
    cfg.SetBoolValue("Misc", "Fake-Lag", vars::misc::fake_lag);
    cfg.SetLongValue("Misc", "Fake-Lag style", vars::misc::fake_lag_type);
    cfg.SetBoolValue("Misc", "Spiderman", vars::misc::spiderman);
    cfg.SetBoolValue("Misc", "Fly Auto Stopper", vars::misc::fly_auto_stopper);
    cfg.SetBoolValue("Misc", "No Fall Damage", vars::misc::no_fall);
    cfg.SetBoolValue("Misc", "Infinity Jump", vars::misc::inf_jump);
    cfg.SetBoolValue("Misc", "Fake Shots", vars::misc::weapon_spam);
    cfg.SetLongValue("Misc", "Shots Key", vars::keys::weaponspam);
    cfg.SetBoolValue("Misc", "Silent Melee", vars::combat::silent_melee);
//    cfg.SetBoolValue("Misc", "Insta Revive", vars::misc::auto_revive);
    cfg.SetBoolValue("Misc", "Auto Pick Up", vars::misc::auto_pickup);
    cfg.SetBoolValue("Misc", "Auto Healing", vars::misc::faster_healing);
    cfg.SetBoolValue("Misc", "Speed Hack", vars::misc::speedhack);
    cfg.SetLongValue("Misc", "Speed Hack Key", vars::keys::speedkey);
    cfg.SetBoolValue("Misc", "Anti-Aim", vars::misc::anti_aim);
    cfg.SetLongValue("Misc", "Anti-Aim style", vars::misc::anti_aim_yaw);
#pragma region Resourse Color
    /* SaveColorValue("Resourse - Color", "Stone - Ore Color", Bools::ResourcesColor::StoneOreColor);
     SaveColorValue("Resourse - Color", "Mettal - Ore Color", Bools::ResourcesColor::MettalOreColor);
     SaveColorValue("Resourse - Color", "Sulfure - Ore Color", Bools::ResourcesColor::SulfureOreColor);*/
#pragma endregion

#pragma region Construction Color
     /*
     SaveColorValue("Construction - Color", "Cupboard Color", Bools::ConstructionColor::CupboardColor);
     SaveColorValue("Construction - Color", "Large Wood Box Color", Bools::ConstructionColor::LargeWoodBoxColor);
     SaveColorValue("Construction - Color", "Small Stash Color", Bools::ConstructionColor::SmallStashColor);*/
#pragma endregion 

    cfg.SaveFile(result);
}
void CREATY(std::string FileName)
{
    DWORD SerialNumber;

    GetVolumeInformation(L"C:\\Satanic", 0, 0, &SerialNumber, 0, 0, 0, 0);

    char Path[0x100];
    sprintf(Path, ("C:\\Satanic\\"));

    if (!folder_exists(Path))
        _mkdir(Path);
    cfg.SetUnicode();
    char result[0x100];
    sprintf(result, ("C:\\Satanic\\%s.ini"), FileName);
    cfg.SetBoolValue("AimBot", "Perfect Silent", vars::combat::psilent);
    cfg.SetBoolValue("AimBot", "Simple Aimbot", vars::combat::aimbot);
    cfg.SetLongValue("AimBot", "AimBone", vars::combat::psilentbone);
    cfg.SetLongValue("AimBot", "Fov Value", vars::combat::fov);
    cfg.SetLongValue("AimBot", "Draw Fov style", vars::players::fovstyle);
    cfg.SetBoolValue("AimBot", "Draw fov", vars::combat::visualize_fov);
    SaveColorValue("Visuals", "Fov  Color", vars::colors::fov_color);
    cfg.SetBoolValue("AimBot", "Heli Aim", vars::combat::psilentheli);
    cfg.SetBoolValue("AimBot", "Manipulator", vars::combat::manipulator);
    cfg.SetLongValue("AimBot", "Manipulator Key", vars::keys::manipulated_key);
    cfg.SetBoolValue("AimBot", "Auto Fire", vars::combat::autoshoot);
    cfg.SetLongValue("AimBot", "Auto Fire type", vars::combat::desync_autoshoot_type);
    
    cfg.SetBoolValue("AimBot", "Time Shot", vars::combat::instakill);
    cfg.SetLongValue("AimBot", "Time Shot Key", vars::keys::instakill);
    cfg.SetBoolValue("AimBot", "Visual Projectile", vars::weapons::local_scale);
    cfg.SetLongValue("AimBot", "Bullet Size x", vars::weapons::bullet_sizex);
    cfg.SetLongValue("AimBot", "Bullet Size y", vars::weapons::bullet_sizey);
    cfg.SetLongValue("AimBot", "Bullet Size z", vars::weapons::bullet_sizez);
    cfg.SetBoolValue("AimBot", "Ignore NPC", vars::combat::ignore_npc);
    cfg.SetBoolValue("AimBot", "Ignore Teammates", vars::combat::ignore_team);
    cfg.SetBoolValue("AimBot", "Ignore Sleeping", vars::combat::ignore_sleepers);
    cfg.SetBoolValue("AimBot", "Recoil Control", vars::weapons::no_recoil);
    cfg.SetLongValue("AimBot", "Recoil", vars::weapons::recoil_control);
    cfg.SetBoolValue("AimBot", "Anti Spread", vars::weapons::no_spread);
    cfg.SetLongValue("AimBot", "Anti Spread value", vars::weapons::no_spreadvalue);
    cfg.SetBoolValue("AimBot", "Remove Sway", vars::weapons::no_sway);
    cfg.SetBoolValue("AimBot", "Fast Bullets", vars::weapons::fast_bullets);
    cfg.SetBoolValue("AimBot", "Thick Bullets", vars::weapons::thick_bullet);
    //cfg.SetLongValue("AimBot", "Thick", vars::weapons::thickness);
    cfg.SetBoolValue("AimBot", "Instant Eoka", vars::weapons::eokatap);
    cfg.SetBoolValue("AimBot", "Fast Bow", vars::weapons::fastbow);
    cfg.SetBoolValue("AimBot", "Rapid Fire", vars::weapons::rapid_fire);
    cfg.SetBoolValue("AimBot", "Auto Reload", vars::combat::autoreload);
    cfg.SetBoolValue("AimBot", "No Attack Animation", vars::weapons::remove_attack_anim);
    cfg.SetBoolValue("AimBot", "Insta Charge Compound", vars::weapons::compound);
    cfg.SetBoolValue("AimBot", "Automatic", vars::weapons::automatic);
    cfg.SetBoolValue("AimBot", "Can Hold Items", vars::weapons::minicopter_aim);
    cfg.SetBoolValue("AimBot", "Jump Shoot", vars::misc::can_attack);
    cfg.SetBoolValue("AimBot", "Fake Distance", vars::weapons::spoof_hitdistance);
    cfg.SetLongValue("AimBot", "Distance Value", vars::weapons::hitdistance);
    cfg.SetBoolValue("AimBot", "Bullet Teleport", vars::combat::bullet_tp);
    cfg.SetBoolValue("AimBot", "Magic Heli", vars::combat::always_heli_rotor);
    cfg.SetBoolValue("AimBot", "Long Neck", vars::misc::long_neck);
    cfg.SetLongValue("AimBot", "Long Neck Key", vars::keys::longneck);
    cfg.SetBoolValue("AimBot", "Desync", vars::combat::desync);
    cfg.SetLongValue("AimBot", "Desync Key", vars::keys::desync);
    cfg.SetBoolValue("AimBot", "Pierce Materials", vars::weapons::penetrate);
    cfg.SetBoolValue("Visuals", "Enable Player", vars::visuals::playerEspEnable);
    cfg.SetLongValue("Visuals", "Box Style", vars::players::boxstyle);
    cfg.SetLongValue("Visuals", "Healthbar Style", vars::players::healthbarscolortyle);
    cfg.SetLongValue("Visuals", "Healthbar Style Color", vars::players::healthbarscolor);
    cfg.SetBoolValue("Visuals", "Name", vars::players::name);
    cfg.SetLongValue("Visuals", "Name Position", vars::players::namePos);
    cfg.SetBoolValue("Visuals", "Distance", vars::players::distance);
    cfg.SetBoolValue("Visuals", "Fill Box", vars::players::fillbox);
    cfg.SetBoolValue("Visuals", "Health Bar", vars::players::healthbar);
    cfg.SetBoolValue("Visuals", "Weapon", vars::players::weapon);
    cfg.SetLongValue("Visuals", "Weapon Position", vars::players::weaponPos);
    cfg.SetBoolValue("Visuals", "Skeleton", vars::players::skeleton);
   /* cfg.SetBoolValue("Visuals", "Chams", vars::players::chams);
    cfg.SetLongValue("Visuals", "Chams Style", vars::players::chams_type);*/
    cfg.SetBoolValue("Visuals", "Target Tracers", vars::players::targetline);
    cfg.SetLongValue("Visuals", "Target Tracer Position", vars::players::targetline_pos);
    cfg.SetBoolValue("Visuals", "Target Player Belt", vars::players::belt);
    cfg.SetBoolValue("Visuals", "Out Of Arrows", vars::players::oof_arrows);
    cfg.SetLongValue("Visuals", "Out Of Arrows style", vars::players::Outstyle);
   cfg.SetBoolValue("Visuals", "lookingDirection", vars::visuals::lookingDirection);
     cfg.SetLongValue("Visuals", "Max dist", vars::players::maxdisctanse);
 //   cfg.SetLongValue("Visuals", "Font Size", vars::misc::fotsize);
    cfg.SetBoolValue("Visuals", "Ignore Sleepers", vars::players::sleeperignore);
    SaveColorValue("Visuals", "Skeleton  Color", vars::visible::skeleton_color);
    SaveColorValue("Visuals", "Esp Color", vars::invisible::box_color);
    SaveColorValue("Visuals", "Teammate Color", vars::colors::team_color);
    SaveColorValue("Visuals", "Sleepers Color", vars::colors::sleep_color);
    cfg.SetBoolValue("Npc", "Enable Npc", vars::visuals::NpcEspEnable);
    SaveColorValue("Npc", "Custom Health Color", vars::colors::Player_custom_healthColor);
    SaveColorValue("Npc", "Gradient Two", vars::colors::gradient_2);
    SaveColorValue("Npc", "Gradient One", vars::colors::gradient_1);
    cfg.SetLongValue("Npc", "Box Style", vars::npc::boxstyle);
    cfg.SetLongValue("Npc", "Healthbar Style", vars::npc::healthbarscolortyle);
    cfg.SetLongValue("Npc", "Healthbar Style Color", vars::npc::healthbarscolor);
    cfg.SetBoolValue("Npc", "Name", vars::npc::name);
    cfg.SetBoolValue("Npc", "Health Bar", vars::npc::healthbar);
    cfg.SetBoolValue("Npc", "Distance", vars::npc::distance);
    cfg.SetBoolValue("Npc", "Fill Box", vars::npc::fillbox);
    cfg.SetBoolValue("Npc", "Skeleton", vars::npc::skeleton);
    cfg.SetBoolValue("Npc", "Weapon", vars::npc::weapon);
    SaveColorValue("Npc", "Box  Color", vars::colors::npc_box_color);
    SaveColorValue("Npc", "Name Color", vars::colors::npc_name_color);
    SaveColorValue("Npc", "Skeleton Color", vars::colors::npc_skeleton_color);
    SaveColorValue("Npc", "Weapon Color", vars::colors::npc_weapons_color);
    SaveColorValue("Npc", "Custom Health Color", vars::colors::npc_custom_healthColor);
    SaveColorValue("Npc", "Gradient Two", vars::colors::gradient_2);
    SaveColorValue("Npc", "Gradient One", vars::colors::gradient_1);
    cfg.SetBoolValue("Visuals", "cadicall", vars::crosshair::cadicall);
    SaveColorValue("Visuals", "cadicall color", vars::colors::cadicall_color);
    cfg.SetBoolValue("Visuals", "default", vars::crosshair::default);
    SaveColorValue("Visuals", "default color", vars::colors::default_color);
    cfg.SetBoolValue("Visuals", "dot", vars::crosshair::dot);
    SaveColorValue("Visuals", "dot color", vars::colors::dot_color);
    cfg.SetBoolValue("Visuals", "Swastika", vars::crosshair::swastika);
    SaveColorValue("Visuals", "Swastika color", vars::colors::swaston_color);
    cfg.SetLongValue("Visuals", "Size1", vars::crosshair::razmer);
    cfg.SetLongValue("Visuals", "Speed2", vars::crosshair::speed);
    cfg.SetBoolValue("Visuals", "Custom Cross", vars::crosshair::custom);
    SaveColorValue("Visuals", "Custom Cross color", vars::colors::custom_color);
    cfg.SetLongValue("Visuals", "Gap", vars::crosshair::gap);
    cfg.SetLongValue("Visuals", "Length", vars::crosshair::length);
    cfg.SetLongValue("Misc", "Player Fov", vars::misc::fov);
    cfg.SetBoolValue("Misc", "AspectRatio", vars::misc::aspectraratio);
    cfg.SetLongValue("Misc", "AspectRatio float", vars::misc::aspectraratiofloat);
    cfg.SetBoolValue("Misc", "Zoom", vars::visuals::zoom);
    cfg.SetLongValue("Misc", "Zoom key", vars::keys::zoom);
    cfg.SetBoolValue("Misc", "Sphere", vars::visuals::sphere);
    cfg.SetBoolValue("Misc", "Noclip Bar", vars::misc::flyhack_indicator);
    cfg.SetBoolValue("Misc", "Reload Coldown", vars::misc::reload_coldown);
    cfg.SetBoolValue("Misc", "Desync Indicator", vars::combat::instakill_indicator);
    cfg.SetBoolValue("Misc", "Show Target Name", vars::visuals::target_name);
    cfg.SetBoolValue("Misc", "Hit Logs", vars::misc::hit_logs);
    cfg.SetBoolValue("Misc", "Gesture spam", vars::misc::gesture_spam);
    cfg.SetBoolValue("Misc", "Keybinds", vars::visuals::keybinds);
    cfg.SetBoolValue("Misc", "Side Indicator", vars::visuals::GameSense);
    cfg.SetLongValue("Misc", "Hit Effect", vars::misc::hitmaterial);
    cfg.SetBoolValue("Misc", "Bullet Tracers", vars::misc::bullet_tracers);
    //cfg.SetBoolValue("Misc", "Hitmarker", vars::misc::hitmarker);
    cfg.SetBoolValue("Misc", "Movement Line", vars::misc::movement_line);
    cfg.SetBoolValue("Misc", "Vis. Predict", vars::combat::visualize_prediction);
    cfg.SetBoolValue("Misc", "Nightmode (Ambient)", vars::misc::bright_ambient);
    cfg.SetBoolValue("Misc", "Local Bones", vars::misc::local_bones);
    cfg.SetBoolValue("Misc", "Custom Time", vars::misc::custom_time);
    cfg.SetLongValue("Misc", "Time", vars::misc::time);
    cfg.SetBoolValue("Misc", "Hand Chams", vars::visuals::hand_chams);
    cfg.SetLongValue("Misc", "Chams Style", vars::visuals::hand_chams_type);
    cfg.SetBoolValue("Misc", "Night Stars", vars::misc::night_stars);
    cfg.SetLongValue("Misc", "Stars Amount", vars::misc::stars);
    cfg.SetBoolValue("Misc", "Rayleigh Changer", vars::misc::rayleigh_changer);
    cfg.SetLongValue("Misc", "Rayleigh Amount", vars::misc::rayleigh);
    cfg.SetBoolValue("Misc", "Mie Changer", vars::misc::mie_changer);
    cfg.SetLongValue("Misc", "Mie Amount", vars::misc::mie);
    cfg.SetBoolValue("Misc", "Brightness Changer", vars::misc::brightness_changer);
    cfg.SetLongValue("Misc", "Brightness Amount", vars::misc::brightness);
    cfg.SetBoolValue("Misc", "Clouds", vars::misc::облака);
    cfg.SetLongValue("Misc", "Clouds Amount", vars::misc::облакафлоат);
    cfg.SetBoolValue("Misc", "Rain", vars::misc::Дождь);
    cfg.SetBoolValue("Misc", "Fog", vars::misc::туман);
    cfg.SetBoolValue("Misc", "Storm", vars::misc::шторм);
    cfg.SetBoolValue("Misc", "Rayleigh Changer", vars::misc::rayleigh_changer);
    cfg.SetBoolValue("Misc", "Fake Admin", vars::misc::fakeadmin);
    cfg.SetBoolValue("Misc", "Follow Projectile", vars::combat::followprojectile);
    cfg.SetLongValue("Misc", "Projectile Key", vars::keys::followprojectile);
    cfg.SetBoolValue("Misc", "Fast Loot", vars::misc::fast_loot);
    cfg.SetBoolValue("Misc", "No Collision", vars::misc::walker);
    cfg.SetLongValue("Misc", "Model State", vars::misc::modelstate);
    cfg.SetLongValue("Misc", "Model State Key", vars::keys::ModelState);
    cfg.SetBoolValue("Misc", "Omni-Sprint", vars::misc::omnidirectional_sprinting);
    cfg.SetBoolValue("Misc", "Interactive Debug", vars::misc::interactive_debug);
    cfg.SetLongValue("Misc", "Debug Key", vars::keys::debugging);
    cfg.SetBoolValue("Misc", "Hitsound", vars::misc::custom_hitsound);
    cfg.SetLongValue("Misc", "Sound", vars::misc::hitsound_rejim);
    cfg.SetBoolValue("Misc", "Fake-Lag", vars::misc::fake_lag);
    cfg.SetLongValue("Misc", "Fake-Lag style", vars::misc::fake_lag_type);
    cfg.SetBoolValue("Misc", "Spiderman", vars::misc::spiderman);
    cfg.SetBoolValue("Misc", "Fly Auto Stopper", vars::misc::fly_auto_stopper);
    cfg.SetBoolValue("Misc", "No Fall Damage", vars::misc::no_fall);
    cfg.SetBoolValue("Misc", "Infinity Jump", vars::misc::inf_jump);
    cfg.SetBoolValue("Misc", "Fake Shots", vars::misc::weapon_spam);
    cfg.SetLongValue("Misc", "Shots Key", vars::keys::weaponspam);
    cfg.SetBoolValue("Misc", "Silent Melee", vars::combat::silent_melee);
  //  cfg.SetBoolValue("Misc", "Insta Revive", vars::misc::auto_revive);
    cfg.SetBoolValue("Misc", "Auto Pick Up", vars::misc::auto_pickup);
    cfg.SetBoolValue("Misc", "Auto Healing", vars::misc::faster_healing);
    cfg.SetBoolValue("Misc", "Speed Hack", vars::misc::speedhack);
    cfg.SetLongValue("Misc", "Speed Hack Key", vars::keys::speedkey);
    cfg.SetBoolValue("Misc", "Anti-Aim", vars::misc::anti_aim);
    cfg.SetLongValue("Misc", "Anti-Aim style", vars::misc::anti_aim_yaw);
    /*cfg.SetBoolValue("AimBot", "Psilent", vars::combat::psilent);
    cfg.SetLongValue("AimBot", "aimKey", Keys::aimKey);
    SaveColorValue("Player", "WeaponColor", Colors::WeaponColor);*/
#pragma region AimBot

    /*SaveColorValue("Player - Color", "Player Fill Box Color", Bools::PlayerColor::PlayerFillBoxColor);
    SaveColorValue("Player - Color", "Player Dead Color", Bools::PlayerColor::PlayerDeadColor);
    SaveColorValue("Player - Color", "Player Backpack Color", Bools::PlayerColor::PlayerBackpackColor);*/
#pragma endregion

#pragma region Resourse Color
    /* SaveColorValue("Resourse - Color", "Stone - Ore Color", Bools::ResourcesColor::StoneOreColor);
     SaveColorValue("Resourse - Color", "Mettal - Ore Color", Bools::ResourcesColor::MettalOreColor);
     SaveColorValue("Resourse - Color", "Sulfure - Ore Color", Bools::ResourcesColor::SulfureOreColor);*/
#pragma endregion

#pragma region Construction Color
     /*
     SaveColorValue("Construction - Color", "Cupboard Color", Bools::ConstructionColor::CupboardColor);
     SaveColorValue("Construction - Color", "Large Wood Box Color", Bools::ConstructionColor::LargeWoodBoxColor);
     SaveColorValue("Construction - Color", "Small Stash Color", Bools::ConstructionColor::SmallStashColor);*/
#pragma endregion 

    cfg.SaveFile(result);
}

void Initialize()
{
    //szPath = "C:\\FrogGang.pw\\";
    //Setup();
}

void LoadCFG(std::string FileName)
{

    DWORD SerialNumber;

    GetVolumeInformation(L"C:\\Satanic", 0, 0, &SerialNumber, 0, 0, 0, 0);

    char Path[0x100];
    sprintf(Path, ("C:\\Satanic\\"));

    if (!folder_exists(Path))
        _mkdir(Path);
    cfg.SetUnicode();
    char result[0x100];
    sprintf(result, ("C:\\Satanic\\%s.ini"), FileName);
    cfg.LoadFile(result);
    vars::combat::psilent =   cfg.GetBoolValue("AimBot", "Perfect Silent", vars::combat::psilent);
    vars::combat::aimbot =    cfg.GetBoolValue("AimBot", "Simple Aimbot", vars::combat::aimbot);
    vars::combat::psilentbone =   cfg.GetLongValue("AimBot", "AimBone", vars::combat::psilentbone);
    vars::combat::fov = cfg.GetLongValue("AimBot", "Fov Value", vars::combat::fov);
    vars::players::fovstyle =  cfg.GetLongValue("AimBot", "Draw Fov style", vars::players::fovstyle);
    vars::combat::visualize_fov =  cfg.GetBoolValue("AimBot", "Draw fov", vars::combat::visualize_fov);
    LoadColorValue("Visuals", "Fov  Color", vars::colors::fov_color);
    vars::combat::psilentheli =    cfg.GetBoolValue("AimBot", "Heli Aim", vars::combat::psilentheli);
    vars::combat::manipulator =   cfg.GetBoolValue("AimBot", "Manipulator", vars::combat::manipulator);
    vars::keys::manipulated_key =   cfg.GetLongValue("AimBot", "Manipulator Key", vars::keys::manipulated_key);
    vars::combat::autoshoot =    cfg.GetBoolValue("AimBot", "Auto Fire", vars::combat::autoshoot);
    vars::combat::desync_autoshoot_type =   cfg.GetLongValue("AimBot", "Auto Fire type", vars::combat::desync_autoshoot_type);
    vars::combat::instakill =    cfg.GetBoolValue("AimBot", "Time Shot", vars::combat::instakill);
    vars::keys::instakill =    cfg.GetLongValue("AimBot", "Time Shot Key", vars::keys::instakill);
    vars::weapons::local_scale =  cfg.GetBoolValue("AimBot", "Visual Projectile", vars::weapons::local_scale);
    vars::weapons::bullet_sizex =   cfg.GetLongValue("AimBot", "Bullet Size x", vars::weapons::bullet_sizex);
    vars::weapons::bullet_sizey =   cfg.GetLongValue("AimBot", "Bullet Size y", vars::weapons::bullet_sizey);
    vars::weapons::bullet_sizez =   cfg.GetLongValue("AimBot", "Bullet Size z", vars::weapons::bullet_sizez);
    vars::combat::ignore_npc=   cfg.GetBoolValue("AimBot", "Ignore NPC", vars::combat::ignore_npc);
    vars::combat::ignore_team =  cfg.GetBoolValue("AimBot", "Ignore Teammates", vars::combat::ignore_team);
    vars::combat::ignore_sleepers =    cfg.GetBoolValue("AimBot", "Ignore Sleeping", vars::combat::ignore_sleepers);
    vars::weapons::no_recoil =    cfg.GetBoolValue("AimBot", "Recoil Control", vars::weapons::no_recoil);
    vars::weapons::recoil_control =     cfg.GetLongValue("AimBot", "Recoil", vars::weapons::recoil_control);
    vars::weapons::no_spread =    cfg.GetBoolValue("AimBot", "Anti Spread", vars::weapons::no_spread);
    vars::weapons::no_spreadvalue =    cfg.GetLongValue("AimBot", "Anti Spread value", vars::weapons::no_spreadvalue);
    vars::weapons::no_sway =   cfg.GetBoolValue("AimBot", "Remove Sway", vars::weapons::no_sway);
    vars::weapons::fast_bullets =  cfg.GetBoolValue("AimBot", "Fast Bullets", vars::weapons::fast_bullets);
    vars::weapons::thick_bullet =  cfg.GetBoolValue("AimBot", "Thick Bullets", vars::weapons::thick_bullet);
   // vars::weapons::thickness = cfg.GetLongValue("AimBot", "Thick", vars::weapons::thickness);
    vars::weapons::eokatap =   cfg.GetBoolValue("AimBot", "Instant Eoka", vars::weapons::eokatap);
    vars::weapons::fastbow =    cfg.GetBoolValue("AimBot", "Fast Bow", vars::weapons::fastbow);
    vars::weapons::rapid_fire = cfg.GetBoolValue("AimBot", "Rapid Fire", vars::weapons::rapid_fire);
    vars::combat::autoreload =    cfg.GetBoolValue("AimBot", "Auto Reload", vars::combat::autoreload);
    vars::weapons::remove_attack_anim =   cfg.GetBoolValue("AimBot", "No Attack Animation", vars::weapons::remove_attack_anim);
    vars::weapons::compound = cfg.GetBoolValue("AimBot", "Insta Charge Compound", vars::weapons::compound);
    vars::weapons::automatic = cfg.GetBoolValue("AimBot", "Automatic", vars::weapons::automatic);
    vars::weapons::minicopter_aim =   cfg.GetBoolValue("AimBot", "Can Hold Items", vars::weapons::minicopter_aim);
    vars::misc::can_attack =  cfg.GetBoolValue("AimBot", "Jump Shoot", vars::misc::can_attack);
    vars::weapons::spoof_hitdistance =   cfg.GetBoolValue("AimBot", "Fake Distance", vars::weapons::spoof_hitdistance);
    vars::weapons::hitdistance =   cfg.GetLongValue("AimBot", "Distance Value", vars::weapons::hitdistance);
    vars::combat::bullet_tp = cfg.GetBoolValue("AimBot", "Bullet Teleport", vars::combat::bullet_tp);
    vars::misc::long_neck =   vars::combat::always_heli_rotor =  cfg.GetBoolValue("AimBot", "Magic Heli", vars::combat::always_heli_rotor);
    vars::misc::long_neck = cfg.GetBoolValue("AimBot", "Long Neck", vars::misc::long_neck);
    vars::keys::longneck =   cfg.GetLongValue("AimBot", "Long Neck Key", vars::keys::longneck);
    vars::combat::desync =  cfg.GetBoolValue("AimBot", "Desync", vars::combat::desync);
    vars::keys::desync =   cfg.GetLongValue("AimBot", "Desync Key", vars::keys::desync);
    vars::weapons::penetrate= cfg.GetBoolValue("AimBot", "Pierce Materials", vars::weapons::penetrate);
    vars::visuals::playerEspEnable =  cfg.GetBoolValue("Visuals", "Enable Player", vars::visuals::playerEspEnable);
    vars::players::boxstyle =   cfg.GetLongValue("Visuals", "Box Style", vars::players::boxstyle);
    vars::players::healthbarscolortyle =  cfg.GetLongValue("Visuals", "Healthbar Style", vars::players::healthbarscolortyle);
    vars::players::healthbarscolor =  cfg.GetLongValue("Visuals", "Healthbar Style Color", vars::players::healthbarscolor);
    vars::players::name =  cfg.GetBoolValue("Visuals", "Name", vars::players::name);
    vars::players::namePos  = cfg.GetLongValue("Visuals", "Name Position", vars::players::namePos);
    vars::players::distance=    cfg.GetBoolValue("Visuals", "Distance", vars::players::distance);
    vars::players::fillbox=   cfg.GetBoolValue("Visuals", "Fill Box", vars::players::fillbox);
    vars::players::healthbar =   cfg.GetBoolValue("Visuals", "Health Bar", vars::players::healthbar);
    vars::players::weapon =   cfg.GetBoolValue("Visuals", "Weapon", vars::players::weapon);
    vars::players::weaponPos =    cfg.GetLongValue("Visuals", "Weapon Position", vars::players::weaponPos);
    vars::players::skeleton =   cfg.GetBoolValue("Visuals", "Skeleton", vars::players::skeleton);
   /* vars::players::chams =   cfg.GetBoolValue("Visuals", "Chams", vars::players::chams);
    vars::players::chams_type =  cfg.GetLongValue("Visuals", "Chams Style", vars::players::chams_type);*/
    vars::players::targetline =  cfg.GetBoolValue("Visuals", "Target Tracers", vars::players::targetline);
    vars::players::targetline_pos = cfg.GetLongValue("Visuals", "Target Tracer Position", vars::players::targetline_pos);
    vars::players::belt =   cfg.GetBoolValue("Visuals", "Target Player Belt", vars::players::belt);
    vars::players::oof_arrows = cfg.GetBoolValue("Visuals", "Out Of Arrows", vars::players::oof_arrows);
    vars::players::Outstyle =   cfg.GetLongValue("Visuals", "Out Of Arrows style", vars::players::Outstyle);
    vars::visuals::lookingDirection  = cfg.GetBoolValue("Visuals", "lookingDirection", vars::visuals::lookingDirection);
    vars::players::maxdisctanse = cfg.GetLongValue("Visuals", "Max dist", vars::players::maxdisctanse);
  //  vars::misc::fotsize =   cfg.GetLongValue("Visuals", "Font Size", vars::misc::fotsize);
    vars::players::sleeperignore = cfg.GetBoolValue("Visuals", "Ignore Sleepers", vars::players::sleeperignore);
    LoadColorValue("Visuals", "Skeleton  Color", vars::visible::skeleton_color);
    LoadColorValue("Visuals", "Esp Color", vars::invisible::box_color);
    LoadColorValue("Visuals", "Teammate Color", vars::colors::team_color);
    LoadColorValue("Visuals", "Sleepers Color", vars::colors::sleep_color);
    vars::visuals::NpcEspEnable =   cfg.GetBoolValue("Npc", "Enable Npc", vars::visuals::NpcEspEnable);
    LoadColorValue("Npc", "Custom Health Color", vars::colors::Player_custom_healthColor);
    LoadColorValue("Npc", "Gradient Two", vars::colors::gradient_2);
    LoadColorValue("Npc", "Gradient One", vars::colors::gradient_1);
    vars::npc::boxstyle =    cfg.GetLongValue("Npc", "Box Style", vars::npc::boxstyle);
    vars::npc::healthbarscolortyle =  cfg.GetLongValue("Npc", "Healthbar Style", vars::npc::healthbarscolortyle);
    vars::npc::healthbarscolor =    cfg.GetLongValue("Npc", "Healthbar Style Color", vars::npc::healthbarscolor);
    vars::npc::name=    cfg.GetBoolValue("Npc", "Name", vars::npc::name);
    vars::npc::healthbar =  cfg.GetBoolValue("Npc", "Health Bar", vars::npc::healthbar);
    vars::npc::distance =  cfg.GetBoolValue("Npc", "Distance", vars::npc::distance);
    vars::npc::fillbox =  cfg.GetBoolValue("Npc", "Fill Box", vars::npc::fillbox);
    vars::npc::skeleton =   cfg.GetBoolValue("Npc", "Skeleton", vars::npc::skeleton);
    vars::npc::weapon =cfg.GetBoolValue("Npc", "Weapon", vars::npc::weapon);
    LoadColorValue("Npc", "Box  Color", vars::colors::npc_box_color);
    LoadColorValue("Npc", "Name Color", vars::colors::npc_name_color);
    LoadColorValue("Npc", "Skeleton Color", vars::colors::npc_skeleton_color);
    LoadColorValue("Npc", "Weapon Color", vars::colors::npc_weapons_color);
    LoadColorValue("Npc", "Custom Health Color", vars::colors::npc_custom_healthColor);
    LoadColorValue("Npc", "Gradient Two", vars::colors::gradient_2);
    LoadColorValue("Npc", "Gradient One", vars::colors::gradient_1);
    vars::crosshair::cadicall =    cfg.GetBoolValue("Visuals", "cadicall", vars::crosshair::cadicall);
    LoadColorValue("Visuals", "cadicall color", vars::colors::cadicall_color);
    vars::crosshair::default =   cfg.GetBoolValue("Visuals", "default", vars::crosshair::default);
    LoadColorValue("Visuals", "default color", vars::colors::default_color);
    vars::crosshair::dot =  cfg.GetBoolValue("Visuals", "dot", vars::crosshair::dot);
    LoadColorValue("Visuals", "dot color", vars::colors::dot_color);
    vars::crosshair::swastika =    cfg.GetBoolValue("Visuals", "Swastika", vars::crosshair::swastika);
    LoadColorValue("Visuals", "Swastika color", vars::colors::swaston_color);
    vars::crosshair::razmer =   cfg.GetLongValue("Visuals", "Size1", vars::crosshair::razmer);
    vars::crosshair::speed =  cfg.GetLongValue("Visuals", "Speed2", vars::crosshair::speed);
    vars::crosshair::custom  =  cfg.GetBoolValue("Visuals", "Custom Cross", vars::crosshair::custom);
    LoadColorValue("Visuals", "Custom Cross color", vars::colors::custom_color);
    vars::crosshair::gap =   cfg.GetLongValue("Visuals", "Gap", vars::crosshair::gap);
    vars::crosshair::length =    cfg.GetLongValue("Visuals", "Length", vars::crosshair::length);
    vars::misc::fov =  cfg.GetLongValue("Misc", "Player Fov", vars::misc::fov);
    vars::misc::aspectraratio =  cfg.GetBoolValue("Misc", "AspectRatio", vars::misc::aspectraratio);
    vars::misc::aspectraratiofloat =  cfg.GetLongValue("Misc", "AspectRatio float", vars::misc::aspectraratiofloat);

    vars::visuals::zoom =   cfg.GetBoolValue("Misc", "Zoom", vars::visuals::zoom);
    vars::keys::zoom = cfg.GetLongValue("Misc", "Zoom key", vars::keys::zoom);
    vars::visuals::sphere = cfg.GetBoolValue("Misc", "Sphere", vars::visuals::sphere);
    vars::misc::flyhack_indicator = cfg.GetBoolValue("Misc", "Noclip Bar", vars::misc::flyhack_indicator);
    vars::misc::reload_coldown =    cfg.GetBoolValue("Misc", "Reload Coldown", vars::misc::reload_coldown);
    vars::combat::instakill_indicator =   cfg.GetBoolValue("Misc", "Desync Indicator", vars::combat::instakill_indicator);
    vars::visuals::target_name =   cfg.GetBoolValue("Misc", "Show Target Name", vars::visuals::target_name);
    vars::misc::hit_logs =  cfg.GetBoolValue("Misc", "Hit Logs", vars::misc::hit_logs);
    vars::misc::gesture_spam =  cfg.GetBoolValue("Misc", "Gesture spam", vars::misc::gesture_spam);
    vars::visuals::keybinds =   cfg.GetBoolValue("Misc", "Keybinds", vars::visuals::keybinds);
    vars::visuals::GameSense = cfg.GetBoolValue("Misc", "Side Indicator", vars::visuals::GameSense);
    vars::misc::hitmaterial =  cfg.GetLongValue("Misc", "Hit Effect", vars::misc::hitmaterial);
    vars::misc::bullet_tracers =   cfg.GetBoolValue("Misc", "Bullet Tracers", vars::misc::bullet_tracers);
  //  vars::misc::hitmarker =     cfg.GetBoolValue("Misc", "Hitmarker", vars::misc::hitmarker);
    vars::misc::movement_line =   cfg.GetBoolValue("Misc", "Movement Line", vars::misc::movement_line);
    vars::combat::visualize_prediction =   cfg.GetBoolValue("Misc", "Vis. Predict", vars::combat::visualize_prediction);
    vars::misc::bright_ambient =     cfg.GetBoolValue("Misc", "Nightmode (Ambient)", vars::misc::bright_ambient);
    vars::misc::local_bones  =   cfg.GetBoolValue("Misc", "Local Bones", vars::misc::local_bones);
    vars::misc::custom_time =  cfg.GetBoolValue("Misc", "Custom Time", vars::misc::custom_time);
    vars::misc::time = cfg.GetLongValue("Misc", "Time", vars::misc::time);
    vars::visuals::hand_chams =  cfg.GetBoolValue("Misc", "Hand Chams", vars::visuals::hand_chams);
    vars::visuals::hand_chams_type =  cfg.GetLongValue("Misc", "Chams Style", vars::visuals::hand_chams_type);
    vars::misc::night_stars = cfg.GetBoolValue("Misc", "Night Stars", vars::misc::night_stars);
    vars::misc::stars = cfg.GetLongValue("Misc", "Stars Amount", vars::misc::stars);
    vars::misc::rayleigh_changer =   cfg.GetBoolValue("Misc", "Rayleigh Changer", vars::misc::rayleigh_changer);
    vars::misc::rayleigh =  cfg.GetLongValue("Misc", "Rayleigh Amount", vars::misc::rayleigh);
    vars::misc::mie_changer =   cfg.GetBoolValue("Misc", "Mie Changer", vars::misc::mie_changer);
    vars::misc::mie =    cfg.GetLongValue("Misc", "Mie Amount", vars::misc::mie);
    vars::misc::brightness_changer =   cfg.GetBoolValue("Misc", "Brightness Changer", vars::misc::brightness_changer);
    vars::misc::brightness = cfg.GetLongValue("Misc", "Brightness Amount", vars::misc::brightness);
    vars::misc::облака =  cfg.GetBoolValue("Misc", "Clouds", vars::misc::облака);
    vars::misc::облакафлоат =  cfg.GetLongValue("Misc", "Clouds Amount", vars::misc::облакафлоат);
    vars::misc::Дождь =  cfg.GetBoolValue("Misc", "Rain", vars::misc::Дождь);
    vars::misc::туман =   cfg.GetBoolValue("Misc", "Fog", vars::misc::туман);
    vars::misc::шторм = cfg.GetBoolValue("Misc", "Storm", vars::misc::шторм);
    vars::misc::rayleigh_changer =  cfg.GetBoolValue("Misc", "Rayleigh Changer", vars::misc::rayleigh_changer);
    vars::misc::fakeadmin =  cfg.GetBoolValue("Misc", "Fake Admin", vars::misc::fakeadmin);
    vars::combat::followprojectile =   cfg.GetBoolValue("Misc", "Follow Projectile", vars::combat::followprojectile);
    vars::keys::followprojectile =   cfg.GetLongValue("Misc", "Projectile Key", vars::keys::followprojectile);
    vars::misc::fast_loot =  cfg.GetBoolValue("Misc", "Fast Loot", vars::misc::fast_loot);
    vars::misc::walker =     cfg.GetBoolValue("Misc", "No Collision", vars::misc::walker);
    vars::misc::modelstate =  cfg.GetLongValue("Misc", "Model State", vars::misc::modelstate);
    vars::keys::ModelState =  cfg.GetLongValue("Misc", "Model State Key", vars::keys::ModelState);
    vars::misc::omnidirectional_sprinting =  cfg.GetBoolValue("Misc", "Omni-Sprint", vars::misc::omnidirectional_sprinting);
    vars::misc::interactive_debug =   cfg.GetBoolValue("Misc", "Interactive Debug", vars::misc::interactive_debug);
    vars::keys::debugging =    cfg.GetLongValue("Misc", "Debug Key", vars::keys::debugging);
    vars::misc::custom_hitsound  = cfg.GetBoolValue("Misc", "Hitsound", vars::misc::custom_hitsound);
    vars::misc::hitsound_rejim =   cfg.GetLongValue("Misc", "Sound", vars::misc::hitsound_rejim);
    vars::misc::fake_lag =  cfg.GetBoolValue("Misc", "Fake-Lag", vars::misc::fake_lag);
    vars::misc::fake_lag_type =     cfg.GetLongValue("Misc", "Fake-Lag style", vars::misc::fake_lag_type);
    vars::misc::spiderman =    cfg.GetBoolValue("Misc", "Spiderman", vars::misc::spiderman);
    vars::misc::fly_auto_stopper =   cfg.GetBoolValue("Misc", "Fly Auto Stopper", vars::misc::fly_auto_stopper);
    vars::misc::no_fall =  cfg.GetBoolValue("Misc", "No Fall Damage", vars::misc::no_fall);
    vars::misc::inf_jump =     cfg.GetBoolValue("Misc", "Infinity Jump", vars::misc::inf_jump);
    vars::misc::weapon_spam =  cfg.GetBoolValue("Misc", "Fake Shots", vars::misc::weapon_spam);
    vars::keys::weaponspam =   cfg.GetLongValue("Misc", "Shots Key", vars::keys::weaponspam);
    vars::combat::silent_melee =  cfg.GetBoolValue("Misc", "Silent Melee", vars::combat::silent_melee);
    //vars::misc::auto_revive  =  cfg.GetBoolValue("Misc", "Insta Revive", vars::misc::auto_revive);
    vars::misc::auto_pickup = cfg.GetBoolValue("Misc", "Auto Pick Up", vars::misc::auto_pickup);
    vars::misc::faster_healing = cfg.GetBoolValue("Misc", "Auto Healing", vars::misc::faster_healing);
    vars::misc::speedhack =   cfg.GetBoolValue("Misc", "Speed Hack", vars::misc::speedhack);
    vars::keys::speedkey =  cfg.GetLongValue("Misc", "Speed Hack Key", vars::keys::speedkey);
    vars::misc::anti_aim =    cfg.GetBoolValue("Misc", "Anti-Aim", vars::misc::anti_aim);
    vars::misc::anti_aim_yaw =   cfg.GetLongValue("Misc", "Anti-Aim style", vars::misc::anti_aim_yaw);
    
    //vars::combat::psilent = cfg.GetBoolValue("AimBot", "Psilent", vars::combat::psilent);
    //Keys::aimKey = cfg.GetLongValue("AimBot", "aimKey", Keys::aimKey);
    //LoadColorValue("Player", "Crosshair", Colors::Crosshair2);



#pragma endregion

#pragma region Resourse Color
    //LoadColorValue("Resourse - Color", "Stone - Ore Color", Bools::ResourcesColor::StoneOreColor);
    //LoadColorValue("Resourse - Color", "Mettal - Ore Color", Bools::ResourcesColor::MettalOreColor);
    //LoadColorValue("Resourse - Color", "Sulfure - Ore Color", Bools::ResourcesColor::SulfureOreColor);
#pragma endregion

#pragma region Construction Color
         /*LoadColorValue("Construction - Color", "Cupboard Color", Bools::ConstructionColor::CupboardColor);
         LoadColorValue("Construction - Color", "Large Wood Box Color", Bools::ConstructionColor::LargeWoodBoxColor);
         LoadColorValue("Construction - Color", "Small Stash Color", Bools::ConstructionColor::SmallStashColor);*/
#pragma endregion 
};