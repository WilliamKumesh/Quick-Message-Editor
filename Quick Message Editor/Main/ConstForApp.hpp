#pragma once

constexpr char space = ' ', backspace = '\b', enter = '\n', exclamation = '!', coma = ',', dot = '.',
               question = '?', dash = '-', quot = '"';

constexpr float button_width = 400, button_height = 100;
constexpr unsigned int screen_width = 700, screen_height = 1000, max_char_value = 256, int_tab_value = 9,
button_character_size = 24, int_enter_value = 13;

const std::string text_file_name = "EditorText.txt";
const std::string dictionary_file_name = "Dictionary.txt";
const std::string back_ground_file_name = "BackGround.jpg";
const std::string font_file_name = "SlavicFont.ttf";

const std::string text_for_button = "Add word to dictionary\nClick empty zone to continue";
const std::string window_name = "Slavic Message Editor";

[[nodiscard]]inline bool check_punctuation(char symbol) noexcept
{
    if (symbol == exclamation || symbol == coma || symbol == dot || symbol == question || symbol == dash
        || symbol == quot)
    {
        return true;
    }
    return false;
}