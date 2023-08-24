
namespace StringConverter {
	std::wstring ToUnicode(const std::string& str) {
		using convert_typeX = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_typeX, wchar_t> converterX;
		return converterX.from_bytes(str);
	}

	std::string ToASCII(const std::wstring& wstr) {
		using convert_typeX = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_typeX, wchar_t> converterX;
		return converterX.to_bytes(wstr);
	}
}
float timee = 120.f;
UINT vps = 1;
WNDPROC original_windowproc = nullptr;
bool sdk_initialized = false;
bool timer_initialized = false;
float timeSinceStartup = 0;
float timeFrequency = 0;
float get_time_since_startup() {
	LARGE_INTEGER PerformanceCount;
	LARGE_INTEGER FrequencyCount;

	if (!timer_initialized) {
		timer_initialized = true;

		PerformanceCount.QuadPart = 0;
		QueryPerformanceCounter(&PerformanceCount);

		FrequencyCount.QuadPart = 0;
		QueryPerformanceFrequency(&FrequencyCount);

		timeFrequency = float(FrequencyCount.QuadPart);

		timeSinceStartup = float(PerformanceCount.QuadPart);
	}

	PerformanceCount.QuadPart = 0;
	QueryPerformanceCounter(&PerformanceCount);

	return float(PerformanceCount.QuadPart - timeSinceStartup) / timeFrequency;
}
class LogSystem {
public:
	static inline int max_entries = 10;

	static void draw_text(Vector2, std::string, ImColor col = ImColor(255, 255, 255), int timer = 0);

	struct LogEntry {
	public:
		std::string message;
		float startedAt;
		float duration;

		LogEntry(std::string message, float duration) {
			this->message = message;
			this->duration = duration;
			this->startedAt = get_time_since_startup();
		}
	};

	static inline std::vector<LogEntry> logs = std::vector<LogEntry>();
	static inline std::vector<Explosion> loggedExplosions = std::vector<Explosion>();

	static void Log(std::string message, float duration) {
		if (logs.size() >= max_entries)
			logs.erase(logs.begin());

		logs.push_back(LogEntry(message, duration));
	}
	static void LogExplosion(std::string type, Vector3 pos) {
		bool explosionCollision = false;
		std::vector<Explosion>::iterator it;
		for (it = loggedExplosions.begin(); it != loggedExplosions.end(); it++) {
			Vector2 explPos;
			if (it->position.Distance(pos) <= 25.0f) {
				explosionCollision = true;
				break;
			}
		}
		if (!explosionCollision) {
			Explosion explosion = Explosion();
			explosion.name = StringFormat::format(xorstr_("%s Raid"), type.c_str());
			explosion.position = pos;
			explosion.timeSince = get_time_since_startup();
			loggedExplosions.push_back(explosion);
		}
	}

	static void Render() {
		float yPos = 5.f;
		for (int i = 0; i < logs.size(); i++) {
			LogEntry entry = logs[i];
			if ((get_time_since_startup() - entry.startedAt) >= entry.duration) {
				logs.erase(logs.begin() + i);
				continue;
			}
			draw_text(Vector2(5, yPos), entry.message, ImColor(255, 255, 255));
			yPos += 25.0f;
		}
	}
	static void RenderExplosions() {
		for (int i = 0; i < LogSystem::loggedExplosions.size(); i++) {
			if ((get_time_since_startup() - LogSystem::loggedExplosions[i].timeSince) >= timee) {
				LogSystem::loggedExplosions.erase(LogSystem::loggedExplosions.begin() + i);
				continue;
			}
			Explosion explosion = LogSystem::loggedExplosions.at(i);

			Vector2 explPos;
			if (utils::w2s(explosion.position, explPos)) {
			//	OxyRender::Text(explPos,D2D1::ColorF::Red,			true,true,StringConverter::ToUnicode(StringFormat::format(xorstr_("%s [%1.0fm] [%d]"),explosion.name.c_str(),Math::Distance_3D(explosion.position, LocalPlayer::Entity()->GetBoneByID(head)),(int)(timee - (get_time_since_startup() - LogSystem::loggedExplosions[i].timeSince)))).c_str()

				//);
			
				std::string string;
				char buf[256] = { 0 }; sprintf_s(buf, xorstr_("%s [%1.0fm] [%d]"), explosion.name.c_str(), Math::Distance_3D(explosion.position, LocalPlayer::Entity()->GetBoneByID(head)), (int)(timee - (get_time_since_startup() - LogSystem::loggedExplosions[i].timeSince)));
				string += buf;
				g_Render->DrawString(explPos.x, explPos.y, ImColor(255, 255, 255), render2::outline | render2::centered_x, Cuniaabyser, 12, string.c_str());
			}
		}
	}
};
void LogSystem::draw_text(Vector2 pos, std::string str, ImColor col, int timer) {
	g_Render->DrawString(pos.x + 5, pos.y + 5, ImColor(255, 255, 255), render2::outline, Cuniaabyser, 12, str.c_str());
}
std::map<uint64_t, BaseNetworkable*> projectile_targets = std::map<uint64_t, BaseNetworkable*>();