// $Id$

#ifndef MSXREALTIME_HH
#define MSXREALTIME_HH

#include "Schedulable.hh"
#include "SettingListener.hh"
#include "EmuTime.hh"

namespace openmsx {

class Scheduler;
class IntegerSetting;
class BooleanSetting;

class RealTime : private Schedulable, private SettingListener
{
public:
	static RealTime& instance();

	/** Convert EmuTime to RealTime.
	  */
	double getRealDuration(const EmuTime& time1, const EmuTime& time2);

	/** Convert RealTime to EmuTime.
	  */
	EmuDuration getEmuDuration(double realDur);

	/** Check that there is enough real time left before we reach as certain
	  * point in emulated time.
	  * @param us Real time duration is micro seconds.
	  * @param time Point in emulated time.
	  */
	bool timeLeft(unsigned long long us, const EmuTime& time);

	/** Synchronize EmuTime with RealTime.
	  * @param time The current emulation time.
	  * @param allowSleep Is this method allowed to sleep, typically the
	  *                   result of a previous call to timeLeft() is passed.
	  */
	void sync(const EmuTime& time, bool allowSleep);

private:
	RealTime();
	virtual ~RealTime();

	// Schedulable
	virtual void executeUntil(const EmuTime& time, int userData);
	virtual const std::string& schedName() const;

	// SettingListener
	void update(const Setting* setting);

	void internalSync(const EmuTime& time, bool allowSleep);
	void resync();

	BooleanSetting& throttleSetting;
	IntegerSetting& speedSetting;
	BooleanSetting& pauseSetting;
	BooleanSetting& powerSetting;

	unsigned long long idealRealTime;
	EmuTime emuTime;
	double sleepAdjust;
};

} // namespace openmsx

#endif
