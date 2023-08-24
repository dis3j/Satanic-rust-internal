namespace O {
	namespace BaseNetworkable {
		constexpr auto JustCreatedk__BackingField = 0x18;
		constexpr auto entityDestroy = 0x20;
		constexpr auto prefabID = 0x28;
		constexpr auto globalBroadcast = 0x2c;
		constexpr auto net = 0x30;
		constexpr auto IsDestroyedk__BackingField = 0x38;
		constexpr auto _prefabName = 0x40;
		constexpr auto _prefabNameWithoutExtension = 0x48;
		constexpr auto postNetworkUpdateComponents = 0x50;
		constexpr auto parentEntity = 0x58;
		constexpr auto children = 0x68;
		constexpr auto canTriggerParent = 0x70;


	};

	namespace BasePlayer {
		constexpr auto __menuOption_Climb = 0x250;
		constexpr auto __menuOption_Drink = 0x2b8;
		constexpr auto __menuOption_InviteToTeam = 0x320;
		constexpr auto __menuOption_Menu_AssistPlayer = 0x388;
		constexpr auto __menuOption_Menu_LootPlayer = 0x3f0;
		constexpr auto __menuOption_Promote = 0x458;
		constexpr auto __menuOption_SaltWater = 0x4c0;
		constexpr auto playerModel = 0x528;
		constexpr auto Frozen = 0x530;
		constexpr auto voiceRecorder = 0x538;
		constexpr auto voiceSpeaker = 0x540;
		constexpr auto input = 0x548;
		constexpr auto movement = 0x550;
		constexpr auto collision = 0x558;
		constexpr auto bagCount = 0x560;
		constexpr auto _lookingAt = 0x568;
		constexpr auto _lookingAtEntity = 0x570;
		constexpr auto _lookingAtCollider = 0x578;
		constexpr auto lookingAtPointk__BackingField = 0x580;
		constexpr auto wakeTime = 0x58c;
		constexpr auto needsClothesRebuild = 0x590;
		constexpr auto wasSleeping = 0x591;
		constexpr auto wokeUpBefore = 0x592;
		constexpr auto wasDead = 0x593;
		constexpr auto lastClothesHash = 0x594;
		constexpr auto visiblePlayerList = 0x8;
		constexpr auto craftMode = 0x10;
		constexpr auto lootPanelOverride = 0x18;
		constexpr auto lastOpenSoundPlay = 0x598;
		constexpr auto currentViewMode = 0x59c;
		constexpr auto selectedViewMode = 0x5a0;
		constexpr auto lastRevivePoint = 0x5a4;
		constexpr auto lastReviveDirection = 0x5b0;
		constexpr auto IsWearingDiveGogglesk__BackingField = 0x5bc;
		constexpr auto GestureViewModel = 0x5c0;
		constexpr auto currentClientRespawnInformation = 0x5c8;
		constexpr auto respawnOptionsTimestamp = 0x5d0;
		constexpr auto timeSinceUpdatedLookingAt = 0x5d4;
		constexpr auto nextTopologyTestTime = 0x5d8;
		constexpr auto usePressTime = 0x5dc;
		constexpr auto useHeldTime = 0x5e0;
		constexpr auto lookingAtTest = 0x5e8;
		constexpr auto lastDeathTimeClient = 0x20;
		constexpr auto cachedWaterDrinkingPoint = 0x5f0;
		constexpr auto gestureList = 0x600;
		constexpr auto gestureFinishedTime = 0x608;
		constexpr auto blockHeldInputTimer = 0x60c;
		constexpr auto currentGesture = 0x610;
		constexpr auto disabledHeldEntity = 0x618;
		constexpr auto nextGestureMenuOpenTime = 0x620;
		constexpr auto lastGestureCancel = 0x624;
		constexpr auto client_lastHelloTime = 0x628;
		constexpr auto currentTeam = 0x630;
		constexpr auto MaxTeamSizeToast = 0x28;
		constexpr auto clientTeam = 0x638;
		constexpr auto lastReceivedTeamTime = 0x640;
		constexpr auto lastPresenceTeamId = 0x648;
		constexpr auto lastPresenceTeamSize = 0x650;
		constexpr auto playerGroupKey = 0x658;
		constexpr auto playerGroupSizeKey = 0x660;
		constexpr auto clActiveItem = 0x668;
		constexpr auto MarkerLimitPhrase = 0x30;
		constexpr auto ClientCurrentMapNotes = 0x670;
		constexpr auto ClientCurrentDeathNote = 0x678;
		constexpr auto keepOpenMapInterface = 0x680;
		constexpr auto missions = 0x688;
		constexpr auto _activeMission = 0x690;
		constexpr auto modelState = 0x698;
		constexpr auto mounted = 0x6a0;
		constexpr auto nextSeatSwapTime = 0x6b0;
		constexpr auto PetEntity = 0x6b8;
		constexpr auto lastPetCommandIssuedTime = 0x6c0;
		constexpr auto PetPrefabID = 0x6c4;
		constexpr auto PetID = 0x6c8;
		constexpr auto PetWheelHasBeenOpened = 0x38;
		constexpr auto HostileTitle = 0x40;
		constexpr auto HostileDesc = 0x48;
		constexpr auto HostileMarker = 0x50;
		constexpr auto GoToTitle = 0x70;
		constexpr auto GoToDesc = 0x78;
		constexpr auto GoToMarker = 0x80;
		constexpr auto DollarTitle = 0xa0;
		constexpr auto DollarDesc = 0xa8;
		constexpr auto DollarMarker = 0xb0;
		constexpr auto LootTitle = 0xd0;
		constexpr auto LootDesc = 0xd8;
		constexpr auto LootMarker = 0xe0;
		constexpr auto NodeTitle = 0x100;
		constexpr auto NodeDesc = 0x108;
		constexpr auto NodeMarker = 0x110;
		constexpr auto GunTitle = 0x130;
		constexpr auto GunDesc = 0x138;
		constexpr auto GunMarker = 0x140;
		constexpr auto RadialPings = 0x160;
		constexpr auto ClientCurrentPings = 0x6d0;
		constexpr auto tapInProcess = 0x6d8;
		constexpr auto lastPingTap = 0x6dc;
		constexpr auto cachedBuildingPrivilegeTime = 0x6e0;
		constexpr auto cachedBuildingPrivilege = 0x6e8;
		constexpr auto cachedVehicleBuildingBlockedTime = 0x6f0;
		constexpr auto cachedVehicleBuildingBlocked = 0x6f4;
		constexpr auto maxProjectileID = 0x6f8;
		constexpr auto lastUpdateTime = 0x6fc;
		constexpr auto cachedThreatLevel = 0x700;
		constexpr auto serverTickRate = 0x704;
		constexpr auto clientTickRate = 0x708;
		constexpr auto serverTickInterval = 0x70c;
		constexpr auto clientTickInterval = 0x710;
		constexpr auto lastSentTickTime = 0x714;
		constexpr auto lastTickStopwatch = 0x718;
		constexpr auto lastSentTick = 0x720;
		constexpr auto nextVisThink = 0x728;
		constexpr auto lastTimeSeen = 0x72c;
		constexpr auto debugPrevVisible = 0x730;
		constexpr auto fallDamageEffect = 0x738;
		constexpr auto drownEffect = 0x740;
		constexpr auto playerFlags = 0x748;
		constexpr auto eyes = 0x750;
		constexpr auto inventory = 0x758;
		constexpr auto blueprints = 0x760;
		constexpr auto metabolism = 0x768;
		constexpr auto modifiers = 0x770;
		constexpr auto playerCollider = 0x778;
		constexpr auto Belt = 0x780;
		constexpr auto playerRigidbody = 0x788;
		constexpr auto userID = 0x790;
		constexpr auto UserIDString = 0x798;
		constexpr auto gamemodeteam = 0x7a0;
		constexpr auto reputation = 0x7a4;
		constexpr auto _displayName = 0x7a8;
		constexpr auto _lastSetName = 0x7b0;
		constexpr auto playerColliderStanding = 0x7b8;
		constexpr auto playerColliderDucked = 0x7cc;
		constexpr auto playerColliderCrawling = 0x7e0;
		constexpr auto playerColliderLyingDown = 0x7f4;
		constexpr auto cachedProtection = 0x808;
		constexpr auto oldCameraFix = 0x168;
		constexpr auto lastHeadshotSoundTime = 0x810;
		constexpr auto nextColliderRefreshTime = 0x814;
		constexpr auto clothingBlocksAiming = 0x818;
		constexpr auto clothingMoveSpeedReduction = 0x81c;
		constexpr auto clothingWaterSpeedBonus = 0x820;
		constexpr auto clothingAccuracyBonus = 0x824;
		constexpr auto equippingBlocked = 0x828;
		constexpr auto eggVision = 0x82c;
		constexpr auto activeTelephone = 0x830;
		constexpr auto designingAIEntity = 0x838;


	};

	namespace BaseMovement {
		constexpr auto adminCheat = 0x18;
		constexpr auto adminSpeed = 0x1c;
		constexpr auto Ownerk__BackingField = 0x20;
		constexpr auto InheritedVelocityk__BackingField = 0x28;
		constexpr auto TargetMovementk__BackingField = 0x34;
		constexpr auto Runningk__BackingField = 0x40;
		constexpr auto Duckingk__BackingField = 0x44;
		constexpr auto Crawlingk__BackingField = 0x48;
		constexpr auto Groundedk__BackingField = 0x4c;
		constexpr auto lastTeleportedTime = 0x50;


	};

	namespace BaseProjectile {
		constexpr auto NoiseRadius = 0x280;
		constexpr auto damageScale = 0x284;
		constexpr auto distanceScale = 0x288;
		constexpr auto projectileVelocityScale = 0x28c;
		constexpr auto automatic = 0x290;
		constexpr auto usableByTurret = 0x291;
		constexpr auto turretDamageScale = 0x294;
		constexpr auto attackFX = 0x298;
		constexpr auto silencedAttack = 0x2a0;
		constexpr auto muzzleBrakeAttack = 0x2a8;
		constexpr auto MuzzlePoint = 0x2b0;
		constexpr auto reloadTime = 0x2b8;
		constexpr auto canUnloadAmmo = 0x2bc;
		constexpr auto primaryMagazine = 0x2c0;
		constexpr auto fractionalReload = 0x2c8;
		constexpr auto reloadStartDuration = 0x2cc;
		constexpr auto reloadFractionDuration = 0x2d0;
		constexpr auto reloadEndDuration = 0x2d4;
		constexpr auto aimSway = 0x2d8;
		constexpr auto aimSwaySpeed = 0x2dc;
		constexpr auto recoil = 0x2e0;
		constexpr auto aimconeCurve = 0x2e8;
		constexpr auto aimCone = 0x2f0;
		constexpr auto hipAimCone = 0x2f4;
		constexpr auto aimconePenaltyPerShot = 0x2f8;
		constexpr auto aimConePenaltyMax = 0x2fc;
		constexpr auto aimconePenaltyRecoverTime = 0x300;
		constexpr auto aimconePenaltyRecoverDelay = 0x304;
		constexpr auto stancePenaltyScale = 0x308;
		constexpr auto hasADS = 0x30c;
		constexpr auto noAimingWhileCycling = 0x30d;
		constexpr auto manualCycle = 0x30e;
		constexpr auto needsCycle = 0x30f;
		constexpr auto isCycling = 0x310;
		constexpr auto aiming = 0x311;
		constexpr auto useEmptyAmmoState = 0x312;
		constexpr auto isBurstWeapon = 0x313;
		constexpr auto canChangeFireModes = 0x314;
		constexpr auto defaultOn = 0x315;
		constexpr auto internalBurstRecoilScale = 0x318;
		constexpr auto internalBurstFireRateScale = 0x31c;
		constexpr auto internalBurstAimConeScale = 0x320;
		constexpr auto Toast_BurstDisabled = 0x328;
		constexpr auto Toast_BurstEnabled = 0x330;
		constexpr auto resetDuration = 0x338;
		constexpr auto numShotsFired = 0x33c;
		constexpr auto nextReloadTime = 0x340;
		constexpr auto startReloadTime = 0x344;
		constexpr auto stancePenalty = 0x348;
		constexpr auto aimconePenalty = 0x34c;
		constexpr auto cachedModHash = 0x350;
		constexpr auto sightAimConeScale = 0x354;
		constexpr auto sightAimConeOffset = 0x358;
		constexpr auto hipAimConeScale = 0x35c;
		constexpr auto hipAimConeOffset = 0x360;
		constexpr auto Param_Ammo_False = 0x4;
		constexpr auto isReloading = 0x364;
		constexpr auto timeSinceReloadFinished = 0x368;
		constexpr auto swaySampleTime = 0x36c;
		constexpr auto lastShotTime = 0x370;
		constexpr auto reloadPressTime = 0x374;
		constexpr auto ammoTypePreReload = 0x378;
		constexpr auto fractionalReloadDesiredCount = 0x380;
		constexpr auto fractionalReloadNumAdded = 0x384;
		constexpr auto currentBurst = 0x388;
		constexpr auto triggerReady = 0x38c;
		constexpr auto nextHeightCheckTime = 0x390;
		constexpr auto cachedUnderground = 0x394;
		constexpr auto createdProjectiles = 0x398;


	};

	namespace PlayerWalkMovement {
		constexpr auto zeroFrictionMaterial = 0x58;
		constexpr auto highFrictionMaterial = 0x60;
		constexpr auto capsuleHeight = 0x68;
		constexpr auto capsuleCenter = 0x6c;
		constexpr auto capsuleHeightDucked = 0x70;
		constexpr auto capsuleCenterDucked = 0x74;
		constexpr auto capsuleHeightCrawling = 0x78;
		constexpr auto capsuleCenterCrawling = 0x7c;
		constexpr auto gravityTestRadius = 0x80;
		constexpr auto gravityMultiplier = 0x84;
		constexpr auto gravityMultiplierSwimming = 0x88;
		constexpr auto maxAngleWalking = 0x8c;
		constexpr auto maxAngleClimbing = 0x90;
		constexpr auto maxAngleSliding = 0x94;
		constexpr auto maxStepHeight = 0x98;
		constexpr auto body = 0xa0;
		constexpr auto initialColDetectionMode = 0xa8;
		constexpr auto capsule = 0xb0;
		constexpr auto ladder = 0xb8;
		constexpr auto maxVelocity = 0xc0;
		constexpr auto groundAngle = 0xc4;
		constexpr auto groundAngleNew = 0xc8;
		constexpr auto groundTime = 0xcc;
		constexpr auto jumpTime = 0xd0;
		constexpr auto landTime = 0xd4;
		constexpr auto previousPosition = 0xd8;
		constexpr auto previousVelocity = 0xe4;
		constexpr auto previousInheritedVelocity = 0xf0;
		constexpr auto groundNormal = 0xfc;
		constexpr auto groundNormalNew = 0x108;
		constexpr auto groundVelocity = 0x114;
		constexpr auto groundVelocityNew = 0x120;
		constexpr auto nextSprintTime = 0x12c;
		constexpr auto lastSprintTime = 0x130;
		constexpr auto sprintForced = 0x134;
		constexpr auto attemptedMountTime = 0x138;
		constexpr auto modify = 0x13c;
		constexpr auto grounded = 0x140;
		constexpr auto climbing = 0x141;
		constexpr auto sliding = 0x142;
		constexpr auto swimming = 0x143;
		constexpr auto wasSwimming = 0x144;
		constexpr auto jumping = 0x145;
		constexpr auto wasJumping = 0x146;
		constexpr auto falling = 0x147;
		constexpr auto wasFalling = 0x148;
		constexpr auto flying = 0x149;
		constexpr auto wasFlying = 0x14a;
		constexpr auto forcedDuckDelta = 0x14c;

	};

	namespace UnityEngine_GUI {
		constexpr auto s_BoxHash = 0x4;
		constexpr auto s_ButonHash = 0x8;
		constexpr auto s_RepeatButtonHash = 0xc;
		constexpr auto s_ToggleHash = 0x10;
		constexpr auto s_ButtonGridHash = 0x14;
		constexpr auto s_SliderHash = 0x18;
		constexpr auto s_BeginGroupHash = 0x1c;
		constexpr auto s_ScrollviewHash = 0x20;
		constexpr auto scrollTroughSidek__BackingField = 0x24;
		constexpr auto nextScrollStepTimek__BackingField = 0x28;
		constexpr auto s_Skin = 0x30;
		constexpr auto s_ToolTipRect = 0x38;
		constexpr auto scrollViewStatesk__BackingField = 0x48;


	};

	namespace UnityEngine_GUIStyle {
		constexpr auto m_Ptr = 0x10;
		constexpr auto m_Normal = 0x18;
		constexpr auto m_Hover = 0x20;
		constexpr auto m_Active = 0x28;
		constexpr auto m_Focused = 0x30;
		constexpr auto m_OnNormal = 0x38;
		constexpr auto m_OnHover = 0x40;
		constexpr auto m_OnActive = 0x48;
		constexpr auto m_OnFocused = 0x50;
		constexpr auto m_Border = 0x58;
		constexpr auto m_Padding = 0x60;
		constexpr auto m_Margin = 0x68;
		constexpr auto m_Overflow = 0x70;
		constexpr auto m_Name = 0x78;
		constexpr auto s_None = 0x8;

			};




		namespace UnityEngine_DDraw {
			constexpr auto singleton = 0x8;
			constexpr auto list = 0x18;
			constexpr auto AutoYPosition = 0x10;
			constexpr auto LastAutoY = 0x14;
			constexpr auto lineMaterial = 0x18;
			constexpr auto _skin = 0x20;

		};

		namespace ModelState {
			constexpr auto waterLevel = 0x10;
			constexpr auto lookDir = 0x14;
			constexpr auto flags = 0x20;
			constexpr auto poseType = 0x24;
			constexpr auto inheritedVelocity = 0x28;
			constexpr auto ladderType = 0x34;
			constexpr auto ShouldPool = 0x38;
			constexpr auto _disposed = 0x39;


		};

		namespace ProtoBuf_PlayerProjectileUpdate {
			constexpr auto projectileID = 0x10;
			constexpr auto curPosition = 0x14;
			constexpr auto curVelocity = 0x20;
			constexpr auto travelTime = 0x2c;
			constexpr auto ShouldPool = 0x30;
			constexpr auto _disposed = 0x31;

	
		};

		namespace Projectile {
			constexpr auto initialVelocity = 0x18;
			constexpr auto drag = 0x24;
			constexpr auto gravityModifier = 0x28;
			constexpr auto thickness = 0x2c;
			constexpr auto initialDistance = 0x30;
			constexpr auto remainInWorld = 0x34;
			constexpr auto stickProbability = 0x38;
			constexpr auto breakProbability = 0x3c;
			constexpr auto conditionLoss = 0x40;
			constexpr auto ricochetChance = 0x44;
			constexpr auto penetrationPower = 0x48;
			constexpr auto waterIntegrityLoss = 0x4c;
			constexpr auto damageProperties = 0x50;
			constexpr auto damageDistances = 0x58;
			constexpr auto damageMultipliers = 0x60;
			constexpr auto damageTypes = 0x68;
			constexpr auto rendererToScale = 0x70;
			constexpr auto firstPersonRenderer = 0x78;
			constexpr auto createDecals = 0x80;
			constexpr auto doDefaultHitEffects = 0x81;
			constexpr auto flybySound = 0x88;
			constexpr auto flybySoundDistance = 0x90;
			constexpr auto closeFlybySound = 0x98;
			constexpr auto closeFlybyDistance = 0xa0;
			constexpr auto tumbleSpeed = 0xa4;
			constexpr auto tumbleAxis = 0xa8;
			constexpr auto swimScale = 0xb4;
			constexpr auto swimSpeed = 0xc0;
			constexpr auto owner = 0xd0;
			constexpr auto sourceWeaponPrefab = 0xd8;
			constexpr auto sourceProjectilePrefab = 0xe0;
			constexpr auto mod = 0xe8;
			constexpr auto projectileID = 0xf0;
			constexpr auto seed = 0xf4;
			constexpr auto clientsideEffect = 0xf8;
			constexpr auto clientsideAttack = 0xf9;
			constexpr auto integrity = 0xfc;
			constexpr auto maxDistance = 0x100;
			constexpr auto modifier = 0x104;
			constexpr auto invisible = 0x114;
			constexpr auto currentVelocity = 0x118;
			constexpr auto currentPosition = 0x124;
			constexpr auto traveledDistance = 0x130;
			constexpr auto traveledTime = 0x134;
			constexpr auto launchTime = 0x138;
			constexpr auto sentPosition = 0x13c;
			constexpr auto previousPosition = 0x148;
			constexpr auto previousVelocity = 0x154;
			constexpr auto previousTraveledTime = 0x160;
			constexpr auto isUnderwater = 0x164;
			constexpr auto isRicochet = 0x165;
			constexpr auto isRetiring = 0x166;
			constexpr auto flybyPlayed = 0x167;
			constexpr auto wasFacingPlayer = 0x168;
			constexpr auto flybyPlane = 0x16c;
			constexpr auto flybyRay = 0x17c;
			constexpr auto cleanupAction = 0x198;
			constexpr auto hitTest = 0x1a0;
			constexpr auto swimRandom = 0x1a8;
			constexpr auto _waterMaterialID = 0x4;
			constexpr auto cachedWaterString = 0x8;

		};

		namespace PlayerEyes {
			constexpr auto DuckOffset = 0xc;
			constexpr auto CrawlOffset = 0x18;
			constexpr auto thirdPersonSleepingOffset = 0x20;
			constexpr auto defaultLazyAim = 0x30;
			constexpr auto viewOffset = 0x38;
			constexpr auto bodyRotationk__BackingField = 0x44;
			constexpr auto headAnglesk__BackingField = 0x54;
			constexpr auto rotationLookk__BackingField = 0x60;
			constexpr auto IsAltLookingLegsThresholdk__BackingField = 0x70;

		};

		namespace ViewModel {
			constexpr auto viewModelPrefab = 0x18;
			constexpr auto targetEntity = 0x20;
			constexpr auto instance = 0x28;


		};

		namespace BowWeapon {
			constexpr auto attackReady = 0x3a0;
			constexpr auto arrowBack = 0x3a4;
			constexpr auto swapArrows = 0x3a8;
			constexpr auto wasAiming = 0x3b0;


		};

		namespace AttackEntity {
			constexpr auto deployDelay = 0x1f8;
			constexpr auto repeatDelay = 0x1fc;
			constexpr auto animationDelay = 0x200;
			constexpr auto effectiveRange = 0x204;
			constexpr auto npcDamageScale = 0x208;
			constexpr auto attackLengthMin = 0x20c;
			constexpr auto attackLengthMax = 0x210;
			constexpr auto attackSpacing = 0x214;
			constexpr auto aiAimSwayOffset = 0x218;
			constexpr auto aiAimCone = 0x21c;
			constexpr auto aiOnlyInRange = 0x220;
			constexpr auto CloseRangeAddition = 0x224;
			constexpr auto MediumRangeAddition = 0x228;
			constexpr auto LongRangeAddition = 0x22c;
			constexpr auto CanUseAtMediumRange = 0x230;
			constexpr auto CanUseAtLongRange = 0x231;
			constexpr auto reloadSounds = 0x238;
			constexpr auto thirdPersonMeleeSound = 0x240;
			constexpr auto recoilCompDelayOverride = 0x248;
			constexpr auto wantsRecoilComp = 0x24c;
			constexpr auto nextAttackTime = 0x250;
			constexpr auto lastTickTime = 0x254;
			constexpr auto nextTickTime = 0x258;
			constexpr auto timeSinceDeploy = 0x25c;
			constexpr auto lastRecoilCompTime = 0x260;
			constexpr auto startAimingDirection = 0x264;
			constexpr auto wasDoingRecoilComp = 0x270;
			constexpr auto reductionSpeed = 0x274;

	
		};

		namespace BaseEntity {
			constexpr auto ragdoll = 0x78;
			constexpr auto positionLerp = 0x80;
			constexpr auto menuOptions = 0x88;
			constexpr auto bounds = 0x90;
			constexpr auto impactEffect = 0xa8;
			constexpr auto enableSaving = 0xb0;
			constexpr auto syncPosition = 0xb1;
			constexpr auto model = 0xb8;
			constexpr auto flags = 0xc0;
			constexpr auto parentBone = 0xc4;
			constexpr auto skinID = 0xc8;
			constexpr auto _components = 0xd0;
			constexpr auto HasBrain = 0xd8;
			constexpr auto _name = 0xe0;
			constexpr auto OwnerIDk__BackingField = 0xe8;
			constexpr auto globalBroadcastProtocol = 0x8;
			constexpr auto broadcastProtocol = 0xf0;
			constexpr auto links = 0xf8;
			constexpr auto linkedToNeighbours = 0x100;
			constexpr auto QueuedFileRequests = 0x10;
			constexpr auto _fileRequestCounter = 0x18;
			constexpr auto _flushQueuedFileRequests = 0x30;
			constexpr auto _pendingFileRequests = 0x108;
			constexpr auto updateParentingAction = 0x110;
			constexpr auto addedToParentEntity = 0x118;
			constexpr auto itemSkin = 0x120;
			constexpr auto entitySlots = 0x128;
			constexpr auto triggers = 0x130;
			constexpr auto isVisible = 0x138;
			constexpr auto isAnimatorVisible = 0x139;
			constexpr auto isShadowVisible = 0x13a;
			constexpr auto localOccludee = 0x140;
			constexpr auto Weightk__BackingField = 0x160;


		};



		namespace UnityEngine_Physics {
			constexpr auto ContactModifyEventCCD = 0x8;

		};

		namespace AssetNameCache {
			constexpr auto lower = 0x8;
			constexpr auto upper = 0x10;

		};


	

		namespace HitTest {
			constexpr auto type = 0x10;
			constexpr auto AttackRay = 0x14;
			constexpr auto Radius = 0x2c;
			constexpr auto Forgiveness = 0x30;
			constexpr auto MaxDistance = 0x34;
			constexpr auto RayHit = 0x38;
			constexpr auto MultiHit = 0x64;
			constexpr auto BestHit = 0x65;
			constexpr auto DidHit = 0x66;
			constexpr auto damageProperties = 0x68;
			constexpr auto gameObject = 0x70;
			constexpr auto collider = 0x78;
			constexpr auto ignoreEntity = 0x80;
			constexpr auto HitEntity = 0x88;
			constexpr auto HitPoint = 0x90;
			constexpr auto HitNormal = 0x9c;
			constexpr auto HitDistance = 0xa8;
			constexpr auto HitTransform = 0xb0;
			constexpr auto HitPart = 0xb8;
			constexpr auto HitMaterial = 0xc0;

		
		};

		namespace UnityEngine_Quaternion {
			constexpr auto x = 0x10;
			constexpr auto y = 0x14;
			constexpr auto z = 0x18;
			constexpr auto w = 0x1c;

		};

		namespace GamePhysics {
			constexpr auto hitBufferB = 0x8;
			constexpr auto colBuffer = 0x10;


		};



		namespace System_Math {
			constexpr auto roundPower10Double = 0x8;


		};


		namespace Door {
			constexpr auto __menuOption_Menu_CloseDoor = 0x288;
			constexpr auto __menuOption_Menu_KnockDoor = 0x2f0;
			constexpr auto __menuOption_Menu_OpenDoor = 0x358;
			constexpr auto __menuOption_Menu_ToggleHatch = 0x3c0;
			constexpr auto knockEffect = 0x428;
			constexpr auto canTakeLock = 0x430;
			constexpr auto hasHatch = 0x431;
			constexpr auto canTakeCloser = 0x432;
			constexpr auto canTakeKnocker = 0x433;
			constexpr auto canNpcOpen = 0x434;
			constexpr auto canHandOpen = 0x435;
			constexpr auto isSecurityDoor = 0x436;
			constexpr auto vehiclePhysBoxes = 0x438;
			constexpr auto checkPhysBoxesOnOpen = 0x440;
			constexpr auto vehicleCollisionSfx = 0x448;
			constexpr auto ClosedColliderRoots = 0x450;
			constexpr auto openAnimLength = 0x458;
			constexpr auto closeAnimLength = 0x45c;
			constexpr auto closeHash = 0x4;

		
		};

		namespace UnityEngine_Object {
			constexpr auto m_CachedPtr = 0x10;

		};

		namespace BaseMelee {
			constexpr auto damageProperties = 0x280;
			constexpr auto damageTypes = 0x288;
			constexpr auto maxDistance = 0x290;
			constexpr auto attackRadius = 0x294;
			constexpr auto isAutomatic = 0x298;
			constexpr auto blockSprintOnAttack = 0x299;
			constexpr auto canUntieCrates = 0x29a;
			constexpr auto strikeFX = 0x2a0;
			constexpr auto useStandardHitEffects = 0x2a8;
			constexpr auto aiStrikeDelay = 0x2ac;
			constexpr auto swingEffect = 0x2b0;
			constexpr auto materialStrikeFX = 0x2b8;
			constexpr auto heartStress = 0x2c0;
			constexpr auto gathering = 0x2c8;
			constexpr auto throwReady = 0x2d0;
			constexpr auto canThrowAsProjectile = 0x2d1;
			constexpr auto canAiHearIt = 0x2d2;
			constexpr auto onlyThrowAsProjectile = 0x2d3;

		};

		namespace ItemModProjectile {
			constexpr auto projectileObject = 0x18;
			constexpr auto mods = 0x20;
			constexpr auto ammoType = 0x28;
			constexpr auto numProjectiles = 0x2c;
			constexpr auto projectileSpread = 0x30;
			constexpr auto projectileVelocity = 0x34;
			constexpr auto projectileVelocitySpread = 0x38;
			constexpr auto useCurve = 0x3c;
			constexpr auto spreadScalar = 0x40;
			constexpr auto attackEffectOverride = 0x48;
			constexpr auto barrelConditionLoss = 0x50;
			constexpr auto category = 0x58;


		};

		namespace RecoilProperties {
			constexpr auto recoilYawMin = 0x18;
			constexpr auto recoilYawMax = 0x1c;
			constexpr auto recoilPitchMin = 0x20;
			constexpr auto recoilPitchMax = 0x24;
			constexpr auto timeToTakeMin = 0x28;
			constexpr auto timeToTakeMax = 0x2c;
			constexpr auto ADSScale = 0x30;
			constexpr auto movementPenalty = 0x34;
			constexpr auto clampPitch = 0x38;
			constexpr auto pitchCurve = 0x40;
			constexpr auto yawCurve = 0x48;
			constexpr auto useCurves = 0x50;
			constexpr auto curvesAsScalar = 0x51;
			constexpr auto shotsUntilMax = 0x54;
			constexpr auto maxRecoilRadius = 0x58;
			constexpr auto overrideAimconeWithCurve = 0x5c;
			constexpr auto aimconeCurveScale = 0x60;
			constexpr auto aimconeCurve = 0x68;
			constexpr auto aimconeProbabilityCurve = 0x70;
			constexpr auto newRecoilOverride = 0x78;


		};

		namespace ItemDefinition {
			constexpr auto itemid = 0x18;
			constexpr auto shortname = 0x20;
			constexpr auto displayName = 0x28;
			constexpr auto displayDescription = 0x30;
			constexpr auto iconSprite = 0x38;
			constexpr auto category = 0x40;
			constexpr auto selectionPanel = 0x44;
			constexpr auto maxDraggable = 0x48;
			constexpr auto itemType = 0x4c;
			constexpr auto amountType = 0x50;
			constexpr auto occupySlots = 0x54;
			constexpr auto stackable = 0x58;
			constexpr auto quickDespawn = 0x5c;
			constexpr auto rarity = 0x60;
			constexpr auto despawnRarity = 0x64;
			constexpr auto spawnAsBlueprint = 0x68;
			constexpr auto inventoryGrabSound = 0x70;
			constexpr auto inventoryDropSound = 0x78;
			constexpr auto physImpactSoundDef = 0x80;
			constexpr auto condition = 0x88;
			constexpr auto hidden = 0xa0;
			constexpr auto flags = 0xa4;
			constexpr auto steamItem = 0xa8;
			constexpr auto steamDlc = 0xb0;
			constexpr auto Parent = 0xb8;
			constexpr auto worldModelPrefab = 0xc0;
			constexpr auto isRedirectOf = 0xc8;
			constexpr auto redirectVendingBehaviour = 0xd0;
			constexpr auto itemMods = 0xd8;
			constexpr auto Traits = 0xe0;
			constexpr auto skins = 0xe8;
			constexpr auto _skins2 = 0xf0;
			constexpr auto panel = 0xf8;
			constexpr auto ItemModWearablek__BackingField = 0x100;
			constexpr auto isHoldablek__BackingField = 0x108;
			constexpr auto isUsablek__BackingField = 0x109;
			constexpr auto CraftableWithSkink__BackingField = 0x10a;
			constexpr auto Children = 0x110;

			
		};

		namespace PlayerInput {
			constexpr auto state = 0x20;
			constexpr auto hadInputBuffer = 0x28;
			constexpr auto bodyRotation = 0x2c;
			constexpr auto bodyAngles = 0x3c;
			constexpr auto headRotation = 0x48;
			constexpr auto headAngles = 0x58;
			constexpr auto recoilAngles = 0x64;
			constexpr auto viewDelta = 0x70;
			constexpr auto headLerp = 0x78;
			constexpr auto mouseWheelUp = 0x7c;
			constexpr auto mouseWheelDn = 0x80;
			constexpr auto autorun = 0x84;
			constexpr auto toggleDuck = 0x85;
			constexpr auto toggleAds = 0x86;
			constexpr auto lastAdsEntity = 0x88;
			constexpr auto pendingMouseDelta = 0x90;
			constexpr auto offsetAngles = 0x9c;
			constexpr auto ignoredButtons = 0xa8;
			constexpr auto hasKeyFocus = 0xac;


		};

		namespace PlayerModel {
			constexpr auto acceleration = 0x4;
			constexpr auto rotationYaw = 0x8;
			constexpr auto forward = 0xc;
			constexpr auto right = 0x10;
			constexpr auto up = 0x14;
			constexpr auto ducked = 0x18;
			constexpr auto grounded = 0x1c;
			constexpr auto crawling = 0x20;
			constexpr auto waterlevel = 0x24;
			constexpr auto attack = 0x28;
			constexpr auto attack_alt = 0x2c;
			constexpr auto deploy = 0x30;
			constexpr auto turnOn = 0x34;
			constexpr auto turnOff = 0x38;
			constexpr auto reload = 0x3c;
			constexpr auto throwWeapon = 0x40;
			constexpr auto holster = 0x44;
			constexpr auto aiming = 0x48;
			constexpr auto onLadder = 0x4c;
			constexpr auto posing = 0x50;
			constexpr auto poseType = 0x54;
			constexpr auto relaxGunPose = 0x58;
			constexpr auto vehicle_aim_yaw = 0x5c;
			constexpr auto vehicle_aim_speed = 0x60;
			constexpr auto onPhone = 0x64;
			constexpr auto usePoseTransition = 0x68;
			constexpr auto leftFootIK = 0x6c;
			constexpr auto rightFootIK = 0x70;
			constexpr auto vehicleSteering = 0x74;
			constexpr auto sitReaction = 0x78;
			constexpr auto forwardReaction = 0x7c;
			constexpr auto rightReaction = 0x80;
			constexpr auto ladderType = 0x84;
			constexpr auto collision = 0x18;
			constexpr auto censorshipCube = 0x20;
			constexpr auto censorshipCubeBreasts = 0x28;
			constexpr auto jawBone = 0x30;
			constexpr auto neckBone = 0x38;
			constexpr auto headBone = 0x40;
			constexpr auto eyeController = 0x48;
			constexpr auto blinkController = 0x50;
			constexpr auto SpineBones = 0x58;
			constexpr auto leftFootBone = 0x60;
			constexpr auto rightFootBone = 0x68;
			constexpr auto leftHandPropBone = 0x70;
			constexpr auto rightHandPropBone = 0x78;
			constexpr auto rightHandTarget = 0x80;
			constexpr auto leftHandTargetPosition = 0x8c;
			constexpr auto leftHandTargetRotation = 0x98;
			constexpr auto rightHandTargetPosition = 0xa8;
			constexpr auto rightHandTargetRotation = 0xb4;
			constexpr auto steeringTargetDegrees = 0xc4;
			constexpr auto rightFootTargetPosition = 0xc8;
			constexpr auto rightFootTargetRotation = 0xd4;
			constexpr auto leftFootTargetPosition = 0xe4;
			constexpr auto leftFootTargetRotation = 0xf0;
			constexpr auto CinematicAnimationController = 0x100;
			constexpr auto DefaultAvatar = 0x108;
			constexpr auto CinematicAvatar = 0x110;
			constexpr auto DefaultHoldType = 0x118;
			constexpr auto SleepGesture = 0x120;
			constexpr auto CrawlToIncapacitatedGesture = 0x128;
			constexpr auto StandToIncapacitatedGesture = 0x130;
			constexpr auto CurrentGesture = 0x138;
			constexpr auto MaleSkin = 0x140;
			constexpr auto FemaleSkin = 0x148;
			constexpr auto subsurfaceProfile = 0x150;
			constexpr auto voiceVolume = 0x158;
			constexpr auto skinColor = 0x15c;
			constexpr auto skinNumber = 0x160;
			constexpr auto meshNumber = 0x164;
			constexpr auto hairNumber = 0x168;
			constexpr auto skinType = 0x16c;
			constexpr auto movementSounds = 0x170;
			constexpr auto showSash = 0x178;
			constexpr auto tempPoseType = 0x17c;
			constexpr auto underwearSkin = 0x180;
			constexpr auto overrideSkinSeedk__BackingField = 0x188;
			constexpr auto AimAnglesk__BackingField = 0x190;
			constexpr auto LookAnglesk__BackingField = 0x1a0;
			constexpr auto modelState = 0x1b0;
			constexpr auto position = 0x1b8;
			constexpr auto velocity = 0x1c4;
			constexpr auto speedOverride = 0x1d0;
			constexpr auto newVelocity = 0x1dc;
			constexpr auto rotation = 0x1e8;
			constexpr auto mountedRotation = 0x1f8;
			constexpr auto smoothLeftFootIK = 0x208;
			constexpr auto smoothRightFootIK = 0x214;
			constexpr auto drawShadowOnly = 0x220;
			constexpr auto isIncapacitated = 0x221;
			constexpr auto flinchLocation = 0x224;
			constexpr auto visible = 0x228;
			constexpr auto nameTag = 0x230;
			constexpr auto animatorNeedsWarmup = 0x238;
			constexpr auto isLocalPlayer = 0x239;
			constexpr auto aimSoundDef = 0x240;
			constexpr auto aimEndSoundDef = 0x248;
			constexpr auto InGesture = 0x250;
			constexpr auto CurrentGestureConfig = 0x258;
			constexpr auto InCinematic = 0x260;
			constexpr auto defaultAnimatorController = 0x268;
			constexpr auto _multiMesh = 0x270;
			constexpr auto _animator = 0x278;
			constexpr auto _lodGroup = 0x280;
			constexpr auto _currentGesture = 0x288;
			constexpr auto holdTypeLock = 0x290;
			constexpr auto hasHeldEntity = 0x294;
			constexpr auto wasMountedRightAim = 0x295;
			constexpr auto cachedMask = 0x298;
			constexpr auto cachedConstructionMask = 0x29c;
			constexpr auto WorkshopHeldEntity = 0x2a0;
			constexpr auto wasCrawling = 0x2a8;
			constexpr auto mountedSpineLookWeight = 0x2ac;
			constexpr auto mountedAnimSpeed = 0x2b0;
			constexpr auto preserveBones = 0x2b4;
			constexpr auto downLimitOverride = 0x2b8;
			constexpr auto blendShapeControllers = 0x2c0;
			constexpr auto IsNpck__BackingField = 0x2c8;
			constexpr auto timeSinceReactionStart = 0x2cc;
			constexpr auto timeSinceLeftFootTest = 0x2d0;
			constexpr auto cachedLeftFootPos = 0x2d4;
			constexpr auto cachedLeftFootNormal = 0x2e0;
			constexpr auto timeSinceRightFootTest = 0x2ec;
			constexpr auto cachedRightFootPos = 0x2f0;
			constexpr auto cachedRightFootNormal = 0x2fc;
			constexpr auto pm_uplimit = 0x88;
			constexpr auto pm_downlimit = 0x8c;
			constexpr auto pm_upspine = 0x90;
			constexpr auto pm_downspine = 0x94;
			constexpr auto pm_lookoffset = 0x98;
			constexpr auto pm_anglesmoothspeed = 0xa4;
			constexpr auto pm_nohold = 0xa8;
			constexpr auto pm_ladder = 0xac;
			constexpr auto pm_minweight = 0xb0;
			constexpr auto _smoothAimWeight = 0x308;
			constexpr auto _smoothVelocity = 0x30c;
			constexpr auto _smoothlookAngle = 0x310;
			constexpr auto allowMountedHeadLook = 0x31c;
			constexpr auto smoothLookDir = 0x320;
			constexpr auto lastSafeLookDir = 0x32c;
			constexpr auto Shoulders = 0x338;
			constexpr auto AdditionalSpineBones = 0x340;
			constexpr auto FinishedLegWearables = 0xb8;
			constexpr auto LegParts = 0x348;
			constexpr auto fakeSpineBones = 0x350;
			constexpr auto extraLeanBack = 0x358;
			constexpr auto drawState = 0x35c;
			constexpr auto timeInArmsMode = 0x360;


		};

		namespace ProtoBuf_PlayerTeam {
			constexpr auto teamID = 0x10;
			constexpr auto teamName = 0x18;
			constexpr auto teamLeader = 0x20;
			constexpr auto members = 0x28;
			constexpr auto teamLifetime = 0x30;
			constexpr auto leaderMapNotes = 0x38;
			constexpr auto teamPings = 0x40;
			constexpr auto ShouldPool = 0x48;
			constexpr auto _disposed = 0x49;

		};

		namespace PlayerInventory {
			constexpr auto containerMain = 0x20;
			constexpr auto containerBelt = 0x28;
			constexpr auto containerWear = 0x30;
			constexpr auto crafting = 0x38;
			constexpr auto loot = 0x40;

		};

		namespace ItemContainer {
			constexpr auto flags = 0x10;
			constexpr auto allowedContents = 0x14;
			constexpr auto onlyAllowedItems = 0x18;
			constexpr auto availableSlots = 0x20;
			constexpr auto capacity = 0x28;
			constexpr auto uid = 0x30;
			constexpr auto dirty = 0x38;
			constexpr auto itemList = 0x40;
			constexpr auto temperature = 0x48;
			constexpr auto parent = 0x50;
			constexpr auto playerOwner = 0x58;
			constexpr auto entityOwner = 0x60;
			constexpr auto isServer = 0x68;
			constexpr auto maxStackSize = 0x6c;

		
		};

		namespace Item {
			constexpr auto _condition = 0x10;
			constexpr auto _maxCondition = 0x14;
			constexpr auto info = 0x18;
			constexpr auto uid = 0x20;
			constexpr auto dirty = 0x28;
			constexpr auto amount = 0x2c;
			constexpr auto position = 0x30;
			constexpr auto busyTime = 0x34;
			constexpr auto removeTime = 0x38;
			constexpr auto fuel = 0x3c;
			constexpr auto isServer = 0x40;
			constexpr auto instanceData = 0x48;
			constexpr auto skin = 0x50;
			constexpr auto name = 0x58;
			constexpr auto streamerName = 0x60;
			constexpr auto text = 0x68;
			constexpr auto cookTimeLeft = 0x70;
			constexpr auto progressBar = 0x74;
			constexpr auto OnDirty = 0x78;
			constexpr auto flags = 0x80;
			constexpr auto contents = 0x88;
			constexpr auto parent = 0x90;
			constexpr auto worldEnt = 0x98;
			constexpr auto heldEntity = 0xa8;
			constexpr auto amountOverride = 0xb8;


		};

		namespace Model {
			constexpr auto collision = 0x18;
			constexpr auto rootBone = 0x20;
			constexpr auto headBone = 0x28;
			constexpr auto eyeBone = 0x30;
			constexpr auto animator = 0x38;
			constexpr auto skeleton = 0x40;
			constexpr auto boneTransforms = 0x48;
			constexpr auto boneNames = 0x50;
			constexpr auto boneDict = 0x58;
			constexpr auto skin = 0x60;
			constexpr auto _lodGroup = 0x68;


		};

		namespace MedicalTool {
			constexpr auto healDurationSelf = 0x280;
			constexpr auto healDurationOther = 0x284;
			constexpr auto healDurationOtherWounded = 0x288;
			constexpr auto maxDistanceOther = 0x28c;
			constexpr auto canUseOnOther = 0x290;
			constexpr auto canRevive = 0x291;
			constexpr auto useTarget = 0x298;
			constexpr auto resetTime = 0x2a0;


		};

		namespace HeldEntity {
			constexpr auto worldModelAnimator = 0x168;
			constexpr auto thirdPersonDeploySound = 0x170;
			constexpr auto thirdPersonAimSound = 0x178;
			constexpr auto thirdPersonAimEndSound = 0x180;
			constexpr auto viewModel = 0x188;
			constexpr auto isDeployed = 0x190;
			constexpr auto nextExamineTime = 0x194;
			constexpr auto handBone = 0x198;
			constexpr auto HoldAnimationOverride = 0x1a0;
			constexpr auto isBuildingTool = 0x1a8;
			constexpr auto hostileScore = 0x1ac;
			constexpr auto holsterInfo = 0x1b0;
			constexpr auto HeldCameraMode = 0x1b8;
			constexpr auto FirstPersonArmOffset = 0x1bc;
			constexpr auto FirstPersonArmRotation = 0x1c8;
			constexpr auto FirstPersonRotationStrength = 0x1d4;
			constexpr auto ownerItemUID = 0x1d8;
			constexpr auto _punches = 0x1e0;
			constexpr auto punchAdded = 0x1e8;
			constexpr auto lastPunchTime = 0x1f4;


		};

		namespace UnityEngine_GUIContent {
			constexpr auto m_Text = 0x10;
			constexpr auto m_Image = 0x18;
			constexpr auto m_Tooltip = 0x20;
			constexpr auto s_Image = 0x8;
			constexpr auto s_TextImage = 0x10;
			constexpr auto none = 0x18;

		};

		namespace BaseCombatEntity {
			constexpr auto __menuOption_Menu_Pickup = 0x168;
			constexpr auto skeletonProperties = 0x1d0;
			constexpr auto baseProtection = 0x1d8;
			constexpr auto startHealth = 0x1e0;
			constexpr auto pickup = 0x1e8;
			constexpr auto repair = 0x208;
			constexpr auto ShowHealthInfo = 0x230;
			constexpr auto lifestate = 0x234;
			constexpr auto sendsHitNotification = 0x238;
			constexpr auto sendsMeleeHitNotification = 0x239;
			constexpr auto markAttackerHostile = 0x23a;
			constexpr auto _health = 0x23c;
			constexpr auto _maxHealth = 0x240;
			constexpr auto faction = 0x244;
			constexpr auto deathTime = 0x248;
			constexpr auto lastNotifyFrame = 0x24c;


		};

		namespace InputState {
			constexpr auto current = 0x10;
			constexpr auto previous = 0x18;
			constexpr auto SwallowedButtons = 0x20;


		};

		namespace InputMessage {
			constexpr auto buttons = 0x10;
			constexpr auto aimAngles = 0x14;
			constexpr auto mouseDelta = 0x20;
			constexpr auto ShouldPool = 0x2c;
			constexpr auto _disposed = 0x2d;

		};

		namespace BaseMountable {
			constexpr auto __menuOption_Menu_Mount = 0x250;
			constexpr auto eyePositionOverride = 0x2b8;
			constexpr auto eyeCenterOverride = 0x2c0;
			constexpr auto pitchClamp = 0x2c8;
			constexpr auto yawClamp = 0x2d0;
			constexpr auto canWieldItems = 0x2d8;
			constexpr auto relativeViewAngles = 0x2d9;
			constexpr auto mountAnchor = 0x2e0;
			constexpr auto mountLOSVertOffset = 0x2e8;
			constexpr auto mountPose = 0x2ec;
			constexpr auto maxMountDistance = 0x2f0;
			constexpr auto dismountPositions = 0x2f8;
			constexpr auto checkPlayerLosOnMount = 0x300;
			constexpr auto disableMeshCullingForPlayers = 0x301;
			constexpr auto allowHeadLook = 0x302;
			constexpr auto ignoreVehicleParent = 0x303;
			constexpr auto legacyDismount = 0x304;
			constexpr auto modifiesPlayerCollider = 0x305;
			constexpr auto customPlayerCollider = 0x308;
			constexpr auto mountSoundDef = 0x320;
			constexpr auto swapSoundDef = 0x328;
			constexpr auto dismountSoundDef = 0x330;
			constexpr auto mountTimeStatType = 0x338;
			constexpr auto allowedGestures = 0x33c;
			constexpr auto canDrinkWhileMounted = 0x340;
			constexpr auto allowSleeperMounting = 0x341;
			constexpr auto animateClothInLocalSpace = 0x342;
			constexpr auto MountedCameraMode = 0x344;
			constexpr auto isMobile = 0x348;
			constexpr auto SideLeanAmount = 0x34c;

		};

		namespace TOD_Sky {
			constexpr auto ColorSpace = 0x18;
			constexpr auto ColorRange = 0x1c;
			constexpr auto ColorOutput = 0x20;
			constexpr auto SkyQuality = 0x24;
			constexpr auto CloudQuality = 0x28;
			constexpr auto MeshQuality = 0x2c;
			constexpr auto StarQuality = 0x30;
			constexpr auto Cycle = 0x38;
			constexpr auto World = 0x40;
			constexpr auto Atmosphere = 0x48;
			constexpr auto Day = 0x50;
			constexpr auto Night = 0x58;
			constexpr auto Sun = 0x60;
			constexpr auto Moon = 0x68;
			constexpr auto Stars = 0x70;
			constexpr auto Clouds = 0x78;
			constexpr auto Light = 0x80;
			constexpr auto Fog = 0x88;
			constexpr auto Ambient = 0x90;
			constexpr auto Reflection = 0x98;
			constexpr auto Initializedk__BackingField = 0xa0;
			constexpr auto Componentsk__BackingField = 0xa8;
			constexpr auto Resourcesk__BackingField = 0xb0;
			constexpr auto IsDayk__BackingField = 0xb8;
			constexpr auto IsNightk__BackingField = 0xb9;
			constexpr auto LerpValuek__BackingField = 0xbc;
			constexpr auto SunZenithk__BackingField = 0xc0;
			constexpr auto SunAltitudek__BackingField = 0xc4;
			constexpr auto SunAzimuthk__BackingField = 0xc8;
			constexpr auto MoonZenithk__BackingField = 0xcc;
			constexpr auto MoonAltitudek__BackingField = 0xd0;
			constexpr auto MoonAzimuthk__BackingField = 0xd4;
			constexpr auto SunsetTimek__BackingField = 0xd8;
			constexpr auto SunriseTimek__BackingField = 0xdc;
			constexpr auto LocalSiderealTimek__BackingField = 0xe0;
			constexpr auto SunVisibilityk__BackingField = 0xe4;
			constexpr auto MoonVisibilityk__BackingField = 0xe8;
			constexpr auto SunDirectionk__BackingField = 0xec;
			constexpr auto MoonDirectionk__BackingField = 0xf8;
			constexpr auto LightDirectionk__BackingField = 0x104;
			constexpr auto LocalSunDirectionk__BackingField = 0x110;
			constexpr auto LocalMoonDirectionk__BackingField = 0x11c;
			constexpr auto LocalLightDirectionk__BackingField = 0x128;
			constexpr auto SunLightColork__BackingField = 0x134;
			constexpr auto MoonLightColork__BackingField = 0x144;
			constexpr auto SunRayColork__BackingField = 0x154;
			constexpr auto MoonRayColork__BackingField = 0x164;
			constexpr auto SunSkyColork__BackingField = 0x174;
			constexpr auto MoonSkyColork__BackingField = 0x184;
			constexpr auto SunMeshColork__BackingField = 0x194;
			constexpr auto MoonMeshColork__BackingField = 0x1a4;
			constexpr auto SunCloudColork__BackingField = 0x1b4;
			constexpr auto MoonCloudColork__BackingField = 0x1c4;
			constexpr auto FogColork__BackingField = 0x1d4;
			constexpr auto GroundColork__BackingField = 0x1e4;
			constexpr auto AmbientColork__BackingField = 0x1f4;
			constexpr auto MoonHaloColork__BackingField = 0x204;
			constexpr auto ReflectionCur = 0x218;
			constexpr auto ReflectionSrc = 0x220;
			constexpr auto ReflectionDst = 0x228;
			constexpr auto ReflectionUpdateSpeed = 0x8;
			constexpr auto ReflectionResolution = 0xc;
			constexpr auto ReflectionUpdateInterval = 0x10;
			constexpr auto ReflectionTimeSlicing = 0x14;
			constexpr auto timeSinceLightUpdate = 0x230;
			constexpr auto timeSinceAmbientUpdate = 0x234;
			constexpr auto timeSinceReflectionUpdate = 0x238;
			constexpr auto kBetaMie = 0x23c;
			constexpr auto kSun = 0x248;
			constexpr auto k4PI = 0x258;
			constexpr auto kRadius = 0x268;
			constexpr auto kScale = 0x278;


		};



		namespace UnityEngine_PhysicsScene {
			constexpr auto m_Handle = 0x10;


		};


		namespace BaseHelicopter {
			constexpr auto rotorPivot = 0x250;
			constexpr auto mainRotor = 0x258;
			constexpr auto mainRotor_blades = 0x260;
			constexpr auto mainRotor_blur = 0x268;
			constexpr auto tailRotor = 0x270;
			constexpr auto tailRotor_blades = 0x278;
			constexpr auto tailRotor_blur = 0x280;
			constexpr auto rocket_tube_left = 0x288;
			constexpr auto rocket_tube_right = 0x290;
			constexpr auto left_gun_yaw = 0x298;
			constexpr auto left_gun_pitch = 0x2a0;
			constexpr auto left_gun_muzzle = 0x2a8;
			constexpr auto right_gun_yaw = 0x2b0;
			constexpr auto right_gun_pitch = 0x2b8;
			constexpr auto right_gun_muzzle = 0x2c0;
			constexpr auto spotlight_rotation = 0x2c8;
			constexpr auto rocket_fire_effect = 0x2d0;
			constexpr auto gun_fire_effect = 0x2d8;
			constexpr auto bulletEffect = 0x2e0;
			constexpr auto explosionEffect = 0x2e8;
			constexpr auto fireBall = 0x2f0;
			constexpr auto crateToDrop = 0x2f8;
			constexpr auto maxCratesToSpawn = 0x300;
			constexpr auto bulletSpeed = 0x304;
			constexpr auto bulletDamage = 0x308;
			constexpr auto servergibs = 0x310;
			constexpr auto debrisFieldMarker = 0x318;
			constexpr auto rotorWashSoundDef = 0x320;
			constexpr auto _rotorWashSound = 0x328;
			constexpr auto flightEngineSoundDef = 0x330;
			constexpr auto flightThwopsSoundDef = 0x338;
			constexpr auto flightEngineSound = 0x340;
			constexpr auto flightThwopsSound = 0x348;
			constexpr auto flightEngineGainMod = 0x350;
			constexpr auto flightThwopsGainMod = 0x358;
			constexpr auto rotorGainModSmoothing = 0x360;
			constexpr auto engineGainMin = 0x364;
			constexpr auto engineGainMax = 0x368;
			constexpr auto thwopGainMin = 0x36c;
			constexpr auto thwopGainMax = 0x370;
			constexpr auto spotlightJitterAmount = 0x374;
			constexpr auto spotlightJitterSpeed = 0x378;
			constexpr auto nightLights = 0x380;
			constexpr auto spotlightTarget = 0x388;
			constexpr auto engineSpeed = 0x394;
			constexpr auto targetEngineSpeed = 0x398;
			constexpr auto blur_rotationScale = 0x39c;
			constexpr auto _rotorWashParticles = 0x3a0;
			constexpr auto myAI = 0x3a8;
			constexpr auto mapMarkerEntityPrefab = 0x3b0;
			constexpr auto client_rotorPivotIdeal = 0x3b8;
			constexpr auto nightLightsOn = 0x3c8;
			constexpr auto weakspots = 0x3d0;

		};

		namespace HitInfo {
			constexpr auto Initiator = 0x10;
			constexpr auto WeaponPrefab = 0x18;
			constexpr auto Weapon = 0x20;
			constexpr auto DoHitEffects = 0x28;
			constexpr auto DoDecals = 0x29;
			constexpr auto IsPredicting = 0x2a;
			constexpr auto UseProtection = 0x2b;
			constexpr auto Predicted = 0x30;
			constexpr auto DidHit = 0x38;
			constexpr auto HitEntity = 0x40;
			constexpr auto HitBone = 0x48;
			constexpr auto HitPart = 0x4c;
			constexpr auto HitMaterial = 0x50;
			constexpr auto HitPositionWorld = 0x54;
			constexpr auto HitPositionLocal = 0x60;
			constexpr auto HitNormalWorld = 0x6c;
			constexpr auto HitNormalLocal = 0x78;
			constexpr auto PointStart = 0x84;
			constexpr auto PointEnd = 0x90;
			constexpr auto ProjectileID = 0x9c;
			constexpr auto ProjectileHits = 0xa0;
			constexpr auto ProjectileDistance = 0xa4;
			constexpr auto ProjectileIntegrity = 0xa8;
			constexpr auto ProjectileTravelTime = 0xac;
			constexpr auto ProjectileTrajectoryMismatch = 0xb0;
			constexpr auto ProjectileVelocity = 0xb4;
			constexpr auto ProjectilePrefab = 0xc0;
			constexpr auto material = 0xc8;
			constexpr auto damageProperties = 0xd0;
			constexpr auto damageTypes = 0xd8;
			constexpr auto CanGather = 0xe0;
			constexpr auto DidGather = 0xe1;
			constexpr auto gatherScale = 0xe4;


		};

		namespace System_Number {
			constexpr auto s_negCurrencyFormats = 0x8;
			constexpr auto s_posPercentFormats = 0x10;
			constexpr auto s_negPercentFormats = 0x18;
			constexpr auto s_negNumberFormats = 0x20;
			constexpr auto s_charToHexLookup = 0x28;
			constexpr auto s_rgval64Power10 = 0x30;
			constexpr auto s_rgexp64Power10 = 0x38;
			constexpr auto s_rgval64Power10By16 = 0x40;
			constexpr auto s_rgexp64Power10By16 = 0x48;


		};

		namespace System_Globalization_NumberFormatInfo {
			constexpr auto numberGroupSizes = 0x10;
			constexpr auto currencyGroupSizes = 0x18;
			constexpr auto percentGroupSizes = 0x20;
			constexpr auto positiveSign = 0x28;
			constexpr auto negativeSign = 0x30;
			constexpr auto numberDecimalSeparator = 0x38;
			constexpr auto numberGroupSeparator = 0x40;
			constexpr auto currencyGroupSeparator = 0x48;
			constexpr auto currencyDecimalSeparator = 0x50;
			constexpr auto currencySymbol = 0x58;
			constexpr auto ansiCurrencySymbol = 0x60;
			constexpr auto nanSymbol = 0x68;
			constexpr auto positiveInfinitySymbol = 0x70;
			constexpr auto negativeInfinitySymbol = 0x78;
			constexpr auto percentDecimalSeparator = 0x80;
			constexpr auto percentGroupSeparator = 0x88;
			constexpr auto percentSymbol = 0x90;
			constexpr auto perMilleSymbol = 0x98;
			constexpr auto nativeDigits = 0xa0;
			constexpr auto m_dataItem = 0xa8;
			constexpr auto numberDecimalDigits = 0xac;
			constexpr auto currencyDecimalDigits = 0xb0;
			constexpr auto currencyPositivePattern = 0xb4;
			constexpr auto currencyNegativePattern = 0xb8;
			constexpr auto numberNegativePattern = 0xbc;
			constexpr auto percentPositivePattern = 0xc0;
			constexpr auto percentNegativePattern = 0xc4;
			constexpr auto percentDecimalDigits = 0xc8;
			constexpr auto digitSubstitution = 0xcc;
			constexpr auto isReadOnly = 0xd0;
			constexpr auto m_useUserOverride = 0xd1;
			constexpr auto m_isInvariant = 0xd2;
			constexpr auto validForParseAsNumber = 0xd3;
			constexpr auto validForParseAsCurrency = 0xd4;

			
		};



		namespace TOD_AtmosphereParameters {
			constexpr auto RayleighMultiplier = 0x10;
			constexpr auto MieMultiplier = 0x14;
			constexpr auto Brightness = 0x18;
			constexpr auto Contrast = 0x1c;
			constexpr auto Directionality = 0x20;
			constexpr auto Fogginess = 0x24;

		};

		namespace TOD_MoonParameters {
			constexpr auto MeshSize = 0x10;
			constexpr auto MeshBrightness = 0x14;
			constexpr auto MeshContrast = 0x18;
			constexpr auto HaloSize = 0x1c;
			constexpr auto HaloBrightness = 0x20;
			constexpr auto Position = 0x24;

		};

		namespace TOD_CloudParameters {
			constexpr auto Size = 0x10;
			constexpr auto Opacity = 0x14;
			constexpr auto Coverage = 0x18;
			constexpr auto Sharpness = 0x1c;
			constexpr auto Coloring = 0x20;
			constexpr auto Attenuation = 0x24;
			constexpr auto Saturation = 0x28;
			constexpr auto Scattering = 0x2c;
			constexpr auto Brightness = 0x30;

		};

		namespace TOD_NightParameters {
			constexpr auto MoonColor = 0x10;
			constexpr auto LightColor = 0x18;
			constexpr auto RayColor = 0x20;
			constexpr auto SkyColor = 0x28;
			constexpr auto CloudColor = 0x30;
			constexpr auto FogColor = 0x38;
			constexpr auto AmbientColor = 0x40;
			constexpr auto LightIntensity = 0x48;
			constexpr auto ShadowStrength = 0x4c;
			constexpr auto AmbientMultiplier = 0x50;
			constexpr auto ReflectionMultiplier = 0x54;

		};

	}

