// $Id$

#include "DummyPrinterPortDevice.hh"

namespace openmsx {

bool DummyPrinterPortDevice::getStatus(EmuTime::param /*time*/)
{
	return true; // true = high = not ready
}

void DummyPrinterPortDevice::setStrobe(bool /*strobe*/, EmuTime::param /*time*/)
{
	// ignore strobe
}

void DummyPrinterPortDevice::writeData(byte /*data*/, EmuTime::param /*time*/)
{
	// ignore data
}

const std::string DummyPrinterPortDevice::getDescription() const
{
	const std::string EMPTY;
	return EMPTY;
}

void DummyPrinterPortDevice::plugHelper(
	Connector& /*connector*/, EmuTime::param /*time*/)
{
}

void DummyPrinterPortDevice::unplugHelper(EmuTime::param /*time*/)
{
}

} // namespace openmsx
