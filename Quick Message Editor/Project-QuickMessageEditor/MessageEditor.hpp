#pragma once
#include "PrefixTreeSearcher.hpp"
#include <fstream>

class MessageEditor final
{
	PrefixTree trie;
public:
	MessageEditor() = default;

	[[nodiscard]] std::string SuggestWord(const std::string& check_prefix) const noexcept;
	[[nodiscard]]bool IncreaseWordFrequency(const std::string& word);
	void AddNewWord(const std::string& new_word);
	[[nodiscard]]bool SearchCertainWord(const std::string& check_word) const noexcept;
	void SaveDictionaryToFile(std::ofstream& out_file);
};

[[nodiscard]]MessageEditor CreateMessageEditor(std::ifstream& file_input);