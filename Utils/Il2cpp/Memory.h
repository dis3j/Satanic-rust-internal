template <typename T>
T Read(DWORD64 address) {
	if (address > 0x40000 && (address + sizeof(T)) < 0x7FFFFFFF0000) {
		return *(T*)(address);
	}
	else {
		return T{};
	}
}
template <typename T>
void Write(DWORD64 address, T data) {
	if (address > 0x40000 && (address + sizeof(T)) < 0x7FFFFFFF0000) {
		*(T*)(address) = data;
	}
}
namespace mem {
	template<typename t>
	t neko_read(uintptr_t addr) {
		if (addr < 0xffffff)
			return t();
		if (addr > 0x7fffffff0000)
			return t();

		return *reinterpret_cast<t*>(addr);
	}

	template<typename t>
	bool neko_write(uintptr_t addr, t buffer) {
		*reinterpret_cast<t*>(addr) = buffer;
		return true;
	}
}
#define read(Addr, Type) Read<Type>((DWORD64)Addr)
#define write(Addr, Data, Type) Write<Type>((DWORD64)Addr, Data);
#define CALLED_BY(func,off) (reinterpret_cast<std::uint64_t>(_ReturnAddress()) > func && reinterpret_cast<std::uint64_t>(_ReturnAddress()) < func + off)
#define safe_read(Addr, Type) (((((ULONG64)Addr) > 0x400000) && (((ULONG64)Addr + sizeof(Type)) < 0x00007FFFFFFF0000)) ? *(Type*)((ULONG64)Addr) : Type{})
#define safe_write(Addr, Data, Type) if ((((ULONG64)Addr) > 0x400000) && (((ULONG64)Addr + sizeof(Type)) < 0x00007FFFFFFF0000)) { *(Type*)((ULONG64)Addr) = (Data); }

#define OFFSETFIELD(type, name, offset) struct {unsigned char _pad##__COUNTER__[offset]; type name;}