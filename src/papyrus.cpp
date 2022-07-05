#include "papyrus.h"
#include "scale.h"

using namespace SKSE;
using namespace Gts;
using namespace RE;
using namespace RE::BSScript;

namespace {
	constexpr std::string_view PapyrusClass = "GtsPlugin";

	bool SetModelScale(StaticFunctionTag*, Actor* actor, float scale) {
		return set_scale(actor, scale);
	}
	float GetModelScale(StaticFunctionTag*, Actor* actor) {
		return get_scale(actor);
	}
}

namespace Gts {
	bool register_papyrus(IVirtualMachine* vm) {
		vm->RegisterFunction("SetModelScale", PapyrusClass, SetModelScale);
		vm->RegisterFunction("GetModelScale", PapyrusClass, GetModelScale);

		return true;
	}
}
