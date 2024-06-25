#include "MessageEditor.hpp"

std::string MessageEditor::SuggestWord(const std::string& check_prefix) const noexcept
{
	return  PrefixTreeSearcher::SearchFillingWords(trie, check_prefix);
}

void MessageEditor::AddNewWord(const std::string& new_word)
{
	trie.Add(new_word);
}

bool MessageEditor::IncreaseWordFrequency(const std::string& word)
{
	if (SearchCertainWord(word))
	{
		trie.IncreaseWordWay(word);
		return true;
	}
	return false;
}

bool MessageEditor::SearchCertainWord(const std::string& check_word) const noexcept
{
	return PrefixTreeSearcher::SearchCertainWord(trie, check_word);
}

void MessageEditor::SaveDictionaryToFile(std::ofstream& out_file)
{
	trie.SaveTreeToFile(out_file);
}

MessageEditor CreateMessageEditor(std::ifstream& file_input)
{
	MessageEditor editor;

	std::string line_from_dictionary;

	while (std::getline(file_input, line_from_dictionary))
	{
		const auto space_pos = line_from_dictionary.find(' ');
		std::string word_from_dictionary = line_from_dictionary.substr(0, space_pos);
		const int word_count = std::stoi(line_from_dictionary.substr(space_pos, line_from_dictionary.size() - word_from_dictionary.size()));

		editor.AddNewWord(word_from_dictionary);

		for (int i = 0; i < word_count - 1; i++)
		{
			editor.IncreaseWordFrequency(word_from_dictionary);
		}
	}

	return editor;
}