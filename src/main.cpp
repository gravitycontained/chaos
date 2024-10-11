#include <ql/ql.hpp>
#include <ql/graphic/graphic.hpp>

#include "fix-vcxproj.hpp"

struct test
{
	std::string to_string() const
	{
		return "test";
	}
};


struct point
{
	ql::f64 mass;
	ql::vec2 velocity;
	ql::vec2 position;

	ql::circle circle;
	ql::circular_array<ql::vec2> fade_outs;
	ql::thick_lines lines;
	ql::sprite light_sprite;

	void create(ql::f64 mass, ql::vec2 velocity, ql::vec2 position)
	{
		this->position = position;
		this->mass = mass;
		this->velocity = velocity;

		this->apply_radius();
		this->apply_position();

		auto color = ql::get_random_color();
		this->circle.set_color(color.grayified(0.5));

		this->fade_outs.resize(50);

		this->light_sprite.set_color(color.intensified(0.5).with_alpha(50));
		this->light_sprite.set_texture(ql::get_texture("light"));
	}

	void apply_radius()
	{
		auto log = std::log(this->mass);
		this->circle.set_radius(log);
		this->circle.set_outline_color(ql::rgb(10, 10, 10));
		this->circle.set_outline_thickness(log * 0.5);
		this->light_sprite.set_scale(log / 10);
	}

	void apply_position()
	{
		this->circle.set_center(this->position);
		this->light_sprite.set_center(this->position);
	}

	void consider_gravity(ql::f64 frame_time, const std::vector<point>& others, ql::size current_index)
	{
		constexpr ql::f64 G = 10;	// gravitational constant in m^3 kg^-1 s^-2

		for (ql::size i = 0; i < others.size(); ++i)
		{
			if (i == current_index)
				continue;

			const point& other = others[i];

			ql::vec2 r = other.position - this->position;
			ql::f64 distance_squared = std::pow(r.length(), 2);

			ql::vec2 force = (G * this->mass * other.mass / distance_squared) * r.normalized();

			ql::vec2 acceleration = force / this->mass;
			this->velocity += acceleration * frame_time;
		}
	}

	void update(const ql::event_info& event, ql::f64 time_factor, bool add_fade_out)
	{
		this->position += this->velocity * event.frame_time_f() * time_factor;

		auto dimension = event.screen_dimension();

		auto margin = 300;
		auto decrease = 0.5f;

		if (this->position.x < -margin)
		{
			this->position.x = -margin;
			this->velocity.x *= -(1.0f - decrease);
		}
		else if (this->position.x > dimension.x + margin)
		{
			this->position.x = dimension.x + margin;
			this->velocity.x *= -(1.0f - decrease);
		}

		if (this->position.y < -margin)
		{
			this->position.y = -margin;
			this->velocity.y *= -(1.0f - decrease);
		}
		else if (this->position.y > dimension.y + margin)
		{
			this->position.y = dimension.y + margin;
			this->velocity.y *= -(1.0f - decrease);
		}

		this->apply_position();

		if (add_fade_out)
		{
			this->fade_outs.add(this->circle.get_center());

			this->lines.clear();
			for (ql::size i = 0u; i < this->fade_outs.used_size(); ++i)
			{
				auto center = this->fade_outs.get_previous(i);

				auto progress = 1 - ql::f64_cast(i) / this->fade_outs.used_size();
				auto log = std::log(this->mass) / 2;

				auto color = this->circle.get_color().intensified(-0.3f).brightened(0.2f);
				this->lines.add_thick_line(center, color, log * progress);
			}
		}
	}

	void draw(ql::draw_object& draw) const
	{
		draw.draw(this->lines);
		draw.draw(this->circle);
		draw.draw(this->light_sprite);
	}
};

struct points
{
	std::vector<point> points;
	ql::f64 time_factor = 1.0;
	ql::small_clock fade_out_timer;

	void spawn_point(ql::vec2 dimension)
	{
		auto mass = std::pow(10, ql::random(3.0, 9.0));
		auto position = ql::random(dimension);
		auto velocity = ql::random(ql::vec(-1.0, -1.0), ql::vec(1.0, 1.0)) * 5;

		point point;
		point.create(mass, velocity, position);
		this->points.emplace_back(std::move(point));
	}

