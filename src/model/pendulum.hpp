#pragma once

#include <ql/ql.hpp>
#include "attraction.hpp"

class Pendulum
{
public:
	ql::vec2d position = {0, 0};
	ql::vec2d velocity = {0, 0};

	void apply_attractors(const std::vector<Attractor>& attractors)
	{
		for (const auto& attractor : attractors)
		{
			auto difference = attractor.position - this->position;
			auto distance = difference.length();

			// avoid division by zero
			if (distance <= 0)
				continue;

			auto direction = difference.normalized();

			auto delta_velocity = (1.0 / std::pow(distance, 2)) * attractor.get_resulting_force() * direction;

			this->velocity += delta_velocity;
		}
	}

	void apply_friction()
	{
		this->velocity *= (1 - constants::Friction);
	}

	void move()
	{
		this->position += this->velocity;
	}

	void update(const std::vector<Attractor>& attractors)
	{
		this->apply_attractors(attractors);
		this->apply_friction();
		this->move();
	}
};