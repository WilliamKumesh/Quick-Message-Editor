#pragma once
#include <string>
#include <unordered_map>
#include <fstream>

class PrefixTree final
{
	class PrefixNode final
	{
		std::unordered_map<char, PrefixNode> transition;
		size_t word_frequency{};
		bool is_end_of_word = false;
	public:
		PrefixNode() = default;

		[[nodiscard]] std::unordered_map<char, PrefixNode>& GetTransition() noexcept
		{
			return transition;
		}

		[[nodiscard]] bool GetState() const noexcept
		{
			return is_end_of_word;
		}

		[[nodiscard]] size_t GetWordFrequency() const noexcept
		{
			return word_frequency;
		}

		void IncreaseWordFrequency() noexcept
		{
			word_frequency++;
		}

		void SetState(bool state) noexcept
		{
			is_end_of_word = state;
		}
	};

	PrefixNode root;
public:
	PrefixTree() = default;
	[[nodiscard]]const PrefixNode& GetRoot() const noexcept
	{
		return root;
	}
	void IncreaseWordWay(const std::string& input_string);
	void Add(const std::string& input_str);
	[[nodiscard]]bool DeleteElement(const std::string& input_str);
	void SaveTreeToFile(std::ofstream& file_out);
};