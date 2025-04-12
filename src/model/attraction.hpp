#pragma once

#include <ql/ql.hpp>
#include "constants.hpp"


/// <summary>
/// base class for all attractors.
/// </summary>
class Attractor
{
public:
	ql::f64 force = 1.0;
	ql::vec2d position = ql::vec(0, 0);

	virtual ql::vec2d get_resulting_force() const = 0;
};

class MagneticAttractor : public Attractor
{
 public:
	 ql::vec2d get_resulting_force() const override
	 {
		 return constants::MagneticForce * this->force;
	 }
};

class GravityAttractor : public Attractor
{
public:
	ql::vec2d get_resulting_force() const override
	{
		return constants::GravityForce * this->force * -1;
	}
};