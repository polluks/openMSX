#ifndef SAVESTATECLI_HH
#define SAVESTATECLI_HH

#include "CLIOption.hh"

namespace openmsx {

class CommandLineParser;

class SaveStateCLI final : public CLIOption, public CLIFileType
{
public:
	explicit SaveStateCLI(CommandLineParser& parser);
	void parseOption(const std::string& option,
	                 span<std::string>& cmdLine) override;
	std::string_view optionHelp() const override;
	void parseFileType(const std::string& filename,
	                   span<std::string>& cmdLine) override;
	std::string_view fileTypeHelp() const override;

private:
	CommandLineParser& parser;
};

} // namespace openmsx

#endif
