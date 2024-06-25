#include "PrefixTreeSearcher.hpp"

#include <iostream>

std::string PrefixTreeSearcher::SearchFillingWords(const PrefixTree& trie, const std::string& check_prefix) noexcept
{
	auto node = trie.GetRoot();

	if(node.GetTransition().empty())
	{
		return {};
	}

	std::string result_string;

	for (auto it : check_prefix)
	{
		auto node_transition = node.GetTransition();

		if (auto num = node_transition.find(it); num != node_transition.end())
		{
			node = num->second;
		}
		else
		{
			return {};
		}
	}

	if(node.GetTransition().begin() != node.GetTransition().end() && node.GetState())
	{
		result_string += node.GetTransition().begin()->first;
		auto new_node = node.GetTransition().begin()->second;
		node = new_node;
	}

	while (!node.GetState())
	{
		auto max_elem = node.GetTransition().begin();

		for (auto it = node.GetTransition().begin(); it != node.GetTransition().end(); ++it)
		{
			if (max_elem->second.GetWordFrequency() < it->second.GetWordFrequency())
			{
				max_elem = it;
			}
		}

		result_string += max_elem->first;
		auto new_node = max_elem->second;

		node = new_node;
	}

	return result_string;
}

bool PrefixTreeSearcher::SearchCertainWord(const PrefixTree& trie, const std::string& check_string) noexcept
{
	auto node = trie.GetRoot();

	for (auto it : check_string)
	{
		auto node_transition = node.GetTransition();

		if (auto num = node_transition.find(it); num != node_transition.end())
		{
			node = num->second;
		}
		else
		{
			return false;
		}
	}

	return node.GetState();
}