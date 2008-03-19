// $Id$

#include "WavAudioInput.hh"
#include "PlugException.hh"
#include "FilenameSetting.hh"
#include "CliComm.hh"
#include "WavData.hh"

using std::string;

namespace openmsx {

WavAudioInput::WavAudioInput(CommandController& commandController)
	: audioInputFilenameSetting(new FilenameSetting(
		commandController, "audio-inputfilename",
		"filename of the file where the sampler reads data from",
		"audio-input.wav"))
	, reference(EmuTime::zero)
	, plugged(false)
{
	audioInputFilenameSetting->attach(*this);
}

WavAudioInput::~WavAudioInput()
{
	audioInputFilenameSetting->detach(*this);
}

void WavAudioInput::loadWave()
{
	wav.reset(new WavData(audioInputFilenameSetting->getValue(), 16, 0));
}

const string& WavAudioInput::getName() const
{
	static const string name("wavinput");
	return name;
}

const string& WavAudioInput::getDescription() const
{
	static const string desc(
		"Read .wav files. Can for example be used as input for "
		"samplers.");
	return desc;
}

void WavAudioInput::plugHelper(Connector& /*connector*/, const EmuTime& time)
{
	if (!wav.get()) {
		try {
			loadWave();
		} catch (MSXException& e) {
			throw PlugException("Load of wave file failed: " +
			                    e.getMessage());
		}
	}
	reference = time;
	plugged = true;
}

void WavAudioInput::unplugHelper(const EmuTime& /*time*/)
{
	wav.reset();
	plugged = false;
}

void WavAudioInput::update(const Setting& setting)
{
	(void)setting;
	assert(&setting == audioInputFilenameSetting.get());
	if (plugged) {
		try {
			loadWave();
		} catch (MSXException& e) {
			// TODO proper error handling, message should go to console
			setting.getCommandController().getCliComm().printWarning(
				"Load of wave file failed: " + e.getMessage());
		}
	}
}

short WavAudioInput::readSample(const EmuTime& time)
{
	if (wav.get()) {
		unsigned pos = (time - reference).getTicksAt(wav->getFreq());
		if (pos < wav->getSize()) {
			const short* buf =
				static_cast<const short*>(wav->getData());
			return buf[pos];
		}
	}
	return 0;
}

} // namespace openmsx
