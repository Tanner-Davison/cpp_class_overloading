#include <iostream>
#include "Entity.h"

using namespace std;

Entity::Entity(int pAge, int pMainMember, double pPtr, Vector2D vec)
	: age(pAge), mainMember(pMainMember), instance(++count), entityPtr(new double(pPtr)), location(vec) {
	cout << "Constructor invoked #:  " << this->instance << "\n";
}

//copy Constructor
Entity::Entity(const Entity& other)
	: mainMember(other.mainMember), age(other.age), instance(++count), entityPtr(new double(*other.entityPtr)), location(other.location) {
	cout << "Copy Constructor Invoked #: " << count << "\n";
}

//Move Constructor
Entity::Entity(Entity&& other) noexcept
	: age(other.age), mainMember(other.mainMember), instance(other.instance), entityPtr(other.entityPtr), location(other.location) {
	cout << "Move Constructor Invoked\n";

	other.entityPtr = nullptr;
}

//Destructor
Entity::~Entity() {
	if (this->entityPtr != nullptr) {
		delete entityPtr;
		this->entityPtr = nullptr;
		count--;
	}
}

//prefix increment;
Entity& Entity::operator++() {
	++age;
	++mainMember;
	++(*this->entityPtr);
	++location;
	return *this;
}

//postfix increment++;
Entity Entity::operator++(int) {
	Entity temp = *this;
	++(*this);
	return *this;
}

//preFix decrement;
Entity& Entity::operator--() {
	--age;
	--mainMember;
	--*this->entityPtr;
	--location;

	return *this;
}

//post fix decrement
Entity Entity::operator--(int) {
	Entity temp = *this;
	--(*this);
	return *this;
}

//copy assignment operator overloading
Entity& Entity::operator=(const Entity& other) {
	if (this == &other) {
		return *this;
	}
	delete entityPtr;
	mainMember = other.mainMember;
	this->entityPtr = new double(*other.entityPtr);
	this->location = other.location;
	this->age = other.age;
	cout << "copy assaignment overload invoked #: " << count << "\n";
	return *this;
}
//move assignment operator;
Entity& Entity::operator=(Entity&& other) noexcept {
	if (this != &other) {
		delete entityPtr;  // Clean up existing resource
		age = other.age;
		mainMember = other.mainMember;
		instance = other.instance;
		entityPtr = other.entityPtr;
		location = other.location;
		other.entityPtr = nullptr;
		cout << "move assaignment = operator invoked\n";
	}
	return *this;
}
//arithmatic operator overload;
Entity Entity::operator+ (const Entity& other) const {
	return Entity(this->age + other.age, this->mainMember + other.mainMember, *this->entityPtr + *other.entityPtr, location + other.location);
}
//addition overloaded operator
Entity Entity::add(const Entity& other) {
	return Entity(this->age += other.age, mainMember += other.mainMember, *entityPtr += *other.entityPtr, location + other.location);
}

//comparison overloaded operator
bool Entity::operator==(const Entity& other)const {
	return ((mainMember == other.mainMember) && (age == other.age));
}

//* overloaded multiply operator
Entity Entity::operator*(const Entity& other) const {
	return Entity(this->age, this->mainMember * other.mainMember);
}
//multiply overloaded operator
Entity Entity::multiply(const Entity& other) const {
	return Entity(this->age, this->mainMember * other.mainMember);
}
//member getters
int Entity::getAge() const {
	return this->age;
}
double Entity::getPointer()const {
	return *entityPtr;
}
int Entity::getAccess() const {
	return this->mainMember;
}

Vector2D Entity::getLocation()const {
	return this->location;
}

bool Entity::isEqual(const Entity& other)const {
	if (this->mainMember == other.mainMember) {
		return true;
	}
	else {
		return false;
	}
}

// member Setters functions
void Entity::setMainMember(int pAccess) {
	this->mainMember = pAccess;
}

void Entity::setAge(int pAge) {
	this->age = pAge;
}
void Entity::toString() const {
	cout << "Entity # " << this->instance << " "
		<< "\nage: " << this->age << " "
		<< "mainMember: " << this->mainMember
		<< " entityPtr: " << *this->entityPtr
		<< " " << "location x : "
		<< this->location.x << " " << "location y: " << this->location.y << "\n";
}
void Entity::setLocation(Vector2D vec) {
	location = vec;
}
//static member variables;
int Entity::count = 0;

Vector2D Vector2D::operator=(const Vector2D& other) {
	this->x = other.x;
	this->y = other.y;
	return *this;
}
Vector2D Vector2D::addToSelf(const Vector2D& other) {
	this->x += other.x;
	this->y += other.y;
	return *this;
}
Vector2D Vector2D::operator+(const Vector2D& other)const {
	return Vector2D(this->x + other.x, this->y + other.y);
}
void Vector2D::readLocation()const {
	cout << "location X: " << this->x << " location Y: " << this->y << "\n";
}
Vector2D& Vector2D::operator--() {
	this->x--;
	this->y--;
	return *this;
}
Vector2D Vector2D::operator--(int) {
	Vector2D temp;
	temp = --(*this);
	return temp;
}
Vector2D& Vector2D::operator++() {
	x++;
	y++;
	return *this;
}
Vector2D Vector2D::operator++(int) {
	Vector2D temp;
	temp = ++(*this);
	return temp;
}
//overloaded constructor
ArrayList::ArrayList(int lengthP) : length(lengthP), list(new char[lengthP]) {
	list = new char[length];

	for (int i = 0; i < length; i++) {
		list[i] = 'X';
	}
	cout << "ArrayList Created with default Constructor\n";
}
//Copy constructor
ArrayList::ArrayList(const ArrayList& other) :length(other.length), list(new char[other.length]) {
	for (int i = 0; i < other.length; i++) {
		this->list[i] = other.list[i];
	}
	cout << "ArrayList Created with copy constructor\n";
}
//Destructure
ArrayList::~ArrayList() {
	if (this->list != nullptr) {
		delete[] list;
		list = nullptr;
	}
}
//Assaignment operator 
ArrayList& ArrayList::operator=(const ArrayList& other) {
	if (this == &other) {
		return *this;
	}
	delete[] this->list;

	this->length = other.length;
	this->list = new char[length];
	for (int i = 0; i < length; i++) {
		this->list[i] = other.list[i];
	}
	cout << "ArrayList was assaigned to another ArrayList variable\n";
	return *this;
}
void ArrayList::printList()const {
	for (int i = 0; i < this->length; i++) {
		cout << this->list[i];
	}
	cout << endl;
}