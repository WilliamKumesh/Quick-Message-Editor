#include<iostream>
#include <fstream>
#include "MessageEditor.hpp"
#include "SFML/Graphics.hpp"
#include "ConstForApp.hpp"

using namespace sf;

int main()
{
    std::ifstream file_input(dictionary_file_name);
    MessageEditor editor = CreateMessageEditor(file_input);
    file_input.close();

    RenderWindow window(sf::VideoMode(screen_width, screen_height), window_name);
    View view(sf::FloatRect(0.f, 0.f, 700.f, 1000.f));
    window.setView(view);

    Texture texture;
    texture.loadFromFile(back_ground_file_name);
    Sprite sprite;
    sprite.setTexture(texture);

    Text text;
    Text suggested_text;
    Font font;
    font.loadFromFile(font_file_name);

    sf::Vector2u windowSize = window.getSize();
    float centerX = static_cast<float>(windowSize.x) / 2.f;
    float centerY = static_cast<float>(windowSize.y) / 2.f;

    sf::RectangleShape button(sf::Vector2f(button_width, button_height));
    button.setPosition(centerX - button.getSize().x / 2, centerY - button.getSize().y / 2);
    button.setFillColor(Color::White);
    Text button_text(text_for_button, font, button_character_size);
    button_text.setFillColor(Color::Black);
    button_text.setPosition(button.getPosition().x + button.getSize().x / 2 - button_text.getGlobalBounds().width / 2, 
        button.getPosition().y + button.getSize().y / 2 - button_text.getGlobalBounds().height / 2);
    bool condition = false;

    text.setFont(font);
    suggested_text.setFont(font);

    text.setFillColor(Color::Black);
    suggested_text.setFillColor(Color::Blue);

    std::string user_str;
    std::string suggested_str;
    std::string prefix;

    /// Обработка ввода

    while (window.isOpen())
    {
        Event event{};

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                std::ofstream file_out_dictionary(dictionary_file_name);
                std::ofstream file_out_text(text_file_name);
                editor.SaveDictionaryToFile(file_out_dictionary);
                file_out_text << text.getString().toAnsiString();
                file_out_dictionary.close();
                file_out_text.close();
                window.close();
            }
        }

        if (event.type == sf::Event::TextEntered && !condition)
        {
            if (event.text.unicode < max_char_value)
            {
                user_str += static_cast<char>(event.text.unicode);

                if (!check_punctuation(static_cast<char>(event.text.unicode)))
                {
                    prefix += static_cast<char>(event.text.unicode);
                }
            }

            if (event.text.unicode == int_enter_value)
            {
                user_str.pop_back();
                user_str += enter;

                prefix.pop_back();
                if (!prefix.empty() && suggested_str.empty() && !editor.SearchCertainWord(prefix))
                {
                    condition = true;
                }
                else
                {
                    prefix.clear();
                }
            }

            if (event.text.unicode == backspace)
            {
                user_str.pop_back();
                prefix.pop_back();
                if (!user_str.empty())
                {
                    user_str.pop_back();
                }
                if (!prefix.empty())
                {
                    prefix.pop_back();
                }
            }

            if (event.text.unicode == space)
            {
                prefix.pop_back();
                if (!prefix.empty() && suggested_str.empty() && !editor.SearchCertainWord(prefix))
                {
                    condition = true;
                }
                else
                {
                    prefix.clear();
                }
            }

            if (event.text.unicode == int_tab_value && !suggested_str.empty())
            {
                user_str.pop_back();
                prefix.pop_back();
                user_str += suggested_str;
                user_str += space;
                prefix += suggested_str;

                auto new_suggest_str = editor.SuggestWord(prefix);

                if (!new_suggest_str.empty())
                {
                    user_str.pop_back();
                    suggested_str = new_suggest_str;
                    continue;
                }

                editor.IncreaseWordFrequency(prefix);
                prefix.clear();
            }
        }

        /// Для нажатия кнопки добавления

        if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
        {
            sf::Vector2f mouse_local_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            if (button.getGlobalBounds().contains(mouse_local_position))
            {
            	condition = false;
                editor.AddNewWord(prefix);
                prefix.clear();
            }
            else
            {
                condition = false;
                prefix.clear();
            }
            continue;
        }

        /// Отрисовка слов и кнопки

        text.setString(user_str);

        sf::Vector2f text_pos = text.findCharacterPos(text.getString().getSize());

        suggested_str = editor.SuggestWord(prefix);

        if (user_str.empty() || user_str[user_str.size() - 1] == space || !prefix.empty() || user_str[user_str.size() - 1] == enter)
        {
            suggested_text.setPosition(text_pos.x, text_pos.y);
        }
        else
        {
            suggested_str.clear();
        }

        suggested_text.setString(suggested_str);

        sf::Vector2f suggested_text_pos = text.findCharacterPos(suggested_text.getString().getSize());

        if (suggested_text_pos.x + text_pos.x > static_cast<float>(screen_width))
        {
            user_str.pop_back();
            user_str += enter;
        }

        window.clear();
        window.draw(sprite);

        if (text_pos.y > static_cast<float>(screen_height))
        {
            std::ofstream file_output(dictionary_file_name);
            std::ofstream file_out_text(text_file_name);
            editor.SaveDictionaryToFile(file_output);
            file_out_text << text.getString().toAnsiString();
            file_out_text.close();
            file_output.close();
        	window.close();
        }

        if (condition)
        {
            window.draw(button);
            window.draw(button_text);
        }
        window.draw(text);
        window.draw(suggested_text);
        window.display();
    }

	return 0;
}