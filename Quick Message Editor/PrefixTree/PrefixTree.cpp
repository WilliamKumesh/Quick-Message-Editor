#include "PrefixTree.hpp"
#include <stack>

void PrefixTree::Add(const std::string& input_str) 
{
	PrefixNode* node = &root;

	for (auto input_str_iterator : input_str)
	{
		std::unordered_map<char, PrefixNode>* node_transition = &node->GetTransition();

		auto is_char_it = node_transition->find(input_str_iterator);

		if (is_char_it != node_transition->end())
		{
			node = &is_char_it->second;
		}
		else
		{
			node_transition->insert(std::make_pair(input_str_iterator, PrefixNode()));
			node_transition->find(input_str_iterator)->second.IncreaseWordFrequency();
			node = &node_transition->find(input_str_iterator)->second;
		}
	}
	node->SetState(true);
}

void PrefixTree::IncreaseWordWay(const std::string& input_string)
{
	PrefixNode* node = &root;

	for (auto it : input_string)
	{
		std::unordered_map<char, PrefixNode>* node_transition = &node->GetTransition();

		if (auto num = node_transition->find(it); num != node_transition->end())
		{
			node = &num->second;
			node->IncreaseWordFrequency();
		}
	}
}

bool PrefixTree::DeleteElement(const std::string& input_str)
{
	PrefixNode* node = &root;

	for (auto it : input_str)
	{
		std::unordered_map<char, PrefixNode>* node_transition = &node->GetTransition();

		if (auto num = node_transition->find(it); num != node_transition->end())
		{
			node = &num->second;
		}
		else
		{
			return false;
		}
	}

	node->SetState(false);

	return true;
}

void PrefixTree::SaveTreeToFile(std::ofstream& file_out)
{
	if(root.GetTransition().begin() == root.GetTransition().end())
	{
		return;
	}

	std::stack<std::unordered_map<char, PrefixNode>::iterator> tree_stack;
	tree_stack.push(root.GetTransition().begin());

	std::string word;

	while(!tree_stack.empty())
	{
		auto current_node = tree_stack.top();
		word += current_node->first;

		if (current_node->second.GetState())
		{
			file_out << word << ' ' << current_node->second.GetWordFrequency() << '\n';
		}

		if(current_node->second.GetTransition().begin() != current_node->second.GetTransition().end())
		{
			tree_stack.push(current_node->second.GetTransition().begin());
		}
		else
		{
			bool is_root = false;
			current_node = tree_stack.top();
			tree_stack.pop();
			word.pop_back();
			if(tree_stack.empty())
			{
				if(++current_node == root.GetTransition().end())
				{
					return;
				}
				tree_stack.push(current_node);
				continue;
			}
			while (++current_node == tree_stack.top()->second.GetTransition().end())
			{
				current_node = tree_stack.top();
				word.pop_back();
				tree_stack.pop();
				if(tree_stack.empty())
				{
					if (++current_node != root.GetTransition().end())
					{
						tree_stack.push(current_node);
						is_root = true;
						break;
					}
					return;
				}
			}
			if (!is_root)
			{
				tree_stack.push(current_node);
			}
		}
	}
}