// $Id$

#include "DummyCassetteDevice.hh"

namespace openmsx {

void DummyCassetteDevice::setMotor(bool /*status*/, EmuTime::param /*time*/)
{
	// do nothing
}

short DummyCassetteDevice::readSample(EmuTime::param /*time*/)
{
	return 32767; // TODO check value
}

void DummyCassetteDevice::setSignal(bool /*output*/, EmuTime::param /*time*/)
{
	// do nothing
}

const std::string DummyCassetteDevice::getDescription() const
{
	const std::string EMPTY;
	return EMPTY;
}

void DummyCassetteDevice::plugHelper(Connector& /*connector*/,
                                     EmuTime::param /*time*/)
{
}

void DummyCassetteDevice::unplugHelper(EmuTime::param /*time*/)
{
}

} // namespace openmsx
