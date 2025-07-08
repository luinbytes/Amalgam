#include "../SDK/SDK.h"

MAKE_SIGNATURE(CRendering3dView_EnableWorldFog, "client.dll", "40 53 48 83 EC ? 48 8B 0D ? ? ? ? 48 89 74 24", 0x0);

MAKE_HOOK(CRendering3dView_EnableWorldFog, S::CRendering3dView_EnableWorldFog(), void,
	)
{
#ifdef DEBUG_HOOKS
	if (!Vars::Hooks::CRendering3dView_EnableWorldFog[DEFAULT_BIND])
		return CALL_ORIGINAL();
#endif

	if (!(Vars::Visuals::World::Modulations.Value & Vars::Visuals::World::ModulationsEnum::Fog) || I::EngineClient->IsTakingScreenshot() && Vars::Visuals::UI::CleanScreenshots.Value)
		return CALL_ORIGINAL();

	if (!Vars::Colors::FogModulation.Value.a)
		return;

	CALL_ORIGINAL();
	if (auto pRenderContext = I::MaterialSystem->GetRenderContext())
	{
		float blend[3] = { float(Vars::Colors::FogModulation.Value.r) / 255.f, float(Vars::Colors::FogModulation.Value.g) / 255.f, float(Vars::Colors::FogModulation.Value.b) / 255.f };
		pRenderContext->FogColor3fv(blend);
	}
}