// $Id$

#ifndef ROMGAMEMASTER2_HH
#define ROMGAMEMASTER2_HH

#include "RomBlocks.hh"

namespace openmsx {

class RomGameMaster2 : public Rom4kBBlocks
{
public:
	RomGameMaster2(MSXMotherBoard& motherBoard, const XMLElement& config,
	               std::auto_ptr<Rom> rom);
	virtual ~RomGameMaster2();

	virtual void reset(const EmuTime& time);
	virtual void writeMem(word address, byte value, const EmuTime& time);
	virtual byte* getWriteCacheLine(word address) const;

	template<typename Archive>
	void serialize(Archive& ar, unsigned version);

private:
	word sramOffset;
	bool sramEnabled;
};

REGISTER_MSXDEVICE(RomGameMaster2, "RomGameMaster2");

} // namespace openmsx

#endif