	void check_collision()
	{
		for (ql::size i = 0u; i < this->points.size(); ++i)
		{
			auto& a = this->points[i];
			for (ql::size j = 0u; j < this->points.size(); ++j)
			{
				if (i == j)
				{
					continue;
				}
				auto& b = this->points[j];

				auto a_pos = a.position;
				auto b_pos = b.position;

				auto distance = (a_pos - b_pos).length();
				auto length = a.circle.get_radius() + b.circle.get_radius();
				if (distance < length / 4)
				{
					if (a.mass > b.mass)
					{
						a.mass += b.mass;
						a.apply_radius();

						ql::remove_index(this->points, j);
					}
					else
					{
						b.mass += a.mass;
						b.apply_radius();

						ql::remove_index(this->points, i);
					}
					this->check_collision();
					return;
				}
			}
		}
	}

	void check_too_fast_points()
	{
		for (ql::size i = 0u; i < this->points.size(); ++i)
		{
			auto& point = this->points[i];
			if (point.velocity.length() > 50000)
			{
				ql::remove_index(this->points, i);
				this->check_too_fast_points();
				return;
			}
		}
	}

	void update(const ql::event_info& event)
	{
		bool add_fade_out = false;
		if (this->fade_out_timer.has_elapsed((1.0 / this->time_factor) * (1.0 / 1500)))
		{
			this->fade_out_timer.reset();
			add_fade_out = true;
		}
		for (ql::size i = 0u; i < this->points.size(); ++i)
		{
			auto& point = this->points[i];
			auto f = event.frame_time_f();

			point.consider_gravity(f * this->time_factor, this->points, i);
			point.update(event, this->time_factor, add_fade_out);
		}

		// this->check_collision();
		// this->check_too_fast_points();
	}

	void draw(ql::draw_object& draw) const
	{
		draw.draw(this->points);
	}
};

struct main_state : ql::base_state
{
	void init() override
	{
		for (ql::size i = 0u; i < 2; ++i)
		{
			this->points.spawn_point(this->dimension());
		}
		this->speed_slider.set_position({10, 10});
		this->speed_slider.set_range(-5.0, 5.0, 0.0);
		this->speed_slider.set_knob_dimension({20, 20});

		this->call_on_resize();
	}

	void call_on_resize() override
	{
		this->speed_slider.set_dimension(ql::vec(this->dimension().x - 100, 20));
		this->view.set_hitbox(*this);

		ql::hitbox hitbox;
		hitbox.set_dimension(this->dimension());
		hitbox.increase(300);
		this->border.set_color(ql::rgb(20, 20, 30));
		this->border.set_hitbox(hitbox);
		this->border.set_outline_thickness(20.0);
		this->border.set_outline_color(ql::rgb(100, 100, 150));
	}

	void updating() override
	{
		this->update(this->speed_slider);

		if (this->speed_slider.value_was_modified())
		{
			this->points.time_factor = std::pow(10.0, this->speed_slider.get_value());
		}

		this->view.allow_dragging = !(this->speed_slider.hovering_over_background || this->speed_slider.dragging);
		this->update(this->view);

		this->update(this->points);

		if (this->event().key_holding(sf::Keyboard::Space))
		{
			for (ql::size i = 0u; i < 2; ++i)
			{
				this->points.spawn_point(this->dimension());
			}
		}
	}

	void drawing() override
	{
		this->draw(this->border, this->view);
		this->draw(this->points, this->view);
		this->draw(this->speed_slider);
	}

	points points;
	ql::view_control view;
	ql::slider<ql::f64> speed_slider;
	ql::rectangle border;
};

int main()
try
{
	constexpr auto tuple = ql::to_tuple(1, std::array{5, 6, 7}, 3, ql::to_tuple(4, 5, test{}), std::make_pair(4, "ok���"));

	auto str = ql::to_string(tuple);
	ql::println(tuple);

	ql::state_manager state_manager;
	state_manager.set_title("ql");
	state_manager.add_texture("light", "resources/light.png");
	state_manager.set_antialiasing_level(12);
	state_manager.set_dimension({1400u, 950u});

	state_manager.add_state<main_state>();
	state_manager.game_loop();
}
catch (const std::exception& any)
{
	ql::println("exception: ", any.what());
}