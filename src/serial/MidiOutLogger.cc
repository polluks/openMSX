// $Id$

#include "MidiOutLogger.hh"
#include "PlugException.hh"
#include "FilenameSetting.hh"
#include "FileOperations.hh"
#include "serialize.hh"

namespace openmsx {

MidiOutLogger::MidiOutLogger(CommandController& commandController)
	: logFilenameSetting(new FilenameSetting(
		commandController, "midi-out-logfilename",
		"filename of the file where the MIDI output is logged to",
		"/dev/midi"))
{
}

void MidiOutLogger::plugHelper(Connector& /*connector*/,
                               EmuTime::param /*time*/)
{
	FileOperations::openofstream(file, logFilenameSetting->getValue());
	if (file.fail()) {
		file.clear();
		throw PlugException("Error opening log file");
	}
}

void MidiOutLogger::unplugHelper(EmuTime::param /*time*/)
{
	file.close();
}

const std::string& MidiOutLogger::getName() const
{
	static const std::string name("midi-out-logger");
	return name;
}

const std::string MidiOutLogger::getDescription() const
{
	return	"Midi output logger. Log all data that is sent to this "
		"pluggable to a file. The filename is set with the "
		"'midi-out-logfilename' setting.";
}

void MidiOutLogger::recvByte(byte value, EmuTime::param /*time*/)
{
	if (file.is_open()) {
		file.put(value);
		file.flush();
	}
}

template<typename Archive>
void MidiOutLogger::serialize(Archive& /*ar*/, unsigned /*version*/)
{
	// don't try to resume a previous logfile (see PrinterPortLogger)
}
INSTANTIATE_SERIALIZE_METHODS(MidiOutLogger);
REGISTER_POLYMORPHIC_INITIALIZER(Pluggable, MidiOutLogger, "MidiOutLogger");

} // namespace openmsx
