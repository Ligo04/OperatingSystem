#include "menu.h"
#include<iostream>

#pragma warning(disable:26451)
Menu* Menu::mInstance = nullptr;

Menu* Menu::Instance() {
	if (mInstance == nullptr)
		mInstance = new Menu();
	return mInstance;
}

void Menu::SetTitle(std::string title)
{
	this->title = title;
}

void Menu::Display() {
	std::cout << title << std::endl;
	for (auto PAIR : SelectionCallBack)
	{
		std::cout << PAIR.first << std::endl;
	}
}

void Menu::GetInput() {
	std::cout << "ÇëÑ¡Ôñ" << std::endl;
	std::cin >> input;
}

void Menu::HandleInput() {
	SelectionCallBack[input - 1].second();
}

