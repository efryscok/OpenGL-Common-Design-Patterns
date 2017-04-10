#pragma once

class CSingleton {
private:
	// Override the copy constructors and make inaccessible
	CSingleton(CSingleton const&) = delete;
	CSingleton& operator=(CSingleton const&) = delete;

protected:
	// Constructors/Destructors
	CSingleton() {};
	virtual ~CSingleton() {};
};