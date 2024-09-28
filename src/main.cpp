#include <ql/ql.hpp>

int main()
{
	ql::cubic_generator_vec3 x;

	ql::aes_256_encrypted("hello world", "password");

	while (true)
	{
		x.update(0.2);
		ql::println("value: ", x.get());
	}
}