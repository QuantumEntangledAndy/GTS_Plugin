[![CI](https://github.com/QuantumEntangledAndy/GTS_Plugin/actions/workflows/build.yml/badge.svg)](https://github.com/QuantumEntangledAndy/GTS_Plugin/actions/workflows/build.yml)

# Size Matters SKSE64 Plugin

This is the source for the Gianttess mod Size matters SKSE plugin.

WIP

---

## Feature Wish List

- [ ] Auto scale height to room
- [ ] Correct bumper for height 
- [ ] Talk to actor when crouching
- [ ] Disable size effects when standing still so enemies won't be pushed around, doesn't really makes sense
- [ ] Accurate Body Collision that inflicts size effects on contact instead of using cloak magiceffects
- [ ] Proper headtracking instead of bugged one (NPC's have headtracking of the x1.00 scale towards player, player HT needs fixing too)
- [ ] Ability to edit HitBoxes so it'll be possible to have Giant Enemies/Have more accurate hitbox
  - AABB was shared between all actors of the same skeleton
  - Found a way to clone the AABB and make them unique to each actor
- [ ] Ability to spawn dust effect explosions literally under the feet, not under center of character. Ideally even scale them.
- [x] Automatic High-Heel module that dynamically adjusts high heel size based on Root scale.
- [x] In the perfect scenario, repair Animation Speed based on size
- [ ] If possible, transfer from SkyrimPlatform to Pure DLL, so SP won't be needed
- [ ] Make DLL track Giantess PC/NPC footsteps to shake the screen/place dust without lags at the point of footstep. Currently it has a delay because of script latency.
- [ ] Ray-Casted Vore with some radius instead of dialogue. Vore on button press if conditions are met. No more than 1 target at once.
- [ ] Blood on the feet after crushing (Not sure how to do it at all)
- [ ] Quest progression ui/current size ui
- [ ] Vore anim
- [ ] Vore belly

## Easier Things
- [ ] Scale
  - [x] Change scale in papyrus
  - [ ] Get height in meters of any actor
  - [ ] Get volume of any actor
- [ ] Mechanics  
  - [ ] Apply size effects to near by actor
  - [x] Move away from favor active
  - [x] Animation speed adjustment
- [ ] Walk/Jump events
  - [x] Camera distance to event
  - [ ] Camera shake
  - [ ] Feet sounds
