#pragma once
#include <string>
#include "PrefixTree.hpp"

class PrefixTreeSearcher final
{
public:
	PrefixTreeSearcher() = delete;

	[[nodiscard]]static std::string SearchFillingWords(const PrefixTree& trie, const std::string& check_prefix) noexcept;

	[[nodiscard]]static bool SearchCertainWord(const PrefixTree& trie, const std::string& check_string) noexcept;
};