namespace CO {
	// BasePlayer

    constexpr auto set_timeScale = 0x2757570;//  UnityEngine.Time set_timeScale
	constexpr auto ClientUpdate = 0x8B1FF0; // protected void ClientUpdate() { }
	constexpr auto ClientUpdate_Sleeping = 0x8B1C20; // protected void ClientUpdate_Sleeping() { }
	constexpr auto Refract = 0x70A150; // private bool Refract(ref uint seed, Vector3 point, Vector3 normal, float resistance) { }
	constexpr auto SendSignalBroadcast = 0x5612A0; // public void SendSignalBroadcast(BaseEntity.Signal signal, string arg = "") { }
	constexpr auto GetJumpHeight = 0x8B8240; // public float GetJumpHeight() { }
	constexpr auto MathfMin = 0x274A7A0; // public static float Min(float a, float b) { }
	constexpr auto MathfAbs = 0x2749E00; // public static float Abs(float f) { }
	constexpr auto MathfMax = 0x274A790; // public static float Max(float a, float b) { }
	constexpr auto MathfCos = 0x274A2D0; // public static float Cos(float f) { }
	constexpr auto MathfSin = 0x274AA40; // public static float Sin(float f) { }
	constexpr auto GetHeight = 0x8B77B0; // public float GetHeight(bool ducked) { }
	constexpr auto GetRadius = 0x7B24A0; // public float GetRadius() { }
	constexpr auto CheckCapsule = 0x27AA430; // public static bool CheckCapsule(Vector3 start, Vector3 end, float radius, int layerMask, QueryTriggerInteraction queryTriggerInteraction) { }
	constexpr auto RebuildAll = 0x9F4640; //public static void RebuildAll() { }
	constexpr auto GetMaxSpeed = 0x8B8410; // public float GetMaxSpeed() { }
	constexpr auto DoFixedUpdate = 0x378B30;//public virtual void DoFixedUpdate(ModelState modelState) { }
	constexpr auto get_rotation = 0x7835A0; // playereyes public Quaternion get_rotation() { }
	constexpr auto Play = 0x730200; // ViewModel// public void Play(string name, int layer = 0) { }
	constexpr auto GetRandomVelocity = 0x842420; // 	public float GetRandomVelocity() { }
	constexpr auto AddPunch = 0x5B52C0; // public virtual void AddPunch(Vector3 amount, float duration) { }
	constexpr auto get_jumped = 0x1E58350; // public bool get_jumped() { }
	constexpr auto VisUpdateUsingCulling = 0x8D6250; //	private void VisUpdateUsingCulling(float dist, bool visibility) { }
	constexpr auto IsDucked = 0x8BE0A0; // public bool IsDucked() { }
	constexpr auto OnLand = 0x8C1C00; // public void OnLand(float fVelocity) { } || BasePlayer->OnLand
	constexpr auto get_position = 0x7830F0; // playereyes->get_position //public Vector3 get_position() { }
	constexpr auto AssistPlayer = 0x8C0EC0; // public void Menu_AssistPlayer(BasePlayer player) { }
	constexpr auto UpdateAmbient = 0x381AF0; // public void UpdateAmbient() { } || TOD_Sky
	constexpr auto Launch = 0x7097B0; // internal void Launch() { }
	constexpr auto get_isHeadshot = 0x806A10; // public bool get_isHeadshot() { }
	constexpr auto DoHitNotify = 0x7A9390; // public void DoHitNotify(HitInfo info) { }
	constexpr auto StartAttackCooldown = 0x74D8B0; // protected void StartAttackCooldown(float cooldown) { }
	constexpr auto ProcessAttack = 0x580D60; // protected virtual void ProcessAttack(HitTest hit) { }
	constexpr auto get_transform = 0x2746C30; // public Transform get_transform() { } | UnityEngine::Component
	constexpr auto DoMovement = 0x707F20; // private void DoMovement(float deltaTime) { }
	constexpr auto DoHit = 0x707810; // private bool DoHit(HitTest test, Vector3 point, Vector3 normal) { }
	constexpr auto ClientInput = 0x8AF150; // internal virtual void ClientInput(InputState state) { }
	constexpr auto set_flying = 0x1E58450; // public void set_flying(bool value) { }
	constexpr auto CanAttack = 0x8ACBD0; // public bool CanAttack() { }
	constexpr auto SendClientTick = 0x8D0EA0; // internal void SendClientTick() { }
	constexpr auto HandleJumping = 0x7C2470; // private void HandleJumping(ModelState state, bool wantsJump, bool jumpInDirection = False) { }
	constexpr auto CreateProjectile = 0x57F7A0; // private Projectile CreateProjectile(string prefabPath, Vector3 pos, Vector3 forward, Vector3 velocity) { }
	constexpr auto CanHoldItems = 0x7AED30; // public virtual bool CanHoldItems() { }
	constexpr auto SendProjectileAttack = 0x8D15E0; // public void SendProjectileAttack(PlayerProjectileAttack attack) { }
	constexpr auto KnockDoor = 0xB03C90; // public void Menu_KnockDoor(BasePlayer player) { }
	constexpr auto OpenDoor = 0xB03E10; // public void Menu_OpenDoor(BasePlayer player) { }
	constexpr auto OpenHatch = 0xB03E60; // public void Menu_ToggleHatch(BasePlayer player) { }
	constexpr auto set_shader = 0x2732450; // public void set_shader(Shader value) { }
	constexpr auto get_shader = 0xA9D8A0; // public Shader get_shader() { }
	constexpr auto SetInt = 0x2731720; // public void SetInt(string name, int value) { } || public class Material : Object
	constexpr auto SetColor = 0x27322E0; // public class Material : Object || public void set_color(Color value) { }
	constexpr auto UpdateVelocity = 0x7C5FA0;// private void UpdateVelocity() { }
	constexpr auto ClosestPoint = 0x27A6D70; // public Vector3 ClosestPoint(Vector3 position) { }
	constexpr auto Set_rain = 0xB7FE70; // weather set_rain 	public static void set_rain(float value) { }
	constexpr auto set_storm_chance = 0xB7FFD0; // weather set_storm_chance
	constexpr auto set_fog_chance = 0xB7FAD0; // weather set_fog_chance
	constexpr auto get_BodyLeanOffset = 0x782790; // PlayerEyes get_BodyLeanOffset
	constexpr auto DoFirstPersonCamera = 0x77F5E0;// PlayerEyes DoFirstPersonCamera

