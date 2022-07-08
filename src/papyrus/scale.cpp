#include "papyrus/scale.h"
#include "scale.h"
#include "persistent.h"
#include "GtsManager.h"


using namespace SKSE;
using namespace Gts;
using namespace RE;
using namespace RE::BSScript;

namespace {
	constexpr std::string_view PapyrusClass = "GtsScale";

	bool SetModelScale(StaticFunctionTag*, Actor* actor, float scale) {
		bool result = false;
		auto actor_data = Persistent::GetSingleton().GetActorData(actor);
		if (actor_data) {
			result = set_model_scale(actor, scale);
			actor_data->visual_scale = scale;
			actor_data->visual_scale_v = 0.0;
			actor_data->target_scale = scale;
		}
		return result;
	}
	float GetModelScale(StaticFunctionTag*, Actor* actor) {
		if (!actor) {
			return 0.0;
		}
		auto result = get_model_scale(actor);
		return result;
	}
	bool ModModelScale(StaticFunctionTag*, Actor* actor, float amt) {
		bool result = false;
		auto actor_data = Persistent::GetSingleton().GetActorData(actor);
		if (actor_data) {
			auto scale = get_model_scale(actor) + amt;
			result = set_model_scale(actor, scale);
			actor_data->visual_scale = scale;
			actor_data->visual_scale_v = 0.0;
			actor_data->target_scale = scale;
		}
		return result;
	}

	void SetTargetScale(StaticFunctionTag*, Actor* actor, float scale) {
		if (!actor) {
			return;
		}
		auto actor_data = Persistent::GetSingleton().GetActorData(actor);
		if (actor_data) {
			actor_data->target_scale = scale;
		}
	}

	float GetTargetScale(StaticFunctionTag*, Actor* actor) {
		if (!actor) {
			return 0.0;
		}
		auto actor_data = Persistent::GetSingleton().GetActorData(actor);
		if (actor_data) {
			return actor_data->target_scale;
		}
		return 0.0;
	}

	void ModTargetScale(StaticFunctionTag*, Actor* actor, float amt) {
		if (!actor) {
			return;
		}
		auto actor_data = Persistent::GetSingleton().GetActorData(actor);
		if (actor_data) {
			actor_data->target_scale += amt;
		}
	}

	void SetMaxScale(StaticFunctionTag*, Actor* actor, float scale) {
		if (!actor) {
			return;
		}
		auto actor_data = Persistent::GetSingleton().GetActorData(actor);
		if (actor_data) {
			actor_data->max_scale = scale;
		}
	}

	float GetMaxScale(StaticFunctionTag*, Actor* actor) {
		if (!actor) {
			return 0.0;
		}
		auto actor_data = Persistent::GetSingleton().GetActorData(actor);
		if (actor_data) {
			return actor_data->max_scale;
		}
		return 0.0;
	}

	void ModMaxScale(StaticFunctionTag*, Actor* actor, float amt) {
		if (!actor) {
			return;
		}
		auto actor_data = Persistent::GetSingleton().GetActorData(actor);
		if (actor_data) {
			actor_data->max_scale += amt;
		}
	}

	float GetVisualScale(StaticFunctionTag*, Actor* actor) {
		if (!actor) {
			return 0.0;
		}
		auto actor_data = Persistent::GetSingleton().GetActorData(actor);
		if (actor_data) {
			return actor_data->visual_scale;
		}
		return 0.0;
	}

	void ModTeammateScale(StaticFunctionTag*, float amt) {
		log::info("+ ModTeammateScale");
		for (auto actor: find_actors()) {
			if (!actor) {
				continue;
			}
			if (!actor->Is3DLoaded()) {
				continue;
			}
			log::info("  - ModTeammateScale For: {}", actor->GetActorBase()->GetFullName());
			if (actor->IsPlayerTeammate()) {
				log::info("  - Is teammate");
				auto actor_data = Persistent::GetSingleton().GetActorData(actor);
				if (actor_data) {
					log::info("  - Has Data");
					actor_data->target_scale += amt;
				}
			}
		}
		log::info("- ModTeammateScale");
	}
}

namespace Gts {
	bool register_papyrus_scale(IVirtualMachine* vm) {
		vm->RegisterFunction("SetModelScale", PapyrusClass, SetModelScale);
		vm->RegisterFunction("GetModelScale", PapyrusClass, GetModelScale);
		vm->RegisterFunction("ModModelScale", PapyrusClass, ModModelScale);

		vm->RegisterFunction("SetTargetScale", PapyrusClass, SetTargetScale);
		vm->RegisterFunction("GetTargetScale", PapyrusClass, GetTargetScale);
		vm->RegisterFunction("ModTargetScale", PapyrusClass, ModTargetScale);

		vm->RegisterFunction("SetMaxScale", PapyrusClass, SetMaxScale);
		vm->RegisterFunction("GetMaxScale", PapyrusClass, GetMaxScale);
		vm->RegisterFunction("ModMaxScale", PapyrusClass, ModMaxScale);

		vm->RegisterFunction("GetVisualScale", PapyrusClass, GetVisualScale);

		vm->RegisterFunction("ModTeammateScale", PapyrusClass, ModTeammateScale);

		return true;
	}
}