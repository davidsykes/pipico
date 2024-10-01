#include "code_sequences_display_action.h"
#include <vector>
#include <sstream>

const std::string SEQUENCE_LINK = "/sequence/";

std::string CodeSequencesDisplayAction::Action()
{
	std::vector<CodeSequence> cs = codeSequenceRepository.GetCodeSequences();

	std::stringstream str;
	for (int s = 0; s < cs.size(); ++s)
	{
		if (s > 0)
		{
			str << "<br>";
		}
		str << buttonFormatter.FormatButton(cs[s].DisplayText, SEQUENCE_LINK + cs[s].Name);
	}

	return str.str();
}