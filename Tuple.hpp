
#pragma once

class Tuple  
{
	private:
		//Tuple Components
		double w;
		double x;
		double y;
		double z;
	public:

		Tuple();
		//w can differentiate between vectors and points, otherwise it can be used in any other way.
		Tuple(double x, double y, double z, double w);
		~Tuple();
		static Tuple Point(double x, double y, double z);
		static Tuple Vector(double x, double y, double z);

		//If one of these returns true, the other will return false.
		bool isPoint();
		bool isVector();
		//Only for use with vectors
		double magnitude();
		Tuple normalize();
		double dot(const Tuple& t);
		Tuple cross(const Tuple& t);
		Tuple reflect(const Tuple& normal);

		double W() const;
		double X() const;
		double Y() const;
		double Z() const;

		bool operator==(const Tuple& t);
		Tuple operator+(const Tuple& t) const;
		Tuple operator-() const;
		Tuple operator-(const Tuple& t) const;
		Tuple operator*(const double t) const;
		Tuple operator/(const double t) const;

};