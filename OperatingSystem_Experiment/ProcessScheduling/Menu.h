#pragma once
#include <string>
#include <functional>
#include <memory>
#include <vector>
class Menu
{
public:
	~Menu() = default;
	// 设置菜单标题
	void SetTitle(std::string title);

	// 显示菜单选项
	void Display();
	// 接受输入
	void GetInput();
	// 处理输入
	void HandleInput();
	//获取单例
	static Menu* Instance();

private:
	Menu() = default;
public:
	// 菜单选项
	std::vector<std::pair<std::string, std::function<void(void)>>> SelectionCallBack;
private:
	// 菜单输入
	int input;
	// 菜单标题
	std::string title;
	// 菜单类单例
	static Menu* mInstance;
};