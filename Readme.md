# DemoPlugin

## how to build

```cpp
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

you can set the CMAKE var BUILD_SHARED_LIBS as ON 
if you want to have the common lib built in SHARED instead of STATIC

## Design

The app and the plugin are depending both of a static lib 
who contain The singleton and the plugina abstract

## Common as Static Library :

If there is a singleton used by the app and the plugin (or any static variable), 
when the plugin is loaded, the singleton accessed from the plugin is initialized.

So the singleton accessed from the app and accessed from the plugin are not the same.
So the datas inside are not the same too.

In the singleton here there is a var m_Name who have default value : "Default".
The singleton m_Name was defined as "App" in the app

In the main.cpp of the app : the "Singleton::Instance()->print();" will print :
```
Singleton::print() : my name is App
```

So if you go in APlugin in the common lib (who is the base class for plugin).
This code will be executed for each plugins :

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

The first "Singleton::Instance()->print()" is the singleton initialized in the plugin
and will print : 
```
Singleton::print() : my name is Default
```

So after we transfer the singleton instance pointer from the app to the one in the plugin.
Oo the second "Singleton::Instance()->print()" is the singleton initialized from the App
and will print : 
```
Singleton::print() : my name is App
```

We must pay attention to any static vars used everywhere when we have plugins in our app 
depending of a static common lib who embed the statics.

## Common as Shared Library :

when the app and pluign are depending of a lib build as sahred, there is no more static issue
all static's are shared (so no double instancing issues)