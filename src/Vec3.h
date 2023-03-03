#pragma once
#include <iostream>
#include <string>

template <typename T>
class Vec3{
	public:
		Vec3(T x, T y, T z):x(x), y(y), z(z){}
		Vec3(){}
		T x;
		T y;
		T z;

  static void print(Vec3<T> vec){
		std::cout<<vec.x<< " " << vec.y<< " " <<vec.z<<std::endl;
	}

	Vec3<T> operator - (const Vec3<T>& v){
		return Vec3<T>(x - v.x, y - v.y, z - v.z);
	}

	static float dot(Vec3<T> v1, Vec3<T> v2){
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}
};

typedef Vec3<float> Vec3f;
