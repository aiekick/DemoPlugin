#pragma once

#include <string>

class Singleton {

private:
    std::string m_Name = "Default";

public:
	void setName(const std::string& vName);
	void print();

public:
	static Singleton* Instance(Singleton* vCopy = nullptr, bool vForce = false)
	{
		static Singleton _instance;
		static Singleton* _instance_copy = nullptr;
		if (vCopy || vForce)
			_instance_copy = vCopy;
		if (_instance_copy)
			return _instance_copy;
		return &_instance;
	}
};