#pragma once
// Misc codes
#include <SKSE/SKSE.h>
#include <math.h>

using namespace std;
using namespace RE;
using namespace SKSE;

namespace Gts {
	inline static float* g_delta_time = (float*)REL::RelocationID(523660, 410199).address();

	inline std::string_view actor_name(Actor* actor) {
		if (actor) {
			auto ba = actor->GetActorBase();
			if (ba) {
				return ba->GetFullName();
			}
		}
		return "";
	}

	inline bool starts_with(std::string_view arg, std::string_view prefix) {
		return arg.compare(0, prefix.size(), prefix);
	}

	vector<Actor*> find_actors();
	float unit_to_meter(float unit);
	float meter_to_unit(float meter);
	void critically_damped(
		float& x,
		float& v,
		float x_goal,
		float halflife,
		float dt);

	inline bool logit(Actor* actor) {
		return (actor->formID == 0x14 || actor->IsPlayerTeammate());
	}

	struct SoftPotential {
		float k;
		float n;
		float s;
		float o;
	};
	inline float soft_core(float x, float k, float n, float s, float o) {
		return 1.0/(pow(1.0+pow(k*(x-o),n*s),1.0/s));
	}
	inline float soft_core(float x, SoftPotential& soft_potential) {
		return soft_core(x, soft_potential.k, soft_potential.n, soft_potential.s, soft_potential.o);
	}
}
