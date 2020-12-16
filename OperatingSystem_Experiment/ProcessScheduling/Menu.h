#pragma once
#include <string>
#include <functional>
#include <memory>
#include <vector>
class Menu
{
public:
	~Menu() = default;
	// ���ò˵�����
	void SetTitle(std::string title);

	// ��ʾ�˵�ѡ��
	void Display();
	// ��������
	void GetInput();
	// ��������
	void HandleInput();
	//��ȡ����
	static Menu* Instance();

private:
	Menu() = default;
public:
	// �˵�ѡ��
	std::vector<std::pair<std::string, std::function<void(void)>>> SelectionCallBack;
private:
	// �˵�����
	int input;
	// �˵�����
	std::string title;
	// �˵��൥��
	static Menu* mInstance;
};