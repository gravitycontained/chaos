#pragma once

#include <ql/ql.hpp>
#include <nlohmann/json.hpp>

namespace ql
{
	template <typename T>
	struct value_identifier
	{
		std::string_view identifier;
		T* const value;
	};

	template <typename T>
	constexpr auto create_identifier(T& value, const std::string_view& identifier)
	{
		return ql::value_identifier<T>{identifier, &value};
	}

	struct seralizer
	{
		template <typename T>
		void load(ql::value_identifier<T>& value, const nlohmann::json& json)
		{
			const auto& json_value = json[value.identifier];

			if constexpr (ql::is_standard_string_type<T>())
			{
				if (value.value != nullptr)
					*value.value = json_value;
			}
		}

		template <typename T>
		nlohmann::json parse(const ql::value_identifier<T>& value)
		{
			if constexpr (ql::is_standard_string_type<T>())
			{
				return *value.value;
			}
		}
	};
}	 // namespace ql