	constexpr auto EyePositionForPlayer = 0x7AF530; // BaseMountable EyePositionForPlayer
	constexpr auto IsDown = 0x839600;// InputState IsDown

//там в misc.h в начале 2 оффсета

	// script.json
	constexpr auto BaseNetworkable = 52264688; // BaseNetworkable_c*
    constexpr auto ConvarGraphics = 52503112; // ConVar_Graphics_c*
    constexpr auto HitTest = 52522520; // HitTest_c*
    constexpr auto Client = 52332432; // ConVar_Client_c*
    constexpr auto ConvarAdmin = 52812296; // ConVar_Admin_c*
	// dump.cs
	constexpr auto ServerRPC = 0x561450; // public void ServerRPC(string funcName) { }
	constexpr auto LineOfSight = 0x720F60; // public static bool LineOfSight(Vector3 p0, Vector3 p1, int layerMask, BaseEntity ignoreEntity) { }
	constexpr auto EffectRun = 0x74B6C0; // public static void Run(string strName, GameObject obj) { }
	constexpr auto IsUpgradeBlocked = 0x595B80; // private bool IsUpgradeBlocked() { }
	constexpr auto get_Entity = 0x7BC910; // public static BasePlayer get_Entity() { } || public static class LocalPlayer
	constexpr auto Magnitude2D = 0x20C2B30; // public static float Magnitude2D(Vector3 v) { }
	constexpr auto CanAffordUpgrade = 0x591CB0; // private bool CanAffordUpgrade(BuildingGrade.Enum iGrade, ulong iSkin, BasePlayer player) { }
	constexpr auto CanChangeToGrade = 0x591E70; // private bool CanChangeToGrade(BuildingGrade.Enum iGrade, ulong iSkin, BasePlayer player) { }
	constexpr auto UpgradeToGrade = 0x5972B0; // private void UpgradeToGrade(BuildingGrade.Enum iGrade, ulong iSkin, BasePlayer player) { }
	constexpr auto MoveTowards = 0x275D7F0; // public static Vector3 MoveTowards(Vector3 current, Vector3 target, float maxDistanceDelta) { }

