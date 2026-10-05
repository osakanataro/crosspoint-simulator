#include "HalOtaSlot.h"

// The host has no second application slot, so the inactive slot is reported
// as absent: the SD font flash copy (SdCardFontCache) then sees zero capacity
// and the firmware runs its SD-only path.

HalOtaSlot HalOtaSlot::inactive() { return HalOtaSlot(); }

HalOtaSlot::RunningImageState HalOtaSlot::runningImageState() {
  return RunningImageState::Untracked;
}

bool HalOtaSlot::safeForScratchWrite() const { return false; }

bool HalOtaSlot::contains(size_t, size_t) const { return false; }

bool HalOtaSlot::read(size_t, void *, size_t) const { return false; }

bool HalOtaSlot::erase(size_t, size_t) const { return false; }

bool HalOtaSlot::write(size_t, const void *, size_t) const { return false; }
