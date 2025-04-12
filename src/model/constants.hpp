#pragma once

/// <summary>
/// here we define the constants for the forces.
/// </summary>
namespace constants
{
	constexpr ql::f64 MagneticForce = 1.0;
	constexpr ql::f64 GravityForce = 1.0;
	constexpr ql::f64 Friction = 0.0;

	constexpr ql::size ticks_per_second = 144ull;
	constexpr auto tick_time = 1.0 / ticks_per_second;
}
