class StringFormat {
public:
	template <typename ...Args>
	static std::wstring format(const std::wstring_view text, Args... args) {
		const auto size = static_cast<std::size_t>(std::swprintf(nullptr, 0, text.data(), std::forward<Args>(args)...) + 1);

		const std::unique_ptr<wchar_t[]> buffer(new wchar_t[size]);
		std::swprintf(buffer.get(), size, text.data(), std::forward<Args>(args)...);

		const auto str = std::wstring(buffer.get(), buffer.get() + size - 1);

		return str;
	}

	template <typename ...Args>
	static std::string format(const std::string_view text, Args... args) {
		char temp[256]{};
		const auto size = static_cast<std::size_t>(std::sprintf(temp, text.data(), std::forward<Args>(args)...) + 1);

		const std::unique_ptr<char[]> buffer(new char[size]);
		std::sprintf(buffer.get(), text.data(), std::forward<Args>(args)...);

		const auto str = std::string(buffer.get(), buffer.get() + size - 1);

		return str;
	}
};

struct _Color {
public:
	float r, g, b, a;

	_Color(float r, float g, float b, float a) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
	static _Color red() { return { 1, 0, 0, 1 }; }
	static _Color green() { return { 0, 1, 0, 1 }; }
	static _Color blue() { return { 0, 0, 1, 1 }; }
	static _Color yellow() { return { 1, 1, 0, 1 }; }
	static _Color white() { return { 1, 1, 1, 1 }; }
};

struct Matrix4x4 {
	union {
		struct {
			float        _11, _12, _13, _14;
			float        _21, _22, _23, _24;
			float        _31, _32, _33, _34;
			float        _41, _42, _43, _44;

		}; float m[4][4];
	};
};