	constexpr auto IsBeingHacked = 0x578BA0; // public bool IsBeingHacked() { }
	constexpr auto IsFullyHacked = 0x4A3340; // public bool IsFullyHacked() { }
	constexpr auto set_rayleigh = 0xB7F270;// public static void set_atmosphere_rayleigh(float value) { }
	constexpr auto set_mie = 0xB7F1C0; // public static void set_atmosphere_mie(float value) { }
	constexpr auto set_brightness = 0xB7EFB0; // public static void set_atmosphere_brightness(float value) { }
	constexpr auto IsHidden = 0x4A4D40; // public class StashContainer : StorageContainer || public bool IsHidden() { }
	constexpr auto GetModifiedAimConeDirection = 0x64A8C0; // public static Vector3 GetModifiedAimConeDirection(float aimCone, Vector3 inputVec, bool anywhereInside = True) { }
	constexpr auto Run = 0xDF1C60; // public static string Run(ConsoleSystem.Option options, string strCommand, object[] args) { }
	constexpr auto StartCoroutine = 0x274DAA0; // public Coroutine StartCoroutine(IEnumerator routine) { }
	constexpr auto CreateEffect = 0x7387B0; // public static GameObject CreateEffect(string strPrefab, Effect effect) { }
	constexpr auto set_aspect = 0x2723340; //public void set_aspect(float value) { }
	constexpr auto Get_Camera_Main = 0x2722B10; //public static Camera get_main() { }
	constexpr auto set_collider = 0x27A6BA0; //public void set_radius(float value) { }
}