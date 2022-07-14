#pragma once
using namespace RE;
using namespace SKSE;

namespace Hooks
{
	class Hook_TESObjectREFR
	{
		public:
			static void Hook();
		private:

			static void UpdateAnimation(RE::TESObjectREFR* a_this, float a_delta);
			static inline REL::Relocation<decltype(UpdateAnimation)> _UpdateAnimation;
	};
}