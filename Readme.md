# DemoPlugin

## how to build

```cpp
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

## What is it for :

if there is a singleton used by the app and the plugin (or any static variable), 
when the plugin is loaded, the singleton accessed from the plugin is initialized

so the singleton accessed from the app and accessed from the plugin are not the same,
so the datas inside are not the same too.

in the singleton here there is a var m_Name who have default value : "Default"
the singleton m_Name was defined as "App" in the app

in the main.cpp of the app : the "Singleton::Instance()->print();" will print :
```
Singleton::print() : my name is App
```

so if you go in APlugin in the common lib (who is the base class for plugin)

```cpp
bool APlugin::Init(Singleton* vGuiHelperPtr)
{
	// the static instance of the singleton was reinit during the plugin loading
	Singleton::Instance()->print();

	// so we transfer the singleton instance from the app to the plugin
	Singleton::Instance(vGuiHelperPtr);
	Singleton::Instance()->print();

	return true;
}
```

the first "Singleton::Instance()->print()" is the singleton initialized in the plugin
and will print : 
```
Singleton::print() : my name is Default
```

So after we transfer the singleton instance pointer from the app to the one in the plugin
so the second "Singleton::Instance()->print()" is the singleton initialized from the App
and will print : 
```
Singleton::print() : my name is App
```

we must pay attention to any static vars used everywhere when we have plugins in our app
